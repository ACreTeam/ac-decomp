#include "m_tag_ovl.h"

#include "m_common_data.h"
#include "m_inventory_ovl.h"
#include "m_hand_ovl.h"
#include "m_cpmail_ovl.h"
#include "m_cporiginal_ovl.h"
#include "m_gba_ovl.h"
#include "m_needlework_ovl.h"
#include "m_catalog_ovl.h"
#include "m_font.h"
#include "_mem.h"
#include "m_lib.h"
#include "m_item_name.h"
#include "ac_my_room.h"
#include "m_needlework.h"
#include "m_haniwa_ovl.h"
#include "m_player_lib.h"
#include "m_warning_ovl.h"
#include "m_mailbox_ovl.h"
#include "m_music_ovl.h"
#include "m_mark_room.h"

static mTG_Ovl_c tag_ovl_data;

typedef struct tag_word_s {
    u8 str[mTG_TAG_STR_LEN];
    mSM_MOVE_PROC move_proc;
} mTG_tag_word_c;

typedef struct tag_data_s {
    mTG_tag_word_c** words; /* array of words for each line */
    int lines;              /* # of lines */
} mTG_tag_data_c;

typedef struct tag_table_data_s {
    s16 col_num;
    s16 row_num;
    s16* col_pos;
    s16* row_pos;
} mTG_tag_data_table_c;

/* columns */
static s16 mTG_item_col_pos[] = { -77, -53, -29, -5, 19 };
static s16 mTG_mail_col_pos[] = { 55, 79 };
static s16 mTG_money_col_pos[] = { 19 };
static s16 mTG_player_col_pos[] = { -59 };
static s16 mTG_bg_col_pos[] = { 19 };
static s16 mTG_mbox_col_pos[] = { -36, -12 };
static s16 mTG_haniwa_col_pos[] = { -35, -11, 13, 37 };
static s16 mTG_collect_col_pos[] = { -89, -65, -41, -17, 8, 32, 57, 81 };
static s16 mTG_wchange_col_pos[] = { 105 };
static s16 mTG_cpmail_col_pos[] = { -16, 8, 32, 56 };
static s16 mTG_cpmail_wc_col_pos[] = { 98 };
static s16 mTG_cpmail_ti_col_pos[] = { 24 };
static s16 mTG_cpedit_col_pos[] = { 20 };
static s16 mTG_cpedit_end_col_pos[] = { 20 };
static s16 mTG_catalog_col_pos[] = { 65 };
static s16 mTG_catalog_wc_col_pos[] = { 93 };
static s16 mTG_music_main_col_pos[] = { -100, -80, -60, -40, -20, 0, 20, 40, 60, 80, 100 };
static s16 mTG_needlework_col_pos[] = { -19, 19 };
static s16 mTG_cporiginal_col_pos[] = { 0, 32, 64 };
static s16 mTG_inventory_wc_org_col_pos[] = { -105 };
static s16 mTG_cporiginal_nw_col_pos[] = { -88, -56 };
static s16 mTG_cporiginal_wc_col_pos[] = { 102 };
static s16 mTG_cporiginal_ti_col_pos[] = { 32 };
static s16 mTG_gba_col_pos[] = { -97, -67, -37, -7 };
static s16 mTG_gba_nw_col_pos[] = { 48, 80 };
static s16 mTG_card_col_pos[] = { -45 };

/* rows */
static s16 mTG_item_line_pos[] = { -10, -34, -58 };
static s16 mTG_mail_line_pos[] = { 38, 14, -10, -34, -58 };
static s16 mTG_money_line_pos[] = { 18 };
static s16 mTG_player_line_pos[] = { 63 };
static s16 mTG_bg_line_pos[] = { -90 };
static s16 mTG_mbox_line_pos[] = { 39, 15, -9, -33, -57 };
static s16 mTG_haniwa_line_pos[] = { 46 };
static s16 mTG_collect_line_pos[] = { 42, 18, -6, -30, -54 };
static s16 mTG_wchange_line_pos[] = { 37, 0, -37 };
static s16 mTG_cpmail_wc_line_pos[] = { 50, 35, 20, 5, -10, -25, -40, -55 };
static s16 mTG_cpmail_ti_line_pos[] = { 71 };
static s16 mTG_cpedit_line_pos[] = { 50, 18, -14 };
static s16 mTG_cpedit_end_line_pos[] = { -49 };
static s16 mTG_catalog_line_pos[] = { 60, 42, 24, 6, -12, -30, -48 };
static s16 mTG_catalog_wc_line_pos[] = { 64, 48, 32, 16, 0, -16, -32, -48, -64 };
static s16 mTG_music_main_line_pos[] = { 25, 5, -15, -35, -55 };
static s16 mTG_needlework_line_pos[] = { 50, 16, -18, -52 };
static s16 mTG_cporiginal_line_pos[] = { 44, 15, -14, -43 };
static s16 mTG_inventory_wc_org_line_pos[] = { 0 };
static s16 mTG_cporiginal_nw_line_pos[] = { 45, 16, -13, -42 };
static s16 mTG_cporiginal_wc_line_pos[] = { 53, 40, 24, 10, -4, -18, -34, -47 };
static s16 mTG_cporiginal_ti_line_pos[] = { 74 };
static s16 mTG_gba_line_pos[] = { 6, -25 };
static s16 mTG_gba_nw_line_pos[] = { 40, 11, -18, -47 };
static s16 mTG_card_line_pos[] = { -10 };

/* Data table */
static mTG_tag_data_table_c mTG_table_data[] = {
    { 5, 3, mTG_item_col_pos, mTG_item_line_pos },                         /* mTG_TABLE_ITEM */
    { 2, 5, mTG_mail_col_pos, mTG_mail_line_pos },                         /* mTG_TABLE_MAIL */
    { 1, 1, mTG_money_col_pos, mTG_money_line_pos },                       /* mTG_TABLE_MONEY */
    { 1, 1, mTG_player_col_pos, mTG_player_line_pos },                     /* mTG_TABLE_PLAYER */
    { 1, 1, mTG_bg_col_pos, mTG_bg_line_pos },                             /* mTG_TABLE_BG */
    { 2, 5, mTG_mbox_col_pos, mTG_mbox_line_pos },                         /* mTG_TABLE_MBOX */
    { 4, 1, mTG_haniwa_col_pos, mTG_haniwa_line_pos },                     /* mTG_TABLE_HANIWA */
    { 8, 5, mTG_collect_col_pos, mTG_collect_line_pos },                   /* mTG_TABLE_COLLECT */
    { 1, 3, mTG_wchange_col_pos, mTG_wchange_line_pos },                   /* mTG_TABLE_WCHANGE */
    { 4, 5, mTG_cpmail_col_pos, mTG_mail_line_pos },                       /* mTG_TABLE_CPMAIL */
    { 1, 8, mTG_cpmail_wc_col_pos, mTG_cpmail_wc_line_pos },               /* mTG_TABLE_CPMAIL_WC */
    { 1, 1, mTG_cpmail_ti_col_pos, mTG_cpmail_ti_line_pos },               /* mTG_TABLE_CPMAIL_TI */
    { 1, 3, mTG_cpedit_col_pos, mTG_cpedit_line_pos },                     /* mTG_TABLE_CPEDIT */
    { 1, 1, mTG_cpedit_end_col_pos, mTG_cpedit_end_line_pos },             /* mTG_TABLE_CPEDIT_END */
    { 1, 7, mTG_catalog_col_pos, mTG_catalog_line_pos },                   /* mTG_TABLE_CATALOG */
    { 1, 9, mTG_catalog_wc_col_pos, mTG_catalog_wc_line_pos },             /* mTG_TABLE_CATALOG_WC */
    { 11, 5, mTG_music_main_col_pos, mTG_music_main_line_pos },            /* mTG_TABLE_MUSIC_MAIN */
    { 2, 4, mTG_needlework_col_pos, mTG_needlework_line_pos },             /* mTG_TABLE_NEEDLEWORK */
    { 3, 4, mTG_cporiginal_col_pos, mTG_cporiginal_line_pos },             /* mTG_TABLE_CPORIGINAL */
    { 1, 1, mTG_inventory_wc_org_col_pos, mTG_inventory_wc_org_line_pos }, /* mTG_TABLE_INVENTORY_WC_ORG */
    { 2, 4, mTG_cporiginal_nw_col_pos, mTG_cporiginal_nw_line_pos },       /* mTG_TABLE_CPORIGINAL_NW */
    { 1, 8, mTG_cporiginal_wc_col_pos, mTG_cporiginal_wc_line_pos },       /* mTG_TABLE_CPORIGINAL_WC */
    { 1, 1, mTG_cporiginal_ti_col_pos, mTG_cporiginal_ti_line_pos },       /* mTG_TABLE_CPORIGINAL_TI */
    { 4, 2, mTG_gba_col_pos, mTG_gba_line_pos },                           /* mTG_TABLE_GBA */
    { 2, 4, mTG_gba_nw_col_pos, mTG_gba_nw_line_pos },                     /* mTG_TABLE_GBA_NW */
    { 1, 1, mTG_card_col_pos, mTG_card_line_pos },                         /* mTG_TABLE_CARD */
    { 2, 4, mTG_gba_nw_col_pos, mTG_gba_nw_line_pos },                     /* mTG_TABLE_GBA_NW2 */
};

static u8 str_omikuji[7] = "fortune";
static u8 str_happy_room[7] = "the HRA";
static u8 postoffice_str[15] = "the post office";
static u8 mother_str[4] = "home";
static u8 str_otodokemono[12] = "Delivery for";
static u8 str_otegami[9] = "letter to";
static u8 str_title0[5] = "to\xD3  ";
static u8 str_title1[5] = "from\xD3";
static u8 str_title2[5] = "'s   ";
static u8 str_title3[5] = "for\xD3 ";
static u8 str_title4[5] = "the\xD3 ";

static void mTG_present_open_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_nw_select_this_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_give_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_sell_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_sell_all_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_get_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_dump_mail_mark_exe_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_mailbox_change_mail_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_cpmail_change_mail_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_dump_mail_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_dump_item_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_send_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_rewrite_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_stick_select_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_carpet_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_cover_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_putin_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_music_listen_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_music_takeout_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_plant_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_field_put_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_room_put_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_put_all_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_dump_mail_mark_conf_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_next_open_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_next_open_needlework_sel_stick_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_next_open_needlework_sel_put_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_free_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_catch_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_password_item_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_write_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_priceset_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_present_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_show_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_cancel_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_read_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_take_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_m100_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_m1000_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_m10000_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_1catch_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_order_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_bury_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_release_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_fly_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_hukubukuro_open_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_cp_data_delete_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_nw_room_put_manekin_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_nw_stk_pat_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_tag_remove_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_nw_room_put_umbrella_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_nw_st_umbrella_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_nw_st_wear_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_change_original_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_drop_proc(Submenu*, mSM_MenuInfo_c*);

static mTG_tag_word_c mTG_tag_word_akeru = {
    "Open            ",
    &mTG_present_open_proc,
};

static mTG_tag_word_c mTG_tag_word_ageru = {
    "Give            ",
    &mTG_give_proc,
};

static mTG_tag_word_c mTG_tag_word_itadaku = {
    "Take it         ",
    &mTG_get_proc,
};

static mTG_tag_word_c mTG_tag_word_dump_item = {
    "Yes             ",
    &mTG_dump_item_proc,
};

static mTG_tag_word_c mTG_tag_word_field_sign = {
    "Erect           ",
    &mTG_field_put_proc,
};

static mTG_tag_word_c mTG_tag_word_dump_mail = {
    "Yes             ",
    &mTG_dump_mail_proc,
};

static mTG_tag_word_c mTG_tag_word_sell = {
    "Sell            ",
    &mTG_sell_proc,
};

static mTG_tag_word_c mTG_tag_word_sell_all = {
    "Sell All        ",
    &mTG_sell_all_proc,
};

static mTG_tag_word_c mTG_tag_word_okuru = {
    "Send            ",
    &mTG_send_proc,
};

static mTG_tag_word_c mTG_tag_word_kakinaosu = {
    "Rewrite         ",
    &mTG_rewrite_proc,
};

static mTG_tag_word_c mTG_tag_word_kabeniharu = {
    "Put on Wall     ",
    &mTG_cover_proc,
};

static mTG_tag_word_c mTG_tag_word_korewoireru = {
    "Put Away        ",
    &mTG_putin_proc,
};

static mTG_tag_word_c mTG_tag_word_zimenniueru = {
    "Plant           ",
    &mTG_plant_proc,
};

static mTG_tag_word_c mTG_tag_word_zimennioku = {
    "Drop            ",
    &mTG_field_put_proc,
};

static mTG_tag_word_c mTG_tag_word_suteru = {
    "Throw Away      ",
    &mTG_next_open_proc,
};

static mTG_tag_word_c mTG_tag_word_tada = {
    "Give Away       ",
    &mTG_free_proc,
};

static mTG_tag_word_c mTG_tag_word_tukamu = {
    "Grab            ",
    &mTG_catch_proc,
};

static mTG_tag_word_c mTG_tag_word_tegamiwokaku = {
    "Write Letter    ",
    &mTG_write_proc,
};

static mTG_tag_word_c mTG_tag_word_nedanwotukeru = {
    "Set Price       ",
    &mTG_priceset_proc,
};

static mTG_tag_word_c mTG_tag_word_present = {
    "Present         ",
    &mTG_present_proc,
};

static mTG_tag_word_c mTG_tag_word_miserudake = {
    "Display         ",
    &mTG_show_proc,
};

static mTG_tag_word_c mTG_tag_word_yameru = {
    "Quit            ",
    &mTG_cancel_proc,
};

static mTG_tag_word_c mTG_tag_word_heyanioku = {
    "Drop            ",
    &mTG_room_put_proc,
};

static mTG_tag_word_c mTG_tag_word_yukanisiku = {
    "Spread on Floor ",
    &mTG_carpet_proc,
};

static mTG_tag_word_c mTG_tag_word_yomu = {
    "Read            ",
    &mTG_read_proc,
};

static mTG_tag_word_c mTG_tag_word_watasu = {
    "Give            ",
    &mTG_take_proc,
};

static mTG_tag_word_c mTG_tag_word_100 = {
    "100             ",
    &mTG_m100_proc,
};

static mTG_tag_word_c mTG_tag_word_1000 = {
    "1000            ",
    &mTG_m1000_proc,
};

static mTG_tag_word_c mTG_tag_word_10000 = {
    "10000           ",
    &mTG_m10000_proc,
};

static mTG_tag_word_c mTG_tag_word_okane = {
    "Price\xD3:\xD3\xD3\xD3\xD3\xD3\xD3\xD3  ",
    NULL,
};

static mTG_tag_word_c mTG_tag_word_beru = {
    "Bells           ",
    NULL,
};

static mTG_tag_word_c mTG_tag_word_osameru = {
    "Give            ",
    &mTG_putin_proc,
};

static mTG_tag_word_c mTG_tag_word_zenbutukamu = {
    "Grab All        ",
    &mTG_catch_proc,
};

static mTG_tag_word_c mTG_tag_word_1maitukamu = {
    "Grab One        ",
    &mTG_1catch_proc,
};

static mTG_tag_word_c mTG_tag_word_1tamatukamu = {
    "Grab            ",
    &mTG_1catch_proc,
};

static mTG_tag_word_c mTG_tag_word_order = {
    "Order           ",
    &mTG_order_proc,
};

static mTG_tag_word_c mTG_tag_word_zimenniumeru = {
    "Bury            ",
    &mTG_bury_proc,
};

static mTG_tag_word_c mTG_tag_word_nigasu = {
    "Release         ",
    &mTG_release_proc,
};

static mTG_tag_word_c mTG_tag_word_fly = {
    "Let Go          ",
    &mTG_fly_proc,
};

static mTG_tag_word_c mTG_tag_word_akeru2 = {
    "Open            ",
    &mTG_hukubukuro_open_proc,
};

static mTG_tag_word_c mTG_tag_word_kesu = {
    "????            ",
    &mTG_next_open_proc,
};

static mTG_tag_word_c mTG_tag_word_hai = {
    "Yes             ",
    &mTG_cp_data_delete_proc,
};

static mTG_tag_word_c mTG_tag_word_iie = {
    "No              ",
    &mTG_cancel_proc,
};

static mTG_tag_word_c mTG_tag_word_dump_mail_mark_conf = {
    "Throw All Away  ",
    &mTG_dump_mail_mark_conf_proc,
};

static mTG_tag_word_c mTG_tag_word_dump_mail_mark_exe = {
    "Yes             ",
    &mTG_dump_mail_mark_exe_proc,
};

static mTG_tag_word_c mTG_tag_word_mailbox_change_mail = {
    "Copy All        ",
    &mTG_mailbox_change_mail_proc,
};

static mTG_tag_word_c mTG_tag_word_cpmail_change_mail = {
    "Swap            ",
    &mTG_cpmail_change_mail_proc,
};

static mTG_tag_word_c mTG_tag_word_music_listen = {
    "Listen          ",
    &mTG_music_listen_proc,
};

static mTG_tag_word_c mTG_tag_word_music_takeout = {
    "Take out        ",
    &mTG_music_takeout_proc,
};

static mTG_tag_word_c mTG_tag_word_music_takeout_all = {
    "Take out all    ",
    &mTG_music_takeout_proc,
};

