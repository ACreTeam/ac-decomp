#ifndef THA_GA_H
#define THA_GA_H

#include "TwoHeadArena.h"
#include "PR/mbi.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  size_t size;
  Gfx* buf_p;
  Gfx* head_p;
  Gfx* tail_p;
} TwoHeadArenaGfx_t;

typedef TwoHeadArenaGfx_t TwoHeadArenaGfx;

typedef union {
  TwoHeadArena tha;
  TwoHeadArenaGfx thaGfx;
} THA_GA_t;

typedef THA_GA_t THA_GA;

extern void THA_GA_ct(THA_GA* this, Gfx* p, size_t n);
extern void THA_GA_dt(THA_GA* this); /* @unused */
extern int THA_GA_isCrash(THA_GA* this);
extern void THA_GA_init(THA_GA* this); /* @unused*/
extern int THA_GA_getFreeBytes(THA_GA* this);
extern void* THA_GA_getTailPtr(THA_GA* this); /* @unused */
extern void* THA_GA_nextPtrN(THA_GA* this, size_t n); /* @unused */
extern void* THA_GA_nextPtr1(THA_GA* this); /* @unused */
extern Gfx* THA_GA_NEXT_DISP(THA_GA* this); /* @unused */
extern void* THA_GA_getHeadPtr(THA_GA* this); /* @unused */
extern void THA_GA_setHeadPtr(THA_GA* this, void *p); /* @unused */
extern Mtx* THA_GA_alloc(THA_GA* this, size_t n); /* @unused */
extern Mtx* THA_GA_allocMtxN(THA_GA* this, size_t n); /* @unused */
extern Mtx* THA_GA_allocMtx1(THA_GA* this); /* @unused */
extern Vtx* THA_GA_allocVtxN(THA_GA* this, size_t n); /* @unused */
extern Vtx* THA_GA_allocVtx1(THA_GA* this); /* @unused */

#ifdef __cplusplus
};
#endif

#endif
