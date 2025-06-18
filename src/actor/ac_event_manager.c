#include "ac_event_manager.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_handbill.h"
#include "m_font.h"
#include "m_string.h"
#include "m_msg.h"
#include "m_malloc.h"
#include "m_debug.h"
#include "m_debug_display.h"
#include "m_snowman.h"
#include "m_event_map_npc.h"
#include "ac_groundhog_control.h"
#include "m_bgm.h"
#include "m_random_field.h"
#include "zurumode.h"
#include "_mem.h"

// this is cursed
#define aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN (mEv_place_data_c*)-1

static int title_fade(EVENT_MANAGER_ACTOR* evmgr, int type, int state, u32 area);
static void schedule_init(ACTOR* actorx);
static void schedule_main(ACTOR* actorx);

static mEv_place_data_c* wpppp;
static mEv_place_data_c* spppp;
static mEv_place_data_c* dpppp;
static mEv_place_data_c* tpppp;

static int get_forward_block(int* bx, int* bz) {
    if (Common_Get(player_actor_exists) == FALSE) {
        return FALSE;
    }

    if (mFI_GetNextBlockNum(bx, bz) == FALSE) {
        ACTOR* playerx = GET_PLAYER_ACTOR_NOW_ACTOR();

        if (playerx == NULL) {
            return FALSE;
        }

        if (mFI_Wpos2BlockNum(bx, bz, playerx->world.position) == FALSE) {
            return FALSE;
        }
    }

    return TRUE;
}

static void aEvMgr_actor_renewal_player_pos(GAME* game, EVENT_MANAGER_ACTOR* evmgr) {
    aEvMgr_player_pos_c* player_pos = &evmgr->player_pos;
    int bx;
    int bz;

    player_pos->last_bx = player_pos->bx;
    player_pos->last_bz = player_pos->bz;
    if (get_forward_block(&bx, &bz) == TRUE) {
        player_pos->bx = bx;
        player_pos->bz = bz;
    }
}

static void aEvMgr_actor_regist_handbill(int handbill_idx, u8 paper_type, u8 mail_type) {
    static Mail_c mail;
    Mail_ct_c* content = &mail.content;
    int header_back_start;

    mMl_clear_mail(&mail);
    mHandbill_Load_HandbillFromRom(content->header, &header_back_start, content->footer, content->body, handbill_idx);
    mail.content.font = mMl_FONT_RECV;
    mail.content.paper_type = paper_type;
    mail.content.header_back_start = header_back_start;
    mail.content.mail_type = mail_type;
    mPO_receipt_proc(&mail, mPO_SENDTYPE_EVENT_LEAFLET);
}

static void aEvMgr_actor_set_shop_handbill_str(mEv_special_c* sp_ev, int sale_item_count) {
    mEv_bargin_c* bargin_p = &sp_ev->event.bargin;
    mActor_name_t* item_p = bargin_p->items;
    lbRTC_time_c* start_p = &bargin_p->start_time;
    u8 item_cnt_str[1] = { 0 };
    u8 month_str[9];
    u8 day_str[4];
    u8 hour_str[15];
    u8 item_name_str[mIN_ITEM_NAME_LEN];
    int len;
    int i;

    mFont_UnintToString(item_cnt_str, 1, sale_item_count, 1, TRUE, FALSE, TRUE);
    mHandbill_Set_free_str(mHandbill_FREE_STR0, item_cnt_str, sizeof(item_cnt_str));
    
    for (i = 0; i < sale_item_count; i++) {
        mIN_copy_name_str(item_name_str, item_p[i]);
        mHandbill_Set_free_str(mHandbill_FREE_STR7 + i, item_name_str, mIN_ITEM_NAME_LEN);
    }

    mem_clear(month_str, sizeof(month_str), CHAR_SPACE);
    mString_Load_StringFromRom(month_str, sizeof(month_str), mString_MONTH_START + (start_p->month - 1));
    mHandbill_Set_free_str(mHandbill_FREE_STR17, month_str, sizeof(month_str));

    mem_clear(day_str, sizeof(day_str), CHAR_SPACE);
    mString_Load_StringFromRom(day_str, sizeof(day_str), mString_DAY_START + (start_p->day - 1));
    mHandbill_Set_free_str(mHandbill_FREE_STR18, day_str, sizeof(day_str));

    len = mString_Load_HourStringFromRom(hour_str, start_p->hour);
    mHandbill_Set_free_str(mHandbill_FREE_STR19, hour_str, len);
}

static void aEvMgr_actor_set_broker_handbill_str(mEv_special_c* sp_ev) {
    lbRTC_time_c* start_p = &sp_ev->scheduled;
    u8 month_str[9];
    u8 day_str[4];
    u8 hour_str[15];
    int len;

    mem_clear(month_str, sizeof(month_str), CHAR_SPACE);
    mString_Load_StringFromRom(month_str, sizeof(month_str), mString_MONTH_START + (start_p->month - 1));
    mHandbill_Set_free_str(mHandbill_FREE_STR0, month_str, sizeof(month_str));

    mem_clear(day_str, sizeof(day_str), CHAR_SPACE);
    mString_Load_StringFromRom(day_str, sizeof(day_str), mString_DAY_START + (start_p->day - 1));
    mHandbill_Set_free_str(mHandbill_FREE_STR1, day_str, sizeof(day_str));

    len = mString_Load_HourStringFromRom(hour_str, start_p->hour);
    mHandbill_Set_free_str(mHandbill_FREE_STR2, hour_str, len);
}

static void aEvMgr_actor_regist_broker_handbill(mEv_special_c* sp_ev) {
    static int broker_handbill_no[] = { 0x031, 0x032, 0x033 };
    int handbill_no = RANDOM(ARRAY_COUNT(broker_handbill_no));

    aEvMgr_actor_set_broker_handbill_str(sp_ev);
    aEvMgr_actor_regist_handbill(broker_handbill_no[handbill_no], (ITM_PAPER54 - ITM_PAPER_START), mMl_TYPE_BROKER_SALE_LEAFLET);
}

static void aEvMgr_actor_init_field_info(aEvMgr_field_info_c* field_info) {
    int reserved_max;
    u8 free_num;

    field_info->block_max.x = mFI_GetBlockXMax();
    field_info->block_max.z = mFI_GetBlockZMax();
    reserved_max = field_info->block_max.x * field_info->block_max.z;
    field_info->reserve_buf = (Anmhome_c*)zelda_malloc(reserved_max * sizeof(Anmhome_c));
    free_num = 0;
    mNpc_MakeReservedListAfterFieldct(field_info->reserve_buf, reserved_max, &free_num, field_info->block_max.x, field_info->block_max.z);
    field_info->reserve_num = free_num;
    field_info->block_max.z -= 2;
}

static void aEvMgr_move(ACTOR* actorx, GAME* game) {
    EVENT_MANAGER_ACTOR* evmgr = (EVENT_MANAGER_ACTOR*)actorx;
    
    aEvMgr_actor_renewal_player_pos(game, evmgr);
    mEv_RenewalDataEveryDay();
    schedule_main(actorx);
}

static void aEvMgr_draw(ACTOR* actorx, GAME* game) {
    // nothing
}

static void aEvMgr_actor_player_pos_init(EVENT_MANAGER_ACTOR* evmgr) {
    evmgr->player_pos.bx = 0;
    evmgr->player_pos.bz = 0;
    evmgr->player_pos.last_bx = 0;
    evmgr->player_pos.last_bz = 0;
}

static void aEvMgr_ct(ACTOR* actorx, GAME* game) {
    EVENT_MANAGER_ACTOR* evmgr = (EVENT_MANAGER_ACTOR*)actorx;

    wpppp = NULL;
    spppp = NULL;
    dpppp = NULL;
    tpppp = NULL;
    aEvMgr_actor_player_pos_init(evmgr);
    aEvMgr_actor_init_field_info(&evmgr->field_info);
    schedule_init(actorx);
    CLIP(event_manager_clip) = &evmgr->clip;
    CLIP(event_manager_clip)->event_manager_actor = evmgr;
    CLIP(event_manager_clip)->title_fade_proc = &title_fade;
}

static void aEvMgr_dt(ACTOR* actorx, GAME* game) {
    CLIP(event_manager_clip) = NULL;
}

static void aEvMgr_save(ACTOR* actorx, GAME* game) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    mEv_schedule_date_u date;

    if (mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELDTYPE2_FG) {
        mEv_erase_FG_all_in_common_place();
    }

    date.d.month = rtc_time->month;
    date.d.day = rtc_time->day;
    Save_Get(event_save_common).dates[mEv_SAVE_DATE_LAST_PLAY_DATE] = date.md;
}

static void w_guide_arrow(void) {
    ACTOR* playerx = GET_PLAYER_ACTOR_NOW_ACTOR();
    int bx;
    int bz;

    if (mFI_Wpos2BlockNum(&bx, &bz, playerx->world.position) && wpppp != NULL) {
        xyz_t arrow_pos = playerx->world.position;
        xyz_t center_pos;
        s_xyz angle;

        arrow_pos.y += 65.0f;
        mFI_BkandUtNum2CenterWpos(&center_pos, wpppp->block.x, wpppp->block.z, wpppp->unit.x, wpppp->unit.z);
        angle = sanglexy_by_2pos(&arrow_pos, &center_pos);
        if (bx != wpppp->block.x || bz != wpppp->block.z) {
            Debug_Display_new(arrow_pos.x, arrow_pos.y, arrow_pos.z, 0, angle.y, 0, 0.4f, 0.4f, 0.5f, 190, 250, 120, 128, Debug_Display_SHAPE_ARROW_MODEL, gamePT->graph);
        } else {
            Debug_Display_new(arrow_pos.x, arrow_pos.y, arrow_pos.z, 0, angle.y, 0, 0.4f, 0.4f, 0.8f, 190, 250, 120, 128, Debug_Display_SHAPE_ARROW_MODEL, gamePT->graph);
        }
    }
}

static void sp_guide_arrow(void) {
    ACTOR* playerx = GET_PLAYER_ACTOR_NOW_ACTOR();
    int bx;
    int bz;

    if (mFI_Wpos2BlockNum(&bx, &bz, playerx->world.position) && spppp != NULL) {
        xyz_t arrow_pos = playerx->world.position;
        xyz_t center_pos;
        s_xyz angle;

        arrow_pos.y += 60.0f;
        mFI_BkandUtNum2CenterWpos(&center_pos, spppp->block.x, spppp->block.z, spppp->unit.x, spppp->unit.z);
        angle = sanglexy_by_2pos(&arrow_pos, &center_pos);
        if (bx != spppp->block.x || bz != spppp->block.z) {
            Debug_Display_new(arrow_pos.x, arrow_pos.y, arrow_pos.z, 0, angle.y, 0, 0.4f, 0.4f, 0.5f, 120, 120, 240, 128, Debug_Display_SHAPE_ARROW_MODEL, gamePT->graph);
        } else {
            Debug_Display_new(arrow_pos.x, arrow_pos.y, arrow_pos.z, 0, angle.y, 0, 0.4f, 0.4f, 0.8f, 120, 120, 240, 128, Debug_Display_SHAPE_ARROW_MODEL, gamePT->graph);
        }
    }
}

static void day_guide_arrow(void) {
    ACTOR* playerx = GET_PLAYER_ACTOR_NOW_ACTOR();
    int bx;
    int bz;

    if (mFI_Wpos2BlockNum(&bx, &bz, playerx->world.position) && dpppp != NULL) {
        xyz_t arrow_pos = playerx->world.position;
        xyz_t center_pos;
        s_xyz angle;

        arrow_pos.y += 60.0f;
        mFI_BkandUtNum2CenterWpos(&center_pos, dpppp->block.x, dpppp->block.z, dpppp->unit.x, dpppp->unit.z);
        angle = sanglexy_by_2pos(&arrow_pos, &center_pos);
        if (bx != dpppp->block.x || bz != dpppp->block.z) {
            Debug_Display_new(arrow_pos.x, arrow_pos.y, arrow_pos.z, 0, angle.y, 0, 0.4f, 0.4f, 0.5f, 250, 120, 120, 128, Debug_Display_SHAPE_ARROW_MODEL, gamePT->graph);
        } else {
            Debug_Display_new(arrow_pos.x, arrow_pos.y, arrow_pos.z, 0, angle.y, 0, 0.4f, 0.4f, 0.8f, 250, 120, 120, 128, Debug_Display_SHAPE_ARROW_MODEL, gamePT->graph);
        }
    }
}

static void turkey_guide_arrow(void) {
    ACTOR* playerx = GET_PLAYER_ACTOR_NOW_ACTOR();
    int bx;
    int bz;

    if (mFI_Wpos2BlockNum(&bx, &bz, playerx->world.position) && tpppp != NULL) {
        xyz_t arrow_pos = playerx->world.position;
        xyz_t center_pos;
        s_xyz angle;

        arrow_pos.y += 60.0f;
        mFI_BkandUtNum2CenterWpos(&center_pos, tpppp->block.x, tpppp->block.z, tpppp->unit.x, tpppp->unit.z);
        angle = sanglexy_by_2pos(&arrow_pos, &center_pos);
        if (bx != tpppp->block.x || bz != tpppp->block.z) {
            Debug_Display_new(arrow_pos.x, arrow_pos.y, arrow_pos.z, 0, angle.y, 0, 0.4f, 0.4f, 0.5f, 250, 100, 255, 128, Debug_Display_SHAPE_ARROW_MODEL, gamePT->graph);
        } else {
            Debug_Display_new(arrow_pos.x, arrow_pos.y, arrow_pos.z, 0, angle.y, 0, 0.4f, 0.4f, 0.8f, 250, 100, 255, 128, Debug_Display_SHAPE_ARROW_MODEL, gamePT->graph);
        }
    }
}

typedef struct event_control_s aEvMgr_event_ctrl_c;

typedef int (*aEvMgr_EVENT_START_PROC)(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* event_ctrl);
typedef int (*aEvMgr_EVENT_STOP_PROC)(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* event_ctrl);
typedef int (*aEvMgr_EVENT_IN_PROC)(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* event_ctrl);
typedef int (*aEvMgr_EVENT_OUT_PROC)(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* event_ctrl);
typedef int (*aEvMgr_EVENT_BEHIND_PROC)(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* event_ctrl);

struct event_control_s {
    int type;
    aEvMgr_EVENT_START_PROC start_proc;
    aEvMgr_EVENT_STOP_PROC stop_proc;
    aEvMgr_EVENT_IN_PROC in_proc;
    aEvMgr_EVENT_OUT_PROC out_proc;
    aEvMgr_EVENT_BEHIND_PROC behind_proc;
    BlockOrUnit_c block;
};

static int fluc = 0;

static int init_sp_bargain(void) {
    int cat_table[4] = { mSP_KIND_FURNITURE, mSP_KIND_CARPET, mSP_KIND_WALLPAPER, mSP_KIND_CLOTH };
    int handbill_table[mSP_SHOP_TYPE_NUM][4] = {
        { 0x002, 0x003, 0x004, 0x005 },
        { 0x006, 0x007, 0x008, 0x009 },
        { 0x00A, 0x00B, 0x00C, 0x00D },
        { 0x00E, 0x00F, 0x010, 0x011 },
    };
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    mEv_special_c* ev_save = &Save_Get(event_save_data).special;
    mEv_bargin_c* bargin_p = &ev_save->event.bargin;
    mEv_schedule_date_u today;
    mEv_schedule_date_u start_day;
    mEv_schedule_date_u end_day;
    int shop_level = mSP_GetShopLevel();
    int item_count;
    int item_count_table[mSP_SHOP_TYPE_NUM] = { 1, 2, 3, 5 };
    int cat;
    int cat_idx;
    int i;
    mActor_name_t spotlight;

    today.d.month = rtc_time->month;
    today.d.day = rtc_time->day;
    
    start_day.md = Save_Get(event_save_common).dates[mEv_SAVE_DATE_SPECIAL1];

    bargin_p->start_time.year = rtc_time->year;
    if (today.md > start_day.md) {
        bargin_p->start_time.year = rtc_time->year + 1;
    }
    bargin_p->start_time.month = start_day.d.month;
    bargin_p->start_time.day = start_day.d.day;
    bargin_p->start_time.hour = Save_Get(event_save_common).dates[mEv_SAVE_DATE_SPECIAL3];
    bargin_p->start_time.sec = 0;
    bargin_p->start_time.min = 0;

    ev_save->scheduled.hour = Save_Get(event_save_common).dates[mEv_SAVE_DATE_SPECIAL3];

    end_day.md = Save_Get(event_save_common).dates[mEv_SAVE_DATE_SPECIAL2];
    bargin_p->end_time.year = rtc_time->year;
    if (today.md > end_day.md) {
        bargin_p->end_time.year = rtc_time->year + 1;
    }

    bargin_p->end_time.month = end_day.d.month;
    bargin_p->end_time.day = end_day.d.day;
    bargin_p->end_time.hour = bargin_p->start_time.hour + 1;
    bargin_p->end_time.min = 0;
    bargin_p->end_time.sec = 0;

    cat_idx = start_day.md % 4;
    cat = cat_table[cat_idx];
    
    item_count = 1 + ((int)rtc_time->sec % 3);
    if (item_count > item_count_table[shop_level]) {
        item_count = item_count_table[shop_level];
    }
    
    for (i = 0; i < ARRAY_COUNT(bargin_p->items); i++) {
        bargin_p->items[i] = EMPTY_NO;
    }

    // Try selecting an uncollected item from ABC list going from rare -> uncommon -> common
    mSP_SelectRandomItem_New(NULL, &spotlight, 1, NULL, 0, cat, mSP_LISTTYPE_RARE, TRUE);
    if (spotlight == EMPTY_NO) {
        mSP_SelectRandomItem_New(NULL, &spotlight, 1, NULL, 0, cat, mSP_LISTTYPE_UNCOMMON, TRUE);
    }
    if (spotlight == EMPTY_NO) {
        mSP_SelectRandomItem_New(NULL, &spotlight, 1, NULL, 0, cat, mSP_LISTTYPE_COMMON, TRUE);
    }

    if (spotlight == EMPTY_NO) {
        // No uncollected items in ABC list, so pick a random one from the rare list
        mSP_SelectRandomItem_New(NULL, bargin_p->items, item_count, NULL, 0, cat, mSP_LISTTYPE_RARE, FALSE);
    } else {
        // Found an uncollected item in the ABC list, so use that as the spotlight item
        bargin_p->items[0] = spotlight;

        if (item_count > 1) {
            // The rest will be random items from the rare list
            mSP_SelectRandomItem_New(NULL, &bargin_p->items[1], item_count - 1, &spotlight, 1, cat, mSP_LISTTYPE_RARE, FALSE);
        }
    }

    bargin_p->kind = cat;
    aEvMgr_actor_set_shop_handbill_str(ev_save, item_count);
    aEvMgr_actor_regist_handbill(handbill_table[shop_level][cat_idx], (ITM_PAPER55 - ITM_PAPER_START), mMl_TYPE_SHOP_SALE_LEAFLET);
    return TRUE;
}

