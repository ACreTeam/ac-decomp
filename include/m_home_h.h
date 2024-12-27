#ifndef M_HOME_H_H
#define M_HOME_H_H

#include "types.h"
#include "m_field_make.h"
#include "m_actor_type.h"
#include "m_personal_id.h"
#include "audio.h"
#include "lb_rtc.h"
#include "m_mail.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HOME_MAILBOX_SIZE 10
#define HANIWA_ITEM_HOLD_NUM 4
#define HANIWA_MESSAGE_LEN 128
#define mHm_LAYER_NUM 4

enum {
    mHm_ROOM_MAIN,
    mHm_ROOM_UPPER,
    mHm_ROOM_BASEMENT,

    mHm_ROOM_NUM
};

enum {
    mHm_ROOMTYPE_SMALL,
    mHm_ROOMTYPE_MEDIUM,
    mHm_ROOMTYPE_LARGE,
    mHm_ROOMTYPE_COTTAGE,

    mHm_ROOMTYPE_NUM
};

enum {
    mHm_HOMESIZE_SMALL,  /* initial size */
    mHm_HOMESIZE_MEDIUM, /* paid off first debt */
    mHm_HOMESIZE_LARGE,  /* paid off second debt (excluding basement) */
    mHm_HOMESIZE_UPPER,  /* paid off third debt & basement */
    mHm_HOMESIZE_STATUE, /* paid off final debt */

    mHm_HOMESIZE_NUM
};

enum {
    mHm_HANIWA_TRADE_0,
    mHm_HANIWA_TRADE_1,
    mHm_HANIWA_TRADE_2,
    mHm_HANIWA_TRADE_3,

    mHm_HANIWA_TRADE_NUM
};

enum {
    mHm_OUTLOOK_PAL_0,
    mHm_OUTLOOK_PAL_1,
    mHm_OUTLOOK_PAL_2,
    mHm_OUTLOOK_PAL_3,
    mHm_OUTLOOK_PAL_4,
    mHm_OUTLOOK_PAL_5,
    mHm_OUTLOOK_PAL_6,
    mHm_OUTLOOK_PAL_7,
    mHm_OUTLOOK_PAL_8,
    mHm_OUTLOOK_PAL_9,
    mHm_OUTLOOK_PAL_10,
    mHm_OUTLOOK_PAL_11,

    mHm_OUTLOOK_PAL_NUM
};

/* sizeof(mHm_rmsz_c) == 6 */
typedef struct home_size_info_s {
    /* 0x00 */ struct {
        /* 0x00 */ u8 day;
        /* 0x01 */ u8 month;
        /* 0x02 */ u16 year;
    } upgrade_order_date; /* date you ordered an upgrade, seems to be a struct */

    /* 0x04 */ u8 size : 3;             /* current house size */
    /* 0x04 */ u8 next_size : 3;        /* next house size when upgrade is ordered */
    /* 0x04 */ u8 statue_rank : 2;      /* statue ranking, 0 = gold, 1 = silver, 2 = bronze, 3 = jade */
    /* 0x05 */ u8 renew : 1;            /* refresh house size & 'outlook' palette */
    /* 0x05 */ u8 statue_ordered : 1;   /* set when statue is ordered from Nook */
    /* 0x05 */ u8 basement_ordered : 1; /* set when basement has been ordered */
    /* 0x05 */ u8 pad_1 : 1;              /* unused? */
    /* 0x05 */ u8 pad : 4;
} mHm_rmsz_c;

/* sizeof(Haniwa_Item_c) == 8 */
typedef struct home_haniwa_item_s {
    /* 0x00 */ mActor_name_t item; /* held item */
    /* 0x02 */ s16 exchange_type;  /* type of exchange (sale, free, trade) */
    /* 0x04 */ u32 extra_data;     /* trade related data */
} Haniwa_Item_c;

/* sizeof(Haniwa_c) == 0xA4 */
typedef struct home_haniwa_s {
    /* 0x00 */ Haniwa_Item_c items[HANIWA_ITEM_HOLD_NUM]; /* held items */
    /* 0x20 */ u8 message[HANIWA_MESSAGE_LEN];            /* message for visitors */
    /* 0xA0 */ u32 bells;                                 /* held bells from selling items */
} Haniwa_c;

/* sizeof(mHm_wf_c) == 2 */
typedef struct home_wall_floor_s {
    /* 0x00 */ u8 flooring_idx;
    /* 0x01 */ u8 wallpaper_idx;
} mHm_wf_c;

/* sizeof(mHm_goki_c) == 0xA */
typedef struct home_goki_s {
    /* 0x00 */ lbRTC_time_c time; /* last time updated */
    /* 0x08 */ u8 num;            /* number of cockroaches in the house */
    /* 0x09 */ u8 pad;            /* unused outside of being initalized to 0 */
} mHm_goki_c;

