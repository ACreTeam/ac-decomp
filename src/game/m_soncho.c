#include "m_soncho.h"

#include "m_common_data.h"
#include "m_name_table.h"
#include "m_event.h"
#include "m_play.h"
#include "m_room_type.h"
#include "m_msg.h"
#include "m_item_name.h"
#include "m_string.h"
#include "m_font.h"
#include "ac_taisou_npc0.h"
#include "m_player_lib.h"

static u8 event_table[mSC_EVENT_NUM] = {
    mEv_EVENT_SONCHO_NEW_YEARS_DAY,
    mEv_EVENT_SONCHO_FOUNDERS_DAY,
    mEv_EVENT_SONCHO_GRADUATION_DAY,
    mEv_EVENT_SONCHO_APRILFOOLS_DAY,
    mEv_EVENT_SONCHO_TOWN_DAY,
    mEv_EVENT_SONCHO_MOTHERS_DAY,
    mEv_EVENT_SONCHO_SALE_DAY,
    mEv_EVENT_SONCHO_CHERRY_BLOSSOM_FESTIVAL,
    mEv_EVENT_SONCHO_SPRING_SPORTS_FAIR,
    mEv_EVENT_SONCHO_NATURE_DAY,
    mEv_EVENT_SONCHO_SPRING_CLEANING,
    mEv_EVENT_SONCHO_FATHERS_DAY,
    mEv_EVENT_SONCHO_FISHING_TOURNEY_1,
    mEv_EVENT_SONCHO_GROUNDHOG_DAY,
    mEv_EVENT_SONCHO_EXPLORERS_DAY,
    mEv_EVENT_SONCHO_FIREWORKS_SHOW,
    mEv_EVENT_METEOR_SHOWER,
    mEv_EVENT_HARVEST_MOON_FESTIVAL,
    mEv_EVENT_SONCHO_MAYORS_DAY,
    mEv_EVENT_SONCHO_OFFICERS_DAY,
    mEv_EVENT_SONCHO_FALL_SPORTS_FAIR,
    mEv_EVENT_SONCHO_HALLOWEEN,
    mEv_EVENT_SONCHO_FISHING_TOURNEY_2,
    mEv_EVENT_SONCHO_SNOW_DAY,
    mEv_EVENT_SONCHO_LABOR_DAY,
    mEv_EVENT_SONCHO_TOY_DAY,
    mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN,
    mEv_EVENT_SONCHO_HARVEST_FESTIVAL,
};

extern u8 mSC_get_soncho_event() {
    u8* event_table_p = event_table;
    int i = 0;

    for (i = 0; i < mSC_EVENT_NUM; i++) {
        if (i != mSC_EVENT_FISHING_TOURNEY_2 && mEv_check_status(event_table[i], mEv_STATUS_RUN) != FALSE) {
            return i;
        }
    }

    if (mEv_check_status(mEv_EVENT_SONCHO_FISHING_TOURNEY_2, mEv_STATUS_RUN)) {
        return mSC_EVENT_FISHING_TOURNEY_2;
    }

    if (mEv_check_status(mEv_EVENT_SONCHO_VACATION_JANUARY, mEv_STATUS_RUN)) {
        return mSC_SPECIAL_EVENT_JAN_VACATION;
    }

    if (mEv_check_status(mEv_EVENT_SONCHO_VACATION_FEBRUARY, mEv_STATUS_RUN)) {
        return mSC_SPECIAL_EVENT_FEB_VACATION;
    }

    if (mEv_check_status(mEv_EVENT_MORNING_AEROBICS, mEv_STATUS_RUN)) {
        return mSC_SPECIAL_EVENT_MORNING_AEROBICS;
    }

    return 0xFF;
}

extern u8 mSC_get_soncho_field_event() {
    if (mEv_check_status(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, mEv_STATUS_RUN)) {
        return mSC_FIELD_EVENT_FOOT_RACE;
    }

    if (mEv_check_status(mEv_EVENT_SPORTS_FAIR_BALL_TOSS, mEv_STATUS_RUN)) {
        return mSC_FIELD_EVENT_BALL_TOSS;
    }

    if (mEv_check_status(mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR, mEv_STATUS_RUN)) {
        return mSC_FIELD_EVENT_TUG_O_WAR;
    }

    return mSC_FIELD_EVENT_AEROBICS; // mEv_EVENT_SPORTS_FAIR_AEROBICS
}

