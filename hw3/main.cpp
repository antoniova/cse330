#include <iostream>
#include <list>
#include <string>
#include <fstream>
using namespace std;

class Student;
bool studentCompare( Student *, Student *);

//*********** Course Class ************
class Course
{
 public:
  Course ( string n, int s):name(n), max(s){}
  bool full() { return students.size() >= max; }
  void addStudent(Student * s) { students.push_back(s); }
  void generateClassList();
  string getName() { return name; }

 protected:
  string name;
  int max;
  list <Student *> students;
};

//*************Student Class **************
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


void Course::generateClassList()
{
  students.sort ( studentCompare );

  cout << "Class list for " << name << endl;
  list<Student *>::iterator start, stop;
  start = students.begin();
  stop = students.end();
  for( ; start != stop; ++start)
      cout << (*start)->name() << endl;

}
//*****************************************************


list<Course *> all_courses;
list<Student *> all_students;


bool studentCompare( Student *a, Student *b)
{
  return a->name() <  b->name();
}

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
  ifstream input( "class.txt" );
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
