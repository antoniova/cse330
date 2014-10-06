#include <iostream>
#include <vector>
using namespace std;

int main()
{
  vector<int> v;
  
  for( int i = 0; i < 10; i++ )
    v.push_back(i );

  vector<int>::iterator it = v.begin();


  int temp = *it;
  int pos = (v.end() - v.begin() ) - 1;

  *it = it[pos];
  it[pos] = temp;

  for( it = v.begin(); it != v.end(); it++ )
    cout << *it << " " ;

  cout << endl;



  return 0;

}
