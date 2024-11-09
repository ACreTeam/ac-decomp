#ifndef M_ISLAND_H
#define M_ISLAND_H

#include "types.h"
#include "m_personal_id.h"
#include "m_npc.h"
#include "m_land.h"
#include "m_field_make.h"
#include "m_home.h"
#include "m_needlework.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mISL_ISLANDER_NUM 1

#define mISL_ISLAND_NAME_LEN 8

#define mISL_FG_BLOCK_X_NUM 2
#define mISL_FG_BLOCK_Z_NUM 1

#define mISL_BLOCK_X0 4
#define mISL_BLOCK_X1 5
#define mISL_BLOCK_Z 8

enum {
  mISL_ISLAND_BLOCK_LEFT,
  mISL_ISLAND_BLOCK_RIGHT,

  mISL_ISLAND_BLOCK_NUM
};

#define mISL_PLAYER_ACTION_NUM 32

#define mISL_PLAYER_ACTION_DIG_SCOOP (1 << 0)
#define mISL_PLAYER_ACTION_PLANT_FLOWER (1 << 1)
#define mISL_PLAYER_ACTION_CHANGE_FLAG (1 << 2)
#define mISL_PLAYER_ACTION_SHAKE_TREE (1 << 3)
#define mISL_PLAYER_ACTION_TRAMPLE_FLOWER (1 << 4)
#define mISL_PLAYER_ACTION_TRAMPLE_ALL_FLOWERS (1 << 5) // seems to be incorrectly? set when only a single flower was trampled
#define mISL_PLAYER_ACTION_CHOP_PALM_TREE (1 << 6)
#define mISL_PLAYER_ACTION_CHOP_TREE (1 << 7)
#define mISL_PLAYER_ACTION_PLANT_TREE (1 << 8)
#define mISL_PLAYER_ACTION_UZAI_PUSHED (1 << 9)
#define mISL_PLAYER_ACTION_UZAI_HIT (1 << 10)
#define mISL_PLAYER_ACTION_BEST_FRIEND (1 << 11) // seemingly unused but based on intention from dialogue
#define mISL_PLAYER_ACTION_UZAI_HIT_NET (1 << 12) // set at the same time as "UZAI_HIT"
#define mISL_PLAYER_ACTION_FALL_PITFALL (1 << 13)
#define mISL_PLAYER_ACTION_PLANT_APPLE_TREE (1 << 14)
#define mISL_PLAYER_ACTION_PLANT_PEACH_TREE (1 << 15)
#define mISL_PLAYER_ACTION_PLANT_CHERRY_TREE (1 << 16)
#define mISL_PLAYER_ACTION_PLANT_PEAR_TREE (1 << 17)
#define mISL_PLAYER_ACTION_PLANT_ORANGE_TREE (1 << 18)
#define mISL_PLAYER_ACTION_PLANT_COCONUT_TREE (1 << 19)
#define mISL_PLAYER_ACTION_PICKUP_COCONUT (1 << 20)
#define mISL_PLAYER_ACTION_EAT_COCONUT (1 << 21)
#define mISL_PLAYER_ACTION_TUMBLE (1 << 22)
#define mISL_PLAYER_ACTION_DESTINY_POPULAR (1 << 23)
#define mISL_PLAYER_ACTION_DESTINY_UNPOPULAR (1 << 24)
#define mISL_PLAYER_ACTION_DESTINY_BAD_LUCK (1 << 25)
#define mISL_PLAYER_ACTION_DESTINY_MONEY_LUCK (1 << 26)
#define mISL_PLAYER_ACTION_DESTINY_GOODS_LUCK (1 << 27)
#define mISL_PLAYER_ACTION_SEX_MALE (1 << 28)
#define mISL_PLAYER_ACTION_SEX_FEMALE (1 << 29)
#define mISL_PLAYER_ACTION_TRADE_CLOTH (1 << 30)
#define mISL_PLAYER_ACTION_NOTICE_FISHING_ROD (1 << 31)

/* sizeof(Island_c) == 0x1900 */
typedef struct island_s {
  /* 0x0000 */ u8 name[mISL_ISLAND_NAME_LEN]; /* island name */
  /* 0x0008 */ mLd_land_info_c landinfo; /* land info for town */
  /* 0x0014 */ mFM_fg_c fgblock[mISL_FG_BLOCK_Z_NUM][mISL_FG_BLOCK_X_NUM]; /* island item actor data */
  /* 0x0418 */ mHm_cottage_c cottage; /* player shared cottage data */
  /* 0x0CE0 */ mNW_original_design_c flag_design; /* island flag design */
  /* 0x0F00 */ Animal_c animal; /* islander info */
  /* 0x1888 */ u16 deposit[mISL_FG_BLOCK_X_NUM * mISL_FG_BLOCK_Z_NUM][UT_Z_NUM]; /* buried item bitfield */
  /* 0x18C8 */ u8 bg_data[mISL_ISLAND_BLOCK_NUM]; /* island acre ids */
  /* 0x18CA */ lbRTC_time_c renew_time; /* last time island was visited? */
  /* 0x18D2 */ u8 unused_18D2[14]; /* unused */
  /* 0x18E0 */ u8 grass_tex_type; /* grass type */
  /* 0x18E1 */ u8 last_song_to_island; /* last song kapp'n sang to the island */
  /* 0x18E2 */ u8 last_song_from_island; /* last song kapp'n sang leaving the island */
  /* 0x18E3 */ u8 unused_18E3[29]; /* unused */
} Island_c;

