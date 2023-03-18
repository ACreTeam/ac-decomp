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

extern void THA_ct(TwoHeadArena* this, char* p, size_t n);
extern void THA_dt(TwoHeadArena* this);
extern void* THA_getHeadPtr(TwoHeadArena* this); /* @unused */
extern void THA_setHeadPtr(TwoHeadArena* this, void* p); /* @unused */
extern void* THA_getTailPtr(TwoHeadArena* this); /* @unused */
extern void* THA_nextPtrN(TwoHeadArena* this, size_t n); /* @unused */
extern void* THA_nextPtr1(TwoHeadArena* this); /* @unused */
extern void* THA_alloc(TwoHeadArena* this, size_t siz);
extern void* THA_alloc16(TwoHeadArena* this, size_t siz);
extern void* THA_allocAlign(TwoHeadArena* this, size_t siz, int mask);
extern int THA_isCrash(TwoHeadArena* this);
extern void THA_init(TwoHeadArena* this);
extern int THA_getFreeBytes16(TwoHeadArena* this);
extern int THA_getFreeBytes(TwoHeadArena* this);
extern int THA_getFreeBytesAlign(TwoHeadArena* this, int mask);

#ifdef __cplusplus
};
#endif

#endif
