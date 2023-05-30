#ifndef M_PRIVATE_H
#define M_PRIVATE_H

#include "types.h"
#include "libu64/gfxprint.h"
#include "m_personal_id.h"
#include "m_npc.h"
#include "m_museum.h"
#include "m_mail.h"
#include "m_needlework.h"
#include "m_calendar.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PLAYER_NUM 4
#define FOREIGNER_NUM 1
#define TOTAL_PLAYER_NUM (PLAYER_NUM + FOREIGNER_NUM)

enum {
  mPr_PLAYER_0,
  mPr_PLAYER_1,
  mPr_PLAYER_2,
  mPr_PLAYER_3,
  mPr_FOREIGNER,

  mPr_PLAYER_NUM
};

#define mPr_ECARD_NUM 367
#define mPr_ECARD_LETTER_NUM ((mPr_ECARD_NUM + 7) / 8) // 46

#define mPr_POCKETS_SLOT_COUNT 15
#define mPr_INVENTORY_MAIL_COUNT 10
#define mPr_DELIVERY_QUEST_NUM mPr_POCKETS_SLOT_COUNT
#define mPr_ERRAND_QUEST_NUM 5
#define mPr_CATALOG_ORDER_NUM 5
#define mPr_FOREIGN_MAP_COUNT 8
#define mPr_ORIGINAL_DESIGN_COUNT 8

#define mPr_SUNBURN_MIN_RANK 0
#define mPr_SUNBURN_MAX_RANK 8

enum {
  mPr_DESTINY_NORMAL,     /* standard fortune state */
  mPr_DESTINY_POPULAR,    /* good luck with villagers */
  mPr_DESTINY_UNPOPULAR,  /* bad luck with villagers */
  mPr_DESTINY_BAD_LUCK,   /* bad luck in general */
  mPr_DESTINY_MONEY_LUCK, /* good money luck */
  mPr_DESTINY_GOODS_LUCK  /* good goods/item luck */
};

/* sizeof(mPr_destiny_c) == 0xA */
typedef struct player_destiny_s {
  /* 0x00 */ lbRTC_time_c received_time; /* time fortune was received */
  /* 0x08 */ u8 type; /* fortune type */ 
} mPr_destiny_c;

/* sizeof(mPr_birthday_c) == 4 */
typedef struct player_birthday_s {
  /* 0x00 */ u16 year; /* assumed, set in mPr_ClearPrivateBirthday but goes unused elsewhere */
  /* 0x02 */ u8 month;
  /* 0x03 */ u8 day;
} mPr_birthday_c;

/* sizeof(mPr_catalog_order_c) == 4 */
typedef struct player_catalog_order_s {
  /* 0x00 */ mActor_name_t item; /* ordered item */
  /* 0x02 */ u8 shop_level; /* shop 'level' at time of order */
} mPr_catalog_order_c;

/* sizeof(mPr_animal_memory_c) == 0xA */
typedef struct player_animal_memory_s {
  /* 0x00 */ mActor_name_t npc_id;
  /* 0x02 */ u8 land_name[LAND_NAME_SIZE];
} mPr_animal_memory_c;

/* sizeof(mPr_map_info_c) == 0xA */
typedef struct player_map_s {
  /* 0x00 */ u8 land_name[LAND_NAME_SIZE];
  /* 0x08 */ u16 land_id;
} mPr_map_info_c;

/* sizeof(mPr_day_day_c) == 6 */
typedef struct player_day_day_s {
  /* 0x00 */ lbRTC_ymd_t last_date; /* last date modified */
  /* 0x04 */ u8 days; /* number of unique days */
} mPr_day_day_c;

/* sizeof(mPr_sunburn_c) == 6 */
typedef struct player_sunburn_s {
  /* 0x00 */ lbRTC_ymd_t last_changed_date; /* last date that the sunburn rank changed */
  /* 0x04 */ s8 rank; /* level of sunburn, 0-8 */
  /* 0x05 */ s8 rankdown_days; /* days until sunburn rank decreases */
} mPr_sunburn_c;

/* sizeof(mPr_carde_data_c) == 0x32 */
typedef struct player_ecard_data_s {
  /* 0x00 */ lbRTC_ymd_t letter_send_date; /* date the latest eCard letter was sent */
  /* 0x04 */ u8 card_letters_sent[mPr_ECARD_LETTER_NUM]; /* bitfield keeping track of which eCard letters have been sent to the player [0, 366] */
} mPr_carde_data_c;