static mTG_tag_word_c mTG_tag_word_hand_over_curator = {
    "Give            ",
    &mTG_give_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_select_this = {
    "Use             ",
    &mTG_nw_select_this_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_select_put = {
    "Drop            ",
    &mTG_nw_select_this_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_select_change = {
    "Swap            ",
    &mTG_nw_select_this_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_st_wear = {
    "Use on Clothes  ",
    &mTG_nw_st_wear_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_st_umbrella = {
    "Use on Umbrella ",
    &mTG_nw_st_umbrella_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_cover = {
    "Use on Walls    ",
    &mTG_stick_select_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_carpet = {
    "Use on Floor    ",
    &mTG_stick_select_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_catch = {
    "Grab            ",
    &mTG_catch_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_mr_sel_stick = {
    "Use             ",
    &mTG_next_open_needlework_sel_stick_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_or_sel_stick = {
    "Use             ",
    &mTG_next_open_needlework_sel_stick_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_sel_put = {
    "Drop            ",
    &mTG_next_open_needlework_sel_put_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_put_umbrella = {
    "Drop as Umbrella",
    &mTG_nw_room_put_umbrella_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_put_wear = {
    "Drop as Clothes ",
    &mTG_nw_room_put_manekin_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_stk_pat_nrml = {
    "Basic Paste     ",
    &mTG_nw_stk_pat_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_stk_pat_turn = {
    "Mix it up       ",
    &mTG_nw_stk_pat_proc,
};

static mTG_tag_word_c mTG_tag_word_remove = {
    "Remove          ",
    &mTG_tag_remove_proc,
};

static mTG_tag_word_c mTG_tag_word_put_all = {
    "Drop All        ",
    &mTG_put_all_proc,
};

static mTG_tag_word_c mTG_tag_word_put_chk = {
    "That's Fine     ",
    &mTG_drop_proc,
};

static mTG_tag_word_c mTG_tag_word_never_mind = {
    "Never mind      ",
    &mTG_cancel_proc,
};

static mTG_tag_word_c mTG_tag_word_change_original = {
    "Swap            ",
    &mTG_change_original_proc,
};

static mTG_tag_word_c mTG_tag_word_password_item = {
    "Give            ",
    &mTG_password_item_proc,
};

static u8 mTG_tag_str_suteruno[13] = "Throw it out?";
static u8 mTG_tag_str_hontoni[6] = "??????";
static u8 mTG_tag_str_iidesuka[6] = "??????";
static u8 mTG_tag_str_put_chk1[11] = "You'll lose";
static u8 mTG_tag_str_put_chk2[12] = "that design.";

// clang-format off
static u8 mTG_catalog_str[][mCL_TAG_STR_SIZE] = {
    "Furniture ",
    "Wallpaper ",
    "Carpet    ",
    "Clothing  ",
    "Items     ",
    "Stationery",
    "Gyroids   ",
    "Fossils   ",
    "Music     ",
};
// clang-format on

static mTG_tag_word_c* mTG_field_default[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_zimennioku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_default_bury[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_zimennioku,
    &mTG_tag_word_zimenniumeru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_letter[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_tegamiwokaku,
    &mTG_tag_word_zimennioku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_letter_bury[] = {
    &mTG_tag_word_tukamu,       &mTG_tag_word_tegamiwokaku, &mTG_tag_word_zimennioku,
    &mTG_tag_word_zimenniumeru, &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_sign[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_field_sign,
    &mTG_tag_word_suteru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_balloon[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_fly,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_hukubukuro[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_akeru2,
    &mTG_tag_word_zimennioku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_hukubukuro_bury[] = {
    &mTG_tag_word_tukamu,       &mTG_tag_word_akeru2, &mTG_tag_word_zimennioku,
    &mTG_tag_word_zimenniumeru, &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_release[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_nigasu,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_catch_item[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_plant[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_zimennioku,
    &mTG_tag_word_zimenniueru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_plant_job[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_zimenniueru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_present_item[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_akeru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_room_default[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_heyanioku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_room_wall[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_heyanioku,
    &mTG_tag_word_kabeniharu,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_room_carpet[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_heyanioku,
    &mTG_tag_word_yukanisiku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_room_letter[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_tegamiwokaku,
    &mTG_tag_word_heyanioku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_room_hukubukuro[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_akeru2,
    &mTG_tag_word_heyanioku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_other_letter[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_tegamiwokaku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_other_hukubukuro[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_akeru2,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_def_rmail[] = {
    &mTG_tag_word_yomu,
    &mTG_tag_word_tukamu,
    &mTG_tag_word_suteru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_room_rmail[] = {
    &mTG_tag_word_yomu,
    &mTG_tag_word_tukamu,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_def_rmail_pre[] = {
    &mTG_tag_word_yomu,
    &mTG_tag_word_tukamu,
    &mTG_tag_word_present,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_def_smail[] = {
    &mTG_tag_word_kakinaosu,
    &mTG_tag_word_tukamu,
    &mTG_tag_word_suteru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_room_smail[] = {
    &mTG_tag_word_kakinaosu,
    &mTG_tag_word_tukamu,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_def_smail_pre[] = {
    &mTG_tag_word_kakinaosu,
    &mTG_tag_word_tukamu,
    &mTG_tag_word_present,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_dump_mail[] = {
    &mTG_tag_word_dump_mail,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_dump_item[] = {
    &mTG_tag_word_dump_item,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_money_sack3[] = {
    &mTG_tag_word_100,
    &mTG_tag_word_1000,
    &mTG_tag_word_10000,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_quest_item[] = {
    &mTG_tag_word_watasu,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_sell_item[] = {
    &mTG_tag_word_sell,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_give_item[] = {
    &mTG_tag_word_ageru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_send_mail[] = {
    &mTG_tag_word_okuru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_ticket[] = {
    &mTG_tag_word_zenbutukamu,
    &mTG_tag_word_1maitukamu,
    &mTG_tag_word_zimennioku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_ticket_bury[] = {
    &mTG_tag_word_zenbutukamu,  &mTG_tag_word_1maitukamu, &mTG_tag_word_zimennioku,
    &mTG_tag_word_zimenniumeru, &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_room_ticket[] = {
    &mTG_tag_word_zenbutukamu,
    &mTG_tag_word_1maitukamu,
    &mTG_tag_word_heyanioku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_catch_ticket[] = {
    &mTG_tag_word_zenbutukamu,
    &mTG_tag_word_1maitukamu,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_putin_item[] = {
    &mTG_tag_word_korewoireru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_shrine_item[] = {
    &mTG_tag_word_osameru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_haniwa_item[] = {
    &mTG_tag_word_tukamu,     &mTG_tag_word_tada,   &mTG_tag_word_nedanwotukeru,
    &mTG_tag_word_miserudake, &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_haniwa_put_item[] = {
    &mTG_tag_word_tada,
    &mTG_tag_word_nedanwotukeru,
    &mTG_tag_word_miserudake,
};

static mTG_tag_word_c* mTG_haniwa_get_item[] = {
    &mTG_tag_word_itadaku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_haniwa_price[] = {
    &mTG_tag_word_okane,
    &mTG_tag_word_beru,
};

static mTG_tag_word_c* mTG_order_item[] = {
    &mTG_tag_word_order,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_cp_delete[] = {
    &mTG_tag_word_yameru,
    &mTG_tag_word_kesu,
};

static mTG_tag_word_c* mTG_cp_delete2[] = {
    &mTG_tag_word_iie,
    &mTG_tag_word_hai,
};

static mTG_tag_word_c* mTG_field_mail_mark[] = {
    &mTG_tag_word_dump_mail_mark_conf,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_dump_mail_mark_conf[] = {
    &mTG_tag_word_dump_mail_mark_exe,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_mail_mark2[] = {
    &mTG_tag_word_mailbox_change_mail,
    &mTG_tag_word_dump_mail_mark_conf,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_cpack_mail_mark[] = {
    &mTG_tag_word_cpmail_change_mail,
    &mTG_tag_word_dump_mail_mark_conf,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_sell_all_item[] = {
    &mTG_tag_word_sell_all,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_music_select[] = {
    &mTG_tag_word_music_listen,
    &mTG_tag_word_music_takeout,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_music_select_many[] = {
    &mTG_tag_word_music_takeout_all,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_wisp[] = {
    &mTG_tag_word_zenbutukamu,
    &mTG_tag_word_1tamatukamu,
    &mTG_tag_word_nigasu,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_catch_wisp[] = {
    &mTG_tag_word_zenbutukamu,
    &mTG_tag_word_1tamatukamu,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_hand_over_curator[] = {
    &mTG_tag_word_hand_over_curator,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_select[] = {
    &mTG_tag_word_nw_select_this,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_my_room[] = {
    &mTG_tag_word_nw_catch,
    &mTG_tag_word_nw_mr_sel_stick,
    &mTG_tag_word_nw_sel_put,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_ot_room[] = {
    &mTG_tag_word_nw_catch,
    &mTG_tag_word_nw_or_sel_stick,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_ug_room[] = {
    &mTG_tag_word_nw_catch,
    &mTG_tag_word_nw_mr_sel_stick,
    &mTG_tag_word_nw_sel_put,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_mr_sel_stick[] = {
    &mTG_tag_word_nw_st_wear, &mTG_tag_word_nw_st_umbrella, &mTG_tag_word_nw_cover,
    &mTG_tag_word_nw_carpet,  &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_sel_put[] = {
    &mTG_tag_word_nw_put_wear,
    &mTG_tag_word_nw_put_umbrella,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_or_sel_stick[] = {
    &mTG_tag_word_nw_st_wear,
    &mTG_tag_word_nw_st_umbrella,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_sel_stk_pattern[] = {
    &mTG_tag_word_nw_stk_pat_nrml,
    &mTG_tag_word_nw_stk_pat_turn,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_remove[] = {
    &mTG_tag_word_remove,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_put_all[] = {
    &mTG_tag_word_put_all,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_put_chk[] = {
    &mTG_tag_word_put_chk,
    &mTG_tag_word_never_mind,
};

static mTG_tag_word_c* mTG_field_letters[] = {
    &mTG_tag_word_tukamu,     &mTG_tag_word_1maitukamu, &mTG_tag_word_tegamiwokaku,
    &mTG_tag_word_zimennioku, &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_letters_bury[] = {
    &mTG_tag_word_tukamu,     &mTG_tag_word_1maitukamu,   &mTG_tag_word_tegamiwokaku,
    &mTG_tag_word_zimennioku, &mTG_tag_word_zimenniumeru, &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_room_letters[] = {
    &mTG_tag_word_tukamu,    &mTG_tag_word_1maitukamu, &mTG_tag_word_tegamiwokaku,
    &mTG_tag_word_heyanioku, &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_other_letters[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_1maitukamu,
    &mTG_tag_word_tegamiwokaku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_change_original[] = {
    &mTG_tag_word_change_original,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_taisou_card[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_suteru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_select_change[] = {
    &mTG_tag_word_nw_select_change,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_select_put[] = {
    &mTG_tag_word_nw_select_put,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_password_item[] = {
    &mTG_tag_word_password_item,
    &mTG_tag_word_yameru,
};

static mTG_tag_data_c mTG_label_table[] = {
    { NULL, 0 },                                                             /* mTG_TYPE_NONE */
    { mTG_field_default, ARRAY_COUNT(mTG_field_default) },                   /* mTG_TYPE_FIELD_DEFAULT */
    { mTG_field_default_bury, ARRAY_COUNT(mTG_field_default_bury) },         /* mTG_TYPE_FIELD_DEFAULT_BURY */
    { mTG_field_letter, ARRAY_COUNT(mTG_field_letter) },                     /* mTG_TYPE_FIELD_LETTER */
    { mTG_field_letter_bury, ARRAY_COUNT(mTG_field_letter_bury) },           /* mTG_TYPE_FIELD_LETTER_BURY */
    { mTG_field_hukubukuro, ARRAY_COUNT(mTG_field_hukubukuro) },             /* mTG_TYPE_FIELD_HUKUBUKURO */
    { mTG_field_hukubukuro_bury, ARRAY_COUNT(mTG_field_hukubukuro_bury) },   /* mTG_TYPE_FIELD_HUKUBUKURO_BURY */
    { mTG_field_release, ARRAY_COUNT(mTG_field_release) },                   /* mTG_TYPE_FIELD_RELEASE */
    { mTG_catch_item, ARRAY_COUNT(mTG_catch_item) },                         /* mTG_TYPE_CATCH_ITEM */
    { mTG_field_plant, ARRAY_COUNT(mTG_field_plant) },                       /* mTG_TYPE_FIELD_PLANT */
    { mTG_field_plant_job, ARRAY_COUNT(mTG_field_plant_job) },               /* mTG_TYPE_FIELD_PLANT_JOB */
    { mTG_present_item, ARRAY_COUNT(mTG_present_item) },                     /* mTG_TYPE_PRESENT_ITEM */
    { mTG_room_default, ARRAY_COUNT(mTG_room_default) },                     /* mTG_TYPE_ROOM_DEFAULT */
    { mTG_room_wall, ARRAY_COUNT(mTG_room_wall) },                           /* mTG_TYPE_ROOM_WALL */
    { mTG_room_carpet, ARRAY_COUNT(mTG_room_carpet) },                       /* mTG_TYPE_ROOM_CARPET */
    { mTG_room_letter, ARRAY_COUNT(mTG_room_letter) },                       /* mTG_TYPE_ROOM_LETTER */
    { mTG_room_hukubukuro, ARRAY_COUNT(mTG_room_hukubukuro) },               /* mTG_TYPE_ROOM_HUKUBUKURO */
    { mTG_other_letter, ARRAY_COUNT(mTG_other_letter) },                     /* mTG_TYPE_OTHER_LETTER */
    { mTG_other_hukubukuro, ARRAY_COUNT(mTG_other_hukubukuro) },             /* mTG_TYPE_OTHER_HUKUBUKURO */
    { mTG_def_rmail, ARRAY_COUNT(mTG_def_rmail) },                           /* mTG_TYPE_DEF_RMAIL */
    { mTG_room_rmail, ARRAY_COUNT(mTG_room_rmail) },                         /* mTG_TYPE_ROOM_RMAIL */
    { mTG_def_rmail_pre, ARRAY_COUNT(mTG_def_rmail_pre) },                   /* mTG_TYPE_DEF_RMAIL_PRE */
    { mTG_def_smail, ARRAY_COUNT(mTG_def_smail) },                           /* mTG_TYPE_DEF_SMAIL */
    { mTG_room_smail, ARRAY_COUNT(mTG_room_smail) },                         /* mTG_TYPE_ROOM_SMAIL */
    { mTG_def_smail_pre, ARRAY_COUNT(mTG_def_smail_pre) },                   /* mTG_TYPE_DEF_SMAIL_PRE */
    { mTG_dump_mail, ARRAY_COUNT(mTG_dump_mail) },                           /* mTG_TYPE_DUMP_MAIL */
    { mTG_money_sack3, ARRAY_COUNT(mTG_money_sack3) },                       /* mTG_TYPE_MONEY_SACK */
    { mTG_quest_item, ARRAY_COUNT(mTG_quest_item) },                         /* mTG_TYPE_QUEST_ITEM */
    { mTG_sell_item, ARRAY_COUNT(mTG_sell_item) },                           /* mTG_TYPE_SELL_ITEM */
    { mTG_give_item, ARRAY_COUNT(mTG_give_item) },                           /* mTG_TYPE_GIVE_ITEM */
    { mTG_send_mail, ARRAY_COUNT(mTG_send_mail) },                           /* mTG_TYPE_SEND_MAIL */
    { mTG_field_ticket, ARRAY_COUNT(mTG_field_ticket) },                     /* mTG_TYPE_FIELD_TICKET */
    { mTG_field_ticket_bury, ARRAY_COUNT(mTG_field_ticket_bury) },           /* mTG_TYPE_FIELD_TICKET_BURY */
    { mTG_room_ticket, ARRAY_COUNT(mTG_room_ticket) },                       /* mTG_TYPE_ROOM_TICKET */
    { mTG_catch_ticket, ARRAY_COUNT(mTG_catch_ticket) },                     /* mTG_TYPE_CATCH_TICKET */
    { mTG_putin_item, ARRAY_COUNT(mTG_putin_item) },                         /* mTG_TYPE_PUTIN_ITEM */
    { mTG_shrine_item, ARRAY_COUNT(mTG_shrine_item) },                       /* mTG_TYPE_SHRINE_ITEM */
    { mTG_haniwa_item, ARRAY_COUNT(mTG_haniwa_item) },                       /* mTG_TYPE_HANIWA_ITEM */
    { mTG_haniwa_put_item, ARRAY_COUNT(mTG_haniwa_put_item) },               /* mTG_TYPE_HANIWA_PUT_ITEM */
    { mTG_haniwa_price, ARRAY_COUNT(mTG_haniwa_price) },                     /* mTG_TYPE_HANIWA_PRICE */
    { mTG_haniwa_get_item, ARRAY_COUNT(mTG_haniwa_get_item) },               /* mTG_TYPE_HANIWA_GET_ITEM */
    { mTG_order_item, ARRAY_COUNT(mTG_order_item) },                         /* mTG_TYPE_ORDER_ITEM */
    { mTG_cp_delete, ARRAY_COUNT(mTG_cp_delete) },                           /* mTG_TYPE_CP_DELETE */
    { mTG_cp_delete2, ARRAY_COUNT(mTG_cp_delete2) },                         /* mTG_TYPE_CP_DELETE2 */
    { mTG_field_mail_mark, ARRAY_COUNT(mTG_field_mail_mark) },               /* mTG_TYPE_FIELD_MAIL_MARK */
    { mTG_dump_mail_mark_conf, ARRAY_COUNT(mTG_dump_mail_mark_conf) },       /* mTG_TYPE_DUMP_MAIL_MARK_CONF */
    { mTG_field_mail_mark2, ARRAY_COUNT(mTG_field_mail_mark2) },             /* mTG_TYPE_FIELD_MAIL_MARK2 */
    { mTG_cpack_mail_mark, ARRAY_COUNT(mTG_cpack_mail_mark) },               /* mTG_TYPE_CPACK_MAIL_MARK */
    { mTG_sell_all_item, ARRAY_COUNT(mTG_sell_all_item) },                   /* mTG_TYPE_SELL_ALL_ITEM */
    { mTG_music_select, ARRAY_COUNT(mTG_music_select) },                     /* mTG_TYPE_MUSIC_SELECT */
    { mTG_music_select_many, ARRAY_COUNT(mTG_music_select_many) },           /* mTG_TYPE_MUSIC_SELECT_MANY */
    { mTG_field_wisp, ARRAY_COUNT(mTG_field_wisp) },                         /* mTG_TYPE_FIELD_WISP */
    { mTG_catch_wisp, ARRAY_COUNT(mTG_catch_wisp) },                         /* mTG_TYPE_CATCH_WISP */
    { mTG_tag_hand_over_curator, ARRAY_COUNT(mTG_tag_hand_over_curator) },   /* mTG_TYPE_TAG_HAND_OVER_CURATOR */
    { mTG_tag_nw_select, ARRAY_COUNT(mTG_tag_nw_select) },                   /* mTG_TYPE_TAG_NW_SELECT */
    { mTG_tag_nw_my_room, ARRAY_COUNT(mTG_tag_nw_my_room) },                 /* mTG_TYPE_TAG_NW_MY_ROOM */
    { mTG_tag_nw_ot_room, ARRAY_COUNT(mTG_tag_nw_ot_room) },                 /* mTG_TYPE_TAG_NW_OT_ROOM */
    { mTG_tag_nw_ug_room, ARRAY_COUNT(mTG_tag_nw_ug_room) },                 /* mTG_TYPE_TAG_NW_UG_ROOM */
    { mTG_tag_nw_mr_sel_stick, ARRAY_COUNT(mTG_tag_nw_mr_sel_stick) },       /* mTG_TYPE_TAG_NW_MR_SEL_STICK */
    { mTG_tag_nw_or_sel_stick, ARRAY_COUNT(mTG_tag_nw_or_sel_stick) },       /* mTG_TYPE_TAG_NW_OR_SEL_STICK */
    { mTG_tag_nw_sel_put, ARRAY_COUNT(mTG_tag_nw_sel_put) },                 /* mTG_TYPE_TAG_NW_SEL_PUT */
    { mTG_tag_nw_sel_stk_pattern, ARRAY_COUNT(mTG_tag_nw_sel_stk_pattern) }, /* mTG_TYPE_TAG_NW_SEL_STK_PATTERN */
    { mTG_tag_remove, ARRAY_COUNT(mTG_tag_remove) },                         /* mTG_TYPE_TAG_REMOVE */
    { mTG_tag_put_all, ARRAY_COUNT(mTG_tag_put_all) },                       /* mTG_TYPE_TAG_PUT_ALL */
    { mTG_tag_put_chk, ARRAY_COUNT(mTG_tag_put_chk) },                       /* mTG_TYPE_TAG_PUT_CHK */
    { mTG_field_letters, ARRAY_COUNT(mTG_field_letters) },                   /* mTG_TYPE_FIELD_LETTERS */
    { mTG_field_letters_bury, ARRAY_COUNT(mTG_field_letters_bury) },         /* mTG_TYPE_FIELD_LETTERS_BURY */
    { mTG_room_letters, ARRAY_COUNT(mTG_room_letters) },                     /* mTG_TYPE_ROOM_LETTERS */
    { mTG_other_letters, ARRAY_COUNT(mTG_other_letters) },                   /* mTG_TYPE_OTHER_LETTERS */
    { mTG_change_original, ARRAY_COUNT(mTG_change_original) },               /* mTG_TYPE_CHANGE_ORIGINAL */
    { mTG_taisou_card, ARRAY_COUNT(mTG_taisou_card) },                       /* mTG_TYPE_TAISOU_CARD */
    { mTG_dump_item, ARRAY_COUNT(mTG_dump_item) },                           /* mTG_TYPE_DUMP_ITEM */
    { mTG_field_sign, ARRAY_COUNT(mTG_field_sign) },                         /* mTG_TYPE_FIELD_SIGN */
    { mTG_field_balloon, ARRAY_COUNT(mTG_field_balloon) },                   /* mTG_TYPE_FIELD_BALLOON */
    { mTG_tag_nw_select_change, ARRAY_COUNT(mTG_tag_nw_select_change) },     /* mTG_TYPE_TAG_NW_SELECT_CHANGE */
    { mTG_tag_nw_select_put, ARRAY_COUNT(mTG_tag_nw_select_put) },           /* mTG_TYPE_TAG_NW_SELECT_PUT */
    { NULL, 0 },                                                             /* mTG_TYPE_76 */
    { mTG_tag_password_item, ARRAY_COUNT(mTG_tag_password_item) },           /* mTG_TYPE_TAG_PASSWORD_ITEM */
};

static void mTG_init_tag_data_item_win(Submenu*);

static int mTG_check_hand_condition(Submenu* submenu) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    int res = FALSE;

    if (hand_ovl->info.item == EMPTY_NO && mMl_check_not_used_mail(&hand_ovl->info.mail) == TRUE) {
        res = TRUE;
    }

    return res;
}

static f32 mTG_set_hand_pos_offset(Submenu* submenu, int table) {
    f32 res = 0.0f;

    if (submenu->overlay->needlework_ovl != NULL) {
        int nw_type = submenu->overlay->menu_info[mSM_OVL_NEEDLEWORK].data0;

        if (nw_type == 0) {
            res = 21.0f;
        } else if (nw_type == 1 && table == mTG_TABLE_NEEDLEWORK) {
            res = 46.0f;
        }
    } else if (submenu->overlay->inventory_ovl != NULL) {
        if (submenu->overlay->menu_info[mSM_OVL_INVENTORY].data0 == mSM_IV_OPEN_CPMAIL && table == mTG_TABLE_MAIL) {
            res = -155.0f;
        }
    }

    return res;
}

static void mTG_set_hand_pos(Submenu* submenu, f32* pos, int table, int idx) {
    mTG_tag_data_table_c* data_p = &mTG_table_data[table];
    f32 ofs = mTG_set_hand_pos_offset(submenu, table);
    int col = idx % data_p->col_num;
    int row;
    f32 pos_x = data_p->col_pos[col];

    pos_x += ofs;
    pos[0] = pos_x;

    row = idx / data_p->col_num;
    pos[1] = data_p->row_pos[row];
}

static int mTG_get_tag_idx(Submenu* submenu, int type) {
    int idx = submenu->overlay->tag_ovl->sel_tag_idx;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[idx];
    int i;

    for (i = idx; i >= 0; i--) {
        if (tag->type == type) {
            return i;
        }

        tag--;
    }

    return -1;
}

static int mTG_return_tag_init(Submenu* submenu, int ret_type, int type) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag;
    int ret_idx = mTG_get_tag_idx(submenu, ret_type);
    int i;

    if (ret_idx >= 0) {
        if (ret_idx == 0) {
            tag_ovl->ret_tag_idx = -1;
        } else {
            tag_ovl->ret_tag_idx = ret_idx;
        }

        if (type == mTG_TYPE_NONE) {
            tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];

            for (i = tag_ovl->sel_tag_idx - tag_ovl->ret_tag_idx; i != 0; i--) {
                tag->base_pos[0] += tag->body_ofs[0];
                tag->base_pos[1] += tag->body_ofs[1];
                tag->body_ofs[0] = 0.0f;
                tag->body_ofs[1] = 0.0f;
                tag--;
            }
        }
    }

    return ret_idx;
}

static u16 mTG_get_item_name_wait_time(mTG_tag_c* tag) {
    u16 time;

    tag->scale = 0.0f;
    if (tag->table == mTG_TABLE_CATALOG_WC) {
        time = 16;
    } else {
        time = 20;
    }

    return time;
}

static void mTG_return_tag_func(Submenu* submenu, mTG_Ovl_c* tag_ovl, mTG_tag_c* tag) {
    mTG_tag_c* now_tag = tag;
    int count = 0;
    int tag_num = tag_ovl->sel_tag_idx - tag_ovl->ret_tag_idx;
    int i;

    for (i = tag_num; i != 0; i--) {
        now_tag->scale -= 0.125f;
        if (now_tag->scale <= 0.0f) {
            if (now_tag->type == mTG_TYPE_NONE) {
                tag_ovl->item_name_wait_time = mTG_get_item_name_wait_time(now_tag);
            }

            now_tag->scale = 0.0f;
            count++;
        }

        now_tag--;
    }

    if (count == tag_num) {
        if (tag_ovl->ret_tag_idx == -1) {
            tag_ovl->ret_tag_idx = 0;
        }

        tag_ovl->sel_tag_idx = tag_ovl->ret_tag_idx;
        if (tag_ovl->sel_tag_idx == 0) {
            mTG_init_tag_data_item_win(submenu);
        }
    }
}

static int mTG_quest_disp_up_check(mTG_tag_c* tag) {
    int res = FALSE;

    if ((tag->table == mTG_TABLE_ITEM && tag->tag_row == 0) || (tag->table == mTG_TABLE_MAIL && tag->tag_row == 2)) {
        res = TRUE;
    }

    return res;
}

static int mTG_quest_disp_low_check(mTG_tag_c* tag) {
    int res = FALSE;

    if ((tag->table == mTG_TABLE_MAIL && tag->tag_row == 1)) {
        res = TRUE;
    }

    return res;
}

typedef struct tag_win_arrow_ofs_s {
    f32 ofs[2];
    f32 scale[2];
} mTG_win_arrow_ofs_c;

typedef struct tag_win_data_s {
    f32 _00[2];
    f32 _08[2];
    f32 _10;
    f32 _14;
    f32 _18;
    f32 _1C[2];
    f32 _24[2];
    mTG_win_arrow_ofs_c* arrow_offset;
} mTG_win_data_c;

enum {
    mTG_WIN_TYPE_ITEM,
    mTG_WIN_TYPE_SELECT,
    mTG_WIN_TYPE_SELECT2,

    mTG_WIN_TYPE_NUM
};

static void mTG_set_tag_win_scale_p(mTG_tag_c* tag, int win_type, f32 x, f32 y) {
    static mTG_win_arrow_ofs_c tag_win_data_pix_arrow_offset_item = {
        { -3.5f, -3.5f },
        { -7.0f, 3.5f },
    };

    static mTG_win_arrow_ofs_c tag_win_data_pix_arrow_offset_quest = {
        { -1.0f, 21.0f },
        { -11.0f, 5.0f },
    };

    static mTG_win_arrow_ofs_c tag_win_data_pix_arrow_offset_quest_up = {
        { -13.0f, 4.0f },
        { -6.0f, 10.0f },
    };

    static mTG_win_arrow_ofs_c tag_win_data_pix_arrow_offset_quest_low = {
        { -13.0f, 56.0f },
        { -6.0f, -2.0f },
    };

    static mTG_win_arrow_ofs_c tag_win_data_pix_arrow_offset_select = {
        { 6.125f, 15.75f },
        { 0.875f, 26.25f },
    };

    static mTG_win_data_c tag_win_data_pix[] = {
        {
            { 0.2972973f, 0.8125f },
            { -64.75f, 14.0f },
            0.875f,
            21.0f,
            84.0f,
            { 8.75f, -4.375f },
            { 4.375f, -2.625f },
            &tag_win_data_pix_arrow_offset_item,
        },
        {
            { 0.5714286f, 0.43243244f },
            { -61.25f, 64.75f },
            0.875f,
            31.5f,
            42.0f,
            { 22.75f, -14.875f },
            { 5.25f, -15.75f },
            &tag_win_data_pix_arrow_offset_select,
        },
    };

    mTG_win_data_c* win_data = &tag_win_data_pix[win_type];
    mTG_win_arrow_ofs_c* arrow_data = win_data->arrow_offset;
    int i;

    tag->_04[0] = (x - win_data->_14) / win_data->_18;

    if (y != 0.0f) {
        tag->_04[1] = (y - 28.0f) / 42.0f;
    } else {
        tag->_04[1] = tag->_04[0];
    }

    if (win_type == mTG_WIN_TYPE_SELECT) {
        if (mTG_quest_disp_up_check(tag) == TRUE) {
            arrow_data = &tag_win_data_pix_arrow_offset_quest_up;
        } else if (mTG_quest_disp_low_check(tag) == TRUE) {
            arrow_data = &tag_win_data_pix_arrow_offset_quest_low;
        }
    }

    tag->_34 = win_data->_10;
    for (i = 0; i < 2; i++) {
        tag->body_scale[i] = win_data->_00[i] + tag->_04[i] * (1.0f - win_data->_00[i]);
        tag->arrow_scale[i] = 1.0f;
        tag->text_ofs[i] = win_data->_1C[i] + win_data->_24[i] * tag->_04[i] + win_data->_08[i] * tag->body_scale[i];
        tag->body_ofs[i] =
            (arrow_data->ofs[i] + arrow_data->scale[i] * tag->_04[i]) - win_data->_08[i] * tag->body_scale[i];
    }
}

static int mTG_get_table_idx(mTG_tag_c* tag) {
    int idx = tag->tag_col + tag->tag_row * mTG_table_data[tag->table].col_num;

    if (idx >= 0) {
        return idx;
    }

    return 0;
}

static int mTG_check_edge_right_item(mTG_tag_c* tag) {
    f32 edge;
    int res = FALSE;

    if (tag->str2_type == 0) {
        edge = 64.75f;
    } else {
        edge = 92.0f;
    }

    if (tag->base_pos[0] + tag->body_ofs[0] + tag->body_scale[0] * edge <= 146.0f) {
        res = TRUE;
    }

    return res;
}

static void mTG_calc_right_edge_select(mTG_tag_c* tag, f32* right_edge) {
    f32 margin = tag->body_scale[0] * 122.5f * 0.5f;

    *right_edge = tag->base_pos[0] + tag->body_ofs[0] + margin;
}

static int mTG_check_edge_right_select(mTG_tag_c* tag, f32* right_edge) {
    f32 margin = tag->body_scale[0] * 122.5f * 0.5f;
    int res = FALSE;

    *right_edge = (tag->base_pos[0] + tag->body_ofs[0] + margin) - 134.0f;

    if (*right_edge <= 0.0f) {
        res = TRUE;
    }

    return res;
}

static int mTG_check_edge_foot_select(mTG_tag_c* tag) {
    f32 margin = (tag->body_scale[1] * 129.5f) * 0.5f;
    f32 tmp;
    int res = FALSE;

    tmp = (tag->base_pos[1] + tag->body_ofs[1]) - margin;
    tag->flags &= ~mTG_TAG_FLAG_EDGE_FOOT_SELECT;
    if (tmp - 3.0f >= -120.0f) {
        tag->flags |= mTG_TAG_FLAG_EDGE_FOOT_SELECT;
        res = TRUE;
    }

    return res;
}

static int mTG_get_max_col_width_data(mTG_tag_word_c** tag_word, int lines) {
    int max_col_width = 0;
    int i;

    if (tag_word != NULL) {
        for (i = 0; i < lines; i++) {
            int len = mMl_strlen(tag_word[i]->str, mTG_TAG_STR_LEN, CHAR_SPACE);
            int width = mFont_GetStringWidth(tag_word[i]->str, len, TRUE);

            if (width > max_col_width) {
                max_col_width = width;
            }
        }
    }

    return max_col_width;
}

static void mTG_get_col_width_and_line_select(mTG_tag_c* tag, mTG_tag_data_c* tag_data, f32* max_width,
                                              f32* max_height) {
    *max_width = mTG_get_max_col_width_data(tag_data->words, tag_data->lines);

    switch (tag->type) {
        case mTG_TYPE_CP_DELETE2: {
            *max_height = (f32)(tag_data->lines + 2) * 16.0f;
            *max_width = mFont_GetStringWidth(mTG_tag_str_iidesuka, sizeof(mTG_tag_str_iidesuka), TRUE);
            break;
        }

        case mTG_TYPE_DUMP_MAIL:
        case mTG_TYPE_DUMP_MAIL_MARK_CONF:
        case mTG_TYPE_DUMP_ITEM: {
            f32 width;

            *max_height = (f32)(tag_data->lines + 1) * 16.0f;
            width = mFont_GetStringWidth(mTG_tag_str_suteruno, sizeof(mTG_tag_str_suteruno), TRUE);

            if (width > *max_width) {
                *max_width = width;
            }
            break;
        }

        case mTG_TYPE_TAG_PUT_CHK: {
            *max_width = mFont_GetStringWidth(mTG_tag_str_put_chk1, sizeof(mTG_tag_str_put_chk1), TRUE);
            *max_height = (f32)(tag_data->lines + 2) * 16.0f;
            break;
        }

        default: {
            *max_height = (f32)tag_data->lines * 16.0f;
            break;
        }
    }
}

static Mail_c* mTG_get_mail_pointer(Submenu* submenu, mHD_Ovl_c* hand_ovl) {
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    int table;
    int idx;
    int page;

    if (hand_ovl != NULL) {
        table = hand_ovl->info.hold_tbl;
        idx = hand_ovl->info.hold_idx;
        page = hand_ovl->info.catch_pg;
    } else {
        mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];

        table = tag->table;
        idx = mTG_get_table_idx(tag);

        if (cpmail_ovl != NULL) {
            page = cpmail_ovl->page_order[0];
        } else {
            page = 0;
        }
    }

    switch (table) {
        case mTG_TABLE_CPMAIL:
            return &cpmail_ovl->card_mail->mail[page][idx];
        case mTG_TABLE_MBOX:
            return &Common_Get(now_home)->mailbox[idx];
        default:
            return &Now_Private->mail[idx];
    }
}

static int mTG_strcat(u8* str0, u8* str1, int str0_max, int str1_max) {
    int str0_len = mMl_strlen(str0, str0_max, CHAR_SPACE);
    int str1_len = mMl_strlen(str1, str1_max, CHAR_SPACE);

    if ((str0_len + str1_len) > str0_max) {
        str1_len -= (str0_len + str1_len) - str0_max;
    }

    if (str1_len > 0) {
        memcpy(&str0[str0_len], str1, str1_len);
        str0_len += str1_len;
    }

    return str0_len;
}

static int mTG_strcpy(u8* dst, u8* src, int dst_max, int src_max) {
    int src_len;

    mem_clear(dst, dst_max, CHAR_SPACE);

    src_len = mMl_strlen(src, src_max, CHAR_SPACE);
    if (src_len < dst_max) {
        dst_max = src_len;
    }

    memcpy(dst, src, dst_max);
    return dst_max;
}

static int mTG_strcat_color(u8* str, u8* src, int str_max, int src_max, rgba_t* color) {
    /* 0x7F 0x05 0x00 0x00 0x00 0x00 */
    static u8 font_color_base[] = { CHAR_CONTROL_CODE, mFont_CONT_CODE_COLOR, 0, 0, 0, 0 };
    int str_len = mMl_strlen(str, str_max, CHAR_SPACE);
    int src_len = mMl_strlen(src, src_max, CHAR_SPACE);

    if ((str_max - src_len) - str_len > 1) {
        int col_len = mTG_strcat(str, font_color_base, str_max, sizeof(font_color_base));

        if ((col_len + src_len) > str_max) {
            src_len -= (col_len + src_len) - str_max;
        }

        str[col_len - 4] = color->r;
        str[col_len - 3] = color->g;
        str[col_len - 2] = color->b;
        str[col_len - 1] = (u8)src_len;
        memcpy(str + col_len, src, src_len);
        str_len = col_len + src_len;
    }

    return str_len;
}

typedef struct tag_str_info_s {
    u8 str[mTG_TAG_SEL_STRING_LEN];
    int str_len;
    int color_idx;
} mTG_str_info_c;

enum {
    mTG_MAIL_TYPE_NONE,
    mTG_MAIL_TYPE_FROM,
    mTG_MAIL_TYPE_FROM_THE,
    mTG_MAIL_TYPE_FROM2,
    mTG_MAIL_TYPE_FROM_S,
    mTG_MAIL_TYPE_FROM3,

    mTG_MAIL_TYPE_NUM
};

enum {
    mTG_MAIL_NAME_COLOR_RED,
    mTG_MAIL_NAME_COLOR_VIOLET,
    mTG_MAIL_NAME_COLOR_GREEN,
    mTG_MAIL_NAME_COLOR_PURPLE,
    mTG_MAIL_NAME_COLOR_INDIGO,
    mTG_MAIL_NAME_COLOR_PINK,
    mTG_MAIL_NAME_COLOR_BLACK,

    mTG_MAIL_NAME_COLOR_NUM
};

static int mTG_init_tag_data_item_win_sub_mail_item_mail(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    int type = mTG_MAIL_TYPE_FROM;

    mTG_strcpy(str_infos[1].str, mail->header.sender.personalID.player_name, mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;

    if (mail->header.recipient.type == mMl_NAME_TYPE_MUSEUM) {
        str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_VIOLET;
        tag->str2_type = 4;
        type = mTG_MAIL_TYPE_FROM_THE;
    } else if (mail->header.sender.type == mMl_NAME_TYPE_MUSEUM) {
        str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_GREEN;
        tag->str2_type = 3;
        type = mTG_MAIL_TYPE_FROM2;
    } else {
        str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_VIOLET;
        tag->str2_type = 2;
    }

    return type;
}

static int mTG_init_tag_data_item_win_sub_mail_item_xmas(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, mNpc_GetNpcWorldNameP(SP_NPC_SANTA), mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_PURPLE;
    tag->str2_type = 5;

    return mTG_MAIL_TYPE_FROM;
}

static int mTG_init_tag_data_item_win_sub_mail_item_tanukiti(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, mNpc_GetNpcWorldNameP(SP_NPC_SHOP_MASTER), mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_INDIGO;
    tag->str2_type = 6;

    return mTG_MAIL_TYPE_FROM;
}

static int mTG_init_tag_data_item_win_sub_mail_item_tunekiti(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, mNpc_GetNpcWorldNameP(SP_NPC_BROKER), mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_INDIGO;
    tag->str2_type = 6;

    return mTG_MAIL_TYPE_FROM;
}

static int mTG_init_tag_data_item_win_sub_mail_item_mother(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, mother_str, mTG_TAG_SEL_STRING_LEN, sizeof(mother_str));
    str_infos[1].str_len = sizeof(mother_str);
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_INDIGO;
    tag->str2_type = 7;

    return mTG_MAIL_TYPE_FROM2;
}

static int mTG_init_tag_data_item_win_sub_mail_item_omikuji(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, mNpc_GetNpcWorldNameP(SP_NPC_EV_MIKO), mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_INDIGO;
    tag->str2_type = 9;

    return mTG_MAIL_TYPE_FROM_S;
}

static int mTG_init_tag_data_item_win_sub_mail_item_happy(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, str_happy_room, mTG_TAG_SEL_STRING_LEN, sizeof(str_happy_room));
    str_infos[1].str_len = sizeof(str_happy_room);
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_GREEN;
    tag->str2_type = 11;

    return mTG_MAIL_TYPE_FROM;
}

static int mTG_init_tag_data_item_win_sub_mail_item_snowman(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, mNpc_GetNpcWorldNameP(ETC_SNOWMAN_BALL_A), mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_PURPLE;
    tag->str2_type = 5;

    return mTG_MAIL_TYPE_FROM;
}

static int mTG_init_tag_data_item_win_sub_mail_item_angler(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, mNpc_GetNpcWorldNameP(SP_NPC_ANGLER), mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_PURPLE;
    tag->str2_type = 8;

    return mTG_MAIL_TYPE_FROM;
}

static int mTG_init_tag_data_item_win_sub_mail_item_postoffice(mTG_tag_c* tag, mTG_str_info_c* str_infos,
                                                               Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, postoffice_str, mTG_TAG_SEL_STRING_LEN, sizeof(postoffice_str));
    str_infos[1].str_len = sizeof(postoffice_str);
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_GREEN;
    tag->str2_type = 10;

    return mTG_MAIL_TYPE_FROM2;
}

static int mTG_init_tag_data_item_win_sub_mail_item_sp_npc(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, mail->header.sender.personalID.player_name, mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_PURPLE;
    tag->str2_type = 5;

    return mTG_MAIL_TYPE_FROM;
}

// clang-format off
static rgba_t str_color[] = {
    { 205,  40,  40, 255 },
    { 100,  65, 195, 255 },
    {  60, 150,  65, 255 },
    {  54,  20, 255, 255 },
    {  60,  50, 155, 255 },
    { 225,  30, 220, 255 },
    {   0,   0,   0, 255 },
};
// clang-format on

static void mTG_init_tag_data_item_win_sub_mail_item_set_string(mTG_tag_c* tag, mTG_str_info_c* str_infos, int type) {
    switch (type) {
        case mTG_MAIL_TYPE_FROM: {
            mTG_strcat_color(tag->str0, str_infos[0].str, mTG_TAG_SEL_STRING_LEN, str_infos[0].str_len,
                             &str_color[str_infos[0].color_idx]);
            mTG_strcat(tag->str1, str_title1, mTG_TAG_SEL_STRING_LEN, sizeof(str_title1));
            mTG_strcat_color(tag->str1, str_infos[1].str, mTG_TAG_SEL_STRING_LEN, str_infos[1].str_len,
                             &str_color[str_infos[1].color_idx]);

            break;
        }

        case mTG_MAIL_TYPE_FROM_THE: {
            mTG_strcat(tag->str0, str_title4, mTG_TAG_SEL_STRING_LEN, sizeof(str_title4));
            mTG_strcat_color(tag->str0, str_infos[0].str, mTG_TAG_SEL_STRING_LEN, str_infos[0].str_len,
                             &str_color[str_infos[0].color_idx]);
            mTG_strcat(tag->str1, str_title1, mTG_TAG_SEL_STRING_LEN, sizeof(str_title1));
            mTG_strcat_color(tag->str1, str_infos[1].str, mTG_TAG_SEL_STRING_LEN, str_infos[1].str_len,
                             &str_color[str_infos[1].color_idx]);

            break;
        }

        case mTG_MAIL_TYPE_FROM2: {
            mTG_strcat_color(tag->str0, str_infos[0].str, mTG_TAG_SEL_STRING_LEN, str_infos[0].str_len,
                             &str_color[str_infos[0].color_idx]);
            mTG_strcat(tag->str1, str_title1, mTG_TAG_SEL_STRING_LEN, sizeof(str_title1));
            mTG_strcat_color(tag->str1, str_infos[1].str, mTG_TAG_SEL_STRING_LEN, str_infos[1].str_len,
                             &str_color[str_infos[1].color_idx]);

            break;
        }

        case mTG_MAIL_TYPE_FROM_S: {
            mTG_strcat_color(tag->str0, str_infos[0].str, mTG_TAG_SEL_STRING_LEN, str_infos[0].str_len,
                             &str_color[str_infos[0].color_idx]);
            mTG_strcat(tag->str0, str_title2, mTG_TAG_SEL_STRING_LEN, sizeof(str_title2));
            mTG_strcat(tag->str1, str_title1, mTG_TAG_SEL_STRING_LEN, sizeof(str_title1));
            mTG_strcat_color(tag->str1, str_infos[1].str, mTG_TAG_SEL_STRING_LEN, str_infos[1].str_len,
                             &str_color[str_infos[1].color_idx]);

            break;
        }

        case mTG_MAIL_TYPE_FROM3: {
            mTG_strcat_color(tag->str0, str_infos[0].str, mTG_TAG_SEL_STRING_LEN, str_infos[0].str_len,
                             &str_color[str_infos[0].color_idx]);
            mTG_strcat(tag->str1, str_title1, mTG_TAG_SEL_STRING_LEN, sizeof(str_title1));
            mTG_strcat_color(tag->str1, str_infos[1].str, mTG_TAG_SEL_STRING_LEN, str_infos[1].str_len,
                             &str_color[str_infos[1].color_idx]);

            break;
        }
    }
}

typedef int (*mTG_ITEM_WIN_SUB_MAIL_ITEM_PROC)(mTG_tag_c*, mTG_str_info_c*, Mail_c*);

static void mTG_init_tag_data_item_win_sub_mail_item(Submenu* submenu, mTG_tag_c* tag, Mail_c* mail,
                                                     mActor_name_t itemNo, int itemCond, int idx) {
    static mTG_ITEM_WIN_SUB_MAIL_ITEM_PROC proc[] = {
        &mTG_init_tag_data_item_win_sub_mail_item_mail,       &mTG_init_tag_data_item_win_sub_mail_item_xmas,
        &mTG_init_tag_data_item_win_sub_mail_item_tanukiti,   &mTG_init_tag_data_item_win_sub_mail_item_tunekiti,
        &mTG_init_tag_data_item_win_sub_mail_item_mother,     &mTG_init_tag_data_item_win_sub_mail_item_omikuji,
        &mTG_init_tag_data_item_win_sub_mail_item_happy,      &mTG_init_tag_data_item_win_sub_mail_item_tanukiti,
        &mTG_init_tag_data_item_win_sub_mail_item_snowman,    &mTG_init_tag_data_item_win_sub_mail_item_angler,
        &mTG_init_tag_data_item_win_sub_mail_item_postoffice, &mTG_init_tag_data_item_win_sub_mail_item_sp_npc,
    };
    static u8 present_str[7] = "Present";

    f32 scale = 0.875f;
    int win_type = mTG_WIN_TYPE_ITEM;
    int mail_type = mTG_MAIL_TYPE_NONE;
    mTG_str_info_c str_infos[3];
    int i;

    mem_clear(str_infos[0].str, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);
    mem_clear(str_infos[1].str, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);
    mem_clear(str_infos[2].str, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);

    if (itemNo == EMPTY_NO) {
        scale = 0.75f;
        win_type = mTG_WIN_TYPE_SELECT;
        mTG_strcpy(str_infos[0].str, mail->header.recipient.personalID.player_name, mTG_TAG_SEL_STRING_LEN,
                   PLAYER_NAME_LEN);
        str_infos[0].str_len = PLAYER_NAME_LEN;

        if (mail->content.mail_type == mMl_TYPE_MAIL && mail->header.recipient.type == mMl_NAME_TYPE_MUSEUM) {
            str_infos[0].color_idx = mTG_MAIL_NAME_COLOR_GREEN;
        } else {
            str_infos[0].color_idx = mTG_MAIL_NAME_COLOR_RED;
        }

        mail_type = (*proc[mail->content.mail_type])(tag, str_infos, mail);
    } else if (tag->table == mTG_TABLE_ITEM) {
        tag->str2_type = 0;
        win_type = mTG_WIN_TYPE_SELECT;

        /* Show quest item info */
        if ((itemCond & mPr_ITEM_COND_QUEST)) {
            u8 str0[mTG_TAG_SEL_STRING_LEN];
            u8 str1[mTG_TAG_SEL_STRING_LEN];

            mem_clear(str0, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);
            mem_clear(str1, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);

            if (mQst_GetToFromName(str0, str1, idx) == TRUE) {
                mTG_strcpy(str_infos[0].str, str0, mTG_TAG_SEL_STRING_LEN, mTG_TAG_SEL_STRING_LEN);
                str_infos[0].str_len = mTG_TAG_SEL_STRING_LEN;
                str_infos[0].color_idx = mTG_MAIL_NAME_COLOR_RED;

                mTG_strcpy(str_infos[1].str, str1, mTG_TAG_SEL_STRING_LEN, mTG_TAG_SEL_STRING_LEN);
                str_infos[1].str_len = mTG_TAG_SEL_STRING_LEN;
                str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_VIOLET;

                scale = 0.75f;
                mail_type = mTG_MAIL_TYPE_FROM3;
                tag->str2_type = 1;
            }
        }
    } else {
        tag->str2_type = 0;
    }

    if (tag->str2_type == 0) {
        if (itemCond == mPr_ITEM_COND_PRESENT) {
            mem_copy(tag->str0, present_str, sizeof(present_str));
        } else if (itemNo >= ITM_MY_ORG_UMBRELLA0 && itemNo <= ITM_MY_ORG_UMBRELLA7) {
            mem_copy(tag->str0, Now_Private->my_org[(itemNo - ITM_MY_ORG_UMBRELLA0) & 7].name,
                     mNW_ORIGINAL_DESIGN_NAME_LEN);
        } else {
            mIN_copy_name_str(tag->str0, itemNo);
        }

        win_type = mTG_WIN_TYPE_ITEM;
    }

    if (tag->str2_type != 0) {
        if (tag->str2_type == 1) {
            mTG_strcpy(tag->str2, str_otodokemono, mTG_TAG_SEL_STRING_LEN, sizeof(str_otodokemono));
        } else if (tag->str2_type == 9) {
            mTG_strcpy(tag->str2, str_omikuji, mTG_TAG_SEL_STRING_LEN, sizeof(str_omikuji));
        } else {
            mTG_strcpy(tag->str2, str_otegami, mTG_TAG_SEL_STRING_LEN, sizeof(str_otegami));
        }
    }

    mTG_init_tag_data_item_win_sub_mail_item_set_string(tag, str_infos, mail_type);

    {
        int str0_len = mMl_strlen(tag->str0, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);
        int str1_len = mMl_strlen(tag->str1, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);
        int str2_len = mMl_strlen(tag->str2, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);
        f32 width = mFont_GetStringWidth2(tag->str0, str0_len, TRUE);
        f32 str1_width = mFont_GetStringWidth2(tag->str1, str1_len, TRUE);
        f32 str2_width = mFont_GetStringWidth2(tag->str2, str2_len, TRUE);

        if (str1_width > width) {
            width = str1_width;
        }

        if (str2_width > width) {
            width = str2_width;
        }

        width *= scale;
        mTG_set_tag_win_scale_p(tag, win_type, width, 0.0f);
    }

    if (win_type == mTG_WIN_TYPE_SELECT && mTG_quest_disp_up_check(tag) == FALSE &&
        mTG_quest_disp_low_check(tag) == FALSE) {
        tag->body_ofs[1] += 8.0f;
    }

    if (mTG_check_edge_right_item(tag) == TRUE) {
        tag->arrow_dir = 1;
    } else {
        tag->body_ofs[0] *= -1.0f;
        tag->arrow_dir = 2;
    }

    submenu->overlay->tag_ovl->item_name_wait_time = mTG_get_item_name_wait_time(tag);
}

static void mTG_init_tag_data_set_base_pos(mTG_tag_c* tag) {
    switch (tag->table) {
        case mTG_TABLE_NEEDLEWORK:
            tag->base_pos[0] += -3.0f;
            tag->base_pos[1] += -7.0f;
            break;
        case mTG_TABLE_CPORIGINAL:
        case mTG_TABLE_CPORIGINAL_NW:
        case mTG_TABLE_GBA:
        case mTG_TABLE_GBA_NW:
        case mTG_TABLE_CARD:
            tag->base_pos[0] += -2.0f;
            tag->base_pos[1] += -5.0f;
            break;
        case mTG_TABLE_CATALOG_WC:
            tag->base_pos[0] += -8.75f;
            break;
        case mTG_TABLE_CPMAIL_WC:
            tag->base_pos[0] += -8.75f;
            break;
    }
}

static void mTG_init_tag_data_set_itemNo(mActor_name_t* itemNo, Mail_c** mail_pp, int* itemCond, Submenu* submenu,
                                         int idx) {
    switch (submenu->overlay->tag_ovl->tags[0].table) {
        case mTG_TABLE_ITEM:
            *itemNo = Now_Private->inventory.pockets[idx];
            *itemCond = mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, idx);
            break;
        case mTG_TABLE_PLAYER:
            *itemNo = Now_Private->equipment;
            break;
        case mTG_TABLE_HANIWA:
            *itemNo = Save_Get(homes[submenu->overlay->menu_info[mSM_OVL_HANIWA].data1]).haniwa.items[idx].item;
            break;
        case mTG_TABLE_COLLECT: {
            mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

            *itemNo = inv_ovl->set_collect_itemNo_proc(idx, inv_ovl->page_order[0]);
            break;
        }
        case mTG_TABLE_MAIL:
        case mTG_TABLE_MBOX:
        case mTG_TABLE_CPMAIL:
            *mail_pp = mTG_get_mail_pointer(submenu, NULL);
            break;
        default:
            *itemNo = EMPTY_NO;
            break;
    }
}

static void mTG_init_tag_data_catalog_win(Submenu* submenu, int idx) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int len;
    f32 width;

    mem_copy(tag->str0, mTG_catalog_str[idx], mCL_TAG_STR_SIZE);
    len = mMl_strlen(tag->str0, mTG_TAG_STR_LEN, CHAR_SPACE);
    width = mFont_GetStringWidth(tag->str0, len, TRUE);
    mTG_set_tag_win_scale_p(tag, mTG_WIN_TYPE_ITEM, width * 0.875f, 0.0f);
    tag->body_ofs[0] *= -1.0f;
    tag->arrow_dir = 2;
    submenu->overlay->tag_ovl->item_name_wait_time = mTG_get_item_name_wait_time(tag);
}

static void mTG_init_tag_data_cpmail_wc_win(Submenu* submenu, int folder_idx) {
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int len;

    mem_copy(tag->str0, cpmail_ovl->card_mail->folder_names[folder_idx], mCM_FOLDER_NAME_LEN);
    len = mMl_strlen(tag->str0, mCM_FOLDER_NAME_LEN, CHAR_SPACE);

    if (len <= 0 || cpmail_ovl->page_order[0] == tag->tag_row) {
        tag->arrow_dir = 0;
        tag->str2_type = 0;
    } else {
        f32 width = mFont_GetStringWidth(tag->str0, len, TRUE);

        mTG_set_tag_win_scale_p(tag, mTG_WIN_TYPE_ITEM, width * 0.875f, 0.0f);
        tag->str2_type = 0;
        tag->body_ofs[0] *= -1.0f;
        tag->arrow_dir = 2;
        submenu->overlay->tag_ovl->item_name_wait_time = mTG_get_item_name_wait_time(tag);
    }
}

static void mTG_init_tag_data_cporiginal_wc_win(Submenu* submenu) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int len;

    mem_copy(tag->str0, mCO_get_folder_name(submenu, tag->tag_row), mCO_FOLDER_NAME_LEN);
    len = mMl_strlen(tag->str0, mCO_FOLDER_NAME_LEN, CHAR_SPACE);

    if (len <= 0 || mCO_top_folder(submenu) == tag->tag_row) {
        tag->arrow_dir = 0;
        tag->str2_type = 0;
    } else {
        f32 width = mFont_GetStringWidth(tag->str0, len, TRUE);

        mTG_set_tag_win_scale_p(tag, mTG_WIN_TYPE_ITEM, width * 0.875f, 0.0f);
        tag->str2_type = 0;
        tag->body_ofs[0] *= -1.0f;
        tag->arrow_dir = 2;
        submenu->overlay->tag_ovl->item_name_wait_time = mTG_get_item_name_wait_time(tag);
    }
}

static void mTG_init_tag_data_needlework_win(Submenu* submenu, int idx) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int len;

    tag->str2_type = 0;
    if (tag->table == mTG_TABLE_CPORIGINAL) {
        int hide = mCO_check_hide_flg(submenu, mCO_top_folder(submenu), idx);

        if (hide) {
            tag->arrow_dir = 0;
            return;
        }
    } else {
        int hide = mNW_check_hide_flg(submenu, idx);

        if (hide) {
            tag->arrow_dir = 0;
            return;
        }
    }

    switch (tag->table) {
        case mTG_TABLE_CPORIGINAL:
            mem_copy(tag->str0, mCO_get_image_name(submenu, mCO_top_folder(submenu), idx),
                     mNW_ORIGINAL_DESIGN_NAME_LEN);
            break;
        case mTG_TABLE_GBA:
        case mTG_TABLE_CARD:
            mem_copy(tag->str0, mGB_get_image_name(submenu, idx), mNW_ORIGINAL_DESIGN_NAME_LEN);
            break;
        default:
            mem_copy(tag->str0, mNW_get_image_name(submenu, idx), mNW_ORIGINAL_DESIGN_NAME_LEN);
            break;
    }

    len = mMl_strlen(tag->str0, mNW_ORIGINAL_DESIGN_NAME_LEN, CHAR_SPACE);
    if (len <= 0) {
        tag->arrow_dir = 0;
    } else {
        f32 width = mFont_GetStringWidth(tag->str0, len, TRUE);

        mTG_set_tag_win_scale_p(tag, mTG_WIN_TYPE_ITEM, width * 0.875f, 0.0f);
        switch (tag->table) {
            case mTG_TABLE_CPORIGINAL:
            case mTG_TABLE_CPORIGINAL_NW:
            case mTG_TABLE_GBA:
            case mTG_TABLE_CARD:
                if (mTG_check_edge_right_item(tag) == TRUE) {
                    tag->arrow_dir = 1;
                } else {
                    tag->body_ofs[0] *= -1.0f;
                    tag->arrow_dir = 2;
                }
                break;
            default:
                tag->body_ofs[0] *= -1.0f;
                tag->arrow_dir = 2;
                break;
        }

        submenu->overlay->tag_ovl->item_name_wait_time = mTG_get_item_name_wait_time(tag);
    }
}

static void mTG_init_tag_data_item_win(Submenu* submenu) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    mActor_name_t itemNo = EMPTY_NO;
    Mail_c* mail = NULL;
    int itemCond = mPr_ITEM_COND_NORMAL;
    int idx = mTG_get_table_idx(tag);

    tag_ovl->sel_tag_idx = 0;
    mTG_set_hand_pos(submenu, tag->base_pos, tag->table, idx);
    mTG_init_tag_data_set_base_pos(tag);
    mem_clear(tag->str0, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);
    mem_clear(tag->str1, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);
    mem_clear(tag->str2, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);
    mTG_init_tag_data_set_itemNo(&itemNo, &mail, &itemCond, submenu, idx);

    if (itemNo != EMPTY_NO || (mail != NULL && mMl_check_not_used_mail(mail) == FALSE)) {
        mTG_init_tag_data_item_win_sub_mail_item(submenu, tag, mail, itemNo, itemCond, idx);
    } else {
        if (tag->table == mTG_TABLE_CATALOG_WC) {
            mTG_init_tag_data_catalog_win(submenu, idx);
        } else if (tag->table == mTG_TABLE_CPMAIL_WC) {
            mTG_init_tag_data_cpmail_wc_win(submenu, idx);
        } else if (tag->table == mTG_TABLE_CPORIGINAL_WC) {
            mTG_init_tag_data_cporiginal_wc_win(submenu);
        } else if (tag->table == mTG_TABLE_CPORIGINAL_NW || tag->table == mTG_TABLE_NEEDLEWORK ||
                   tag->table == mTG_TABLE_CPORIGINAL || tag->table == mTG_TABLE_GBA_NW ||
                   tag->table == mTG_TABLE_CARD || tag->table == mTG_TABLE_GBA_NW2 || tag->table == mTG_TABLE_GBA) {
            mTG_init_tag_data_needlework_win(submenu, idx);
        } else {
            tag->arrow_dir = 0;
        }
    }
}

static void mTG_init_tag_data_select_win_only(mTG_tag_c* tag, mTG_tag_data_c* data) {
    static f32 other_arrow_min_offset[][2] = {
        { 6.125f, 15.75f },
        { -4.375f, 15.75f },
        { 4.375f, -15.75f },
        { -6.125f, -15.75f },
    };

    static f32 other_arrow_offset_dis[][2] = {
        { 0.875f, 26.25f },
        { 0.875f, 26.25f },
        { -0.875f, -26.25f },
        { -0.875f, -26.25f },
    };

    f32 dist_right;
    f32 max_width;
    f32 max_height;
    int edge_right;
    int edge_foot;
    f32* min_ofs_p;
    f32* ofs_dis_p;
    int idx;
    f32 dir_x;
    f32 dir_y;

    mTG_get_col_width_and_line_select(tag, data, &max_width, &max_height);
    mTG_set_tag_win_scale_p(tag, mTG_WIN_TYPE_SELECT2, max_width * 0.875f, max_height * 0.875f);
    edge_right = mTG_check_edge_right_select(tag, &dist_right);
    edge_foot = mTG_check_edge_foot_select(tag);

    if (edge_right) {
        tag->arrow_dir = 1;
        dir_x = 1.0f;
        if (edge_foot) {
            idx = 0;
            dir_y = -1.0f;
        } else {
            idx = 2;
            dir_y = 1.0f;
        }
    } else {
        tag->arrow_dir = 2;
        dir_x = -1.0f;
        if (edge_foot) {
            idx = 1;
            dir_y = -1.0f;
        } else {
            idx = 3;
            dir_y = 1.0f;
        }
    }

    min_ofs_p = other_arrow_min_offset[idx];
    ofs_dis_p = other_arrow_offset_dis[idx];

    tag->body_ofs[0] = min_ofs_p[0] + ofs_dis_p[0] * tag->_04[0] + tag->body_scale[0] * 61.25f * dir_x;
    tag->body_ofs[1] = min_ofs_p[1] + ofs_dis_p[1] * tag->_04[1] + (tag->body_scale[1] * 64.75f - 6.0f) * dir_y;
}

typedef struct add_item_data_s {
    f32 down_min[2][2];
    f32 down_ofs[2][2];

    f32 up_min[2][2];
    f32 up_ofs[2][2];
} mTG_add_item_data_c;

static void mTG_init_tag_data_select_win_after_item(mTG_tag_c* tag, mTG_tag_c* item_tag, mTG_tag_data_c* tag_data) {
    // clang-format off
    static mTG_add_item_data_c tag_add_item_data[] = {
        {
            { {  27.125f,  1.750f }, {  54.250f,  1.750f } }, /* down_min */
            { {  27.125f, -1.750f }, {  54.250f, -1.750f } }, /* down_ofs */

            { { -29.750f,  6.125f }, { -28.875f,  8.750f } }, /* up_min */
            { { -29.750f, -6.125f }, { -28.875f, -8.750f } }, /* up_ofs */
        },
        {
            { {  52.500f,  4.375f }, {  39.375f,  0.000f } },
            { {  52.500f, -4.375f }, {  39.375f,  0.000f } },
            
            { { -27.125f,  7.000f }, { -28.000f,  8.750f } },
            { { -27.125f, -7.000f }, { -28.000f, -8.750f } },
        },
    };
    // clang-format on

    int left_flag;
    mTG_add_item_data_c* data_p;
    f32 scale_x;
    f32 scale_y;
    f32 dist_right;
    f32 max_width;
    f32 max_height;
    int tmp;
    int idx;

    mTG_get_col_width_and_line_select(tag, tag_data, &max_width, &max_height);
    mTG_set_tag_win_scale_p(tag, mTG_WIN_TYPE_SELECT2, max_width * 0.875f, max_height * 0.875f);

    left_flag = FALSE;
    if (item_tag->body_ofs[0] < 0.0f) {
        left_flag = TRUE;
    }

    if (item_tag->str2_type != 0) {
        scale_x = 68.0f;
        scale_y = 184.0f;
        data_p = &tag_add_item_data[1];
    } else {
        scale_x = 28.0f;
        scale_y = 129.5f;
        data_p = &tag_add_item_data[0];
    }

    tag->base_pos[1] += data_p->down_min[0][1] + (item_tag->body_ofs[1] - item_tag->body_scale[1] * scale_y * 0.5f) +
                        item_tag->_04[1] * data_p->down_min[1][1];
    tag->body_ofs[1] = (data_p->up_min[0][1] + tag->_04[1] * data_p->up_min[1][1]) - tag->body_scale[1] * 129.0f * 0.5f;

    tag->base_pos[0] += item_tag->body_ofs[0] - item_tag->body_scale[0] * scale_x * 0.5f;
    tag->body_ofs[0] = tag->body_scale[0] * 122.5f * 0.5f;

    tmp = mTG_check_edge_foot_select(tag);
    if (tmp && item_tag->table == mTG_TABLE_ITEM && item_tag->tag_row == 1 && mTG_label_table[tag->type].lines == 2) {
        tmp = FALSE;
    }

    if (tmp) {
        tag->base_pos[0] += data_p->down_min[0][0] + item_tag->_04[0] * data_p->down_min[1][0];
        tag->body_ofs[0] += data_p->up_min[0][0] + tag->_04[0] * data_p->up_min[1][0];
        mTG_calc_right_edge_select(tag, &dist_right);

        idx = 0;
        if (dist_right >= 131.0f) {
            if (dist_right >= 167.0f) {
                idx = 2;
            } else {
                idx = 1;
            }
        }

        if (idx == 2 || left_flag) {
            f32 xofs;

            tag->base_pos[0] =
                (item_tag->base_pos[0] + item_tag->body_ofs[0] + item_tag->body_scale[0] * scale_x * 0.5f) -
                (data_p->down_min[0][0] + item_tag->_04[0] * data_p->down_min[1][0]);
            tag->body_ofs[0] =
                -(tag->body_scale[0] * 122.5f * 0.5f) - (data_p->up_min[0][0] + tag->_04[0] * data_p->up_min[1][0]);
            xofs = (tag->base_pos[0] + tag->body_ofs[0] - tag->body_scale[0] * 122.5f * 0.5f) - -134.0f;

            if (xofs < 0.0f) {
                tag->body_ofs[0] -= xofs;
            }
        } else if (idx == 1) {
            tag->base_pos[0] -= (dist_right - 131.0f);
        }
    } else {
        f32 yofs;

        tag->base_pos[1] = item_tag->base_pos[1] + item_tag->body_ofs[1] + item_tag->body_scale[1] * scale_y * 0.5f +
                           data_p->down_ofs[0][1] + item_tag->_04[1] * data_p->down_ofs[1][1];
        tag->body_ofs[1] =
            (tag->body_scale[1] * 129.5f * 0.5f) + (data_p->up_ofs[0][1] + tag->_04[1] * data_p->up_ofs[1][1]);
        yofs = (tag->base_pos[1] + tag->body_ofs[1] + tag->body_scale[1] * 129.5f * 0.5f);

        if (yofs > 120.0f) {
            tag->base_pos[1] -= yofs - 120.0f;
        }

        tag->base_pos[0] += data_p->down_ofs[0][0] + item_tag->_04[0] * data_p->down_ofs[1][0];
        tag->body_ofs[0] += data_p->up_ofs[0][0] + tag->_04[0] * data_p->up_ofs[1][0];

        mTG_calc_right_edge_select(tag, &dist_right);

        idx = 0;
        if (dist_right >= 131.0f) {
            if (dist_right >= 167.0f) {
                idx = 2;
            } else {
                idx = 1;
            }
        }

        if (idx == 2 || left_flag) {
            f32 xofs;

            tag->base_pos[0] =
                (item_tag->base_pos[0] + item_tag->body_ofs[0] + item_tag->body_scale[0] * scale_x * 0.5f) -
                (data_p->down_ofs[0][0] + item_tag->_04[0] * data_p->down_ofs[1][0]);
            tag->body_ofs[0] =
                -(tag->body_scale[0] * 122.5f * 0.5f) - (data_p->up_ofs[0][0] + tag->_04[0] * data_p->up_ofs[1][0]);
            xofs = (tag->base_pos[0] + tag->body_ofs[0] - tag->body_scale[0] * 122.5f * 0.5f) - -134.0f;

            if (xofs < 0.0f) {
                tag->body_ofs[0] -= xofs;
            }
        } else if (idx == 1) {
            tag->base_pos[0] -= (dist_right - 131.0f);
        }
    }

    tag->arrow_dir = 0;
}

static void mTG_init_tag_data_select_win_after_select(mTG_tag_c* tag, mTG_tag_c* parent_tag, mTG_tag_data_c* tag_data) {
    f32 dist_right;
    f32 line;
    f32 col;
    f32 pos;

    mTG_get_col_width_and_line_select(tag, tag_data, &col, &line);
    mTG_set_tag_win_scale_p(tag, mTG_WIN_TYPE_SELECT2, col * 0.875f, line * 0.875f);
    tag->arrow_dir = 0;
    pos = tag->base_pos[1];

    tag->base_pos[0] += tag->_04[0] * -0.875f + -0.875f;
    tag->base_pos[1] += tag->_04[1] * 8.75f + 6.125f;
    tag->base_pos[1] -= 7.0f;
    tag->body_ofs[0] = tag->body_scale[0] * 61.25f;
    tag->body_ofs[1] = tag->body_scale[1] * -64.75f;

    if (mTG_check_edge_right_select(tag, &dist_right) == FALSE) {
        tag->body_ofs[0] -= dist_right;
    }

    if (mTG_check_edge_foot_select(tag) == FALSE) {
        f32 tmp;

        tag->body_ofs[1] *= -1.0f;
        tag->base_pos[1] = pos - (tag->_04[1] * 8.75f + 6.125f);
        tag->base_pos[1] += 7.0f;

        tmp = tag->body_scale[1] * 129.5f * 0.5f + (tag->base_pos[1] + tag->body_ofs[1]);
        if (tmp > 120.0f) {
            tag->base_pos[1] -= tmp - 120.0f;
        }
    }
}

static void mTG_init_tag_data(Submenu* submenu, int table, int type, f32 base_x, f32 base_y, int idx_x, int idx_y) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_data_c* tag_data = &mTG_label_table[type];
    mTG_tag_c* tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];
    mTG_tag_c* item_tag = &tag_ovl->tags[0];
    mTG_tag_c* parent_tag;

    if (tag_ovl->sel_tag_idx > 0) {
        parent_tag = &tag_ovl->tags[tag_ovl->sel_tag_idx - 1];
    } else {
        parent_tag = NULL;
    }

    tag->type = type;
    tag->table = table;
    tag->tag_col = idx_x;
    tag->tag_row = idx_y;
    tag->scale = 0.0f;

    if (tag_ovl->sel_tag_idx == 0) {
        mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
        int table_idx = mTG_get_table_idx(item_tag);

        hand_ovl->info.type = 1;
        mTG_init_tag_data_item_win(submenu);
        mTG_set_hand_pos(submenu, hand_ovl->info.pos, item_tag->table, table_idx);
    } else {
        tag->base_pos[0] = base_x;
        tag->base_pos[1] = base_y;

        if (tag_ovl->sel_tag_idx == 1) {
            if (item_tag->arrow_dir != 0) {
                mTG_init_tag_data_select_win_after_item(tag, item_tag, tag_data);
            } else {
                mTG_init_tag_data_select_win_only(tag, tag_data);
            }
        } else {
            mTG_init_tag_data_select_win_after_select(tag, parent_tag, tag_data);
        }
    }
}

static void mTG_chg_tag_func(Submenu* submenu, int table, int type, int idx, f32 base_x, f32 base_y) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_data_table_c* data_table = &mTG_table_data[table];
    int idx_x;
    int idx_y;

    idx_y = idx / data_table->col_num;
    idx_x = idx - (idx_y * data_table->col_num);

    if (tag_ovl->sel_tag_idx < 3) {
        tag_ovl->sel_tag_idx++;
        tag_ovl->ret_tag_idx = tag_ovl->sel_tag_idx;
        mTG_init_tag_data(submenu, table, type, base_x, base_y, idx_x, idx_y);
    }
}

static void mTG_chg_tag_func2(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag, int type) {
    // clang-format off
    mTG_chg_tag_func(
        submenu,
        tag->table,
        type,
        0,
        tag->base_pos[0] + menu_info->position[0] + (tag->body_ofs[0] + tag->text_ofs[0] + -3.5f),
        tag->base_pos[1] + menu_info->position[1] + ((tag->body_ofs[1] + tag->text_ofs[1] - tag->tag_row * 16.0f) - 8.0f) * 0.875f
    );
    // clang-format on
}

static int mTG_check_item_on_mail(mActor_name_t item, int cond) {
    int res = TRUE;

    if (cond != mPr_ITEM_COND_NORMAL ||
        ((item >= ITM_EXCERCISE_CARD00 && item <= ITM_EXCERCISE_CARD12) || item == ITM_KNIFE_AND_FORK)) {
        res = FALSE;
    } else if (ITEM_IS_ITEM1(item)) {
        int cat = ITEM_NAME_GET_CAT(item);

        if (cat == ITEM1_CAT_KABU || cat == ITEM1_CAT_FISH || cat == ITEM1_CAT_INSECT) {
            res = FALSE;
        }
    }

    return res;
}

static int mTG_check_put_unit(xyz_t* pos_p) {
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    int ux;
    int uz;
    int res = TRUE;

    mFI_Wpos2UtNum(&ux, &uz, *pos_p);

    if (mRlib_snowman_ball_unit_check_from_pos(play, pos_p)) {
        res = FALSE;
    } else if (mCoBG_CheckAcceptDesignSign(pos_p) == FALSE) {
        res = FALSE;
    } else {
        mCoBG_Collision_u* col = mFI_UtNum2UtCol(ux, uz);

        if (mCoBG_GetHoleNumber_ClData(col) > 0) {
            res = FALSE;
        }
    }

    return res;
}

static int mTG_put_place_check(xyz_t* pos_p, int plant_flag, int unit_flag) {
    int res = TRUE;

    if (unit_flag) {
        res = mTG_check_put_unit(pos_p);
    }

    if (res == TRUE) {
        if (plant_flag) {
            if (mCoBG_CheckPlant(*pos_p) == -1) {
                res = FALSE;
            }
        } else {
            res = mCoBG_CheckPlace(*pos_p);
        }
    }

    return res;
}

static void mTG_check_direction_put_pos(int* dir_p) {
    if (*dir_p < 0) {
        (*dir_p) += 8;
    } else if (*dir_p >= 8) {
        (*dir_p) -= 8;
    }
}

static int mTG_check_wall_put_pos(const xyz_t* start_pos_p, const xyz_t* end_pos_p) {
    mCoBG_Check_c bg_check;
    int res = FALSE;

    bg_check.result.hit_wall = 0;
    bg_check.result.hit_attribute_wall = 0;

    mCoBG_VirtualBGCheck(NULL, &bg_check, start_pos_p, end_pos_p, 0, FALSE, TRUE, 10.0f, -20.0f, 1, 1, 0);
    if (bg_check.result.hit_wall != 0 || bg_check.result.hit_attribute_wall != 0) {
        res = TRUE;
    }

    return res;
}

static int mTG_check_pos_slope(xyz_t* pos_p) {
    // clang-format off
    static f32 offset_pos[][2] = {
        {                  0.0f,  mFI_UT_WORLDSIZE_Z_F },
        {  mFI_UT_WORLDSIZE_X_F,  mFI_UT_WORLDSIZE_Z_F },
        {  mFI_UT_WORLDSIZE_X_F,                  0.0f },
        {  mFI_UT_WORLDSIZE_X_F, -mFI_UT_WORLDSIZE_Z_F },
        {                  0.0f, -mFI_UT_WORLDSIZE_Z_F },
        { -mFI_UT_WORLDSIZE_X_F, -mFI_UT_WORLDSIZE_Z_F },
        { -mFI_UT_WORLDSIZE_X_F,                  0.0f },
        { -mFI_UT_WORLDSIZE_X_F,  mFI_UT_WORLDSIZE_Z_F },
    };
    // clang-format on

    int res = TRUE;
    int i;

    for (i = 0; i < 8; i++) {
        xyz_t pos;
        mCoBG_Collision_u* col;

        pos.x = pos_p->x + offset_pos[i][0];
        pos.z = pos_p->z + offset_pos[i][1];
        pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(pos, 0.0f);

        col = mFI_GetUnitCol(pos);
        if (mCoBG_GetHoleNumber_ClData(col) > 0 || pos_p->y != pos.y) {
            res = FALSE;
            break;
        }
    }

    return res;
}

// clang-format off
#define mTG_SEARCH_BAD_ITEM(item) ( \
    (item) == TREE_S0 || \
    (item) == TREE_S1 || \
    (item) == TREE_S2 || \
    (item) == TREE || \
    (item) == TREE_1000BELLS_S0 || \
    (item) == TREE_1000BELLS_S1 || \
    (item) == TREE_1000BELLS_S2 || \
    (item) == TREE_1000BELLS || \
    (item) == TREE_10000BELLS_S0 || \
    (item) == TREE_10000BELLS_S1 || \
    (item) == TREE_10000BELLS_S2 || \
    (item) == TREE_10000BELLS || \
    (item) == TREE_30000BELLS_S0 || \
    (item) == TREE_30000BELLS_S1 || \
    (item) == TREE_30000BELLS_S2 || \
    (item) == TREE_30000BELLS || \
    (item) == TREE_100BELLS_S0 || \
    (item) == TREE_100BELLS_S1 || \
    (item) == TREE_100BELLS_S2 || \
    (item) == TREE_100BELLS || \
    (item) == CEDAR_TREE_S0 || \
    (item) == CEDAR_TREE_S1 || \
    (item) == CEDAR_TREE_S2 || \
    (item) == CEDAR_TREE || \
    (item) == GOLD_TREE_S0 || \
    (item) == GOLD_TREE_S1 || \
    (item) == GOLD_TREE_S2 || \
    (item) == GOLD_TREE || \
    (item) == GOLD_TREE_SHOVEL || \
    (item) == TREE_APPLE_S0 || \
    (item) == TREE_APPLE_S1 || \
    (item) == TREE_APPLE_S2 || \
    (item) == TREE_APPLE_NOFRUIT_0 || \
    (item) == TREE_APPLE_NOFRUIT_1 || \
    (item) == TREE_APPLE_NOFRUIT_2 || \
    (item) == TREE_APPLE_FRUIT || \
    (item) == TREE_ORANGE_S0 || \
    (item) == TREE_ORANGE_S1 || \
    (item) == TREE_ORANGE_S2 || \
    (item) == TREE_ORANGE_NOFRUIT_0 || \
    (item) == TREE_ORANGE_NOFRUIT_1 || \
    (item) == TREE_ORANGE_NOFRUIT_2 || \
    (item) == TREE_ORANGE_FRUIT || \
    (item) == TREE_PEACH_S0 || \
    (item) == TREE_PEACH_S1 || \
    (item) == TREE_PEACH_S2 || \
    (item) == TREE_PEACH_NOFRUIT_0 || \
    (item) == TREE_PEACH_NOFRUIT_1 || \
    (item) == TREE_PEACH_NOFRUIT_2 || \
    (item) == TREE_PEACH_FRUIT || \
    (item) == TREE_PEAR_S0 || \
    (item) == TREE_PEAR_S1 || \
    (item) == TREE_PEAR_S2 || \
    (item) == TREE_PEAR_NOFRUIT_0 || \
    (item) == TREE_PEAR_NOFRUIT_1 || \
    (item) == TREE_PEAR_NOFRUIT_2 || \
    (item) == TREE_PEAR_FRUIT || \
    (item) == TREE_CHERRY_S0 || \
    (item) == TREE_CHERRY_S1 || \
    (item) == TREE_CHERRY_S2 || \
    (item) == TREE_CHERRY_NOFRUIT_0 || \
    (item) == TREE_CHERRY_NOFRUIT_1 || \
    (item) == TREE_CHERRY_NOFRUIT_2 || \
    (item) == TREE_CHERRY_FRUIT || \
    (item) == TREE_PALM_S0 || \
    (item) == TREE_PALM_S1 || \
    (item) == TREE_PALM_S2 || \
    (item) == TREE_PALM_NOFRUIT_0 || \
    (item) == TREE_PALM_NOFRUIT_1 || \
    (item) == TREE_PALM_NOFRUIT_2 || \
    (item) == TREE_PALM_FRUIT || \
    (item) == TREE_BEES || \
    (item) == TREE_FTR || \
    (item) == TREE_LIGHTS || \
    (item) == TREE_PRESENT || \
    (item) == TREE_BELLS || \
    (item) == CEDAR_TREE_BELLS || \
    (item) == CEDAR_TREE_FTR || \
    (item) == CEDAR_TREE_BEES || \
    (item) == GOLD_TREE_BELLS || \
    (item) == GOLD_TREE_FTR || \
    (item) == GOLD_TREE_BEES || \
    (item) == CEDAR_TREE_LIGHTS || \
    ITEM_IS_HOLE((item)) || \
    (item) == HOLE_SHINE || \
    IS_ITEM_TREE_STUMP((item)) \
)
// clang-format on

static int mTG_search_put_pos2(ACTOR* player_actor, xyz_t* pos_tbl, int plant_flag, int param_4, int num_pos,
                               int param_6, int unit_flag, int param_8) {
    // clang-format off
    static f32 offset_pos[][2] = {
        {                  0.0f,  mFI_UT_WORLDSIZE_Z_F },
        {  mFI_UT_WORLDSIZE_X_F,  mFI_UT_WORLDSIZE_Z_F },
        {  mFI_UT_WORLDSIZE_X_F,                  0.0f },
        {  mFI_UT_WORLDSIZE_X_F, -mFI_UT_WORLDSIZE_Z_F },
        {                  0.0f, -mFI_UT_WORLDSIZE_Z_F },
        { -mFI_UT_WORLDSIZE_X_F, -mFI_UT_WORLDSIZE_Z_F },
        { -mFI_UT_WORLDSIZE_X_F,                  0.0f },
        { -mFI_UT_WORLDSIZE_X_F,  mFI_UT_WORLDSIZE_Z_F },
    };
    // clang-format on
    xyz_t pos;
    xyz_t center_pos;
    xyz_t pos2;
    xyz_t start_pos;
    int unit;
    int next_unit;
    mActor_name_t* fg_p;
    s16 player_angle_y;
    int max;
    int i;
    int count;

    pos2.x = player_actor->world.position.x;
    pos2.z = player_actor->world.position.z;
    pos2.y = player_actor->world.position.y;
    count = 0;

    mFI_Wpos2UtCenterWpos(&center_pos, pos2);
    center_pos.y = mCoBG_Wpos2BgUtCenterHeight_AddColumn(center_pos);
    fg_p = mFI_GetUnitFG(center_pos);

    if (param_6 == 0 && param_4 == 0 && fg_p != NULL && *fg_p == EMPTY_NO &&
        mTG_put_place_check(&center_pos, plant_flag, unit_flag)) {
        xyz_t_move(pos_tbl, &center_pos);
        pos_tbl++;
        count = 1;
    }

    player_angle_y = player_actor->shape_info.rotation.y;

    if (player_angle_y > DEG2SHORT_ANGLE2(157.5f) || player_angle_y <= DEG2SHORT_ANGLE2(-157.5f)) {
        unit = 4;
    } else if (player_angle_y > DEG2SHORT_ANGLE2(112.5f)) {
        unit = 3;
    } else if (player_angle_y > DEG2SHORT_ANGLE2(67.5f)) {
        unit = 2;
    } else if (player_angle_y > DEG2SHORT_ANGLE2(22.5f)) {
        unit = 1;
    } else if (player_angle_y > DEG2SHORT_ANGLE2(-22.5f)) {
        unit = 0;
    } else if (player_angle_y > DEG2SHORT_ANGLE2(-67.5f)) {
        unit = 7;
    } else if (player_angle_y > DEG2SHORT_ANGLE2(-112.5f)) {
        unit = 6;
    } else {
        unit = 5;
    }

    max = param_8 ? 5 : 8;
    for (i = 0; i < max && count < num_pos; i++) {
        mActor_name_t* fg_p;

        if (i & 1) {
            unit += i;
        } else {
            unit -= i;
        }

        mTG_check_direction_put_pos(&unit);
        pos.x = center_pos.x + offset_pos[unit][0];
        pos.z = center_pos.z + offset_pos[unit][1];
        pos.y = mCoBG_Wpos2BgUtCenterHeight_AddColumn(pos);

        fg_p = mFI_GetUnitFG(pos);
        if (fg_p != NULL && *fg_p == EMPTY_NO && mTG_put_place_check(&pos, plant_flag, unit_flag) &&
            (unit_flag == FALSE || (unit_flag != FALSE && mTG_check_pos_slope(&pos)))) {
            start_pos = player_actor->world.position;
            start_pos.y -= 20.0f;

            if ((unit & 1)) {
                mActor_name_t* fg_p;

                next_unit = unit + 1;
                mTG_check_direction_put_pos(&next_unit);

                pos2.x = center_pos.x + offset_pos[next_unit][0];
                pos2.z = center_pos.z + offset_pos[next_unit][1];
                pos2.y = mCoBG_Wpos2BgUtCenterHeight_AddColumn(pos2);

                fg_p = mFI_GetUnitFG(pos2);
                if (fg_p != NULL && !mTG_SEARCH_BAD_ITEM(*fg_p) && mTG_check_wall_put_pos(&start_pos, &pos2) == FALSE &&
                    mTG_check_wall_put_pos(&pos2, &pos) == FALSE) {
                    xyz_t_move(pos_tbl, &pos);
                    count++;
                    pos_tbl++;
                } else {
                    next_unit = unit - 1;
                    mTG_check_direction_put_pos(&next_unit);

                    pos2.x = center_pos.x + offset_pos[next_unit][0];
                    pos2.z = center_pos.z + offset_pos[next_unit][1];
                    pos2.y = mCoBG_Wpos2BgUtCenterHeight_AddColumn(pos2);

                    fg_p = mFI_GetUnitFG(pos2);
                    if (fg_p != NULL && !mTG_SEARCH_BAD_ITEM(*fg_p) &&
                        mTG_check_wall_put_pos(&start_pos, &pos2) == FALSE &&
                        mTG_check_wall_put_pos(&pos2, &pos) == FALSE) {
                        xyz_t_move(pos_tbl, &pos);
                        count++;
                        pos_tbl++;
                    }
                }
            } else {
                if (mTG_check_wall_put_pos(&start_pos, &pos) == FALSE) {
                    xyz_t_move(pos_tbl, &pos);
                    count++;
                    pos_tbl++;
                }
            }
        }
    }

    return count;
}

static int mTG_search_put_pos(ACTOR* player_actor, xyz_t* pos_tbl, int plant_flag, int param_4, int param_5,
                              int unit_flag, int param_7) {
    return mTG_search_put_pos2(player_actor, pos_tbl, plant_flag, param_4, 1, param_5, unit_flag, param_7);
}

static void mTG_open_warning_window(Submenu* submenu, mSM_MenuInfo_c* menu_info, int type) {
    mSM_open_submenu(submenu, mSM_OVL_WARNING, type, 0);
    menu_info->proc_status = mSM_OVL_PROC_WAIT;
    menu_info->next_proc_status = mSM_OVL_PROC_WAIT;
    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
    sAdo_SysTrgStart(MONO(NA_SE_3));
}

static int mTG_common_throw_put_field(GAME_PLAY* play, mActor_name_t item, xyz_t* pos_p, s16 layer) {
    int res = FALSE;

    if (item == ITM_SIGNBOARD) {
        res = aSIGN_set_white_sign(&play->game, pos_p);
    } else {
        int ux;
        int uz;

        if (mFI_Wpos2UtNum(&ux, &uz, *pos_p) && Common_Get(clip).bg_item_clip != NULL &&
            Common_Get(clip).bg_item_clip->player_drop_entry_proc != NULL) {
            res = Common_Get(clip).bg_item_clip->player_drop_entry_proc(&play->game, item, ux, uz, layer);
        }
    }

    return res;
}

static int mTG_common_throw_put_room(GAME_PLAY* play, mActor_name_t item, xyz_t* pos_p, int layer, int delay_timer) {
    int ux;
    int uz;
    int res = FALSE;

    if (mFI_Wpos2UtNum(&ux, &uz, *pos_p) && Common_Get(clip).shop_goods_clip != NULL &&
        Common_Get(clip).shop_goods_clip->player_drop_entry_proc != NULL) {
        res = Common_Get(clip).shop_goods_clip->player_drop_entry_proc(&play->game, item, ux, uz, layer, delay_timer);
    }

    return res;
}

static void mTG_close_window(Submenu* submenu, mSM_MenuInfo_c* menu_info, int se_flag) {
    submenu->overlay->move_chg_base_proc(menu_info, mSM_OVL_PROC_MOVE);
    if (se_flag) {
        sAdo_SysTrgStart(NA_SE_31);
    }
}

static void mTG_open_board_init(Submenu* submenu, mSM_MenuInfo_c* menu_info, int mail_idx, int type, int item_idx) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* item_tag = &tag_ovl->tags[0];
    Mail_c* mail;

    if (mail_idx == -1) {
        mail = mTG_get_mail_pointer(submenu, NULL);
    } else {
        mail = &Now_Private->mail[mail_idx];
    }

    tag_ovl->sel_tag_idx = 0;
    tag_ovl->ret_tag_idx = 0;
    tag_ovl->item_name_wait_time = mTG_get_item_name_wait_time(item_tag);

    mSM_open_submenu_new(submenu, mSM_OVL_BOARD, type, item_idx, mail);

    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->next_proc_status = mSM_OVL_PROC_WAIT;
    menu_info->move_drt = mSM_MOVE_OUT_LEFT;
    sAdo_SysTrgStart(NA_SE_5F);
}

static void mTG_set_catch_se(Submenu* submenu) {
    if (submenu->overlay->tag_ovl->sel_tag_idx == 0) {
        sAdo_SysTrgStart(NA_SE_33);
    } else {
        sAdo_SysTrgStart(NA_SE_33);
    }
}

static void mTG_catch_item_from_table(Submenu* submenu, Mail_c* mail, mActor_name_t* item, int item_cond, int table,
                                      int table_idx) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;

    if (table == mTG_TABLE_PLAYER) {
        hand_ovl->info.wait_timer = 16;
        submenu->overlay->segment.change_player_main_anime_idx = mIV_ANIM_CATCH;
    } else if (table == mTG_TABLE_NEEDLEWORK || table == mTG_TABLE_CPORIGINAL_NW) {
        hand_ovl->info.next_act = mHD_ACTION_CLOSE;
        hand_ovl->info.hold_tbl = table;
        hand_ovl->info.hold_idx = table_idx;
        hand_ovl->info.item = *item;
        hand_ovl->info.item_cond = item_cond;
        *item = EMPTY_NO;
        mNW_on_hide_flg(submenu, table_idx);
    } else if (table == mTG_TABLE_CPORIGINAL) {
        int top = mCO_top_folder(submenu);

        hand_ovl->info.next_act = mHD_ACTION_CLOSE;
        hand_ovl->info.hold_tbl = table;
        hand_ovl->info.hold_idx = table_idx;
        hand_ovl->info.item = *item;
        hand_ovl->info.item_cond = item_cond;
        hand_ovl->info.catch_pg = top;
        *item = EMPTY_NO;
        mCO_on_hide_flg(submenu, top, table_idx);
    } else {
        hand_ovl->info.next_act = mHD_ACTION_CLOSE;
        hand_ovl->info.hold_tbl = table;
        hand_ovl->info.hold_idx = table_idx;

        if (table == mTG_TABLE_CPMAIL) {
            hand_ovl->info.catch_pg = submenu->overlay->cpmail_ovl->page_order[0];
        } else {
            hand_ovl->info.catch_pg = 0;
        }

        if (mail != NULL) {
            mMl_copy_mail(&hand_ovl->info.mail, mail);
            mMl_clear_mail(mail);
        } else {
            hand_ovl->info.item = *item;
            hand_ovl->info.item_cond = item_cond;

            if (table == mTG_TABLE_ITEM) {
                mPr_SetPossessionItem(Now_Private, table_idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
            } else {
                *item = EMPTY_NO;
            }
        }
    }

    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
    mTG_set_catch_se(submenu);
}

static int mTG_itemNo_to_amount(mActor_name_t itemNo) {
    switch (itemNo) {
        case ITM_MONEY_1000:
            return 1000;
        case ITM_MONEY_10000:
            return 10000;
        case ITM_MONEY_30000:
            return 30000;
        case ITM_MONEY_100:
            return 100;
        default:
            return 0;
    }
}

static int mTG_make_money_sack(Submenu* submenu, mSM_MenuInfo_c* menu_info, mActor_name_t item) {
    u32* money_p = &Now_Private->inventory.wallet;
    int amount = mTG_itemNo_to_amount(item);
    int res = FALSE;

    if ((int)*money_p >= amount) {
        mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;

        *money_p -= amount;
        hand_ovl->info.next_act = mHD_ACTION_CLOSE;
        hand_ovl->info.item = item;
        hand_ovl->info.item_cond = mPr_ITEM_COND_NORMAL;
        hand_ovl->info.wait_timer = 42;
        hand_ovl->info.hold_tbl = mTG_TABLE_MONEY;
        hand_ovl->info.hold_idx = 0;
        hand_ovl->info.catch_pg = 0;
        mTG_mark_main_CLR(submenu, menu_info);
        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
        submenu->overlay->inventory_ovl->disp_money_change_frames = -(amount / 42);
        sAdo_SysTrgStart(MONO(NA_SE_52));
        res = TRUE;
    }

    return res;
}

static int mTG_drop_furniture(GAME_PLAY* play, mActor_name_t item) {
    int idx = -1;

    if (aMR_CLIP != NULL) {
        GAME* game = (GAME*)play;
        int sq_ofs;
        int layer;
        int ux;
        int uz;
        u16 rot;
        u16 ftrIdx = mRmTp_FtrItemNo2FtrIdx(item);

        idx = aMR_CLIP->judge_breed_new_ftr_proc(game, ftrIdx, &ux, &uz, &rot, &sq_ofs, &layer);
        if (idx >= 0) {
            aMR_CLIP->reserve_ftr_proc(game, ftrIdx, idx, ux, uz, rot, sq_ofs, layer);
        }
    }

    return idx;
}

static int mTG_nw_drop_furniture(GAME_PLAY* play, int image_no, mActor_name_t itemNo) {
    GAME* game = (GAME*)play;
    int idx = -1;
    int sq_ofs;
    int layer;
    int ux;
    int uz;
    u16 rot;

    switch (image_no) {
        case mNW_TYPE_MANEKIN:
            idx = aMR_CLIP->judge_breed_new_ftr_proc(game, 0x2EA + (itemNo & 7), &ux, &uz, &rot, &sq_ofs, &layer);
            break;
        case mNW_TYPE_UMBRELLA:
            idx = aMR_CLIP->judge_breed_new_ftr_proc(game, 0x362 + (itemNo & 7), &ux, &uz, &rot, &sq_ofs, &layer);
            break;
    }

    if (idx >= 0) {
        switch (image_no) {
            case mNW_TYPE_MANEKIN:
                aMR_CLIP->reserve_ftr_proc(game, 0x2EA + (itemNo & 7), idx, ux, uz, rot, sq_ofs, layer);
                break;
            case mNW_TYPE_UMBRELLA:
                aMR_CLIP->reserve_ftr_proc(game, 0x362 + (itemNo & 7), idx, ux, uz, rot, sq_ofs, layer);
                break;
        }
    }

    return idx;
}

static int mTG_get_unit_front_player(xyz_t* pos_p, const xyz_t* player_pos, s16 angle_y) {
    int dir;
    static f32 offset_pos[][2] = {
        // clang-format off
        {                  0.0f,  mFI_UT_WORLDSIZE_Z_F },
        {  mFI_UT_WORLDSIZE_X_F,  mFI_UT_WORLDSIZE_Z_F },
        {  mFI_UT_WORLDSIZE_X_F,                  0.0f },
        {  mFI_UT_WORLDSIZE_X_F, -mFI_UT_WORLDSIZE_Z_F },
        {                  0.0f, -mFI_UT_WORLDSIZE_Z_F },
        { -mFI_UT_WORLDSIZE_X_F, -mFI_UT_WORLDSIZE_Z_F },
        { -mFI_UT_WORLDSIZE_X_F,                  0.0f },
        { -mFI_UT_WORLDSIZE_X_F,  mFI_UT_WORLDSIZE_Z_F },
        // clang-format on
    };

    if (angle_y > DEG2SHORT_ANGLE2(157.5f) || angle_y <= DEG2SHORT_ANGLE2(-157.5f)) {
        dir = 4;
    } else if (angle_y > DEG2SHORT_ANGLE2(112.5f)) {
        dir = 3;
    } else if (angle_y > DEG2SHORT_ANGLE2(67.5f)) {
        dir = 2;
    } else if (angle_y > DEG2SHORT_ANGLE2(22.5f)) {
        dir = 1;
    } else if (angle_y > DEG2SHORT_ANGLE2(-22.5f)) {
        dir = 0;
    } else if (angle_y > DEG2SHORT_ANGLE2(-67.5f)) {
        dir = 7;
    } else if (angle_y > DEG2SHORT_ANGLE2(-112.5f)) {
        dir = 6;
    } else {
        dir = 5;
    }

    pos_p->x = player_pos->x + offset_pos[dir][0];
    pos_p->y = player_pos->y;
    pos_p->z = player_pos->z + offset_pos[dir][1];
}

static int mTG_check_free_2nd_layer(const xyz_t* pos_p) {
    int bx;
    int bz;
    int ux;
    int uz;
    mActor_name_t* fg_p;
    int res = FALSE;

    if (mFI_Wpos2BlockNum(&bx, &bz, *pos_p) && mFI_Wpos2UtNum_inBlock(&ux, &uz, *pos_p)) {
        fg_p = mFI_BkNum2UtFGTop_layer(bx, bz, mCoBG_LAYER1);
        if (fg_p != NULL && fg_p[ux + uz * UT_X_NUM] == EMPTY_NO) {
            res = TRUE;
        }
    }

    return res;
}

static void mTG_set_trade_cond(Submenu* submenu, mSM_MenuInfo_c* menu_info, s16 cond, u32 arg) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];

    Save_Get(homes[menu_info->data1]).haniwa.items[tag->tag_col].exchange_type = cond;
    Save_Get(homes[menu_info->data1]).haniwa.items[tag->tag_col].extra_data = arg;
    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
    sAdo_SysTrgStart(NA_SE_33);
    submenu->overlay->haniwa_ovl->set_interrupt_message_proc(submenu, tag, 4);
}

static void mTG_present_open_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    int table_idx;

    table_idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);
    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_FIELD_DEFAULT);
    sAdo_SysTrgStart(NA_SE_436);
    mPr_SetItemCollectBit(Now_Private->inventory.pockets[table_idx]);
    submenu->overlay->inventory_ovl->item_scale_type[table_idx] = 5;
    submenu->overlay->inventory_ovl->remove_timer = 48;
}

static void mTG_nw_select_this_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    int table_idx;
    Submenu_Item_c* item_p;

    table_idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);
    item_p = submenu->item_p;
    item_p->item = RSV_NO;
    item_p->slot_no = table_idx;
    submenu->selected_item_num = 1;
    mTG_close_window(submenu, menu_info, TRUE);
}

static void mTG_give_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    int table_idx;
    Submenu_Item_c* item_p;
    int category;

    table_idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);
    item_p = submenu->item_p;
    item_p->item = Now_Private->inventory.pockets[table_idx];
    item_p->slot_no = table_idx;
    submenu->selected_item_num = 1;

    category = ITEM_NAME_GET_CAT(item_p->item);
    if (menu_info->data1 == 2) {
        submenu->after_mode = aHOI_REQUEST_GET_PULL_WAIT;
    } else if (menu_info->data1 == 1) {
        submenu->after_mode = aHOI_REQUEST_PUTAWAY;
    } else if (ITEM_NAME_GET_TYPE(item_p->item) == NAME_TYPE_ITEM1 &&
               (category == ITEM1_CAT_FRUIT || category == ITEM1_CAT_FISH)) {
        submenu->after_mode = aHOI_REQUEST_EAT;
    } else {
        submenu->after_mode = aHOI_REQUEST_PUTAWAY;
    }

    mPlib_request_main_give_from_submenu(item_p->item, submenu->after_mode,
                                         mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, item_p->slot_no) & 1,
                                         FALSE);
    mTG_close_window(submenu, menu_info, TRUE);
}

static void mTG_sell_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    int table_idx = mTG_get_table_idx(tag);
    Submenu_Item_c* item_p = submenu->item_p;

    if (mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, table_idx) == mPr_ITEM_COND_QUEST) {
        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_SELL_QUEST_ITEM);
    } else {
        item_p->item = Now_Private->inventory.pockets[table_idx];
        item_p->slot_no = table_idx;
        submenu->selected_item_num = 1;
        mTG_close_window(submenu, menu_info, TRUE);
    }
}

static void mTG_sell_all_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mIV_Ovl_c* inventory_ovl;
    int table_idx;
    Submenu_Item_c* item_p;
    int count;
    int i;

    inventory_ovl = submenu->overlay->inventory_ovl;
    table_idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);

    if (mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, table_idx) == mPr_ITEM_COND_QUEST) {
        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_SELL_QUEST_ITEM);
    } else {
        item_p = submenu->item_p;
        count = 0;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            item_p->item = EMPTY_NO;
            item_p->slot_no = 0;
            item_p++;
        }

        item_p = submenu->item_p;
        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if ((inventory_ovl->item_mark_bitfield & (1 << i)) != 0) {
                count++;
                item_p->item = Now_Private->inventory.pockets[i];
                item_p->slot_no = i;
                item_p++;
            }
        }

        submenu->selected_item_num = count;
        mTG_close_window(submenu, menu_info, TRUE);
    }
}

static void mTG_get_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    static mActor_name_t mTG_money_name[] = { ITM_MONEY_100, ITM_MONEY_1000, ITM_MONEY_10000, ITM_MONEY_30000 };
    static u32 mTG_money_amount[] = { 100, 1000, 10000, 30000 };
    int money;
    mActor_name_t* item_p2;
    int k;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mPr_GetPossessionItemIdxWithCond(Now_Private, EMPTY_NO, mPr_ITEM_COND_NORMAL);
    mHW_Ovl_c* haniwa_ovl;
    Haniwa_Item_c* haniwa_item_p;
    mActor_name_t* item_p;
    int changed_money;
    int keep_money;
    int i;
    int j;
    mIV_Ovl_c* inventory_ovl;
    mActor_name_t* money_name_p;
    u32* money_amount_p;
    int change_money;

    if (idx == -1) {
        haniwa_ovl = submenu->overlay->haniwa_ovl;

        haniwa_ovl->msg_interrupt_idx = 6;
        haniwa_ovl->table_idx = tag->table;
        haniwa_ovl->sub_idx = tag->tag_col;
        haniwa_ovl->msg_time = 120;
        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
        sAdo_SysTrgStart(MONO(NA_SE_3));
    } else {
        haniwa_item_p = &Save_Get(homes[menu_info->data1]).haniwa.items[tag->tag_col];
        item_p = Now_Private->inventory.pockets;

        money = Now_Private->inventory.wallet;
        changed_money = money;
        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++, item_p++) {
            if (mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, i) == mPr_ITEM_COND_NORMAL) {
                changed_money += mTG_itemNo_to_amount(*item_p);
            }
        }

        changed_money -= haniwa_item_p->extra_data;
        if (changed_money < 0) {
            submenu->overlay->haniwa_ovl->set_interrupt_message_proc(submenu, tag, 7);
            mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
            sAdo_SysTrgStart(MONO(NA_SE_3));
        } else {
            inventory_ovl = submenu->overlay->inventory_ovl;
            money_name_p = mTG_money_name;
            money_amount_p = mTG_money_amount;

            keep_money = money - haniwa_item_p->extra_data;
            for (j = 0; j < ARRAY_COUNT(mTG_money_name) && keep_money < 0; j++, money_name_p++, money_amount_p++) {
                item_p2 = Now_Private->inventory.pockets;
                for (k = 0; k < mPr_POCKETS_SLOT_COUNT; k++, item_p2++) {
                    if (mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, k) == mPr_ITEM_COND_NORMAL &&
                        *item_p2 == *money_name_p) {
                        keep_money += *money_amount_p;
                        mPr_SetPossessionItem(Now_Private, k, EMPTY_NO, mPr_ITEM_COND_NORMAL);

                        if (keep_money >= 0) {
                            break;
                        }
                    }
                }
            }

            Now_Private->inventory.wallet = keep_money;
            mPr_SetPossessionItem(Now_Private, idx, haniwa_item_p->item, mPr_ITEM_COND_NORMAL);
            submenu->overlay->haniwa_ovl->set_interrupt_message_proc(submenu, tag, 8);
            mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
            Save_Get(homes[menu_info->data1]).haniwa.bells += haniwa_item_p->extra_data;
            haniwa_item_p->item = EMPTY_NO;

            if (haniwa_item_p->exchange_type == mHm_HANIWA_TRADE_0) {
                sAdo_SysTrgStart(NA_SE_5F);
            } else {
                change_money = (int)keep_money - (int)money;

                if (ABS(change_money) < 42) {
                    sAdo_SysTrgStart(MONO(NA_SE_REGISTER));
                    inventory_ovl->disp_money = keep_money;
                } else {
                    sAdo_SysTrgStart(MONO(NA_SE_52));
                    submenu->overlay->hand_ovl->info.wait_timer = 42;
                    inventory_ovl->disp_money_change_frames = change_money / 42;

                    if (ABS(inventory_ovl->disp_money_change_frames) % 5 == 0) {
                        if (inventory_ovl->disp_money_change_frames > 0) {
                            inventory_ovl->disp_money_change_frames--;
                        } else {
                            inventory_ovl->disp_money_change_frames++;
                        }
                    }
                }
            }
        }
    }
}

static void mTG_dump_mail_mark_exe_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    mMB_Ovl_c* mailbox_ovl = submenu->overlay->mailbox_ovl;
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    int delete_flag;
    int i;

    if (menu_info->menu_type == mSM_OVL_MAILBOX) {
        mailbox_ovl->mark_flag = FALSE;
        for (i = 0; i < HOME_MAILBOX_SIZE; i++) {
            Mail_c* mail = &Common_Get(now_home)->mailbox[i];

            // clear selected mail if it has a present or is from the player (sending)
            if (mail->present != EMPTY_NO || (mail->content.font != mMl_FONT_2 && mail->content.font != mMl_FONT_4)) {
                mailbox_ovl->mark_bitfield &= ~(1 << i);
            }
        }

        if (mailbox_ovl->mark_bitfield != 0) {
            mailbox_ovl->mark_flag = TRUE;
        }
    } else if (menu_info->menu_type == mSM_OVL_CPMAIL) {
        int page = cpmail_ovl->page_order[0];

        for (i = 0; i < mCM_MAIL_COUNT; i++) {
            Mail_c* mail = &cpmail_ovl->card_mail->mail[page][i];

            // clear selected mail if it has a present or is from the player (sending)
            if (mail->present != EMPTY_NO || (mail->content.font != mMl_FONT_2 && mail->content.font != mMl_FONT_4)) {
                cpmail_ovl->mark_bitfield &= ~(1 << i);
            }
        }

        cpmail_ovl->mark_flag = FALSE;
        if (cpmail_ovl->mark_bitfield != 0) {
            cpmail_ovl->mark_flag = TRUE;
        }
    }

    for (i = 0; i < mPr_INVENTORY_MAIL_COUNT; i++) {
        Mail_c* mail = &Now_Private->mail[i];

        // clear selected mail if it has a present or is from the player (sending)
        if (mail->present != EMPTY_NO || (mail->content.font != mMl_FONT_2 && mail->content.font != mMl_FONT_4)) {
            inv_ovl->mail_mark_bitfield2 &= ~(1 << i);
        }
    }

    inv_ovl->mail_mark_flag = FALSE;
    if (inv_ovl->mail_mark_bitfield2 != 0) {
        inv_ovl->mail_mark_flag = TRUE;
    }

    delete_flag = FALSE;
    if (inv_ovl->mail_mark_flag == TRUE) {
        delete_flag = TRUE;
    } else if (menu_info->menu_type == mSM_OVL_MAILBOX) {
        if (mailbox_ovl->mark_flag == TRUE) {
            delete_flag = TRUE;
        }
    } else if (menu_info->menu_type == mSM_OVL_CPMAIL) {
        if (cpmail_ovl->mark_flag == TRUE) {
            delete_flag = TRUE;
        }
    }

    if (delete_flag) {
        inv_ovl->remove_timer = 24;
        sAdo_SysTrgStart(NA_SE_435);
    } else {
        sAdo_SysTrgStart(MONO(NA_SE_A));
    }

    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
}

static void mTG_mailbox_change_mail_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mMB_Ovl_c* mailbox_ovl = submenu->overlay->mailbox_ovl;
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    int idx = mMl_chk_mail_free_space(Now_Private->mail, mPr_INVENTORY_MAIL_COUNT);

    inv_ovl->mail_mark_bitfield2 = 0;
    if (idx != -1) {
        mailbox_ovl->mark_flag = 2;
        sAdo_SysTrgStart(NA_SE_MENU_EXIT);
    } else {
        mailbox_ovl->mark_bitfield = 0;
        sAdo_SysTrgStart(MONO(NA_SE_A));
    }

    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
}

static void mTG_cpmail_change_mail_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    int inv_free_cnt;
    int inv_mark_cnt;
    int cpmail_mark_cnt;
    int cpmail_free_cnt;
    int inv_cnt;
    int cpmail_cnt;
    int page;
    int i;

    inv_mark_cnt = 0;
    for (i = 0; i < mPr_INVENTORY_MAIL_COUNT; i++) {
        if ((inv_ovl->mail_mark_bitfield2 & (1 << i)) != 0) {
            inv_mark_cnt++;
        }
    }

    cpmail_mark_cnt = 0;
    for (i = 0; i < mCM_MAIL_COUNT; i++) {
        if ((cpmail_ovl->mark_bitfield & (1 << i)) != 0) {
            cpmail_mark_cnt++;
        }
    }

    inv_free_cnt = 0;
    for (i = 0; i < mPr_INVENTORY_MAIL_COUNT; i++) {
        if (mMl_check_not_used_mail(&Now_Private->mail[i])) {
            inv_free_cnt++;
        }
    }

    cpmail_free_cnt = 0;
    page = cpmail_ovl->page_order[0];
    for (i = 0; i < mCM_MAIL_COUNT; i++) {
        if (mMl_check_not_used_mail(&cpmail_ovl->card_mail->mail[page][i]) == TRUE) {
            cpmail_free_cnt++;
        }
    }

    inv_cnt = 0;
    cpmail_cnt = 0;
    if (inv_mark_cnt > cpmail_mark_cnt && (inv_mark_cnt - cpmail_mark_cnt) > cpmail_free_cnt) {
        inv_cnt = (inv_mark_cnt - cpmail_mark_cnt) - cpmail_free_cnt;
    } else if (cpmail_mark_cnt > inv_mark_cnt && (cpmail_mark_cnt - inv_mark_cnt) > inv_free_cnt) {
        cpmail_cnt = (cpmail_mark_cnt - inv_mark_cnt) - inv_free_cnt;
    }

    if (inv_cnt == inv_mark_cnt && cpmail_cnt == cpmail_mark_cnt) {
        cpmail_ovl->mark_bitfield = 0;
        inv_ovl->mail_mark_bitfield2 = 0;
        sAdo_SysTrgStart(MONO(NA_SE_A));
    } else {
        int i;
        int cnt;
        if (inv_cnt > 0) {
            for (cnt = 0, i = 0; cnt < inv_cnt && i < mPr_INVENTORY_MAIL_COUNT; i++) {
                if ((inv_ovl->mail_mark_bitfield2 & (1 << i)) != 0) {
                    inv_ovl->mail_mark_bitfield2 &= ~(1 << i);
                    cnt++;
                }
            }
        }

        if (cpmail_cnt > 0) {
            for (cnt = 0, i = 0; cnt < cpmail_cnt && i < mCM_MAIL_COUNT; i++) {
                if ((cpmail_ovl->mark_bitfield & (1 << i)) != 0) {
                    cpmail_ovl->mark_bitfield &= ~(1 << i);
                    cnt++;
                }
            }
        }

        inv_ovl->mail_mark_flag = 2;
        cpmail_ovl->mark_flag = 2;
        sAdo_SysTrgStart(NA_SE_MENU_EXIT);
    }

    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
}

static void mTG_dump_mail_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

    inv_ovl->remove_timer = 24;
    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
    sAdo_SysTrgStart(NA_SE_435);
}

static void mTG_dump_item_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

    inv_ovl->remove_timer = 12;
    inv_ovl->item_scale_type[idx] = mIV_ITEM_SCALE_TYPE_SHRINK;
    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
    sAdo_SysTrgStart(NA_SE_435);
}

static void mTG_send_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    Mail_c* mail = &Now_Private->mail[idx];
    Submenu_Item_c* item_p = submenu->item_p;

    mail->content.font = mMl_FONT_0;
    mMl_copy_mail(&submenu->mail, mail);
    mMl_clear_mail(mail);
    item_p->slot_no = idx;
    item_p->item = ITM_QST_LETTER;
    submenu->selected_item_num = 1;
    submenu->after_mode = aHOI_REQUEST_PUTAWAY;
    mPlib_request_main_give_from_submenu(item_p->item, submenu->after_mode, FALSE, TRUE);
    mTG_close_window(submenu, menu_info, TRUE);
}

static void mTG_rewrite_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_open_board_init(submenu, menu_info, -1, mSM_BD_OPEN_REWRITE, -1);
}

static void mTG_stick_select_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];

    mTG_chg_tag_func2(submenu, menu_info, tag, mTG_TYPE_TAG_NW_SEL_STK_PATTERN);
    sAdo_SysTrgStart(NA_SE_33);
}

static void mTG_nw_carpet_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    int changed_flag = TRUE;
    int change_org_flag = FALSE;
    int img_no;

    if (tag_ovl->tags[3].tag_row == 1) {
        change_org_flag = TRUE;
    }

    if (mRmTp_CheckFloorIsMyOriginalInThisScene()) {
        if (change_org_flag) {
            img_no = mNW_get_image_no(submenu, idx) & 7;
            CLIP(my_indoor_clip)->floor_idx_2_change_floor_proc(FLOOR_MY_ORIG_START + img_no, TRUE);
        } else {
            img_no = mNW_get_image_no(submenu, idx) & 7;
            CLIP(my_indoor_clip)->floor_idx_2_change_floor_proc(FLOOR_MY_ORIG_START + img_no, FALSE);
        }
    } else {
        int free_idx = mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO);

        if (free_idx >= 0) {
            mActor_name_t* item_p = &Now_Private->inventory.pockets[free_idx];

            if (change_org_flag) {
                img_no = mNW_get_image_no(submenu, idx) & 7;
                *item_p = CLIP(my_indoor_clip)->floor_idx_2_change_floor_proc(FLOOR_MY_ORIG_START + img_no, TRUE);
            } else {
                img_no = mNW_get_image_no(submenu, idx) & 7;
                *item_p = CLIP(my_indoor_clip)->floor_idx_2_change_floor_proc(FLOOR_MY_ORIG_START + img_no, FALSE);
            }
        } else {
            mTG_open_warning_window(submenu, menu_info, mWR_WARNING_ORIGINAL);
            changed_flag = FALSE;
        }
    }

    if (changed_flag) {
        if (inv_ovl != NULL) {
            inv_ovl->original_flag = TRUE;
        }

        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
        mTG_close_window(submenu, menu_info, FALSE);
    }
}

static void mTG_carpet_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);

    if (CLIP(my_indoor_clip) != NULL) {
        mActor_name_t* item_p = &Now_Private->inventory.pockets[idx];

        if (mRmTp_CheckFloorIsMyOriginalInThisScene()) {
            CLIP(my_indoor_clip)->change_carpet_proc(*item_p);
            *item_p = EMPTY_NO;
        } else {
            mActor_name_t item;

            item = CLIP(my_indoor_clip)->change_carpet_proc(*item_p);
            *item_p = item;
        }

        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
        mTG_close_window(submenu, menu_info, FALSE);
    }
}

static void mTG_nw_cover_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    int changed_flag = TRUE;
    int change_org_flag = FALSE;
    int img_no;

    if (tag_ovl->tags[3].tag_row == 1) {
        change_org_flag = TRUE;
    }

    if (mRmTp_CheckWallIsMyOriginalInThisScene()) {
        if (change_org_flag) {
            img_no = mNW_get_image_no(submenu, idx) & 7;
            CLIP(my_indoor_clip)->wall_idx_2_change_wall_proc(WALL_MY_ORIG_START + img_no, TRUE);
        } else {
            img_no = mNW_get_image_no(submenu, idx) & 7;
            CLIP(my_indoor_clip)->wall_idx_2_change_wall_proc(WALL_MY_ORIG_START + img_no, FALSE);
        }
    } else {
        int free_idx = mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO);

        if (free_idx >= 0) {
            mActor_name_t* item_p = &Now_Private->inventory.pockets[free_idx];

            if (change_org_flag) {
                img_no = mNW_get_image_no(submenu, idx) & 7;
                *item_p = CLIP(my_indoor_clip)->wall_idx_2_change_wall_proc(WALL_MY_ORIG_START + img_no, TRUE);
            } else {
                img_no = mNW_get_image_no(submenu, idx) & 7;
                *item_p = CLIP(my_indoor_clip)->wall_idx_2_change_wall_proc(WALL_MY_ORIG_START + img_no, FALSE);
            }
        } else {
            mTG_open_warning_window(submenu, menu_info, mWR_WARNING_ORIGINAL);
            changed_flag = FALSE;
        }
    }

    if (changed_flag) {
        if (inv_ovl != NULL) {
            inv_ovl->original_flag = TRUE;
        }

        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
        mTG_close_window(submenu, menu_info, FALSE);
    }
}

static void mTG_cover_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);

    if (CLIP(my_indoor_clip) != NULL) {
        mActor_name_t* item_p = &Now_Private->inventory.pockets[idx];

        if (mRmTp_CheckWallIsMyOriginalInThisScene()) {
            CLIP(my_indoor_clip)->change_wall_proc(*item_p);
            *item_p = EMPTY_NO;
        } else {
            mActor_name_t item;

            item = CLIP(my_indoor_clip)->change_wall_proc(*item_p);
            *item_p = item;
        }

        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
        mTG_close_window(submenu, menu_info, FALSE);
    }
}

static void mTG_putin_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    Submenu_Item_c* item_p = submenu->item_p;

    item_p->item = Now_Private->inventory.pockets[idx];
    item_p->slot_no = idx;
    submenu->selected_item_num = 1;

    if (menu_info->data0 == 10) {
        if (ChkRoomMusicBox((u32)(item_p->item - ITM_MINIDISK_START))) {
            item_p->item = EMPTY_NO;
            mTG_open_warning_window(submenu, menu_info, mWR_WARNING_MUSIC2);
        } else {
            SetRoomMusicBox((u32)(item_p->item - ITM_MINIDISK_START));
            mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
            mTG_close_window(submenu, menu_info, TRUE);
        }
    } else {
        if (menu_info->data0 != 11) {
            mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
        }

        mTG_close_window(submenu, menu_info, TRUE);
    }
}

static void mTG_music_listen_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    Submenu_Item_c* item_p = submenu->item_p;

    item_p->item = ITM_MINIDISK_START + idx;
    item_p->slot_no = idx;
    submenu->selected_item_num = 1;
    mTG_close_window(submenu, menu_info, TRUE);
}

static void mTG_music_takeout_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    mMU_Ovl_c* music_ovl = submenu->overlay->music_ovl;
    u32 mark_cnt = 0;
    int free_idx;
    int i;

    for (i = 0; i < MINIDISK_NUM; i++) {
        if (ChkMusicBox(music_ovl->mark_flg, i)) {
            mark_cnt++;
        }
    }

    if (mark_cnt == 0 || ChkMusicBox(music_ovl->mark_flg, idx) == FALSE) {
        if (mPr_GetPossessionItemSum(Now_Private, EMPTY_NO) >= 1) {
            free_idx = mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO);

            if (free_idx >= 0) {
                ClrRoomMusicBox(idx);
                mPr_SetPossessionItem(Now_Private, free_idx, ITM_MINIDISK_START + idx, mPr_ITEM_COND_NORMAL);
            }

            mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
            mTG_close_window(submenu, menu_info, TRUE);
        } else {
            mTG_open_warning_window(submenu, menu_info, mWR_WARNING_MUSIC);
        }
    } else {
        if (mPr_GetPossessionItemSum(Now_Private, EMPTY_NO) >= 1) {
            for (i = 0; i < MINIDISK_NUM; i++) {
                if (ChkMusicBox(music_ovl->mark_flg, i)) {
                    free_idx = mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO);

                    if (free_idx >= 0) {
                        ClrRoomMusicBox(i);
                        mPr_SetPossessionItem(Now_Private, free_idx, ITM_MINIDISK_START + i, mPr_ITEM_COND_NORMAL);
                    }
                }
            }

            mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
            mTG_close_window(submenu, menu_info, TRUE);
        } else {
            mTG_open_warning_window(submenu, menu_info, mWR_WARNING_MUSIC);
        }
    }
}

static void mTG_island_check_plant_plant(mActor_name_t item) {
    if (item == ITM_SAPLING || item == ITM_CEDAR_SAPLING) {
        mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_TREE);
    } else if (ITEM_IS_FLOWER_BAG(item)) {
        mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_FLOWER);
    }
}

static void mTG_island_check_fruit_plant(mActor_name_t item) {
    switch (item) {
        case ITM_FOOD_APPLE:
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_APPLE_TREE);
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_TREE);
            break;
        case ITM_FOOD_CHERRY:
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_CHERRY_TREE);
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_TREE);
            break;
        case ITM_FOOD_PEAR:
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_PEAR_TREE);
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_TREE);
            break;
        case ITM_FOOD_PEACH:
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_PEACH_TREE);
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_TREE);
            break;
        case ITM_FOOD_ORANGE:
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_ORANGE_TREE);
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_TREE);
            break;
        case ITM_FOOD_COCONUT:
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_COCONUT_TREE);
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_TREE);
            break;
    }
}

static void mTG_island_check_fruit_eat(mActor_name_t item) {
    if (item == ITM_FOOD_COCONUT) {
        mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_EAT_COCONUT);
    }
}

static void mTG_plant_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    ACTOR* player = GET_PLAYER_ACTOR_ACTOR(play);
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    mActor_name_t plant_item;
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    xyz_t pos;

    plant_item = Now_Private->inventory.pockets[idx];

    if (((Now_Private->equipment >= ITM_SHOVEL && Now_Private->equipment <= ITM_SHOVEL) ||
         (Now_Private->equipment >= ITM_GOLDEN_SHOVEL && Now_Private->equipment <= ITM_GOLDEN_SHOVEL)) &&
        inv_ovl->shovel_flag == TRUE) {
        mTG_island_check_plant_plant(plant_item);
        mTG_island_check_fruit_plant(plant_item);
        mPlib_request_main_putin_scoop_from_submenu(&inv_ovl->shovel_pos, Now_Private->inventory.pockets[idx], FALSE);
        mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
        mTG_close_window(submenu, menu_info, TRUE);
        return;
    } else {
        if (mTG_search_put_pos(player, &pos, TRUE, plant_item == ITM_SIGNBOARD, plant_item == ITM_SIGNBOARD, FALSE,
                               FALSE)) {
            mActor_name_t item = Now_Private->inventory.pockets[idx];
            mActor_name_t throw_item;

            mTG_island_check_plant_plant(item);
            if (item == ITM_SAPLING) {
                throw_item = TREE_SAPLING;
            } else if (item == ITM_CEDAR_SAPLING) {
                throw_item = CEDAR_TREE_SAPLING;
            } else {
                throw_item = FLOWER_PANSIES0 + (item - ITM_WHITE_PANSY_BAG);
            }

            if (mTG_common_throw_put_field(play, throw_item, &pos, mCoBG_LAYER0)) {
                mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(pos, 0.0f);
                sAdo_OngenTrgStart(NA_SE_2A, &pos);
                mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
                mTG_close_window(submenu, menu_info, TRUE);
                return;
            }
        }
    }

    mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_PLANT);
}

static int mTG_check_island_famicom(mActor_name_t item) {
    int res = TRUE;

    if (mFI_CheckInIsland() &&
        (mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_HOMEPAGE, NULL) ||
         mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_SPECIALPRESENT, NULL))) {
        res = FALSE;
    }

    return res;
}

static void mTG_field_put_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    ACTOR* player = GET_PLAYER_ACTOR_ACTOR(play);
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    mActor_name_t put_item = Now_Private->inventory.pockets[idx];
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    xyz_t pos;

    if (inv_ovl->item_mark_bitfield != 0 && (inv_ovl->item_mark_bitfield & (1 << idx)) != 0) {
        int i;
        int put_cnt = 0;
        int bad_famicom_cnt = 0;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if ((inv_ovl->item_mark_bitfield & (1 << i)) != 0) {
                mActor_name_t item = Now_Private->inventory.pockets[i];

                if (mTG_check_island_famicom(item)) {
                    if (mTG_search_put_pos(player, &pos, item == ITM_SIGNBOARD, FALSE, item == ITM_SIGNBOARD,
                                           item == ITM_SIGNBOARD, item == ITM_SIGNBOARD) &&
                        mTG_common_throw_put_field(play, item, &pos, put_cnt)) {
                        mPr_SetPossessionItem(Now_Private, i, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                        put_cnt++;
                    }
                } else {
                    bad_famicom_cnt++;
                }
            }
        }

        if (put_cnt != 0) {
            mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
            mTG_close_window(submenu, menu_info, TRUE);
        } else if (bad_famicom_cnt != 0) {
            mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_FAMI);
        } else {
            mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_ITEM);
        }

        inv_ovl->item_mark_bitfield = 0;
    } else {
        if (put_item == ITM_SIGNBOARD && (mFI_CheckInIsland() || mLd_PlayerManKindCheck())) {
            if (mFI_CheckInIsland()) {
                mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_SIGN_ISLAND);
            } else {
                mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_SIGN_OTHER);
            }
        } else if ((mSP_SearchItemCategoryPriority(put_item, mSP_KIND_FURNITURE, mSP_LISTTYPE_HOMEPAGE, NULL) ||
                    mSP_SearchItemCategoryPriority(put_item, mSP_KIND_FURNITURE, mSP_LISTTYPE_SPECIALPRESENT, NULL)) &&
                   mFI_CheckInIsland()) {
            mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_FAMI);
        } else {
            if (mTG_search_put_pos(player, &pos, put_item == ITM_SIGNBOARD, FALSE, put_item == ITM_SIGNBOARD,
                                   put_item == ITM_SIGNBOARD, put_item == ITM_SIGNBOARD) &&
                mTG_common_throw_put_field(play, put_item, &pos, mCoBG_LAYER0)) {
                if (menu_info->data0 == 13) {
                    mPr_SetPossessionItem(Now_Private, idx, (mActor_name_t)menu_info->data1, mPr_ITEM_COND_NORMAL);
                    mPlib_request_main_wait_from_submenu();
                } else {
                    mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                }

                mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
                mTG_close_window(submenu, menu_info, FALSE);
            } else {
                if (put_item == ITM_SIGNBOARD) {
                    mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_SIGN);
                } else {
                    mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_ITEM);
                }
            }
        }
    }
}

