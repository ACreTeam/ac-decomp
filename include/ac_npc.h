#ifndef AC_NPC_H
#define AC_NPC_H

#include "types.h"
#include "m_actor.h"
#include "m_play.h"
#include "ac_npc_h.h"
#include "m_npc_schedule.h"
#include "m_actor_dlftbls.h"
#include "m_npc.h"
#include "c_keyframe.h"
#include "ac_npc_anim_def.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aNPC_SPNPC_BIT_CURATOR 0
#define aNPC_SPNPC_BIT_GOHOME_NPC 1
#define aNPC_SPNPC_BIT_MASK_CAT 2
#define aNPC_SPNPC_BIT_SHOP_MASTER 3
#define aNPC_SPNPC_BIT_DOZAEMON 4
#define aNPC_SPNPC_BIT_EV_SONCHO 5

#define aNPC_SPNPC_BIT_GET(field, bit) (((field) >> (bit)) & 1)
#define aNPC_SPNPC_BIT_SET(field, bit) ((field) |= (1 << (bit)))
#define aNPC_SPNPC_BIT_CLR(field, bit) ((field) &= ~(1 << (bit)))

// To use this enum, make sure that m_common_data.h is included!
#define NPC_CLIP CLIP(npc_clip)

enum {
    aNPC_JOINT_BASE_ROOT,
    aNPC_JOINT_BASE,
    aNPC_JOINT_LFOOT_ROOT,
    aNPC_JOINT_LFOOT1,
    aNPC_JOINT_LFOOT2,
    aNPC_JOINT_LFOOT3,
    aNPC_JOINT_RFOOT_ROOT,
    aNPC_JOINT_RFOOT1,
    aNPC_JOINT_RFOOT2,
    aNPC_JOINT_RFOOT3,
    aNPC_JOINT_TAIL_ROOT,
    aNPC_JOINT_TAIL1,
    aNPC_JOINT_TAIL2,
    aNPC_JOINT_CHEST,
    aNPC_JOINT_LARM_ROOT,
    aNPC_JOINT_LARM1,
    aNPC_JOINT_LARM2,
    aNPC_JOINT_RARM_ROOT,
    aNPC_JOINT_RARM1,
    aNPC_JOINT_RARM2,
    aNPC_JOINT_HAND,
    aNPC_JOINT_HEAD_ROOT,
    aNPC_JOINT_MOUTH_ROOT,
    aNPC_JOINT_MOUTH,
    aNPC_JOINT_HEAD,
    aNPC_JOINT_FEEL,

    aNPC_JOINT_NUM
};

enum {
    aNPC_ANIM_SPEED_TYPE_LOCKED,
    aNPC_ANIM_SPEED_TYPE_FREE,

    aNPC_ANIM_SPEED_TYPE_NUM
};

enum {
    aNPC_SUB_ANIM_NONE,
    aNPC_SUB_ANIM_UMBRELLA,
    aNPC_SUB_ANIM_UTIWA, // paper fan
    aNPC_SUB_ANIM_TUE,   // Tortimer's cane

    aNPC_SUB_ANIM_NUM
};

enum {
    aNPC_TEX_ANIM_EYE,
    aNPC_TEX_ANIM_MOUTH,

    aNPC_TEX_ANIM_NUM
};

enum {
    aNPC_CHN_BASE_TYPE_RELATIVE,
    aNPC_CHN_BASE_TYPE_WORLD,

    aNPC_CHN_BASE_TYPE_NUM
};

enum {
    aNPC_CLOTH_IDX_NONE,
    aNPC_CLOTH_IDX0,
    aNPC_CLOTH_IDX1,
    aNPC_CLOTH_IDX2,
    aNPC_CLOTH_IDX3,
    aNPC_CLOTH_IDX4,
    aNPC_CLOTH_IDX5,
    aNPC_CLOTH_IDX6,
    aNPC_CLOTH_IDX7,
    aNPC_CLOTH_IDX8,
    aNPC_CLOTH_IDX9,
    aNPC_CLOTH_IDX_ORG,

    aNPC_CLOTH_IDX_NUM
};

enum {
    aNPC_MASK_CAT_TYPE_NONE,
    aNPC_MASK_CAT_TYPE_MASKCAT,

    aNPC_MASK_CAT_TYPE_NUM
};

typedef struct ac_npc_clip_s aNPC_Clip_c;

enum {
    aNPC_EYE_TEX0,
    aNPC_EYE_TEX1,
    aNPC_EYE_TEX2,
    aNPC_EYE_TEX3,
    aNPC_EYE_TEX4,
    aNPC_EYE_TEX5,
    aNPC_EYE_TEX6,
    aNPC_EYE_TEX7,
    aNPC_EYE_TEX_NUM,
};

enum {
    aNPC_MOUTH_TEX0,
    aNPC_MOUTH_TEX1,
    aNPC_MOUTH_TEX2,
    aNPC_MOUTH_TEX3,
    aNPC_MOUTH_TEX4,
    aNPC_MOUTH_TEX5,
    aNPC_MOUTH_TEX_NUM,
};

/* sizeof(aNPC_draw_tex_data_c) == 0x4C */
typedef struct ac_npc_draw_data_tex_s {
    /* 0x00 */ u8* texture;  // main animal texture
    /* 0x04 */ u16* palette; // palette for animal
    /* 0x08 */ u8* eye_texture[aNPC_EYE_TEX_NUM];
    /* 0x28 */ u8* mouth_texture[aNPC_MOUTH_TEX_NUM];
    /* 0x40 */ int _40;
    /* 0x44 */ int _44;
    /* 0x48 */ int _48;
} aNPC_draw_tex_data_c;

