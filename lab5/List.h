#ifndef LIST_H
#define LIST_H

// List.h - a doubly-linked list

#include <algorithm>
#include <cassert>

using namespace std;

// forward declaration of classes defined in this header
template <class T> class Link;
template <class T> class List_iterator;

template <class T> 
class List
{
public:
   typedef List_iterator<T> iterator;

   List();
   List(const List<T> & l);
   ~List();

   bool empty() const;
   unsigned int size() const; 
   T & back() const;
   T & front() const;
   void push_front(const T & x);
   void push_back(const T & x);
   void pop_front();
   void pop_back();
   iterator begin() const;
   iterator end() const;
   void insert(iterator pos, const T & x); // insert x before pos
   void erase(iterator & pos);             // pos must be valid after erase() returns
   List<T> & operator=(const List<T> & l);

protected:
   Link<T> * first_link;
   Link<T> * last_link;
   unsigned int my_size;
};

template <class T>
List<T>::List()
{
  first_link = 0;
  last_link = 0;
  my_size = 0;
}

template <class T>
List<T>::List(const List & l) // copy constructor
{
  first_link = 0;
  last_link = 0;
  my_size = 0;
  for (Link<T> * current = l.first_link; current != 0; current = current -> next_link)
    push_back(current -> value);
}

template <class T>
List<T>::~List() // destructor
{
  if( my_size > 0 ){
       for ( Link<T> * current = first_link; current != 0;){
	   Link<T> * temp = current->next_link;
	   delete current;
	   current = temp;
       }
  }
  first_link = 0;
  last_link = 0;
  my_size = 0;
}

template <class T>
bool List<T>::empty() const
{
  return my_size == 0;
}

template <class T>
unsigned int List<T>::size()const
{
  return my_size;
}

template <class T>
T& List<T>::back()const
{
  return last_link->value;
}

template <class T>
T& List<T>::front()const
{
  return first_link->value;
}

template <class T>
void List<T>::push_back(const T & x)
{
  Link<T> * new_link = new Link<T>(x);

  if( first_link == 0 )
      first_link = last_link = new_link;
  else{
      new_link->prev_link = last_link;
      last_link->next_link = new_link;
      last_link = new_link;
  }
  my_size++;
}

template <class T>
void List<T>::push_front(const T & x)
{
  Link<T> * new_link = new Link<T>(x);
  if( last_link == 0 )
      first_link = last_link = new_link;
  else{
      new_link->next_link = first_link;
      first_link->prev_link = new_link;
      first_link = new_link;
  }
  my_size++;
}

template <class T>
void List<T>::pop_front()
{
  if( my_size > 0 ){
      iterator it = iterator( first_link->next_link );
    
      if( it.current_link == 0 ) //there's one element in the list
 	  pop_back();
      else{
	  it.current_link->prev_link = 0;
	  delete first_link;
	  first_link = it.current_link;
	  my_size--;
      }
  }
}

template <class T>
void List<T>::pop_back()
{
  if( my_size > 0 ){
      iterator it = iterator( last_link->prev_link);

      if( it.current_link == 0 ){ // there's one element in the list
	  delete first_link;
	  first_link = last_link = 0;
	  my_size = 0;
      }else{           //there's more then one in the list
	  it.current_link->next_link = 0;
	  delete last_link;
	  last_link = it.current_link;
	  my_size--;
      }
  }
}


template <class T>
typename List<T>::iterator List<T>::begin() const
{
  return iterator(first_link);
}

template <class T>
typename List<T>::iterator List<T>::end() const
{
  return iterator(last_link->next_link);
}

template <class T>
void List<T>::insert(iterator pos, const T & x) // insert x before pos
{
  if( pos.current_link != 0){
      if(pos.current_link == first_link){
	  push_front(x);
	  return;
      }
      Link<T> * newlink = new Link<T>(x);
      iterator before = iterator( pos.current_link->prev_link );
      
      newlink->next_link = pos.current_link;
      newlink->prev_link = before.current_link;
      pos.current_link->prev_link = newlink;
      before.current_link->next_link = newlink;
      my_size++;
  }
}

template <class T>
void List<T>::erase(iterator & pos)             // pos must be valid after erase() returns
{
  assert( pos.current_link != 0);
    
  Link<T> * after = pos.current_link->next_link;
  Link<T> * before = pos.current_link->prev_link;
  
  if( before == 0 ){ //at first element in list
      after->prev_link = 0;
      first_link = after;
  }else
      after->prev_link = before;

  if( after == 0 ){ //at last element in list
      before->next_link = 0;
      last_link = before;
  }else
      before->next_link = after;

  iterator target = pos++;
  delete target.current_link;
  my_size--;
}

/* 
   Overloading the assignment operator
*/
template <class T>
List<T> & List<T>::operator=(const List<T> & l)
{
  if( my_size > 0 ){
      for ( Link<T> * current = first_link; current != 0;){
	  Link<T> * temp = current->next_link;
	  delete current;
	  current = temp;
      }
  }  
  
  first_link = 0;
  last_link = 0;
  my_size = 0;
  for (Link<T> * current = l.first_link; current != 0; current = current -> next_link)
      push_back(current -> value);

  return *this;
}

/**********************************
  Link class
  Used to hold value T
**********************************/

template <class T> 
class Link 
{
private:
   Link(const T & x): value(x), next_link(0), prev_link(0) {}
                
   T value;     
   Link<T> * next_link;
   Link<T> * prev_link;

   friend class List<T>;
   friend class List_iterator<T>;
};

/******************************
  Iterator class.
  Used to traverse and modify lists
******************************/
template <class T> 
class List_iterator{

public:
   typedef List_iterator<T> iterator;

   List_iterator(Link<T> * source_link): current_link(source_link) { }
   List_iterator(): current_link(0) { }
   List_iterator(List_iterator<T> * source_iterator): current_link(source_iterator.current_link) { }

   T & operator*();  // dereferencing operator
   iterator & operator=(const iterator & rhs);
   bool operator==(const iterator & rhs) const;
   bool operator!=(const iterator & rhs) const;
   iterator & operator++();  // pre-increment, ex. ++it
   iterator operator++(int); // post-increment, ex. it++
   iterator & operator--();  // pre-decrement
   iterator operator--(int); // post-decrement

protected:
   Link<T> * current_link;

   friend class List<T>;
};

template <class T>
T & List_iterator<T>::operator*()
{
  return current_link -> value;
}

template<class T>
List_iterator<T> & List_iterator<T>::operator=(const iterator & rhs)
{
  current_link = rhs.current_link;
  return *this;
}

template <class T>
bool List_iterator<T>::operator==(const iterator & rhs)const
{
  return current_link == rhs.current_link;
}

template <class T>
bool List_iterator<T>::operator!=(const iterator & rhs)const
{
  return current_link != rhs.current_link;
}

template <class T>
List_iterator<T> & List_iterator<T>::operator++() // pre-increment
{
  current_link = current_link -> next_link;
  return *this;
}

template <class T>
List_iterator<T>  List_iterator<T>::operator++(int x) //post-increment
{
  iterator temp = *this;
  current_link = current_link -> next_link;
  return temp;
}

template <class T>
List_iterator<T> & List_iterator<T>::operator--() //pre-decrement
{
  current_link = current_link -> prev_link;
  return *this;
}

template <class T>
List_iterator<T>  List_iterator<T>::operator--(int x) //post-decrement
{
  iterator temp = *this;
  current_link = current_link -> prev_link;
  return temp;
}
#endif

