#ifndef AC_TURI_CLIP_H
#define AC_TURI_CLIP_H

#include "types.h"
#include "ac_ev_angler.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*aTRC_GET_MSGNO_PROC)(mActor_name_t);
typedef void (*aTRC_RANDOM_TOPSIZE_PROC)(void);
typedef void (*aTRC_SET_TOPNAME_PROC)(void);
typedef int (*aTRC_FISH_RNDSIZE_PROC)(int);

typedef struct turi_clip_s {
    aTRC_GET_MSGNO_PROC get_msgno_proc;
    aTRC_RANDOM_TOPSIZE_PROC random_topsize_proc;
    aTRC_SET_TOPNAME_PROC set_topname_proc;
    aTRC_FISH_RNDSIZE_PROC fish_rndsize_proc;
} aTRC_clip_c;

extern int aTRC_clip_get_msgno(mActor_name_t item);
extern void aTRC_clip_random_topsize(void);
extern void aTRC_clip_set_topname(void);
extern int aTRC_clip_fish_rndsize(int size_rank);

#ifdef __cplusplus
}
#endif

#endif
