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

static mTG_Ovl_c tag_ovl_data;

typedef struct tag_word_s {
    u8 str[mTG_TAG_STR_LEN];
    mSM_MOVE_PROC move_proc;
} mTG_tag_word_c;

typedef struct tag_data_s {
    mTG_tag_word_c* words; /* array of words for each line */
    int lines;             /* # of lines */
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
static s16 mTG_gba_nw_col_pos[] = { 48, 80 };

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
static s16 mTG_mail_line_pos[] = { 38, 14, -10, -34, -58 };
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
static s16 mTG_gba_nw_line_pos[] = { 40, 11, -18, -47 };

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
    if (submenu->overlay->needlework_ovl != NULL) {
        int nw_type = submenu->overlay->menu_info[mSM_OVL_NEEDLEWORK].data0;

        if (nw_type == 0) {
            return 21.0f;
        } else if (nw_type == 1 && table == mTG_TABLE_NEEDLEWORK) {
            return 46.0f;
        }
    } else if (submenu->overlay->inventory_ovl != NULL) {
        if (submenu->overlay->menu_info[mSM_OVL_INVENTORY].data0 == mSM_IV_OPEN_MAILBOX) {
            return -155.0f;
        }
    }

    return 0.0f;
}

static void mTG_set_hand_pos(Submenu* submenu, f32* pos, int table, int idx) {
    mTG_tag_data_table_c* data_p = &mTG_table_data[table];
    f32 ofs = mTG_set_hand_pos_offset(submenu, table);
    int col = idx % data_p->col_num;
    int row = idx / data_p->col_num;

    pos[0] = data_p->col_pos[col] + ofs;
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

static void mTG_return_tag_init(Submenu* submenu, int ret_type, int type) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    int ret_idx = mTG_get_tag_idx(submenu, ret_type);

    if (ret_idx >= 0) {
        if (ret_idx == 0) {
            tag_ovl->ret_tag_idx = -1;
        } else {
            tag_ovl->ret_tag_idx = ret_idx;
        }

        if (type == mTG_TYPE_NONE) {
            mTG_tag_c* tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];
            int i;

            for (i = tag_ovl->sel_tag_idx - tag_ovl->ret_tag_idx; i != 0; i--) {
                tag->base_pos[0] += tag->body_ofs[0];
                tag->base_pos[1] += tag->body_ofs[1];
                tag->body_ofs[0] = 0.0f;
                tag->body_ofs[1] = 0.0f;
                tag--;
            }
        }
    }
}

static u16 mTG_get_item_name_wait_time(mTG_tag_c* tag) {
    u16 time = 20;

    tag->scale = 0.0f;
    if (tag->table == mTG_TABLE_CATALOG_WC) {
        time = 16;
    }

    return time;
}

