#ifndef M_COMMON_DATA_H
#define M_COMMON_DATA_H

#include "types.h"
#include "m_actor_type.h"
#include "m_land_h.h"
#include "lb_rtc.h"
#include "m_flashrom.h"
#include "m_home.h"
#include "m_private.h"
#include "m_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct time_s {
  u32 season;
  u32 term_idx;
  s16 bgitem_profile;
  s16 bgitem_bank;
  int now_sec;
  lbRTC_time_c rtc_time;
  s16 rad_min; /* clock hand radial position for mins */
  s16 rad_hour; /* clock hand radial position for hours */
  u8 time_signal;
  u8 under_sec;
  u8 disp;
  u8 rtc_crashed;
  int rtc_enabled;
  int add_sec;
  int add_idx;
} Time_c;

typedef struct Save_s {
  /* 0x000000 */ mFRm_chk_t save_check; /* save information */
  /* 0x000014 */ int scene_no; /* current 'scene' id */
  /* 0x000018 */ u8 _tmp0[0x9108];
  /* 0x009120 */ mLd_land_info_c land_info; /* town name & id */
  /* 0x00912C */ u8 _tmp1[0xBBC];
  /* 0x009CE8 */ mHm_hs_c homes[PLAYER_NUM]; /* player house data */
  /* 0x0137A8 */ u8 _tmp2[0x3C90];
  /* 0x017438 */ Animal_c animals[ANIMAL_NUM_MAX]; /* villagers in town */
  /* 0x020330 */ AnmPersonalID_c last_removed_animal_id; /* ID of last villager who left town */
  /* 0x02033E */ u8 _tmp3[0xBD6];
  /* 0x020F14 */ lbRTC_ymd_t renew_time; /* next renew date */
  /* 0x020F18 */ u8 _tmp4[0x476];
  /* 0x02138E */ u8 saved_rom_debug; /* flag to set save to 'debug rom' mode */
  /* 0x02138F */ u8 _tmp5[0x1199];
  /* 0x022528 */ OSTime time_delta; /* time delta against GC RTC */
  /* 0x022530 */ u8 _tmp6[0x3AD0];
} Save_t;

typedef union save_u {
  Save_t save;
  u8 raw[0x26000]; /* Temp to force length */
} Save;

typedef struct common_data_s {
  /* 0x000000 */ Save save;
  /* 0x026000 */ u8 game_started;
  /* 0x026001 */ u8 field_type;
  /* 0x026002 */ u8 field_draw_type;
  /* 0x026003 */ u8 player_no;
  /* 0x026004 */ int last_scene_no;
  /* 0x026008 */ int player_data_mode;
  /* 0x02600C */ u8 _clip[0x104]; /* Temporary, clip is a struct with size 0x104 */
  /* 0x026110 */ Time_c time;
} common_data_t;

extern common_data_t common_data;

#define Common_Get(name) (common_data.name)
#define Common_GetPointer(name) (&common_data.name)
#define Common_Set(name, value) (common_data.name = (value))

#define Save_Get(name) (Common_Get(save.save.name))
#define Save_GetPointer(name) (Common_GetPointer(save.save.name))
#define Save_Set(name, value) (Common_Set(save.save.name, value))

#ifdef __cplusplus
}
#endif

#endif
