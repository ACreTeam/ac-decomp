#ifndef TWOHEADARENA_H
#define TWOHEADARENA_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  size_t size;
  char *buf_p;
  char *head_p;
  char *tail_p;
} TwoHeadArena_t;
typedef TwoHeadArena_t TwoHeadArena;
typedef TwoHeadArena_t THA;

extern void THA_ct(TwoHeadArena* tha, char* p, size_t n);
extern void THA_dt(TwoHeadArena* tha);
extern void* THA_getHeadPtr(TwoHeadArena* tha); /* @unused */
extern void THA_setHeadPtr(TwoHeadArena* tha, void* p); /* @unused */
extern void* THA_getTailPtr(TwoHeadArena* tha); /* @unused */
extern void* THA_nextPtrN(TwoHeadArena* tha, size_t n); /* @unused */
extern void* THA_nextPtr1(TwoHeadArena* tha); /* @unused */
extern void* THA_alloc(TwoHeadArena* tha, size_t siz);
extern void* THA_alloc16(TwoHeadArena* tha, size_t siz);
extern void* THA_allocAlign(TwoHeadArena* tha, size_t siz, int mask);
extern int THA_isCrash(TwoHeadArena* tha);
extern void THA_init(TwoHeadArena* tha);
extern int THA_getFreeBytes16(TwoHeadArena* tha);
extern int THA_getFreeBytes(TwoHeadArena* tha);
extern int THA_getFreeBytesAlign(TwoHeadArena* tha, int mask);

#ifdef __cplusplus
};
#endif

#endif