static void mTG_room_put_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    ACTOR* player = GET_PLAYER_ACTOR_ACTOR(play);
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx;
    mActor_name_t put_item;
    mIV_Ovl_c* inv_ovl;
    int ftrID;
    xyz_t pos;
    xyz_t ut_pos;
    int ux;
    int uz;

    idx = mTG_get_table_idx(tag);
    put_item = mRmTp_Item1ItemNo2FtrItemNo_AtPlayerRoom(Now_Private->inventory.pockets[idx], TRUE);
    inv_ovl = submenu->overlay->inventory_ovl;

    switch (ITEM_NAME_GET_TYPE(put_item)) {
        case NAME_TYPE_FTR0:
        case NAME_TYPE_FTR1:
            if (!mFI_CheckInIsland() ||
                !(mSP_SearchItemCategoryPriority(put_item, mSP_KIND_FURNITURE, mSP_LISTTYPE_HOMEPAGE, NULL) ||
                  mSP_SearchItemCategoryPriority(put_item, mSP_KIND_FURNITURE, mSP_LISTTYPE_SPECIALPRESENT, NULL))) {
                ftrID = mTG_drop_furniture(play, put_item);
                if (ftrID >= 0) {
                    mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
                    mTG_close_window(submenu, menu_info, FALSE);
                    mMkRm_ReportChangePlayerRoom();
                } else {
                    if (ftrID == -1) {
                        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_MAX_FURNITURE);
                    } else {
                        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_FURNITURE);
                    }
                }
            } else {
                mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_FAMI);
            }
            break;
        case NAME_TYPE_ITEM1:
            xyz_t_move(&pos, &player->world.position);
            if (inv_ovl->item_mark_bitfield != 0 && (inv_ovl->item_mark_bitfield & (1 << idx)) != 0) {
                int i;
                int cnt = 0;

                for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
                    if ((inv_ovl->item_mark_bitfield & (1 << i)) != 0) {
                        mActor_name_t item =
                            mRmTp_Item1ItemNo2FtrItemNo_AtPlayerRoom(Now_Private->inventory.pockets[i], TRUE);

                        if (mTG_search_put_pos(player, &pos, FALSE, FALSE, cnt, FALSE, FALSE) &&
                            mTG_common_throw_put_room(play, item, &pos, mCoBG_LAYER0, cnt)) {
                            mPr_SetPossessionItem(Now_Private, i, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                            cnt++;
                        }
                    }
                }

                if (cnt > 0) {
                    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
                    mMkRm_ReportChangePlayerRoom();
                    mTG_close_window(submenu, menu_info, FALSE);
                } else {
                    mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_ITEM);
                }
            } else {
                if (aMR_CLIP != NULL) {
                    mTG_get_unit_front_player(&ut_pos, &pos, player->shape_info.rotation.y);
                    if (mTG_check_free_2nd_layer(&ut_pos)) {
                        if (mFI_Wpos2UtNum(&ux, &uz, ut_pos) && aMR_CLIP->judge_place_2nd_layer_proc(ux, uz) &&
                            mTG_common_throw_put_room(play, put_item, &ut_pos, mCoBG_LAYER1, 0)) {
                            mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                            mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
                            mTG_close_window(submenu, menu_info, FALSE);
                            mMkRm_ReportChangePlayerRoom();
                            return;
                        }
                    }
                }

                if (mTG_search_put_pos(player, &pos, FALSE, FALSE, 0, FALSE, FALSE) &&
                    mTG_common_throw_put_room(play, put_item, &pos, mCoBG_LAYER0, 0)) {
                    mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
                    mMkRm_ReportChangePlayerRoom();
                    mTG_close_window(submenu, menu_info, FALSE);
                } else {
                    mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_ITEM);
                }
            }
            break;
    }
}

