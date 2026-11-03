#ifndef _DOLPHIN_DVDPRIV
#define _DOLPHIN_DVDPRIV

#include <dolphin/dvd.h>
#include "dvd/__dvd.h"
typedef DVDCommandChecker DVDOptionalCommandChecker;
#include <dolphin/hw_regs.h>
#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DVDBB1 {
  u32 appLoaderLength;
  void* appLoaderFunc1;
  void* appLoaderFunc2;
  void* appLoaderFunc3;
} DVDBB1;



#ifdef __cplusplus
}
#endif // _DOLPHIN_DVDPRIV

#endif __DVDPRIV_H__
