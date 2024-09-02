#include "ac_shop_level.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_house.h"
#include "m_handbill.h"
#include "m_string.h"

static void Shop_Level_Actor_ct(ACTOR* actorx, GAME* game);
static void Shop_Level_Actor_dt(ACTOR* actorx, GAME* game);
static void Shop_Level_Actor_move(ACTOR* actorx, GAME* game);
static void Shop_Level_Actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Shop_Level_Profile = {
    mAc_PROFILE_SHOP_LEVEL,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(SHOP_LEVEL_ACTOR),
    &Shop_Level_Actor_ct,
    &Shop_Level_Actor_dt,
    &Shop_Level_Actor_move,
    &Shop_Level_Actor_draw,
    NULL,
};
// clang-format on

static void aSL_SetShopRenewalChirashi_Notice(int shop_level, lbRTC_time_c* time_p) {
    static int renewal_chirashi_bunmen[] = { 0x0018, 0x0019, 0x001A, 0x001A };
    int header_back_start;
    Mail_c mail;
    Mail_ct_c* content = &mail.content;
    u8 year_str[6];
    u8 month_str[9];
    u8 day_str[4];
    lbRTC_time_c renew_start_date = *time_p;
    int i;

    lbRTC_Sub_DD(&renew_start_date, 1);
    for (i = 0; i < PLAYER_NUM; i++) {
        int player_no = mHS_get_pl_no_detail(i);
        int free_idx = mMl_chk_mail_free_space(Save_Get(homes[i]).mailbox, HOME_MAILBOX_SIZE);

        if (free_idx >= 0 && player_no != -1 && mEv_ArbeitPlayer(player_no) == FALSE) {
            int year_str_len;

            mString_Load_StringFromRom(month_str, sizeof(month_str),
                                       mString_MONTH_START + (renew_start_date.month - 1));
            mHandbill_Set_free_str(mHandbill_FREE_STR0, month_str, sizeof(month_str));
            mString_Load_StringFromRom(day_str, sizeof(day_str), mString_DAY_START + (renew_start_date.day - 1));
            mHandbill_Set_free_str(mHandbill_FREE_STR1, day_str, sizeof(day_str));
            year_str_len = mString_Load_YearStringFromRom(year_str, renew_start_date.year);
            mHandbill_Set_free_str(mHandbill_FREE_STR2, year_str, year_str_len);
            mMl_clear_mail(&mail);
            mHandbill_Load_HandbillFromRom(content->header, &header_back_start, content->footer, content->body,
                                           renewal_chirashi_bunmen[shop_level & 3]);
            content->header_back_start = header_back_start;
            content->font = mMl_FONT_0;
            content->paper_type = (u8)ITM_PAPER55;
            content->mail_type = mMl_TYPE_SHOP_SALE_LEAFLET;
            mPr_CopyPersonalID(&mail.header.recipient.personalID, &Save_Get(private_data[player_no]).player_ID);
            mail.header.recipient.type = mMl_NAME_TYPE_PLAYER;
            mMl_copy_mail(&Save_Get(homes[i]).mailbox[free_idx], &mail);
        }
    }
}

static void aSL_SetRenewalChiraswhi_Notice(void) {
    if (Save_Get(shop).shop_info.send_upgrade_notice == TRUE) {
        if (mSP_GetShopLevel() < mSP_GetRealShopLevel()) {
            lbRTC_time_c* rtc_time_p = Common_GetPointer(time.rtc_time);
            lbRTC_time_c renew_time = Save_Get(shop).renewal_time;

            lbRTC_Sub_DD(&renew_time, 1);
            if (lbRTC_IsOverTime(&renew_time, rtc_time_p) == lbRTC_OVER ||
                lbRTC_IsEqualTime(rtc_time_p, &renew_time, lbRTC_CHECK_YEARS | lbRTC_CHECK_MONTHS | lbRTC_CHECK_DAYS)) {
                aSL_SetShopRenewalChirashi_Notice(mSP_GetShopLevel(), &Save_Get(shop).renewal_time);
                Save_Get(shop).shop_info.send_upgrade_notice = FALSE;
            }
        } else {
            aSL_SetShopRenewalChirashi_Notice((mSP_GetShopLevel() - 1) & 3, &Save_Get(shop).renewal_time);
            Save_Get(shop).shop_info.send_upgrade_notice = FALSE;
        }
    }
}

