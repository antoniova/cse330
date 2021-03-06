#include "String.h"

String::String()//default constructor
{
  size = 0;
  buffer = 0;
}

String::String( const String &s) //copy constructor
{
  size = s.size;
  buffer = new char[size];
  strcpy( buffer, s.buffer );
}

String::String( const char *txt)
{
  size = strlen(txt);
  buffer = new char[size];
  strcpy( buffer, txt );
}

String::~String() //destructor
{
  delete[] buffer;
}

//calculates the length of a string of characters
int String::strlen( const char *s)
{
  int i;
  for( i = 0; *s++; i++);
  return i;
}

//returns the size of the string
int String::length() 
{
  return size;
}

String& String::operator=(const char *txt)
{
  delete[] buffer;
  size = strlen(txt);
  buffer = new char[size];
  strcpy( buffer, txt );
  return *this;
}

String& String::operator=( const String& x)
{
  delete[] buffer;
  size = x.size;
  buffer = new char[size];
  strcpy( buffer, x.buffer );
  return *this;  
}

bool String::operator==( const String &s)
{
  if ( size != s.size )
      return false;
  else{
      for(int i = 0; i < size; i++){
	  if( buffer[i] != s.buffer[i] )
	      return false;
      }
  }
  return true;
}
    
bool String::operator==( const char *txt)
{
  if( size != strlen(txt) )
      return false;
  else{
      for( int i = 0; i < size; i++){
	  if( buffer[i] != txt[i] )
	      return false;
      } 
  } 
  return true;
}

char String::operator[]( int x )
{
  return buffer[x];
}

//append more characters to an existing string
void String::operator+=( const char* txt)
{
  if( strlen(txt) > 0){     
      int newsize = size + strlen(txt);
    
      if( size > 0 ){
          char* temp = new char[newsize];
          strcpy( temp, buffer );
          delete[] buffer;
          int j;

          for(int i = size, j = 0; i < newsize; i++, j++)
	      temp[i] = txt[j];

	  buffer = temp;
	  size = newsize;
    }else{
	  size = newsize;
          buffer = new char[size];
          strcpy( buffer, txt );
      }
  }
}

void String::strcpy( char* dest, const char* src)
{
  for(int i = 0; i < size ; i++)
      *dest++ = *src++;
}