/* sizeof(aNPC_draw_data_c) == 0x6C */
typedef struct npc_draw_data_s {
    /* 0x00 */ s16 model_bank;
    /* 0x02 */ s16 texture_bank;
    /* 0x04 */ cKF_Skeleton_R_c* model_skeleton;
    /* 0x08 */ aNPC_draw_tex_data_c tex_data;
    /* 0x54 */ f32 scale;
    /* 0x58 */ int talk_type;
    /* 0x5C */ u8 species_sub_idx; // index into the current species type
    /* 0x5D */ u8 umbrella_type;   // default umbrella type -- only used for special NPCs
    /* 0x5E */ u8 eye_height;      // height of "eye" from the ground
    /* 0x5F */ u8 _5F;
    /* 0x60 */ u16 _60;
    /* 0x62 */ u16 voice_type;      // voice/melody type
    /* 0x64 */ s16 col_radius;      // collision pipe radius
    /* 0x66 */ s16 col_height;      // collision pipe height
    /* 0x68 */ s16 accessory_type;  // type of accessory
    /* 0x6A */ s16 accessory_joint; // joint the accessory is attached to
} aNPC_draw_data_c;

enum {
    aNPC_ATTENTION_TYPE_NONE,
    aNPC_ATTENTION_TYPE_ACTOR,
    aNPC_ATTENTION_TYPE_POSITION,

    aNPC_ATTENTION_TYPE_NUM
};

#ifndef aNPC_NPC2
enum {
    aNPC_THINK_WAIT,
    aNPC_THINK_WANDER,
    aNPC_THINK_WALK_WANDER,
    aNPC_THINK_GO_HOME,
    aNPC_THINK_INTO_HOUSE,
    aNPC_THINK_LEAVE_HOUSE,
    aNPC_THINK_IN_BLOCK,
    aNPC_THINK_PITFALL,
    aNPC_THINK_SLEEP,
    aNPC_THINK_SPECIAL,

    aNPC_THINK_NUM
};
#else
enum {
    aNPC_THINK_WAIT,
    aNPC_THINK_HIDE,
    aNPC_THINK_WANDER,
    aNPC_THINK_OUT_OF_ROOM,
    aNPC_THINK_EXIT_WAIT,
    aNPC_THINK_INTO_ROOM,
    aNPC_THINK_SPECIAL,

    aNPC_THINK_NUM
};
#endif

enum {
    aNPC_THINK_TYPE_INIT,
    aNPC_THINK_TYPE_CHK_INTERRUPT,
    aNPC_THINK_TYPE_MAIN,

    aNPC_THINK_TYPE_NUM
};

enum {
    aNPC_THINK_PROC_INIT,
    aNPC_THINK_PROC_MAIN,

    aNPC_THINK_PROC_NUM
};

enum {
    aNPC_CT_SCHED_TYPE_NONE,
    aNPC_CT_SCHED_TYPE_NORMAL,
    aNPC_CT_SCHED_TYPE_STAND,
    aNPC_CT_SCHED_TYPE_WANDER,
    aNPC_CT_SCHED_TYPE_WALK_WANDER,
    aNPC_CT_SCHED_TYPE_SPECIAL,

    aNPC_CT_SCHED_TYPE_NUM
};

typedef void (*aNPC_TALK_REQUEST_PROC)(ACTOR*, GAME*);
typedef int (*aNPC_TALK_INIT_PROC)(ACTOR*, GAME*);
typedef int (*aNPC_TALK_END_CHECK_PROC)(ACTOR*, GAME*);

typedef struct npc_ct_data_s {
    mActor_proc move_proc;
    mActor_proc draw_proc;
    int sched_type;
    aNPC_TALK_REQUEST_PROC talk_request_proc;
    aNPC_TALK_INIT_PROC talk_init_proc;
    aNPC_TALK_END_CHECK_PROC talk_end_check_proc;
    int _18;
} aNPC_ct_data_c;

enum {
    aNPC_ATT_TYPE_NONE,
    aNPC_ATT_TYPE_ACTOR,
    aNPC_ATT_TYPE_POS,

    aNPC_ATT_TYPE_NUM
};

typedef struct npc_attention_s {
    u8 type;
    ACTOR* actor;
    xyz_t pos;
} aNPC_attention_c;

typedef struct npc_overlay_s {
    u8* buf;
    int used;
} aNPC_overlay_c;

typedef int (*aNPC_SETUP_ACTOR_PROC)(GAME_PLAY* play, mActor_name_t name, s8 idx, int mvlist_no, s16 arg, int bx,
                                     int bz, int ux, int uz);
