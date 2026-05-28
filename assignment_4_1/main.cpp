#include <cpprest/http_client.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>
#include <cpprest/details/basic_types.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

struct student
{
public:
    int id = 0;
    std::string name;
    std::string email;
    int year = 2001;
};

// connect to the server at localhost:5000
http_client connectToServer()
{
    http_client client(U("http://localhost:5000"));
    return client;
}

void readStudents(http_client client)
{
    client.request(methods::GET, uri_builder(U("/students/")).to_string())
        .then([](const http_response &response)
              {
            if(response.status_code() == status_codes::OK)
            {
                return response.extract_json();
            }
            return pplx::task<json::value>([](){return json::value();}); })
        .then([](json::value jsonValue)
              {
                        if(jsonValue.is_null())
            {
                return;
            }

            std::vector<student> students;
            for(auto& student : jsonValue.as_array())
            {
                struct student s;
                s.id = student[U("id")].as_integer();
                s.name = student[U("name")].as_string();
                s.email = student[U("email")].as_string();
                s.year = student[U("year")].as_integer();
                students.push_back(s);
            }

            for(auto& s : students)
            {
                std::cout << "id: " << s.id << ", name: ";
                std::cout << s.name << ", email: " << s.email << ", year: ";
                std::cout << s.year << std::endl;
            } })
        .wait();
}

void getStudentByID(http_client client, int id)
{
    utility::string_t path(to_string(id));
    client.request(methods::GET, uri_builder(U("/students/")).append_path(path).to_string())
        .then([](const http_response &response)
              {
                  if (response.status_code() == status_codes::OK)
                  {
                      return response.extract_json();
                  }
                  else if (response.status_code() == status_codes::NotFound)
                  {
                      std::cout << "Student not found" << std::endl;
                      return pplx::task<json::value>([]()
                                                     { return json::value(); });
                  }else{
                      return pplx::task<json::value>([]()
                                                     { return json::value(); });
                  } })
        .then([](json::value jsonValue)
              {
            if(jsonValue.is_null())
            {
                return;
            }

            student s;
            s.id = jsonValue[U("id")].as_integer();
            s.name = jsonValue[U("name")].as_string();
            s.email = jsonValue[U("email")].as_string();
            s.year = jsonValue[U("year")].as_integer();
            std::cout << "id: " << s.id << ", name: ";
            std::cout << s.name << ", email: " << s.email << ", year: ";
            std::cout << s.year << std::endl; })
        .wait();
}

void addStudent(http_client client, const student &s)
{
    json::value jsonValue;
    jsonValue[U("name")] = json::value(s.name);
    jsonValue[U("email")] = json::value(s.email);
    jsonValue[U("year")] = json::value(s.year);

    client.request(methods::POST, uri_builder(U("/students/")).to_string(), jsonValue)
        .then([](const http_response &response)
              {
            if(response.status_code() == status_codes::Created)
            {
                // get the student id
                return response.extract_json();
            }else{
                return pplx::task<json::value>([](){return json::value();});
            } })
        .then([](json::value jsonValue)
              {
                        if(jsonValue.is_null())
            {
                return;
            }

            student s;
            s.id = jsonValue[U("id")].as_integer();
            s.name = jsonValue[U("name")].as_string();
            s.email = jsonValue[U("email")].as_string();
            s.year = jsonValue[U("year")].as_integer();

            std::cout << "Added student: id: " << s.id << ", name: ";
            std::cout << s.name << ", email: " << s.email << ", year: ";
            std::cout << s.year << std::endl; })
        .wait();
}

void updateStudent(http_client client, const student &s)
{
    json::value jsonValue;
    jsonValue[U("id")] = json::value(s.id);
    jsonValue[U("name")] = json::value(s.name);
    jsonValue[U("email")] = json::value(s.email);
    jsonValue[U("year")] = json::value(s.year);

    utility::string_t path(to_string(s.id));
    client.request(methods::PUT, uri_builder(U("/students/")).append_path(path).to_string(), jsonValue)
        .then([](const http_response &response)
              {
            if(response.status_code() == status_codes::OK)
            {
                cout << "Student was edited successfully" << endl;            
            }else if(response.status_code() == status_codes::NotFound)
            {
                cout << "Student not found" << endl;
            } })
        .wait();
}

void deleteStudent(http_client client, int id)
{
    utility::string_t path(to_string(id));
    client.request(methods::DEL, uri_builder(U("/students/")).append_path(path).to_string())
        .then([](const http_response &response)
              {
            if(response.status_code() == status_codes::NoContent)
            {
                cout << "Student was removed successfully" << endl;
            }else if(response.status_code() == status_codes::NotFound)
            {
                cout << "Student not found" << endl;
            } })
        .wait();
}

int main()
{
    http_client client = connectToServer();
    student temp;
    int choice, id;
    do
    {
        cout << "1. Read all students" << endl;
        cout << "2. Read student by id" << endl;
        cout << "3. Add student" << endl;
        cout << "4. Update student" << endl;
        cout << "5. Delete student" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            readStudents(client);
            break;
        case 2:
            cout << "Enter student id: ";
            cin >> id;
            getStudentByID(client, id);
            break;
        case 3:
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, temp.name);
            cout << "Enter student email: ";
            getline(cin, temp.email);
            cout << "Enter student year: ";
            cin >> temp.year;
            addStudent(client, temp);
            break;
        case 4:
            cout << "Enter student id: ";
            cin >> temp.id;
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, temp.name);
            cout << "Enter student email: ";
            getline(cin, temp.email);
            cout << "Enter student year: ";
            cin >> temp.year;
            updateStudent(client, temp);
            break;
        case 5:
            cout << "Enter student id: ";
            cin >> id;
            deleteStudent(client, id);
            break;
        case 6:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 6);
    return 0;
}