/* sizeof(mHm_lyr_c) == 0x228 */
typedef struct home_layer_s {
    /* 0x000 */ mActor_name_t items[UT_Z_NUM][UT_X_NUM]; /* Furniture item actors */
    /* 0x200 */ u64 ftr_switch;     /* Bitfield for controlling which furniture items are active, max of 64 */
    /* 0x208 */ u32 haniwa_step[8]; /* Only referenced in mISL_gc_to_agb_layer */
} mHm_lyr_c;

typedef struct floor_bit_info_s {
    u8 wall_original : 1;  /* is wallpaper a pattern (original)? */
    u8 floor_original : 1; /* is flooring a pattern (original)? */
    u8 bit_2_7 : 6;        /* unused? */
} mHm_fllot_bit_c;

/* sizeof(mHm_flr_c) == 0x8A8 */
typedef struct home_floor_s {
    /* 0x000 */ mHm_lyr_c layer_main;
    /* 0x228 */ mHm_lyr_c layer_secondary; /* Also storage layer 0 */
    /* 0x450 */ mHm_lyr_c layer_storage1;
    /* 0x678 */ mHm_lyr_c layer_storage2;
    /* 0x8A0 */ mHm_wf_c wall_floor;
    /* 0x8A2 */ TempoBeat_c tempo_beat;
    /* 0x8A4 */ mHm_fllot_bit_c floor_bit_info;
} mHm_flr_c;

/* sizeof(mHm_flg_c) == 1 */
typedef struct home_flags_s {
    u8 house_updated : 1; /* signals HRA to re-score house */
    u8 has_saved : 1;     /* whether or not the player has saved at this house before */
    u8 hra_member : 1;    /* whether or not the house has been setup for HRA membership */
    u8 has_basement : 1;  /* set when the basement is built */
    u8 hra_reward0 : 1;   /* earned 70k HRA points reward */
    u8 hra_reward1 : 1;   /* earned 100k HRA points reward */
    u8 bit_6 : 1;         /* unused */
    u8 bit_7 : 1;         /* unused */
} mHm_flg_c;

/* sizeof(mHm_hs_c) == 0x26B0 */
typedef struct home_s {
    /* 0x0000 */ PersonalID_c ownerID; /* owner player's ID */
    /* 0x0014 */ u8 unk_14[6];
    /* 0x001A */ TempoBeat_c haniwa_tempo;  /* unsure about this */
    /* 0x001C */ lbRTC_ymd_c hra_mark_time; /* last HRA judge date */
    /* 0x0020 */ u32 hra_mark_info;         /* bitfield of HRA info pulled when HRA mails letter */
    /* 0x0024 */ mHm_flg_c flags;
    /* 0x0026 */ mHm_rmsz_c size_info;   /* home size info */
    /* 0x002C */ u8 outlook_pal;         /* current house palette */
    /* 0x002D */ u8 ordered_outlook_pal; /* house palette ordered at Nook's via upgrade */
    /* 0x002E */ u8
        next_outlook_pal; /* next house palette set via all other means (villager, Wisp, paint @ Nook's, ...) */
    /* 0x002F */ u8
        door_original;         /* player design shown on door, apparently called 'original', maybe 'original design'? */
    /* 0x0030 */ u8 unk_30[8]; /* unused? */
    /* 0x0038 */ mHm_flr_c floors[mHm_ROOM_NUM];    /* house floors, might be a union idk */
    /* 0x1A30 */ Mail_c mailbox[HOME_MAILBOX_SIZE]; /* mailbox */
    /* 0x25D4 */ Haniwa_c haniwa;                   /* gyroid info */
    /* 0x2678 */ mHm_goki_c goki;                   /* cockroach info */
    /* 0x2684 */ u32 music_box[2];                  /* bitfield of inserted music */
    /* 0x268C */ u8 unk_286C[36];                   /* unused? */
} mHm_hs_c;

/* sizeof(mHm_cottage_c) == 0x8C8 */
typedef struct home_cottage_s {
    /* 0x000 */ mHm_wf_c unused_wall_floor; /* Has wallpaper & flooring bounds checks in sChk_CheckSaveData_Cattage */
    /* 0x002 */ u8 unk_2[2];                /* struct/array that is two bytes long, maybe another wall floor? */
    /* 0x004 */ u8 unk_4;                   /* direct copy in agb_to_gc_cottage, GBA only? */
    /* 0x005 */ u8 unk_5;                   /* direct copy in agb_to_gc_cottage, GBA only? */
    /* 0x008 */ mHm_flr_c room;             /* Cottage room */
    /* 0x8B0 */ mHm_goki_c goki;            /* Cottage cockroaches */
    /* 0x8BC */ u32 music_box[2];           /* Cottage music storage... separate from main home? */
} mHm_cottage_c;

#ifdef __cplusplus
}
#endif

#endif
