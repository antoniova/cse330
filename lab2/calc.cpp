#include<iostream>
#include <vector>
using namespace std;

int main()
{
  double n = 1000;
  double time;
  double ave = 0;
  vector<double> v;

  cin >> time;
  
  while( cin.good() )
    {
      v.push_back( (time / (n*n)));
      n += 1000;
      cin >> time;
    }

  for( int i = 0; i < v.size(); i++)
    ave += v[i];

  cout << (ave / v.size()) << endl;
}
