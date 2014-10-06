#ifndef _CARD_H
#define _CARD_H
#include <iostream>
using namespace std;

enum suits { diamond, club, heart, spade };

class Card{

  int rank;
  suits suit;

 public:
  Card();
  Card( suits, int );
  //accessors
  int getRank() {return rank; } // an in-line function
  suits getSuit() {return suit;}
  //mutators
  void setRank( int rv ){ rank = rv; }
  void setSuits( suits sv) { suit = sv; }
}; //card

#endif