static void mTG_return_tag_func(Submenu* submenu, mTG_Ovl_c* tag_ovl, mTG_tag_c* tag) {
    int count = 0;
    int tag_num = tag_ovl->sel_tag_idx - tag_ovl->ret_tag_idx;
    int i;

    for (i = tag_num; i >= 0; i--) {
        tag->scale -= 0.125f;
        if (tag->scale <= 0.0f) {
            if (tag->type == mTG_TYPE_NONE) {
                tag_ovl->item_name_wait_time = mTG_get_item_name_wait_time(tag);
            }

            tag->scale = 0.0f;
            count++;
        }

        tag--;
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
            arrow_data->ofs[i] + arrow_data->scale[i] * tag->_04[i] + win_data->_08[i] * tag->body_scale[i];
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

    if (tag->base_pos[0] + tag->body_ofs[0] + tag->body_scale[0] * edge >= 146.0f) {
        res = TRUE;
    }

    return res;
}

static void mTG_calc_right_edge_select(mTG_tag_c* tag, f32* right_edge) {
    f32 margin = tag->body_scale[0] * 122.5f;

    *right_edge = margin * 0.5 + tag->base_pos[0] + tag->body_ofs[0];
}

static int mTG_check_edge_right_select(mTG_tag_c* tag, f32* right_edge) {
    f32 margin = tag->body_scale[0] * 122.5f;

    *right_edge = (margin * 0.5 + tag->base_pos[0] + tag->body_ofs[0]) - 134.0f;

    if (*right_edge <= 0.0f) {
        return TRUE;
    }

    return FALSE;
}

static int mTG_check_edge_foot_select(mTG_tag_c* tag) {
    int res = FALSE;

    tag->flags &= ~mTG_TAG_FLAG_EDGE_FOOT_SELECT;
    if ((tag->base_pos[1] + tag->body_ofs[1]) - (tag->body_scale[1] * 129.5f) * 0.5f - 3.0f >= -120.0f) {
        tag->flags |= mTG_TAG_FLAG_EDGE_FOOT_SELECT;
        res = TRUE;
    }

    return res;
}

static int mTG_get_max_col_width_data(mTG_tag_word_c* tag_word, int lines) {
    int max_col_width = 0;
    int i;

    if (tag_word != NULL) {
        for (i = 0; i < lines; i++) {
            int len = mMl_strlen(tag_word[i].str, mTG_TAG_STR_LEN, CHAR_SPACE);
            int width = mFont_GetStringWidth(tag_word[i].str, len, TRUE);

            if (max_col_width < width) {
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

            if (*max_width < width) {
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

    if (str0_max < (str0_len + str1_len)) {
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

        if (str_max < (col_len + src_len)) {
            src_len -= (col_len + src_len) - str_max;
        }

        str += col_len;
        str[-4] = color->r;
        str[-3] = color->g;
        str[-2] = color->b;
        str[-1] = (u8)src_len;
        memcpy(str, src, src_len);
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
    u8* src;

    src = mNpc_GetNpcWorldNameP(SP_NPC_SANTA);
    mTG_strcpy(str_infos[1].str, src, mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_PURPLE;
    tag->str2_type = 5;

    return mTG_MAIL_TYPE_FROM;
}

static int mTG_init_tag_data_item_win_sub_mail_item_tanukiti(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    u8* src;

    src = mNpc_GetNpcWorldNameP(SP_NPC_SHOP_MASTER);
    mTG_strcpy(str_infos[1].str, src, mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_INDIGO;
    tag->str2_type = 6;

    return mTG_MAIL_TYPE_FROM;
}

static int mTG_init_tag_data_item_win_sub_mail_item_tunekiti(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    u8* src;

    src = mNpc_GetNpcWorldNameP(SP_NPC_BROKER);
    mTG_strcpy(str_infos[1].str, src, mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
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
    u8* src;

    src = mNpc_GetNpcWorldNameP(SP_NPC_EV_MIKO);
    mTG_strcpy(str_infos[1].str, src, mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
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
    u8* src;

    src = mNpc_GetNpcWorldNameP(ETC_SNOWMAN_BALL_A);
    mTG_strcpy(str_infos[1].str, src, mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_PURPLE;
    tag->str2_type = 5;

    return mTG_MAIL_TYPE_FROM;
}

static int mTG_init_tag_data_item_win_sub_mail_item_angler(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    u8* src;

    src = mNpc_GetNpcWorldNameP(SP_NPC_ANGLER);
    mTG_strcpy(str_infos[1].str, src, mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
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

        if (width < str1_width) {
            width = str1_width;
        }

        if (width < str2_width) {
            width = str2_width;
        }

        mTG_set_tag_win_scale_p(tag, win_type, width * scale, 0.0f);
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
        case mTG_TABLE_COLLECT:
            mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

            *itemNo = inv_ovl->set_collect_itemNo_proc(idx, inv_ovl->page_order[0]);
            break;
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
        int top = mCO_top_folder(submenu);
        int hide = mCO_check_hide_flg(submenu, top, idx);

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

    f32 max_width;
    f32 max_height;
    f32 dist_right;
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
    tag->body_ofs[1] = min_ofs_p[1] + ofs_dis_p[1] * tag->_04[1] + (tag->body_scale[1] * 61.25f - 6.0f) * dir_y;
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

    mTG_add_item_data_c* data_p;
    f32 max_width;
    f32 max_height;
    f32 scale_x;
    f32 scale_y;
    int left_flag;

    mTG_get_col_width_and_line_select(tag, tag_data, &max_width, &max_height);
    mTG_set_tag_win_scale_p(tag, mTG_WIN_TYPE_SELECT2, max_width * 0.875f, max_height * 0.875f);

    if (item_tag->body_ofs[0] < 0.0f) {
        left_flag = TRUE;
    } else {
        left_flag = FALSE;
    }

    if (item_tag->str2_type != 0) {
        scale_y = 68.0f;
        scale_x = 184.0f;
        data_p = &tag_add_item_data[1];
    } else {
        scale_y = 28.0f;
        scale_x = 129.5f;
        data_p = &tag_add_item_data[0];
    }

    tag->base_pos[1] += data_p->down_min[0][1] + (item_tag->body_ofs[1] - item_tag->body_scale[1] * scale_y * 0.5f) +
                        item_tag->_04[1] * data_p->down_min[1][1];
    tag->body_ofs[1] = (data_p->up_min[0][1] + tag->_04[1] * data_p->up_min[1][1]) - tag->body_scale[1] * 129.0f * 0.5f;

    tag->base_pos[0] += item_tag->body_ofs[0] - item_tag->body_scale[0] * scale_x * 0.5f;
    tag->body_ofs[0] = tag->body_scale[0] * 122.5f * 0.5f;

    // TODO
}