static int init_sp_broker(void) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    mEv_special_c* ev_save = &Save_Get(event_save_data).special;
    mEv_broker_c* broker_p = &ev_save->event.broker;
    mEv_schedule_date_u today;
    mEv_schedule_date_u end_day;
    int goods_power;
    int common_chance;
    int rare_chance;
    int uncommon_chance;
    int threshold;
    f32 event_chance;
    int i;
    int list;

    today.d.month = rtc_time->month;
    today.d.day = rtc_time->day;
    end_day.md = Save_Get(event_save_common).dates[mEv_SAVE_DATE_SPECIAL2];

    broker_p->end_time.year = rtc_time->year;
    if (today.md > end_day.md) {
        broker_p->end_time.year = rtc_time->year + 1;
    }


    broker_p->end_time.month = end_day.d.month;
    broker_p->end_time.day = end_day.d.day;
    broker_p->end_time.hour = 18;
    broker_p->end_time.min = broker_p->end_time.sec = 0;

    for (i = 0; i < ARRAY_COUNT(broker_p->pid); i++) {
        mPr_ClearPersonalID(&broker_p->pid[i]);
    }

    for (i = 0; i < ARRAY_COUNT(broker_p->items); i++) {
        broker_p->items[i] = EMPTY_NO;
    }

    goods_power = mPr_GetGoodsPower();
    common_chance = 50 + goods_power;
    if (goods_power < 0) {
        uncommon_chance = goods_power + 35;
        rare_chance = 5;
        threshold = 100 - (uncommon_chance + 5);
    } else {
        rare_chance = goods_power + 5;
        uncommon_chance = 35;
        threshold = 100 - (rare_chance + 35);
    }

    if (rare_chance >= uncommon_chance && rare_chance >= threshold) {
        list = mSP_LISTTYPE_RARE;
    } else if (uncommon_chance >= rare_chance && uncommon_chance >= threshold) {
        list = mSP_LISTTYPE_UNCOMMON;
    } else {
        list = mSP_LISTTYPE_COMMON;
    }

    if (common_chance < 50) {
        common_chance = 50;
    } else if (common_chance > 70) {
        common_chance = 70;
    }

    event_chance = (f32)common_chance;
    mSP_SelectRandomItem_New(NULL, &broker_p->items[0], 1, NULL, 0, mSP_KIND_FURNITURE, RANDOM_F(100.0f) <= event_chance ? mSP_LISTTYPE_EVENT : list, FALSE);
    mSP_SelectRandomItem_New(NULL, &broker_p->items[1], 1, broker_p->items, 1, mSP_KIND_FURNITURE, RANDOM_F(100.0f) <= event_chance ? mSP_LISTTYPE_EVENT : list, FALSE);
    mSP_SelectRandomItem_New(NULL, &broker_p->items[2], 1, broker_p->items, 2, mSP_KIND_FURNITURE, RANDOM_F(100.0f) <= event_chance ? mSP_LISTTYPE_EVENT : list, FALSE);

    aEvMgr_actor_regist_broker_handbill(ev_save);
    return TRUE;
}

static int init_sp_artist(void) {
    mEv_special_c* ev_save = &Save_Get(event_save_data).special;
    mEv_artist_c* artist_p = &ev_save->event.artist;
    int i;

    for (i = 0; i < ARRAY_COUNT(artist_p->pids); i++) {
        mPr_ClearPersonalID(&artist_p->pids[i]);
        artist_p->walls[i] = EMPTY_NO;
    }

    return TRUE;
}

static int init_sp_arabian(void) {
    mEv_special_c* ev_save = &Save_Get(event_save_data).special;
    mEv_arabian_c* arabian_p = &ev_save->event.arabian;

    arabian_p->used = 0;
    arabian_p->carpet = EMPTY_NO;
    return TRUE;
}

static int init_sp_gypsy(void) {
    mEv_special_c* ev_save = &Save_Get(event_save_data).special;
    mEv_gypsy_c* gypsy_p = &ev_save->event.gypsy;

    gypsy_p->_00 = 0;
    return TRUE;
}

static int init_sp_designer(void) {
    return TRUE;
}

static u32 special_type2kind(int type) {
    u32 ret;

    switch (type) {
        case mEv_EVENT_BROKER_SALE:
        case mEv_EVENT_HANDBILL_BROKER:
            ret = mEv_SPNPC_BROKER;
            break;
        case mEv_EVENT_DESIGNER:
            ret = mEv_SPNPC_DESIGNER;
            break;
        case mEv_EVENT_ARTIST:
            ret = mEv_SPNPC_ARTIST;
            break;
        case mEv_EVENT_CARPET_PEDDLER:
            ret = mEv_SPNPC_ARABIAN;
            break;
        case mEv_EVENT_GYPSY:
            ret = mEv_SPNPC_GYPSY;
            break;
        case mEv_EVENT_SHOP_SALE:
        case mEv_EVENT_HANDBILL_SHOP_SALE:
        default:
            ret = mEv_SPNPC_SHOP;
            break;
    }

    return ret;
}

typedef int (*aEvMgr_INIT_SP_PROC)(void);

static int set_special_event_save(void) {
    mEv_special_c* ev_save = &Save_Get(event_save_data).special;
    int type;
    mEv_schedule_date_u day;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    // @BUG - should be static
    u8 hours[] = {
        0,
        6,
        18,
        6,
        6,
        21,
        0,
        0,
    };
    // @BUG - should be static
    aEvMgr_INIT_SP_PROC init_sp_proc[] = {
        init_sp_bargain,
        init_sp_designer,
        init_sp_broker,
        init_sp_artist,
        init_sp_arabian,
        init_sp_gypsy,
    };

    day.md = Save_Get(event_save_common).dates[mEv_SAVE_DATE_SPECIAL1];
    ev_save->kind = special_type2kind(Save_Get(event_save_common).special_event.type);

    ev_save->scheduled.year = rtc_time->month <= day.d.month ? rtc_time->year : rtc_time->year + 1;
    ev_save->scheduled.month = day.d.month;
    ev_save->scheduled.day = day.d.day;
    ev_save->scheduled.hour = hours[ev_save->kind];
    ev_save->scheduled.min = 0;
    ev_save->scheduled.sec = 0;

    (*init_sp_proc[mEv_SET_SUBTYPE(ev_save->kind)])();

    return TRUE;
}

// clang-format off
static BlockOrUnit_c neighbor_adjust[] = {
    {0, 1},
    {0, -1},
    {-1, 0},
    {1, 0},
    {-1, 1},
    {1, 1},
    {-1, -1},
    {-1, 1},
    {0, 2},
    {2, -2},
    {-2, 2},
    {2, 0},
    {-1, 2},
    {2, 1},
    {-2, -1},
    {-1, -2},
};
// clang-format on

static int neighbor_check(int* ux, int* uz, int bx, int bz) {
    int n_ux;
    int n_uz;
    int i;

    i = fluc & 0xF;
    n_ux = *ux + neighbor_adjust[i].x;
    n_uz = *uz + neighbor_adjust[i].z;
    
    if (n_ux > 15) {
        n_ux = 15;
    } else if (n_ux < 0) {
        n_ux = 0;
    }

    if (n_uz > 15) {
        n_uz = 15;
    } else if (n_uz < 0) {
        n_uz = 0;
    }

    if (mNpc_CheckNpcSet(bx, bz, n_ux, n_uz)) {
        *ux = n_ux;
        *uz = n_uz;
        return TRUE;
    }

    i = gamePT->frame_counter & 0xF;
    n_ux = *ux + neighbor_adjust[i].x;
    n_uz = *uz + neighbor_adjust[i].z;

    if (n_ux > 15) {
        n_ux = 15;
    } else if (n_ux < 0) {
        n_ux = 0;
    }

    if (n_uz > 15) {
        n_uz = 15;
    } else if (n_uz < 0) {
        n_uz = 0;
    }

    if (mNpc_CheckNpcSet(bx, bz, n_ux, n_uz)) {
        *ux = n_ux;
        *uz = n_uz;
        return TRUE;
    }

    for (i = 0; i < 15; i++) {
        n_ux = *ux + neighbor_adjust[i].x;
        n_uz = *uz + neighbor_adjust[i].z;

        if (n_ux > 15) {
            n_ux = 15;
        } else if (n_ux < 0) {
            n_ux = 0;
        }

        if (n_uz > 15) {
            n_uz = 15;
        } else if (n_uz < 0) {
            n_uz = 0;
        }

        if (mNpc_CheckNpcSet(bx, bz, n_ux, n_uz)) {
            *ux = n_ux;
            *uz = n_uz;
            return TRUE;
        }
    }

    return FALSE;
}

static int search_select_unit_cancel_check(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, BlockOrUnit_c block, BlockOrUnit_c* unit, int ofs, int adjust) {
    if (ofs >= 2 && mFI_CheckBgDma(block.x, block.z)) {
        return TRUE;
    }

    if (ofs >= 3 && mEv_use_block_by_other_event(ctrl->type, block)) {
        return TRUE;
    }

    if (mNpc_GetMakeUtNuminBlock(&unit->x, &unit->z, block.x, block.z) == FALSE) {
        return TRUE;
    }

    if (unit->x < adjust || unit->x >= (UT_X_NUM - adjust) || unit->z < adjust || unit->z >= (UT_Z_NUM - adjust)) {
        return TRUE;
    }

    return FALSE;
}

static int search_free_unit_cancel_check(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, BlockOrUnit_c block, BlockOrUnit_c* unit, int ofs, int adjust) {
    if (ofs >= 2 && mFI_CheckBgDma(block.x, block.z)) {
        return TRUE;
    }

    if (
        // clang-format off
        (block.x == evmgr->pool_block.x && block.z == evmgr->pool_block.z) ||
        (block.x == evmgr->station_block.x && block.z == evmgr->station_block.z) ||
        (block.x == evmgr->shrine_block.x && block.z == evmgr->shrine_block.z) ||
        (block.x == evmgr->player_home_block.x && block.z == evmgr->player_home_block.z) ||
        (block.x == evmgr->dock_block.x && block.z == evmgr->dock_block.z)
        // clang-format on
    ) {
        return TRUE;
    }

    return search_select_unit_cancel_check(evmgr, ctrl, block, unit, ofs, adjust);
}

static int search_free_unit(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, BlockOrUnit_c* block, BlockOrUnit_c* unit, int adjust, int seed) {
    aEvMgr_field_info_c* field_info = &evmgr->field_info;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    BlockOrUnit_c block_tmp;
    BlockOrUnit_c unit_tmp;
    int x = field_info->block_max.x - 2;
    int z = field_info->block_max.z - 3;
    int n = x * z;
    int cur;
    int i;
    int nseed;

    for (i = 3; i > 0; i--) {
        for (cur = n; cur > 0; cur--) {
            nseed = rtc_time->month * rtc_time->day + rtc_time->sec + (rtc_time->hour + cur) * 3 + seed * 9;
            if (nseed < 0) {
                nseed = -nseed;
            }
            nseed %= n;
            
            block_tmp.x = 1 + nseed % x;
            block_tmp.z = 2 + nseed / x;
            
            if (search_free_unit_cancel_check(evmgr, ctrl, block_tmp, &unit_tmp, i, adjust) == FALSE) {
                *block = block_tmp;
                *unit = unit_tmp;
                i = 0;
                break;
            }
        }
    }

    return cur;
}

static int search_select_unit(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, BlockOrUnit_c* block, BlockOrUnit_c* unit, int adjust) {
    aEvMgr_field_info_c* field_info = &evmgr->field_info;
    BlockOrUnit_c block_tmp;
    BlockOrUnit_c unit_tmp;
    int x = field_info->block_max.x - 2;
    int z = field_info->block_max.z - 3;
    int n = x * z;
    int cur;
    int i;

    block_tmp.x = block->x;
    block_tmp.z = block->z;
    for (i = 3; i > 0; i--) {
        for (cur = n; cur > 0; cur--) {
            if (search_select_unit_cancel_check(evmgr, ctrl, block_tmp, &unit_tmp, i, adjust) == FALSE) {
                *unit = unit_tmp;
                i = 0;
                break;
            }
        }
    }

    return cur;
}

static int search_empty_unit(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, BlockOrUnit_c* block, BlockOrUnit_c* unit, int seed) {
    aEvMgr_field_info_c* field_info = &evmgr->field_info;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    BlockOrUnit_c ball_block;
    BlockOrUnit_c block_tmp;
    BlockOrUnit_c unit_tmp;
    int x = field_info->block_max.x - 2;
    int z = field_info->block_max.z - 3;
    int n = x * z;
    int cur;
    int i;
    int nseed;

    for (i = 3; i > 0; i--) {
        for (cur = n; cur > 0; cur--) {
            nseed = rtc_time->month * rtc_time->day + rtc_time->sec + (rtc_time->hour + cur) * 7 - seed;
            if (nseed < 0) {
                nseed = -nseed;
            }
            nseed %= n;
            
            block_tmp.x = 1 + nseed % x;
            block_tmp.z = 2 + nseed / x;
            
            if (
                // clang-format off
                (i < 2 || mFI_CheckBgDma(block_tmp.x, block_tmp.z) == FALSE) &&
                (
                    (block_tmp.x != evmgr->pool_block.x || block_tmp.z != evmgr->pool_block.z) &&
                    (block_tmp.x != evmgr->station_block.x || block_tmp.z != evmgr->station_block.z) &&
                    (block_tmp.x != evmgr->shrine_block.x || block_tmp.z != evmgr->shrine_block.z) &&
                    (block_tmp.x != evmgr->player_home_block.x || block_tmp.z != evmgr->player_home_block.z) &&
                    (block_tmp.x != evmgr->dock_block.x || block_tmp.z != evmgr->dock_block.z)
                ) &&
                (i < 3 || mEv_use_block_by_other_event(ctrl->type, block_tmp) == FALSE)
                // clang-format on
            ) {
                if (
                    // clang-format off
                    (
                        i < 3 ||
                        mFI_Wpos2BlockNum(&ball_block.x, &ball_block.z, Common_Get(ball_pos)) == FALSE ||
                        (block_tmp.x != ball_block.x || block_tmp.z != ball_block.z)
                    )
                    // clang-format on
                ) {
                    if (mNpc_GetMakeUtNuminBlock_hard_area(&unit_tmp.x, &unit_tmp.z, block_tmp.x, block_tmp.z, i)) {
                        *block = block_tmp;
                        *unit = unit_tmp;
                        i = 0;
                        break;
                    }
                }
            }
        }
    }

    return cur;
}

static void be_flat_unit(mEv_place_data_c* place_data) {
    mActor_name_t* fg_p;
    mActor_name_t item;
    int res;
    xyz_t pos;

    mFI_BkandUtNum2CenterWpos(&pos, place_data->block.x, place_data->block.z, place_data->unit.x, place_data->unit.z);
    fg_p = mFI_GetUnitFG(pos);

    if (fg_p != NULL && mSN_ClearSnowman(fg_p) == FALSE) {
        item = *fg_p;

        if ((ITEM_IS_BURIED_PITFALL_HOLE(item) || item == SHINE_SPOT) == TRUE) {
            mPB_keep_item(bg_item_fg_sub_dig2take_conv(item));
            mFI_SetFG_common(EMPTY_NO, pos, TRUE);
            mFI_Wpos2DepositOFF(pos);
        } else if (ITEM_IS_SIGNBOARD(item)) {
            mPB_keep_item(ITM_SIGNBOARD);
            mFI_SetFG_common(EMPTY_NO, pos, TRUE);
        }
    }
}

static int search_seaside_unit(EVENT_MANAGER_ACTOR* evmgr, BlockOrUnit_c* block, BlockOrUnit_c* unit, int seed) {
    int n;
    int i;
    int ret = TRUE;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);


    block->z = FG_BLOCK_Z_NUM;
    n = mFI_GetBlockXMax() - 2;
    block->x = 1 + ((seed + rtc_time->day + rtc_time->sec) % n);
    
    if (block->x == evmgr->dock_block.x && block->z == evmgr->dock_block.z) {
        if (block->x > mFI_GetBlockXMax() / 2) {
            block->x--;
        } else {
            block->x++;
        }
    }

    if (mFI_CheckBgDma(block->x, block->z)) {
        if (block->x > mFI_GetBlockXMax() / 2) {
            block->x -= 2;
        } else {
            block->x += 2;
        }
    }

    for (i = 0; i < 5; i++) {
        if (mFI_GetWaveUtinBlock(&unit->x, &unit->z, block->x, block->z) && (unit->x > 0 && unit->x < UT_X_NUM - 1) &&
            (unit->z > 0 && unit->z < UT_Z_NUM - 1)) {
            break;
        }
    }

    if (i == 5) {
        int x;
        
        ret = FALSE;
        x = mFI_GetBlockXMax(); // @cleanup - this is unused
        for (i = mFI_GetBlockXMax() - 1; i != 0; i--) {
            n = mFI_GetBlockXMax() - 2;
            block->x = 1 + ((block->x + i) % n);
            if (mFI_CheckBgDma(block->x, block->z) == FALSE && mFI_GetWaveUtinBlock(&unit->x, &unit->z, block->x, block->z)) {
                ret = TRUE;
                break;
            }
        }
    }

    return ret;
}

