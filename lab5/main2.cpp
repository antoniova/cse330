#include <iostream>
#include <list>

using namespace std;

int main()
{
  list<int> l;
  
  l.push_back(0);  
  l.push_back(1);  
  l.push_back(2);  
  l.push_back(3);  
  l.push_back(4);  
  l.push_back(5);  

  cout << "size of list: " << l.size() << endl;

  list<int>::iterator it(l.begin());

  for(; it != l.end(); it++ )
    cout << *it << endl;

  cout << endl;
  it = l.end();
  it--;
  l.erase( it );

  for( it = l.begin(); it != l.end(); it++ )
    cout << *it << endl;
  cout << "size of list now: " << l.size() << endl;
  cout << endl;

}


