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
	bool empty();
	iterator begin();
	iterator end();
	void erase(const iterator &);
	//	void erase(const iterator &, const iterator &);
	void insert(const iterator &, const T &);
	int size();
	void push_front(const T & value);
	void push_back(const T & value);
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
bool Deque<T>::empty()
{
  return (vecOne.empty() && vecTwo.empty());
}

template <class T>
DequeIterator<T> Deque<T>::begin()
{
  return iterator( this, 0 );
}

template <class T>
DequeIterator<T> Deque<T>::end()
{
  return iterator( this, size() );
}

template <class T>
void Deque<T>::push_front(const T & value)
{
  vecOne.push_back( value );
}

template <class T>
void Deque<T>::push_back(const T & value)
{
  vecTwo.push_back( value );
}

template <class T>
int Deque<T>::size()
{
  return vecOne.size() + vecTwo.size();
}

template <class T>
void Deque<T>::insert(const iterator & itr, const T & value)
{
  assert( itr.index < size() );
  int n = vecOne.size();
  if( itr.index < n ){
    vector<T>::iterator it = vecOne.rbegin();
    for( int i = 0; i < itr.index ; i++, --it );
    vecOne.insert( it, value );
  }else{
    for( vector<T>::iterator it = vecTwo.begin(), i = vecOne.size(); i < itr.index; i++, it++);
    vecTwo.insert( it, value );
  }

}

template <class T>
void Deque<T>::erase(const iterator & itr)
{
  assert( itr.index < size() );
  int n = vecOne.size();
  vector<T>::iterator it;
  if( itr.index < n ){
     for( int i = 0, it = vecOne.rbegin(); i < itr.index; i++, it-- );
     vecOne.erase(it);
  }else{
      for( int i = vecOne.size(), it = vecTwo.begin(); i < itr.index; i++, it++);
      vecTwo.erase(it);
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
// Your code goes here ...

template <class T>
class DequeIterator {

  friend class Deque<T>;
  typedef DequeIterator<T> iterator;

 public:

  DequeIterator(): theDeque(0), index(0) { }
  DequeIterator(Deque<T> * d, int i): theDeque(d), index(i) { }
  DequeIterator(const iterator & d): theDeque(d.theDeque), index(d.index) { }
  
  T & operator*();
  iterator & operator++();
  iterator operator++(int);
  iterator & operator--();
  iterator operator--(int);
  bool operator==(const iterator & r);
  bool operator!=(const iterator & r);
  bool operator<(const iterator & r);
  T & operator[](unsigned int i);
  iterator operator=(const iterator & r);
  iterator operator+(int i);
  iterator operator-(int i);

 protected:

  Deque<T> * theDeque;
  int index;
};

template <class T>
T & DequeIterator<T>::operator*()
{
  return *theDeque[

template <class T>
iterator & DequeIterator<T>::operator++()
{
  index++;
  return *this;
}

template <class T>
iterator DequeIterator<T>::operator++(int x)
{
  iterator temp = *this;
  index++;
  return temp;
}

template <class T>
iterator & DequeIterator<T>::operator--()
{
  index--;
  return *this;
}

template <class T>
iterator DequeIterator<T>::operator--(int x)
{
  iterator temp = *this;
  index--;
  return temp;
}

template <class T>
bool DequeIterator<T>::operator==(const iterator & r)
{
  return ( theDeque == r.theDeque ) && ( index == r.index );
}

template <class T>
bool DequeIterator<T>::operator!=(const iterator & r)
{
  return ( theDeque != r.theDeque ) && ( index != r.index );
}

templace <class T>
bool DequeIterator<T>::operator<(const iterator & r)
{
  return ( theDeque == r.theDeque ) && ( index < r.index);
}

template <class T>
T &  DequeIterator<T>::operator[](unsigned int i)
{
  return *theDeque[index + i];
}


template <class T>
iterator DequeIterator<T>::operator=(const iterator & r)
{
  theDeque = r.theDeque;
  index = r.index;
  return *this;
}

template <class T>
iterator DequeIterator<T>::operator+(int i)
{
  return iterator( theDeque, [index + i]);
}

template <class T>
iterator DequeIterator<T>::operator-(int i)
{
  return iterator( theDeque, [index - i]);
}
#endif