static int get_unit_lot4sale(EVENT_MANAGER_ACTOR* evmgr, BlockOrUnit_c* block, BlockOrUnit_c* unit, int seed) {
    aEvMgr_field_info_c* field_info = &evmgr->field_info;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    Anmhome_c* animal_home;
    int lot_count;
    mActor_name_t item;
    BlockOrUnit_c lot_block;
    BlockOrUnit_c lot_unit;
    int i;
    int nseed;
    int ret = 0;

    for (i = field_info->reserve_num; i != 0; i--) {
        lot_count = field_info->reserve_num;
        nseed = (rtc_time->sec + rtc_time->month * rtc_time->hour + rtc_time->day) + (lot_count - i) + seed * 3;
        if (nseed < 0) {
            nseed = -nseed;
        }
        nseed %= lot_count;
        
        animal_home = field_info->reserve_buf;
        lot_block.x = animal_home[nseed].block_x;
        lot_block.z = animal_home[nseed].block_z;

        if (mFI_CheckBgDma(lot_block.x, lot_block.z)) {
            ret = nseed;
            continue;
        }

        lot_unit.x = animal_home[nseed].ut_x;
        lot_unit.z = animal_home[nseed].ut_z;

        mFI_GetBlockUtNum2FG(&item, lot_block.x, lot_block.z, lot_unit.x, lot_unit.z);
        if (mNT_IS_RESERVE(item)) {
            *block = lot_block;
            *unit = lot_unit;
            break;
        }
    }

    if (i == 0 && ret != 0) {
        animal_home = &field_info->reserve_buf[ret];
        lot_block.x = animal_home->block_x;
        lot_block.z = animal_home->block_z;
        lot_unit.x = animal_home->ut_x;
        lot_unit.z = animal_home->ut_z;
        mFI_GetBlockUtNum2FG(&item, lot_block.x, lot_block.z, lot_unit.x, lot_unit.z);
        if (mNT_IS_RESERVE(item)) {
            *block = lot_block;
            *unit = lot_unit;
            i = ret;
        }
    }

    return i;
}

static int search_empty_hide_unit(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, BlockOrUnit_c* block, BlockOrUnit_c* unit, int seed) {
    aEvMgr_field_info_c* field_info = &evmgr->field_info;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    BlockOrUnit_c ball_block;
    BlockOrUnit_c block_tmp;
    BlockOrUnit_c unit_tmp;
    int x = field_info->block_max.x - 2;
    int z = field_info->block_max.z - 3;
    int n = x * z;
    int cur;
    int nseed;

    for (cur = n; cur > 0; cur--) {
        nseed = rtc_time->month * rtc_time->day + rtc_time->sec + (rtc_time->hour + cur) * 7 - seed;
        if (nseed < 0) {
            nseed = -nseed;
        }
        nseed %= n;
        
        block_tmp.x = 1 + nseed % x;
        block_tmp.z = 2 + nseed / x;
        
        if (
            // clang-format off
            (mFI_CheckBgDma(block_tmp.x, block_tmp.z) == FALSE) &&
            (
                (block_tmp.x != evmgr->pool_block.x || block_tmp.z != evmgr->pool_block.z) &&
                (block_tmp.x != evmgr->station_block.x || block_tmp.z != evmgr->station_block.z) &&
                (block_tmp.x != evmgr->shrine_block.x || block_tmp.z != evmgr->shrine_block.z) &&
                (block_tmp.x != evmgr->player_home_block.x || block_tmp.z != evmgr->player_home_block.z) &&
                (block_tmp.x != evmgr->dock_block.x || block_tmp.z != evmgr->dock_block.z)
            ) &&
            (mEv_use_block_by_other_event(ctrl->type, block_tmp) == FALSE)
            // clang-format on
        ) {
            if (
                // clang-format off
                (
                    mFI_Wpos2BlockNum(&ball_block.x, &ball_block.z, Common_Get(ball_pos)) == FALSE ||
                    (block_tmp.x != ball_block.x || block_tmp.z != ball_block.z)
                )
                // clang-format on
            ) {
                if (mNpc_GetMakeUtNuminBlock_hide_hard_area(&unit_tmp.x, &unit_tmp.z, block_tmp.x, block_tmp.z, 2)) {
                    *block = block_tmp;
                    *unit = unit_tmp;
                    break;
                }
            }
        }
    }

    return cur;
}

static int search_empty_hide_unit_sub(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, BlockOrUnit_c* block, BlockOrUnit_c* unit, int bx, int bz) {
    aEvMgr_field_info_c* field_info = &evmgr->field_info;
    BlockOrUnit_c ball_block;
    BlockOrUnit_c block_tmp;
    BlockOrUnit_c unit_tmp;
        
    block_tmp.x = bx;
    block_tmp.z = bz;
    if (mFI_CheckBgDma(block_tmp.x, block_tmp.z) != FALSE) {
        return FALSE;
    }

    if (
        // clang-format off
        (block_tmp.x == evmgr->pool_block.x && block_tmp.z == evmgr->pool_block.z) ||
        (block_tmp.x == evmgr->station_block.x && block_tmp.z == evmgr->station_block.z) ||
        (block_tmp.x == evmgr->shrine_block.x && block_tmp.z == evmgr->shrine_block.z) ||
        (block_tmp.x == evmgr->dock_block.x && block_tmp.z == evmgr->dock_block.z)
        // clang-format on
    ) {
        return FALSE;
    }

    if (mEv_use_block_by_other_event(ctrl->type, block_tmp) != FALSE) {
        return FALSE;
    }

    if (
        // clang-format off
        (
            mFI_Wpos2BlockNum(&ball_block.x, &ball_block.z, Common_Get(ball_pos)) != FALSE &&
            (block_tmp.x == ball_block.x && block_tmp.z == ball_block.z)
        )
        // clang-format on
    ) {
        return FALSE;
    }

    if (mNpc_GetMakeUtNuminBlock_hide_hard_area(&unit_tmp.x, &unit_tmp.z, block_tmp.x, block_tmp.z, 2) == FALSE) {
        return FALSE;
    }

    *block = block_tmp;
    *unit = unit_tmp;
    return TRUE;
}

static int search_empty_hide_unit_player(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, BlockOrUnit_c* block, BlockOrUnit_c* unit) {
    return search_empty_hide_unit_sub(evmgr, ctrl, block, unit, 3, 2);
}

static int search_empty_hide_unit_toudai(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, BlockOrUnit_c* block, BlockOrUnit_c* unit) {
    int bx;
    int bz;

    if (mFI_BlockKind2BkNum(&bx, &bz, mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_MARINE) == TRUE) {
        return search_empty_hide_unit_sub(evmgr, ctrl, block, unit, bx, bz);
    }

    return FALSE;
}

static int delete_FG(aEvMgr_event_ctrl_c* ctrl, u8 id) {
    mEv_place_data_c* place_data;
    
    if (mFI_CheckFieldData() != TRUE) {
        return FALSE;
    }

    place_data = mEv_get_common_place(ctrl->type, (u8)id);
    if (place_data != NULL) {
        if (mFI_SetFGStructure_common(place_data->actor_name, place_data->block.x, place_data->block.z, place_data->unit.x, place_data->unit.z, mFI_SET_STRUCTURE_REMOVE) == FALSE) {
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return FALSE;
        }

        mEv_clear_common_place(ctrl->type, (u8)id);
    }

    return TRUE;
}

static int delete_FG2(int type, u8 id) {
    mEv_place_data_c* place_data;
    
    if (mFI_CheckFieldData() != TRUE) {
        return FALSE;
    }

    place_data = mEv_get_common_place(type, (u8)id);
    if (place_data != NULL) {
        mFI_SetFGStructure_common(place_data->actor_name, place_data->block.x, place_data->block.z, place_data->unit.x, place_data->unit.z, mFI_SET_STRUCTURE_REMOVE);
        mEv_clear_common_place(type, (u8)id);
    }

    return TRUE;
}

static void clean_FG(EVENT_MANAGER_ACTOR* evmgr, u32 blockkind) {
    if (mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELDTYPE2_FG) {
        switch (blockkind) {
            case mRF_BLOCKKIND_POOL:
                mPB_keep_all_item_in_block(evmgr->pool_block.x, evmgr->pool_block.z);
                break;
            case mRF_BLOCKKIND_SHRINE:
                mPB_keep_all_item_in_block(evmgr->shrine_block.x, evmgr->shrine_block.z);
                break;
            case mRF_BLOCKKIND_STATION:
                mPB_keep_all_item_in_block(evmgr->station_block.x, evmgr->station_block.z);
                break;
            case mRF_BLOCKKIND_PLAYER:
                mPB_keep_all_item_in_block(evmgr->player_home_block.x, evmgr->player_home_block.z);
                break;
        }
    }
}

static mEv_place_data_c* make_FG_somewhere_lot4sale(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, mActor_name_t ev_name, u8 id) {
    mEv_place_data_c place_data;
    mEv_place_data_c* common_place_data;
    mActor_name_t reserve_item;
    u8* save_area;

    reserve_item = SIGN00;
    if (mFI_GET_TYPE(mFI_GetFieldId()) != mFI_FIELDTYPE2_FG) {
        return NULL;
    }

    common_place_data = mEv_get_common_place(ctrl->type, (u8)id);
    if (common_place_data != NULL) {
        mFI_GetBlockUtNum2FG(&reserve_item, common_place_data->block.x, common_place_data->block.z, common_place_data->unit.x, common_place_data->unit.z);

        if (!mNT_IS_RESERVE(reserve_item)) {
            // the selected lot doesn't have a reserve item so re-roll event lot
            common_place_data = NULL;
        }
    }

    if (common_place_data == NULL) {
        save_area = mEv_get_save_area(ctrl->type, mEv_EVENT_NUM); // search free area
        if (save_area != NULL) {
            memcpy(&place_data, save_area, sizeof(mEv_place_data_c));
            mFI_GetBlockUtNum2FG(&reserve_item, place_data.block.x, place_data.block.z, place_data.unit.x, place_data.unit.z);
            if (!mNT_IS_RESERVE(reserve_item)) {
                // reset save area because it's also not a free lot anymore
                mEv_clear_save_area(ctrl->type, mEv_EVENT_NUM);
                save_area = NULL;
            }
        }

        // try reserving save area data for event
        if (save_area == NULL) {
            place_data.actor_name = ev_name;
            if (get_unit_lot4sale(evmgr, &place_data.block, &place_data.unit, ctrl->type + ev_name + id) == 0) {
                // no free lots to spawn the event at
                mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
                return NULL;
            }

            save_area = mEv_reserve_save_area(ctrl->type, mEv_EVENT_NUM);
            if (save_area != NULL) {
                memcpy(save_area, &place_data, sizeof(mEv_place_data_c));
            }
        }

        // reserve common place data for event
        common_place_data = mEv_reserve_common_place(ctrl->type, (u8)id);
        if (common_place_data == NULL) {
            // failed to reserve common place data
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return NULL;
        }

        memcpy(common_place_data, &place_data, sizeof(mEv_place_data_c));
    }

    if (mFI_SetFGStructure_common(common_place_data->actor_name, common_place_data->block.x, common_place_data->block.z, common_place_data->unit.x, common_place_data->unit.z, mFI_SET_STRUCTURE_SET) == FALSE) {
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return NULL;
    }

    return common_place_data;
}

static mEv_place_data_c* make_actor_in_seaside_block(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, mActor_name_t ev_name, u8 id) {
    mEv_place_data_c place_data;
    mEv_place_data_c* common_place_data;

    if (mFI_GET_TYPE(mFI_GetFieldId()) != mFI_FIELDTYPE2_FG) {
        return NULL;
    }

    common_place_data = mEv_get_common_place(ctrl->type, (u8)id);
    if (common_place_data == NULL) {
        place_data.actor_name = ev_name;
        place_data.flag = 1;

        if (search_seaside_unit(evmgr, &place_data.block, &place_data.unit, ctrl->type + ev_name + id) == FALSE) {
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return NULL;
        }

        common_place_data = mEv_reserve_common_place(ctrl->type, (u8)id);
        if (common_place_data == NULL) {
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return NULL;
        }

        memcpy(common_place_data, &place_data, sizeof(mEv_place_data_c));
    }

    return common_place_data;
}

static mEv_place_data_c* make_actor_in_free_block(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, mActor_name_t ev_name, u8 id, int adjust) {
    mEv_place_data_c place_data;
    mEv_place_data_c* common_place_data;

    if (mFI_GET_TYPE(mFI_GetFieldId()) != mFI_FIELDTYPE2_FG) {
        return NULL;
    }

    common_place_data = mEv_get_common_place(ctrl->type, (u8)id);
    if (common_place_data == NULL) {
        place_data.actor_name = ev_name;
        place_data.flag = 1;

        if (search_free_unit(evmgr, ctrl, &place_data.block, &place_data.unit, adjust, ctrl->type + ev_name + id) == FALSE) {
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return NULL;
        }

        common_place_data = mEv_reserve_common_place(ctrl->type, (u8)id);
        if (common_place_data == NULL) {
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return NULL;
        }

        memcpy(common_place_data, &place_data, sizeof(mEv_place_data_c));
    }

    return common_place_data;
}

static mEv_place_data_c* make_actor_in_select_block(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, mActor_name_t ev_name, u8 id, int bx, int bz, int adjust) {
    mEv_place_data_c place_data;
    mEv_place_data_c* common_place_data;

    if (mFI_GET_TYPE(mFI_GetFieldId()) != mFI_FIELDTYPE2_FG) {
        return NULL;
    }

    common_place_data = mEv_get_common_place(ctrl->type, (u8)id);
    if (common_place_data == NULL) {
        place_data.actor_name = ev_name;
        place_data.flag = 1;
        place_data.block.x = bx;
        place_data.block.z = bz;

        if (search_select_unit(evmgr, ctrl, &place_data.block, &place_data.unit, adjust) == FALSE) {
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return NULL;
        }

        common_place_data = mEv_reserve_common_place(ctrl->type, (u8)id);
        if (common_place_data == NULL) {
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return NULL;
        }

        memcpy(common_place_data, &place_data, sizeof(mEv_place_data_c));
    }

    return common_place_data;
}

static mEv_place_data_c* make_move_actor_in_free_block(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, mActor_name_t ev_name, u8 id) {
    mEv_place_data_c place_data;
    mEv_place_data_c* common_place_data;

    if (mFI_GET_TYPE(mFI_GetFieldId()) != mFI_FIELDTYPE2_FG) {
        return NULL;
    }

    common_place_data = mEv_get_common_place(ctrl->type, (u8)id);
    if (common_place_data == NULL) {
        place_data.actor_name = ev_name;
        place_data.flag = 1;

        if (search_empty_unit(evmgr, ctrl, &place_data.block, &place_data.unit, ctrl->type + ev_name + id) == FALSE) {
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return NULL;
        }

        common_place_data = mEv_reserve_common_place(ctrl->type, (u8)id);
        if (common_place_data == NULL) {
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return NULL;
        }

        memcpy(common_place_data, &place_data, sizeof(mEv_place_data_c));
    }

    if (mFI_AddMoveActorList(common_place_data->actor_name, common_place_data->block.x, common_place_data->block.z, common_place_data->unit.x, common_place_data->unit.z, 0) == FALSE) {
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return NULL;
    }

    return common_place_data;
}

static mEv_place_data_c* make_actor_in_free_block_hide(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, mActor_name_t ev_name, u8 id) {
    mEv_place_data_c place_data;
    mEv_place_data_c* common_place_data;

    if (mFI_GET_TYPE(mFI_GetFieldId()) != mFI_FIELDTYPE2_FG) {
        return NULL;
    }

    common_place_data = mEv_get_common_place(ctrl->type, (u8)id);
    if (common_place_data == NULL) {
        place_data.flag = 1;
        place_data.actor_name = ev_name;

        if (
            // clang-format off
            search_empty_hide_unit(evmgr, ctrl, &place_data.block, &place_data.unit, ctrl->type + ev_name + id) == FALSE &&
            search_empty_hide_unit_player(evmgr, ctrl, &place_data.block, &place_data.unit) == FALSE &&
            search_empty_hide_unit_toudai(evmgr, ctrl, &place_data.block, &place_data.unit) == FALSE
            // clang-format on
        ) {
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return NULL;
        }

        common_place_data = mEv_reserve_common_place(ctrl->type, (u8)id);
        if (common_place_data == NULL) {
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return NULL;
        }

        memcpy(common_place_data, &place_data, sizeof(mEv_place_data_c));
    }

    return common_place_data;
}

static mEv_place_data_c* make_actor_in_fixed_block(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, BlockOrUnit_c* block, BlockOrUnit_c* unit, mActor_name_t ev_name, u8 id) {
    mEv_place_data_c place_data;
    mEv_place_data_c* common_place_data;

    if (mFI_GET_TYPE(mFI_GetFieldId()) != mFI_FIELDTYPE2_FG) {
        return NULL;
    }

    common_place_data = mEv_get_common_place(ctrl->type, (u8)id);
    if (common_place_data == NULL) {
        place_data.flag = 2;
        place_data.actor_name = ev_name;
        place_data.block = *block;
        place_data.unit = *unit;

        if (mNpc_CheckNpcSet(place_data.block.x, place_data.block.z, place_data.unit.x, place_data.unit.z) == FALSE &&
            neighbor_check(&place_data.unit.x, &place_data.unit.z, place_data.block.x, place_data.block.z) == FALSE) {
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return NULL;
        }

        common_place_data = mEv_reserve_common_place(ctrl->type, (u8)id);
        if (common_place_data == NULL) {
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return NULL;
        }

        memcpy(common_place_data, &place_data, sizeof(mEv_place_data_c));
    }

    return common_place_data;
}

static mEv_place_data_c* make_actor_in_fixed_block_checkless(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, BlockOrUnit_c* block, BlockOrUnit_c* unit, mActor_name_t ev_name, u8 id) {
    mEv_place_data_c place_data;
    mEv_place_data_c* common_place_data;

    if (mFI_GET_TYPE(mFI_GetFieldId()) != mFI_FIELDTYPE2_FG) {
        return NULL;
    }

    common_place_data = mEv_get_common_place(ctrl->type, (u8)id);
    if (common_place_data == NULL) {
        place_data.flag = 2;
        place_data.actor_name = ev_name;
        place_data.block = *block;
        place_data.unit = *unit;

        common_place_data = mEv_reserve_common_place(ctrl->type, (u8)id);
        if (common_place_data == NULL) {
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return NULL;
        }

        memcpy(common_place_data, &place_data, sizeof(mEv_place_data_c));
    }

    return common_place_data;
}

