#ifndef STUDENT_H
#define STUDENT_H

#include <string>
class Student {
public:
    std::string NAAME;
    int oppmøte;
    int AALDDER;
    int IIIDD;

    Student(int id, std::string name, int age, int attendance)
            : IIIDD(id), NAAME(name), AALDDER(age), oppmøte(attendance) {}
};



#endif // STUDENT_H