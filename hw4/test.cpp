#include<iostream>
#include "Deque.h"
using namespace std;

int main()
{
  Deque<int> d;


  for(int i = 0; i < 15; i++ )
    d.push_back(i);


  Deque<int>::iterator it = d.begin();

  for(; it != d.end();it++)
    cout << *it << " " ;

  cout << endl;

  Deque<int>::iterator stop;

  stop = d.begin() + 10;

  d.erase( stop);

  for(it = d.begin(); it != d.end();it++)
    cout << *it << " " ;

  stop = d.begin() + 10;
  d.insert( stop, 10 );

  cout << endl;

  for(it = d.begin(); it != d.end();it++)
    cout << *it << " " ;

  stop = d.begin() + 10;
  d.insert( stop, 20 );

  cout << endl;

  for(it = d.begin(); it != d.end();it++)
    cout << *it << " " ;


  Deque<int> q = d;

  Deque<int> s;

  s = d;

  cout << endl;
  return 0;
}
