/*********************************************************************
        Homework 2:      Four Card Solitaire
     	programmer:      Antonio Gonzalez  CSE 330: Data Structures 
     	date:            2/5/12
     	file:            hw2_gonzalez.cpp
     	description:     This program simulates a game of four-card solitaire.
                         The game starts by drawing four cards from the deck and
                         placing them on the four stacks of cards. Four more cards
                         are drawn for every successive round.
        Data Structures: Vector
        Classes Author(s): Timothy Budd and Kay Zemoudeh
    	implementation:  This program uses 3 classes: Card, Deck  and 
                         RandomInteger. These are the same classes used for the war
                         game as written by Timothy Budd and modified by Kay Zemoudeh.
                         Some more modifications were made to accomodate for the
                         rules of four-card solitaire game.

    	modified by:     Antonio Gonzalez (AG from now on)
    	date:            2/5/12
    	modification:    Since the rules for solitaire are completely different to the rules
                         of the war game, only the Card, Deck and RandomInteger classes
                         could be reused. In fact, even these recycled classes required
                         some changes in order to work in the solitaire game. The major 
                         modification is a change of rank of the ACE suit to be the highest(14)
                         and deuce to be the lowest(2)
**********************************************************************/
#include <iostream>
#include <stdlib.h>       // for rand()
#include <algorithm>      // for random_shuffle()
#include <time.h>         
#include <vector>
#include <iomanip>
#define ACE 14

using namespace std;

enum suits { diamond, club, heart, spade };

class Card {
  // private by default
  int      rank;        // rank of card
  suits    suit;        // suit of card
public:
  // constructors
  Card();               // initialize a card with default values
  Card(suits, int);     // initialize a card with given values
   	    // accessors
  int getRank() { return rank; } // an in-line function
  suits getSuit() { return suit; }
  // mutators
  void setRank(int rv) { rank = rv; }
  void setSuit(suits sv) { suit = sv; }
}; // Card

Card::Card()
{
  rank = 2;
  suit = spade;
} // constructor

Card::Card(suits sv, int rv)
{
  rank = rv;
  suit = sv;
} // constructor

// output a textual presentation of a Card
ostream &operator<<(ostream &out, Card aCard)
{
  switch (int rank = aCard.getRank()) {
      case 11: out << left << setw(2) << "J"; break; //AG   2/5/12
      case 12: out << left << setw(2) << "Q"; break; //changed so that the
      case 13: out << left << setw(2) << "K"; break; //ranking for Ace is highest
      case 14: out << left << setw(2) << "A"; break;
      default: out << left << setw(2) << rank;
  }
  
  switch (suits suit = aCard.getSuit()) {
      case diamond: out << left << setw(18) << " of Diamonds"; break; //AG 2/5/12
      case spade:   out << left << setw(18) << " of spades"; break;   //added some
      case heart:   out << left << setw(18) << " of hearts"; break;   //better formatting
      case club:    out << left << setw(18) << " of clubs"; break;
  }
  return out;
} // operator<<

class RandomInteger {
public:
  RandomInteger();
  unsigned int operator()(unsigned int);
}; // RandomInteger

RandomInteger::RandomInteger()
{
  srand(time(0));   // kay 8/20/98
} // constructor

unsigned int RandomInteger::operator()(unsigned int max)
{
  unsigned int rval = rand();
  return rval % max;
} // operator()

RandomInteger randomizer; // global object, often not a good idea!

class Deck {
  Card cards[52];       // deck of 52 cards
  int topCard;          // size of deck
public:
  Deck();
  // shuffle uses the generic algorithm random_shuffle from STL
  void shuffle() { random_shuffle(cards, cards+52, randomizer); }
  bool isEmpty() { return topCard <= 0; }
  Card draw();   // return next card
}; // Deck

Deck::Deck()
{
  topCard = 0;
  for (int i = 2; i <= 14; i++) { //AG 2/5/12 changed to go up to 14
      Card c1(diamond, i), c2(spade, i), c3(heart, i), c4(club, i);
      cards[topCard++] = c1;
      cards[topCard++] = c2;
      cards[topCard++] = c3;
      cards[topCard++] = c4;
  }
} // constructor