static int make_control_actor(s16 profile_id) {
    return !!Actor_info_make_actor(&((GAME_PLAY*)gamePT)->actor_info, gamePT, profile_id, 0.0f, 0.0f, 0.0f, 0, 0, 0, -1, -1, -1, EMPTY_NO, -1, -1, -1);
}

static int make_control_actor_without_indoor(s16 profile_id) {
    if (mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELDTYPE2_FG) {
        return make_control_actor(profile_id);
    }

    return FALSE;
}

static mEv_place_data_c* make_actor_in_reserved_block(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, int map_type, u32 block_kind, u8 id) {
    mEv_place_data_c place_data;
    mEv_place_data_c* common_place_data;

    if (mFI_GET_TYPE(mFI_GetFieldId()) != mFI_FIELDTYPE2_FG) {
        return NULL;
    }

    common_place_data = mEv_get_common_place(ctrl->type, (u8)id);
    if (common_place_data == NULL) {
        place_data.flag = 1;

        switch (block_kind) {
            case mRF_BLOCKKIND_POOL:
                place_data.block.x = evmgr->pool_block.x;
                place_data.block.z = evmgr->pool_block.z;
                break;
            case mRF_BLOCKKIND_STATION:
                place_data.block.x = evmgr->station_block.x;
                place_data.block.z = evmgr->station_block.z;
                break;
            case mRF_BLOCKKIND_SHRINE:
                place_data.block.x = evmgr->shrine_block.x;
                place_data.block.z = evmgr->shrine_block.z;
                break;
            case mRF_BLOCKKIND_PLAYER:
                place_data.block.x = evmgr->player_home_block.x;
                place_data.block.z = evmgr->player_home_block.z;
                break;
            default:
                // Search for the requested block type
                if (mFI_BlockKind2BkNum(&place_data.block.x, &place_data.block.z, block_kind) == FALSE) {
                    // Couldn't locate the block
                    mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
                    return NULL;
                }
                break;
        }

        if (mEvMN_GetEventSetUtInBlock(&place_data.actor_name, &place_data.unit.x, &place_data.unit.z, ctrl->type, map_type) == FALSE) {
            // Couldn't locate the unit
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return NULL;
        }

        common_place_data = mEv_reserve_common_place(ctrl->type, (u8)id);
        if (common_place_data == NULL) {
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return NULL;
        }

        memcpy(common_place_data, &place_data, sizeof(mEv_place_data_c));
    }

    return common_place_data;
}

static mEv_place_data_c* make_FG_in_reserved_block(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, int map_type, u32 block_kind, u8 id) {
    mEv_place_data_c place_data;
    mEv_place_data_c* common_place_data;

    if (mFI_GET_TYPE(mFI_GetFieldId()) != mFI_FIELDTYPE2_FG) {
        return NULL;
    }

    common_place_data = mEv_get_common_place(ctrl->type, (u8)id);
    if (common_place_data == NULL) {
        switch (block_kind) {
            case mRF_BLOCKKIND_POOL:
                place_data.block.x = evmgr->pool_block.x;
                place_data.block.z = evmgr->pool_block.z;
                break;
            case mRF_BLOCKKIND_SHRINE:
                place_data.block.x = evmgr->shrine_block.x;
                place_data.block.z = evmgr->shrine_block.z;
                break;
            default:
                // Search for the requested block type
                if (mFI_BlockKind2BkNum(&place_data.block.x, &place_data.block.z, block_kind) == FALSE) {
                    // Couldn't locate the block
                    mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
                    return NULL;
                }
                break;
        }

        if (mEvMN_GetEventSetUtInBlock(&place_data.actor_name, &place_data.unit.x, &place_data.unit.z, ctrl->type, map_type) == FALSE) {
            // Couldn't locate the unit
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return NULL;
        }

        common_place_data = mEv_reserve_common_place(ctrl->type, (u8)id);
        if (common_place_data == NULL) {
            mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
            return NULL;
        }

        memcpy(common_place_data, &place_data, sizeof(mEv_place_data_c));
    }

    if (mFI_SetFGStructure_common(common_place_data->actor_name, common_place_data->block.x, common_place_data->block.z, common_place_data->unit.x, common_place_data->unit.z, mFI_SET_STRUCTURE_SET) == FALSE) {
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return NULL;
    }

    return common_place_data;
}

static mEv_place_data_c* show_actor_at_wade(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, u8 id) {
    mEv_place_data_c sel_place_data;
    mEv_place_data_c* place_data;

    if (mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELDTYPE2_FG) {
        place_data = mEv_get_common_place(ctrl->type, (u8)id);
        if (place_data != NULL) {
            if (evmgr->next_block.x == place_data->block.x && evmgr->next_block.z == place_data->block.z) {
                return aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN;
            }

            if (get_forward_block(&ctrl->block.x, &ctrl->block.z) == FALSE) {
                return aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN;
            }

            if (ctrl->block.x != place_data->block.x || ctrl->block.z != place_data->block.z) {
                return aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN;
            }

            if (mNpc_CheckNpcSet(place_data->block.x, place_data->block.z, place_data->unit.x, place_data->unit.z) == FALSE ||
                mFI_CheckLapPolice(place_data->block.x, place_data->block.z, place_data->unit.x, place_data->unit.z) != FALSE) {
                memcpy(&sel_place_data, place_data, sizeof(mEv_place_data_c));

                if (mNpc_GetMakeUtNuminBlock(&sel_place_data.unit.x, &sel_place_data.unit.z, place_data->block.x, place_data->block.z) == FALSE) {
                    if (search_free_unit(evmgr, ctrl, &place_data->block, &place_data->unit, 1, fluc + ctrl->type + id)) {
                        // @BUG - this is completely unnecessary, we call memcpy on the same thing immediately after
                        memcpy(place_data, &sel_place_data, sizeof(mEv_place_data_c));
                    } else {
                        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
                        return NULL;
                    }

                }

                memcpy(place_data, &sel_place_data, sizeof(mEv_place_data_c));
            }

            be_flat_unit(place_data);
            if (CLIP(npc_clip)->setupActor_proc((GAME_PLAY*)gamePT, place_data->actor_name, -1, -1, -1, place_data->block.x, place_data->block.z, place_data->unit.x, place_data->unit.z) == FALSE) {
                return NULL;
            }

            return place_data;
        }
    }

    return aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN;
}

static mEv_place_data_c* show_actor_at_wade_checkless(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, u8 id) {
    mEv_place_data_c* place_data;

    if (mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELDTYPE2_FG) {
        place_data = mEv_get_common_place(ctrl->type, (u8)id);
        if (place_data != NULL) {
            if (evmgr->next_block.x == place_data->block.x && evmgr->next_block.z == place_data->block.z) {
                return aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN;
            }

            if (get_forward_block(&ctrl->block.x, &ctrl->block.z) == FALSE) {
                return aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN;
            }

            if (ctrl->block.x != place_data->block.x || ctrl->block.z != place_data->block.z) {
                return aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN;
            }

            be_flat_unit(place_data);
            if (CLIP(npc_clip)->setupActor_proc((GAME_PLAY*)gamePT, place_data->actor_name, -1, -1, -1, place_data->block.x, place_data->block.z, place_data->unit.x, place_data->unit.z)) {
                return place_data;
            }

            return NULL;
        }
    }

    return aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN;
}

static mEv_place_data_c* show_actor_at_wade_checkfgcol(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, u8 id) {
    // what the hell is going on in this function??
    // these should NOT be required to be volatile.
    volatile BlockOrUnit_c unit;
    volatile mEv_place_data_c* place_data; // issue here, there's no way this is actually volatile. Removing volatile causes some loads to be optimized away.
    GAME_PLAY* play;

    if (mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELDTYPE2_FG) {
        place_data = mEv_get_common_place(ctrl->type, (u8)id);
        if (place_data != NULL) {
            if (evmgr->next_block.x == place_data->block.x && evmgr->next_block.z == place_data->block.z) {
                return aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN;
            }

            if (get_forward_block(&ctrl->block.x, &ctrl->block.z) == FALSE) {
                return aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN;
            }

            if (ctrl->block.x != place_data->block.x || ctrl->block.z != place_data->block.z) {
                return aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN;
            }

            unit.x = place_data->unit.x;
            unit.z = place_data->unit.z;
            if (mNpc_GetMakeUtNuminBlock33((int*)&unit.x, (int*)&unit.z, place_data->unit.x, place_data->unit.z, place_data->block.x, place_data->block.z) == TRUE) {
                place_data->unit.x = unit.x;
                place_data->unit.z = unit.z;
            } else if (mNpc_GetMakeUtNuminBlock((int*)&unit.x, (int*)&unit.z, place_data->block.x, place_data->block.z) == TRUE) {
                place_data->unit.x = unit.x;
                place_data->unit.z = unit.z;
            } else {
                return aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN;
            }

            be_flat_unit((mEv_place_data_c*)place_data);
            play = (GAME_PLAY*)gamePT;
            if (CLIP(npc_clip)->setupActor_proc(play, ((mEv_place_data_c*)place_data)->actor_name, -1, -1, -1, ((mEv_place_data_c*)place_data)->block.x, ((mEv_place_data_c*)place_data)->block.z, ((mEv_place_data_c*)place_data)->unit.x, ((mEv_place_data_c*)place_data)->unit.z) == FALSE) {
                return NULL;
            }

            return (mEv_place_data_c*)place_data;
        }
    }

    return aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN;
}

static mEv_place_data_c* walk_actor_at_wade(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, u8 id) {
    mEv_place_data_c place_data;
    mEv_place_data_c* common_place_data;
    int i;

    if (mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELDTYPE2_FG) {
        common_place_data = mEv_get_common_place(ctrl->type, (u8)id);
        if (common_place_data != NULL) {
            memcpy(&place_data, common_place_data, sizeof(mEv_place_data_c));
            for (i = 3; i > 0; i--) {
                if (search_free_unit(evmgr, ctrl, &place_data.block, &place_data.unit, 1, i + fluc + ctrl->type + place_data.actor_name + id) == FALSE) {
                    mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
                    return NULL;
                }

                if (
                    (place_data.block.x != common_place_data->block.x || place_data.block.z != common_place_data->block.z) ||
                    (i < 3 && ((place_data.unit.x != common_place_data->unit.x || place_data.unit.z != common_place_data->unit.z) || i < 2))
                ) {
                    break;
                }

            }

            memcpy(common_place_data, &place_data, sizeof(mEv_place_data_c));
            return common_place_data;
        }
    }

    return NULL;
}

static mEv_place_data_c* walk_actor_at_wade_hide(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, u8 id) {
    mEv_place_data_c place_data;
    mEv_place_data_c* common_place_data;
    int i;

    if (mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELDTYPE2_FG) {
        common_place_data = mEv_get_common_place(ctrl->type, (u8)id);
        if (common_place_data != NULL) {
            memcpy(&place_data, common_place_data, sizeof(mEv_place_data_c));
            for (i = 3; i > 0; i--) {
                if (
                    search_empty_hide_unit(evmgr, ctrl, &place_data.block, &place_data.unit, i + fluc + ctrl->type + place_data.actor_name + id) == FALSE &&
                    search_empty_hide_unit_player(evmgr, ctrl, &place_data.block, &place_data.unit) == FALSE &&
                    search_empty_hide_unit_toudai(evmgr, ctrl, &place_data.block, &place_data.unit) == FALSE
                ) {
                    mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
                    return NULL;
                }

                if (
                    (place_data.block.x != common_place_data->block.x || place_data.block.z != common_place_data->block.z) ||
                    (i < 3 && ((place_data.unit.x != common_place_data->unit.x || place_data.unit.z != common_place_data->unit.z) || i < 2))
                ) {
                    break;
                }

            }

            memcpy(common_place_data, &place_data, sizeof(mEv_place_data_c));
            return common_place_data;
        }
    }

    return NULL;
}

static mEv_place_data_c* walk_FG_somewhere_lot4sale(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl, u8 id) {
    mEv_place_data_c place_data;
    mEv_place_data_c* common_place_data;
    u8* save_area;

    if (mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELDTYPE2_FG) {
        common_place_data = mEv_get_common_place(ctrl->type, (u8)id);
        if (common_place_data != NULL) {
            memcpy(&place_data, common_place_data, sizeof(mEv_place_data_c));
            
            delete_FG(ctrl, id);
            if (get_unit_lot4sale(evmgr, &place_data.block, &place_data.unit, fluc + ctrl->type + place_data.actor_name + id) == 0) {
                mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
                return NULL;
            }

            if (mFI_SetFGStructure_common(place_data.actor_name, place_data.block.x, place_data.block.z, place_data.unit.x, place_data.unit.z, mFI_SET_STRUCTURE_SET) == FALSE) {
                mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
                return NULL;
            }

            common_place_data = mEv_reserve_common_place(ctrl->type, (u8)id);
            if (common_place_data == NULL) {
                mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
                return NULL;
            }

            memcpy(common_place_data, &place_data, sizeof(mEv_place_data_c));

            save_area = mEv_get_save_area(ctrl->type, mEv_EVENT_NUM);
            if (save_area == NULL) {
                save_area = mEv_reserve_save_area(ctrl->type, mEv_EVENT_NUM);
            }

            if (save_area != NULL) {
                memcpy(save_area, &place_data, sizeof(mEv_place_data_c));
            }

            return common_place_data;
        }
    }

    return NULL;
}

static void make_effect(int type) {
    ACTOR* playerx = GET_PLAYER_ACTOR_NOW_ACTOR();

    if (mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELDTYPE2_FG) {
        eEC_CLIP->effect_make_proc(type, playerx->world.position, 3, 0, gamePT, RSV_NO, 0, 0);
    }
}

static void delete_effect(int type) {
    eEC_CLIP->effect_kill_proc(type, RSV_NO);
}

static void set_escape_unit(s_xyz* pos_s, int bx, int bz, int ux, int uz) {
    xyz_t pos;

    mFI_BkandUtNum2CenterWpos(&pos, bx, bz, ux, uz);
    pos_s->x = pos.x;
    pos_s->y = pos.y;
    pos_s->z = pos.z;
}

static int lap_fixed_actor(int bx, int bz, int ux, int uz) {
    if (mFI_CheckLapPolice(bx, bz, ux, uz) != FALSE) {
        return TRUE;
    }

    if (bx == 3 && bz == 1 && ux == 7 && uz == 7) {
        return TRUE;
    }

    return FALSE;
}

static int is_need2escape_unit(int bx, int bz, int ux, int uz) {
    if (mEvMN_CheckLapPlayer(ux, uz)) {
        return TRUE;
    }

    if (lap_fixed_actor(bx, bz, ux, uz)) {
        return TRUE;
    }

    if (mNpc_CheckNpcSet(bx, bz, ux, uz) == FALSE) {
        return TRUE;
    }

    return FALSE;
}

