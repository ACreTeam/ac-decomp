#ifndef AC_MY_ROOM_H
#define AC_MY_ROOM_H

#include "types.h"
#include "m_actor.h"
#include "ac_furniture.h"
#include "m_room_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aMR_MAX_UNIT 8
#define aMR_HANIWA_ON_TABLE_NUM 14
#define aMR_GOKI_MAX 3
#define aMR_FIT_FTR_MAX 4
#define aMR_RSV_FTR_NUM 3

#define aMR_NO_FTR_ID 200
#define aMR_NO_FTR_ID2 201

#define aMR_JUDGE_MAX_FTR -1
#define aMR_JUDGE_CANT_PLACE_FTR -2
#define aMR_JUDGE_OTHER_ROOM -3

typedef struct my_room_actor_s MY_ROOM_ACTOR;

enum {
    aMR_CONTACT_LEFT,
    aMR_CONTACT_RIGHT,
    aMR_CONTACT_CENTER,

    aMR_CONTACT_NUM
};

enum {
    aMR_CONTACT_DIR_BACK,
    aMR_CONTACT_DIR_RIGHT,
    aMR_CONTACT_DIR_FRONT,
    aMR_CONTACT_DIR_LEFT,

    aMR_CONTACT_DIR_NUM
};

enum {
    aMR_FRIEND_ALL,
    aMR_FRIEND_ON,
    aMR_FRIEND_OFF,

    aMR_FRIEND_NUM
};

enum {
    aMR_DIRECT_UP,
    aMR_DIRECT_LEFT,
    aMR_DIRECT_DOWN,
    aMR_DIRECT_RIGHT,

    aMR_DIRECT_NUM
};

typedef struct my_room_contact_s {
    /* 0x00 */ int contact_flag;
    /* 0x04 */ int ftrID;
    /* 0x08 */ int direction;
    /* 0x0C */ int contact_side;
    /* 0x10 */ f32 contact_percent;
    /* 0x14 */ f32* normal_p;
    /* 0x18 */ f32 contact_edge_start[2];
    /* 0x20 */ f32 contact_edge_end[2];
    /* 0x28 */ int contact_direction;
} aMR_contact_info_c;

typedef struct my_room_clock_info_s {
    /* 0x00 */ int tick0;     /* set on frame 15 */
    /* 0x04 */ int tick1;     /* set on frame 45 */
    /* 0x08 */ int tick_stop; /* set on frame 0 */
    /* 0x0C */ int frame;     /* 0-119 */
} aMR_clock_info_c;

typedef int (*aMR_JUDGE_BREED_NEW_FTR_PROC)(GAME* game, u16 ftr_no, int* ut_x, int* ut_z, u16* rotation,
                                            int* square_offset, int* layer);
typedef mActor_name_t (*aMR_SEARCH_PICKUP_FURNITURE_PROC)(GAME* game);
typedef void (*aMR_FURNITURE2ITEMBAG_PROC)(GAME* game);
typedef int (*aMR_JUDGE_PLAYER_ACTION_PROC)(xyz_t* wpos0, xyz_t* wpos1, int ftr_actor_idx);
typedef void (*aMR_PLAYER_MOVE_FURNITURE_PROC)(int ftr_actor_idx, const xyz_t* wpos);
typedef int (*aMR_FTR_ID_2_WPOS_PROC)(xyz_t* wpos, int ftr_id);
typedef int (*aMR_UNIT_NUM_2_FTR_ITEMNO_FTRID_PROC)(mActor_name_t* ftr_item_no, int* ftr_id, int ut_x, int ut_z,
                                                    int layer);
typedef void (*aMR_FTR_ID_2_EXTINGUISH_FURNITURE_PROC)(int ftr_id);
typedef void (*aMR_REDMA_FTR_BANK_PROC)(void);
typedef int (*aMR_RESERVE_FURNITURE_PROC)(GAME* game, u16 ftr_no, int judge_res, int ut_x, int ut_z, u16 rotation,
                                          int square_offset, int layer);
typedef int (*aMR_COUNT_FRIEND_FURNITURE_PROC)(FTR_ACTOR* ftr_actor, u8 switch_on);
typedef int (*aMR_JUDGE_PLACE_2ND_LAYER_PROC)(int ut_x, int ut_z);
typedef void (*aMR_OPEN_CLOSE_COMMON_MOVE_PROC)(FTR_ACTOR* ftr_actor, ACTOR* actor, GAME* game, f32 start_frame,
                                                f32 end_frame);
