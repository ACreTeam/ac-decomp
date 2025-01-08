#ifndef AC_MIKANBOX_CLIP_H
#define AC_MIKANBOX_CLIP_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc_totakeke.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aMKBC_NUM_GOOD_MD (ITM_MINIDISK52 - ITM_MINIDISK_START)

typedef void (*aMKBC_SET_STRING_PROC)(int base);
typedef void (*aMKBC_ROLL_DRAW_PROC)(GAME_PLAY* play, int timer, int page_idx);
typedef void (*aMKBC_THINK_INIT_PROC)(NPC_TOTAKEKE_ACTOR* totakeke, GAME_PLAY* play, int init_idx);
typedef void (*aMKBC_SOUND_PROC)(NPC_TOTAKEKE_ACTOR* totakeke, GAME_PLAY* play, int idx);
typedef int (*aMKBC_SECTION_CHK_PROC)(int section);
typedef u8 (*aMKBC_BGM_NO_PROC)(NPC_TOTAKEKE_ACTOR* totakeke);
typedef void (*aMKBC_ROLL_PROC)(NPC_TOTAKEKE_ACTOR* totakeke, GAME_PLAY* play);
typedef void (*aMKBC_HEAD_UP_PROC)(ACTOR* actorx);
typedef void (*aMKBC_SET_ITEMSTR_PROC)(int str_no, u8 md_no);
typedef void (*aMKBC_SET_ITEMSTR3_PROC)(void);
typedef u8 (*aMKBC_SEARCH_MERODY_PROC)(void);
typedef void (*aMKBC_CHECK_MERODY_PROC)(u32 md_no);

typedef struct mikanbox_clip_s aMKBC_Clip_c;

struct mikanbox_clip_s {
    /* 0x000 */ aMKBC_SET_STRING_PROC set_string_proc;
    /* 0x004 */ aMKBC_ROLL_DRAW_PROC roll_draw_proc;
    /* 0x008 */ aMKBC_THINK_INIT_PROC think_init_proc;
    /* 0x00C */ aMKBC_SOUND_PROC sound_proc;
    /* 0x010 */ aMKBC_SECTION_CHK_PROC section_chk_proc;
    /* 0x014 */ aMKBC_BGM_NO_PROC bgm_no_proc;
    /* 0x018 */ aMKBC_ROLL_PROC roll_proc;
    /* 0x01C */ aMKBC_HEAD_UP_PROC head_up_proc;
    /* 0x020 */ aMKBC_SET_ITEMSTR_PROC set_itemstr_proc;
    /* 0x024 */ aMKBC_SET_ITEMSTR3_PROC set_itemstr3_proc;
    /* 0x028 */ aMKBC_SEARCH_MERODY_PROC search_merody_proc;
    /* 0x02C */ aMKBC_CHECK_MERODY_PROC check_merody_proc;
};

#ifdef __cplusplus
}
#endif

#endif
