/*******************************
Antonio Gonzalez
CSE 330: Data Structures
Lab #7: The Deque Class
This lab consists of an implementation of the deque container class, aka double-ended
queue. The implementation in this particular lab uses a combination two vectors as the
underlaying container. Although the functionality provided by this class is not as 
complete as the functionality provided by its STL counterpart, the core functions are
still provided. This means that during the coding process, one can still learn the main 
concepts pertaining to the class.
*****************************/
#ifndef DEQUE_H
#define DEQUE_H

// Deque.h - an implementation of double-ended queue

#include <vector>
#include <cassert>
using namespace std;

template <class T> class DequeIterator;

template <class T>
class Deque {

public:

  typedef DequeIterator<T> iterator;
	
  Deque(): vecOne(), vecTwo() { }
  Deque(unsigned int size, T& initial): vecOne(size/2, initial), vecTwo(size-(size/2), initial) { }
  Deque(Deque<T> & d): vecOne(d.vecOne), vecTwo(d.vecTwo) { }
  
  T & operator[](unsigned int);
  T & front();
  T & back();
  bool empty() { return vecOne.empty() && vecTwo.empty(); }
  iterator begin() { return iterator( this, 0 ); }
  iterator end() { return iterator( this, size() ); }
  void erase(const iterator &);
  void erase(const iterator &, const iterator &);
  void insert(const iterator &, const T &);
  int size() { return vecOne.size() + vecTwo.size(); }
  void push_front(const T & value) { vecOne.push_back( value ); }
  void push_back(const T & value) { vecTwo.push_back( value ); }
  void pop_front();
  void pop_back();

 protected:

  vector<T> vecOne;
  vector<T> vecTwo;
};

template <class T>
T & Deque<T>::operator[]( unsigned int index )
{
  assert( index < size() );
  int n = vecOne.size();
  if( index < n )
      return vecOne[(n-1) - index];
  else
      return vecTwo[ index - n ];
}

template <class T>
T & Deque<T>::front()
{
  if( vecOne.empty() )
      return vecTwo.front();
  else
      return vecOne.back();
}

template <class T>
T & Deque<T>::back()
{
  if( vecTwo.empty() )
      return vecOne.front();
  else
      return vecTwo.back();
}

template <class T>
void Deque<T>::insert(const iterator & itr, const T & value)
{
  assert( itr.index < size() );
  int index = itr.index;
  int n = vecOne.size();
  if( itr.index < n )
      vecOne.insert( vecOne.begin() + (n-index), value);
  else
      vecTwo.insert( vecTwo.begin() + (index - n), value);
}

template <class T>
void Deque<T>::erase(const iterator & itr)
{
  assert( itr.index < size() );
  int index = itr.index;
  int n = vecOne.size();
  if( itr.index < n )
      vecOne.erase( vecOne.begin() + (n-1)-index );
  else
      vecTwo.erase( vecTwo.begin() + (index - n));
}

template <class T>
void Deque<T>::erase(const iterator &start, const iterator & stop )
{
  assert( start.index < size() && stop.index < size() );
  assert( start < stop && !empty() );

  int beg = start.index;
  int end = stop.index;
  int n = vecOne.size();
  if(  beg < n && end < n )
      vecOne.erase( vecOne.begin() + ((n-1)-end), vecOne.begin() + ((n-1)-beg) );
  else if( beg >= n && end >= n )
      vecTwo.erase( vecTwo.begin() + (beg - n), vecTwo.begin() + (end - n) );
  else{
      vecOne.erase( vecOne.begin(), vecOne.begin() + (n-beg) );
      vecTwo.erase( vecTwo.begin(), vecTwo.begin() + (end - n) );
  }

}

template <class T>
void Deque<T>::pop_front()
{
  assert( !empty() );
  if( vecOne.empty() ){
      for( int i = 0; i < vecTwo.size() - 1; i++ )
	  vecTwo[i] = vecTwo[i+1];
      vecTwo.pop_back();
  }else
      vecOne.pop_back();
}

template <class T>
void Deque<T>::pop_back()
{
  assert( !empty() );
  if( vecTwo.empty() ){
      for( int i = 0; i < vecOne.size() - 1; i++ )
	  vecOne[i] = vecOne[i+1];
      vecOne.pop_back();
  }else
      vecTwo.pop_back();
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
  bool operator!=(const iterator & r) { return theDeque != r.theDeque && index != r.index ; }
  bool operator<(const iterator & r) const { return  theDeque == r.theDeque && index < r.index ; }
  T & operator[](unsigned int i) { return *theDeque[index + i]; }
  iterator operator=(const iterator & r);
  iterator operator+(int i) { return iterator( theDeque, index + i ); }
  iterator operator-(int i) { return iterator( theDeque, index - i ); }

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