static int player_lap_check(EVENT_MANAGER_ACTOR* evmgr, s_xyz* escape_pos, xyz_t* pos, u32 blockkind, int type) {
    BlockOrUnit_c block;
    BlockOrUnit_c unit;
    BlockOrUnit_c adjusted_unit;
    BlockOrUnit_c police_block;
    int n;
    int i;
    int j;

    escape_pos->x = pos->x;
    escape_pos->y = pos->y;
    escape_pos->z = pos->z;
    mFI_Wpos2BkandUtNuminBlock(&block.x, &block.z, &unit.x, &unit.z, *pos);

    if (block.x != 3 || block.z != 1 || unit.x != 7 || unit.z != 7) {
        switch (blockkind) {
            case mRF_BLOCKKIND_POOL:
                if (evmgr->pool_block.x != block.x || evmgr->pool_block.z != block.z) {
                    return FALSE;
                }
                break;
            case mRF_BLOCKKIND_STATION:
                if (evmgr->station_block.x != block.x || evmgr->station_block.z != block.z) {
                    return FALSE;
                }
                break;
            case mRF_BLOCKKIND_SHRINE:
                if (evmgr->shrine_block.x != block.x || evmgr->shrine_block.z != block.z) {
                    return FALSE;
                }
                break;
            case mRF_BLOCKKIND_PLAYER:
                if (evmgr->player_home_block.x != block.x || evmgr->player_home_block.z != block.z) {
                    return FALSE;
                }
                break;
            default:
                if ((type != mEv_EVENT_MORNING_AEROBICS && type != mEv_EVENT_SPORTS_FAIR_AEROBICS) || 
                    mFI_BlockKind2BkNum(&police_block.x, &police_block.z, mRF_BLOCKKIND_POLICE) == FALSE ||
                    police_block.x != block.x || police_block.z != block.z) {
                    return FALSE;
                }
                break;
        }
    }

    n = mEvMN_CheckLapPlayer(unit.x, unit.z);
    if (n != 0) {
        static int delta[2][28][2] = {
            // clang-format off
            {
                {0, 1},
                {0, -1},
                {1, 0},
                {-1, 0},
                {1, 1},
                {-1, 1},
                {1, -1},
                {-1, -1},
                {2, 2},
                {-2, 2},
                {2, -2},
                {-2, -2},
                {-1, 2},
                {-2, 1},
                {1, 2},
                {2, 1},
                {-1, -2},
                {-2, -1},
                {1, -2},
                {2, -1},
                {-3, 0},
                {3, 0},
                {0, 3},
                {0, -3},
                {-3, -3},
                {3, 3},
                {-3, 3},
                {3, -3}
            },
            {
                {0, 1},
                {0, -1},
                {1, 0},
                {-1, 0},
                {0, 2},
                {0, -2},
                {2, 0},
                {-2, 0},
                {2, 2},
                {-2, 2},
                {2, -2},
                {-2, -2},
                {-1, 2},
                {-2, 1},
                {1, 2},
                {2, 1},
                {-1, -2},
                {-2, -1},
                {1, -2},
                {2, -1},
                {-3, 1},
                {3, -1},
                {1, 3},
                {-1, -3},
                {-3, -1},
                {3, 1},
                {-1, 3},
                {1, -3}
            },
            // clang-format on
        };

        for (i = 0; i < 28; i++) {
            adjusted_unit.x = unit.x + delta[n - 1][i][0];
            
            if (adjusted_unit.x >= 0 && adjusted_unit.x < UT_X_NUM) {
                adjusted_unit.z = unit.z + delta[n - 1][i][1];
                if (adjusted_unit.z >= 0 && adjusted_unit.z < UT_Z_NUM) {
                    if (is_need2escape_unit(block.x, block.z, adjusted_unit.x, adjusted_unit.z) == FALSE) {
                        set_escape_unit(escape_pos, block.x, block.z, adjusted_unit.x, adjusted_unit.z);
                        return TRUE;
                    }
                }
            }
        }
    } else if (lap_fixed_actor(block.x, block.z, unit.x, unit.z)) {
        static int delta[12][2] = {
            {0, 1},
            {1, 1},
            {1, 0},
            {2, 0},
            {2, 1},
            {2, -1},
            {1, -1},
            {-1, 1},
            {0, 2},
            {-1, 2},
            {1, 2},
            {2, 2},
        };

        for (j = 0; j < 12; j++) {
            adjusted_unit.x = unit.x + delta[j][0];
            if (adjusted_unit.x >= 0 && adjusted_unit.x < UT_X_NUM) {
                adjusted_unit.z = unit.z + delta[j][1];
                if (adjusted_unit.z >= 0 && adjusted_unit.z < UT_Z_NUM) {
                    if (is_need2escape_unit(block.x, block.z, adjusted_unit.x, adjusted_unit.z) == FALSE) {
                        set_escape_unit(escape_pos, block.x, block.z, adjusted_unit.x, adjusted_unit.z);
                        return TRUE;
                    }
                }
            }
        }
    } else {
        return FALSE;
    }

    for (i = 1; i <= 4; i++) {
        for (j = -i; j <= i; j++) {
            adjusted_unit.x = unit.x + j;
            if (adjusted_unit.x >= 0 && adjusted_unit.x < UT_X_NUM) {
                adjusted_unit.z = unit.z + i;
                if (adjusted_unit.z >= 0 && adjusted_unit.z < UT_Z_NUM) {
                    if (is_need2escape_unit(block.x, block.z, adjusted_unit.x, adjusted_unit.z) == FALSE) {
                        set_escape_unit(escape_pos, block.x, block.z, adjusted_unit.x, adjusted_unit.z);
                        return TRUE;
                    }

                    adjusted_unit.z = unit.z - i;
                    if (adjusted_unit.z >= 0 && adjusted_unit.z < UT_Z_NUM) {
                        if (is_need2escape_unit(block.x, block.z, adjusted_unit.x, adjusted_unit.z) == FALSE) {
                            set_escape_unit(escape_pos, block.x, block.z, adjusted_unit.x, adjusted_unit.z);
                            return TRUE;
                        }
                    }
                }
            }
        }

        for (j = 1 - i; j <= i - 1; j++) {
            adjusted_unit.x = unit.x + i;
            if (adjusted_unit.x >= 0 && adjusted_unit.x < UT_X_NUM) {
                adjusted_unit.z = unit.z + j;
                if (adjusted_unit.z >= 0 && adjusted_unit.z < UT_Z_NUM) {
                    if (is_need2escape_unit(block.x, block.z, adjusted_unit.x, adjusted_unit.z) == FALSE) {
                        set_escape_unit(escape_pos, block.x, block.z, adjusted_unit.x, adjusted_unit.z);
                        return TRUE;
                    }

                    adjusted_unit.x = unit.x - i;
                    if (adjusted_unit.x >= 0 && adjusted_unit.x < UT_X_NUM) {
                        if (is_need2escape_unit(block.x, block.z, adjusted_unit.x, adjusted_unit.z) == FALSE) {
                            set_escape_unit(escape_pos, block.x, block.z, adjusted_unit.x, adjusted_unit.z);
                            return TRUE;
                        }
                    }
                }
            }
        }
    }

    if (mNpcW_GetNearGate(&adjusted_unit.x, &adjusted_unit.z, block.x, block.z, unit.x, unit.z)) {
        set_escape_unit(escape_pos, block.x, block.z, adjusted_unit.x, adjusted_unit.z);
        return TRUE;
    }

    return -1;
}

static int title_fade(EVENT_MANAGER_ACTOR* evmgr, int type, int title_type, u32 blockkind) {
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    ACTOR* playerx = GET_PLAYER_ACTOR_NOW_ACTOR();
    Door_data_c door_data;
    s16 angle_y = playerx->world.angle.y;
    s_xyz pos_s;
    u8 exit_drt;

    if (mDemo_CheckDemo4Event() ||
        mEv_PlayerOK() == FALSE ||
        Common_Get(reset_flag) ||
        mEv_LiveSonchoPresent() ||
        (Common_Get(my_room_message_control_flags) & 0x4)
    ) {
        return FALSE;
    }

    door_data.next_scene_id = SCENE_FG;
    door_data.exit_orientation = mSc_DIRECT_SOUTH;
    door_data.exit_type = 0;
    door_data.extra_data = 4;

    if (type == mEv_EVENT_GROUNDHOG_DAY) {
        int bx;
        int bz;

        if (
            CLIP(groundhog_control_clip) != NULL &&
            CLIP(groundhog_control_clip)->fading_title == TRUE &&
            mFI_BlockKind2BkNum(&bx, &bz, mRF_BLOCKKIND_SHRINE) == TRUE
        ) {
            f32 x;
            f32 z;

            mFI_BkNum2WposXZ(&x, &z, bx, bz);
            x += mFI_BK_WORLDSIZE_HALF_X_F;
            z += mFI_BK_WORLDSIZE_HALF_Z_F + mFI_UT_WORLDSIZE_Z_F * 2;

            door_data.exit_position.x = x;
            door_data.exit_position.y = 0;
            door_data.exit_position.z = z;
            Common_Get(start_demo_request).type = mDemo_TYPE_EVENTMSG2;
            if (play->block_table.block_x == bx && play->block_table.block_z == bz) {
                door_data.exit_position.z += mFI_UT_WORLDSIZE_Z_F * 3;
                door_data.exit_orientation = mSc_DIRECT_NORTH;
                door_data.extra_data = 5;
            }
        } else {
            aGHC_save_c* gh_save = (aGHC_save_c*)mEv_get_common_area(mEv_EVENT_GROUNDHOG_DAY, 0);

            if (gh_save != NULL) {
                gh_save->_00 = 0;
            }

            door_data.exit_position.x = (int)mFI_BK_UT_2_POS(3, 10); // Acre 3, unit 10
            door_data.exit_position.y = 5 * mFI_UNIT_BASE_SIZE;
            door_data.exit_position.z = (int)mFI_BK_UT_2_POS(1, 5) + 10; // Acre 1, unit 5
            Common_Get(start_demo_request).type = mDemo_TYPE_EVENTMSG;
        }
    } else {
        door_data.exit_position.x = (int)mFI_BK_UT_2_POS(3, 10); // Acre 3, unit 10
        door_data.exit_position.y = 5 * mFI_UNIT_BASE_SIZE;
        door_data.exit_position.z = (int)mFI_BK_UT_2_POS(1, 5) + 10; // Acre 1, unit 5
        Common_Get(start_demo_request).type = mDemo_TYPE_EVENTMSG;
    }

    door_data.door_actor_name = EMPTY_NO;
    door_data.wipe_type = WIPE_TYPE_EVENT;
    exit_drt = Common_Get(door_data).exit_orientation;
    pos_s.x = Common_Get(door_data).exit_position.x;
    pos_s.y = Common_Get(door_data).exit_position.y;
    pos_s.z = Common_Get(door_data).exit_position.z;

    if (goto_other_scene(play, &door_data, 0) == TRUE) {
        mFI_SetClimate(mFI_CLIMATE_NUM);
        evmgr->skip_event_at_wade = TRUE;
        Common_Get(event_door_data).exit_type = 0;
        Common_Get(event_door_data).next_scene_id = Save_Get(scene_no);
        Common_Get(event_door_data).extra_data = 0;

        if (mPlib_Check_CorrectPlayerPos_forEvent() == FALSE) {
            exit_drt = ((angle_y + 0x1000 - 1) >> 13) & 7;
            player_lap_check(evmgr, &pos_s, &playerx->world.position, blockkind, type);
        }

        Common_Get(event_door_data).exit_orientation = exit_drt;
        Common_Get(event_door_data).exit_position.x = pos_s.x;
        Common_Get(event_door_data).exit_position.y = pos_s.y;
        Common_Get(event_door_data).exit_position.z = pos_s.z;
        Common_Get(event_door_data).door_actor_name = RSV_NO;
        Common_Get(event_door_data).wipe_type = WIPE_TYPE_EVENT;
        Common_Set(event_id, type);
        Common_Set(event_title_flags, title_type);
        Common_Set(event_title_fade_in_progress, 0);
        play->fb_wipe_type = WIPE_TYPE_EVENT;
        play->fb_fade_type = FADE_TYPE_EVENT;
        Common_Get(transition).wipe_type = WIPE_TYPE_EVENT;
        aMR_SaveWaltzTempo2();
        mPlib_request_player_warp_forEvent();
        mBGMForce_inform_start();
        return TRUE;
    }

    return FALSE;
}

static int wait_culling(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    if (mEv_check_status(ctrl->type, mEv_STATUS_STOP)) {
        return TRUE;
    }

    return FALSE;
}

static int artist_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    }

    if (ret != 0) {
        spppp = make_actor_in_free_block(evmgr, ctrl, SP_NPC_ARTIST, 0x51, 1);
        mEv_EventON(mEv_SPNPC_ARTIST);
    }

    return ret;
}

static int artist_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }
    
    spppp = NULL;
    mEv_EventOFF(mEv_SPNPC_ARTIST);
    mEv_make_new_special_event();

    return ret;
}

static int artist_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade(evmgr, ctrl, 0x51);
    
    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    return place_res != 0;
}

static int artist_behind(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    if (mEv_check_status(ctrl->type, mEv_STATUS_TALK) && walk_actor_at_wade(evmgr, ctrl, 0x51) != 0) {
        mEv_clear_status(ctrl->type, mEv_STATUS_TALK);
        return TRUE;
    }

    return FALSE;
}

static int broker_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;
    BlockOrUnit_c unit;
    mEv_place_data_c* place_data = make_FG_somewhere_lot4sale(evmgr, ctrl, BROKER_TENT, 0x51);

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    }

    if (ret != 0) {
        if (place_data != NULL) {
            spppp = place_data;
            unit.x = place_data->unit.x;
            unit.z = place_data->unit.z + 2;
            make_actor_in_fixed_block_checkless(evmgr, ctrl, &place_data->block, &unit, SP_NPC_BROKER, 1);
        }
        mEv_EventON(mEv_SPNPC_BROKER);
    }

    return ret;
}

static int broker_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    spppp = NULL;
    mEv_EventOFF(mEv_SPNPC_BROKER);
    mEv_make_new_special_event();
    delete_FG(ctrl, 0x51);

    return ret;
}

static int broker_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade_checkless(evmgr, ctrl, 1);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    return place_res != 0;
}

static int prebroker_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    return 1;
}

static int designer_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;
    BlockOrUnit_c unit;
    mEv_place_data_c* place_data = make_FG_somewhere_lot4sale(evmgr, ctrl, DESIGNER_CAR, 0x51);

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    }

    if (ret != 0) {
        if (place_data != NULL) {
            spppp = place_data;
            unit.x = place_data->unit.x;
            unit.z = place_data->unit.z + 2;
            make_actor_in_fixed_block(evmgr, ctrl, &place_data->block, &unit, SP_NPC_DESIGNER, 1);
        }
        mEv_EventON(mEv_SPNPC_DESIGNER);
    }

    return ret;
}

static int designer_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    spppp = NULL;
    mEv_EventOFF(mEv_SPNPC_DESIGNER);
    mEv_make_new_special_event();
    delete_FG(ctrl, 0x51);

    return ret;
}

static int designer_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade(evmgr, ctrl, 1);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    return place_res != 0;
}

static int designer_behind(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_data;
    BlockOrUnit_c unit;

    if (mEv_check_status(ctrl->type, mEv_STATUS_TALK)) {
        place_data = walk_FG_somewhere_lot4sale(evmgr, ctrl, 0x51);
        if (place_data != 0) {
            unit.x = place_data->unit.x;
            unit.z = place_data->unit.z + 2;
            mEv_clear_common_place(ctrl->type, 1);
            make_actor_in_fixed_block(evmgr, ctrl, &place_data->block, &unit, SP_NPC_DESIGNER, 1);
            mEv_clear_status(ctrl->type, mEv_STATUS_TALK);
            return TRUE;
        }
    }

    return TRUE;
}

static int arabian_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;
    BlockOrUnit_c unit;

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    }

    if (ret != 0) {
        spppp = make_actor_in_free_block(evmgr, ctrl, SP_NPC_CARPETPEDDLER, 0x51, 1);
        mEv_EventON(mEv_SPNPC_ARABIAN);
    }

    return ret;
}

static int arabian_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    spppp = NULL;
    mEv_EventOFF(mEv_SPNPC_ARABIAN);
    mEv_make_new_special_event();

    return ret;
}

static int arabian_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade(evmgr, ctrl, 0x51);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    return place_res != 0;
}

static int arabian_behind(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    if (mEv_check_status(ctrl->type, mEv_STATUS_TALK) && walk_actor_at_wade(evmgr, ctrl, 0x51) != 0) {
        mEv_clear_status(ctrl->type, mEv_STATUS_TALK);
        return TRUE;
    }

    return FALSE;
}

static int gypsy_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret;

    spppp = make_FG_somewhere_lot4sale(evmgr, ctrl, FORTUNE_TENT, 0x51);
    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    } else {
        ret = 2;
    }

    mEv_EventON(mEv_SPNPC_GYPSY);
    return ret;
}

static int gypsy_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    mEv_EventOFF(mEv_SPNPC_GYPSY);
    mEv_make_new_special_event();
    delete_FG(ctrl, 0x51);
    spppp = NULL;

    return ret;
}

static int gypsy_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    return 1;
}

static int gypsy_out(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    return 1;
}

static int prebargain_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    return 1;
}

static int bargain_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret;

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    } else {
        ret = 2;
    }

    mEv_EventON(mEv_SPNPC_SHOP);
    return ret;
}

static int bargain_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    mEv_EventOFF(mEv_SPNPC_SHOP);
    mEv_make_new_special_event();

    return ret;
}

static int bargain_out(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    return 1;
}

static int staffroll_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;
    static BlockOrUnit_c b = { 1, 3 }; // A-3
    static BlockOrUnit_c u = { 7, 7 }; // middle of acre

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    }

    if (ret != 0) {
        wpppp = make_actor_in_fixed_block_checkless(evmgr, ctrl, &b, &u, SP_NPC_TOTAKEKE, 0x51);
    }

    return ret;
}

static int staffroll_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    wpppp = NULL;
    return ret;
}

static int staffroll_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res;

    if (Common_Get(event_title_flags) != 0) {
        return 3;
    }

    place_res = show_actor_at_wade_checkless(evmgr, ctrl, 0x51);
    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    return place_res != 0;
}

static int turnipbuyer_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    }

    if (ret != 0 && mAGrw_CheckKabuPeddler()) {
        wpppp = make_actor_in_free_block(evmgr, ctrl, SP_NPC_KABUPEDDLER, 0x51, 1);
    }

    return ret;
}

static int turnipbuyer_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    wpppp = NULL;
    return ret;
}

static int turnipbuyer_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade(evmgr, ctrl, 0x51);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    return place_res != 0;
}

static int turnipbuyer_behind(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    if (mEv_check_status(ctrl->type, mEv_STATUS_TALK) && walk_actor_at_wade(evmgr, ctrl, 0x51) != 0) {
        mEv_clear_status(ctrl->type, mEv_STATUS_TALK);
        return TRUE;
    }

    return FALSE;
}

static int downing_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    }

    if (ret != 0) {
        wpppp = make_actor_in_seaside_block(evmgr, ctrl, SP_NPC_EV_DOZAEMON, 0x51);
    }

    return ret;
}

static int downing_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    wpppp = NULL;
    return ret;
}

static int downing_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade_checkless(evmgr, ctrl, 0x51);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    return place_res != 0;
}

static int aprilfool_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (evmgr->shrine_block_exists == FALSE) {
        mEv_clear_status(ctrl->type, mEv_STATUS_ACTIVE);
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return 0;
    }

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    }

    make_control_actor(mAc_PROFILE_APRILFOOL_CONTROL);
    return ret;
}

static int aprilfool_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    return ret;
}

static int christmas_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) == FALSE) {
        if (title_fade(evmgr, ctrl->type, 1, mRF_BLOCKKIND_POOL)) {
            mEv_set_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        dpppp = make_actor_in_free_block(evmgr, ctrl, SP_NPC_SANTA, 0x51, 1);
    }

    return ret;
}

static int christmas_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    dpppp = NULL;
    if (mEv_check_keep(ctrl->type) != FALSE) {
        if (title_fade(evmgr, ctrl->type, 9, mRF_BLOCKKIND_NONE)) {
            mEv_clear_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    return ret;
}

static int christmas_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade(evmgr, ctrl, 0x51);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    return place_res != 0;
}

static int christmas_behind(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    if (mEv_check_status(ctrl->type, mEv_STATUS_TALK) && walk_actor_at_wade(evmgr, ctrl, 0x51) != 0) {
        mEv_clear_status(ctrl->type, mEv_STATUS_TALK);
        return TRUE;
    }

    return FALSE;
}

static int halloween_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) == FALSE) {
        if (title_fade(evmgr, ctrl->type, 1, mRF_BLOCKKIND_POOL)) {
            mEv_set_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        dpppp = make_actor_in_free_block(evmgr, ctrl, SP_NPC_HALLOWEEN, 0x51, 1);
    }

    return ret;
}

static int halloween_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        if (title_fade(evmgr, ctrl->type, 9, mRF_BLOCKKIND_NONE)) {
            mEv_clear_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    dpppp = NULL;
    return ret;
}

static int halloween_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade(evmgr, ctrl, 0x51);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    return place_res != 0;
}

static int halloween_behind(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    if (mEv_check_status(ctrl->type, mEv_STATUS_TALK) && walk_actor_at_wade(evmgr, ctrl, 0x51) != 0) {
        mEv_clear_status(ctrl->type, mEv_STATUS_TALK);
        return TRUE;
    }

    return FALSE;
}