static void mTG_put_all_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    switch (Common_Get(field_type)) {
        case mFI_FIELDTYPE2_FG:
            mTG_field_put_proc(submenu, menu_info);
            break;
        case mFI_FIELDTYPE2_PLAYER_ROOM:
            mTG_room_put_proc(submenu, menu_info);
            break;
        case mFI_FIELDTYPE2_NPC_ROOM:
            break;
        case mFI_FIELDTYPE2_ROOM:
            break;
        default:
            break;
    }
}

static void mTG_dump_mail_mark_conf_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];

    mTG_chg_tag_func2(submenu, menu_info, tag, mTG_TYPE_DUMP_MAIL_MARK_CONF);
    sAdo_SysTrgStart(NA_SE_33);
}

static void mTG_next_open_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];
    int next_type;

    if (tag->type == mTG_TYPE_CP_DELETE) {
        next_type = mTG_TYPE_CP_DELETE2;
    } else if (tag->type == mTG_TYPE_TAISOU_CARD || tag->type == mTG_TYPE_FIELD_SIGN) {
        next_type = mTG_TYPE_DUMP_ITEM;
    } else {
        next_type = mTG_TYPE_DUMP_MAIL;
    }

    mTG_chg_tag_func2(submenu, menu_info, tag, next_type);
    sAdo_SysTrgStart(NA_SE_33);
}

