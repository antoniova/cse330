#include<iostream>
#include "Queue.h"
#include <cassert>
#include <string>
using namespace std;

int main()
{
  Queue<int> q1;

  assert( q1.size() == 0 );
  assert( q1.empty() );

  q1.push(10);
  assert( q1.size() == 1);
  assert( q1.front() == 10 );

  q1.pop();
  assert( q1.size() == 0 );

  q1.push(11);
  assert( q1.size() == 1 );
  assert( q1.front() == 11 );

  q1.push(15);
  assert( q1.size() == 2);
  assert( q1.front() == 11 );

  q1.push(20);
  assert( q1.size() == 3);
  assert( q1.back() == 20 );

  Queue<string> q2;

  q2.push("hello");
  assert( q2.size() == 1);
  assert( q2.front() == "hello" );

  q2.push("world");
  assert( q2.size() == 2);
  assert( q2.back() == "world");

  cout << q2.front() << " ";
  q2.pop();
  cout << q2.front() << endl;

  cout << "SUCCESS\n";

  return 0;
}