extern void mSC_delete_soncho(ACTOR* actor, GAME_PLAY* play) {
    u8 event = mSC_get_soncho_event();

    switch (event) {
        case mSC_EVENT_NEW_YEARS_DAY: {
            ACTOR* ev_miko = Actor_info_name_search(&play->actor_info, mAc_PROFILE_EV_MIKO, ACTOR_PART_NPC);

            if (ev_miko != NULL) {
                Actor_delete(ev_miko);
            }

            break;
        }

        case mSC_EVENT_FOUNDERS_DAY:
        case mSC_EVENT_GRADUATION_DAY:
        case mSC_EVENT_APRILFOOLS_DAY:
        case mSC_EVENT_TOWN_DAY:
        case mSC_EVENT_MOTHERS_DAY:
        case mSC_EVENT_SALE_DAY:
        case mSC_EVENT_CHERRY_BLOSSOM_FESTIVAL:
        case mSC_EVENT_NATURE_DAY:
        case mSC_EVENT_SPRING_CLEANING:
        case mSC_EVENT_FATHERS_DAY:
        case mSC_EVENT_FISHING_TOURNEY_1:
        case mSC_EVENT_GROUNDHOG_DAY:
        case mSC_EVENT_EXPLORERS_DAY:
        case mSC_EVENT_FIREWORKS_SHOW:
        case mSC_EVENT_METEOR_SHOWER:
        case mSC_EVENT_HARVEST_MOON_FESTIVAL:
        case mSC_EVENT_MAYORS_DAY:
        case mSC_EVENT_OFFICERS_DAY:
        case mSC_EVENT_HALLOWEEN:
        case mSC_EVENT_FISHING_TOURNEY_2:
        case mSC_EVENT_SNOW_DAY:
        case mSC_EVENT_LABOR_DAY:
        case mSC_EVENT_TOY_DAY:
        case mSC_EVENT_NEW_YEARS_EVE_COUNTDOWN:
        case mSC_EVENT_HARVEST_FESTIVAL: {
            mEv_actor_dying_message(event_table[event], actor);
            break;
        }

        case mSC_EVENT_SPRING_SPORTS_FAIR:
        case mSC_EVENT_FALL_SPORTS_FAIR: {
            if (mEv_check_status(mEv_EVENT_SPORTS_FAIR_BALL_TOSS, mEv_STATUS_SHOW)) {
                mEv_actor_dying_message(mEv_EVENT_SPORTS_FAIR_BALL_TOSS, actor);
            } else if (mEv_check_status(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, mEv_STATUS_SHOW)) {
                mEv_actor_dying_message(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, actor);
            } else if (mEv_check_status(mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR, mEv_STATUS_SHOW)) {
                mEv_actor_dying_message(mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR, actor);
            }

            break;
        }

        case mSC_SPECIAL_EVENT_JAN_VACATION: {
            mEv_actor_dying_message(mEv_EVENT_SONCHO_VACATION_JANUARY, actor);
            break;
        }

        case mSC_SPECIAL_EVENT_FEB_VACATION: {
            mEv_actor_dying_message(mEv_EVENT_SONCHO_VACATION_FEBRUARY, actor);
            break;
        }

        case 0xFF: {
            break;
        }
    }
}

extern int mSC_trophy_get(u8 num) {
    int res = FALSE;

    if (num <= mSC_TROPHY_MAX) {
        if (num >= mSC_EVENT_NUM) {
            if ((Common_Get(now_private)->soncho_trophy_field1 & (1 << (u8)(num - mSC_EVENT_NUM))) != 0) {
                res = TRUE;
            }
        } else if ((Common_Get(now_private)->soncho_trophy_field0 & (1 << num)) != 0) {
            res = TRUE;
        }
    }

    return res;
}

extern void mSC_trophy_set(u8 num) {
    if (num > mSC_TROPHY_MAX) {
        return;
    }

    if (num >= mSC_EVENT_NUM) {
        Common_Get(now_private)->soncho_trophy_field1 |= (1 << (u8)(num - mSC_EVENT_NUM));
    } else {
        Common_Get(now_private)->soncho_trophy_field0 |= (1 << num);
    }
}

extern mActor_name_t mSC_trophy_item(u8 soncho_event) {
    static mActor_name_t soncho_item_table[mSC_EVENT_NUM] = {
        ITM_FOOD_APPLE,         // mSC_EVENT_NEW_YEARS_DAY
        FTR_WEED_MODEL,         // mSC_EVENT_FOUNDERS_DAY
        FTR_NEEDLEWORK_MODEL,   // mSC_EVENT_GRADUATION_DAY
        FTR_SUPER_TORTIMER,     // mSC_EVENT_APRILFOOLS_DAY
        ITM_FOOD_APPLE,         // mSC_EVENT_TOWN_DAY
        FTR_LOVELY_PHONE,       // mSC_EVENT_MOTHERS_DAY
        FTR_MARKET_MODEL,       // mSC_EVENT_SALE_DAY
        FTR_PINK_TREE_MODEL,    // mSC_EVENT_CHERRY_BLOSSOM_FESTIVAL
        FTR_SPRING_MEDAL,       // mSC_EVENT_SPRING_SPORTS_FAIR
        FTR_TREE_MODEL,         // mSC_EVENT_NATURE_DAY
        FTR_DUMP_MODEL,         // mSC_EVENT_SPRING_CLEANING
        FTR_LOCOMOTIVE_MODEL,   // mSC_EVENT_FATHERS_DAY
        FTR_ANGLER_TROPHY,      // mSC_EVENT_FISHING_TOURNEY_1
        ITM_FOOD_PEAR,          // mSC_EVENT_GROUNDHOG_DAY
        FTR_BOTTLED_SHIP,       // mSC_EVENT_EXPLORERS_DAY
        FTR_BOTTLE_ROCKET,      // mSC_EVENT_FIREWORKS_SHOW
        FTR_TELESCOPE,          // mSC_EVENT_METEOR_SHOWER
        FTR_MOON,               // mSC_EVENT_HARVEST_MOON_FESTIVAL
        FTR_WELL_MODEL,         // mSC_EVENT_MAYORS_DAY
        FTR_POLICE_MODEL,       // mSC_EVENT_OFFICERS_DAY
        FTR_AUTUMN_MEDAL,       // mSC_EVENT_FALL_SPORTS_FAIR
        FTR_FORTUNE_TENT_MODEL, // mSC_EVENT_HALLOWEEN
        FTR_FISHING_TROPHY,     // mSC_EVENT_FISHING_TOURNEY_2
        FTR_SNOWMAN,            // mSC_EVENT_SNOW_DAY
        FTR_SHOP_MDOEL,         // mSC_EVENT_LABOR_DAY
        ITM_FOOD_APPLE,         // mSC_EVENT_TOY_DAY
        FTR_NOISEMAKER,         // mSC_EVENT_NEW_YEARS_EVE_COUNTDOWN
        FTR_CORNUCOPIA          // mSC_EVENT_HARVEST_FESTIVAL
    };

    mActor_name_t item = ITM_FOOD_APPLE;

    if (soncho_event < mSC_EVENT_NUM) {
        switch (soncho_event) {
            case mSC_EVENT_NEW_YEARS_DAY: {
/* @BUG - devs have another off-by-one error here, as there are 16 diaries but this can only generate the first 15 */
#ifndef BUGFIXES
                item = (RANDOM(DIARY_NUM - 1) & 15) + ITM_DIARY_START;
#else
                item = RANDOM(DIARY_NUM) + ITM_DIARY_START;
#endif
                break;
            }

            case mSC_EVENT_TOY_DAY: {
                if (Common_Get(now_private)->gender == mPr_SEX_MALE) {
                    item = FTR_MINI_CAR;
                } else {
                    item = FTR_DOLLY;
                }
                break;
            }

            case mSC_EVENT_TOWN_DAY: {
                item = mSP_GetRandomStationToyItemNo();
                break;
            }

            case mSC_EVENT_GROUNDHOG_DAY: {
                item = mRmTp_FtrIdx2FtrItemNo(0x4DE + RANDOM(9), mRmTp_DIRECT_SOUTH); // random flower model
                break;
            }

            case mSC_EVENT_FOUNDERS_DAY:
            case mSC_EVENT_GRADUATION_DAY:
            case mSC_EVENT_APRILFOOLS_DAY:
            case mSC_EVENT_MOTHERS_DAY:
            case mSC_EVENT_SALE_DAY:
            case mSC_EVENT_CHERRY_BLOSSOM_FESTIVAL:
            case mSC_EVENT_SPRING_SPORTS_FAIR:
            case mSC_EVENT_NATURE_DAY:
            case mSC_EVENT_SPRING_CLEANING:
            case mSC_EVENT_FATHERS_DAY:
            case mSC_EVENT_FISHING_TOURNEY_1:
            case mSC_EVENT_EXPLORERS_DAY:
            case mSC_EVENT_FIREWORKS_SHOW:
            case mSC_EVENT_METEOR_SHOWER:
            case mSC_EVENT_HARVEST_MOON_FESTIVAL:
            case mSC_EVENT_MAYORS_DAY:
            case mSC_EVENT_OFFICERS_DAY:
            case mSC_EVENT_FALL_SPORTS_FAIR:
            case mSC_EVENT_HALLOWEEN:
            case mSC_EVENT_FISHING_TOURNEY_2:
            case mSC_EVENT_SNOW_DAY:
            case mSC_EVENT_LABOR_DAY:
            default: {
                item = soncho_item_table[soncho_event];
                break;
            }
        }
    }

    return item;
}

