#ifndef strtonum_H
#define strtonum_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

long int getNumber(char  **str);
char *getSubString(char **strPtr);
#endif // strtonum_H
