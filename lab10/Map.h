/****************************
Antonio Gonzalez
Lab#10: The Map class
CSE 330: Data Structures
This lab consists of an implementation of the map container class.
This class is implemented using the set class (built in a previous lab),
as well as the pair class created during this lab. Although the 
functionality provided by this class may not be as complete as the 
functionality provided by its STL counterpart, the core functionality 
is still provided.
*****************************/
#ifndef MAP_H
#define MAP_H

// Map.h

#include "Set.h"
#include "Pair.h"

using namespace std;

template < class key, class value >
class Map : public Set < Pair < key, value > >
{
 public:

   typedef Set < Pair < key, value > > parent;
   typedef Set_iterator < Pair < key, value > > iterator;

   Map(): parent() {}

   iterator find(const key & k);
   value & operator[](const key & k);
   void erase(const key & k);
};

template < class key, class value >
  Set_iterator< Pair < key, value > >  Map< key, value > ::find( const key & k )
{
  Pair < key, value > temp;
  temp.first = k;
  return  parent::find( temp );
}

template < class key, class value >
  void  Map< key, value >::erase( const key & k )
{
  Pair< key, value > temp;
  temp.first = k;
  parent::erase( temp );
}

template < class key, class value >
  value & Map< key, value >::operator[]( const key & k )
{
  Pair< key, value > temp;
  temp.first = k;
  iterator it = parent::insert( temp );
  return it.n->value.second;
}
#endif
