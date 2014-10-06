// test.cpp to test Priority_queue

#include <iostream>
#include <cassert>

#include "Priority_queue.h"

using namespace std;

int main()
{
   Priority_queue<int> pq;

   int x;
   while (cin >> x)
	pq.push(x);


   cout << pq.top() << endl;

   cout << endl;

   return 0;
}


