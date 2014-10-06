/**************************
Antonio Gonzalez
file: Lab1.cpp
This programs takes as input an expression using infix notation
and outputs the same expression in postfix notation. Acceptable 
intput characters are a-z, A-Z and 1-9.
Data Structures: stack
100% complete
***************************/

#include <iostream>
#include <stack>
using namespace std;

/***** precendence *******
Accepts a character as input and returns an 
integer based on the precendence of the char recieved.
acceptable chars: '(' , '*', '/', '+', '-'
time complexity: O(1)
storage complexity: O(1)
***************************/
int precedence( char x )
{
  if ( x == '(' )
      return  0;
  else if( x == '+' || x == '-' )
      return 1;
  else if( x == '*' || x == '/' )
      return 2;
}

/**  main ***/
int main()
{
    char input;
    stack<char> s;

    cout << "infix input: " ;  
    cin >> input;
    cout << "postfix output: " ;

    while( !cin.eof() ){
        if( (input >= 'a' && input <= 'z') || (input >= '0' && input <= '9' ) )
            cout << input;
        else{
	    if ( input == '(' )
	        s.push( input );
	    else if ( input == ')' ){
	        while ( !s.empty() && s.top() != '(' ){
  		    cout << s.top();
		    s.pop();
		}
		
		if ( !s.empty() )
		    s.pop();
		else{
		    cout << "Error. No matching parenthesis" << endl;
		    return -1;
		}
	    }else if ( s.empty() || (precedence( s.top()) < precedence( input )) )
	        s.push( input );
	    else if ( precedence(s.top()) >= precedence(input) ){
	        cout << s.top();
		s.pop();
		s.push( input);
	    }else{
	        cout << "Check for errors" << endl;
		return -1;
	    }
	}
	cin >> input;
    }

    while( !s.empty() ){
        cout << s.top();
        s.pop();
    }

    cout << endl;
    return 0;
}
  