typedef int (*aMR_GET_BED_ACTION_PROC)(ACTOR* actorx, int bed_move_dir);
typedef void (*aMR_MINI_DISK_COMMON_MOVE_PROC)(FTR_ACTOR* ftr_actor, ACTOR* my_room_actorx, GAME* game, f32 start_frame,
                                               f32 end_frame);
typedef int (*aMR_SET_LEAF_PROC)(const xyz_t* pos, f32 scale);
typedef int (*aMR_FTR2LEAF_PROC)(void);
typedef void (*aMR_LEAF_START_POS_PROC)(xyz_t* pos);
typedef int (*aMR_PICKUP_FTR_LAYER_PROC)(void);
typedef void (*aMR_LEAF_PICKUPED_PROC)(void);
typedef void (*aMR_FAMICOM_EMU_COMMON_MOVE_PROC)(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, int rom_no,
                                                 int agb_rom_no);
typedef u8* (*aMR_FTR_NO_2_BANK_ADDRESS_PROC)(u16 ftr_no);
typedef void (*aMR_CALL_SIT_DOWN_ONGEN_POS_SE_PROC)(const xyz_t* pos);
typedef void (*aMR_SOUND_MELODY_PROC)(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, int idx);
typedef int (*aMR_CHECK_DANNA_KILL_PROC)(xyz_t* pos);

typedef struct my_room_clip_s {
    /* 0x00 */ ACTOR* my_room_actor_p;
    /* 0x04 */ aMR_JUDGE_BREED_NEW_FTR_PROC judge_breed_new_ftr_proc;
    /* 0x08 */ aMR_SEARCH_PICKUP_FURNITURE_PROC search_pickup_ftr_proc;
    /* 0x0C */ aMR_FURNITURE2ITEMBAG_PROC ftr2itemBag_proc;
    /* 0x10 */ aMR_JUDGE_PLAYER_ACTION_PROC judge_player_action_proc;
    /* 0x14 */ aMR_PLAYER_MOVE_FURNITURE_PROC player_move_ftr_proc;
    /* 0x18 */ aMR_FTR_ID_2_WPOS_PROC ftrId2wpos_proc;
    /* 0x1C */ aMR_UNIT_NUM_2_FTR_ITEMNO_FTRID_PROC unitNum2ftrItemNoftrId_proc;
    /* 0x20 */ aMR_FTR_ID_2_EXTINGUISH_FURNITURE_PROC ftrId2extinguishFtr_proc;
    /* 0x24 */ aMR_REDMA_FTR_BANK_PROC redma_ftr_bank_proc;
    /* 0x28 */ aMR_RESERVE_FURNITURE_PROC reserve_ftr_proc;
    /* 0x2C */ aMR_COUNT_FRIEND_FURNITURE_PROC count_friend_ftr_proc;
    /* 0x30 */ aMR_JUDGE_PLACE_2ND_LAYER_PROC judge_place_2nd_layer_proc;
    /* 0x34 */ aMR_OPEN_CLOSE_COMMON_MOVE_PROC open_close_common_move_proc;
    /* 0x38 */ aMR_GET_BED_ACTION_PROC get_bed_action_proc;
    /* 0x3C */ aMR_MINI_DISK_COMMON_MOVE_PROC mini_disk_common_move_proc;
    /* 0x40 */ aMR_SET_LEAF_PROC set_leaf_proc;
    /* 0x44 */ aMR_FTR2LEAF_PROC ftr2leaf_proc;
    /* 0x48 */ aMR_LEAF_START_POS_PROC leaf_start_pos_proc;
    /* 0x4C */ aMR_PICKUP_FTR_LAYER_PROC pickup_ftr_layer_proc;
    /* 0x50 */ aMR_LEAF_PICKUPED_PROC leaf_pickuped_proc;
    /* 0x54 */ aMR_FAMICOM_EMU_COMMON_MOVE_PROC famicom_emu_common_move_proc;
    /* 0x58 */ aMR_FTR_NO_2_BANK_ADDRESS_PROC ftrNo2bankAddress_proc;
    /* 0x5C */ aMR_CALL_SIT_DOWN_ONGEN_POS_SE_PROC call_sit_down_ongen_pos_se_proc;
    /* 0x60 */ aMR_clock_info_c* clock_info_p; /* used for playing the clock tick? sfx */
    /* 0x64 */ aMR_SOUND_MELODY_PROC sound_melody_proc;
    /* 0x68 */ aMR_CHECK_DANNA_KILL_PROC check_danna_kill_proc;
} aMR_Clip_c;