static void mTG_next_open_needlework_sel_stick_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];
    int next_type;

    /* @BUG - if Save::field_type is out of the normal enum value range then next_type will be undefined */
    switch (Common_Get(field_type)) {
        case mFI_FIELDTYPE2_PLAYER_ROOM:
            if (Save_Get(scene_no) == SCENE_COTTAGE_MY || mSc_IS_SCENE_BASEMENT(Save_Get(scene_no))) {
                next_type = mTG_TYPE_TAG_NW_OR_SEL_STICK;
            } else {
                next_type = mTG_TYPE_TAG_NW_MR_SEL_STICK;
            }
            break;
        case mFI_FIELDTYPE2_FG:
        case mFI_FIELDTYPE2_NPC_ROOM:
        case mFI_FIELDTYPE2_ROOM:
#ifdef BUGFIXES
        default:
#endif
            next_type = mTG_TYPE_TAG_NW_OR_SEL_STICK;
            break;
    }

    mTG_chg_tag_func2(submenu, menu_info, tag, next_type);
    sAdo_SysTrgStart(NA_SE_33);
}

static void mTG_next_open_needlework_sel_put_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];

    mTG_chg_tag_func2(submenu, menu_info, tag, mTG_TYPE_TAG_NW_SEL_PUT);
    sAdo_SysTrgStart(NA_SE_33);
}

