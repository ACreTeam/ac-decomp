#ifndef M_COMMON_DATA_H
#define M_COMMON_DATA_H

#include "types.h"
#include "m_actor_type.h"
#include "m_land_h.h"
#include "lb_rtc.h"
#include "m_flashrom.h"
#include "m_home_h.h"
#include "m_private.h"
#include "m_npc.h"
#include "m_field_make.h"
#include "m_notice.h"
#include "m_shop.h"
#include "m_kabu_manager.h"
#include "m_post_office.h"
#include "m_police_box.h"
#include "m_snowman.h"
#include "m_config.h"
#include "m_island.h"
#include "m_needlework.h"
#include "m_museum_display.h"
#include "m_lib.h"

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

/* sizeof(PlusBridge_c) == 8 */
typedef struct plus_bridge_s {
  /* 0x00 */ u8 block_x;
  /* 0x01 */ u8 block_z;
  /* 0x02 */ struct {
    u8 exists:1;
    u8 pending:1;
    u8 pad:6;
  };
  /* 0x04 */ lbRTC_ymd_t build_date;
} PlusBridge_c;

typedef struct Save_s {
  /* 0x000000 */ mFRm_chk_t save_check; /* save information */
  /* 0x000014 */ int scene_no; /* current 'scene' id */
  /* 0x000018 */ u8 now_npc_max; /* current number of villagers living in town (see mNpc_(Add/Sub)NowNpcMax) */
  /* 0x000019 */ u8 remove_animal_idx; /* index of the villager which is scheduled to leave town, 0xFF when none selected */
  /* 0x00001A */ u16 copy_protect; /* 'unique' value between [1, 65520] used for copy protection (see mCD_get_land_copyProtect) */
  /* 0x00001C */ u8 pad_1C[4];
  /* 0x000020 */ Private_c private[PLAYER_NUM]; /* player data */
  /* 0x009120 */ mLd_land_info_c land_info; /* town name & id */
  /* 0x00912C */ mNtc_board_post_c noticeboard[mNtc_BOARD_POST_COUNT]; /* noticeboard posts */
  /* 0x009CE4 */ u8 pad_9CE4[4];
  /* 0x009CE8 */ mHm_hs_c homes[PLAYER_NUM]; /* player house data */
  /* 0x0137A8 */ mFM_fg_c fg[FG_BLOCK_Z_NUM][FG_BLOCK_X_NUM]; /* fg items (fg = foreground?) */
  /* 0x0173A8 */ mFM_combination_c combi_table[BLOCK_Z_NUM][BLOCK_X_NUM]; /* acre 'combination' data */
  /* 0x017438 */ Animal_c animals[ANIMAL_NUM_MAX]; /* villagers in town */
  /* 0x020330 */ AnmPersonalID_c last_removed_animal_id; /* ID of last villager who left town */
  /* 0x020340 */ Shop_c shop; /* Nook's shop */
  /* 0x020480 */ Kabu_price_c kabu_price_schedule; /* Stalk Market info */
  /* 0x020498 */ u8 _tmp3[0x1F0]; /* saved events go here, but have a lot of structs in a union so holding off */
  /* 0x020688 */ mActor_name_t fruit; /* town fruit type */
  /* 0x02068A */ u8 house_arrangement; /* 2 bits for each player for the # of house they own */
  /* 0x02068B */ u8 num_statues; /* number of statues built for players who have paid off their debts */
  /* 0x02068C */ lbRTC_time_c all_grow_renew_time; /* renewal time for fg items handled by mAgrw_RenewalFgItem_ovl */
  /* 0x020694 */ PostOffice_c post_office; /* post office data */
  /* 0x020ED0 */ PoliceBox_c police_box; /* police station lost & found */
  /* 0x020EF8 */ mSN_snowman_save_c snowmen; /* saved snowmen data */
  /* 0x020F08 */ u64 melody; /* town tune, each nibble is a note (16 notes) */
  /* 0x020F10 */ Config_c config; /* saved config for sound mode, voice mode, and vibration */
  /* 0x020F14 */ lbRTC_ymd_t renew_time; /* next renew date */
  /* 0x020F18 */ u8 station_type; /* train station type */
  /* 0x020F19 */ u8 weather; /* upper nibble is intensity, lower nibble is type */
  /* 0x020F1A */ u8 save_exist; /* unsure, set in mCD_SaveHome_bg_set_data (1) & mCD_SaveHome_bg (bss) */
  /* 0x020F1B */ u8 npc_force_go_home; /* when set to 1, forces the 'm_go_home' code to activate */
  /* 0x020F1C */ u16 deposit[FG_BLOCK_X_NUM * FG_BLOCK_Z_NUM][UT_Z_NUM]; /* flags for which items are buried around town */
  /* 0x0212DC */ lbRTC_time_c last_grow_time; /* last time that a new villager moved into town */
  /* 0x0212E4 */ u8 _tmp4[0x02137E - 0x0212E4];
  /* 0x02137E */ lbRTC_time_c treasure_buried_time; /* last time treasure was actually buried */
  /* 0x021386 */ lbRTC_time_c treasure_checked_time; /* last time check to bury treasure was executed */
  /* 0x02138E */ u8 saved_rom_debug; /* flag to set save to 'debug rom' mode */
  /* 0x02138F */ u8 snowman_year; /* year last snowman was built */
  /* 0x021390 */ u8 snowman_month; /* month last snowman was built */
  /* 0x021391 */ u8 snowman_day; /* day last snowman was built */
  /* 0x021392 */ u8 snowman_hour; /* hour last snowman was built */
  /* 0x021393 */ u8 haniwa_scheduled; /* when set, gyroids will be spwaned */
  /* 0x021394 */ u8 dust_flag; /* set by field assessment for too much 'dust' (garbage) around town, causes immediate fail of town ranking */
  /* 0x021395 */ u8 clear_grass; /* set by Wisp, removes all weeds */
  /* 0x021396 */ lbRTC_ymd_t event_year_ymd; /* might not exist and just be lbRTC_year_t */
  /* 0x02139A */ u8 unused_2139A[6];
  /* 0x0213A0 */ u8 keep_house_size[PLAYER_NUM]; /* saved flags for house sizes */
  /* 0x0213A4 */ lbRTC_ymd_t force_remove_date; /* last time the NPC force remove timer was updated */
  /* 0x0213A8 */ mMmd_info_c museum_display; /* museum display bits */
  /* 0x0213E7 */ u8 _tmp6[0x213F0 - 0x213E7];
  /* 0x0213F0 */ PlusBridge_c plus_bridge; /* additional bridge info */
  /* 0x021400 */ mNW_needlework_c needlework; /* Able Sisters' designs */
  /* 0x022500 */ u8 _tmp7[0x22528 - 0x22500];
  /* 0x022528 */ OSTime time_delta; /* time delta against GC RTC */
  /* 0x022540 */ Island_c island; /* island data */
  /* 0x023E40 */ u8 _tmp9[0x320];
  /* 0x024160 */ Anmret_c return_animal; /* information about villager which moved back in to your town after moving to someone else's town */
  /* 0x02416C */ u8 _tmp10[0x241A0 - 0x2416C];
  /* 0x0241A0 */ lbRTC_time_c saved_auto_nwrite_time; /* save data notice time used for fishing tourney results? */
  /* 0x0241A8 */ u8 _tmp11[0x26000 - 0x241A8];
} Save_t;