typedef struct room_leaf_s {
    /* 0x00 */ int exist_flag;
    /* 0x04 */ xyz_t pos;
    /* 0x10 */ f32 scale;
} aMR_leaf_info_c;

typedef struct room_pickup_s {
    /* 0x00 */ int pickup_flag;
    /* 0x04 */ int ftrID;
    /* 0x08 */ xyz_t leaf_pos;
    /* 0x14 */ int picking_up_flag;
    /* 0x18 */ s16 layer;
    /* 0x1A */ s16 dust_effect_timer;
    /* 0x1C */ s16 icon;
} aMR_pickup_info_c;

typedef struct room_rsv_ftr_s {
    /* 0x00 */ u8 exist_flag;
    /* 0x02 */ u16 ftr_name;
    /* 0x04 */ int ofs;
    /* 0x08 */ u16 angle_idx;
    /* 0x0C */ int free_no;
    /* 0x10 */ s16 layer;
    /* 0x12 */ s16 frames;
    /* 0x14 */ s16 initial_frames_num;
    /* 0x18 */ int ut_x;
    /* 0x1C */ int ut_z;
} aMR_rsv_ftr_c;

typedef struct room_bgm_s {
    /* 0x00 */ int md_no;
    /* 0x04 */ int last_md_no;
    /* 0x08 */ u8 reserve_flag;
    /* 0x0A */ s16 timer;
    /* 0x0C */ FTR_ACTOR* reserved_ftr_actor;
    /* 0x10 */ FTR_ACTOR* active_ftr_actor;
    /* 0x14 */ int active_flag;
} aMR_bgm_info_c;

typedef struct room_info_s {
    /* 0x00 */ int shop_flag;
    /* 0x04 */ int owner_flag;
} aMR_room_info_c;

typedef struct emu_info_s {
    /* 0x00 */ int request_flag;
    /* 0x04 */ int rom_no;
    /* 0x08 */ int agb_rom_no;
    /* 0x0C */ int explaination_given_flag;
    /* 0x10 */ int _10;
    /* 0x14 */ int card_famicom_count;
    /* 0x18 */ int memory_game_select;
    /* 0x1C */ char* famicom_names_p;
    /* 0x20 */ s16 save_msg_timer;
    /* 0x22 */ s16 external_rom;
#if VERSION == VER_GAFP01_00
    /* 0x24 */ u8 emu_save_msg_ready;
#endif
} aMR_emu_info_c;

typedef void (*aMR_GOKI_CT_PROC)(ACTOR*, GAME*);

typedef struct room_fit_ftr_s {
    /* 0x00 */ int exist_flag;
    /* 0x04 */ xyz_t pos;
    /* 0x10 */ int ftr_ID;
    /* 0x14 */ mActor_name_t item_no;
    /* 0x16 */ s16 angle_y;
    /* 0x18 */ xyz_t ut_pos;
} aMR_fit_ftr_c;

typedef struct room_parent_ftr_s {
    /* 0x00 */ int ftrID;
    /* 0x04 */ s16 angle_y;
    /* 0x08 */ aMR_fit_ftr_c fit_ftr_table[aMR_FIT_FTR_MAX];
} aMR_parent_ftr_c;

