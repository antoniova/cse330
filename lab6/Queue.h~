/*********************
Antonio Gonzalez
CSE 330: Data Structures
Lab 6: Stack and Queue classes
This lab consists of an implementation of the stack and queue container classes. Strictly
speaking, these two classes are adapters for more complex container classes. In this particular
case, we are using the List and Vector  classes developed in previous labs as the underlaying
containers on top of which the Stack and Queue will be built. The functionality provided by 
List and Vector are enough to implement all the functionality found in the Stack and Queue 
classes.
**********************/
#ifndef QUEUE_H
#define QUEUE_H

// Queue.h -- a queue implemented as an adapter (of list )
//hello
#include "../lab5/List.h"
#include "../lab3/String.h"
using namespace std;


template <class T>
class Queue
{
 public:
  bool empty() const{ return container.empty();}
  unsigned int size() const { return container.size();}
  void push(const T & x ){ container.push_back(x);}
  void pop(){ return container.pop_front();}
  T& front(){ return container.front();}
  T& back(){ return container.back();}

 private:
  List<T> container;
};

#endif