static int anglingtournament_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (evmgr->pool_block_exists == FALSE) {
        mEv_clear_status(ctrl->type, mEv_STATUS_ACTIVE);
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return 0;
    }

    if (mEv_check_keep(ctrl->type) == FALSE) {
        if (title_fade(evmgr, ctrl->type, 1, mRF_BLOCKKIND_POOL)) {
            mEv_set_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        clean_FG(evmgr, mRF_BLOCKKIND_POOL);
        make_FG_in_reserved_block(evmgr, ctrl, 6, mRF_BLOCKKIND_POOL, 6);
        make_actor_in_reserved_block(evmgr, ctrl, 5, mRF_BLOCKKIND_POOL, 5);
    }

    return ret;
}

static int anglingtournament_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        if (title_fade(evmgr, ctrl->type, 9, mRF_BLOCKKIND_NONE)) {
            mEv_clear_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        delete_FG(ctrl, 6);
    }

    return ret;
}

static int anglingtournament_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade(evmgr, ctrl, 5);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    return place_res != 0;
}

static int countdown_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (evmgr->pool_block_exists == FALSE) {
        mEv_clear_status(ctrl->type, mEv_STATUS_ACTIVE);
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return 0;
    }

    if (mEv_check_keep(ctrl->type) == FALSE) {
        if (title_fade(evmgr, ctrl->type, 1, mRF_BLOCKKIND_POOL)) {
            mEv_set_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        clean_FG(evmgr, mRF_BLOCKKIND_POOL);
        make_FG_in_reserved_block(evmgr, ctrl, 5, mRF_BLOCKKIND_POOL, 5);
        make_FG_in_reserved_block(evmgr, ctrl, 6, mRF_BLOCKKIND_POOL, 6);
        make_actor_in_reserved_block(evmgr, ctrl, 7, mRF_BLOCKKIND_POOL, 7);
    }

    return ret;
}

static int countdown_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        if (title_fade(evmgr, ctrl->type, 9, mRF_BLOCKKIND_NONE)) {
            mEv_clear_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        delete_FG(ctrl, 5);
        delete_FG(ctrl, 6);
    }

    return ret;
}

static int countdown_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade_checkfgcol(evmgr, ctrl, 7);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    return place_res != 0;
}

static int firework_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (evmgr->pool_block_exists == FALSE) {
        mEv_clear_status(ctrl->type, mEv_STATUS_ACTIVE);
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return 0;
    }

    if (mEv_check_keep(ctrl->type) == FALSE) {
        if (title_fade(evmgr, ctrl->type, 1, mRF_BLOCKKIND_POOL)) {
            mEv_set_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        clean_FG(evmgr, mRF_BLOCKKIND_POOL);
        make_FG_in_reserved_block(evmgr, ctrl, 6, mRF_BLOCKKIND_POOL, 6);
        make_actor_in_reserved_block(evmgr, ctrl, 5, mRF_BLOCKKIND_POOL, 5);
        make_effect(eEC_EFFECT_HANABI_SWITCH);
    }

    return ret;
}

static int firework_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        if (title_fade(evmgr, ctrl->type, 9, mRF_BLOCKKIND_NONE)) {
            mEv_clear_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        delete_FG(ctrl, 6);
        delete_effect(eEC_EFFECT_HANABI_SWITCH);
    }

    return ret;
}

static int firework_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade_checkless(evmgr, ctrl, 5);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    return place_res != 0;
}

static int flowerviewing_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (evmgr->shrine_block_exists == FALSE) {
        mEv_clear_status(ctrl->type, mEv_STATUS_ACTIVE);
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return 0;
    }

    if (mEv_check_keep(ctrl->type) == FALSE) {
        if (title_fade(evmgr, ctrl->type, 1, mRF_BLOCKKIND_SHRINE)) {
            mEv_set_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        clean_FG(evmgr, mRF_BLOCKKIND_SHRINE);
        make_FG_in_reserved_block(evmgr, ctrl, 5, mRF_BLOCKKIND_SHRINE, 0x6E);
        make_FG_in_reserved_block(evmgr, ctrl, 6, mRF_BLOCKKIND_SHRINE, 0x6F);
        make_actor_in_reserved_block(evmgr, ctrl, 7, mRF_BLOCKKIND_SHRINE, 7);
    }

    return ret;
}

static int flowerviewing_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        if (title_fade(evmgr, ctrl->type, 9, mRF_BLOCKKIND_NONE)) {
            mEv_clear_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        delete_FG(ctrl, 0x6E);
        delete_FG(ctrl, 0x6F);
    }

    return ret;
}

static int flowerviewing_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade_checkless(evmgr, ctrl, 7);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    return place_res != 0;
}

static int radiogymnastic_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (evmgr->shrine_block_exists == FALSE) {
        mEv_clear_status(ctrl->type, mEv_STATUS_ACTIVE);
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return 0;
    }

    if (mEv_check_keep(ctrl->type) == FALSE) {
        if (title_fade(evmgr, ctrl->type, 1, mRF_BLOCKKIND_SHRINE)) {
            mEv_set_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        clean_FG(evmgr, mRF_BLOCKKIND_SHRINE);
        make_FG_in_reserved_block(evmgr, ctrl, 5, mRF_BLOCKKIND_SHRINE, 5);
        make_actor_in_reserved_block(evmgr, ctrl, 4, mRF_BLOCKKIND_SHRINE, 4);
        make_actor_in_reserved_block(evmgr, ctrl, 6, mRF_BLOCKKIND_SHRINE, 6);
    }

    return ret;
}

static int radiogymnastic_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        if (title_fade(evmgr, ctrl->type, 9, mRF_BLOCKKIND_NONE)) {
            mEv_clear_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        delete_FG(ctrl, 5);
    }

    return ret;
}

static int radiogymnastic_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade_checkless(evmgr, ctrl, 4);
    mEv_place_data_c* place_res2 = show_actor_at_wade_checkless(evmgr, ctrl, 6);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN || place_res2 == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    if (place_res != 0 && place_res2 != 0) {
        return 1;
    }

    return 0;
}

static void field_day_ct(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    switch (ctrl->type) {
        case mEv_EVENT_SPORTS_FAIR_AEROBICS:
            make_FG_in_reserved_block(evmgr, ctrl, 5, mRF_BLOCKKIND_SHRINE, 5);
            make_actor_in_reserved_block(evmgr, ctrl, 4, mRF_BLOCKKIND_SHRINE, 4);
            make_actor_in_reserved_block(evmgr, ctrl, 6, mRF_BLOCKKIND_SHRINE, 6);
            break;
        case mEv_EVENT_SPORTS_FAIR_FOOT_RACE:
            make_actor_in_reserved_block(evmgr, ctrl, 5, mRF_BLOCKKIND_SHRINE, 5);
            break;
        case mEv_EVENT_SPORTS_FAIR_BALL_TOSS:
            make_FG_in_reserved_block(evmgr, ctrl, 5, mRF_BLOCKKIND_SHRINE, 5);
            make_FG_in_reserved_block(evmgr, ctrl, 6, mRF_BLOCKKIND_SHRINE, 6);
            make_FG_in_reserved_block(evmgr, ctrl, 7, mRF_BLOCKKIND_SHRINE, 7);
            make_FG_in_reserved_block(evmgr, ctrl, 8, mRF_BLOCKKIND_SHRINE, 8);
            make_actor_in_reserved_block(evmgr, ctrl, 9, mRF_BLOCKKIND_SHRINE, 9);
            break;
        case mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR:
            make_actor_in_reserved_block(evmgr, ctrl, 5, mRF_BLOCKKIND_SHRINE, 5);
            break;
    }

    Common_Get(event_common).fieldday_event_id = ctrl->type;
}

static void field_day_delete(void) {
    int type = Common_Get(event_common).fieldday_event_id;

    switch (type) {
        case mEv_EVENT_SPORTS_FAIR_AEROBICS:
            delete_FG2(type, 5);
            mEv_clear_common_place(type, 4);
            mEv_clear_common_place(type, 6);
            break;
        case mEv_EVENT_SPORTS_FAIR_FOOT_RACE:
            mEv_clear_common_place(type, 5);
            break;
        case mEv_EVENT_SPORTS_FAIR_BALL_TOSS:
            delete_FG2(type, 6);
            delete_FG2(type, 5);
            delete_FG2(type, 8);
            delete_FG2(type, 7);
            mEv_clear_common_place(type, 9);
            break;
        case mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR:
            mEv_clear_common_place(type, 5);
            break;
    }

    Common_Get(event_common).fieldday_event_id = -1;
}

static int fdgymnastic_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (evmgr->shrine_block_exists == FALSE) {
        mEv_clear_status(ctrl->type, mEv_STATUS_ACTIVE);
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return 0;
    }

    if (mEv_check_keep(ctrl->type) == FALSE) {
        if (title_fade(evmgr, ctrl->type, 1, mRF_BLOCKKIND_SHRINE)) {
            mEv_set_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        clean_FG(evmgr, mRF_BLOCKKIND_SHRINE);
        field_day_ct(evmgr, ctrl);
    }

    return ret;
}

static int fdgymnastic_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    return ret;
}

static int fdgymnastic_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade_checkless(evmgr, ctrl, 4);
    mEv_place_data_c* place_res2 = show_actor_at_wade_checkless(evmgr, ctrl, 6);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN || place_res2 == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    if (place_res != 0 && place_res2 != 0) {
        return 1;
    }

    return 0;
}

static int fdrace_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (evmgr->shrine_block_exists == FALSE) {
        mEv_clear_status(ctrl->type, mEv_STATUS_ACTIVE);
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return 0;
    }

    if (mEv_check_keep(ctrl->type) == FALSE) {
        if (title_fade(evmgr, ctrl->type, 1, mRF_BLOCKKIND_SHRINE)) {
            field_day_delete();
            mEv_set_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        make_control_actor_without_indoor(mAc_PROFILE_TOKYOSO_CONTROL);
        field_day_ct(evmgr, ctrl);
    }

    return ret;
}

static int fdrace_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    return ret;
}

static int fdrace_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade_checkless(evmgr, ctrl, 5);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    return place_res != 0;
}

static int fdbasket_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (evmgr->shrine_block_exists == FALSE) {
        mEv_clear_status(ctrl->type, mEv_STATUS_ACTIVE);
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return 0;
    }

    if (mEv_check_keep(ctrl->type) == FALSE) {
        if (title_fade(evmgr, ctrl->type, 1, mRF_BLOCKKIND_SHRINE)) {
            field_day_delete();
            mEv_set_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        clean_FG(evmgr, mRF_BLOCKKIND_SHRINE);
        field_day_ct(evmgr, ctrl);
    }

    return ret;
}

static int fdbasket_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    return ret;
}

static int fdbasket_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade_checkless(evmgr, ctrl, 9);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    if (place_res != 0) {
        return 1;
    }

    return 0;
}

static int fdtug_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (evmgr->shrine_block_exists == FALSE) {
        mEv_clear_status(ctrl->type, mEv_STATUS_ACTIVE);
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return 0;
    }

    if (mEv_check_keep(ctrl->type) == FALSE) {
        if (title_fade(evmgr, ctrl->type, 1, mRF_BLOCKKIND_SHRINE)) {
            field_day_delete();
            mEv_set_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        make_control_actor_without_indoor(mAc_PROFILE_TUNAHIKI_CONTROL);
        field_day_ct(evmgr, ctrl);
    }

    return ret;
}

static int fdtug_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        if (Common_Get(event_common).fieldday_event_over_status != -1) {
            mEv_clear_keep(ctrl->type);
            ret = 1;
        } else {
            if (title_fade(evmgr, ctrl->type, 9, mRF_BLOCKKIND_NONE)) {
                field_day_delete();
                mEv_clear_keep(ctrl->type);
                ret = 1;
            } else {
                ret = 0;
            }
        }
    }

    return ret;
}

static int fdtug_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade_checkless(evmgr, ctrl, 5);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    return place_res != 0;
}

static int fdwp_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (evmgr->shrine_block_exists == FALSE) {
        mEv_clear_status(ctrl->type, mEv_STATUS_ACTIVE);
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return 0;
    }

    if (mEv_check_keep(ctrl->type) == FALSE) {
        if (title_fade(evmgr, ctrl->type, 1, mRF_BLOCKKIND_SHRINE)) {
            mEv_set_keep(ctrl->type);
            ret = 1;
            field_day_delete();
            field_day_ct(evmgr, ctrl);
            mPlib_Set_unable_wade(TRUE);
        } else {
            ret = 0;
        }
    }

    return ret;
}

static int fdwp_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
        mPlib_Set_unable_wade(FALSE);
    }

    return ret;
}

static int harvestmoon_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (evmgr->pool_block_exists == FALSE) {
        mEv_clear_status(ctrl->type, mEv_STATUS_ACTIVE);
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return 0;
    }

    if (mEv_check_keep(ctrl->type) == FALSE) {
        if (title_fade(evmgr, ctrl->type, 1, mRF_BLOCKKIND_POOL)) {
            mEv_set_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        clean_FG(evmgr, mRF_BLOCKKIND_POOL);
        make_effect(eEC_EFFECT_NIGHT13_MOON);
        make_actor_in_reserved_block(evmgr, ctrl, 4, mRF_BLOCKKIND_POOL, 4);
    }

    return ret;
}

static int harvestmoon_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        if (title_fade(evmgr, ctrl->type, 9, mRF_BLOCKKIND_NONE)) {
            mEv_clear_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        delete_effect(eEC_EFFECT_NIGHT13_MOON);
    }

    return ret;
}

static int harvestmoon_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade_checkfgcol(evmgr, ctrl, 4);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    if (place_res != 0) {
        return 1;
    }

    return 0;
}

static int meteor_shower_viewing_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (evmgr->pool_block_exists == FALSE) {
        mEv_clear_status(ctrl->type, mEv_STATUS_ACTIVE);
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return 0;
    }

    if (mEv_check_keep(ctrl->type) == FALSE) {
        if (title_fade(evmgr, ctrl->type, 1, mRF_BLOCKKIND_POOL)) {
            mEv_set_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        clean_FG(evmgr, mRF_BLOCKKIND_POOL);
        make_effect(eEC_EFFECT_SHOOTING_SET);
        make_actor_in_reserved_block(evmgr, ctrl, 4, mRF_BLOCKKIND_POOL, 4);
    }

    return ret;
}

static int meteor_shower_viewing_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        if (title_fade(evmgr, ctrl->type, 9, mRF_BLOCKKIND_NONE)) {
            mEv_clear_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        delete_effect(eEC_EFFECT_SHOOTING);
    }

    return ret;
}

static int meteor_shower_viewing_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade_checkfgcol(evmgr, ctrl, 4);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    if (place_res != 0) {
        return 1;
    }

    return 0;
}

static int snowman_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mActor_name_t items[] = { SNOWMAN0, SNOWMAN3, SNOWMAN6 };

    if (mFI_CheckFGExist(items, ARRAY_COUNT(items)) == FALSE && mEv_snowman_born_check()) {
        make_move_actor_in_free_block(evmgr, ctrl, ETC_SNOWMAN_BALL_A, 0x64);
        make_move_actor_in_free_block(evmgr, ctrl, ETC_SNOWMAN_BALL_B, 0x65);
    }

    return 1;
}

static int kamakura_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret;

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    } else {
        ret = 2;
    }

    if (ret != 0) {
        make_FG_somewhere_lot4sale(evmgr, ctrl, KAMAKURA, 0x51);
    }

    return ret;
}

static int kamakura_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    delete_FG(ctrl, 0x51);
    return ret;
}

static int kamakura_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    return 1;
}

static int kamakura_out(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    return 1;
}

static int newyear_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (evmgr->shrine_block_exists == FALSE) {
        mEv_clear_status(ctrl->type, mEv_STATUS_ACTIVE);
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return 0;
    }

    if (mEv_check_keep(ctrl->type) == FALSE) {
        if (title_fade(evmgr, ctrl->type, 1, mRF_BLOCKKIND_SHRINE)) {
            mEv_set_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        clean_FG(evmgr, mRF_BLOCKKIND_SHRINE);
        make_FG_in_reserved_block(evmgr, ctrl, 6, mRF_BLOCKKIND_SHRINE, 6);
        make_control_actor_without_indoor(mAc_PROFILE_HATUMODE_CONTROL);
        make_actor_in_reserved_block(evmgr, ctrl, 5, mRF_BLOCKKIND_SHRINE, 5);
        make_actor_in_reserved_block(evmgr, ctrl, 7, mRF_BLOCKKIND_SHRINE, 7);
    }

    return ret;
}

static int newyear_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        if (title_fade(evmgr, ctrl->type, 9, mRF_BLOCKKIND_NONE)) {
            mEv_clear_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        delete_FG(ctrl, 6);
    }

    return ret;
}

static int newyear_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade_checkless(evmgr, ctrl, 5);
    mEv_place_data_c* place_res2 = show_actor_at_wade_checkless(evmgr, ctrl, 7);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN || place_res2 == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    if (place_res != 0 && place_res2 != 0) {
        return 1;
    }

    return 0;
}

static int ghost_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;
    int i;
    int j;
    int bx;
    int bz;
    mEv_gst_c* gst = (mEv_gst_c*)mEv_get_save_area(mEv_EVENT_GHOST, 0x36);
    mEv_gst_common_c* gst_common = (mEv_gst_common_c*)mEv_get_common_area(mEv_EVENT_GHOST, 0x37);
    int player_no = Common_Get(player_no);
    lbRTC_time_c* now = Common_GetPointer(time.rtc_time);

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    }

    if (gst != NULL && (gst->flags & mEv_GHOST_FLAG_RETURNED_SPIRITS) != 0) {
        ret = 2;
    } else if (ret != 0) {
        wpppp = make_actor_in_free_block(evmgr, ctrl, SP_NPC_EV_GHOST, 0x51, 5);

        if (gst_common == NULL) {
            gst_common = (mEv_gst_common_c*)mEv_reserve_common_area(mEv_EVENT_GHOST, 0x37);
        }

        if (gst_common != NULL) {
            if (gst != NULL) {
                if (
                    (gst->flags & (u16)(1 << player_no)) != 0 &&
                    now->year == gst->renew_time.year &&
                    now->month == gst->renew_time.month &&
                    now->day == gst->renew_time.day
                ) {
                    gst_common->flags |= mEv_GHOST_FLAG_ACTIVE;
                }
            }

            if ((gst_common->flags & mEv_GHOST_COMMON_SPAWNED_SPIRITS) == 0) {
                i = 0;
                while (i < SPIRIT_NUM) {
                    bx = 1 + RANDOM(5);
                    bz = 2 + RANDOM(4);
                    j = 0;

                    while (j < i && (gst_common->hitodama_block_data.block_x[j] != bx || gst_common->hitodama_block_data.block_z[j] != bz)) {
                        j++;
                    }

                    // the inner loop finished without a break so chosen block has no spirits in it
                    if (j == i) {
                        gst_common->hitodama_block_data.block_x[i] = bx;
                        gst_common->hitodama_block_data.block_z[i] = bz;
                        i++;
                    }
                }

                gst_common->flags |= mEv_GHOST_COMMON_SPAWNED_SPIRITS;
            }
        }
    }

    return ret;
}