extern void mSC_item_string_set(mActor_name_t item, int str_no) {
    u8 item_name[mIN_ITEM_NAME_LEN];
    mMsg_Window_c* window = mMsg_Get_base_window_p();

    mIN_copy_name_str(item_name, item);
    mMsg_Set_item_str_art(window, str_no, item_name, mIN_ITEM_NAME_LEN, mIN_get_item_article(item));
}

extern void mSC_get_event_name_str(u8* buf, int buf_len, int soncho_event) {
    static int chg_string_idx[mSC_EVENT_NUM + 1] = {
        0,  // New Year's Day
        14, // Founder's Day
        8,  // Graduation Day
        3,  // April Fools' Day
        11, // "Town" Day
        7,  // Mother's Day
        24, // Sale Day
        4,  // Cherry Festival
        2,  // Sports Fair
        5,  // Nature Day
        6,  // Spring Cleaning
        9,  // Father's Day
        10, // Fishing Tourney
        1,  // Groundhog Day
        18, // Explorer's Day
        12, // Fireworks Show
        13, // Meteor Shower
        17, // Harvest Moon
        20, // Mayor's Day
        21, // Officer's Day
        16, // Sports Fair
        19, // Halloween
        22, // Fishing Tourney
        25, // Snow Day
        15, // Labor Day
        26, // Toy Day
        27, // New Year's Eve
        23, // Harvest Festival
        28  // birthday
    };

    mString_Load_StringFromRom(buf, buf_len, mString_SONCHO_EVENT_NAME_START + chg_string_idx[soncho_event & 0x7F]);
}

extern void mSC_event_name_set(u8 soncho_event) {
    u8 event_name_buf[mIN_ITEM_NAME_LEN];
    int ofs = 0; // for town day name

    if (soncho_event < mSC_EVENT_NUM) {
        if (soncho_event == mSC_EVENT_TOWN_DAY) {
            mLd_CopyLandName(event_name_buf, Save_Get(land_info).name);
            ofs = mMl_strlen(event_name_buf, LAND_NAME_SIZE, CHAR_SPACE);
        }

        mSC_get_event_name_str(event_name_buf + ofs, mIN_ITEM_NAME_LEN - ofs, soncho_event);
        mMsg_Set_item_str(mMsg_Get_base_window_p(), mMsg_ITEM_STR1, event_name_buf, mIN_ITEM_NAME_LEN);
    }
}

extern void mSC_set_free_str_number(int free_str_no, u32 num) {
    u8 number[mIN_ITEM_NAME_LEN];
    int fig;

    if (num >= 100) {
        fig = 3;
    } else if (num >= 10) {
        fig = 2;
    } else {
        fig = 1;
    }

    mFont_UnintToString(number, 3, num, fig, TRUE, FALSE, TRUE);
    mMsg_Set_free_str(mMsg_Get_base_window_p(), free_str_no, number, fig);
}

static int mSC_Radio_many_taisou_card() {
    int i;
    int cards;
    Private_c* priv = Common_Get(now_private);

    for (i = 0, cards = 0; i < 13; i++) {
        cards += mPr_GetPossessionItemSumWithCond(priv, ITM_EXCERCISE_CARD00 + i, mPr_ITEM_COND_NORMAL);
    }

    return cards;
}

static mActor_name_t mSC_Radio_have_taisou_card() {
    int i;
    Private_c* priv = Common_Get(now_private);

    for (i = 0; i < 13; i++) {
        int sum = mPr_GetPossessionItemSumWithCond(priv, ITM_EXCERCISE_CARD00 + i, mPr_ITEM_COND_NORMAL);
        
        if (sum > 0) {
            return ITM_EXCERCISE_CARD00 + i;
        }
    }

    return ITM_EXCERCISE_CARD00;
}