extern void mISL_ClearKeepIsland();
extern void mISL_KeepIsland(Island_c* island);
extern void mISL_ChangeBG();
extern void mISL_RestoreIsland();
extern void mISL_init(Island_c* island);
extern void mISL_ClearNowPlayerAction();
extern void mISL_SetPlayerAction(PersonalID_c* pid, u32 action);
extern void mISL_SetNowPlayerAction(u32 action);
extern int mISL_CheckPlayerAction(PersonalID_c* pid, u32 action);
extern int mISL_CheckNowPlayerAction(u32 action);

/* NOTE: a lot of these seem to be padded to 4-bytes and should be redone in the future */

typedef struct agb_landinfo_s {
  u8 name[LAND_NAME_SIZE];
  s8 exists;
  u16 id;
} mISL_landinfo_agb_c;

typedef struct agb_floor_s {
  /* 0x000 */ mHm_lyr_c layers[mHm_LAYER_NUM];
  /* 0x8A0 */ mHm_wf_c wall_floor;
  /* 0x8A2 */ u16 pad_8A2;
  /* 0x8A4 */ TempoBeat_c tempo_beat;
  /* 0x8A8 */ u32 floor_bit_info;
} mISL_flr_agb_c;

typedef struct agb_cottage_s {
  /* 0x000 */ mHm_wf_c unused_wall_floor; /* Has wallpaper & flooring bounds checks in sChk_CheckSaveData_Cattage */
  /* 0x002 */ u8 pad_2[2];
  /* 0x004 */ u8 unk_2[2]; /* struct/array that is two bytes long, maybe another wall floor? */
  /* 0x008 */ mISL_flr_agb_c room; /* Cottage room */
  /* 0x8B8 */ u8 unk_8B8; // unk_4
  /* 0x8B9 */ u8 unk_8B9; // unk_5
  /* 0x8BA */ u8 pad_8BA;
  /* 0x8BB */ u8 pad_8BB;
  /* 0x8BC */ mHm_goki_c goki; /* Cottage cockroaches */
  /* 0x8C8 */ u32 pad_8C8;
  /* 0x8CC */ u32 music_box[2]; /* Cottage music storage... separate from main home? */
} mISL_cottage_agb_c;

typedef struct agb_anmplayermail_s {
  /* 0x000 */ u8 font; /* 'font' to use for letter info */
  /* 0x001 */ u8 paper_type; 
  /* 0x002 */ mActor_name_t present;
  /* 0x004 */ u8 header_back_start; /* position for name insertion in header */
  /* 0x005 */ u8 pad_5[3]; /* likely pad */
  /* 0x008 */ u8 header[MAIL_HEADER_LEN];
  /* 0x020 */ u8 body[MAIL_BODY_LEN];
  /* 0x0E0 */ u8 footer[MAIL_FOOTER_LEN];
  /* 0x100 */ lbRTC_ymd_c date; /* sent date */
} mISL_Anmplmail_agb_c;

typedef struct agb_anmmem_s {
  PersonalID_c player_id;
  lbRTC_time_c last_speak_time;
  memuni_u memuni;
  u64 saved_town_tune;
  s8 friendship;
  u32 letter_info;
  mISL_Anmplmail_agb_c letter;
} mISL_Anmmem_agb_c;

typedef struct agb_quest_base_s {
  /* 0x00 */ u32 info;
  /* 0x04 */ lbRTC_time_c time_limit;
} mISL_quest_base_c;

typedef struct agb_quest_contest_s {
  /* 0x00 */ mISL_quest_base_c base; /* quest base struct */
  /* 0x0C */ mActor_name_t requested_item; /* item (if any) requested by the villager */
  /* 0x0E */ u8 pad_0E[2];
  /* 0x10 */ PersonalID_c player_id; /* personal id of the player */
  /* 0x24 */ s8 type; /* type of quest, seems to be repeat of data in quest base */
  /* 0x25 */ u8 pad_25[3];
  /* 0x28 */ mQst_contest_info_u info; /* contest info for flower & letter quests */
} mISL_quest_contest_c;

