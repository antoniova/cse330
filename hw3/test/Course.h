/*************************
Antonio Gonzalez
CSE 330: Data Structures
Homework 3
File: Course.h
************************/
#ifndef COURSE_H
#define COURSE_H
#include <iostream>
#include <string>
#include <list>
#include "Student.h"
using namespace std;

class Course
{
 public:
  Course ( string n, int s) : name(n), max(s){}
  bool full() { return students.size() >= max; }
  void addStudent(Student * s) { students.push_back(s); }
  void generateClassList();
  string getName() { return name; }

 protected:
  string name;
  int max;
  list <Student *> students;
};

#endif
