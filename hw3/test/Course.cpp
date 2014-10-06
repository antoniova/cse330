#include "Course.h"

bool studentCompare( Student *a, Student *b)
{
  return a->name() <  b->name();
}

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
