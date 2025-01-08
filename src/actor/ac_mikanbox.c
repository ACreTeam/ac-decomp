#include "ac_mikanbox.h"

#include "m_string.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_bgm.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "sys_matrix.h"
#include "m_rcp.h"

#define aMIK_STRING_NUM 10
#define aMIK_STRING_LEN 25

enum {
    aMIK_ACTION_WAIT,

    aMIK_ACTION_NUM
};

static void aMIK_actor_ct(ACTOR* actorx, GAME* game);
static void aMIK_actor_dt(ACTOR* actorx, GAME* game);
static void aMIK_actor_init(ACTOR* actorx, GAME* game);
static void aMIK_actor_draw(ACTOR* actorx, GAME* game);
static void aMIK_actor_save(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Mikanbox_Profile = {
    mAc_PROFILE_MIKANBOX,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NONE,
    MIKANBOX,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(MIKANBOX_ACTOR),
    &aMIK_actor_ct,
    &aMIK_actor_dt,
    &aMIK_actor_init,
    &aMIK_actor_draw,
    &aMIK_actor_save,
};
// clang-format on

static aMKBC_Clip_c aMKBC_clip;

static void aMKBC_clip_set_string(int base);
static void aMKBC_clip_roll_draw(GAME_PLAY* play, int timer, int page_idx);
static void aMKBC_clip_think_init(NPC_TOTAKEKE_ACTOR* totakeke, GAME_PLAY* play, int init_idx);
static void aMKBC_clip_sound_proc(NPC_TOTAKEKE_ACTOR* totakeke, GAME_PLAY* play, int idx);
static int aMKBC_clip_section_chk(int section);
static u8 aMKBC_clip_bgm_no(NPC_TOTAKEKE_ACTOR* totakeke);
static void aMKBC_clip_roll_proc(NPC_TOTAKEKE_ACTOR* totakeke, GAME_PLAY* play);
static void aMKBC_clip_head_up(ACTOR* actorx);
static void aMKBC_clip_set_itemstr(int str_no, u8 md_no);
static void aMKBC_clip_set_itemstr3(void);
static u8 aMKBC_clip_search_merody(void);
static void aMKBC_clip_check_merody(u32 md_no);

static void aMIK_actor_ct(ACTOR* actorx, GAME* game) {
    aMKBC_clip.set_string_proc = &aMKBC_clip_set_string;
    aMKBC_clip.roll_draw_proc = &aMKBC_clip_roll_draw;
    aMKBC_clip.think_init_proc = &aMKBC_clip_think_init;
    aMKBC_clip.sound_proc = &aMKBC_clip_sound_proc;
    aMKBC_clip.section_chk_proc = &aMKBC_clip_section_chk;
    aMKBC_clip.bgm_no_proc = &aMKBC_clip_bgm_no;
    aMKBC_clip.roll_proc = &aMKBC_clip_roll_proc;
    aMKBC_clip.head_up_proc = &aMKBC_clip_head_up;
    aMKBC_clip.set_itemstr_proc = &aMKBC_clip_set_itemstr;
    aMKBC_clip.set_itemstr3_proc = &aMKBC_clip_set_itemstr3;
    aMKBC_clip.search_merody_proc = &aMKBC_clip_search_merody;
    aMKBC_clip.check_merody_proc = &aMKBC_clip_check_merody;

    CLIP(mikanbox_clip) = &aMKBC_clip;
}


static void aMIK_actor_dt(ACTOR* actorx, GAME* game) {
    CLIP(mikanbox_clip) = NULL;
}

static void aMIK_actor_save(ACTOR* actorx, GAME* game) {
    // nothing
}

#include "../src/actor/ac_mikanbox_clip.c_inc"
#include "../src/actor/ac_mikanbox_move.c_inc"
#include "../src/actor/ac_mikanbox_draw.c_inc"
