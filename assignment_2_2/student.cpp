#include <iostream>
#include "student.h"


using namespace std;

void Student::set_name(string name){
    this->name = name;
}

void Student::set_age(int age){
    this->age = age;
}

void Student::set_attendance(int attendance){
    this->attendance = attendance;
}

void Student::set_id(int id){
    this->id = id;
}

int Student::get_id(){
    return this->id;
}

string Student::get_name(){
    return this->name;
}

int Student::get_age(){
    return this->age;
}

int Student::get_attendance(){
    return this->attendance;
}