typedef struct agb_animal_s {
  /* 0x000 */ AnmPersonalID_c id; /* this villager's ID */
  /* 0x010 */ mISL_Anmmem_agb_c memories[ANIMAL_MEMORY_NUM]; /* memories of players who've spoken to this villager */
  /* 0x8D0 */ Anmhome_c home_info; /* home position info */
  /* 0x8D5 */ u8 pad_8D5[3];
  /* 0x8D8 */ u8 catchphrase[ANIMAL_CATCHPHRASE_LEN]; /* may be called 'word_ending' */
  /* 0x8E2 */ u8 pad_8E2[2];
  /* 0x8E4 */ mISL_quest_contest_c contest_quest; /* current contest quest information */
  /* 0x910 */ u8 parent_name[PLAYER_NAME_LEN]; /* name of the player who 'spawned' the villager in, unsure why this is tracked */
  /* 0x918 */ u8 pad_918[4];
  /* 0x91C */ anmuni_u anmuni; /* name of the last town the villager lived in or saved island ftr */
  /* 0x924 */ u8 pad_924[4]; /* may include last_land_id */
  /* 0x928 */ u8 mood; /* probably called 'feel' based on code */
  /* 0x929 */ u8 mood_time; /* probably called 'feel_tim' based on code */
  /* 0x92A */ mActor_name_t cloth; /* shirt the villager is wearing */
  /* 0x92C */ u16 remove_info; /* info about villager moving between towns? kinda stubbed */
  /* 0x92D */ u8 is_home; /* TRUE when the villager is home, otherwise FALSE */
  /* 0x92E */ u8 moved_in; /* TRUE when the villager moved in after town creation, FALSE if they started out in town */
  /* 0x92F */ u8 removing; /* TRUE when the villager is leaving town, FALSE otherwise */
  /* 0x930 */ u8 cloth_original_id; /* 0xFF when not wearing an Able Sister's pattern, otherwise 0-3 indicating which pattern */
  /* 0x931 */ s8 umbrella_id; /* 0xFF when no umbrella, 0-31 when a standard umbrella, 32-35 when using an Able Sister's pattern */
  /* 0x932 */ u8 unk_932; /* Exists according to mISL_gc_to_agb_animal, but seems unused in practice */
  /* 0x934 */ mActor_name_t present_cloth; /* The most recently received shirt from a letter which the villager may change into */
  /* 0x936 */ u8 pad_936[6];
  /* 0x93C */ u8 animal_relations[ANIMAL_NUM_MAX]; /* relationships between all villagers in town, starts at 128 which is neutral */
  /* 0x94B */ u8 pad_94B[5];
  /* 0x950 */ AnmHPMail_c hp_mail[ANIMAL_HP_MAIL_NUM]; /* mail password info storage */
  /* 0x9C0 */ u8 _9C0[24]; /* unknown usage/unused */
} mISL_Animal_agb_c;

typedef struct island_agb_s {
  /* 0x0000 */ u8 _0000[8];
  /* 0x0008 */ u8 name[mISL_ISLAND_NAME_LEN]; /* island name */
  /* 0x0010 */ u8 grass_tex_type; /* grass type */
  /* 0x0011 */ u8 _0011[2];
  /* 0x0013 */ u8 in_use; /* Set on the GBA when the island has been transferred already */
  /* 0x0014 */ mISL_landinfo_agb_c landinfo; /* land info for town */
  /* 0x0020 */ u8 _0020[4];
  /* 0x0024 */ mFM_fg_c fgblock[mISL_FG_BLOCK_Z_NUM][mISL_FG_BLOCK_X_NUM]; /* island item actor data */
  /* 0x0424 */ u8 _0424[4];
  /* 0x0428 */ mISL_cottage_agb_c cottage; /* player shared cottage data */
  /* 0x0D00 */ mNW_original_design_c flag_design; /* island flag design */
  /* 0x0F20 */ mISL_Animal_agb_c animal; /* islander info */
  /* 0x18F8 */ u16 deposit[mISL_FG_BLOCK_X_NUM * mISL_FG_BLOCK_Z_NUM][UT_Z_NUM]; /* buried item bitfield */
  /* 0x1938 */ u8 bg_data[mISL_ISLAND_BLOCK_NUM]; /* island acre ids */
  /* 0x193A */ u8 weather;
  /* 0x193C */ lbRTC_time_c renew_time; /* last time island was visited? */
  /* 0x1944 */ int npc_idx;
  /* 0x1948 */ u32 earth_tex[1024];
  /* 0x2948 */ u32 npc_tex[1024];
  /* 0x3948 */ u16 npc_pal[16];
  /* 0x3968 */ u8 _3968[20];
  /* 0x397C */ u8 _397C;
  /* 0x397D */ u8 last_song_to_island; /* last song kapp'n sang for a male character */
  /* 0x397E */ u8 last_song_from_island; /* last song kapp'n sang for a female character */
  /* 0x397F */ u8 checksum;
} Island_agb_c;

extern void mISL_gc_to_agb(Island_agb_c* agb, Island_c* gc);
extern void mISL_agb_to_gc(Island_c* gc, Island_agb_c* agb);

#ifdef __cplusplus
}
#endif

#endif
