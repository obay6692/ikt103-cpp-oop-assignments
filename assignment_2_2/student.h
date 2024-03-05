#ifndef _STUDENT_H
#define _STUDENT_H

#include <iostream>

class Student {
    public:
        void set_id(int id);
        void set_name(std::string name);
        void set_age(int age);
        void set_attendance(int attendance);

        int get_id();
        std::string get_name();
        int get_age();
        int get_attendance();
    private:
        int id;
        std::string name;
        int age;
        int attendance;
};

#endif