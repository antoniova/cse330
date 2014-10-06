#ifndef STUDENT_H
#define STUDENT_H
using namespace std;
#include "Course.h"

class Student
{
  typedef list<Course*>::iterator citerator;
 public:
 student(string n):nameText(n){}
  string name() { return nameText; }
  void addcourse (Course * c) { courses.push_back(c); }
  citerator firstCourse() { return courses.begin(); }
  citerator lastCourse() { return courses.end(); }
  void removeCourse (citerator & citr) { courses.erase(citr); }

 protected:
  string nameText;
  list<Course *> courses;
};

#endif
