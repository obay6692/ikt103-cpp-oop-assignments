#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/reader.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <fstream>
#include <list>
#include "student.h"

using namespace std;
using namespace rapidjson;


void print_younger_student(list<Student*> &students)
{
    Student younger_student = *(students.front());
    for (auto s : students)
    {
        if (s->get_age() < younger_student.get_age())
        {
            younger_student = *s;
        }
    }
    cout << "Youngest: " << younger_student.get_name() << endl;
}

void print_older_student(list<Student*> &students)
{
    Student older_student = *(students.front());
    for (auto s : students)
    {
        if (s->get_age() > older_student.get_age())
        {
            older_student = *s;
        }
    }
    cout << "Oldest: " << older_student.get_name() << endl;
}

void print_average_age(list<Student*> &students)
{
    int sum = 0;
    for (auto s : students)
    {
        sum += s->get_age();
    }
    cout << "Average age: " << sum / students.size() << endl;
}

void print_bad_attendance(list<Student*> &students)
{
    for (auto s : students)
    {
        if (s->get_attendance() < 30)
        {
            cout << "Bad student: " << s->get_name() << endl;
        }
    }
}

int main(void)
{
    Document d;
    // using rapid json to read the students.json file
    ifstream file("students.json");
    string json((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    // parse
    d.Parse(json.c_str());

    file.close();

    if (d.HasParseError())
    {
        cerr << "Error parsing students.json" << d.GetParseError() << endl;
        return 1;
    }
    list<Student*> students;

    if (d.Empty())
    {
        cerr << "Error parsing students.json" << endl;
        return 1;
    }

    auto students_array = d.GetArray();
    for (auto &s : students_array)
    {
        Student* student = new Student();
        if(s.HasMember("id"))
            student->set_id(s["id"].GetInt());
        if(s.HasMember("name"))
            student->set_name(s["name"].GetString());
        if(s.HasMember("age"))
            student->set_age(s["age"].GetInt());
        if(s.HasMember("attendance"))
            student->set_attendance(s["attendance"].GetInt());

        students.push_back(student);
    }

    print_younger_student(students);
    print_older_student(students);
    print_average_age(students);
    print_bad_attendance(students);

    // clear students
    students.clear();
    return 0;
}