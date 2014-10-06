/***************************************
Homework 4:        Deque Class 
Programmer:        Antonio Gonzalez
date:              3/24/12
file:              Deque.h
description:       This program provides an alternative implementation
                   of the deque class.
Data Structure(s): Array
Implementation:    This implementation uses a single array as the
                   underlying container. By keeping the elements of 
                   the deque in the center of the array as much as possible,
                   it is possible to maintain the deque in proper working order 
                   and at the same time avoid having to reallocate additional space
                   everytime an element is pushed at either end of the deque.
                   Inevitably, the array will fill up; if this is case, the size of
                   the array is increased by a factor of two. 
***************************************/
#ifndef DEQUE_H
#define DEQUE_H

// Deque.h - an implementation of double-ended queue

#include <cassert>
using namespace std;

template <class T> class DequeIterator;

template <class T>
class Deque{

 public:

  typedef DequeIterator<T> iterator;
	
  Deque(): my_capacity(10) { buffer = new T[10]; front_ptr = next_back = 10/2;}
  Deque( const unsigned int size, const T & initial ): my_capacity(size), front_ptr(0), next_back(size){
      buffer = new T[size];
      for( int i = front_ptr; i < next_back; i++)
	  buffer[i] = initial;
  }
  Deque( const Deque<T> & ); //copy constructor
  ~Deque() { delete[]buffer; } //destructor
  Deque & operator=( const Deque<T> & ); 
  T & operator[](unsigned int);
  T & front() { assert( front_ptr < next_back ); return buffer[front_ptr]; }
  T & back() { assert( front_ptr < next_back ); return buffer[next_back - 1];}
  bool empty() { return size() == 0; }
  iterator begin() { return iterator( this,0 ); }
  iterator end() { return iterator( this, size() ); }
  void erase(const iterator & itr) { erase( itr, itr+1 ); }
  void erase(const iterator &, const iterator &);
  void insert(const iterator &, const T &);
  int size() { return next_back - front_ptr; }
  void push_front(const T & value);
  void push_back(const T & value);
  void pop_front() { if( front_ptr != next_back ) front_ptr++; }
  void pop_back() { if( front_ptr != next_back ) next_back--; }

 protected:

  T * buffer;
  int front_ptr, next_back;
  int my_capacity;
  void center_it();
};

template <class T>
Deque<T>::Deque(const Deque<T> & d )
{
  front_ptr = d.front_ptr;
  next_back = d.next_back;
  my_capacity = d.my_capacity;
  buffer = new T[my_capacity];
  for( int i = 0; i < my_capacity ; i++)
      buffer[i] = d.buffer[i];
}

template <class T>
Deque<T> & Deque<T>::operator=( const Deque<T> & d )
{
  delete[]buffer;
  front_ptr = d.front_ptr;
  next_back = d.next_back;
  my_capacity = d.my_capacity;
  buffer = new T[my_capacity];
  for( int i = 0; i < my_capacity; i++)
      buffer[i] = d.buffer[i];
}

template <class T>
T & Deque<T>::operator[]( unsigned int index )
{
  assert( (front_ptr+index) < next_back );
  return buffer[front_ptr + index];
}

template <class T>
void Deque<T>::push_back(const T & value)
{
  if( next_back == my_capacity )
      center_it();
  buffer[next_back++] = value;
}

template <class T>
void Deque<T>::push_front( const T & value)
{
  if( front_ptr == 0 )
      center_it();
  buffer[--front_ptr] = value;
}

template <class T>
void Deque<T>::insert(const iterator & itr, const T & value)
{
  if( next_back == my_capacity )
      center_it();

  int j = next_back;
  for( int i = j - 1; i >= front_ptr + itr.index; )
      buffer[j--] = buffer[i--];

  buffer[ front_ptr + itr.index ] = value;
  next_back++;
}

template <class T>
void Deque<T>::center_it()
{
  if( size() > (my_capacity / 2) )
      my_capacity *= 2;
    
  T * temp = new T[ my_capacity ];
  int j = ( my_capacity - size()) / 2; //the initial point ( new front_ptr )
  for( int i = front_ptr; i < next_back; i++,j++ )
      temp[j] = buffer[i];

  delete[]buffer;
  buffer = temp;
  front_ptr = ( my_capacity - size() ) / 2;
  next_back = j;
}

template <class T>
void Deque<T>::erase(const iterator &start, const iterator & stop )
{
  assert( front_ptr != next_back );

  T * temp = new T[ my_capacity ];
  int i = front_ptr;
  int j = front_ptr + stop.index;
  for(; i < front_ptr + start.index; i++ )
      temp[i] = buffer[i];
  for(; j < next_back; i++, j++ )
      temp[i] = buffer[j];

  delete[]buffer;
  buffer = temp;
  next_back -= (stop.index - start.index);
}

//*********** DequeIterator Class ******************
template <class T>
class DequeIterator {

  friend class Deque<T>;
  typedef DequeIterator<T> iterator;

 public:

  DequeIterator(): theDeque(0), index(0) { }
  DequeIterator(Deque<T> * d, int i): theDeque(d), index(i) { }
  DequeIterator(const iterator & d): theDeque(d.theDeque), index(d.index) { }
  
  T & operator*() { return (*theDeque)[index]; }
  iterator & operator++() { index++; return *this; }
  iterator operator++(int);
  iterator & operator--() { index--; return *this; }
  iterator operator--(int);
  bool operator==(const iterator & r) { return theDeque == r.theDeque  &&  index == r.index ; }
  bool operator!=(const iterator & r) { return theDeque == r.theDeque && index != r.index ; }
  bool operator<(const iterator & r) const { return  theDeque == r.theDeque && index < r.index ; }
  T & operator[](unsigned int i) { return *theDeque[index + i]; }
  iterator operator=(const iterator & r);
  iterator operator+(int i) const { return iterator( theDeque, index + i ); }
  iterator operator-(int i) const { return iterator( theDeque, index - i ); }

 protected:

  Deque<T> * theDeque;
  int index;
};

template <class T>
DequeIterator<T> DequeIterator<T>::operator++(int x)
{
  iterator temp = *this;
  index++;
  return temp;
}

template <class T>
DequeIterator<T> DequeIterator<T>::operator--(int x)
{
  iterator temp = *this;
  index--;
  return temp;
}

template <class T>
DequeIterator<T> DequeIterator<T>::operator=(const iterator & r)
{
  theDeque = r.theDeque;
  index = r.index;
  return *this;
}
#endif