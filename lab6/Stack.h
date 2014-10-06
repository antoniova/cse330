/*********************
Antonio Gonzalez
CSE 330: Data Structures
Lab 6 : Stack and Queue classes 
This lab consists of an implementation of the stack and queue container classes. Strictly
speaking, these two classes are adapters for more complex container classes. In this particular
case, we are using the List and Vector  classes developed in previous labs as the underlaying
containers on top of which the Stack and Queue will be built. The functionality provided by 
List and Vector are enough to implement all the functionality found in the Stack and Queue 
classes.
**********************/
#ifndef STACK_H
#define STACK_H

// Stack.h  -- a stack implemented as an adapter (of vector or list or ...)

#include "../lab5/List.h"

using namespace std;

//Use the following line for STL containers.
//template <class T, template <class T, class = allocator<T> > class Container = list>
template <class T, template <class T> class Container = List>
class Stack
{
public:
   //We don't need a constructor or destructor because the Container has/should have one
   //Stack(): container() { }
   //~Stack() { ~container(); }
bool empty() const{ return container.empty();}
unsigned int size() const{return container.size();}
void push(const T & x){ container.push_back(x);}
void pop(){ container.pop_back();}
T & top(){ container.back();}

private:
   Container<T> container;
};

#endif

