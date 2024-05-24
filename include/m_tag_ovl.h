#ifndef M_TAG_OVL_H
#define M_TAG_OVL_H

#include "types.h"
#include "m_tag_ovl_h.h"
#include "m_submenu_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mTG_TAG_NUM 4
#define mTG_TAG_STR_LEN 16
#define mTG_TAG_SEL_STRING_LEN 35

#define mTG_TAG_FLAG_EDGE_FOOT_SELECT (1 << 0)

enum {
    mTG_TYPE_NONE,
    mTG_TYPE_FIELD_DEFAULT,
    mTG_TYPE_FIELD_DEFAULT_BURY,
    mTG_TYPE_FIELD_LETTER,
    mTG_TYPE_FIELD_LETTER_BURY,
    mTG_TYPE_FIELD_HUKUBUKURO,
    mTG_TYPE_FIELD_HUKUBUKURO_BURY,
    mTG_TYPE_FIELD_RELEASE,
    mTG_TYPE_CATCH_ITEM,
    mTG_TYPE_FIELD_PLANT,
    mTG_TYPE_FIELD_PLANT_JOB,
    mTG_TYPE_PRESENT_ITEM,
    mTG_TYPE_ROOM_DEFAULT,
    mTG_TYPE_ROOM_WALL,
    mTG_TYPE_ROOM_CARPET,
    mTG_TYPE_ROOM_LETTER,
    mTG_TYPE_ROOM_HUKUBUKURO,
    mTG_TYPE_OTHER_LETTER,
    mTG_TYPE_OTHER_HUKUBUKURO,
    mTG_TYPE_DEF_RMAIL,
    mTG_TYPE_ROOM_RMAIL,
    mTG_TYPE_DEF_RMAIL_PRE,
    mTG_TYPE_DEF_SMAIL,
    mTG_TYPE_ROOM_SMAIL,
    mTG_TYPE_DEF_SMAIL_PRE,
    mTG_TYPE_DUMP_MAIL,
    mTG_TYPE_MONEY_SACK,
    mTG_TYPE_QUEST_ITEM,
    mTG_TYPE_SELL_ITEM,
    mTG_TYPE_GIVE_ITEM,
    mTG_TYPE_SEND_MAIL,
    mTG_TYPE_FIELD_TICKET,
    mTG_TYPE_FIELD_TICKET_BURY,
    mTG_TYPE_ROOM_TICKET,
    mTG_TYPE_CATCH_TICKET,
    mTG_TYPE_PUTIN_ITEM,
    mTG_TYPE_SHRINE_ITEM,
    mTG_TYPE_HANIWA_ITEM,
    mTG_TYPE_HANIWA_PUT_ITEM,
    mTG_TYPE_HANIWA_PRICE,
    mTG_TYPE_HANIWA_GET_ITEM,
    mTG_TYPE_ORDER_ITEM,
    mTG_TYPE_CP_DELETE,
    mTG_TYPE_CP_DELETE2,
    mTG_TYPE_FIELD_MAIL_MARK,
    mTG_TYPE_DUMP_MAIL_MARK_CONF,
    mTG_TYPE_FIELD_MAIL_MARK2,
    mTG_TYPE_CPACK_MAIL_MARK,
    mTG_TYPE_SELL_ALL_ITEM,
    mTG_TYPE_MUSIC_SELECT,
    mTG_TYPE_MUSIC_SELECT_MANY,
    mTG_TYPE_FIELD_WISP,
    mTG_TYPE_CATCH_WISP,
    mTG_TYPE_TAG_HAND_OVER_CURATOR,
    mTG_TYPE_TAG_NW_SELECT,
    mTG_TYPE_TAG_NW_MY_ROOM,
    mTG_TYPE_TAG_NW_OT_ROOM,
    mTG_TYPE_TAG_NW_UG_ROOM,
    mTG_TYPE_TAG_NW_MR_SEL_STICK,
    mTG_TYPE_TAG_NW_OR_SEL_STICK,
    mTG_TYPE_TAG_NW_SEL_PUT,
    mTG_TYPE_TAG_NW_SEL_STK_PATTERN,
    mTG_TYPE_TAG_REMOVE,
    mTG_TYPE_TAG_PUT_ALL,
    mTG_TYPE_TAG_PUT_CHK,
    mTG_TYPE_FIELD_LETTERS,
    mTG_TYPE_FIELD_LETTERS_BURY,
    mTG_TYPE_ROOM_LETTERS,
    mTG_TYPE_OTHER_LETTERS,
    mTG_TYPE_CHANGE_ORIGINAL,
    mTG_TYPE_TAISOU_CARD,
    mTG_TYPE_DUMP_ITEM,
    mTG_TYPE_FIELD_SIGN,
    mTG_TYPE_FIELD_BALLOON,
    mTG_TYPE_TAG_NW_SELECT_CHANGE,
    mTG_TYPE_TAG_NW_SELECT_PUT,
    mTG_TYPE_76,
    mTG_TYPE_TAG_PASSWORD_ITEM,