typedef void (*aNPC_GET_OVERLAY_AREA_PROC)(ACTOR_DLFTBL*, u8*, size_t, mActor_name_t);
typedef void (*aNPC_DMA_DRAW_DATA_PROC)(aNPC_draw_data_c*, mActor_name_t);
typedef void (*aNPC_FREE_OVERLAY_AREA_PROC)(ACTOR_DLFTBL*);
typedef ACTOR* (*aNPC_GET_ACTOR_AREA_PROC)(size_t, const char*, int);
typedef void (*aNPC_FREE_ACTOR_AREA_PROC)(ACTOR*);
typedef void (*aNPC_SET_ATTENTION_REQUEST_PROC)(u8, ACTOR*, xyz_t*);
typedef int (*aNPC_BIRTH_CHECK_PROC)(ACTOR*, GAME*);
typedef void (*aNPC_CT_PROC)(ACTOR*, GAME*, aNPC_ct_data_c*);
typedef void (*aNPC_DT_PROC)(ACTOR*, GAME*);
typedef void (*aNPC_SAVE_PROC)(ACTOR*, GAME*);
typedef void (*aNPC_INIT_PROC)(ACTOR*, GAME*);
typedef void (*aNPC_MOVE_PROC)(ACTOR*, GAME*);
typedef void (*aNPC_MOVE_BEFORE_PROC)(ACTOR*, GAME*);
typedef void (*aNPC_MOVE_AFTER_PROC)(ACTOR*, GAME*);
typedef void (*aNPC_DRAW_PROC)(ACTOR*, GAME*);
typedef void (*aNPC_SET_DST_POS_PROC)(NPC_ACTOR*, f32, f32);

typedef void (*aNPC_REBUILD_DMA_PROC)();
typedef int (*aNPC_SET_REQUEST_ACT_PROC)(NPC_ACTOR* nactorx, u8 priority, u8 act_idx, u8 act_type, u16* arg_data);
typedef int (*aNPC_SET_HEAD_REQUEST_PROC)(NPC_ACTOR* nactorx, u8 priority, u8 type, ACTOR* target_actor,
                                          xyz_t* target_pos);
typedef void (*aNPC_TALK_DEMO_PROC)(ACTOR*);
typedef void (*aNPC_ANIMATION_INIT_PROC)(ACTOR*, int, int);
typedef void (*aNPC_CHG_SCHEDULE_PROC)(NPC_ACTOR*, GAME_PLAY*, u8);
typedef int (*aNPC_CLIP_THINK_PROC)(NPC_ACTOR*, GAME_PLAY*, int, int);
typedef int (*aNPC_FORCE_CALL_REQ_PROC)(NPC_ACTOR*, int);
typedef void (*aNPC_SET_START_POS_PROC)(ACTOR* actorx);

struct ac_npc_clip_s {
    /* 0x000 */ aNPC_SETUP_ACTOR_PROC setupActor_proc;
    /* 0x004 */ aNPC_GET_OVERLAY_AREA_PROC get_overlay_area_proc;
    /* 0x008 */ aNPC_FREE_OVERLAY_AREA_PROC free_overlay_area_proc;
    /* 0x00C */ aNPC_GET_ACTOR_AREA_PROC get_actor_area_proc;
    /* 0x010 */ aNPC_FREE_ACTOR_AREA_PROC free_actor_area_proc;
    /* 0x014 */ aNPC_DMA_DRAW_DATA_PROC dma_draw_data_proc;
    /* 0x018 */ aNPC_SET_ATTENTION_REQUEST_PROC set_attention_request_proc;
    /* 0x01C */ NPC_ACTOR* keep_actors[9];
    /* 0x040 */ int keep_actor_used[9];
    /* 0x064 */ aNPC_overlay_c keep_n_overlay[1];
    /* 0x06C */ aNPC_overlay_c keep_s_overlay[2];
    /* 0x07C */ aNPC_overlay_c keep_k_overlay[3];
    /* 0x094 */ aNPC_overlay_c keep_e_overlay[2];
    /* 0x0A4 */ aNPC_attention_c attention_request;
    /* 0x0B8 */ aNPC_attention_c attention;
    /* 0x0CC */ aNPC_BIRTH_CHECK_PROC birth_check_proc;
    /* 0x0D0 */ aNPC_CT_PROC ct_proc;
    /* 0x0D4 */ aNPC_DT_PROC dt_proc;
    /* 0x0D8 */ aNPC_SAVE_PROC save_proc;
    /* 0x0DC */ aNPC_INIT_PROC init_proc;
    /* 0x0E0 */ aNPC_MOVE_PROC move_proc;
    /* 0x0E4 */ aNPC_MOVE_BEFORE_PROC move_before_proc;
    /* 0x0E8 */ aNPC_MOVE_AFTER_PROC move_after_proc;
    /* 0x0EC */ void* _0EC;
    /* 0x0F0 */ void* _0F0;
    /* 0x0F4 */ aNPC_DRAW_PROC draw_proc;
    /* 0x0F8 */ aNPC_REBUILD_DMA_PROC rebuild_dma_proc;
    /* 0x0FC */ void* _0FC[(0x108 - 0x0FC) / sizeof(void*)];
    /* 0x108 */ aNPC_SET_REQUEST_ACT_PROC set_request_act_proc;
    /* 0x10C */ aNPC_SET_HEAD_REQUEST_PROC set_head_request_act_proc;
    /* 0x110 */ aNPC_TALK_DEMO_PROC talk_demo_proc;
    /* 0x114 */ aNPC_ANIMATION_INIT_PROC animation_init_proc;
    /* 0x118 */ aNPC_CHG_SCHEDULE_PROC chg_schedule_proc;
    /* 0x11C */ aNPC_SET_DST_POS_PROC set_dst_pos_proc;
    /* 0x120 */ aNPC_CLIP_THINK_PROC think_proc;
    /* 0x124 */ aNPC_FORCE_CALL_REQ_PROC force_call_req_proc;
    /* 0x128 */ aNPC_SET_START_POS_PROC set_start_pos_proc;
};