Card Deck::draw()
{
  if (!isEmpty())
      return cards[--topCard];
  else { 
      Card spadeAce(spade, 1);
      return spadeAce;
  }
} // draw

/******* AG 2/5/12  maxColHeight  *******************
This function is a quick and dirty way to find how high the  
highest stack is. This information comes in handy when displaying 
the cards on the screen. The inputs are a reference to each 
of the four stacks of cards.
time complexity: O(n^2) due to use of selection sort.
********************************************/
int maxColHeight( vector<Card>& a, vector<Card>& b, vector<Card>& c, vector<Card>& d)
{
  vector<int> v;
  v.push_back( a.size() );
  v.push_back( b.size() );
  v.push_back( c.size() );
  v.push_back( d.size() );

  for( int i = 0 ; i < v.size() - 1; i++ ){//selection sort
      for( int j = i + 1; j < v.size(); j++ ){
	  if( v[i] > v[j] ){
	      int temp = v[i];
	      v[i] = v[j];
	      v[j] = temp;
	  }
      }
  }
  return v[3];
}	

/****** main ***
time complexity: O(n^2)
Only because we're using a selection sort algorithm. However,
as long as the game only uses for stacks of cards, the time complexity
should be O(n)
************/
main()
{
  Deck theDeck; // create a deck
  theDeck.shuffle();
  vector<vector<Card> > column(4);  
  int input, selected, newColumn, depth;
  int rounds = 12;
  bool nextRound = false;
  input = selected = newColumn = depth =0;

  //*************** main game loop ****************
  while( !theDeck.isEmpty() ){
    
      for( int i = 0; i < 4 ; i++ ) 
       	  column[i].push_back( theDeck.draw() ); //draw four cards in every round
      
      while( nextRound == false ){ //inner loop: playing round loop

          depth = maxColHeight( column[0], column[1], column[2], column[3] ); //call to maxColHeight
	  cout << "   Col1                 Col2                  Col3                Col4" << endl;

	  //**** Display cards on screen ****
	  for( int j = 0; j < depth; j++){
	      for( int i = 0; i < 4; i++){
		  if( j < column[i].size() )
		      cout << column[i][j];
		  else
		      cout << "                    ";
	      }
	      cout << endl;
	  }//*******************************
      
	  cout << endl;        
	  cout << "Rounds left: " << rounds << endl;
	  cout << "Enter a column number ( 0 to draw four new cards): ";
	  cin >> input;
	  while( input < 0 || input > 4 ){
	      cout << "Invalid input. Enter a column number ( 0 to draw four new cards): ";
	      cin >> input;
	  }
	  selected = input - 1;
	  
	  if( input == 0 ){   
	      nextRound = true; //go to next round(draw more cards)
	      rounds--;
	  }else{
	      Card chosen = column[selected].back();
	
	      if( chosen.getRank() == ACE ){
		  cout << "Ace to where? ";
		  cin >> input;
		  newColumn = input - 1;
		  if( column[newColumn].empty() || (column[newColumn].back().getRank() == ACE) ){
		      column[newColumn].push_back( chosen );
		      column[selected].pop_back();
		  }
	      }else{
 		  for( int i = 0 ; i < 4; i++){
		      if( chosen.getSuit() == column[i].back().getSuit() ){
		          if( chosen.getRank() < column[i].back().getRank() ){
		 	      column[selected].pop_back();
			      break;
			  }
		      }
		  }
	      }
	  }
      }//end of round loop
      nextRound = false; //reset to false so we can enter next round loop
  }//end of main game loop

  for( int i = 0 ; i < 4; i++){   //check for winning conditions
      if( column[i].size() != 1 ){
	  cout << "Sorry, you lose." << endl;
	  return 0;
      }else if( column[i].back().getRank() != ACE ){
	  cout << "Sorry, you lose." << endl;
	  return 0;
      }
  }

  cout << "Congratulations. You've beat the game!" << endl;
  return 0;
}//end main

