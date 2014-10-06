// Small test.cpp to test Map

#include <iostream>
#include <cassert>
#include <map>
//#include "Map.h"

using namespace std;

int main()
{
   map<double, long> counts;

   counts[2.1] = 5;
   counts[-4] = 2;
   counts[.35] = 3;
   counts[-4] = 7;
   cout << counts[2.1] << " " << counts[-4] << " " << counts[.35] << endl;
}