typedef struct npc_info_s {
    Animal_c* animal;
    mNpc_NpcList_c* list;
    mNPS_schedule_c* schedule;
    mNpc_EventNpc_c* event;
    mNpc_MaskNpc_c* mask;
    mActor_name_t npc_name;
} NpcActorInfo_c;

typedef struct npc_animation_s {
    cKF_SkeletonInfo_R_c keyframe;
    s_xyz work[27];
    s_xyz morph[27];
    int _1B4;
    s8 animation_id;
} aNPC_ANIMATION_c;

typedef struct {
    int num_check_frames;
    int* check_frame_tbl;
} aNPC_se_data_c;

enum {
    aNPC_OTHER_SE_TYPE_NONE,
    aNPC_OTHER_SE_TYPE1,

    aNPC_OTHER_SE_TYPE_NUM
};

typedef struct {
    aNPC_se_data_c se_data;
    u16 se_no;
} aNPC_other_se_data_c;

#define aNPC_OTHER_SE_NUM 3

typedef struct {
    aNPC_se_data_c lfoot;
    aNPC_se_data_c rfoot;
    int other_se_type;
    aNPC_other_se_data_c other_se[aNPC_OTHER_SE_NUM];
} aNPC_se_c;

typedef struct {
    u8 seq_type;
    u8 last_seq_type;
    u8 seq_pattern;
    u8 seq_counter;
    u8 pattern;
    f32 pattern_counter;
    s8 pattern_stop_idx;
    u8 loop_counter;
    u8* fixed_pattern_seq;
} aNPC_tex_anim_c;

typedef struct {
    s16 feel_type;
    u8 max;
    u8 set_num;
    u32* set_p;
} aNPC_feel_effect_c;

typedef struct npc_draw_info_s {
    /* 0x000 */ int main_animation_frame;
    /* 0x004 */ int main_animation_state;
    /* 0x008 */ int main_animation_frame_changed;
    /* 0x00C */ int sub_animation0_state;
    /* 0x010 */ int sub_animation1_state;
    /* 0x014 */ aNPC_ANIMATION_c main_animation;
    /* 0x1D0 */ aNPC_ANIMATION_c sub_animation0;
    /* 0x38C */ aNPC_ANIMATION_c sub_animation1;
    /* 0x548 */ aNPC_se_c se;
    /* 0x580 */ int animation_id;
    /* 0x584 */ int texture_bank_idx;
    /* 0x588 */ aNPC_tex_anim_c tex_anim[aNPC_TEX_ANIM_NUM]; // eye -> mouth
    /* 0x5B0 */ u8 draw_type;
    /* 0x5B1 */ u8 cloth_change_step;
    /* 0x5B2 */ mActor_name_t next_cloth_no;
    /* 0x5B4 */ mActor_name_t cloth_no;
    /* 0x5B6 */ u8 next_org_idx;
    /* 0x5B7 */ u8 org_idx;
    /* 0x5B8 */ s8 cloth_idx;
    /* 0x5B9 */ u8 chn_base_type;
    /* 0x5BA */ u16 _5BA;
    /* 0x5BC */ u8 umb_state;
    /* 0x5BD */ u8 sub_anim_type;
    /* 0x5BE */ u8 anim_speed_type;
    /* 0x5BF */ u8 loop_flag;
    /* 0x5C0 */ s16 effect_pattern;
    /* 0x5C2 */ s16 effect_type;
    /* 0x5C4 */ aNPC_feel_effect_c* feel_effect;
    /* 0x5C8 */ f32 feel_effect_counter;
    /* 0x5CC */ s16 shape_bank;
    /* 0x5CE */ s16 tex_bank;
    /* 0x5D0 */ f32 frame_speed;
    /* 0x5D4 */ f32 frame_sub_speed;
    /* 0x5D8 */ xyz_t shadow_pos;
    /* 0x5E4 */ aNPC_draw_tex_data_c draw_tex_data;
} aNPC_draw_info_c;

typedef void (*aNPC_THINK_PROC)(NPC_ACTOR*, GAME_PLAY*, int);

#define aNPC_THINK_INTERRUPT_FRIENDSHIP (1 << 0)
#define aNPC_THINK_INTERRUPT_FATIGUE (1 << 1)
#define aNPC_THINK_INTERRUPT_OBSTACLE (1 << 2)
#define aNPC_THINK_INTERRUPT_ENTRANCE (1 << 3)

enum {
    aNPC_FORCE_CALL_NONE,
    aNPC_FORCE_CALL_REQUEST,
    aNPC_FORCE_CALL_SET,
    aNPC_FORCE_CALL_START,

    aNPC_FORCE_CALL_NUM
};

/* sizeof(aNPC_think_info_c) == 0x18 */
typedef struct npc_think_info_s {
    /* 0x00 */ int idx;
    /* 0x04 */ u8 end_flag;
    /* 0x05 */ u8 force_call_flag;
    /* 0x06 */ u16 force_call_timer;
    /* 0x08 */ int force_call_msg_no;
    /* 0x0C */ u8 force_call_camera_type;
    /* 0x10 */ aNPC_THINK_PROC think_proc;
    /* 0x14 */ u32 interrupt_flags;
} aNPC_think_info_c;

typedef void (*aNPC_SCHEDULE_PROC)(NPC_ACTOR*, GAME_PLAY*, int);

typedef struct npc_schedule_info_s {
    u8 type;
    u8 step;
    mNPS_schedule_c schedule;
    aNPC_SCHEDULE_PROC schedule_proc;
} aNPC_schedule_info_c;

