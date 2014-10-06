#include <iostream>
#include <map>
using namespace std;

int main() 
{
  map<string, int> m;
  string input;

  while( cin >> input )
    m[input] += 1;
  
  map<string, int>::iterator it;

  for(it = m.begin(); it != m.end() ; it++)
    cout << (*it).first << " " << (*it).second << endl;

  return 0;
}