static void mTG_free_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_set_trade_cond(submenu, menu_info, mHm_HANIWA_TRADE_0, 0);
}

static void mTG_catch_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    mTG_tag_c* cur_tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];
    int idx = 0;
    int item_cond = mPr_ITEM_COND_NORMAL;
    mActor_name_t* item_p = NULL;
    Mail_c* mail_p = NULL;

    if (cur_tag->table == mTG_TABLE_ITEM) {
        idx = mTG_get_table_idx(tag);
        item_p = &Now_Private->inventory.pockets[idx];
        item_cond = mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, idx);
        if (*item_p != EMPTY_NO) {
            mQst_CheckGrabItem(*item_p, idx);
        }
    } else if (cur_tag->table == mTG_TABLE_MAIL || cur_tag->table == mTG_TABLE_MBOX ||
               cur_tag->table == mTG_TABLE_CPMAIL) {
        idx = mTG_get_table_idx(tag);
        mail_p = mTG_get_mail_pointer(submenu, NULL);

        if (mMl_check_not_used_mail(mail_p) == TRUE) {
            return;
        }

        if (submenu->overlay->tag_ovl->sel_tag_idx == 0 && menu_info->menu_type != mSM_OVL_MAILBOX &&
            menu_info->menu_type != mSM_OVL_CPMAIL) {
            item_p = &mail_p->present;
            if (*item_p != EMPTY_NO) {
                if (mMl_check_set_present_myself(mail_p)) {
                    item_cond = mPr_ITEM_COND_NORMAL;
                    mail_p = NULL;
                } else if (mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO) != -1) {
                    item_cond = mPr_ITEM_COND_PRESENT;
                    mail_p = NULL;
                } else {
                    item_p = NULL;
                }
            } else {
                item_p = NULL;
            }
        }
    } else {
        mActor_name_t item;

        switch (cur_tag->table) {
            case mTG_TABLE_HANIWA:
                idx = tag->tag_col;
                item_p = &Save_Get(homes[menu_info->data1]).haniwa.items[idx].item;
                break;
            case mTG_TABLE_PLAYER:
                item_p = &Now_Private->equipment;
                break;
            case mTG_TABLE_MONEY:
                mTG_make_money_sack(submenu, menu_info, ITM_MONEY_100);
                return;
            case mTG_TABLE_NEEDLEWORK:
            case mTG_TABLE_CPORIGINAL_NW:
                idx = mTG_get_table_idx(tag);
                item_p = &item;
                item = RSV_NW_ORIGINAL0 + idx;
                break;
            case mTG_TABLE_CPORIGINAL:
                idx = mTG_get_table_idx(tag);
                item = RSV_CPORIGINAL_FLD0_00 + mCO_top_folder(submenu) * mCO_ORIGINAL_NUM + idx;
                item_p = &item;
                break;
            case mTG_TABLE_GBA:
            case mTG_TABLE_CARD:
                idx = mTG_get_table_idx(tag);
                item_p = &item;
                item = RSV_GBAORIGINAL0 + idx;
                break;
        }
    }

    if (mail_p != NULL || (item_p != NULL && *item_p != EMPTY_NO)) {
        mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;

        mTG_mark_main_CLR(submenu, menu_info);
        if (cur_tag->table == mTG_TABLE_HANIWA) {
            hand_ovl->info.haniwa_item_cond = Save_Get(homes[menu_info->data1]).haniwa.items[idx].exchange_type;
            hand_ovl->info.haniwa_item_price = Save_Get(homes[menu_info->data1]).haniwa.items[idx].extra_data;
        } else {
            hand_ovl->info.haniwa_item_cond = mPr_ITEM_COND_PRESENT;
            hand_ovl->info.haniwa_item_price = 0;
        }

        mTG_catch_item_from_table(submenu, mail_p, item_p, item_cond, cur_tag->table, idx);
        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_NONE);
    }
}

