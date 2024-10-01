#ifndef AC_BOXTRICK01_H
#define AC_BOXTRICK01_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

// sizeof(BoxTrick01_data_c) == 0x8
typedef struct box_trick_data_s {
    /* 0x0 */ u8 block_x;
    /* 0x1 */ u8 block_z;
    /* 0x4 */ void* data;
} BoxTrick01_data_c;

typedef struct box_trick01_s{
    ACTOR actor_class;
    int block_x;
    int block_z;
}BOXTRICK01_ACTOR;

extern ACTOR_PROFILE BoxTrick01_Profile;


#ifdef __cplusplus
}
#endif

#endif

