/***************************************
Homework 3:        Course Registration System
Programmer:        Antonio Gonzalez
date:              2/28/12
file:              hw3_gonzalez.cpp
description:       This program simulates a simple course registration
                   system. The courses available, as well as the students
                   that want to register for those courses, are entered into
                   text files that the program reads at execution. The program 
                   validates all data and then proceeds to process registrations
                   in a first-come, first-served basis.
Classes Author:    Timothy Budd
Data Structure(s): List
Implementation:    This program makes exclusive use of linked lists. Using lists
                   provides maximum flexibility when it comes to adding courses
                   and students into the system. Also, since both classes need to refer
                   to instances of each other, the only viable option is to create
                   lists that hold pointers to the actual courses and students. This 
                   makes processing registrations a simple matter of passing pointers
                   around as needed. 
Modifications:     The Course class did not have an accesor function for the name
                   of the course. This function was added.
***************************************/
#include <fstream>
#include "Course.h"
#include "Student.h"
using namespace std;

list<Course *> all_courses;
list<Student *> all_students;

//read all courses from file into all_courses list
void readCourses( istream & infile)
{
  string name;
  int max;
  
  while ( infile >> name >> max ){
      Course * newCourse = new Course( name, max );
      all_courses.push_back( newCourse );
  }
}

Student * findStudent( string & searchName )
{
  list<Student *>::iterator start, stop;
  start = all_students.begin();
  stop = all_students.end();
  for( ; start != stop; ++start )
      if( (*start)->name() == searchName )
	  return *start;

  Student * newStudent = new Student( searchName );
  all_students.push_back( newStudent );
  return newStudent;
}

Course * findCourse( string & searchName )
{
  list<Course *>::iterator start, stop;
  start = all_courses.begin();
  stop = all_courses.end();
  for( ; start != stop; ++start )
      if( (*start)->getName() == searchName )
	  return *start;
  
  return 0;
}

void readStudents( istream & infile)
{
  string name;
  string course;

  while ( infile >> name >> course ){
      Student * theStudent= findStudent( name );
      Course * theCourse = findCourse( course );
      if( theCourse != 0 )
	  theStudent->addCourse( theCourse );
      else
	  cout << "student " << name <<
	  " requested invalid course " << course << endl;
  }
}

void fillCourses()
{
  list<Student *>::iterator s_start, s_end;
  s_start =  all_students.begin();
  s_end = all_students.end();

  for( ; s_start != s_end; ++s_start){
      list<Course *>::iterator c_start, c_end, c_next;
      c_start = (*s_start)->firstCourse();
      c_end = (*s_start)->lastCourse();
      for( ; c_start != c_end; c_start = c_next ){
	  c_next = c_start; ++c_next;

	  if( ! (*c_start)->full())
	      (*c_start)->addStudent(*s_start);
	  else
	      (*s_start)->removeCourse(c_start);
      }
  }
}

void generateCourseReports()
{
  list<Course *>::iterator start, stop;
  start = all_courses.begin();
  stop = all_courses.end();
  for( ; start != stop; ++start)
      (*start)->generateClassList();
}

void generateStudentReports()
{
  list<Student *>::iterator s_start, s_stop;
  list<Course *>::iterator c_start, c_stop;
  s_start = all_students.begin();
  s_stop = all_students.end();

  for(; s_start != s_stop; ++s_start ){
      cout << "Class list for " << (*s_start)->name() << endl;
      c_start = (*s_start)->firstCourse();
      c_stop = (*s_start)->lastCourse();
      for(; c_start != c_stop; ++c_start)
	  cout << (*c_start)->getName() << endl;
  }
}

int main()
{
  ifstream input( "classes.txt" );
  readCourses( input );
  input.close();

  input.open( "pupils.txt" );
  readStudents( input );
  input.close();

  fillCourses();
  generateCourseReports();
  cout << "************ end of course rooster report **************\n\n";
  generateStudentReports();
  
  return 0;
}
