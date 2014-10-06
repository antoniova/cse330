/*******************************
Antonio Gonzalez
Lab#9: Priority queue
CSE 330 : Data Structures
This lab consists of an implementation of the priority queue container class. 
Although the functionality provided by this class is not as complete as the 
functionality provided by its STL counterpart, the core functions are still 
provided. This means that during the coding process, one can still learn the
main concepts pertaining to the class. 
*****************************/
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

// Priority_queue.h  -- a priority_queue implemented as a heap
#include <vector>
using namespace std;

template <class T> 
class Priority_queue {
public:
   Priority_queue() : c() { }
   bool empty() { return c.empty(); }
   unsigned int size() { return c.size(); }
   void push(const T & x);
   void pop(); 
   T & top() { return c.front(); }
private:
   vector<T> c;
};

template <class T>
void Priority_queue<T>::push( const T & x)
{
  c.push_back(x);
  push_heap( c.begin(), c.end() );
}

template <class T>
void Priority_queue<T>::pop()
{
  pop_heap( c.begin(), c.end() );
  c.pop_back();
}

template <class Iterator>
void push_heap( Iterator start, Iterator stop )
{
  unsigned int lastpos = (stop - start) - 1;
  unsigned int parent = ( lastpos - 1 )/ 2;

  while( lastpos != 0 && start[lastpos] > start[parent] ){
      swap( start[lastpos], start[parent] );
      lastpos = parent;
      parent = ( lastpos -1 ) / 2;
  }
}

template <class Iterator>
void pop_heap( Iterator start, Iterator stop )
{
  unsigned int lastpos = ( stop - start ) - 1;
  swap( start[0], start[lastpos] );
  adjust_heap( start, lastpos, 0) ;
}

template <class Iterator>
void adjust_heap( Iterator start, unsigned int heapSize, unsigned int position )
{
  while( position < heapSize ){
      unsigned int childpos = position * 2 + 1;
      if( childpos < heapSize ){
	  if (( childpos + 1 < heapSize ) && start[childpos + 1 ] > start[childpos] )
	      childpos++;
	  if( start[position] > start[childpos] )
	      return;
	  else
	      swap( start[position], start[childpos] );
      }
      position = childpos;
  }
}

template <class T, class Iterator>
void swap( Iterator a, Iterator b )
{
  T temp = *a;
  *a = *b;
  *b = temp;
}
#endif