static int mSC_Radio_time_check() {
    Private_c* priv = Common_Get(now_private);
    int equal_date;

    if (Common_Get(time.rtc_time).year != priv->radiocard.last_date.year) {
        return 0;
    }

    equal_date = lbRTC_IsEqualDate(Common_Get(time.rtc_time).year, Common_Get(time.rtc_time).month,
                                   Common_Get(time.rtc_time).day, priv->radiocard.last_date.year,
                                   priv->radiocard.last_date.month, priv->radiocard.last_date.day);

    switch (equal_date) {
        case lbRTC_LESS:
            return mSC_RADIO_TIME_LESS;
        case lbRTC_EQUAL:
            return mSC_RADIO_TIME_SAME_DAY;
        case lbRTC_OVER:
            return mSC_RADIO_TIME_OVER;
        default:
            return mSC_RADIO_TIME_LESS;
    }
}

static int mSC_Radio_limit_check() {
    if (Common_Get(time.rtc_time).month >= lbRTC_AUGUST && Common_Get(time.rtc_time).day >= 19) {
        return FALSE;
    }

    return TRUE;
}

static void mSC_Radio_delete_taisou_card() {
    int i;
    Private_c* priv = Common_Get(now_private);

    for (i = 0; i < 13; i++) {
        int idx = mPr_GetPossessionItemIdxWithCond(priv, ITM_EXCERCISE_CARD00 + i, mPr_ITEM_COND_NORMAL);

        while (idx != -1) {
            mPr_SetPossessionItem(Common_Get(now_private), idx, EMPTY_NO, mPr_ITEM_COND_NORMAL); // probably a macro
            idx = mPr_GetPossessionItemIdxWithCond(priv, ITM_EXCERCISE_CARD00 + i, mPr_ITEM_COND_NORMAL);
        }
    }
}

static void mSC_Radio_change_taisou_card(mActor_name_t old_card, mActor_name_t new_card) {
    Private_c* priv = Common_Get(now_private);
    int idx = mPr_GetPossessionItemIdxWithCond(priv, old_card, mPr_ITEM_COND_NORMAL);

    if (idx != -1) {
        mPr_SetPossessionItem(Common_Get(now_private), idx, new_card, mPr_ITEM_COND_NORMAL); // again, probably a macro
    }
}

static void mSC_Radio_stamp_card(lbRTC_day_t days) {
    const lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    mPr_day_day_c* radiocard = &Common_Get(now_private)->radiocard;

    radiocard->last_date.year = rtc_time->year;
    radiocard->last_date.month = rtc_time->month;
    radiocard->last_date.day = rtc_time->day;
    radiocard->days = days;
}

static int mSC_Radio_msg(TAISOU_NPC0_ACTOR* taisou_actor, int idx) {
    return 0x3280 + taisou_actor->soncho_event * 10 + idx;
}

