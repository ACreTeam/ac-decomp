#ifndef DB_H
#define DB_H

#include "types.h"

#ifdef __cplusplus
extern "C"{
#endif

#define OS_DBINTERFACE_ADDR 0x00000040

typedef struct DBInterface
{
    u32     bPresent;
    u32     exceptionMask;
    void    (*ExceptionDestination) ( void );
    void    *exceptionReturn;
} DBInterface;

extern DBInterface* __DBInterface;

void DBInit(void);
void DBInitComm(int* inputFlagPtr, int* mtrCallback);
static void __DBExceptionDestination(void);
void DBPrintf(char* format, ...);

#ifdef __cplusplus
}
#endif
#endif
