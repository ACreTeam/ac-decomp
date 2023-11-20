#ifndef M_PLAYER_H
#define M_PLAYER_H

#include "types.h"
#include "m_actor.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct player_actor_s PLAYER_ACTOR;

#define mPlayer_FORCE_POSITION_ANGLE_NONE 0
// where is (1 << 0) ??
#define mPlayer_FORCE_POSITION_ANGLE_POSX (1 << 1)
#define mPlayer_FORCE_POSITION_ANGLE_POSY (1 << 2)
#define mPlayer_FORCE_POSITION_ANGLE_POSZ (1 << 3)
#define mPlayer_FORCE_POSITION_ANGLE_ROTX (1 << 4)
#define mPlayer_FORCE_POSITION_ANGLE_ROTY (1 << 5)
#define mPlayer_FORCE_POSITION_ANGLE_ROTZ (1 << 6)

enum {
  mPlayer_ADDRESSABLE_TRUE,
  mPlayer_ADDRESSABLE_FALSE_MOVEMENT,
  mPlayer_ADDRESSABLE_FALSE_TALKING,
  mPlayer_ADDRESSABLE_FALSE_USING_TOOL,

  mPlayer_ADDRESSABLE_NUM
};

enum {
  mPlayer_INDEX_DMA,
  mPlayer_INDEX_INTRO,
  mPlayer_INDEX_REFUSE,
  mPlayer_INDEX_REFUSE_PICKUP,
  mPlayer_INDEX_RETURN_DEMO,
  mPlayer_INDEX_RETURN_OUTDOOR,
  mPlayer_INDEX_RETURN_OUTDOOR2,
  mPlayer_INDEX_WAIT,
  mPlayer_INDEX_WALK,
  mPlayer_INDEX_RUN,
  mPlayer_INDEX_DASH,
  mPlayer_INDEX_TUMBLE,
  mPlayer_INDEX_TUMBLE_GETUP,
  mPlayer_INDEX_TURN_DASH,
  mPlayer_INDEX_FALL,
  mPlayer_INDEX_WADE,
  mPlayer_INDEX_DOOR,
  mPlayer_INDEX_OUTDOOR,
  mPlayer_INDEX_INVADE,
  mPlayer_INDEX_HOLD,
  mPlayer_INDEX_PUSH,
  mPlayer_INDEX_PULL,
  mPlayer_INDEX_ROTATE_FURNITURE,
  mPlayer_INDEX_OPEN_FURNITURE,
  mPlayer_INDEX_WAIT_OPEN_FURNITURE,
  mPlayer_INDEX_CLOSE_FURNITURE,
  mPlayer_INDEX_LIE_BED,
  mPlayer_INDEX_WAIT_BED,
  mPlayer_INDEX_ROLL_BED,
  mPlayer_INDEX_STANDUP_BED,
  mPlayer_INDEX_PICKUP,
  mPlayer_INDEX_PICKUP_JUMP,
  mPlayer_INDEX_PICKUP_FURNITURE,
  mPlayer_INDEX_PICKUP_EXCHANGE,
  mPlayer_INDEX_SITDOWN,
  mPlayer_INDEX_SITDOWN_WAIT,
  mPlayer_INDEX_STANDUP,
  mPlayer_INDEX_SWING_AXE,
  mPlayer_INDEX_AIR_AXE,
  mPlayer_INDEX_REFLECT_AXE,
  mPlayer_INDEX_BROKEN_AXE,
  mPlayer_INDEX_SLIP_NET,
  mPlayer_INDEX_READY_NET,
  mPlayer_INDEX_READY_WALK_NET,
  mPlayer_INDEX_SWING_NET,
  mPlayer_INDEX_PULL_NET,
  mPlayer_INDEX_STOP_NET,
  mPlayer_INDEX_NOTICE_NET,
  mPlayer_INDEX_PUTAWAY_NET,
  mPlayer_INDEX_READY_ROD,
  mPlayer_INDEX_CAST_ROD,
  mPlayer_INDEX_AIR_ROD,
  mPlayer_INDEX_RELAX_ROD,
  mPlayer_INDEX_COLLECT_ROD,
  mPlayer_INDEX_VIB_ROD,
  mPlayer_INDEX_FLY_ROD,
  mPlayer_INDEX_NOTICE_ROD,
  mPlayer_INDEX_PUTAWAY_ROD,
  mPlayer_INDEX_DIG_SCOOP,
  mPlayer_INDEX_FILL_SCOOP,
  mPlayer_INDEX_REFLECT_SCOOP,
  mPlayer_INDEX_AIR_SCOOP,
  mPlayer_INDEX_GET_SCOOP,
  mPlayer_INDEX_PUTAWAY_SCOOP,
  mPlayer_INDEX_PUTIN_SCOOP,
  mPlayer_INDEX_TALK,
  mPlayer_INDEX_RECIEVE_WAIT,
  mPlayer_INDEX_RECIEVE_STRETCH,
  mPlayer_INDEX_RECIEVE,
  mPlayer_INDEX_RECIEVE_PUTAWAY,
  mPlayer_INDEX_GIVE,
  mPlayer_INDEX_GIVE_WAIT,
  mPlayer_INDEX_TAKEOUT_ITEM,
  mPlayer_INDEX_PUTIN_ITEM,
  mPlayer_INDEX_DEMO_WAIT,
  mPlayer_INDEX_DEMO_WALK,
  mPlayer_INDEX_DEMO_GETON_TRAIN,
  mPlayer_INDEX_DEMO_GETON_TRAIN_WAIT,
  mPlayer_INDEX_DEMO_GETOFF_TRAIN,
  mPlayer_INDEX_DEMO_STANDING_TRAIN,
  mPlayer_INDEX_DEMO_WADE,
  mPlayer_INDEX_HIDE,
  mPlayer_INDEX_GROUNDHOG,
  mPlayer_INDEX_RELEASE_CREATURE,
  mPlayer_INDEX_WASH_CAR,
  mPlayer_INDEX_TIRED,
  mPlayer_INDEX_ROTATE_OCTAGON,
  mPlayer_INDEX_THROW_MONEY,
  mPlayer_INDEX_PRAY,
  mPlayer_INDEX_SHAKE_TREE,
  mPlayer_INDEX_MAIL_JUMP,
  mPlayer_INDEX_MAIL_LAND,
  mPlayer_INDEX_READY_PITFALL,
  mPlayer_INDEX_FALL_PITFALL,
  mPlayer_INDEX_STRUGGLE_PITFALL,
  mPlayer_INDEX_CLIMBUP_PITFALL,
  mPlayer_INDEX_STUNG_BEE,
  mPlayer_INDEX_NOTICE_BEE,
  mPlayer_INDEX_REMOVE_GRASS,
  mPlayer_INDEX_SHOCK,
  mPlayer_INDEX_KNOCK_DOOR,
  mPlayer_INDEX_CHANGE_CLOTH,
  mPlayer_INDEX_PUSH_SNOWBALL,
  mPlayer_INDEX_ROTATE_UMBRELLA,
  mPlayer_INDEX_WADE_SNOWBALL,
  mPlayer_INDEX_COMPLETE_PAYMENT,
  mPlayer_INDEX_FAIL_EMU,
  mPlayer_INDEX_STUNG_MOSQUITO,
  mPlayer_INDEX_NOTICE_MOSQUITO,
  mPlayer_INDEX_SWING_FAN,
  mPlayer_INDEX_SWITCH_ON_LIGHTHOUSE,
  mPlayer_INDEX_RADIO_EXERCISE,
  mPlayer_INDEX_DEMO_GETON_BOAT,
  mPlayer_INDEX_DEMO_GETON_BOAT_SITDOWN,
  mPlayer_INDEX_DEMO_GETON_BOAT_WAIT,
  mPlayer_INDEX_DEMO_GETON_BOAT_WADE,
  mPlayer_INDEX_DEMO_GETOFF_BOAT_STANDUP,
  mPlayer_INDEX_DEMO_GETOFF_BOAT,
  mPlayer_INDEX_DEMO_GET_GOLDEN_ITEM,
  mPlayer_INDEX_DEMO_GET_GOLDEN_ITEM2,
  mPlayer_INDEX_DEMO_GET_GOLDEN_AXE_WAIT
};

