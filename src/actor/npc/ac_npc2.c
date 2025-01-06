#define aNPC_NPC2
#include "ac_npc2.h"
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
#include "m_melody.h"
#include "m_actor_shadow.h"
#include "m_event_map_npc.h"
#include "m_malloc.h"

#define aNPC_UNIT_RIGHT (1 << 0)
#define aNPC_UNIT_LEFT (1 << 1)
#define aNPC_UNIT_DOWN (1 << 2)
#define aNPC_UNIT_UP (1 << 3)
#define aNPC_UNIT_ALL (aNPC_UNIT_UP | aNPC_UNIT_DOWN | aNPC_UNIT_LEFT | aNPC_UNIT_RIGHT)

enum {
    aNPC_SEARCH_ROUTE_FORWARD,
    aNPC_SEARCH_ROUTE_BACKWARD,
    aNPC_SEARCH_ROUTE_CANCEL,

    aNPC_SEARCH_ROUTE_NUM = aNPC_SEARCH_ROUTE_CANCEL
};

enum {
    aNPC_ROUTE_ERROR,
    aNPC_ROUTE_FINISH,
    aNPC_ROUTE_MOVING,

    aNPC_ROUTE_NUM
};

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

typedef struct npc_unit_info_s {
    int x;
    int z;
    int direct;
} aNPC_unit_info_c;

#define aNPC_CTRL_CLOTH_NUM 10
#define aNPC2_UNIT_X_NUM 6
#define aNPC2_UNIT_Z_NUM 7
#define aNPC2_UNIT_NUM (aNPC2_UNIT_X_NUM * aNPC2_UNIT_Z_NUM)
#define aNPC_ROUTE_NODE_MAX 20

typedef struct npc_control_actor_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ aNPC_cloth_c cloth[aNPC_CTRL_CLOTH_NUM];
    /* 0x8F4 */ u8 _8F4[0x928 - 0x8F4]; // TODO
    /* 0x928 */ int unit_info[aNPC2_UNIT_Z_NUM][aNPC2_UNIT_X_NUM];
    /* 0x9D0 */ aNPC_unit_info_c route[aNPC_ROUTE_NODE_MAX];
    /* 0xAC0 */ int route_node_count;
    /* 0xAC4 */ int safe_ux[4];
    /* 0xAD4 */ int safe_uz[4];
} NPC_CONTROL_ACTOR;

static aNPC_Clip_c aNPC_clip;
static u16 aNPC_req_default_data[aNPC_REQUEST_ARG_NUM] = { 0, 0, 0, 0, 0, 0 };
static ACTOR* aNPC_ctrlActor = NULL;

static void aNPC_actor_ct_c(ACTOR* actorx, GAME* game);
static void aNPC_actor_dt_c(ACTOR* actorx, GAME* game);
static void aNPC_actor_move_c(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc2_Profile = {
    mAc_PROFILE_NPC, // @BUG - shouldn't this be mAc_PROFILE_NPC2???
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
static void aNPC_set_hide_request(NPC_ACTOR* nactorx, u8 req);
static int aNPC_setP_friendship(NPC_ACTOR* nactorx);
static void aNPC_set_schedule(NPC_ACTOR* nactorx, GAME_PLAY* play);
static void aNPC_dma_draw_data_proc(aNPC_draw_data_c* draw_data_p, mActor_name_t npc_name);
static void aNPC_WalkSeRoom(xyz_t* pos_p);
static int aNPC_route_check(NPC_ACTOR* nactorx, GAME_PLAY* play, int ux, int uz, int turn);

#include "../src/actor/npc/ac_npc_data.c_inc"
#include "../src/actor/npc/ac_npc_cloth.c_inc"
#include "../src/actor/npc/ac_npc_anime.c_inc"
#include "../src/actor/npc/ac_npc_sound.c_inc"
#include "../src/actor/npc/ac_npc_hand.c_inc"
#include "../src/actor/npc/ac_npc_head.c_inc"
#include "../src/actor/npc/ac_npc_talk.c_inc"
#include "../src/actor/npc/ac_npc2_move.c_inc"
#include "../src/actor/npc/ac_npc_draw.c_inc"
#include "../src/actor/npc/ac_npc_effect.c_inc"
#include "../src/actor/npc/ac_npc2_action.c_inc"
#include "../src/actor/npc/ac_npc2_think.c_inc"
#include "../src/actor/npc/ac_npc2_schedule.c_inc"
#include "../src/actor/npc/ac_npc_init.c_inc"
#include "../src/actor/npc/ac_npc_ct.c_inc"
#include "../src/actor/npc/ac_npc_dt.c_inc"
#include "../src/actor/npc/ac_npc_save.c_inc"
#include "../src/actor/npc/ac_npc_ctrl.c_inc"

#undef aNPC_NPC2