typedef struct shop_level_rewrite_offset_s {
    int ofs_ux;
    int ofs_uz;
} aSL_rewrite_ofs_c;

// clang-format off
static aSL_rewrite_ofs_c aSL_zakka_rw[] = {
    { -1, -1 },
    {  0, -1 },
    { -2,  0 },
    { -1,  0 },
    {  1,  0 },
    { -2,  1 },
    { -1,  1 },
    {  0,  1 },
    {  1,  1 },
    { -1,  2 },
    {  0,  2 },
};
// clang-format on

// clang-format off
static aSL_rewrite_ofs_c aSL_conveni_rw[] = {
    { -2, -2 },
    { -1, -2 },
    { -3, -1 },
    { -2, -1 },
    { -1, -1 },
    {  0, -1 },
    { -3,  0 },
    { -2,  0 },
    { -1,  0 },
    {  1,  0 },
    { -2,  1 },
    { -1,  1 },
    {  0,  1 },
    {  1,  1 },
    { -1,  2 },
    {  0,  2 },
};
// clang-format on

// clang-format off
static aSL_rewrite_ofs_c aSL_super_rw[] = {
    { -1, -3 },
    {  0, -3 },
    { -2, -2 },
    { -1, -2 },
    {  0, -2 },
    {  1, -2 },
    { -3, -1 },
    { -2, -1 },
    { -1, -1 },
    {  0, -1 },
    {  1, -1 },
    {  2, -1 },
    { -3,  0 },
    { -2,  0 },
    { -1,  0 },
    {  1,  0 },
    {  2,  0 },
    { -2,  1 },
    { -1,  1 },
    {  0,  1 },
    {  1,  1 },
    { -1,  2 },
    {  0,  2 },
};
// clang-format on

static void aSL_GroundClean(s16 level, s16 next_level, mActor_name_t* fg_p, int bx, int bz, int ux, int uz) {
    static aSL_rewrite_ofs_c* table[] = {
        aSL_zakka_rw,
        aSL_conveni_rw,
        aSL_super_rw,
        aSL_super_rw,
    };
    static int rw_cnt[] = {
        ARRAY_COUNT(aSL_zakka_rw),
        ARRAY_COUNT(aSL_conveni_rw),
        ARRAY_COUNT(aSL_super_rw),
        ARRAY_COUNT(aSL_super_rw),
    };

    int i;
    aSL_rewrite_ofs_c* rewrite_ofs_p;
    u16* deposit_p;

    deposit_p = mFI_GetDepositP(bx, bz);
    rewrite_ofs_p = table[next_level & 3];

    for (i = 0; i < rw_cnt[next_level & 3]; i++) {
        int rewrite_ux = (ux + rewrite_ofs_p[i].ofs_ux) & 0xF;
        int rewrite_uz = (uz + rewrite_ofs_p[i].ofs_uz) & 0xF;
        int rewrite_unit = rewrite_uz * UT_X_NUM + rewrite_ux;

        mPB_keep_item(fg_p[rewrite_unit]);
        mFI_BlockDepositOFF(deposit_p, rewrite_ux, rewrite_uz);
        fg_p[rewrite_unit] = RSV_NO;
    }
}

static int aSL_RewriteShopFg(ACTOR* actorx, GAME* game, s16 level, s16 next_level) {
    SHOP_LEVEL_ACTOR* shop_level = (SHOP_LEVEL_ACTOR*)actorx;
    int i;
    int ux;
    int uz;
    mActor_name_t* fg_top_p;
    mActor_name_t* fg_p;

    fg_top_p = mFI_BkNumtoUtFGTop(shop_level->bx, shop_level->bz);
    fg_p = fg_top_p;

    if (fg_top_p != NULL) {
        for (i = 0; i < UT_TOTAL_NUM; i++) {
            /* @BUG - shouldn't this just be <= SHOP3? This goes one over which would include the Post Office */
            if (*fg_top_p >= SHOP0 && *fg_top_p <= (SHOP3 + 1)) {
                ux = i & 0xF;
                uz = (i >> 4) & 0xF;
                *fg_top_p = SHOP0 + next_level;
                aSL_GroundClean((s16)level, (s16)next_level, fg_p, shop_level->bx, shop_level->bz, ux, uz);
                return TRUE;
            }

            fg_top_p++;
        }
    }

    return FALSE;
}

