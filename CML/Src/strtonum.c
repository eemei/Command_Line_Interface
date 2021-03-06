#include "strtonum.h"
#include <string.h>
#include "ErrorObject.h"
//#include "CException.h"


/**
Using the C library routine strtol:
     A command is a word separated by spaces or tab.  A word separated by certain characters (like space or tab) is called a token.
     To get tokens one by one, I use the C lib routing strtol (part of C stdlib.h see below how to include it).
         It's part of C language library <string.h> which you can look up online.  Basically you:
            1) pass it a string (and the delimeters you use, i.e. space and tab) and it will return the first token from the string
            2) on subsequent calls, pass it NULL (instead of the string ptr) and it will continue where it left off with the initial string.
      I've written a couple of basic helper routines:
          getNumber: uses strtol and sscanf (strtol: base 2,8, 10, 16 to long int, again part of C stdlib.h) to return an long integer.
*/

/**
* getNumber with char **str argumnent and return int 
* - return -1 
*   when invalid hex value, invalid string exclude "write" & "read", other symbol !@@#$%&*()_+=-`~
*     -> example 00x12, 10x12, 01x123
*
* - return val
*   valid decimal value or hex value
*/
long int getNumber(char  **str)
{
  errno = 0;
  char *endptr;  //end pointer  
  int baseDecimal = 10;
  int baseHex = 16;
  char *ptr;
  char *detectHex;
  long int val;
  ptr = *str;

  if(*ptr != '\0')
  {
	    while(*ptr == ' ' || *ptr == '\t'){
	    	ptr++;
	    	*str = ptr;
	    	//return 4;
	    }
	    if(isalpha((char)*ptr)){
	      //getSubString(&ptr);
	      //sscanf(ptr, "%s", data);
	      //if (strcmpInsensitive(data, aWrite) == 0){
	        while(*ptr != '\0')
	        {
	          if(*ptr == ' ')
	          {
	            *str = ptr;
                //throwError("cannot occur alphabet here.", ERR_CANNOT_RESOLVE_ALPHABET);
	            return -1;
	          }
	          if(*ptr == '\t')
	          {
	            *str = ptr;
	            return -1;
	          }
	          ptr++;
	        }
	        *str = ptr;
	        //throwError("cannot occur alphabet here.", ERR_CANNOT_RESOLVE_ALPHABET);
	        return -1;
	    }
    if (isdigit((unsigned char)*ptr))
    {
      val = strtoul(*str, &endptr, baseDecimal);
      if(*ptr == '0')
      {
        detectHex = ptr;
        (detectHex++);
        if(*detectHex == 'x' || *detectHex == 'X'){
          val = strtoul(*str, &endptr, baseHex);
          *str = endptr;
          return val;
        }
        else
        {
          if(*endptr == 'x' || *endptr == 'X')
          {
            while(*ptr != '\0')
            {
              if(*ptr == ' ')
              {
                *str = ptr;
                return -1;
              }
              if(*ptr == '\t')
              {
                *str = ptr;
                //throwError("cannot invalid type HEX.", ERR_INVALID_HEX);
                return -1;
              }
              ptr++;
            }
            *str = ptr;
            //throwError("cannot invalid type HEX.", ERR_INVALID_HEX);
            return -1;
          }
        }
      }
      else 
      {
        if(*endptr == 'x'|| *endptr == 'X')
        {
          while(*ptr != '\0')
          {
            if(*ptr == ' ')
            {
              *str = ptr;
              return -1;
            }
            if(*ptr == '\t')
            {
              *str = ptr;
              return -1;
            }
            ptr++;
          }
          *str = ptr;
          return -1;
        }
      }
      *str = endptr;
      return val;
    }
   else
	  // throwError("empty string.",ERR_INVALID_VALUE);
	   return -1;
  }
 // throwError("empty string.", ERR_EMPTY_STRING);

  return -2;
}

/**
* get the sub-string from a string
* return the sub-string to lower characters
*/
char *getSubString(char **strPtr){
  char *ptr;
  char *str;
  char data[10];
  int length;
  int i = 0;
  char *lower;

  ptr = *strPtr;
  while(*ptr != '\0'){
    if(isalpha((char)*ptr)){
      sscanf(ptr, "%s", data);
      str = &data[0];
      length = strlen(str);
      lower = (char *)malloc(length);
      ptr+=length;
      *strPtr = ptr;
      length++;
      for(i = 0; i < length; i++ )
      {
          lower[i] = tolower(str[i]);
          printf("getstring ['%c']\n", lower[i]);
      }
      lower[length] = 0;
      return lower;
    }
    ptr++;
 }
 return 0;
}