extern int mSC_Radio_Set_Talk_Proc(TAISOU_NPC0_ACTOR* taisou_actor) {
    u8 item_name[mIN_ITEM_NAME_LEN];
    mPr_day_day_c* radiocard = &Common_Get(now_private)->radiocard;
    int msg_no;

    taisou_actor->talk_proc = mSCR_TALK_9;
    if (taisou_actor->soncho_event == mSC_SPECIAL_EVENT_MORNING_AEROBICS) {
        int time_check = mSC_Radio_time_check();
        int num_cards = mSC_Radio_many_taisou_card();
        mActor_name_t card;
        int article;

        if (Common_Get(player_no) == mPr_FOREIGNER) {
            msg_no = 0x343B;
        } else if (time_check == mSC_RADIO_TIME_SAME_DAY) {
            msg_no = 0x3433;
            taisou_actor->talk_state = 18 + RANDOM(3);
            taisou_actor->talk_proc = mSCR_TALK_NEXT;
        } else {
            int action = mSCR_ACTION_TOO_LATE;

            if (num_cards <= 0) {
                int limit_check = mSC_Radio_limit_check();

                if (limit_check == FALSE && (radiocard->days == mSC_RADIO_DAYS || time_check == mSC_RADIO_TIME_LESS)) {
                    action = mSCR_ACTION_TOO_LATE;
                } else {
                    switch (time_check) {
                        case mSC_RADIO_TIME_LESS:
                            action = mSCR_ACTION_NEW_CARD;
                            break;

                        case mSC_RADIO_TIME_OVER: {
                            if (radiocard->days == (mSC_RADIO_DAYS - 1)) {
                                action = mSCR_ACTION_LOST_CARD_AND_FINISH;
                            } else if (radiocard->days < mSC_RADIO_DAYS) {
                                action = mSCR_ACTION_LOST_CARD;
                            } else {
                                action = mSCR_ACTION_NEW_CARD;
                            }
                            break;
                        }
                    }
                }
            } else if (num_cards > 1) {
                action = mSCR_ACTION_DELETE_OLD_CARD;
            } else {
                card = mSC_Radio_have_taisou_card();

                switch (time_check) {
                    case mSC_RADIO_TIME_LESS:
                        action = mSCR_ACTION_DELETE_OLD_CARD;
                        break;

                    case mSC_RADIO_TIME_SAME_DAY:
                        break;

                    case mSC_RADIO_TIME_OVER: {
                        radiocard->days = card - ITM_EXCERCISE_CARD00;
                        radiocard->days++;

                        if (radiocard->days >= mSC_RADIO_DAYS) {
                            action = mSCR_ACTION_FINISH_CARD;
                        } else {
                            action = mSCR_ACTION_STAMP_CARD;
                        }

                        break;
                    }
                }
            }

            switch (action) {
                case mSCR_ACTION_TOO_LATE: {
                    msg_no = 0x3437;
                    taisou_actor->talk_state = 22 + RANDOM(3);
                    taisou_actor->talk_proc = mSCR_TALK_NEXT;
                    break;
                }

                case mSCR_ACTION_DELETE_OLD_CARD: {
                    taisou_actor->talk_proc = mSCR_TALK_PICKUP_ALL;
                    msg_no = 0x343C;
                    mSC_Radio_delete_taisou_card();
                    break;
                }

                case mSCR_ACTION_NEW_CARD: {
                    taisou_actor->talk_state = mSCR_TALK_NEXT_INSPECTION;
                    msg_no = 0x3422;

                    if (mCD_calendar_event_check(Common_Get(time.rtc_time).year, Common_Get(time.rtc_time).month,
                                                 Common_Get(time.rtc_time).day, -1, taisou_actor->soncho_event)) {
                        msg_no = 0x3423;
                    }

                    if (mPr_GetPossessionItemSumWithCond(Common_Get(now_private), EMPTY_NO,
                                                              mPr_ITEM_COND_NORMAL) == 0) {
                        taisou_actor->talk_proc = mSCR_TALK_NEXT;
                    } else {
                        taisou_actor->talk_proc = mSCR_TALK_NEXT_INSPECTION;
                        taisou_actor->held_item = ITM_EXCERCISE_CARD00;
                        mPr_SetFreePossessionItem(Common_Get(now_private), ITM_EXCERCISE_CARD00, mPr_ITEM_COND_NORMAL);
                        mSC_Radio_stamp_card(0);
                        taisou_actor->talk_state++;
                    }

                    break;
                }

                case mSCR_ACTION_LOST_CARD: {
                    taisou_actor->talk_state = 14;
                    msg_no = 0x342E;
                    mSC_set_free_str_number(mMsg_FREE_STR0, radiocard->days + 2);

                    if (mCD_calendar_event_check(Common_Get(time.rtc_time).year, Common_Get(time.rtc_time).month,
                                                 Common_Get(time.rtc_time).day, -1, taisou_actor->soncho_event)) {
                        msg_no = 0x342F;
                    }

                    if (mPr_GetPossessionItemSumWithCond(Common_Get(now_private), EMPTY_NO,
                                                              mPr_ITEM_COND_NORMAL) == 0) {
                        taisou_actor->talk_proc = mSCR_TALK_NEXT;
                    } else {
                        taisou_actor->talk_proc = mSCR_TALK_NEXT_INSPECTION;
                        radiocard->days++;
                        taisou_actor->held_item = ITM_EXCERCISE_CARD00 + radiocard->days;
                        mPr_SetFreePossessionItem(Common_Get(now_private), taisou_actor->held_item,
                                                  mPr_ITEM_COND_NORMAL);
                        mSC_Radio_stamp_card(radiocard->days);
                        taisou_actor->talk_state++;
                    }

                    break;
                }

                case mSCR_ACTION_STAMP_CARD: {
                    taisou_actor->talk_proc = mSCR_TALK_INSPECTION;
                    card = mSC_Radio_have_taisou_card();
                    mSC_Radio_stamp_card(radiocard->days);
                    mSC_Radio_change_taisou_card(card, ITM_EXCERCISE_CARD00 + radiocard->days);
                    mSC_set_free_str_number(mMsg_FREE_STR0, radiocard->days + 1);
                    taisou_actor->talk_state = mSCR_TALK_NEXT;
                    msg_no = 0x3427;

                    break;
                }

                case mSCR_ACTION_FINISH_CARD: {
                    taisou_actor->talk_proc = mSCR_TALK_INSPECTION;
                    card = mSC_Radio_have_taisou_card();
                    mSC_Radio_stamp_card(radiocard->days);
                    taisou_actor->held_item = FTR_AEROBICS_RADIO;
                    mSC_Radio_change_taisou_card(card, taisou_actor->held_item);
                    mIN_copy_name_str(item_name, taisou_actor->held_item);
                    article = mIN_get_item_article(taisou_actor->held_item);
                    mMsg_Set_free_str_art(mMsg_Get_base_window_p(), mMsg_FREE_STR1, item_name, mIN_ITEM_NAME_LEN,
                                          article);
                    taisou_actor->talk_state = 9;
                    msg_no = 0x342A;

                    break;
                }

                case mSCR_ACTION_LOST_CARD_AND_FINISH: {
                    taisou_actor->talk_state = 28;
                    msg_no = 0x342E;
                    mSC_set_free_str_number(mMsg_FREE_STR0, radiocard->days + 2);

                    if (mCD_calendar_event_check(Common_Get(time.rtc_time).year, Common_Get(time.rtc_time).month,
                                                 Common_Get(time.rtc_time).day, -1, taisou_actor->soncho_event)) {
                        msg_no = 0x342F;
                    }

                    if (mPr_GetPossessionItemSumWithCond(Common_Get(now_private), EMPTY_NO,
                                                              mPr_ITEM_COND_NORMAL) == 0) {
                        taisou_actor->talk_proc = mSCR_TALK_NEXT;
                    } else {
                        taisou_actor->talk_proc = mSCR_TALK_NEXT_INSPECTION;
                        radiocard->days++;
                        taisou_actor->held_item = FTR_AEROBICS_RADIO;
                        mPr_SetFreePossessionItem(Common_Get(now_private), taisou_actor->held_item,
                                                  mPr_ITEM_COND_NORMAL);
                        mIN_copy_name_str(item_name, taisou_actor->held_item);
                        article = mIN_get_item_article(taisou_actor->held_item);
                        mMsg_Set_free_str_art(mMsg_Get_base_window_p(), mMsg_FREE_STR1, item_name, mIN_ITEM_NAME_LEN,
                                              article);
                        mSC_Radio_stamp_card(radiocard->days);
                        taisou_actor->talk_state--;
                    }

                    break;
                }

                default: {
                    msg_no = 0x3437;
                    taisou_actor->talk_state = 22 + RANDOM(3);
                    taisou_actor->talk_proc = mSCR_TALK_NEXT;
                    break;
                }
            }
        }
    } else if (Common_Get(player_no) == mPr_FOREIGNER) {
        msg_no = mSC_Radio_msg(taisou_actor, 9);
        taisou_actor->talk_proc = mSCR_TALK_8;
    } else if (mSC_trophy_get(taisou_actor->soncho_event) != FALSE) {
        if (mCD_calendar_event_check(Common_Get(time.rtc_time).year, Common_Get(time.rtc_time).month,
                                     Common_Get(time.rtc_time).day, -1, taisou_actor->soncho_event)) {
            msg_no = mSC_Radio_msg(taisou_actor, 6 + RANDOM(3));
        } else {
            msg_no = mSC_Radio_msg(taisou_actor, 5);
        }

        taisou_actor->talk_proc = mSCR_TALK_7;
    } else {
        taisou_actor->talk_proc = mSCR_TALK_BEFORE_GIVE;

        if (mCD_calendar_event_check(Common_Get(time.rtc_time).year, Common_Get(time.rtc_time).month,
                                     Common_Get(time.rtc_time).day, -1, taisou_actor->soncho_event)) {
            msg_no = mSC_Radio_msg(taisou_actor, 1);
        } else {
            msg_no = mSC_Radio_msg(taisou_actor, 0);
        }
    }

    return msg_no;
}