    mTG_TYPE_NUM
};

enum {
    mTG_TABLE_ITEM,
    mTG_TABLE_MAIL,
    mTG_TABLE_MONEY,
    mTG_TABLE_PLAYER,
    mTG_TABLE_BG,
    mTG_TABLE_MBOX,
    mTG_TABLE_HANIWA,
    mTG_TABLE_COLLECT,
    mTG_TABLE_WCHANGE,
    mTG_TABLE_CPMAIL,
    mTG_TABLE_CPMAIL_WC,
    mTG_TABLE_CPMAIL_TI,
    mTG_TABLE_CPEDIT,
    mTG_TABLE_CPEDIT_END,
    mTG_TABLE_CATALOG,
    mTG_TABLE_CATALOG_WC,
    mTG_TABLE_MUSIC_MAIN,
    mTG_TABLE_NEEDLEWORK,
    mTG_TABLE_CPORIGINAL,
    mTG_TABLE_INVENTORY_WC_ORG,
    mTG_TABLE_CPORIGINAL_NW,
    mTG_TABLE_CPORIGINAL_WC,
    mTG_TABLE_CPORIGINAL_TI,
    mTG_TABLE_GBA,
    mTG_TABLE_GBA_NW,
    mTG_TABLE_CARD,
    mTG_TABLE_GBA_NW2,

    mTG_TABLE_NUM
};

/* sizeof(mTG_tag_c) == 0xB4 */
typedef struct tag_s {
    u8 type;
    u8 arrow_dir;
    u8 str2_type;
    u8 flags;
    f32 _04[2];
    f32 base_pos[2];
    f32 body_scale[2];
    f32 arrow_scale[2];
    f32 body_ofs[2];
    f32 text_ofs[2];
    f32 _34;
    int table;
    int tag_col;
    int tag_row;
    f32 scale;
    u8 str0[mTG_TAG_SEL_STRING_LEN];
    u8 str1[mTG_TAG_SEL_STRING_LEN];
    u8 str2[mTG_TAG_SEL_STRING_LEN];
    u8 _B1[0xB4 - 0xB1];
} mTG_tag_c;

typedef void (*mTG_INIT_TAG_DATA_ITEM_WIN_PROC)(Submenu*);
typedef void (*mTG_CHG_TAG_FUNC_PROC)(Submenu*, int, int, int, f32, f32);
typedef void (*mTG_SET_HAND_POS_PROC)(Submenu*, f32*, int, int);
typedef void (*mTG_EXCHANGE_PROC)(Submenu*, mSM_MenuInfo_c*);
typedef Mail_c* (*mTG_GET_MAIL_POINTER_PROC)(Submenu*, mHD_Ovl_c*);
typedef int (*mTG_GET_TABLE_IDX_PROC)(mTG_tag_c*);

/* TODO */
struct tag_ovl_s {
    /* 0x000 */ int sel_tag_idx;
    /* 0x004 */ int ret_tag_idx;
    /* 0x008 */ mTG_tag_c tags[mTG_TAG_NUM];
    /* 0x2D8 */ mTG_SET_HAND_POS_PROC set_hand_pos_proc;
    /* 0x2DC */ mTG_EXCHANGE_PROC exchange_proc;
    /* 0x2E0 */ mTG_INIT_TAG_DATA_ITEM_WIN_PROC init_tag_data_item_win_proc;
    /* 0x2E4 */ mTG_CHG_TAG_FUNC_PROC chg_tag_func_proc;
    /* 0x2E8 */ mTG_GET_MAIL_POINTER_PROC get_mail_pointer_proc;
    /* 0x2EC */ mTG_GET_TABLE_IDX_PROC get_table_idx_proc;
    /* 0x2F0 */ s16 item_name_wait_time;
    /* 0x2F2 */ u8 _2F2[0x3C4 - 0x2F2];
};

extern int mTG_mark_main(Submenu*, mSM_MenuInfo_c*, int, int);
extern int mTG_mark_mainX(Submenu*, mSM_MenuInfo_c*, int, int, int, int);

extern void mTG_tag_ovl_construct(Submenu* submenu);
extern void mTG_tag_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
