#include<iostream>
using namespace std;

int main()
{
  double c = 0;
  double time;
  double n = 1000;

  cin >> time;
  while( cin.good() )
    {
      c = (time / (n * n));
      n += 1000;
      cout << c << endl;
      cin >> time;
    }

  return 0;
}