static void mSCR_talk_pickup_all(TAISOU_NPC0_ACTOR* taisou_actor, GAME_PLAY* play) {
    switch (mDemo_Get_OrderValue(mDemo_ORDER_NPC0, 9)) {
        case 1: {
            mPlib_request_main_give_type1((GAME*)play, ITM_EXCERCISE_CARD00, 7, FALSE, FALSE);
            mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 9, 2);
            mMsg_Set_LockContinue(mMsg_Get_base_window_p());
            mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 1, 3);
            break;
        }

        case 2: {
            if (Common_Get(clip).handOverItem_clip->master_actor == NULL) {
                mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
                mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 9, 0);
                taisou_actor->talk_proc = mSCR_TALK_9;
            }

            break;
        }
    }
}

static void mSCR_talk_inspection(TAISOU_NPC0_ACTOR* taisou_actor, GAME_PLAY* play) {
    int order = mDemo_Get_OrderValue(mDemo_ORDER_NPC0, 9);
    mMsg_Window_c* msg_win = mMsg_Get_base_window_p();
    mPr_day_day_c* radiocard = &Common_Get(now_private)->radiocard;

    switch (order) {
        case 1: {
            mPlib_request_main_give_type1((GAME*)play, ITM_EXCERCISE_CARD00, 8, FALSE, FALSE);
            mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 9, 2);
            mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 1, 3);
            mMsg_Set_continue_msg_num(msg_win, 0x3422 + taisou_actor->talk_state);
            taisou_actor->talk_state++;
            break;
        }

        case 2: {
            if (Common_Get(clip).handOverItem_clip->request_mode == aHOI_REQUEST_TRANS_WAIT) {
                mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 1, 3);
                Common_Get(clip).handOverItem_clip->player_after_mode = 8;
                mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 9, 3);
                mMsg_Unset_LockContinue(msg_win);
                taisou_actor->npc_actor_class.talk_info.default_animation = 30;
            }
            break;
        }

        case 3: {
            if ((mMsg_Get_msg_num(msg_win) == 0x342B || mMsg_Get_msg_num(msg_win) == 0x3428) &&
                mMsg_Check_MainNormalContinue(msg_win)) {
                mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 9, 4);
                mMsg_Set_LockContinue(mMsg_Get_base_window_p());
            }

            break;
        }

        case 4: {
            if (Common_Get(clip).handOverItem_clip->master_actor == NULL) {
                taisou_actor->npc_actor_class.talk_info.default_animation = -1;
                mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 9, 0);

                if (radiocard->days >= mSC_RADIO_DAYS) {
                    taisou_actor->talk_proc = mSCR_TALK_NEWCARD;
                } else {
                    taisou_actor->talk_proc = mSCR_TALK_9;
                }

                mMsg_Unset_LockContinue(msg_win);
                mMsg_Set_continue_msg_num(msg_win, 0x3422 + taisou_actor->talk_state);
                taisou_actor->talk_state++;
            }

            break;
        }
    }
}

static void mSCR_talk_newcard(TAISOU_NPC0_ACTOR* taisou_actor, GAME_PLAY* play) {
    int order = mDemo_Get_OrderValue(mDemo_ORDER_NPC0, 1);
    mMsg_Window_c* msg_win = mMsg_Get_base_window_p();

    if (order == 2) {
        mDemo_Set_OrderValue(mDemo_ORDER_NPC1, 0, taisou_actor->held_item);
        mDemo_Set_OrderValue(mDemo_ORDER_NPC1, 1, 7);
        mDemo_Set_OrderValue(mDemo_ORDER_NPC1, 2, 0);

        if (taisou_actor->talk_state == 28) {
            mMsg_Set_continue_msg_num(msg_win, 0x342D); /* dialog after giving aerobics radio */
        } else {
            mMsg_Set_continue_msg_num(msg_win, 0x3422 + taisou_actor->talk_state);
            taisou_actor->talk_state++;
        }

        taisou_actor->talk_proc = mSCR_TALK_9;
    }
}

static void mSCR_talk_before_give(TAISOU_NPC0_ACTOR* taisou_actor, GAME_PLAY* play) {
    mMsg_Window_c* msg_win = mMsg_Get_base_window_p();

    if (mMsg_Check_MainNormalContinue(msg_win)) {
        if (mPr_GetPossessionItemSumWithCond(Common_Get(now_private), EMPTY_NO, mPr_ITEM_COND_NORMAL) == 0) {
            mMsg_Set_continue_msg_num(msg_win, mSC_Radio_msg(taisou_actor, 2));
            taisou_actor->talk_proc = mSCR_TALK_9;
        } else {
            mMsg_Set_continue_msg_num(msg_win, mSC_Radio_msg(taisou_actor, 3));
            taisou_actor->talk_proc = mSCR_TALK_GIVE;
        }
    }
}

