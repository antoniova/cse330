#include "Card.h"

Card::Card()
{
  rank = 1;
  suit = spade;
}

Card::Card( suits sv, int rv )
{
  rank = rv;
  suit = sv;
}//constructor

//output a textual presentation of a Card
ostream &operator<<( ostream &out, Card aCard)
{
  switch ( int rank = aCard.getRank()){
  case 1:  out << "Ace"; break;
  case 11: out << "Jack"; break;
  case 12: out << "Queen"; break;
  case 13: out << "King"; break;
  default: out << rank;
  }

  switch ( suits suit = aCard.getSuit() ){
  case diamond: out << "of Diamonds" ; break;
  case spade:   out << "of spades"; break;
  case heart:   out << "of hearts"; break;
  case club:    out << "of clubs"; break;
  }
  return out;
}//operator<<

