/*************************
Antonio Gonzalez
CSE 330: Data Structures
Homework 3
File: Student.h
************************/
#ifndef STUDENT_H
#define STUDENT_H
using namespace std;

class Course;

class Student
{
  typedef list<Course*>::iterator citerator;

 public:
 Student(string n):nameText(n){}
  string name() { return nameText; }
  void addCourse (Course * c) { courses.push_back(c); }
  citerator firstCourse() { return courses.begin(); }
  citerator lastCourse() { return courses.end(); }
  void removeCourse (citerator & citr) { courses.erase(citr); }
  
 protected:
  string nameText;
  list<Course *> courses;
};

#endif