typedef struct private_s {
  /* 0x0000 */ PersonalID_c player_ID; /* player's id info */
  /* 0x0014 */ s8 gender; /* gender/sex of player */
  /* 0x0015 */ s8 face; /* face type of player */
  /* 0x0016 */ u8 reset_count; /* times player has reset */
  /* 0x0017 */ mMsm_mail_info_c museum_mail_info; /* museum items & remail info */

  /* must be a struct due to alignment of first member */
  /* 0x0068 */ struct {
    /* 0x0068 */ mActor_name_t pockets[mPr_POCKETS_SLOT_COUNT]; /* items in inventory */
    /* 0x0086 */ u8 lotto_ticket_expiry_month;
    /* 0x0087 */ u8 lotto_ticket_mail_storage;
    /* 0x0088 */ u32 item_conditions; /* bitfield (15 values), 2 bits per pocket slot */
    /* 0x008C */ u32 wallet;
    /* 0x0090 */ u32 loan;
  } inventory;

  /* 0x0094 */ mQst_delivery_c deliveries[mPr_DELIVERY_QUEST_NUM]; /* delivery quests */
  /* 0x02EC */ mQst_errand_c errands[mPr_ERRAND_QUEST_NUM]; /* errand quests */

  /* 0x04A4 */ mActor_name_t equipment; /* equipped item */

  /* 0x04A6 */ Mail_hs_c saved_mail_header; /* saved mail header/footer which is inserted when writing new letters */
  /* 0x04E0 */ Mail_c mail[mPr_INVENTORY_MAIL_COUNT]; /* letters in inventory */
  /* 0x1084 */ mActor_name_t backgound_texture; /* inventory background shirt item id */
  /* 0x1086 */ u8 exists; /* 0/1 if player exists or not */
  /* 0x1087 */ u8 hint_count; /* total hints heard from villagers (initial dialog) */

  /* 0x1088 */ u16 cloth_idx; /* index value for texture? */
  /* 0x108A */ mActor_name_t cloth; /* shirt item */

  /* 0x108C */ AnmPersonalID_c stored_anm_id; /* foriegn animal personal ID leftover from N64? */

  /* 0x109A */ mPr_destiny_c destiny; /* player fortune, seemingly called destiny */
  /* 0x10A4 */ mPr_birthday_c birthday; /* player birthday */
  /* 0x10A8 */ mPr_catalog_order_c catalog_orders[mPr_CATALOG_ORDER_NUM]; /* items ordered from catalog to be mailed */
  /* 0x10BC */ u8 unk_10A8[24]; /* seemingly unused? */
  /* 0x10D4 */ u32 aircheck_collect_bitfield[2]; /* TODO: this should be a define like #define mPr_AIRCHECK_BITFIELD_NUM ((MD_COUNT / 32) + 1) */
  /* 0x10DC */ Anmremail_c remail; /* scheduled mail received from a foreign villager? */
  /* 0x10F4 */ u32 reset_code; /* 0 when not reset, random value after reset */
  /* 0x10F8 */ mPr_animal_memory_c animal_memory; /* id and town of last animal to move to another town */
  /* 0x1102 */ u8 complete_fish_insect_flags; /* bit0 = completed fish, bit1 = villager acknowledged completed fish, bit2 = completed insect, bit3 = villager acknowledged complete insect */
  /* 0x1104 */ lbRTC_year_t celebrated_birthday_year; /* last year a birthday was celebrated by card or visitor */

                /* catalog */
  /* 0x1108 */ u32 furniture_collected_bitfield[43];
  /* 0x11B4 */ u32 wall_collected_bitfield[3];
  /* 0x11C0 */ u32 carpet_collected_bitfield[3];
  /* 0x11CC */ u32 paper_collected_bitfield[2];
  /* 0x11D4 */ u32 music_collected_bitfield[2];

  /* 0x11DC */ mPr_map_info_c maps[mPr_FOREIGN_MAP_COUNT]; /* maps 'collected' for foreign towns */

  /* 0x122C */ u32 bank_account; /* probably 'deposit' interally */
  /* 0x1240 */ mNW_original_design_c my_org[mPr_ORIGINAL_DESIGN_COUNT]; /* Able Sisters' designs */
  /* 0x2340 */ u8 my_org_no_table[mPr_ORIGINAL_DESIGN_COUNT]; /* order of designs */
  /* 0x2348 */ u32 state_flags; /* TODO: this might be a bitfield/struct, also document bits */
  /* 0x234C */ mCD_player_calendar_c calendar; /* player calendar data */
  /* 0x23B4 */ u32 soncho_trophy_field0; /* first 28 tortimer event flags */
  /* 0x23B8 */ mPr_day_day_c needlework_day; /* info for how many unique days the player has talked to Sable */
  /* 0x23BE */ mPr_day_day_c radio_day; /* radio stamp days */
  /* 0x23C4 */ mPr_sunburn_c sunburn; /* sunburn state */
  /* 0x23CA */ u8 unused_23CA[14]; /* seemingly unused data */
  /* 0x23D8 */ mActor_name_t birthday_present_npc; /* npc id of the 'best friend' villger who will gift the player a present on their birthday (at the door) */
  /* 0x23DA */ u16 golden_items_collected; /* bitfield tracking which golden items the player has received */
  /* 0x23DC */ u32 soncho_trophy_field1; /* remaining tortimer event flags */
  /* 0x23E0 */ mPr_carde_data_c ecard_letter_data; /* info relating to scanned e-Card letters */
  /* 0x2412 */ u8 unused_2412[46];
} Private_c;

extern s16 mPr_GetGoodsPower();
extern s16 mPr_GetMoneyPower();

extern void mPr_PrintMapInfo_debug(gfxprint_t* gfxprint);
extern int mPr_NullCheckPersonalID(PersonalID_c* pid);
extern int mPr_CheckCmpPersonalID(PersonalID_c* pid_a, PersonalID_c* pid_b);
extern void mPr_ClearPersonalID(PersonalID_c* pid);
extern void mPr_CopyPersonalID(PersonalID_c* dst, PersonalID_c* src);
extern void mPr_ClearPrivateInfo(Private_c* private);
extern void mPr_RandomSetPlayerData_title_demo();

#ifdef __cplusplus
}
#endif

#endif