static void ghost_delete_hitodama(void) {
    int i;
    Private_c* priv = Now_Private;

    for (i = 0; i < SPIRIT_NUM; i++) {
        int idx = mPr_GetPossessionItemIdxWithCond(priv, ITM_SPIRIT0 + i, mPr_ITEM_COND_NORMAL);

        while (idx != -1) {
            mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
            idx = mPr_GetPossessionItemIdxWithCond(priv, ITM_SPIRIT0 + i, mPr_ITEM_COND_NORMAL);
        }
    }
}

static int ghost_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;
    
    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
        ghost_delete_hitodama();
    }

    wpppp = NULL;
    return ret;
}

static int ghost_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade_checkfgcol(evmgr, ctrl, 0x51);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    if (place_res != 0) {
        return 1;
    }

    return 0;
}

static int river_start_block(int* bx, int* bz) {
    u32* block_kind_p = (u32*)g_block_kind_p;

    // start at A-1
    *bz = 1;
    *bx = 1;

    // work way through A-5 searching for the first river block
    while (*bx < 6) {
        if ((*(block_kind_p + *bx + ((*bz) * BLOCK_X_NUM)) & mRF_BLOCKKIND_RIVER) == mRF_BLOCKKIND_RIVER) {
            return TRUE;
        }

        (*bx)++;
    }

    return FALSE;
}

static void river_stream(u8* blocks, int count) {
    int river_bx;
    int river_bz;
    int i;
    int j;

    // zero out block data
    j = 0;
    for (i = 0; i < count; i++) {
        blocks[j + 0] = 0;
        blocks[j + 1] = 0;
        j += 2;
    }

    // find the start block
    if (river_start_block(&river_bx, &river_bz)) {
        // trace the river
        for (i = 1; i < count && river_bz < 7; i++) {
            blocks[(i - 1) * 2 + 0] = river_bx;
            blocks[(i - 1) * 2 + 1] = river_bz;

            switch ((u8)mRF_BlockType2RiverNextDirect(mFI_BkNum2BlockType(river_bx, river_bz))) {
                case mRF_DIRECT_WEST:
                    river_bx--;
                    break;
                case mRF_DIRECT_EAST:
                    river_bx++;
                    break;
                case mRF_DIRECT_SOUTH:
                    river_bz++;
                    break;
                default:
                    return;
            }
        }
    }
}

static int bridge_stand_river(u8* blocks, int count) {
    int location_count = 0;
    int i;
    int bx;
    int bz;
    int ux;
    int uz;

    // Remove any acres without a bridge building spot
    for (i = 0; i < count && blocks[i * 2 + 0] != 0; i++) {
        bx = blocks[i * 2 + 0];
        bz = blocks[i * 2 + 1];

        if (mFI_SearchFGInBlock(&ux, &uz, RSV_BRIDGE0, bx, bz) || mFI_SearchFGInBlock(&ux, &uz, RSV_BRIDGE1, bx, bz)) {
            blocks[location_count * 2 + 0] = bx;
            blocks[location_count * 2 + 1] = bz;
            location_count++;
        }
    }

    return location_count;
}

static int bridge_man_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    u8 bridge_blocks[30 * 2];
    int ret = 2;
    int spots;
    int remain;

    if (mFI_GET_TYPE(mFI_GetFieldId()) != mFI_FIELDTYPE2_FG) {
        return 0;
    }

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    }

    if (ret != 0) {
        river_stream(bridge_blocks, 30);
        spots = bridge_stand_river(bridge_blocks, 30);
        if (spots == 0) {
            return 1;
        } else {
            int used = Save_Get(event_save_common).bridge_flags.locations_used;

            if (used >= spots) {
                used = 0;
                Save_Get(event_save_common).bridge_flags.raw = 0;
            }

            remain = (spots - 1) - used;
            if (remain == 0) {
                Save_Get(event_save_common).bridge_flags.raw |= (1 << 7);
            } else {
                Save_Get(event_save_common).bridge_flags.raw &= ~(1 << 7);
            }

            wpppp = make_actor_in_select_block(evmgr, ctrl, SP_NPC_EV_SONCHO, 0x51, bridge_blocks[remain * 2 + 0], bridge_blocks[remain * 2 + 1], 2);
        }
    }

    return ret;
}

static int bridge_man_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    wpppp = NULL;
    return ret;
}

static int bridge_man_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade_checkfgcol(evmgr, ctrl, 0x51);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    if (place_res != 0) {
        return 1;
    }

    return 0;
}

static int bridge_make_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    }

    return ret;
}

static int bridge_make_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    return ret;
}

static int bridge_make_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    lbRTC_time_c now = Common_Get(time.rtc_time);
    int bx;
    int bz;
    int ux;
    int uz;

    if (mEv_bridge_time_check() == -1 || now.hour >= 6) {
        if (Save_Get(bridge).exists == FALSE) {
            bx = Save_Get(bridge).block_x;
            bz = Save_Get(bridge).block_z;

            if (mFI_SearchFGInBlock(&ux, &uz, RSV_BRIDGE0, bx, bz)) {
                mFI_BlockUtNumtoFGSet(BRIDGE_A0, bx, bz, ux, uz);
            } else if (mFI_SearchFGInBlock(&ux, &uz, RSV_BRIDGE1, bx, bz)) {
                mFI_BlockUtNumtoFGSet(BRIDGE_A1, bx, bz, ux, uz);
            }

            Save_Get(bridge).exists = TRUE;
        }

        return 1;
    }

    return 0;
}

static int groundhog_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (evmgr->shrine_block_exists == FALSE) {
        mEv_clear_status(ctrl->type, mEv_STATUS_ACTIVE);
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return 0;
    }

    if (mEv_check_keep(ctrl->type) == FALSE) {
        if (title_fade(evmgr, ctrl->type, 1, mRF_BLOCKKIND_SHRINE)) {
            mEv_set_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        clean_FG(evmgr, mRF_BLOCKKIND_SHRINE);
        make_control_actor_without_indoor(mAc_PROFILE_GROUNDHOG_CONTROL);
        make_FG_in_reserved_block(evmgr, ctrl, 5, mRF_BLOCKKIND_SHRINE, 5);
        make_actor_in_reserved_block(evmgr, ctrl, 4, mRF_BLOCKKIND_SHRINE, 4);
    }

    return ret;
}

static int groundhog_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        if (title_fade(evmgr, ctrl->type, 9, mRF_BLOCKKIND_NONE)) {
            mEv_clear_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        delete_FG(ctrl, 5);
    }

    return ret;
}

static int groundhog_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 0;
    mEv_place_data_c* place_res = show_actor_at_wade_checkless(evmgr, ctrl, 4);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        ret = 2;
    } else if (place_res != 0) {
        ret = 1;
    }

    if (ret != 0) {
        aGHC_save_c* gh_save = (aGHC_save_c*)mEv_get_common_area(mEv_EVENT_GROUNDHOG_DAY, 0);

        if (gh_save != NULL && gh_save->_00 == 1) {
            clean_FG(evmgr, mRF_BLOCKKIND_SHRINE);
            make_control_actor_without_indoor(mAc_PROFILE_GROUNDHOG_CONTROL);
            make_FG_in_reserved_block(evmgr, ctrl, 5, mRF_BLOCKKIND_SHRINE, 5);
        }
    }

    return ret;
}

static int harvestfestival_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (evmgr->shrine_block_exists == FALSE) {
        mEv_clear_status(ctrl->type, mEv_STATUS_ACTIVE);
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return 0;
    }

    if (mEv_check_keep(ctrl->type) == FALSE) {
        if (title_fade(evmgr, ctrl->type, 1, mRF_BLOCKKIND_SHRINE)) {
            mEv_set_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    if (ret != 0) {
        clean_FG(evmgr, mRF_BLOCKKIND_SHRINE);
        make_actor_in_reserved_block(evmgr, ctrl, 5, mRF_BLOCKKIND_SHRINE, 5);
        make_FG_in_reserved_block(evmgr, ctrl, 6, mRF_BLOCKKIND_SHRINE, 6);
        make_FG_in_reserved_block(evmgr, ctrl, 7, mRF_BLOCKKIND_SHRINE, 7);
        make_FG_in_reserved_block(evmgr, ctrl, 8, mRF_BLOCKKIND_SHRINE, 8);
    }

    return ret;
}

static int harvestfestival_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        if (title_fade(evmgr, ctrl->type, 9, mRF_BLOCKKIND_NONE)) {
            mEv_clear_keep(ctrl->type);
            ret = 1;
        } else {
            ret = 0;
        }
    }

    return ret;
}

static int harvestfestival_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade_checkless(evmgr, ctrl, 5);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    if (place_res != 0) {
        return 1;
    }

    return 0;
}

static int harvestfestival_turkey_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (evmgr->shrine_block_exists == FALSE) {
        mEv_clear_status(ctrl->type, mEv_STATUS_ACTIVE);
        mEv_set_status(ctrl->type, mEv_STATUS_ERROR);
        return 0;
    }

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    }

    if (ret != 0) {
        tpppp = make_actor_in_free_block_hide(evmgr, ctrl, SP_NPC_TURKEY, 0x51);
    }

    return ret;
}

static int harvestfestival_turkey_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    tpppp = NULL;
    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    return ret;
}

static int harvestfestival_turkey_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade(evmgr, ctrl, 0x51);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    if (place_res != 0) {
        return 1;
    }

    return 0;
}

static int turkey_behind(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    if (mEv_check_status(ctrl->type, mEv_STATUS_TALK) && walk_actor_at_wade_hide(evmgr, ctrl, 0x51)) {
        mEv_clear_status(ctrl->type, mEv_STATUS_TALK);
        return 1;
    }

    return 0;
}

static int summercamp_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mActor_name_t* summercamper;
    int ret;

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    } else {
        ret = 2;
    }

    if (ret != 0) {
        summercamper = (mActor_name_t*)mEv_get_save_area(mEv_EVENT_SUMMER_CAMPER, 0);
        if (summercamper == NULL) {
            summercamper = (mActor_name_t*)mEv_reserve_save_area(mEv_EVENT_SUMMER_CAMPER, 0);

            if (summercamper != NULL) {
                mNpc_DecideMaskNpc_summercamp(summercamper);
                Common_Set(npc_is_summercamper, FALSE);
            }
        }

        if (summercamper != NULL && ITEM_NAME_GET_TYPE(*summercamper) == NAME_TYPE_NPC && mNpc_GetSameMaskNpc(SP_NPC_EV_SUMMERCAMP_0) == NULL) {
            mNpc_RegistMaskNpc_summercamp(SP_NPC_EV_SUMMERCAMP_0, *summercamper, EMPTY_NO);
        }

        make_FG_somewhere_lot4sale(evmgr, ctrl, TENT, 0x51);
    }

    return ret;
}

static int summercamp_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    delete_FG(ctrl, 0x51);
    return ret;
}

static int summercamp_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    return 1;
}

static int summercamp_out(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    return 1;
}

static int check_masknpc_reregist(mActor_name_t mask_id) {
    mNpc_MaskNpc_c* mask_npc = Common_Get(mask_npc);
    int i;

    for (i = 0; i < mNpc_MASK_NPC_NUM; i++) {
        if (mask_npc->mask_id == mask_id) {
            return TRUE;
        }

        mask_npc++;
    }

    return FALSE;
}

static int regist_mask_gohome(void) {
    if (Save_Get(return_animal).npc_id == EMPTY_NO) {
        return FALSE;
    }

    if (check_masknpc_reregist(SP_NPC_GO_HONE_NPC)) {
        return TRUE;
    }

    mNpc_RegistMaskNpc(SP_NPC_GO_HONE_NPC, Save_Get(return_animal).npc_id, EMPTY_NO);
    return TRUE;
}

static int regist_mask_maskcat(void) {
    if (mMC_check_birth() == FALSE) {
        return FALSE;
    }

    if (check_masknpc_reregist(SP_NPC_MASK_CAT)) {
        return TRUE;
    }

    mNpc_RegistMaskNpc(SP_NPC_MASK_CAT, SP_NPC_MASK_CAT, ITM_CLOTH_START + Save_Get(mask_cat).cloth_no);
    return TRUE;
}

static int gohome_mask_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    Anmret_c* return_animal;
    int ret = 2;

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    }

    Save_Get(return_animal).exist = FALSE;
    return_animal = Save_GetPointer(return_animal);

    // Visiting player cannot trigger this event
    if (Common_Get(player_no) != PLAYER_NUM) {
        if (mMC_check_birth_day()) {
            wpppp = make_actor_in_free_block(evmgr, ctrl, SP_NPC_MASK_CAT, 0x51, 1);
        } else if (mGH_check_birth()) {
            return_animal->exist = TRUE;
            wpppp = make_actor_in_free_block(evmgr, ctrl, SP_NPC_GO_HONE_NPC, 0x51, 1);
        } else if (mMC_check_birth()) {
            wpppp = make_actor_in_free_block(evmgr, ctrl, SP_NPC_MASK_CAT, 0x51, 1);
        }
    }

    return ret;
}

static int gohome_mask_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    wpppp = NULL;
    return ret;
}

static int gohome_mask_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res;
    
    if (Save_Get(return_animal).exist) {
        if (regist_mask_gohome() == FALSE) {
            return 2;
        }
    } else {
        if (regist_mask_maskcat() == FALSE) {
            return 2;
        }
    }

    place_res = show_actor_at_wade_checkfgcol(evmgr, ctrl, 0x51);
    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    if (place_res != 0) {
        return 1;
    }

    return 0;
}

static int gohome_mask_behind(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    if (mEv_check_status(ctrl->type, mEv_STATUS_TALK) && walk_actor_at_wade(evmgr, ctrl, 0x51)) {
        mEv_clear_status(ctrl->type, mEv_STATUS_TALK);
        return 1;
    }

    return 0;
}

static int soncho_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    }

    if (ret != 0) {
        make_actor_in_select_block(evmgr, ctrl, SP_NPC_EV_SONCHO2, 0x51, evmgr->shrine_block.x, evmgr->shrine_block.z, 2);
    }

    return ret;
}

static int soncho_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    return ret;
}

static int soncho_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade_checkfgcol(evmgr, ctrl, 0x51);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    if (place_res != 0) {
        return 1;
    }

    return 0;
}

static int sonchohalloween_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    }

    if (ret != 0) {
        make_actor_in_select_block(evmgr, ctrl, SP_NPC_SONCHO_D079, 0x51, evmgr->shrine_block.x, evmgr->shrine_block.z, 2);
    }

    return ret;
}

static int sonchowandar_start(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) == FALSE) {
        mEv_set_keep(ctrl->type);
        ret = 1;
    }

    if (ret != 0) {
        dpppp = make_actor_in_free_block(evmgr, ctrl, SP_NPC_EV_SONCHO2, 0x51, 1);
    }

    return ret;
}

static int sonchowandar_stop(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 2;

    if (mEv_check_keep(ctrl->type) != FALSE) {
        mEv_clear_keep(ctrl->type);
        ret = 1;
    }

    dpppp = NULL;
    return ret;
}

static int sonchowandar_in(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    mEv_place_data_c* place_res = show_actor_at_wade_checkfgcol(evmgr, ctrl, 0x51);

    if (place_res == aEvMgr_SHOW_ACTOR_RESULT_NOT_SHOWN) {
        return 2;
    }

    if (place_res != 0) {
        return 1;
    }

    return 0;
}

static int event_at_oclock(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = TRUE;

    if (mEv_check_status(ctrl->type, mEv_STATUS_ACTIVE) != FALSE && mEv_check_status(ctrl->type, mEv_STATUS_RUN) == FALSE) {
        if (ctrl->start_proc != NULL && (*ctrl->start_proc)(evmgr, ctrl) == 0) {
            ret = FALSE;
        } else if (mEv_check_status(ctrl->type, mEv_STATUS_ERROR) == FALSE) {
            mEv_set_status(ctrl->type, mEv_STATUS_RUN);
        }
    } else {
        if (mEv_check_status(ctrl->type, mEv_STATUS_ACTIVE) == FALSE && mEv_check_status(ctrl->type, mEv_STATUS_RUN) != FALSE) {
            if (ctrl->stop_proc != NULL && (*ctrl->stop_proc)(evmgr, ctrl) == 0) {
                ret = FALSE;
            } else {
                mEv_clear_status(ctrl->type, mEv_STATUS_RUN);
            }
        }
    }

    return ret;
}

static int event_at_wade(EVENT_MANAGER_ACTOR* evmgr, aEvMgr_event_ctrl_c* ctrl) {
    int ret = 0;

    if (evmgr->skip_event_at_wade) {
        return FALSE;
    }

    if (mEv_check_status(ctrl->type, mEv_STATUS_ACTIVE) == FALSE || mEv_check_status(ctrl->type, mEv_STATUS_STOP) != FALSE) {
        if (mEv_check_status(ctrl->type, mEv_STATUS_SHOW) != FALSE) {
            if (ctrl->out_proc != NULL && (*ctrl->out_proc)(evmgr, ctrl) == 0) {
                return FALSE;
            }

            mEv_clear_status(ctrl->type, mEv_STATUS_SHOW);
            mEv_clear_status(ctrl->type, mEv_STATUS_STOP);
            if (ctrl->behind_proc != NULL) {
                (*ctrl->behind_proc)(evmgr, ctrl);
            }
        }
    } else {
        if (mFI_CheckPlayerWade(mFI_WADE_NONE) == TRUE && ((GAME_PLAY*)gamePT)->fb_fade_type == FADE_TYPE_NONE) {
            return FALSE;
        }

        if (mEv_check_status(ctrl->type, mEv_STATUS_SHOW) == FALSE) {
            if (ctrl->in_proc != NULL) {
                ret = (*ctrl->in_proc)(evmgr, ctrl);
                if (ret == 0) {
                    return FALSE;
                }
            }

            if (ret == 1 && mEv_check_status(ctrl->type, mEv_STATUS_ERROR) == FALSE) {
                mEv_set_status(ctrl->type, mEv_STATUS_SHOW);
            }
        }
    }

    return TRUE;
}