struct my_room_actor_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ s16 state;
    /* 0x178 */ aMR_contact_info_c contact0;
    /* 0x1A4 */ aMR_contact_info_c contact1;
    /* 0x1D0 */ u8 allow_rotation_flag;
    /* 0x1D4 */ int _1D4;
    /* 0x1D8 */ cKF_SkeletonInfo_R_c keyframe;
    /* 0x248 */ s_xyz joint[1];
    /* 0x24E */ s_xyz morph[1];
    /* 0x254 */ u8 _254[132];
    /* 0x2D8 */ s16 move_angle;
    /* 0x2DC */ xyz_t nice_pos;
    /* 0x2E8 */ aMR_Clip_c clip;
    /* 0x354 */ s16 sit_timer;
    /* 0x356 */ s16 bed_timer;
    /* 0x358 */ aMR_leaf_info_c leaf_info;
    /* 0x36C */ aMR_pickup_info_c pickup_info;
    /* 0x38C */ aMR_rsv_ftr_c rsv_ftr[3];
    /* 0x3EC */ s16 msg_type;
    /* 0x3EE */ s16 requested_msg_type;
    /* 0x3F0 */ int emu_ftrID;
    /* 0x3F4 */ int _3F4;
    /* 0x3F8 */ s16 demo_flag;
    /* 0x3FA */ s16 demo_ftrID;
    /* 0x3FC */ int _3FC;
    /* 0x400 */ s16 pull_timer;
    /* 0x402 */ s16 push_timer;
    /* 0x404 */ s16 msg_timer;
    /* 0x406 */ s16 head_direction;
    /* 0x408 */ s16 bed_ftr_actor_idx;
    /* 0x40A */ s16 pull_bubu;
    /* 0x40C */ s16 push_bubu;
    /* 0x40E */ s16 keep_push_flag;
    /* 0x410 */ s16 keep_pull_flag;
    /* 0x414 */ xyz_t pull_target_pos0;
    /* 0x420 */ xyz_t pull_target_pos1;
    /* 0x42C */ int haniwa_on_table[aMR_HANIWA_ON_TABLE_NUM];
    /* 0x464 */ aMR_bgm_info_c bgm_info;
    /* 0x47C */ aMR_room_info_c room_info;
    /* 0x484 */ aMR_emu_info_c emu_info;
    /* 0x4A8 */ aMR_clock_info_c clock_info;
    /* 0x4B8 */ aMR_GOKI_CT_PROC goki_ct_proc;
    /* 0x4BC */ int _4BC[3];
    /* 0x4C8 */ int weight;
    /* 0x4CC */ u8 melody[8];
    /* 0x4D4 */ int _4D4;
    /* 0x4D8 */ int _4D8;
    /* 0x4DC */ int bank_count0;
    /* 0x4E0 */ int bank_count1;
    /* 0x4E4 */ int request_player_surprise;
    /* 0x4E8 */ s16 player_surprise_angle_y;
    /* 0x4EA */ s16 switch_timer;
    /* 0x4EC */ s16 force_open_demo_flag;
    /* 0x4F0 */ int _4F0;
    /* 0x4F4 */ int _4F4;
    /* 0x4F8 */ int room_msg_flag;
    /* 0x4FC */ int haniwa_step_idx;
    /* 0x500 */ aMR_parent_ftr_c parent_ftr;
    /* 0x598 */ u32 music_box[2];
    /* 0x5A0 */ int scene;
    /* 0x5A4 */ int _5A4;
    /* 0x5A8 */ int throw_item_lock_flag;
    /* 0x5AC */ void* bank0_p;
    /* 0x5B0 */ u32 agb_game_size;
    /* 0x5B4 */ void* famicom_agb_image_p;
    /* 0x5B8 */ s16 agb_connect_tries;
#if VERSION != VER_GAFP01_00
    /* 0x5BC */ int _5BC;
#endif
};

extern ACTOR_PROFILE My_Room_Profile;

extern int aMR_CorrespondFurniture(mActor_name_t ftr0, mActor_name_t ftr1);
extern int aMR_GetFurnitureUnit(mActor_name_t ftr);
extern mActor_name_t aMR_FurnitureFg_to_FurnitureFgWithDirect(mActor_name_t ftr, int direct);
extern void aMR_SameFurnitureSwitchOFF(u16 ftr_name);
extern aMR_contact_info_c* aMR_GetContactInfoLayer1(void);
extern FTR_ACTOR* aMR_GetParentFactor(FTR_ACTOR* ftr_actor, ACTOR* my_room_actorx);
extern s16 aMR_GetParentAngleOffset(FTR_ACTOR* ftr_actor, ACTOR* my_room_actorx);
extern void aMR_SetSurprise(ACTOR* my_room_actor, s16 rot);
extern void aMR_RadioCommonMove(FTR_ACTOR* ftr_actor, ACTOR* my_room_actorx);
extern void aMR_SaveWaltzTempo2(void);
extern u8 aMR_GetAlphaEdge(u16 ftr_name);
extern int aMR_DrawDolphinMode(u16 ftr_name);
extern Gfx* aMR_IconNo2Gfx1(int icon_no);
extern Gfx* aMR_IconNo2Gfx2(int icon_no);
extern int aMR_RadioBgmNow(void);
extern void aMR_ThrowItem_FurnitureLock(void);
extern void aMR_ThrowItem_FurnitureUnlock(void);

#ifdef __cplusplus
}
#endif

#endif