enum {
    aNPC_ACT_OBJ_DEFAULT,
    aNPC_ACT_OBJ_PLAYER,
    aNPC_ACT_OBJ_ANY_NPC,
    aNPC_ACT_OBJ_TARGET_NPC,
    aNPC_ACT_OBJ_4,
    aNPC_ACT_OBJ_5,
    aNPC_ACT_OBJ_BALL,
    aNPC_ACT_OBJ_INSECT,
    aNPC_ACT_OBJ_FISH,

    aNPC_ACT_OBJ_NUM
};

enum {
    aNPC_ACT_TYPE_DEFAULT,
    aNPC_ACT_TYPE_AVOID,
    aNPC_ACT_TYPE_SEARCH,
    aNPC_ACT_TYPE_TO_POINT,

    aNPC_ACT_TYPE_NUM
};

#define aNPC_ACT_NONE 0xFF

enum {
    aNPC_ACTION_PROC_TYPE_INIT,
    aNPC_ACTION_PROC_TYPE_CHG_DATA,
    aNPC_ACTION_PROC_TYPE_MAIN,

    aNPC_ACTION_PROC_TYPE_NUM
};

#ifndef aNPC_NPC2
enum {
    aNPC_ACT_WAIT,
    aNPC_ACT_WALK,
    aNPC_ACT_RUN,
    aNPC_ACT_TURN,
    aNPC_ACT_TURN2,
    aNPC_ACT_CHASE_INSECT,
    aNPC_ACT_CHASE_GYOEI,
    aNPC_ACT_GREETING,
    aNPC_ACT_TALK,
    aNPC_ACT_INTO_HOUSE,
    aNPC_ACT_LEAVE_HOUSE,
    aNPC_ACT_UMB_OPEN,
    aNPC_ACT_UMB_CLOSE,
    aNPC_ACT_ENSOU,
    aNPC_ACT_TALK2,
    aNPC_ACT_REACT_TOOL,
    aNPC_ACT_CLAP,
    aNPC_ACT_TRANS,
    aNPC_ACT_GET,
    aNPC_ACT_CHANGE_CLOTH,
    aNPC_ACT_PITFALL,
    aNPC_ACT_REVIVE,
    aNPC_ACT_SPECIAL,

    aNPC_ACT_NUM
};

enum {
    aNPC_ACTION_TYPE_WAIT,
    aNPC_ACTION_TYPE_WAIT_KI,
    aNPC_ACTION_TYPE_WAIT_DO,
    aNPC_ACTION_TYPE_WAIT_AI,
    aNPC_ACTION_TYPE_WAIT_NEMU,
    aNPC_ACTION_TYPE_WALK,
    aNPC_ACTION_TYPE_WALK_KI,
    aNPC_ACTION_TYPE_WALK_DO,
    aNPC_ACTION_TYPE_WALK_AI,
    aNPC_ACTION_TYPE_RUN,
    aNPC_ACTION_TYPE_RUN_KI,
    aNPC_ACTION_TYPE_RUN_DO,
    aNPC_ACTION_TYPE_RUN_AI,
    aNPC_ACTION_TYPE_TURN,
    aNPC_ACTION_TYPE_TURN2,
    aNPC_ACTION_TYPE_PAL_WAIT,
    aNPC_ACTION_TYPE_GREETING0,
    aNPC_ACTION_TYPE_GREETING1,
    aNPC_ACTION_TYPE_GREETING2,
    aNPC_ACTION_TYPE_GREETING3,
    aNPC_ACTION_TYPE_GURATUKU,
    aNPC_ACTION_TYPE_OTIRU1,
    aNPC_ACTION_TYPE_OTIRU2,
    aNPC_ACTION_TYPE_MOGAKU,
    aNPC_ACTION_TYPE_DERU1,
    aNPC_ACTION_TYPE_DERU2,
    aNPC_ACTION_TYPE_TALK_TURN,
    aNPC_ACTION_TYPE_TALK,
    aNPC_ACTION_TYPE_OPEN_DOOR,
    aNPC_ACTION_TYPE_GO_OUT,
    aNPC_ACTION_TYPE_UMB_OPEN,
    aNPC_ACTION_TYPE_UMB_CLOSE,
    aNPC_ACTION_TYPE_TRANSFER_MOVE,
    aNPC_ACTION_TYPE_TRANSFER,
    aNPC_ACTION_TYPE_TRANSFER_WAIT,
    aNPC_ACTION_TYPE_TRANSFER_F,
    aNPC_ACTION_TYPE_TRANSFER_F_WAIT,
    aNPC_ACTION_TYPE_SEND_MAIL,
    aNPC_ACTION_TYPE_GET_MOVE,
    aNPC_ACTION_TYPE_GET,
    aNPC_ACTION_TYPE_GET_PULL,
    aNPC_ACTION_TYPE_GET_PULL_WAIT,
    aNPC_ACTION_TYPE_GET_PUTAWAY,
    aNPC_ACTION_TYPE_GET_EAT,
    aNPC_ACTION_TYPE_GET_CHANGE,
    aNPC_ACTION_TYPE_GET_RETURN,
    aNPC_ACTION_TYPE_GET_F,
    aNPC_ACTION_TYPE_GET_PULL_F,
    aNPC_ACTION_TYPE_GET_PULL_WAIT_F,
    aNPC_ACTION_TYPE_GET_PUTAWAY_F,
    aNPC_ACTION_TYPE_GET_RETURN_F,
    aNPC_ACTION_TYPE_ESTIMATE_F,
    aNPC_ACTION_TYPE_ENSOU_E,
    aNPC_ACTION_TYPE_WAIT_E,
    aNPC_ACTION_TYPE_GYAFUN1,
    aNPC_ACTION_TYPE_GYAFUN2,
    aNPC_ACTION_TYPE_CLAP,