static int mTG_mail_check(Mail_c* mail) {
    int flags = 0;

    if (mail->present != EMPTY_NO) {
        flags |= mTG_MAIL_FLAG_PRESENT;
    }

    if (!mMl_check_send_mail(mail)) {
        flags |= mTG_MAIL_FLAG_RECV;
    }

    return flags;
}

static void mTG_password_item_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    Submenu_Item_c* item_p = submenu->item_p;

    if (mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, idx) == mPr_ITEM_COND_QUEST) {
        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_SELL_QUEST_ITEM);
    } else {
        item_p->item = Now_Private->inventory.pockets[idx];
        item_p->slot_no = idx;
        submenu->selected_item_num = 1;
        mTG_close_window(submenu, menu_info, TRUE);
    }
}

static int mTG_mark_enable_check(int menu_type, int param, int table, u8 field_type) {
    int res = mTG_MARK_TYPE_NONE;

    switch (menu_type) {
        case mSM_OVL_INVENTORY:
            switch (param) {
                case mSM_IV_OPEN_NORMAL:
                    switch (table) {
                        case mTG_TABLE_ITEM:
                            switch (field_type) {
                                case mFI_FIELDTYPE2_FG:
                                    res = mTG_MARK_TYPE_INV_FG_ITEM;
                                    break;
                                case mFI_FIELDTYPE2_PLAYER_ROOM:
                                    res = mTG_MARK_TYPE_INV_PLAYERROOM_ITEM;
                                    break;
                                default:
                                    res = mTG_MARK_TYPE_INV_OTHERROOM_ITEM;
                                    break;
                            }
                            break;
                        case mTG_TABLE_MAIL:
                            if (field_type == mFI_FIELDTYPE2_FG) {
                                res = mTG_MARK_TYPE_INV_FG_MAIL;
                            }
                            break;
                    }
                    break;
                case mSM_IV_OPEN_MAILBOX:
                    res = mTG_MARK_TYPE_INV_MAILBOX;
                    break;
                case mSM_IV_OPEN_SELL:
                    if (table == mTG_TABLE_ITEM) {
                        res = mTG_MARK_TYPE_INV_SELL_ITEM;
                    }
                    break;
            }
            break;
        case mSM_OVL_MAILBOX:
            res = mTG_MARK_TYPE_MAILBOX;
            break;
        case mSM_OVL_CPMAIL:
            switch (table) {
                case mTG_TABLE_CPMAIL:
                    res = mTG_MARK_TYPE_CPMAIL_CPMAIL;
                    break;
                case mTG_TABLE_MAIL:
                    res = mTG_MARK_TYPE_CPMAIL_MAIL;
                    break;
            }
            break;
        case mSM_OVL_MUSIC:
            res = mTG_MARK_TYPE_MUSIC;
            break;
        case mSM_OVL_NEEDLEWORK:
            // scrapped?
            break;
        case mSM_OVL_CPORIGINAL:
            // scrapped?
            break;
    }

    return res;
}

