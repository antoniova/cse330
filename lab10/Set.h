/***************************
Antonio Gonzalez
CSE 330: Data Structures
Lab #8: The Set class
This lab consists of an implementation of the set container class.
Although the functionality provided by this class is not as complete
as the functionality provided by its STL counterpart, the core functions
are still provided. This means that during the coding process, one can
still learn the main concepts pertaining to the class. 
***************************/
#ifndef SET_H
#define SET_H

// Set.h - an implementation of Set using Node and Set_iterator
#include <iostream>
using namespace std;

template <class T> class Set;
template <class T> class Set_iterator;

template <class T>
class Node {

public:

  Node(): value(0), parent(0), leftChild(0), rightChild(0) { }
  Node(const T & x, Node * p, Node * lc, Node * rc):
     value(x), parent(p), leftChild(lc), rightChild(rc) { }
  void insert(Node<T> * newNode); // this is a helper func for Set::insert()
  Node * find(const T & x);
  Node * merge(Node<T> * left, Node<T> * right);
  T value;

 protected:

  Node * parent;
  Node * leftChild;
  Node * rightChild;

  friend class Set<T>;
  friend class Set_iterator<T>;
};

template <class T>
Node<T>* Node<T>::find( const T & x)
{
  if( value == x )
      return this;

  Node<T> * current;
  if( x < value ){
      if( leftChild )
	  current = leftChild->find(x);
      else
	  return 0;
  }else{
      if( rightChild )
	  current = rightChild->find(x);  
      else
	  return 0;
  }
  return current;
}

template <class T>
void Node<T>::insert( Node<T> * newNode )
{
  if( newNode->value < value ){
      if( leftChild )
	  leftChild->insert( newNode );
      else{
	  leftChild = newNode;
	  newNode->parent = this;
      }
  }else if( newNode->value > value ){
      if( rightChild )
	  rightChild->insert( newNode );
      else{
	  rightChild = newNode;
	  newNode->parent = this;
      }
  }
}

template <class T>
Node<T>* Node<T>::merge( Node<T> *left, Node<T> *right )
{
  if ( left == 0 )
    return right;

  if ( right == 0 )
    return left;
  
  Node<T> * child = merge( left, right->leftChild);
  child->parent = right;
  right->leftChild = child;
  return right;
}

template <class T>
class Set {
public:
  typedef Set_iterator<T> iterator;
  
 Set(): root(0), my_size(0) { }
  bool empty() const { return root == 0; } 
  unsigned int size() const { return my_size; } 
  iterator insert(const T & x); 
  void erase(iterator & it) { root = remove( root, it.n->value ); }
  void erase(const T & x) { root = remove(root, x); } 
  unsigned int count(const T & x) const; // returns 1 or 0 because this is a set, not a multi-set...
  iterator find(const T & x) const;
  iterator begin() const; // for in-order traversal
  iterator end() const { return iterator(0); }

 protected:
  
  Node<T> * root;
  unsigned int my_size;
  Node<T> * remove(Node<T> *, const T &);
};

template <class T>
Set_iterator<T> Set<T>::begin() const
{
  if( root == 0 )
    return iterator(0);

  Node<T> * current = root;
  while( current->leftChild )
      current = current->leftChild;
  
  return iterator( current );
}

template <class T>
unsigned int Set<T>::count(const T & x) const
{
  iterator itr = begin();
  for(; itr != end(); itr++ )
      if( *itr == x )
          return 1;
  return 0;
}

template <class T>
Set_iterator<T> Set<T>::find( const T & x) const
{
  return iterator( root->find(x) );
}

template <class T>
Set_iterator<T> Set<T>::insert( const T & x )
{
  if( count(x) > 0)
    return find(x);

  Node<T> * newNode = new Node<T>(x,0,0,0);
  if( empty() )
      root = newNode;
  else{
      root->insert( newNode );
      my_size++;
  }
  return iterator( newNode );
}

template <class T>
Node<T> * Set<T>::remove( Node<T> * current, const T & x )
{
  if ( current != 0 ){
    Node<T> * pa = current->parent;
    if( x < current->value )
      current->leftChild = remove( current->leftChild, x );
    else if( x > current->value )
      current->rightChild = remove( current->rightChild, x );
    else{
      Node<T> * result = current->merge( remove(current->leftChild, x), current->rightChild );
      delete current;
      if( result )
	result-> parent = pa;
      return result;
    }
  }
  return current;
}



// More code for Set goes here ...

template <class T>
class Set_iterator {
public:
	Set_iterator(): n(0) { }
	Set_iterator(Node<T> * newNode): n(newNode) { }

	bool operator==(Set_iterator it) const { return n == it.n; }
	bool operator!=(Set_iterator it) const { return n != it.n; }
	Set_iterator & operator++(); // inorder traversal, pre-increment
	Set_iterator operator++(int); // inorder traversal, post-increment
	T & operator*() { return n->value; }
	Set_iterator & operator=(Set_iterator<T> it) { n = it.n; return *this; }
	Node<T> * n;
protected:

friend class Set<T>;
};

template <class T>
Set_iterator<T> & Set_iterator<T>::operator++()
{
  if(n->rightChild){
      n = n->rightChild;
      while(n &&  n->leftChild )
	  n = n->leftChild;
  }else{
      Node<T>* child = n;
      n = n->parent;
      while( n && n->rightChild == child ){
	  child = n;
	  n = n->parent;
      }
  }
  return *this;   
}

template <class T>
Set_iterator<T>  Set_iterator<T>::operator++(int x)
{
  Set_iterator<T> temp = *this;
  operator++();
  return temp;
}

#endif
