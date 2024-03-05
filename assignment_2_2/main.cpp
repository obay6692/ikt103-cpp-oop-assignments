//Optional
#include <iostream>
#include "rapidjson/istreamwrapper.h"
#include <list>
#include <limits>
#include <fstream>
//Optional
#include "rapidjson/document.h"
#include <cmath>
#include "student.h"

int main() {
    // hmmmmmmmmmmmmmm
    std::ifstream ifs("students.json");
    rapidjson::IStreamWrapper isw(ifs);
//rapidjsonn
    rapidjson::Document d;
    d.ParseStream(isw);

    // liisttt
    std::list<Student*> students; // Endret til std::list<Student*>
    for (const auto& m : d.GetArray()) {
        students.emplace_back(
                new Student(
                        m["id"].GetInt(),
                        m["name"].GetString(),
                        m["age"].GetInt(),
                        m["attendance"].GetInt()
                )
        );
    }

    // Find attendance
    int minAge = std::numeric_limits<int>::max();
    int maxAge = std::numeric_limits<int>::min();
    std::string youngest, oldest;
    //www.o
    int totalAge = 0;

    std::list<std::string> badStudents;

    for (const auto* student : students) { // Endret til const auto* student
        // Finn den eldste og yngste studenten
        if (student->AALDDER < minAge) { // Endret til student->AALDDER
            minAge = student->AALDDER; // Endret til student->AALDDER
            youngest = student->NAAME; // Endret til student->NAAME
        }
        if (student->AALDDER > maxAge) { // Endret til student->AALDDER
            maxAge = student->AALDDER; // Endret til student->AALDDER
            oldest = student->NAAME; // Endret til student->NAAME
        }

        totalAge += student->AALDDER; // Endret til student->AALDDER

        // Ffind student with bad attendance
        if (student->oppmøte < 30) { // Endret til student->oppmøte
            badStudents.push_back(student->NAAME); // Endret til student->NAAME
        }
    }

    // Finn average age
    int averageAge = std::floor(static_cast<double>(totalAge) / students.size());

    // odofojoj
    std::cout << "Youngest: " << youngest << std::endl;
    std::cout << "Oldest: " << oldest << std::endl;
    std::cout << "Average age: " << averageAge << std::endl;
    for (const auto& name : badStudents) {
        std::cout << "Bad student: " << name << std::endl;
    }

    // Slett studentene for å unngå minnelkninger
    for (auto* student : students) {
        delete student;
    }

    return 0;
}
