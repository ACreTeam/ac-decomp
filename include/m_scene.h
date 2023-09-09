#ifndef M_SCENE_H
#define M_SCENE_H

#include "types.h"
#include "m_lib.h"
#include "famicom_emu.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct door_data_s {
  int next_scene_id;
  u8 exit_orientation;
  u8 exit_type; // 0 = normal, 1 = restart game?
  u16 extra_data;
  s_xyz exit_position;
  mActor_name_t door_actor_name;
  u8 wipe_type;
  u8 pad[3]; // possibly necessary due to struct copy
} Door_data_c;

#define mSc_OBJECT_BANK_NUM 70

typedef struct object_bank_s {
  s16 bank_id;
  char* ram_start;
  // TODO: others
  u8 _08[0x58 - 0x08];
  s16 num_exist;
  u8 _0x5A[0x5C - 0x5A];
} Object_Bank_c;

typedef struct object_exchange_s {
  Object_Bank_c banks[mSc_OBJECT_BANK_NUM];
  int _1928;
  int _192C;
  int exchange_id;
  u8 _1934[0x1958-0x1934];
} Object_Exchange_c;

typedef struct scene_status_s{
    u8 unk0[0x13];
    u8 unk13;
}Scene_status_c;

extern Scene_status_c test01_info;
extern Scene_status_c test02_info;
extern Scene_status_c test03_info;
extern Scene_status_c water_test_info;
extern Scene_status_c test_step01_info;
extern Scene_status_c test04_info;
extern Scene_status_c npc_room01_info;
extern Scene_status_c test_fd_npc_land_info;
extern Scene_status_c field_tool_field_info;
extern Scene_status_c shop01_info;
extern Scene_status_c BG_TEST01_info;
extern Scene_status_c BG_TEST01_XLU_info;
extern Scene_status_c broker_shop_info;
extern Scene_status_c fg_tool_in_info;
extern Scene_status_c post_office_info;
extern Scene_status_c start_demo1_info;
extern Scene_status_c start_demo2_info;
extern Scene_status_c police_box_info;
extern Scene_status_c buggy_info;
extern Scene_status_c player_select_info;
extern Scene_status_c player_room_s_info;
extern Scene_status_c player_room_m_info;
extern Scene_status_c player_room_l_info;
extern Scene_status_c shop02_info;
extern Scene_status_c shop03_info;
extern Scene_status_c shop04_1f_info;
extern Scene_status_c test05_info;
extern Scene_status_c PLAYER_SELECT2_info;
extern Scene_status_c PLAYER_SELECT3_info;
extern Scene_status_c shop04_2f_info;
extern Scene_status_c event_notification_info;
extern Scene_status_c kamakura_info;
extern Scene_status_c field_tool_field_info;
extern Scene_status_c title_demo_info;
extern Scene_status_c PLAYER_SELECT4_info;
extern Scene_status_c museum_entrance_info;
extern Scene_status_c museum_picture_info;
extern Scene_status_c museum_fossil_info;
extern Scene_status_c museum_insect_info;
extern Scene_status_c museum_fish_info;
extern Scene_status_c player_room_ll1_info;
extern Scene_status_c player_room_ll2_info;
extern Scene_status_c p_room_bm_s_info;
extern Scene_status_c p_room_bm_m_info;
extern Scene_status_c p_room_bm_l_info;
extern Scene_status_c p_room_bm_ll1_info;
extern Scene_status_c NEEDLEWORK_info;
extern Scene_status_c player_room_island_info;
extern Scene_status_c npc_room_island_info;
extern Scene_status_c start_demo3_info;
extern Scene_status_c lighthouse_info;
extern Scene_status_c tent_info;

extern int mSc_bank_regist_check(Object_Exchange_c* exchange, s16 bank_id);
extern void mSc_regist_initial_exchange_bank(GAME_PLAY* play);
extern void mSc_dmacopy_data_bank(Object_Exchange_c*);
extern void mSc_data_bank_ct(GAME_PLAY*, Object_Exchange_c*);
extern void Door_info_ct(Door_data_c**);
extern void Scene_ct(GAME_PLAY*, void*);
extern void mSc_decide_exchange_bank(Object_Exchange_c*);
extern void return_emu_game(GAME*);


#ifdef __cplusplus
}
#endif

#endif
