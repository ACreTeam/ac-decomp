#ifndef AC_SIGN_H
#define AC_SIGN_H

#include "types.h"
#include "m_actor.h"
#include "m_field_make.h"
#include "m_olib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aSIGN_SINGLE_NUM 10

#define aSIGN_CULL_MAX_DIST (mFI_UNIT_BASE_SIZE_F * 4)

typedef struct sign_actor_s SIGN_ACTOR;

typedef struct sign_draw_s {
    BlockOrUnit_c block;
    u16 exist_bitfield[UT_Z_NUM];
} aSIGN_draw_c;

typedef struct sign_single_s {
    BlockOrUnit_c block;
    BlockOrUnit_c unit;
    mActor_name_t item;
    xyz_t scale;
    f32 _20;
    s16 _24;
    s16 _26;
    int exist_flag;
} aSIGN_single_c;

typedef void (*aSIGN_ACTION_PROC)(SIGN_ACTOR*, GAME*);

struct sign_actor_s {
    ACTOR actor_class;
    aSIGN_ACTION_PROC action_proc;
    aSIGN_draw_c draw[mFM_VISIBLE_BLOCK_NUM];
    aSIGN_single_c single[aSIGN_SINGLE_NUM];
    BlockOrUnit_c target_block;
    BlockOrUnit_c target_unit;
    xyz_t target_pos;
    xyz_t sign_birth_pos;
    xyz_t sign_pos;
    int _404;
    int is_winter;
};

extern int aSIGN_set_white_sign(GAME* game, xyz_t* pos_p);
extern int aSIGN_erase_white_sign(GAME* game, xyz_t* pos_p);

extern ACTOR_PROFILE Ac_Sign_Profile;

#ifdef __cplusplus
}
#endif

#endif
