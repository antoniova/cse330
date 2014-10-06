#include <iostream>
#include "List.h"

using namespace std;

int main()
{
  List<int> l;
  
  l.push_back(0);  
  l.push_back(1);  
  l.push_back(2);  
  l.push_back(3);  
  l.push_back(4);  
  l.push_back(5);  

  cout << "size of list: " << l.size() << endl;

  List<int>::iterator it(l.begin());

  for(; it != l.end(); it++ )
    cout << *it << endl;

  cout << endl;
  it--;
  l.insert( it, 6 );

  for( it = l.begin(); it != l.end(); it++ )
    cout << *it << endl;
  cout << "size of list now: " << l.size() << endl;
  cout << endl;

}


