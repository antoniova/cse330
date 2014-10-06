#include <iostream>
using namespace std;

	    
int main()
{
  int z = 5;
  int w = 3;
  int * x;
  int *y;

  x = &z;
  y = &w;

  if( x == y )
    cout << "equal"<< endl;

  return 0;
}