    aNPC_ACTION_TYPE_NUM
};
#else
enum {
    aNPC_ACT_WAIT,
    aNPC_ACT_WALK,
    aNPC_ACT_RUN,
    aNPC_ACT_TURN,
    aNPC_ACT_TURN2,
    aNPC_ACT_TALK,
    aNPC_ACT_KEITAI_ON,
    aNPC_ACT_KEITAI_OFF,
    aNPC_ACT_ENSOU,
    aNPC_ACT_WAIT_E,
    aNPC_ACT_TRANS,
    aNPC_ACT_GET,
    aNPC_ACT_CONTRACT,
    aNPC_ACT_NOT_CONTRACT,
    aNPC_ACT_NOT_CONTRACT2,
    aNPC_ACT_CHANGE_CLOTH,
    aNPC_ACT_SPECIAL,

    aNPC_ACT_NUM
};

enum {
    aNPC_ACTION_TYPE_WAIT,
    aNPC_ACTION_TYPE_WAIT_KI,
    aNPC_ACTION_TYPE_WAIT_DO,
    aNPC_ACTION_TYPE_WAIT_AI,
    aNPC_ACTION_TYPE_WAIT_NEMU,
    aNPC_ACTION_TYPE_WALK,
    aNPC_ACTION_TYPE_WALK_KI,
    aNPC_ACTION_TYPE_WALK_DO,
    aNPC_ACTION_TYPE_WALK_AI,
    aNPC_ACTION_TYPE_RUN,
    aNPC_ACTION_TYPE_RUN_KI,
    aNPC_ACTION_TYPE_RUN_DO,
    aNPC_ACTION_TYPE_RUN_AI,
    aNPC_ACTION_TYPE_TURN,
    aNPC_ACTION_TYPE_TURN2,
    aNPC_ACTION_TYPE_TALK_TURN,
    aNPC_ACTION_TYPE_TALK,
    aNPC_ACTION_TYPE_KEITAI_ON,
    aNPC_ACTION_TYPE_KEITAI_OFF,
    aNPC_ACTION_TYPE_TRANS_MOVE,
    aNPC_ACTION_TYPE_TRANSFER,
    aNPC_ACTION_TYPE_TRANS_WAIT,
    aNPC_ACTION_TYPE_SEND_MAIL,
    aNPC_ACTION_TYPE_GET_MOVE,
    aNPC_ACTION_TYPE_GET,
    aNPC_ACTION_TYPE_GET_PULL,
    aNPC_ACTION_TYPE_GET_PULL_WAIT,
    aNPC_ACTION_TYPE_GET_PUTAWAY,
    aNPC_ACTION_TYPE_GET_EAT,
    aNPC_ACTION_TYPE_GET_CHANGE,
    aNPC_ACTION_TYPE_GET_RETURN,
    aNPC_ACTION_TYPE_GET_F,
    aNPC_ACTION_TYPE_GET_PULL_F,
    aNPC_ACTION_TYPE_GET_PULL_WAIT_F,
    aNPC_ACTION_TYPE_GET_PUTAWAY_F,
    aNPC_ACTION_TYPE_GET_RETURN_F,
    aNPC_ACTION_TYPE_ESTIMATE_F,
    aNPC_ACTION_TYPE_CONTRACT,
    aNPC_ACTION_TYPE_CONTRACT_PULL,
    aNPC_ACTION_TYPE_CONTRACT_PUTAWAY,
    aNPC_ACTION_TYPE_NOT_CONTRACT,
    aNPC_ACTION_TYPE_ENSOU,
    aNPC_ACTION_TYPE_WAIT_E,

    aNPC_ACTION_TYPE_NUM
};
#endif

typedef void (*aNPC_ACTION_PROC)(NPC_ACTOR*, GAME_PLAY*, int);

#define aNPC_ACTION_END_STEP 0xFF

typedef struct npc_action_s {
    u8 priority;
    u8 idx;
    u8 step;
    u8 type;
    u8 prev_idx;
    u8 prev_step;
    u16 act_timer;
    u8 feel;
    u8 act_obj;
    u16 act_obj_id;
    s16 move_x;
    s16 move_z;
    aNPC_ACTION_PROC act_proc;
} aNPC_action_c;

#define aNPC_REQUEST_ARG_NUM 6

typedef struct npc_request_s {
    u8 act_priority;
    u8 act_idx;
    u8 act_type;
    u16 act_args[aNPC_REQUEST_ARG_NUM];
    u8 umb_flag;
    u8 _11;
    u8 head_priority;
    u8 head_type;
    ACTOR* head_target;
    xyz_t head_pos;
} aNPC_request_c;

