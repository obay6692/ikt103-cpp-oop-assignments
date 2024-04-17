#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>

//Hei
#include <iostream>
#include <string>
#include <limits>

using namespace web::http;
using namespace web::http::client;
using namespace utility;
using namespace web;

// Extract JSON data in a robust way
utility::string_t extract_json_string(const json::value& data, const utility::string_t& field) {
    if (!data.has_field(field)) return U("");
    if (data.at(field).is_string()) return data.at(field).as_string();
    if (data.at(field).is_integer()) return conversions::to_string_t(std::to_string(data.at(field).as_integer()));
    return U("");
}

int extract_json_integer(const json::value& data, const utility::string_t& field) {
    if (!data.has_field(field) || !data.at(field).is_integer()) return 0;
    return data.at(field).as_integer();
}

// Declarations of main functionalities
void displayAllStudents(http_client &client);
void queryStudent(http_client &client);
void createNewStudent();
void updateStudent(http_client &client);
void deleteStudent(http_client &client);

int main() {
    http_client client(U("http://localhost:5000"));
    int menu_option = 0;
    do {
        ucout << "1. Show all students" << std::endl;
        ucout << "2. Search student by ID" << std::endl;
        ucout << "3. Enroll a new student" << std::endl;
        ucout << "4. Update student details" << std::endl;
        ucout << "5. Expel a student" << std::endl;
        ucout << "6. Close application" << std::endl;
        ucout << "Select an option: ";
        ucin >> menu_option;

        switch (menu_option) {
            case 1:
                displayAllStudents(client);
                break;
            case 2:
                queryStudent(client);
                break;
            case 3:
                createNewStudent();
                break;
            case 4:
                updateStudent(client);
                break;
            case 5:
                deleteStudent(client);
                break;
            case 6:
                ucout << "Shutting down the program." << std::endl;
                break;
            default:
                ucout << "Unknown choice. Please select again." << std::endl;
        }
    } while (menu_option != 6);
    return 0;
}

void displayAllStudents(http_client &client) {
    // Interaction message
    ucout << "Fetching data..." << std::endl;
    client.request(methods::GET, uri_builder(U("students")).to_string())
            .then([](const http_response &response) {
                if (response.status_code() != status_codes::OK) {
                    throw std::runtime_error("Error occurred: " + std::to_string(response.status_code()));
                }
                return response.extract_json();
            })
            .then([](json::value root) {
                for (const auto& student : root.as_array()) {
                    utility::string_t id = extract_json_string(student, U("id"));
                    utility::string_t name = extract_json_string(student, U("name"));
                    utility::string_t email = extract_json_string(student, U("email"));
                    int grade_level = extract_json_integer(student, U("year"));
                    ucout << U("id: ") << id << U(", name: ") << name << U(", email: ") << email << U(", year: ") << grade_level << std::endl;
                }
            })
            .wait();
}

