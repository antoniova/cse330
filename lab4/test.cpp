#include <iostream>
#include "Vector.h"
using namespace std;


int main()
{
  Vector<int> v;
  Vector<int> s(5);
  Vector<int> x(10,2);

  cout << "The size of v is: " << v.size() << endl;
  cout << "The size of s is: " << s.size() << endl;
  cout << "The size of x is: " << x.size() << endl;

  if( !x.empty() )
    cout << "x is not empty" << endl;
  else
    cout << "x is empty" << endl;

  cout << "s's capacity before reserving: " << s.capacity() << endl;
  s.reserve(5);
  cout << "s's capacity  after reserving 5 more: " << s.capacity() << endl;

  return 0;
}