static void mSCR_talk_give(TAISOU_NPC0_ACTOR* taisou_actor, GAME_PLAY* play) {
    int order = mDemo_Get_OrderValue(mDemo_ORDER_NPC0, 1);

    if (order == 2) {
        mActor_name_t trophy_item = mSC_trophy_item(taisou_actor->soncho_event);

        mSC_item_string_set(trophy_item, mMsg_ITEM_STR0);
        mDemo_Set_OrderValue(mDemo_ORDER_NPC1, 0, trophy_item);
        mDemo_Set_OrderValue(mDemo_ORDER_NPC1, 1, 7);
        mDemo_Set_OrderValue(mDemo_ORDER_NPC1, 2, 0);
        mPr_SetFreePossessionItem(Common_Get(now_private), trophy_item, mPr_ITEM_COND_NORMAL);
        mSC_trophy_set(taisou_actor->soncho_event);
        taisou_actor->talk_proc = mSCR_TALK_9;
    }
}

static void mSCR_talk_next(TAISOU_NPC0_ACTOR* taisou_actor, GAME_PLAY* play) {
    mMsg_Window_c* msg_win = mMsg_Get_base_window_p();

    if (mMsg_Check_MainNormalContinue(msg_win)) {
        mMsg_Set_continue_msg_num(msg_win, 0x3422 + taisou_actor->talk_state);
        taisou_actor->talk_proc++;
        taisou_actor->talk_state++;
    }
}

typedef void (*mSCR_TALK_PROC)(TAISOU_NPC0_ACTOR*, GAME_PLAY*);

extern void mSC_Radio_Talk_Proc(TAISOU_NPC0_ACTOR* taisou_actor, GAME_PLAY* play) {
    static mSCR_TALK_PROC proc[mSCR_TALK_NUM] = { &mSCR_talk_pickup_all,
                                                  &mSCR_talk_inspection,
                                                  &mSCR_talk_next,
                                                  &mSCR_talk_newcard,
                                                  &mSCR_talk_before_give,
                                                  &mSCR_talk_give,
                                                  &mSCR_talk_next,
                                                  (mSCR_TALK_PROC)&none_proc1,
                                                  (mSCR_TALK_PROC)&none_proc1,
                                                  (mSCR_TALK_PROC)&none_proc1 };

    (*proc[taisou_actor->talk_proc])(taisou_actor, play);
}

extern int mSC_LightHouse_get_period(lbRTC_time_c* time) {
    lbRTC_time_c lh_start_time;
    lbRTC_time_c lh_end_time;
    lbRTC_time_c lh_max_time;
    lbRTC_ymd_c* renew_time = &Save_Get(LightHouse).renew_time;
    int equal;

    if (Save_Get(LightHouse).renew_time.day == 0) {
        return mSC_LIGHTHOUSE_PERIOD_NONE;
    }

    mTM_ymd_2_time(&lh_start_time, renew_time);
    lbRTC_TimeCopy(&lh_end_time, &lh_start_time);
    lbRTC_Add_DD(&lh_end_time, lbRTC_WEEK);
    lbRTC_TimeCopy(&lh_max_time, &lh_start_time);
    lbRTC_Add_DD(&lh_max_time, mSC_LIGHTHOUSE_DAYS);

    equal = lbRTC_IsEqualDate(lh_start_time.year, lh_start_time.month, lh_start_time.day, time->year, time->month,
                              time->day);

    if (equal == lbRTC_OVER) {
        return mSC_LIGHTHOUSE_PERIOD_NONE; // start date is after the current date (time travelled backwards)
    }

    if (equal == lbRTC_EQUAL) {
        return mSC_LIGHTHOUSE_PERIOD_0; // start date is current date
    }

    if (lbRTC_IsEqualDate(lh_end_time.year, lh_end_time.month, lh_end_time.day, time->year, time->month, time->day) !=
        lbRTC_LESS) {
        return mSC_LIGHTHOUSE_PERIOD_1;
    } else if (lbRTC_IsEqualDate(lh_max_time.year, lh_max_time.month, lh_max_time.day, time->year, time->month,
                                 time->day) != lbRTC_LESS) {
        return mSC_LIGHTHOUSE_PERIOD_2;
    }

    return mSC_LIGHTHOUSE_PERIOD_NONE;
}

extern int mSC_LightHouse_day(const lbRTC_time_c* time) {
    lbRTC_time_c lh_start_time;
    int days;
    lbRTC_ymd_c* renew_time = &Save_Get(LightHouse).renew_time;

    if (Save_Get(LightHouse).renew_time.day == 0) {
        return 0;
    }

    mTM_ymd_2_time(&lh_start_time, renew_time);

    if (lbRTC_IsOverTime(&lh_start_time, time) == lbRTC_LESS) {
        return 0;
    }

    days = lbRTC_GetIntervalDays(&lh_start_time, time) - 1;

    if (days < 0) {
        return 0;
    }

    return days <= (lbRTC_WEEK - 1) ? days : (lbRTC_WEEK - 1);
}