static int n_today_event = 0;

static aEvMgr_event_ctrl_c* today_event[32];

static aEvMgr_event_ctrl_c schedule_event[] = {
    { mEv_EVENT_FISHING_TOURNEY_1, anglingtournament_start, anglingtournament_stop, anglingtournament_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_FISHING_TOURNEY_2, anglingtournament_start, anglingtournament_stop, anglingtournament_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_ARTIST, artist_start, artist_stop, artist_in, wait_culling, artist_behind, {0, 0} },
    { mEv_EVENT_BROKER_SALE, broker_start, broker_stop, broker_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_DESIGNER, designer_start, designer_stop, designer_in, wait_culling, designer_behind, {0, 0} },
    { mEv_EVENT_CARPET_PEDDLER, arabian_start, arabian_stop, arabian_in, wait_culling, arabian_behind, {0, 0} },
    { mEv_EVENT_GYPSY, gypsy_start, gypsy_stop, gypsy_in, gypsy_out, NULL, {0, 0} },
    { mEv_EVENT_SHOP_SALE, bargain_start, bargain_stop, NULL, bargain_out, NULL, {0, 0} },
    { mEv_EVENT_HANDBILL_BROKER, prebroker_start, NULL, NULL, NULL, NULL, {0, 0} },
    { mEv_EVENT_HANDBILL_SHOP_SALE, prebargain_start, NULL, NULL, NULL, NULL, {0, 0} },
    { mEv_EVENT_TOY_DAY_JINGLE, christmas_start, christmas_stop, christmas_in, wait_culling, christmas_behind, {0, 0} },
    { mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN, countdown_start, countdown_stop, countdown_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_DOZAEMON, downing_start, downing_stop, downing_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_APRILFOOLS_DAY, aprilfool_start, aprilfool_stop, NULL, NULL, NULL, {0, 0} },
    { mEv_EVENT_SPORTS_FAIR_BALL_TOSS, fdbasket_start, fdbasket_stop, fdbasket_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SPORTS_FAIR_AEROBICS, fdgymnastic_start, fdgymnastic_stop, fdgymnastic_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SPORTS_FAIR_FOOT_RACE, fdrace_start, fdrace_stop, fdrace_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR, fdtug_start, fdtug_stop, fdtug_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SPORTS_FAIR, fdwp_start, fdwp_stop, NULL, NULL, NULL, {0, 0} },
    { mEv_EVENT_FIREWORKS_SHOW, firework_start, firework_stop, firework_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_CHERRY_BLOSSOM_FESTIVAL, flowerviewing_start, flowerviewing_stop, flowerviewing_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_HALLOWEEN, halloween_start, halloween_stop, halloween_in, wait_culling, halloween_behind, {0, 0} },
    { mEv_EVENT_KAMAKURA, kamakura_start, kamakura_stop, kamakura_in, kamakura_out, NULL, {0, 0} },
    { mEv_EVENT_NEW_YEARS_DAY, newyear_start, newyear_stop, newyear_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_MORNING_AEROBICS, radiogymnastic_start, radiogymnastic_stop, radiogymnastic_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SNOWMAN_SEASON, snowman_start, NULL, NULL, NULL, NULL, {0, 0} },
    { mEv_EVENT_KK_SLIDER, staffroll_start, staffroll_stop, staffroll_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_KABU_PEDDLER, turnipbuyer_start, turnipbuyer_stop, turnipbuyer_in, wait_culling, turnipbuyer_behind, {0, 0} },
    { mEv_EVENT_GHOST, ghost_start, ghost_stop, ghost_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_BRIDGE_MAKE, bridge_man_start, bridge_man_stop, bridge_man_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_BRIDGE_MAKE, bridge_make_start, bridge_make_stop, bridge_make_in, NULL, NULL, {0, 0} },
    { mEv_EVENT_MASK_NPC, gohome_mask_start, gohome_mask_stop, gohome_mask_in, wait_culling, gohome_mask_behind, {0, 0} },
    { mEv_EVENT_SONCHO_VACATION_JANUARY, soncho_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_VACATION_FEBRUARY, soncho_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SPRING_EQUINOX, prebroker_start, NULL, NULL, NULL, NULL, {0, 0} },
    { mEv_EVENT_AUTUMN_EQUINOX, prebroker_start, NULL, NULL, NULL, NULL, {0, 0} },
    { mEv_EVENT_GROUNDHOG_DAY, groundhog_start, groundhog_stop, groundhog_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_HARVEST_MOON_FESTIVAL, harvestmoon_start, harvestmoon_stop, harvestmoon_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_HARVEST_FESTIVAL, harvestfestival_start, harvestfestival_stop, harvestfestival_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_METEOR_SHOWER, meteor_shower_viewing_start, meteor_shower_viewing_stop, meteor_shower_viewing_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_NEW_YEARS_DAY, NULL, NULL, NULL, NULL, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_GROUNDHOG_DAY, soncho_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_SPRING_SPORTS_FAIR, NULL, NULL, NULL, NULL, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_APRILFOOLS_DAY, soncho_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_CHERRY_BLOSSOM_FESTIVAL, NULL, NULL, NULL, NULL, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_NATURE_DAY, soncho_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_SPRING_CLEANING, soncho_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_MOTHERS_DAY, soncho_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_GRADUATION_DAY, soncho_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_FATHERS_DAY, soncho_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_FISHING_TOURNEY_1, sonchowandar_start, sonchowandar_stop, sonchowandar_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_TOWN_DAY, soncho_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_FIREWORKS_SHOW, sonchowandar_start, sonchowandar_stop, sonchowandar_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_METEOR_SHOWER, NULL, NULL, NULL, NULL, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_FOUNDERS_DAY, soncho_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_LABOR_DAY, soncho_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_FALL_SPORTS_FAIR, NULL, NULL, NULL, NULL, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_HARVEST_MOON_FESTIVAL, NULL, NULL, NULL, NULL, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_EXPLORERS_DAY, soncho_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_HALLOWEEN, sonchohalloween_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_MAYORS_DAY, soncho_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_OFFICERS_DAY, soncho_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_FISHING_TOURNEY_2, sonchowandar_start, sonchowandar_stop, sonchowandar_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_HARVEST_FESTIVAL, NULL, NULL, NULL, NULL, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_SALE_DAY, soncho_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_SNOW_DAY, soncho_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_SONCHO_TOY_DAY, soncho_start, soncho_stop, soncho_in, wait_culling, NULL, {0, 0} },
    { mEv_EVENT_TALK_NEW_YEARS_COUNTDOWN, NULL, NULL, NULL, NULL, NULL, {0, 0} },
    { mEv_EVENT_HARVEST_FESTIVAL_FRANKLIN, harvestfestival_turkey_start, harvestfestival_turkey_stop, harvestfestival_turkey_in, wait_culling, turkey_behind, {0, 0} },
    { mEv_EVENT_SUMMER_CAMPER, summercamp_start, summercamp_stop, summercamp_in, summercamp_out, NULL, {0, 0} },
};

static int n_schedule_event = ARRAY_COUNT(schedule_event);

static int check_past_day(u32 min, u32 now, u32 max) {
    if (min > max) {
        return FALSE;
    }

    return min < now && now <= max;
}

static int set_today_event(void) {
    int i;

    n_today_event = 0;
    for (i = 0; i < n_schedule_event; i++) {
        if (mEv_check_run_today(schedule_event[i].type) != FALSE) {
            today_event[n_today_event] = &schedule_event[i];
            if (n_today_event < ARRAY_COUNT(today_event)) {
                n_today_event++;
            }
        }
    }

    return TRUE;
}

typedef union {
    struct {
        u8 year;
        u8 month;
        u8 day;
        u8 hour;
    };
    u32 raw;
} ymdh;

static int mail_event_check(void) {
    lbRTC_time_c* now = Common_GetPointer(time.rtc_time);
    Private_c* priv = Save_Get(private_data);
    int i;
    int n = 0;
    ymdh last_time;
    ymdh target_date;
    ymdh date;

    date.year = now->year % 100;
    date.month = now->month;
    date.day = now->day;
    date.hour = now->hour;

    last_time.raw = Save_Get(event_save_common).last_date;
    if (Save_Get(cheated_flag) == FALSE &&
        // check dates between Jan 1st and Dec 31st
        (last_time.raw & 0x00FFFFFF) >= 0x00010100 && 
        (last_time.raw & 0x00FFFFFF) <= 0x000C1F17) {
        
        target_date.hour = 0;
        for (i = 0; i < PLAYER_NUM; i++) {
            if (mPr_NullCheckPersonalID(&priv[i].player_ID) == FALSE && mEv_ArbeitPlayer(i) == FALSE) {
                // Send birthday card
                if (priv[i].birthday.month >= lbRTC_JANUARY && priv[i].birthday.month <= lbRTC_DECEMBER) {
                    target_date.month = priv[i].birthday.month;
                    target_date.day = priv[i].birthday.day;
                    target_date.year = (last_time.month > date.month && last_time.month <= target_date.month) ? last_time.year : date.year;

                    if (check_past_day(last_time.raw, target_date.raw, date.raw) != FALSE) {
                        mNpc_SendEventBirthdayCard2(&priv[i].player_ID, i);
                        n++;
                    }
                }

                // Send xmas card
                target_date.month = lbRTC_DECEMBER;
                target_date.day = 25;
                target_date.year = (last_time.month > date.month && last_time.month <= target_date.month) ? last_time.year : date.year;
                if (check_past_day(last_time.raw, target_date.raw, date.raw) != FALSE && date.year == last_time.year && date.day <= (target_date.day + lbRTC_WEEK)) {
                    mNpc_SendEventXmasCard(&priv[i].player_ID, i);
                    n++;
                }
            }
        }

        // Valentine's day
        target_date.month = lbRTC_FEBRUARY;
        target_date.day = 14;
        target_date.hour = 0;
        target_date.year = (last_time.month > date.month && last_time.month <= target_date.month) ? last_time.year : date.year;

        // check Valentine's day is between the last event mail save date and the current date
        // also check that the current date is within a week of Valentine's day
        if (check_past_day(last_time.raw, target_date.raw, date.raw) != FALSE && date.year == last_time.year && date.day <= (target_date.day + lbRTC_WEEK)) {
            // schedule Valentine's day mail for 10 am on February 14th
            target_date.hour = 10; // 10am on Valentine's day
            Save_Get(event_save_common).valentines_day_date = target_date.raw;
            n++;
        }
    }

    Save_Get(event_save_common).last_date = date.raw;

    if (Save_Get(npc_force_go_home) == TRUE) {
        mGH_animal_return_init();
    }

    Save_Set(cheated_flag, FALSE);
    Save_Set(npc_force_go_home, FALSE);
    return n;
}

static int vt_wt_mail_check(void) {
    lbRTC_time_c* now = Common_GetPointer(time.rtc_time);
    int ret = FALSE;
    ymdh vt_date;
    ymdh date;

    date.year = now->year % 100;
    date.month = now->month;
    date.day = now->day;
    date.hour = now->hour;
    
    if (Save_Get(event_save_common).valentines_day_date != 0) {
        vt_date.raw = Save_Get(event_save_common).valentines_day_date;
        vt_date.hour = 0;

        if (Save_Get(event_save_common).valentines_day_date <= date.raw) {
            mNpc_SendVtdayMail();
            Save_Get(event_save_common).valentines_day_date = 0;
            ret = TRUE;
        } else if (date.raw < vt_date.raw) {
            Save_Get(event_save_common).valentines_day_date = 0;
        }
    }

    return ret;
}

static void schedule_init(ACTOR* actorx) {
    EVENT_MANAGER_ACTOR* evmgr = (EVENT_MANAGER_ACTOR*)actorx;
    lbRTC_time_c* now = Common_GetPointer(time.rtc_time);
    int seed[] = { 0x6CF5F763, 0x5687FF74, 0xF66F567B, 0x054693DF, 0xC8968F49, 0xF6D7BCA4, 0x786CD6A8, 0x154645D3 };
    
    evmgr->month_day = 0;
    evmgr->change = 0;
    evmgr->day_hour = 0;
    evmgr->next_block.x = -1;
    evmgr->next_block.z = -1;
    evmgr->skip_event_at_wade = 0;
    fluc = now->min * 16 + now->sec * seed[now->sec & 7];
    evmgr->pool_block_exists = TRUE;
    evmgr->station_block_exists = TRUE;
    evmgr->shrine_block_exists = TRUE;
    evmgr->player_home_exists = TRUE;
    evmgr->dock_block_exists = TRUE;

    if (mFI_BlockKind2BkNum(&evmgr->pool_block.x, &evmgr->pool_block.z, mRF_BLOCKKIND_POOL) == FALSE) {
        evmgr->pool_block_exists = FALSE;
    }

    if (mFI_BlockKind2BkNum(&evmgr->station_block.x, &evmgr->station_block.z, mRF_BLOCKKIND_STATION) == FALSE) {
        evmgr->station_block_exists = FALSE;
    }

    if (mFI_BlockKind2BkNum(&evmgr->shrine_block.x, &evmgr->shrine_block.z, mRF_BLOCKKIND_SHRINE) == FALSE) {
        evmgr->shrine_block_exists = FALSE;
    }

    if (mFI_BlockKind2BkNum(&evmgr->player_home_block.x, &evmgr->player_home_block.z, mRF_BLOCKKIND_PLAYER) == FALSE) {
        evmgr->player_home_exists = FALSE;
    }

    if (mFI_BlockKind2BkNum(&evmgr->dock_block.x, &evmgr->dock_block.z, mRF_BLOCKKIND_DOCK) == FALSE) {
        evmgr->dock_block_exists = FALSE;
    }
}

static void schedule_main(ACTOR* actorx) {
    ACTOR* playerx = GET_PLAYER_ACTOR_NOW_ACTOR();
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    EVENT_MANAGER_ACTOR* evmgr = (EVENT_MANAGER_ACTOR*)actorx;
    lbRTC_time_c* now = Common_GetPointer(time.rtc_time);
    Event_c* event = &play->event;
    int month = mEv_GetMonth(event);
    int day = mEv_GetDay(event);
    int hour = mEv_GetHour(event);
    int i;
    int month_day;
    int day_hour;
    int change;
    int event_waiting;
    BlockOrUnit_c block;
    aEvMgr_event_ctrl_c* ctrl;
    u32 player_no = Common_Get(player_no);

    if (Save_Get(event_save_common).special_event.flags == 1) {
        set_special_event_save();
        Save_Get(event_save_common).special_event.flags = 0;
    }

    if (mDemo_CheckDemo() == FALSE) {
        month_day = (month << 8) + day;
        if (month_day != evmgr->month_day) {
            if (mEv_ArbeitPlayer_kari(player_no) == FALSE && mEv_LivePlayer(player_no) != FALSE && mEv_LiveSonchoPresent() == FALSE) {
                set_today_event();
            }

            evmgr->month_day = month_day;
            mail_event_check();
        }

        day_hour = (day << 8) + hour;
        if (day_hour != evmgr->day_hour) {
            vt_wt_mail_check();
            evmgr->day_hour = day_hour;
        }

        if (mEv_ArbeitPlayer_kari(player_no) == FALSE && mEv_LivePlayer(player_no) != FALSE && mEv_LiveSonchoPresent() == FALSE) {
            change = mEv_change(event);

            if (change != evmgr->change) {
                event_waiting = 0;

                for (i = 0; i < n_today_event; i++) {
                    ctrl = today_event[i];
                    if (event_at_oclock(evmgr, ctrl) == FALSE) {
                        event_waiting++;
                    }
                }

                if (event_waiting == 0) {
                    evmgr->change = change;
                    Save_Get(event_save_common).delete_event_id = 0;
                }
            }
        }
    }

    if (mEv_ArbeitPlayer_kari(player_no) != FALSE || mEv_LivePlayer(player_no) == FALSE || mEv_LiveSonchoPresent() != FALSE) {
        return;
    }
    if (mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELDTYPE2_FG) {
        mFI_Wpos2BlockNum(&block.x, &block.z, playerx->world.position);
        if (
            // clang-format off
            block.x != evmgr->next_block.x || block.z != evmgr->next_block.z ||
            mFI_CheckPlayerWade(mFI_WADE_START) == TRUE ||
            mFI_CheckPlayerWade(mFI_WADE_INPROGRESS) == TRUE ||
            mFI_CheckPlayerWade(mFI_WADE_END) == TRUE ||
            play->fb_fade_type != FADE_TYPE_NONE ||
            mEv_someone_died() != FALSE
            // clang-format on
        ) {
            event_waiting = 0;

            for (i = 0; i < n_today_event; i++) {
                ctrl = today_event[i];
                if (event_at_wade(evmgr, ctrl) == FALSE) {
                    event_waiting++;
                }
            }

            if (event_waiting == 0) {
                mFI_GetNextBlockNum(&block.x, &block.z);
                evmgr->next_block.x = block.x;
                evmgr->next_block.z = block.z;
            }

            fluc = fluc * 2 + ((fluc & 0xD5FE46CF) + (now->sec | 1)) * 9;
        }
    } else {
        evmgr->next_block.x = -1;
        evmgr->next_block.z = -1;
    }

    if (ZURUMODE2_ENABLED()) {
        w_guide_arrow();
        sp_guide_arrow();
        day_guide_arrow();
        turkey_guide_arrow();
    }
}

// clang-format off
ACTOR_PROFILE Event_Manager_Profile = {
    mAc_PROFILE_EVENT_MANAGER,
    ACTOR_PART_ITEM,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EVENT_MANAGER_ACTOR),
    &aEvMgr_ct,
    &aEvMgr_dt,
    &aEvMgr_move,
    &aEvMgr_draw,
    &aEvMgr_save,
};
// clang-format on
