#ifndef ErrorObject_H
#define ErrorObject_H
#include "strtonum.h"

typedef enum{
  ERR_INVALID_HEX,
  ERR_INVALID_VALUE,
  ERR_CANNOT_RESOLVE_ALPHABET,
  ERR_EMPTY_STRING
}ErrorCode;

typedef struct{
  char *errorMsg;
  ErrorCode errorCode;
}ErrorObject;

void freeError(ErrorObject* errObj);
void throwError(char *message, ErrorCode errCode);


#endif // ErrorObject_H