void queryStudent(http_client &client) {
    utility::string_t studentId;
    ucout << "Type the student ID: ";
    ucin >> studentId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

    utility::string_t endpoint = U("/students/") + studentId;
    client.request(methods::GET, endpoint)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    std::cout << "No student found with that ID" << std::endl;
                    return pplx::task_from_result(json::value());
                }
            })
            .then([](json::value student_info) {
                if (!student_info.is_null() && !student_info.as_object().empty()) {
                    utility::string_t id = extract_json_string(student_info, U("id"));
                    utility::string_t name = extract_json_string(student_info, U("name"));
                    utility::string_t email = extract_json_string(student_info, U("email"));
                    int year = extract_json_integer(student_info, U("year"));
                    ucout << "id: " << id << ", name: " << name << ", email: " << email << ", year: " << year << std::endl;
                } else {
                    std::cout << "Student not found" << std::endl;
                }
            })
            .wait();
}
// Function to  create a new student
void createNewStudent() {
    utility::string_t base_url = U("http://localhost:5000");
    utility::string_t endpoint = U("/students/");
    http_client client(base_url);

    utility::string_t student_name, student_email;
    int student_year;

    // Handling input
    std::locale::global(std::locale(""));

    // Clearing input buffer
    ucin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    ucout << U("Student's name: ");
    std::getline(ucin, student_name);

    ucout << U("Student's email: ");
    std::getline(ucin, student_email);

    ucout << U("Student's class year: ");
    while (!(std::cin >> student_year)) {
        ucout << U("Please enter a valid year: ");
        ucin.clear();
        ucin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Clearing input buffer again
    ucin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    json::value new_student = json::value::object();
    new_student[U("name")] = json::value::string(student_name);
    new_student[U("email")] = json::value::string(student_email);
    new_student[U("year")] = json::value::number(student_year);

    // Sending request to server
    client.request(methods::POST, endpoint, new_student.serialize(), U("application/json"))
            .then([](http_response response) -> pplx::task<json::value> {
                if (response.status_code() == status_codes::OK || response.status_code() == status_codes::Created) {
                    return response.extract_json();
                } else {
                    ucout << U("Failed to enroll student. Error: ") << response.status_code() << std::endl;
                    return pplx::task_from_result(json::value());
                }
            })
            .then([](json::value response_body) {
                if (!response_body.is_null()) {
                    auto id = extract_json_string(response_body, U("id"));
                    auto name = extract_json_string(response_body, U("name"));
                    auto email = extract_json_string(response_body, U("email"));
                    auto year = extract_json_integer(response_body, U("year"));

                    ucout << U("Added student: ")
                          << U("id: ") << id
                          << U(", name: ") << name
                          << U(", email: ") << email
                          << U(", year: ") << year << std::endl;
                } else {
                    ucout << U("Addition of new student failed.") << std::endl;
                }
            })
            .wait();
}
// Function to edit a student and updatestudent.
void updateStudent(http_client &client) {
    utility::string_t base_url = U("http://localhost:5000");

    int student_id;
    utility::string_t new_name, new_email;
    int new_year;

    ucout << "Student ID for update: ";
    std::cin >> student_id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

    ucout << "New name for student: ";
    std::getline(ucin, new_name);

    ucout << "New email for student: ";
    std::getline(ucin, new_email);

    ucout << "New class year for student: ";
    while (!(ucin >> new_year)) {
        ucout << "Enter a valid year: ";
        std::wcin.clear();
        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Final clearing of the buffer

    utility::string_t student_endpoint = U("/students/") + conversions::to_string_t(std::to_string(student_id));

    json::value updated_student_data = json::value::object();
    updated_student_data[U("id")] = json::value::number(student_id);
    updated_student_data[U("name")] = json::value::string(new_name);
    updated_student_data[U("email")] = json::value::string(new_email);
    updated_student_data[U("year")] = json::value::number(new_year);

    // Update the student info on the server
    client.request(methods::PUT, student_endpoint, updated_student_data.serialize(), U("application/json"))
            .then([student_id](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    std::cout << "Student was edited successfully" << std::endl;
                } else {
                    std::cout << "Student not found" << std::endl;
                }
            }).wait();
}
// Function to del etestudent an existing student
void deleteStudent(http_client &client) {
    int student_id;
    std::cout << "ID of student to remove: ";
    std::cin >> student_id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer

    utility::string_t endpoint = U("/students/") + conversions::to_string_t(std::to_string(student_id));
    client.request(methods::DEL, endpoint)
            .then([](http_response response) {
                if (response.status_code() == status_codes::NoContent) {
                    std::cout << "Student was removed successfully" << std::endl;
                } else if (response.status_code() == status_codes::NotFound) {
                    std::cout << "Student not found" << std::endl;
                } else {
                    std::cerr << "Error removing student. Status code: " << response.status_code() << std::endl;
                }
            }).wait();
}