typedef union save_u {
  Save_t save;
  //u8 raw[0x26000]; /* Temp to force length */
} Save;

/* sizeof(common_data_t) == 0x2DC00 */
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
  /* 0x02613C */ Private_c* now_private;
  /* 0x026140 */ mHm_hs_c* now_home;
  /* 0x026144 */ u8 tmp0[0x2614D - 0x26144];
  /* 0x02614D */ u8 transFadeDuration;
  /* 0x02614E */ u8 transWipeSpeed;
  /* 0x02614F */ u8 tmp34[0x2852C - 0x2614F];
  /* 0x02852C */ s16 money_power;
  /* 0x02852E */ s16 goods_power;
  /* 0x028530 */ u8 tmp1[0x28879 - 0x28530];
  /* 0x028879 */ u8 auto_nwrite_count;
  /* 0x02887A */ lbRTC_year_t auto_nwrite_year;
  /* 0x02887C */ u8 save_error_type; /* set to one of the mFRm_ERROR_* states when save is invalid */
  /* 0x02887D */ u8 train_coming_flag; /* set when the train is coming */
  /* 0x02887E */ u8 buried_treasure_flag; /* when set, treasure cannot be buried */
  /* 0x02887F */ u8 tmp2[0x2DB40 - 0x2887F];
  /* 0x02DB40 */ u8 auto_nwrite_set; /* when true, saved nwrite time will be utilized. Seems to be used to keep same date for fishing tourney stuff. */
  /* 0x02DB41 */ u8 tmp3[0x2DBB0 - 0x2DB41];
  /* 0x02DBB0 */ s16 can_look_goki_count;
  /* 0x02DBB4 */ f32 rainbow_opacity; /* current opacity of rainbow (0.0f - 1.0f) */
  /* 0x02DBB8 */ u32 event_flags[7]; /* TODO: make array size a definition/enum */
  /* 0x02DBD4 */ xyz_t* pluss_bridge_pos; /* position of extra bridge */
  /* 0x02DBD8 */ lbRTC_time_c auto_nwrite_time; /* cached notice time used for fishing tourney results? */
  /* 0x02DBE0 */ u8 rhythym_updated;
  /* 0x02DBE1 */ u8 _2dbe1;
  /* 0x02DBE2 */ u8 hem_visible; /* controls farley's visiblilty during cutscene? */
  /* 0x02DBE4 */ u8* carde_program_p; /* pointer to current e-Reader program data */
  /* 0x02DBE8 */ size_t carde_program_size; /* size of current e-Reader program data */
  /* 0x02DBEC */ int unk_nook_present_count; /* something possibly to do withhanding over password present? */
  /* 0x02DBF0 */ u8 pad[16];
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
