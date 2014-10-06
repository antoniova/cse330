#include <vector>
#include <iostream>
using namespace std;

int main()
{
  vector<int> t;
  t.push_back(2);
  cout<< t.size() << endl;
  t.pop_back();
  if( t.empty() )
    cout << "empty" << endl;
  cout << t.size() << endl;
  t.pop_back();
  cout << t.size() << endl;
  t.pop_back();

  cout << t.size() << endl;

    return 0;
}
