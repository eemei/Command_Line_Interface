#ifndef _strtonum_H
#define _strtonum_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

long int getNumber(char  **str);
int strcmpInsensitive(char* a);
int loop(char **str);
char *subString(char **strPtr);
char *getSubString(char **strPtr);
#endif // _strtonum_H