#define aNPC_COND_DEMO_SKIP_MOVE_RANGE_CHECK (1 << 0) /* 0x0001 */
#define aNPC_COND_DEMO_SKIP_MOVE_CIRCLE_REV (1 << 1)  /* 0x0002 */
#define aNPC_COND_DEMO_SKIP_MOVE_Y (1 << 2)           /* 0x0004 */
#define aNPC_COND_DEMO_SKIP_OBJ_COL_CHECK (1 << 3)    /* 0x0008 */
#define aNPC_COND_DEMO_SKIP_BGCHECK (1 << 4)          /* 0x0010 */
#define aNPC_COND_DEMO_SKIP_FORWARD_CHECK (1 << 5)    /* 0x0020 */
#define aNPC_COND_DEMO_SKIP_ITEM (1 << 6)             /* 0x0040 */
#define aNPC_COND_DEMO_SKIP_TALK_CHECK (1 << 7)       /* 0x0080 */
#define aNPC_COND_DEMO_SKIP_HEAD_LOOKAT (1 << 8)      /* 0x0100 */
#define aNPC_COND_DEMO_SKIP_ENTRANCE_CHECK (1 << 9)   /* 0x0200 */
#define aNPC_COND_DEMO_SKIP_KUTIPAKU (1 << 10)        /* 0x0400 */
#define aNPC_COND_DEMO_SKIP_FOOTSTEPS (1 << 11)       /* 0x0800 */
#define aNPC_COND_DEMO_SKIP_FEEL_CHECK (1 << 12)      /* 0x1000 */
#define aNPC_COND_DEMO_SKIP_LOVE_CHECK (1 << 13)      /* 0x2000 */
#define aNPC_COND_DEMO_SKIP_FOOTSTEPS_VFX (1 << 14)   /* 0x4000 */
#define aNPC_COND_DEMO_SKIP_UZAI_CHECK (1 << 15)      /* 0x8000 */

enum {
    aNPC_ENTRANCE_TYPE_NONE,   // not near any entrance
    aNPC_ENTRANCE_TYPE_NEARBY, // near a house entrance
    aNPC_ENTRANCE_TYPE_AT,     // at a house entrance

    aNPC_ENTRANCE_TYPE_NUM
};

typedef struct npc_condition_s {
    u8 hide_flg;
    u8 hide_request;
    u8 action;
    u8 talk_condition;
    u8 greeting_flag;
    u8 entrance_flag;
    u16 fatigue;
    int feel_tim;
    int _0C;
    u32 demo_flg;
    u32 talk_demo_flg_save;
    u32 trans_demo_flg_save;
    u8 appear_flag;
    u8 appear_rotation;
    u8 pitfall_flag;
    u32 actor_state_save;
    int _24;
    int _28;
    int _2C;
    s8* friendship;
    int over_friendship;
    mActor_name_t* under_fg_p;
    int ut_x;
    int ut_z;
} aNPC_condition_info_c;

typedef struct npc_uzai_s {
    int step;
    u8 tool;
    u8 flag;
    u8 cross;
} aNPC_uzai_c;

enum {
    aNPC_ITEM_TYPE_NONE,
    aNPC_ITEM_TYPE_UMBRELLA,
    aNPC_ITEM_TYPE_KEITAI,
    aNPC_ITEM_TYPE_PUTAWAY,
    aNPC_ITEM_TYPE_LEFT_HAND,

    aNPC_ITEM_TYPE_NUM
};

typedef struct npc_hand_s {
    u8 item_type;
    u8 requested_item_type;
    mActor_name_t item;
    u8 after_mode;
    u8 present_flag;
    u8 umbrella_disabled_flag;
    u8 umbrella_type;
    ACTOR* item_actor_p;
    ACTOR* prev_item_actor_p;
    xyz_t pos;
} aNPC_hand_c;

enum {
    aNPC_HEAD_TARGET_NONE,
    aNPC_HEAD_TARGET_ACTOR,
    aNPC_HEAD_TARGET_POS,

    aNPC_HEAD_TARGET_NUM
};

typedef struct npc_head_s {
    s16 angle_x;
    s16 angle_y;
    s16 angle_add_x;
    s16 angle_add_y;
    s16 _08;
    u8 lock_flag;
    u8 target_type;
    ACTOR* target;
    xyz_t pos;
} aNPC_head_c;

enum {
    aNPC_FOOT_LEFT,
    aNPC_FOOT_RIGHT,

    aNPC_FOOT_NUM
};

typedef struct npc_speed_s {
    f32 max_speed;
    f32 acceleration;
    f32 deceleration;
} aNPC_spd_c;

enum {
    aNPC_MOVE_RANGE_TYPE_BLOCK,
    aNPC_MOVE_RANGE_TYPE_CIRCLE,
#if VERSION >= VER_GAFU01_00
    aNPC_MOVE_RANGE_TYPE_SQUARE,
#endif

    aNPC_MOVE_RANGE_TYPE_NUM
};

enum {
    aNPC_FRIENDSHIP_NORMAL, // default
    aNPC_FRIENDSHIP_AVOID,  // avoid player (hate player)
    aNPC_FRIENDSHIP_SEARCH, // search for player (love player)

    aNPC_FRIENDSHIP_NUM
};

typedef struct npc_movement_s {
    aNPC_spd_c speed;
    f32 dst_pos_x;
    f32 dst_pos_z;
    f32 avoid_pos_x;
    f32 avoid_pos_z;
    s16 move_timer;
    u8 avoid_direction;
    u8 range_type;
    f32 range_center_x;
    f32 range_center_z;
    f32 range_radius;
    s16 mv_angl;
    s16 mv_add_angl;
    f32 arrival_area_radius;
    ACTOR* target;
    s8 movement_ut_x;
    s8 movement_ut_z;
    s16 body_angle;
    u8 override_body_angle_flag;
    u8 demo_move_timer;
} aNPC_movement_c;

enum {
    aNPC_BG_CHECK_TYPE_NONE,        // no collision
    aNPC_BG_CHECK_TYPE_ONLY_GROUND, // only ground collision
    aNPC_BG_CHECK_TYPE_NORMAL,      // standard
    aNPC_BG_CHECK_TYPE_RANGE,       // standard plus range

