#ifndef _JAUDIO_BANKREAD_H
#define _JAUDIO_BANKREAD_H

#include "types.h"

typedef struct Bank_ Bank_;

Bank_* Bank_Test(u8*);
BOOL Bank_Regist(void*, u32);
BOOL Bank_Regist_Direct(void*, u32, u32);
void Bank_Init();
Bank_* Bank_Get(u32);

#endif