/* sizeof(struct player_actor_s) == 0x13A8 */
struct player_actor_s {
  /* 0x0000 */ ACTOR actor_class;
  /* 0x0174 */ u8 tmp0174[0x1270 - 0x0174];
  /* 0x1270 */ int (*request_main_invade_all_proc)(GAME*, int);
  /* 0x1274 */ int (*request_main_refuse_all_proc)(GAME*, int);
  /* 0x1278 */ int (*request_main_return_demo_all_proc)(GAME*, int, f32, int);
  /* 0x127C */ int (*request_main_wait_all_proc)(GAME*, f32, int, int);
  /* 0x1280 */ int (*request_main_talk_all_proc)(GAME*, ACTOR*, int, f32, int, int);
  /* 0x1284 */ int (*request_main_hold_all_proc)(GAME*, int, int, const xyz_t*, f32, int, int);
  /* 0x1288 */ int (*request_main_recieve_wait_all_proc)(GAME*, ACTOR*, int, int, mActor_name_t, int, int);
  /* 0x128C */ int (*request_main_give_all_proc)(GAME*, ACTOR*, int, int, mActor_name_t, int, int, int, int);
  /* 0x1290 */ int (*request_main_sitdown_all_proc)(GAME*, int, const xyz_t*, int, int);
  /* 0x1294 */ int (*request_main_close_furniture_all_proc)(GAME*, int);
  /* 0x1298 */ int (*request_main_lie_bed_all_proc)(GAME*, int, const xyz_t*, int, int, int);
  /* 0x129C */ int (*request_main_hide_all_proc)(GAME*, int);
  /* 0x12A0 */ int (*request_main_groundhog_proc)(GAME*, int);
  /* 0x12A4 */ int (*request_main_door_all_proc)(GAME*, const xyz_t*, s16, int, void*, int);
  /* 0x12A8 */ int (*request_main_outdoor_all_proc)(GAME*, int, int, int);
  /* 0x12AC */ int (*request_main_wash_car_all_proc)(GAME*, const xyz_t*, const xyz_t*, s16, ACTOR*, int);
  /* 0x12B0 */ int (*request_main_rotate_octagon_all_proc)(GAME*, ACTOR*, int, int, const xyz_t*, s16, int);
  /* 0x12B4 */ int (*request_main_throw_money_all_proc)(GAME*, const xyz_t*, s16, int);
  /* 0x12B8 */ int (*request_main_pray_all_proc)(GAME*, const xyz_t*, s16, int);
  /* 0x12BC */ int (*request_main_mail_jump_all_proc)(GAME*, const xyz_t*, s16, int);
  /* 0x12C0 */ int (*request_main_demo_wait_all_proc)(GAME*, int, void*, int);
  /* 0x12C4 */ int (*request_main_demo_walk_all_proc)(GAME*, f32, f32, f32, int, int);
  /* 0x12C8 */ int (*request_main_demo_geton_train_all_proc)(GAME*, const xyz_t*, s16, int);
  /* 0x12CC */ int (*request_main_demo_getoff_train_all_proc)(GAME*, const xyz_t*, s16, int);
  /* 0x12D0 */ int (*request_main_demo_standing_train_all_proc)(GAME*, int);
  /* 0x12D4 */ int (*request_main_stung_bee_all_proc)(GAME*, int);
  /* 0x12D8 */ int (*request_main_shock_all_proc)(GAME*, f32, s16, s8, int, int);
  /* 0x12DC */ int (*request_main_change_cloth_forNPC_proc)(GAME*, mActor_name_t, int);
  /* 0x12E0 */ int (*request_main_push_snowball_all_proc)(GAME*, void*, int, int);
  /* 0x12E4 */ int (*request_main_stung_mosquito_all_proc)(GAME*, int, int);
  /* 0x12E8 */ int (*request_main_switch_on_lighthouse_all_proc)(GAME*, const xyz_t*, int, int);
  /* 0x12EC */ int (*request_main_demo_geton_boat_all_proc)(GAME*, const xyz_t*, s16, int);
  /* 0x12F0 */ int (*request_main_demo_getoff_boat_standup_all_proc)(GAME*, const xyz_t*, s16, int);
  /* 0x12F4 */ int (*request_main_demo_get_golden_item2_all_proc)(GAME*, int, int);
  /* 0x12F8 */ int (*request_main_demo_get_golden_axe_wait_all_proc)(GAME*, int);
  /* 0x12FC */ int (*check_request_main_priority_proc)(GAME*, int); 
  /* 0x1300 */ void* (*get_door_label_proc)(GAME*); 
  /* 0x1304 */ int (*Set_Item_net_catch_request_table_proc)(ACTOR*, GAME*, u32, s8, const xyz_t*, f32);
  /* 0x1308 */ f32 (*Get_Item_net_catch_swing_timer_proc)(ACTOR*, GAME*);
  /* 0x130C */ u8 (*Set_Item_net_catch_request_force_proc)(ACTOR*, GAME*, u32, s8);
  /* 0x1310 */ void (*Set_force_position_angle_proc)(GAME*, const xyz_t*, const s_xyz*, u8);
  /* 0x1314 */ u8 (*Get_force_position_angle_proc)(GAME*, xyz_t*, s_xyz*);
  /* 0x1318 */ int (*Get_WadeEndPos_proc)(GAME*, xyz_t*);
  /* 0x131C */ u8 tmp131C[0x138C - 0x131C];
  /* 0x138C */ int a_btn_pressed;
  /* 0x1390 */ int a_btn_triggers_submenu;
  /* 0x1394 */ mActor_name_t item_in_front; /* item directly in front of the player */
  /* 0x1396 */ u8 _1396[0x13A8 - 0x1396];
  /* TODO: finish */
};

void Player_actor_ct(ACTOR*, GAME*);
void Player_actor_dt(ACTOR*, GAME*);
void Player_actor_move(ACTOR*, GAME*);
void Player_actor_draw(ACTOR*, GAME*);

#ifdef __cplusplus
}
#endif

#endif
