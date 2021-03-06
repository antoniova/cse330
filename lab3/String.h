/*******************
Antonio Gonzalez
CSE 330: Data Structures
Winter 2012
Description: This lab is a simplified implementation
             of the string class. The functionality provided is very 
             basic, but it is enough to teach the underlaying design
             of the string class.
*********************/

#ifndef _STRING_H_
#define _STRING_H_

class String{

  int size;
  char * buffer;
  int strlen( const char *);
  void strcpy( char*, const char* );

 public:

  String();
  String( const String &);
  String( const char *);
  ~String();
  int length();
  String& operator=( const char *);
  String& operator=( const String&);
  bool operator==( const String&);
  bool operator==( const char* );
  char operator[](int);
  void operator+=( const char * );

};

#endif