    aNPC_BG_CHECK_TYPE_NUM
};

typedef struct npc_collision_s {
    ClObjPipe_c pipe;
    f32 BGcheck_radius;
    u8 collision_flag;
    u8 check_kind;
    u8 turn_flag;
    u16 _24;
    s16 turn_angle;
    f32 bg_rev_add;
} aNPC_collision_c;

enum {
    aNPC_TALK_TYPE_NONE,
    aNPC_TALK_TYPE_START,
    aNPC_TALK_TYPE_CONTINUE,

    aNPC_TALK_TYPE_NUM
};

enum {
    aNPC_TALK_TURN_NORMAL,
    aNPC_TALK_TURN_HEAD,
    aNPC_TALK_TURN_NONE,

    aNPC_TALK_TURN_NUM
};

enum {
    aNPC_MANPU_CODE_RESET_KEKE = 0xFD,
    aNPC_MANPU_CODE_RESET_SIT = 0xFE,
    aNPC_MANPU_CODE_RESET = 0xFF,
    aNPC_MANPU_CODE_NONE = 0,
};

typedef struct npc_actor_talk_info_s {
    aNPC_TALK_REQUEST_PROC talk_request_proc;
    aNPC_TALK_INIT_PROC talk_init_proc;
    aNPC_TALK_END_CHECK_PROC talk_end_check_proc;
    u8 type;
    u8 default_act;
    u8 demo_code;
    u8 turn;
    s16 default_animation;
    s16 default_turn_animation;
    s16 melody_inst;
    s16 npc_voice_id;
    u8 feel;
    u8 memory;
    u8 kutipaku_timer; // frames of mouth movement animation
} aNPC_talk_info_c;

typedef struct npc_accessory_s {
    s16 type;
    s16 pos_joint_idx; // might be better suited as base_joint_idx?
    ACTOR* accessory;
} aNPC_accessory_c;

/* Used for think, schedule, action, & talk */
typedef void (*aNPC_PROC)(NPC_ACTOR* npc_actorx, GAME_PLAY* play, int schedule_idx);
typedef void (*aNPC_SUB_PROC)(NPC_ACTOR* npc_actorx, GAME_PLAY* play);

enum {
    aNPC_SCHEDULE_TYPE_FIELD,
    aNPC_SCHEDULE_TYPE_IN_HOUSE,
    aNPC_SCHEDULE_TYPE_SLEEP,
    aNPC_SCHEDULE_TYPE_STAND,
    aNPC_SCHEDULE_TYPE_WANDER,
    aNPC_SCHEDULE_TYPE_WALK_WANDER,
    aNPC_SCHEDULE_TYPE_SPECIAL,

    aNPC_SCHEDULE_TYPE_NUM
};

#define aNPC_SCHEDULE_NONE 0xFF

enum {
    aNPC_SCHEDULE_PROC_INIT,
    aNPC_SCHEDULE_PROC_MAIN,

    aNPC_SCHEDULE_PROC_NUM
};

struct npc_actor_s {
    ACTOR actor_class;
    s_xyz _174;
    NpcActorInfo_c npc_info;
    aNPC_draw_info_c draw;
    aNPC_think_info_c think;
    aNPC_schedule_info_c schedule;
    aNPC_action_c action;
    aNPC_request_c request;
    f32 eye_y;
    aNPC_condition_info_c condition_info;
    aNPC_uzai_c uzai;
    aNPC_hand_c left_hand;
    aNPC_hand_c right_hand;
    aNPC_head_c head;
    xyz_t feet[aNPC_FOOT_NUM];
    mActor_proc move_proc;
    mActor_proc draw_proc;
    ACTOR* palActor;
    int palActorIgnoreTimer;
    aNPC_movement_c movement;
    aNPC_collision_c collision;
    aNPC_talk_info_c talk_info;
    aNPC_accessory_c accessory;
    int act_react_tool_timer;
    int _98C;
    int _990;
};

typedef struct {
    aNPC_se_data_c* lfoot_data;
    aNPC_se_data_c* rfoot_data;
    int other_se_type;
    aNPC_other_se_data_c* other_se_data;
} aNPC_se_data_table_c;

typedef struct {
    cKF_Animation_R_c anim;
    f32 start_frame;
    f32 end_frame;
    int mode;
    f32 morph_counter;
    u8* eye_seq_p;
    s16 eye_seq_type;
    s16 eye_seq_stop_frame;
    u8* mouth_seq_p;
    s16 mouth_seq_type;
    s16 mouth_seq_stop_frame;
    s16 feel_effect_set_frame;
    s16 feel_effect_type;
    aNPC_feel_effect_c* feel_effect;
    aNPC_se_data_table_c* se_data_table;
} aNPC_Animation_c;

typedef struct {
    aNPC_Animation_c* anim_p;
    int anim_idx;
} aNPC_anim_info_c;

#define aNPC_DEMO_GIVE_ITEM(item, mode, present)       \
    mDemo_Set_OrderValue(mDemo_ORDER_NPC1, 0, (item)); \
    mDemo_Set_OrderValue(mDemo_ORDER_NPC1, 1, (mode)); \
    mDemo_Set_OrderValue(mDemo_ORDER_NPC1, 2, (present))

extern ACTOR_PROFILE Npc_Profile;

#ifdef __cplusplus
}
#endif

#endif
