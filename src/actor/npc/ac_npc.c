#include "ac_npc.h"

#include "libultra/libultra.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_msg.h"
#include "ac_handOverItem.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "jsyswrap.h"
#include "dolphin/os.h"
#include "ac_ev_ghost.h"
#include "ac_gyoei.h"
#include "m_melody.h"
#include "ac_ball.h"
#include "m_actor_shadow.h"

extern aNPC_draw_data_c npc_draw_data_tbl[];

#define aNPC_CLOTH_TEX_SIZE ((32*32)/2)
#define aNPC_CLOTH_PAL_SIZE (16*sizeof(u16))

#define aNPC_GET_TYPE(npc) (ITEM_NAME_GET_TYPE((npc)->actor_class.npc_id))
#define aNPC_IS_NRM_NPC(npc) (aNPC_GET_TYPE(npc) == NAME_TYPE_NPC)
#define aNPC_IS_SP_NPC(npc) (aNPC_GET_TYPE(npc) == NAME_TYPE_SPNPC)
#define aNPC_GET_ANM(npc) ((npc)->npc_info.animal)
#define aNPC_GET_LOOKS(npc) (aNPC_GET_ANM(npc)->id.looks)

typedef struct npc_control_cloth_s {
    /* 0x00 */ u8 dma_flag;
    /* 0x01 */ u8 init_flag;
    /* 0x02 */ s16 _02;
    /* 0x04 */ mActor_name_t cloth_item;
    /* 0x06 */ s8 in_use_count;
    /* 0x07 */ u8 id;
    /* 0x08 */ Object_Bank_c texture_bank;
    /* 0x0A */ Object_Bank_c palette_bank;
} aNPC_cloth_c;

typedef struct npc_control_talk_area_s {
    u32 frame_counter;
    ACTOR* talk_actor;
    f32 radius;
    xyz_t center_pos;
} aNPC_talk_area_c;

#define aNPC_CTRL_CLOTH_NUM 10

typedef struct npc_control_actor_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ aNPC_cloth_c cloth[aNPC_CTRL_CLOTH_NUM];
    /* 0x8F4 */ u8 _8F4[0x9B0 - 0x8F4]; // TODO
    /* 0x9B0 */ aNPC_talk_area_c talk_area;
    /* 0x9C8 */ ACTOR* door_exit_actor;
    /* 0x9CC */ int door_exit_timer;
    /* 0x9D0 */ ACTOR* umbrella_open_actor;
    /* 0x9D4 */ int umbrella_open_timer;
} NPC_CONTROL_ACTOR;

static aNPC_Clip_c aNPC_clip;
static u16 aNPC_req_default_data[aNPC_REQUEST_ARG_NUM] = { 0, 0, 0, 0, 0, 0 };
static ACTOR* aNPC_ctrlActor = NULL;

static void aNPC_actor_ct_c(ACTOR* actorx, GAME* game);
static void aNPC_actor_dt_c(ACTOR* actorx, GAME* game);
static void aNPC_actor_move_c(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Profile = {
    mAc_PROFILE_NPC,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_CONTROL_ACTOR),
    &aNPC_actor_ct_c,
    &aNPC_actor_dt_c,
    &aNPC_actor_move_c,
    mActor_NONE_PROC1,
    NULL,
};
// clang-format on

static void aNPC_set_frame_sub_speed(NPC_ACTOR* nactorx, int seqNo);
static void aNPC_TumbleSe(xyz_t* pos_p);
static void aNPC_WalkSe(xyz_t* pos_p);
static void aNPC_OngenTrgStart(NPC_ACTOR* nactorx, u16 se_no);
static int aNPC_set_request_act(NPC_ACTOR* nactorx, u8 prio, u8 act_idx, u8 act_type, u16* args);
static int aNPC_set_head_request(NPC_ACTOR* nactorx, u8 prio, u8 type, ACTOR* target_actor, xyz_t* target_pos);
static void aNPC_set_feel_info(NPC_ACTOR* nactorx, int feel, int timer);
static void aNPC_set_dst_pos(NPC_ACTOR* nactorx, f32 pos_x, f32 pos_z);
static void aNPC_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play);
static void aNPC_action_proc(NPC_ACTOR* nactorx, GAME_PLAY* play);
static void aNPC_talk_area_check(NPC_ACTOR* nactorx, GAME_PLAY* play);
static void aNPC_set_feel_effect(GAME* game, NPC_ACTOR* nactorx);
static void aNPC_set_other_effect(GAME* game, NPC_ACTOR* nactorx);
static void aNPC_act_get_chg_cloth(NPC_ACTOR* nactorx, GAME_PLAY* play);
static void aNPC_act_get_chg_umb(NPC_ACTOR* nactorx, GAME_PLAY* play);
static void aNPC_act_get_chg_cloth_and_umb(NPC_ACTOR* nactorx, GAME_PLAY* play);
static void aNPC_act_umb_close_main_proc(NPC_ACTOR* nactorx, GAME_PLAY* play);
static void aNPC_set_hide_request(NPC_ACTOR* nactorx, u8 req);
static void aNPC_reset_out_of_door_flg(NPC_CONTROL_ACTOR* ctrl, ACTOR* actorx);
static void aNPC_reset_umb_open_flg(NPC_CONTROL_ACTOR* ctrl, ACTOR* actorx);
static int aNPC_setP_friendship(NPC_ACTOR* nactorx);
static void aNPC_think_in_block_chg_native_info(ACTOR* actorx, f32 home_x, f32 home_z);
static int aNPC_check_home_block(NPC_ACTOR* nactorx);
static void aNPC_set_schedule(NPC_ACTOR* nactorx, GAME_PLAY* play);
static void aNPC_dma_draw_data_proc(aNPC_draw_data_c* draw_data_p, mActor_name_t npc_name);

#include "../src/actor/npc/ac_npc_data.c_inc"
#include "../src/actor/npc/ac_npc_cloth.c_inc"
#include "../src/actor/npc/ac_npc_anime.c_inc"
#include "../src/actor/npc/ac_npc_sound.c_inc"
#include "../src/actor/npc/ac_npc_hand.c_inc"
#include "../src/actor/npc/ac_npc_head.c_inc"
#include "../src/actor/npc/ac_npc_talk.c_inc"
#include "../src/actor/npc/ac_npc_move.c_inc"
#include "../src/actor/npc/ac_npc_draw.c_inc"
#include "../src/actor/npc/ac_npc_effect.c_inc"
#include "../src/actor/npc/ac_npc_action.c_inc"
#include "../src/actor/npc/ac_npc_think.c_inc"
#include "../src/actor/npc/ac_npc_schedule.c_inc"
#include "../src/actor/npc/ac_npc_init.c_inc"
#include "../src/actor/npc/ac_npc_ct.c_inc"
#include "../src/actor/npc/ac_npc_dt.c_inc"
#include "../src/actor/npc/ac_npc_save.c_inc"
#include "../src/actor/npc/ac_npc_ctrl.c_inc"