typedef union tag_mark_field_u {
    u16 field16;
    u32 field32;
    u32 music_box[2];
    u8 u8array[8];
} mTG_mark_field_u;

static int mTG_mark_main_sub(Submenu* submenu, int menu_type, int param, int table, int table_idx, Mail_c* mail,
                             int mode, mTG_mark_field_u** mark_bitfield_p, int* max_mark_count,
                             mTG_mark_field_u* updated_mark_bitfield) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    mMB_Ovl_c* mailbox_ovl = submenu->overlay->mailbox_ovl;
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    mMU_Ovl_c* music_ovl = submenu->overlay->music_ovl;
    mNW_Ovl_c* needlework_ovl = submenu->overlay->needlework_ovl;
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    int mark_type;

    mark_type = mTG_mark_enable_check(menu_type, param, table, Common_Get(field_type));
    switch (mark_type) {
        case mTG_MARK_TYPE_NONE:
            return FALSE;
        case mTG_MARK_TYPE_INV_FG_ITEM:
        case mTG_MARK_TYPE_INV_PLAYERROOM_ITEM: {
            mActor_name_t item = Now_Private->inventory.pockets[table_idx];
            u32 cond = mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, table_idx);
            int type;
            int category;

            category = ITEM_NAME_GET_CAT(item);
            type = ITEM_NAME_GET_TYPE(item);
            *(u16**)mark_bitfield_p = &inv_ovl->item_mark_bitfield;
            updated_mark_bitfield->field16 = 1 << table_idx;
            *max_mark_count = mPr_POCKETS_SLOT_COUNT;

            if ((mode == mTG_MARK_CHK || mode == mTG_MARK_OFF || mode == mTG_MARK_CLR) ||
                (item != EMPTY_NO && cond == mPr_ITEM_COND_NORMAL && !ITEM_IS_EXERCISE_CARD(item) &&
                 item != ITM_KNIFE_AND_FORK && !ITEM_IS_BALLOON(item) &&
                 (type != NAME_TYPE_ITEM1 || (category != ITEM1_CAT_FISH && category != ITEM1_CAT_INSECT)) &&
                 (mark_type != mTG_MARK_TYPE_INV_FG_ITEM ||
                  (mark_type == mTG_MARK_TYPE_INV_FG_ITEM && item != ITM_SIGNBOARD)) &&
                 (mark_type != mTG_MARK_TYPE_INV_PLAYERROOM_ITEM ||
                  ((mark_type == mTG_MARK_TYPE_INV_PLAYERROOM_ITEM && type != NAME_TYPE_FTR0 &&
                    type != NAME_TYPE_FTR1) &&
                   (!ITEM_IS_UMBRELLA(item) && !ITEM_IS_CLOTH(item)))) &&
                 (mEv_CheckFirstJob() == FALSE || mark_type == mTG_MARK_TYPE_INV_PLAYERROOM_ITEM ||
                  type != NAME_TYPE_ITEM1 || category != ITEM1_CAT_PLANT))) {
                return TRUE;
            }
            return FALSE;
        }
        case mTG_MARK_TYPE_INV_OTHERROOM_ITEM:
            return FALSE;
        case mTG_MARK_TYPE_INV_SELL_ITEM: {
            mActor_name_t item = Now_Private->inventory.pockets[table_idx];

            *(u16**)mark_bitfield_p = &inv_ovl->item_mark_bitfield;
            updated_mark_bitfield->field16 = 1 << table_idx;
            *max_mark_count = mPr_POCKETS_SLOT_COUNT;

            if ((mode == mTG_MARK_CHK || mode == mTG_MARK_OFF || mode == mTG_MARK_CLR) ||
                (item != EMPTY_NO && !ITEM_IS_EXERCISE_CARD(item) && item != ITM_KNIFE_AND_FORK &&
                 (ITEM_NAME_GET_TYPE(item) != NAME_TYPE_ITEM1 || (ITEM_NAME_GET_CAT(item) != ITEM1_CAT_MONEY)) &&
                 (Common_Get(time.rtc_time).weekday != lbRTC_SUNDAY ||
                  (ITEM_NAME_GET_TYPE(item) != NAME_TYPE_ITEM1 || (ITEM_NAME_GET_CAT(item) != ITEM1_CAT_KABU))))) {
                return TRUE;
            }
            return FALSE;
        }
        case mTG_MARK_TYPE_INV_FG_MAIL:
        case mTG_MARK_TYPE_INV_MAILBOX:
        case mTG_MARK_TYPE_CPMAIL_MAIL:
        case mTG_MARK_TYPE_MAILBOX:
        case mTG_MARK_TYPE_CPMAIL_CPMAIL: {
            if (table == mTG_TABLE_MAIL) {
                *(u16**)mark_bitfield_p = &inv_ovl->mail_mark_bitfield2;
                updated_mark_bitfield->field16 = 1 << table_idx;
                *max_mark_count = mPr_INVENTORY_MAIL_COUNT;

                if (mode != mTG_MARK_CHK && mode != mTG_MARK_OFF && mode != mTG_MARK_CLR) {
                    if (mMl_check_not_used_mail(mail) == TRUE) {
                        return FALSE;
                    }

                    if (menu_type == mSM_OVL_MAILBOX) {
                        if (mail->present != EMPTY_NO ||
                            (mail->content.font != mMl_FONT_2 && mail->content.font != mMl_FONT_4) ||
                            (mTG_mail_check(mail) & mTG_MAIL_FLAG_RECV) != mTG_MAIL_FLAG_RECV) {
                            return FALSE;
                        }
                    } else if (menu_type == mSM_OVL_CPMAIL) {
                        if ((mTG_mail_check(mail) & mTG_MAIL_FLAG_RECV) != mTG_MAIL_FLAG_RECV) {
                            return FALSE;
                        }
                    } else {
                        if ((mail->content.font != mMl_FONT_2 && mail->content.font != mMl_FONT_4) ||
                            (mTG_mail_check(mail) & mTG_MAIL_FLAG_RECV) != mTG_MAIL_FLAG_RECV ||
                            (mTG_mail_check(mail) & mTG_MAIL_FLAG_PRESENT) == mTG_MAIL_FLAG_PRESENT) {
                            return FALSE;
                        }
                    }
                }

                return TRUE;
            } else if (table == mTG_TABLE_MBOX) {
                *(u16**)mark_bitfield_p = &mailbox_ovl->mark_bitfield;
                updated_mark_bitfield->field16 = 1 << table_idx;
                *max_mark_count = HOME_MAILBOX_SIZE;

                if ((mode != mTG_MARK_CHK || mode != mTG_MARK_OFF || mode != mTG_MARK_CLR)) {
                    if (mMl_check_not_used_mail(mail) == TRUE ||
                        (mTG_mail_check(mail) & mTG_MAIL_FLAG_RECV) != mTG_MAIL_FLAG_RECV) {
                        return FALSE;
                    }
                    return TRUE;
                }
            } else if (table == mTG_TABLE_CPMAIL) {
                if ((mode != mTG_MARK_CHK || mode != mTG_MARK_OFF || mode != mTG_MARK_CLR)) {
                    if (mMl_check_not_used_mail(mail) == TRUE ||
                        (mTG_mail_check(mail) & mTG_MAIL_FLAG_RECV) != mTG_MAIL_FLAG_RECV) {
                        return FALSE;
                    }
                }

                *(u32**)mark_bitfield_p = &cpmail_ovl->mark_bitfield;
                updated_mark_bitfield->field32 = 1 << table_idx;
                *max_mark_count = mCM_MAIL_COUNT;
            } else {
                return FALSE;
            }
            break;
        }
        case mTG_MARK_TYPE_MUSIC: {
            *(u32**)mark_bitfield_p = music_ovl->mark_flg;
            updated_mark_bitfield->music_box[(table_idx / 32)] = 1 << ((u32)table_idx - (table_idx / 32) * 32);
            // SetMusicBox(updated_mark_bitfield->music_box, table_idx);
            *max_mark_count = MINIDISK_NUM;

            if ((mode != mTG_MARK_CHK || mode != mTG_MARK_OFF || mode != mTG_MARK_CLR)) {
                if (!ChkRoomMusicBox(table_idx)) {
                    return FALSE;
                }
            }
            break;
        }
        case mTG_MARK_TYPE_NEEDLEWORK_ORIGINAL:
            *(u16**)mark_bitfield_p = &needlework_ovl->mark_flg;
            updated_mark_bitfield->field16 = 1 << table_idx;
            *max_mark_count = mPr_ORIGINAL_DESIGN_COUNT;

            if (mode == mTG_MARK_CHK || mode == mTG_MARK_OFF || mode == mTG_MARK_CLR) {
                if (mNW_check_hide_flg(submenu, table_idx)) {
                    return FALSE;
                }
            }
            break;
        case mTG_MARK_TYPE_CPORIGINAL_ORIGINAL:
            *(u16**)mark_bitfield_p = &cporiginal_ovl->mark_flg;
            updated_mark_bitfield->field16 = 1 << table_idx;
            *max_mark_count = mCO_ORIGINAL_NUM;

            if (mode == mTG_MARK_CHK || mode == mTG_MARK_OFF || mode == mTG_MARK_CLR) {
                if (mCO_check_hide_flg(submenu, mCO_top_folder(submenu), table_idx)) {
                    return FALSE;
                }
            }
            break;
    }

    return TRUE;
}

static int mTG_bit_chk(u8* flags, u8* masks, int count) {
    int res = 0;
    int i;

    for (i = 0; i < count; i++) {
        res |= *flags++ & *masks++;
    }

    return res;
}

static void mTG_bit_on(u8* flags, u8* bits, int count) {
    int i;

    for (i = 0; i < count; i++) {
        *flags++ |= *bits++;
    }
}

static void mTG_bit_off(u8* flags, u8* bits, int count) {
    int i;

    for (i = 0; i < count; i++) {
        *flags++ &= ~*bits++;
    }
}

static void mTG_bit_rvs(u8* flags, u8* bits, int count) {
    int i;

    for (i = 0; i < count; i++) {
        *flags++ ^= *bits++;
    }
}

static void mTG_bit_clr(u8* flags, u8* bits, int count) {
    int i;

    for (i = 0; i < count; i++) {
        *flags++ = 0;
    }
}

static int mTG_bit_chk_all0(u8* flags, u8* bits, int count) {
    int res = 0;
    int i;

    for (i = 0; i < count; i++) {
        res |= *flags++ == 0;
    }

    return res;
}

static int mTG_mark_mainX(Submenu* submenu, mSM_MenuInfo_c* menu_info, int table, int table_idx, int mode,
                          int* chk_result) {
    int mark_res;
    Mail_c* mail;
    mTG_mark_field_u set_flags;
    mTG_mark_field_u* current_flags_p;
    int max_flag_count;
    int chk_res = FALSE;
    int i;

    for (i = 0; i < 8; i++) {
        set_flags.u8array[i] = 0;
    }

    mail = mTG_get_mail_pointer(submenu, NULL);
    mark_res = mTG_mark_main_sub(submenu, menu_info->menu_type, menu_info->data0, table, table_idx, mail, mode,
                                 &current_flags_p, &max_flag_count, &set_flags);
    if (mark_res) {
        int byte_count = ((max_flag_count + 15) / 16) * 2;

        switch (mode) {
            case mTG_MARK_CHK:
                chk_res = mTG_bit_chk(current_flags_p->u8array, set_flags.u8array, byte_count);
                break;
            case mTG_MARK_ON:
                mTG_bit_on(current_flags_p->u8array, set_flags.u8array, byte_count);
                break;
            case mTG_MARK_OFF:
                mTG_bit_off(current_flags_p->u8array, set_flags.u8array, byte_count);
                break;
            case mTG_MARK_RVS:
                mTG_bit_rvs(current_flags_p->u8array, set_flags.u8array, byte_count);
                break;
            case mTG_MARK_CLR:
                mTG_bit_clr(current_flags_p->u8array, set_flags.u8array, byte_count);
                break;
            case mTG_MARK_CHK_ALL0:
                chk_res = mTG_bit_chk_all0(current_flags_p->u8array, set_flags.u8array, byte_count);
                break;
        }

        if (mode != mTG_MARK_CHK) {
            mTG_mark_mainX(submenu, menu_info, table, table_idx, mTG_MARK_CHK, &chk_res);
        }
    }

    if (chk_result != NULL) {
        *chk_result = chk_res;
    }

    return mark_res;
}

static void mTG_mark_main_CLR(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    switch (menu_info->menu_type) {
        case mSM_OVL_INVENTORY:
            mTG_mark_mainX(submenu, menu_info, mTG_TABLE_ITEM, 0, mTG_MARK_CLR, NULL);
            mTG_mark_mainX(submenu, menu_info, mTG_TABLE_MAIL, 0, mTG_MARK_CLR, NULL);
            break;
        case mSM_OVL_MAILBOX:
            mTG_mark_mainX(submenu, menu_info, mTG_TABLE_MAIL, 0, mTG_MARK_CLR, NULL);
            mTG_mark_mainX(submenu, menu_info, mTG_TABLE_MBOX, 0, mTG_MARK_CLR, NULL);
            break;
        case mSM_OVL_CPMAIL:
            mTG_mark_mainX(submenu, menu_info, mTG_TABLE_MAIL, 0, mTG_MARK_CLR, NULL);
            mTG_mark_mainX(submenu, menu_info, mTG_TABLE_CPMAIL, 0, mTG_MARK_CLR, NULL);
            break;
        case mSM_OVL_CPORIGINAL:
            mTG_mark_mainX(submenu, menu_info, mTG_TABLE_CPORIGINAL_NW, 0, mTG_MARK_CLR, NULL);
            mTG_mark_mainX(submenu, menu_info, mTG_TABLE_CPORIGINAL, 0, mTG_MARK_CLR, NULL);
            break;
    }
}

static int mTG_mark_main(Submenu* submenu, mSM_MenuInfo_c* menu_info, int mode, int* chk_result) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);

    return mTG_mark_mainX(submenu, menu_info, tag->table, idx, mode, chk_result);
}

static void mTG_write_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    int mail_idx = mMl_chk_mail_free_space(Now_Private->mail, mPr_INVENTORY_MAIL_COUNT);

    if (mail_idx >= 0) {
        mTG_open_board_init(submenu, menu_info, mail_idx, mSM_BD_OPEN_WRITE, idx);
    } else {
        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_WRITE);
    }
}

static void mTG_priceset_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    mTG_tag_c* sel_tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];

    mTG_chg_tag_func2(submenu, menu_info, sel_tag, mTG_TYPE_HANIWA_PRICE);
    submenu->overlay->haniwa_ovl->price = Save_Get(homes[menu_info->data1]).haniwa.items[tag->tag_col].extra_data;
    sAdo_SysTrgStart(NA_SE_33);
}

static void mTG_present_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    Mail_c* mail = &Now_Private->mail[idx];
    int present_myself = mMl_check_set_present_myself(mail);

    if (present_myself == FALSE && mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO) == -1) {
        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PR_LEAVE);
    } else {
        mTG_catch_item_from_table(submenu, NULL, &mail->present,
                                  present_myself ? mPr_ITEM_COND_NORMAL : mPr_ITEM_COND_PRESENT, mTG_TABLE_MAIL, idx);
    }
}

static void mTG_show_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_set_trade_cond(submenu, menu_info, mHm_HANIWA_TRADE_1, 0);
}

static void mTG_cancel_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    if (menu_info->menu_type == mSM_OVL_INVENTORY) {
        mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

        if (menu_info->data0 == mSM_IV_OPEN_QUEST) {
            mTG_close_window(submenu, menu_info, TRUE);
        } else {
            if (inv_ovl != NULL) {
                inv_ovl->mail_mark_flag = 0;
            }

            mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_FIELD_DEFAULT);
            sAdo_SysTrgStart(MONO(NA_SE_3));
        }
    } else {
        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_TYPE_FIELD_DEFAULT);
        sAdo_SysTrgStart(MONO(NA_SE_3));
    }
}