static void aSL_RenewShop(ACTOR* actorx, GAME* game) {
    int last_scene = Common_Get(last_scene_no);

    if (last_scene == SCENE_SHOP0 || last_scene == SCENE_CONVENI || last_scene == SCENE_SUPER ||
        last_scene == SCENE_DEPART || last_scene == SCENE_DEPART_2) {
        return;
    }

    if (mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELD_FG && Save_Get(scene_no) == SCENE_FG &&
        mEv_CheckEvent(mEv_SAVED_RENEWSHOP) == TRUE) {
        lbRTC_time_c renew_time = Save_Get(shop).renewal_time;
        lbRTC_time_c now_time = Common_Get(time.rtc_time);

        aSL_SetRenewalChiraswhi_Notice();
        if (lbRTC_IsOverTime(&renew_time, &now_time) == lbRTC_OVER ||
            lbRTC_IsEqualTime(&now_time, &renew_time, lbRTC_CHECK_YEARS | lbRTC_CHECK_MONTHS | lbRTC_CHECK_DAYS)) {
            if (aSL_RewriteShopFg(actorx, game, mSP_GetShopLevel(), mSP_GetRealShopLevel()) && mSP_RenewShopLevel()) {
                mEv_EventOFF(mEv_SAVED_RENEWSHOP);
                mSP_NewExchangeDay();
                mSP_ExchangeLineUp_ZeldaMalloc();
            }
        }
    }
}

