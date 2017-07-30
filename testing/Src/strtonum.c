#include "strtonum.h"
#include <string.h>



/**
Using the C library routine strtol:
     A command is a word separated by spaces or tab.  A word separated by certain characters (like space or tab) is called a token.
     To get tokens one by one, I use the C lib routing strtol (part of C stdlib.h see below how to include it).
         It's part of C language library <string.h> which you can look up online.  Basically you:
            1) pass it a string (and the delimeters you use, i.e. space and tab) and it will return the first token from the string
            2) on subsequent calls, pass it NULL (instead of the string ptr) and it will continue where it left off with the initial string.
      I've written a couple of basic helper routines:
          getNumber: uses strtol and sscanf (strtol: base 2,8, 10, 16 to long int, again part of C stdlib.h) to return an long integer.
          loop: returns how many valid value

*/

/**
* getNumber with char **str argumnent and return int 
* - return -1 
*   when invalid hex value, invalid string exclude "write" & "read", other symbol !@@#$%&*()_+=-`~
*     -> example 00x12, 10x12, 01x123
*
* - return -2
*   when end of line '\n'
* 
* - return 2
*   when given char is write
*   case insensitive
*
** - return 3
*   when given char is read
*   case insensitive
*
* - return 4
*   when given space or tab
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
	      //sscanf(ptr, "%s", data);
	      //if (strcmpInsensitive(data, aWrite) == 0){
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
    if (isdigit((unsigned char)*ptr))
    {
      val = strtol(*str, &endptr, baseDecimal);
      if(*ptr == '0')
      {
        detectHex = ptr;
        (detectHex++);
        if(*detectHex == 'x' || *detectHex == 'X'){
          val = strtol(*str, &endptr, baseHex);
          //if((val == LONG_MAX || val == LONG_MIN) && errno == ERANGE)
          //{
            //*str = endptr;
            //return -1;
          //}
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
                return -1;
              }
              ptr++;
            }
            *str = ptr;
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
	   return -1;
  }

  return -2;
}

/**
* compare two strings which in case insensitive
*/


int strcmpInsensitive(char* a)
{
  printf("['%s']\n", a);
  int length = strlen(a);
  int i = 0;
  length = length +1;
  char *lower = (char *)malloc(length);
  lower[length] = 0;

  // copy all character bytes to the new buffer using tolower
  for(i = 0; i < length; i++ )
  {
      lower[i] = tolower(a[i]);
      printf("['%c']\n", a[i]);
  }
  //cmp = strcmp(lower, b);
  //remember free memory
  return 0;
}
 

char *getSubString(char **strPtr){
  char *ptr;
  char *str;
  char data[10];
  int length;
  int i = 0;
  //length = length +1;
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
      //printf("['%s']\n", str);
      // copy all character bytes to the new buffer using tolower
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

 /**
 this function return how many byte data that is valid value and character  
 */

int loop(char **str){
  char *ptr;
  ptr = *str;
  int i=0;
  int value = 0;
  while(*ptr !='\n')
  {
    value = getNumber(str);
    printf("value = %d\n", value);
    ptr = *str;
    if(value != 4 || value !=-2 || value != 2 || value != 3 ||value != -1)
    {
      i++;
      printf("i = %d\n", i);
    }
    printf("i == %d\n", i);
  }

  return i;
}