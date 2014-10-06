/************************
Antonio Gonzalez
1/16/12
file: hw1_gonzalez.cpp
This program calculates the variance for a given array 
of n elements. The program reads the numbers from the 
standard input until the end of file is reached. 
The array and its size are then passed as parameters to the
'variance' function; which calculates the actual result.
Time complexity: O(n)
Data Structure: array
**************************/
#include <iostream>
#define MAX_SIZE 255
using namespace std;

/******** variance ************
Calculates the variance for a given array
with n elements. The function accepts the array and its size.
It returns the final result back to the calling function.
******************************/
double variance( double d[], int size )
{
  double var = 0;
  double average = 0;

  for( int i = 0; i < size; i++ ) //add all elements 
      average += d[i];

  average = average / size; //divide by size of array to get average.

  for( int i = 0; i < size; i++ )
      var += (( d[i] - average ) * ( d[i] - average ));

  return  var / (size - 1);
}

/**** main ****/
int main()
{
  int value;
  int n = 0; //size of array
  double dArray[MAX_SIZE];

  cout << "Enter values for the array( ENTER followed by [crtl-D] stops input) : " << endl;
  cin >> value;
  while( !cin.eof() ){
      dArray[n] = value;
      n++;
      cin >> value;
  }
  
  if( n > MAX_SIZE ){
      cout << "Error. Maximum size exceeded." << endl;
      return 1;
  }else
      cout << "Variance is: " << variance( dArray, n ) << endl;

  return 0;
}
