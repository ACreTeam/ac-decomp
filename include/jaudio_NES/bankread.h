#ifndef BANKREAD_H
#define BANKREAD_H

#include "types.h"
#include "audiostruct.h"

#ifdef __cplusplus
extern "C" {
#endif

BOOL Bank_Regist(void* bank, u32 pid);
void Bank_Init(void);
Bank* Bank_Get(u32 pid);

#ifdef __cplusplus
}
#endif

#endif /* BANKREAD_H */
