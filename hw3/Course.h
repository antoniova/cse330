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
  course ( string n, int s) : name(n), max(s){}
  bool full() { return students.size() >= max; }
  void addStudent(Student * s) { students.push_back(s); }
  void generateClassList();
  string name() { return name; }

 protected:
  string name;
  int max;
  list <Student *> students;
};

#endif