extern int mSC_LightHouse_Event_Check(int player_no) {
    LightHouse_c* lh = Save_GetPointer(LightHouse);

    if (player_no == -1) {
        player_no = Common_Get(player_no);
    }

    if (player_no >= mPr_FOREIGNER) {
        return mSC_LIGHTHOUSE_EVENT_NONE;
    }

    if (mSC_LightHouse_get_period(Common_GetPointer(time.rtc_time)) != mSC_LIGHTHOUSE_PERIOD_2) {
        return mSC_LIGHTHOUSE_EVENT_NONE;
    }

    if ((lh->players_completed & (1 << player_no)) != 0) {
        return mSC_LIGHTHOUSE_EVENT_NONE;
    }

    if ((lh->days_switched_on & 0x7F) == 0x7F) {
        if ((lh->players_quest_started & (u8)(1 << (player_no + 4))) != 0) {
            if (lh->renew_time.month == lbRTC_JANUARY) {
                return mSC_LIGHTHOUSE_EVENT_JAN_CONTRIBUTED;
            } else {
                return mSC_LIGHTHOUSE_EVENT_FEB_CONTRIBUTED;
            }
        }
    } else if ((lh->players_quest_started & (u8)(1 << Common_Get(player_no))) != 0) {
        if (lh->renew_time.month == lbRTC_JANUARY) {
            return mSC_LIGHTHOUSE_EVENT_JAN_STARTED;
        } else {
            return mSC_LIGHTHOUSE_EVENT_FEB_STARTED;
        }
    }

    return mSC_LIGHTHOUSE_EVENT_NONE;
}

extern void mSC_LightHouse_Event_Clear(int player_no) {
    LightHouse_c* lh = Save_GetPointer(LightHouse);

    if (player_no == -1) {
        player_no = Common_Get(player_no);
    }

    if (player_no < mPr_FOREIGNER) {
        int check;

        lh->players_completed |= (1 << player_no);
        check = mSC_LightHouse_Event_Check(player_no);

        if (check == 2 || check == 4) {
            lh->players_completed |= 0b1111;
        }
    }
}

extern mActor_name_t mSC_LightHouse_Event_Present_Item(u32 player_no) {
    if (Save_Get(LightHouse).renew_time.month == lbRTC_JANUARY) {
        return FTR_LIGHTHOUSE_MODEL;
    }

    return FTR_CHOCOLATES;
}

static void mSC_LightHouse_clear_data() {
    mem_clear((u8*)Save_GetPointer(LightHouse), sizeof(LightHouse_c), 0);
}

extern int mSC_LightHouse_Event_Start() {
    LightHouse_c* lh = Save_GetPointer(LightHouse);
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    if (lh->renew_time.day == 0) {
        return TRUE;
    }

    if (mSC_LightHouse_get_period(rtc_time) != mSC_LIGHTHOUSE_PERIOD_NONE) {
        return FALSE;
    }

    mSC_LightHouse_clear_data();
    return TRUE;
}

extern int mSC_LightHouse_Talk_After_Check() {
    LightHouse_c* lh = Save_GetPointer(LightHouse);
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    if (mSC_LightHouse_get_period(rtc_time) == mSC_LIGHTHOUSE_PERIOD_NONE) {
        return FALSE;
    }

    return (lh->players_quest_started & 0b1111) != 0;
}

extern void mSC_LightHouse_Quest_Start() {
    LightHouse_c* lh = Save_GetPointer(LightHouse);
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    mSC_LightHouse_clear_data();
    mTM_set_renew_time(&lh->renew_time, rtc_time);
    lh->players_quest_started |= (u8)(1 << Common_Get(player_no));
}

extern int mSC_LightHouse_Switch_Check() {
    lbRTC_time_c adjusted_rtc_time;
    LightHouse_c* lh = Save_GetPointer(LightHouse);
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int day;

    lbRTC_TimeCopy(&adjusted_rtc_time, rtc_time);
    lbRTC_Sub_hh(&adjusted_rtc_time, 6);

    if (lh->renew_time.day == 0) {
        return TRUE;
    }

    if (mSC_LightHouse_get_period(&adjusted_rtc_time) != mSC_LIGHTHOUSE_PERIOD_1) {
        return TRUE;
    }

    day = mSC_LightHouse_day(&adjusted_rtc_time);
    return (lh->days_switched_on & (1 << day)) != 0;
}

extern int mSC_LightHouse_In_Check() {
    lbRTC_time_c time;
    LightHouse_c* lh = Save_GetPointer(LightHouse);
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int day;

    if (Common_Get(player_no) >= mPr_FOREIGNER) {
        return FALSE;
    }

    if (mEv_CheckFirstJob() != FALSE) {
        return FALSE;
    }

    lbRTC_TimeCopy(&time, rtc_time);

    if (lh->renew_time.day == 0) {
        return FALSE;
    }

    if (mSC_LightHouse_get_period(&time) != mSC_LIGHTHOUSE_PERIOD_1) {
        return FALSE;
    }

    if (time.hour < 18 || time.hour >= 22) {
        return FALSE;
    }

    day = mSC_LightHouse_day(&time);
    return (lh->days_switched_on & (1 << day)) == 0;
}

extern void mSC_LightHouse_Switch_On() {
    LightHouse_c* lh = Save_GetPointer(LightHouse);
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int day;
    int player_no;

    day = mSC_LightHouse_day(rtc_time);
    lh->days_switched_on |= (1 << day);
    player_no = Common_Get(player_no);

    if (player_no < mPr_FOREIGNER) {
        lh->players_quest_started |= (u8)(1 << (player_no + 4));
    }
}

extern void mSC_LightHouse_Delete_Player(int player_no) {
    Save_Get(LightHouse).players_quest_started &= ~(u8)(1 << (player_no + 4));
}

extern int mSC_LightHouse_travel_check() {
    switch (mSC_LightHouse_get_period(Common_GetPointer(time.rtc_time))) {
        case mSC_LIGHTHOUSE_PERIOD_1:
            return TRUE;
        default:
            return FALSE;
    }
}

extern void mSC_change_player_freeze(GAME_PLAY* play) {
    if (mPlib_get_player_actor_main_index((GAME*)play) != mPlayer_INDEX_DEMO_WAIT) {
        mPlib_request_main_demo_wait_type1((GAME*)play, 0, NULL);
    }
}

extern u32 mSC_check_ArbeitPlayer() {
    return mSC_trophy_get(32);
}
