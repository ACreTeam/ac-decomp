#ifndef AC_GYOEI_H
#define AC_GYOEI_H

#include "types.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aGYO_MAX_GYOEI 2

enum {
    aGYO_TYPE_TEST,
    aGYO_TYPE_KASEKI,

    aGYO_TYPE_NUM
};

enum {
    aGYO_ROD_NORMAL,
    aGYO_ROD_GOLDEN,

    aGYO_ROD_NUM
};

enum {
    aGYO_DRAW_TYPE_GYOEI,
    aGYO_DRAW_TYPE_FISH,

    aGYO_DRAW_TYPE_NUM
};

typedef struct gyo_ctrl_actor_s aGYO_CTRL_ACTOR;

typedef void (*aGYO_ACT_PROC)(ACTOR*, GAME*);

/* sizeof(aGYO_CTRL_ACTOR) == 0x250 */
struct gyo_ctrl_actor_s {
    /* 0x000 */ TOOLS_ACTOR tools_class;
    /* 0x1CC */ ACTOR* linked_actor; /* Generally UKI_ACTOR */
    /* 0x1D0 */ int exist;
    /* 0x1D4 */ int draw_type;
    /* 0x1D8 */ int gyo_type;
    /* 0x1DC */ s16 size_type;
    /* 0x1E0 */ int action;
    /* 0x1E4 */ aGYO_ACT_PROC act_proc;
    /* 0x1E8 */ int anim_frame;
    /* 0x1EC */ f32 speed_step;
    /* 0x1F0 */ f32 speed;
    /* 0x1F4 */ f32 range;
    /* 0x1F8 */ int _1F8;
    /* 0x1FC */ ClObjPipe_c col_pipe;
    /* 0x218 */ int work0;
    /* 0x21C */ f32 fwork0;
    /* 0x220 */ f32 fwork1;
    /* 0x224 */ f32 fwork2;
    /* 0x228 */ f32 fwork3;
    /* 0x22C */ s16 swork0;
    /* 0x22E */ s16 swork1;
    /* 0x230 */ s16 swork2;
    /* 0x232 */ s16 swork3;
    /* 0x234 */ s16 swork4;
    /* 0x236 */ s16 move_counter;
    /* 0x238 */ s16 move_angle;
    /* 0x23A */ s16 pattern_subcounter;
    /* 0x23C */ s16 pattern_counter;
    /* 0x23E */ s16 touch_counter;
    /* 0x240 */ u16 gyo_flags;
    /* 0x242 */ u8 swim_flag;
    /* 0x243 */ u8 escape_flag;
    /* 0x244 */ int alpha;
    /* 0x248 */ int col_flags;
    /* 0x24C */ u8* overlay_p;
};

typedef struct gyoei_actor_s GYOEI_ACTOR;

/* sizeof(GYOEI_ACTOR) == 0x628 */
struct gyoei_actor_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ aGYO_CTRL_ACTOR ctrl[aGYO_MAX_GYOEI];
    /* 0x614 */ u8 exist[4];
    /* 0x618 */ int segment_type[4];
};

extern ACTOR_PROFILE Gyoei_Profile;

#ifdef __cplusplus
}
#endif

#endif