static void Shop_Level_Actor_ct(ACTOR* actorx, GAME* game) {
    SHOP_LEVEL_ACTOR* shop_level = (SHOP_LEVEL_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    ACTOR* player_actor = GET_PLAYER_ACTOR_ACTOR(play);
    xyz_t* pos_p;
    int shop_block_flag;

    shop_level->bx = 0;
    shop_level->bz = 0;
    if (player_actor != NULL) {
        pos_p = &player_actor->world.position;
    } else {
        pos_p = &actorx->world.position;
    }

    /* Try to move shop level actor to where the player currently is */
    actorx->world.position = *pos_p;
    shop_block_flag = mFI_BlockKind2BkNum(&shop_level->bx, &shop_level->bz, mRF_BLOCKKIND_SHOP);
    if (Save_Get(scene_no) == SCENE_FG) {
        mSP_SetShopRareFurnitureChirashi(Common_Get(player_no), Save_Get(shop).items, mSP_GOODS_COUNT, NULL);
        Save_Get(shop).shop_info.not_loaded_before = FALSE;
    }

    if (shop_block_flag) {
        aSL_RenewShop(actorx, game);
    }
}

static void Shop_Level_Actor_dt(ACTOR* actorx, GAME* game) {
    // nothing
}

static void Shop_Level_Actor_draw(ACTOR* actorx, GAME* game) {
    // nothing
}

static void aSL_JudgeRenewShop(ACTOR* actorx, GAME* game) {
    if (Save_Get(scene_no) == SCENE_FG && mEv_CheckEvent(mEv_SAVED_RENEWSHOP) == FALSE) {
        if (mSP_GetShopLevel() < mSP_GetRealShopLevel()) {
            lbRTC_time_c now_time = Common_Get(time.rtc_time);
            lbRTC_time_c renewal_two_days = now_time;
            lbRTC_time_c renewal_one_day;
            u16 bargain_date;

            renewal_two_days.hour = mSP_GetShopOpenTime();
            renewal_two_days.min = 0;
            renewal_two_days.sec = 0;
            lbRTC_Add_DD(&renewal_two_days, 2);
            renewal_one_day = now_time;
            lbRTC_Add_DD(&renewal_one_day, 1);
            bargain_date = mEv_get_bargain_day();
            if (bargain_date != 0) {
                lbRTC_month_t bargain_month = (bargain_date >> 8) & 0xFF;
                lbRTC_day_t bargain_day = bargain_date & 0xFF;

                /* No upgrading shop if a Nook sale event happens within 2 days */
                if ((now_time.month == bargain_month && now_time.day == bargain_day) ||
                    (renewal_two_days.month == bargain_month && renewal_two_days.day == bargain_day) ||
                    (renewal_one_day.month == bargain_month && renewal_one_day.day == bargain_day)) {
                    return;
                }
            }

            {
                lbRTC_year_t now_year = now_time.year;
                lbRTC_month_t now_month = now_time.month;
                lbRTC_day_t max_day = lbRTC_GetDaysByMonth(now_year, now_time.month);
                lbRTC_day_t now_day = now_time.day;

                /* No upgrading shop if lottery day is within 2 days */
                if (now_day == max_day ||
                    (renewal_two_days.day == lbRTC_GetDaysByMonth(renewal_two_days.year, renewal_two_days.month)) ||
                    (renewal_one_day.day == lbRTC_GetDaysByMonth(renewal_one_day.year, renewal_one_day.month))) {
                    return;
                }
                /* Don't upgrade shop on sale day */
                if ((now_month == lbRTC_NOVEMBER &&
                     now_day == (lbRTC_Weekly_day(now_year, lbRTC_NOVEMBER, 4, lbRTC_THURSDAY) + 1)) ||
                    (renewal_two_days.month == lbRTC_NOVEMBER &&
                     renewal_two_days.day ==
                         (lbRTC_Weekly_day(renewal_two_days.year, lbRTC_NOVEMBER, 4, lbRTC_THURSDAY) + 1)) ||
                    (renewal_one_day.month == lbRTC_NOVEMBER &&
                     renewal_one_day.day ==
                         (lbRTC_Weekly_day(renewal_one_day.year, lbRTC_NOVEMBER, 4, lbRTC_THURSDAY) + 1))) {
                    return;
                }
            }

            mEv_EventON(mEv_SAVED_RENEWSHOP);
            Save_Get(shop).renewal_time = renewal_two_days;
            Save_Get(shop).shop_info.send_upgrade_notice = TRUE;
            Save_Get(shop).shop_info.upgrading_today = TRUE;
        }
    }

    if (Save_Get(scene_no) == SCENE_FG && mEv_CheckEvent(mEv_SAVED_RENEWSHOP) == TRUE) {
        lbRTC_time_c now_time = Common_Get(time.rtc_time);
        lbRTC_time_c renewal_time = Save_Get(shop).renewal_time;

        lbRTC_Sub_DD(&renewal_time, 2);
        if (lbRTC_IsOverTime(&now_time, &renewal_time) == lbRTC_OVER) {
            mEv_EventOFF(mEv_SAVED_RENEWSHOP);
            Save_Get(shop).shop_info.upgrading_today = FALSE;
            Save_Get(shop).shop_info.send_upgrade_notice = FALSE;
            return;
        }
    }

    aSL_SetRenewalChiraswhi_Notice();
    mSP_SetRenewalChiraswhi_AppoDay();
}

static void aSL_ExchangeShopGoodsInGame(ACTOR* actorx, GAME* game, lbRTC_hour_t hour) {
    lbRTC_time_c now_time = Common_Get(time.rtc_time);
    lbRTC_hour_t now_hour = now_time.hour;

    if (mEv_CheckEvent(mEv_SAVED_RENEWSHOP) == FALSE && Save_Get(scene_no) == SCENE_FG && now_hour >= hour &&
        mSP_CheckExchangeDay2()) {
        if (mSP_CheckExchangeMonth()) {
            mSP_LotteryLineUp_ZeldaMalloc();
        }

        mSP_NewExchangeDay();
        mSP_ExchangeLineUp_ZeldaMalloc();
    }
}

static void aSL_ReportShopOpen2Event(void) {
    int status = mSP_ShopOpen(); // @unused

    if (mSP_ShopOpen() == mSP_SHOP_STATUS_OPEN || mSP_ShopOpen() == mSP_SHOP_STATUS_OPENEVENT) {
        mEv_EventON(mEv_DAILY_OPEN_SHOP);
    } else {
        mEv_EventOFF(mEv_DAILY_OPEN_SHOP);
    }
}

static void Shop_Level_Actor_move(ACTOR* actorx, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ACTOR* player_actor = GET_PLAYER_ACTOR_ACTOR(play);
    xyz_t* pos_p;

    if (player_actor != NULL) {
        pos_p = &player_actor->world.position;
    } else {
        pos_p = &actorx->world.position;
    }

    actorx->world.position = *pos_p;
    aSL_JudgeRenewShop(actorx, game);
    aSL_ExchangeShopGoodsInGame(actorx, game, 6);
    aSL_ReportShopOpen2Event();
}
