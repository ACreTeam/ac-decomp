#include "m_fishrecord.h"

#include "libultra/libultra.h"
#include "m_lib.h"
#include "m_event_map_npc.h"
#include "m_font.h"
#include "m_house.h"
#include "m_item_name.h"
#include "m_handbill.h"
#include "m_malloc.h"
#include "m_common_data.h"

static void mFR_delete_record(mFR_record_c* record) {
    mem_clear((u8*)record, sizeof(mFR_record_c), 0);
}

static void mFR_delete_after_record(lbRTC_ymd_c* after) {
    int i;

    for (i = 0; i < mFR_RECORD_NUM; i++) {
        mFR_record_c* record = Save_Get(fishRecord) + i;

        int equal = lbRTC_IsEqualDate(after->year, after->month, after->day, record->time.year, record->time.month,
                                      record->time.day);

        if (equal == lbRTC_LESS) {
            mFR_delete_record(record);
        }
    }
}

static void mFR_delete_npc_record(lbRTC_ymd_c* date) {
    int i;

    for (i = 0; i < mFR_RECORD_NUM; i++) {
        mFR_record_c* record = Save_Get(fishRecord) + i;

        if (record->size != 0 &&
            (date == NULL || lbRTC_IsEqualDate(date->year, date->month, date->day, record->time.year,
                                               record->time.month, record->time.day) != lbRTC_EQUAL) &&
            mPr_GetPrivateIdx(&record->pid) == -1) {
            mFR_delete_record(record);
        }
    }
}

static mFR_record_c* mFR_get_record(lbRTC_ymd_c date) {
    int i;

    for (i = 0; i < mFR_RECORD_NUM; i++) {
        mFR_record_c* record = Save_Get(fishRecord) + i;

        int equal =
            lbRTC_IsEqualDate(date.year, date.month, date.day, record->time.year, record->time.month, record->time.day);

        if (equal == lbRTC_EQUAL) {
            return record;
        }
    }

    return NULL;
}

static mFR_record_c* mFR_get_free_record() {
    int i;

    for (i = 0; i < mFR_RECORD_NUM; i++) {
        mFR_record_c* record = Save_Get(fishRecord) + i;

        if (record->size == 0) {
            return record;
        }
    }

    return NULL;
}

static mFR_record_c* mFR_recycle_record() {
    int i;
    mFR_record_c* record;
    mFR_record_c* recycle = Save_GetPointer(fishRecord[0]);

    for (i = 1; i < mFR_RECORD_NUM; i++) {
        int equal;

        record = Save_Get(fishRecord) + i;
        equal = lbRTC_IsEqualDate(recycle->time.year, recycle->time.month, recycle->time.day, record->time.year,
                                  record->time.month, record->time.day);

        if (equal == lbRTC_OVER) {
            recycle = record;
        }
    }

    mFR_delete_record(recycle);
    return recycle;
}

static mFR_record_c* mFR_new_record(lbRTC_ymd_c date) {
    mFR_record_c* new_record;

    mFR_delete_after_record(&date);
    mFR_delete_npc_record(&date);

    new_record = mFR_get_free_record();
    if (new_record != NULL) {
        return new_record;
    } else {
        return mFR_recycle_record();
    }
}

extern void mEv_fishRecord_set(PersonalID_c* pid, int size) {
    lbRTC_ymd_c date;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    mFR_record_c* record;

    mTM_set_renew_time(&date, rtc_time);
    record = mFR_get_record(date);

    if (record == NULL) {
        record = mFR_new_record(date);
    }

    mPr_CopyPersonalID(&record->pid, pid);
    record->size = size;
    lbRTC_TimeCopy(&record->time, rtc_time);
}

extern int mFR_fish_rndsize(int fish_size) {
    f32 rng = fqrand();

    switch (fish_size) {
        case mFR_SIZE_LARGE:
            return (50.0f + 20.0f * rng * rng) / 2.54f;
        case mFR_SIZE_MEDIUM:
            return (30.0f + 20.0f * rng) / 2.54f;
        default: /* mFR_SIZE_SMALL */
            return (30.0f - 20.0f * rng * rng) / 2.54f;
    }
}

extern int mFR_make_NpcRecord(lbRTC_hour_t hour) {
    int rand;
    if (hour < 9) {
        return (int)mFR_fish_rndsize(mFR_SIZE_SMALL);
    } else if (hour < 15) {
        rand = RANDOM(2);
        return (int)mFR_fish_rndsize(rand); /* 50/50 mFR_SIZE_SMALL, mFR_SIZE_MEDIUM */
    } else {
        rand = RANDOM(3);
        return (int)mFR_fish_rndsize(rand); /* equal chance for all sizes */
    }
}

static int mEv_fishRecord_local(PersonalID_c* pid, int* record_size, lbRTC_time_c* record_set_time,
                                int player_record_size) {
    static u8 l_name[] = { 0x98, 0xA6, 0x8F, 0xA1, 0x20 }; /* Untranslated JP, クニッチ */

    u8 name[ANIMAL_NAME_LEN];
    mActor_name_t selected_npc;
    lbRTC_time_c l_record_time;

    fqrand(); /* unused call to fqrand..? */
    lbRTC_TimeCopy(&l_record_time, record_set_time);

    /* Adjust time to 5:50 PM */
    l_record_time.hour = 17;
    l_record_time.min = 50;
    l_record_time.sec = 0;

    *record_size = 0;

    /* Roll potential new record size for every 30 minutes between the last record set time and 5:50PM */
    while (lbRTC_IsOverTime(&l_record_time, record_set_time) == lbRTC_LESS) {
        /* Roll a potential new record size set by an NPC */
        int npc_record = mFR_make_NpcRecord(record_set_time->hour);

        if (npc_record > *record_size) {
            *record_size = npc_record;
        }

        lbRTC_Add_mm(record_set_time, 30); // add 30 minutes
    }

    /* Adjust set time to 6:00PM */
    record_set_time->hour = 18;
    record_set_time->min = 0;
    record_set_time->sec = 0;

    if (*record_size <= player_record_size) {
        return FALSE;
    } else {
        mPr_ClearPersonalID(pid);
        if (mEvMN_GetJointEventRandomNpc(&selected_npc) == TRUE) {
            mNpc_GetNpcWorldNameTableNo(name, selected_npc);
        } else {
            mNpc_GetRandomAnimalName(name);
        }

        mem_copy(pid->player_name, name, ANIMAL_NAME_LEN);
        mLd_ClearLandName(pid->land_name);
        mem_copy(pid->land_name, l_name, sizeof(l_name));

        return TRUE;
    }
}

static void mEv_fishRecord_holder1(PersonalID_c* pid, int* size, mFR_record_c* record) {
    PersonalID_c record_id;
    int record_size;

    if (mEv_fishRecord_local(&record_id, &record_size, &record->time, record->size) == FALSE) {
        /* Player wins */
        mPr_CopyPersonalID(pid, &Save_GetPointer(fishRecord[0])->pid);
        *size = Save_GetPointer(fishRecord[0])->size;
    } else {
        /* NPC wins */
        record->size = record_size;
        mPr_CopyPersonalID(&record->pid, &record_id);
        *size = record_size;
        mPr_CopyPersonalID(pid, &record_id);
    }
}

static void mEv_fishRecord_holder2(PersonalID_c* pid, int* size) {
    /* NPC only win */
    lbRTC_time_c time;

    lbRTC_TimeCopy(&time, Common_GetPointer(time.rtc_time));
    time.hour = 6;
    time.min = 0;
    time.sec = 0;

    mEv_fishRecord_local(pid, size, &time, 0);
}

extern void mEv_fishRecord_holder(PersonalID_c* winning_pid, u32* winning_size, const lbRTC_ymd_c* contest_date) {
    int i;

    for (i = 0; i < mFR_RECORD_NUM; i++) {
        mFR_record_c* record = Save_Get(fishRecord) + i;

        if (record->time.year == contest_date->year && record->time.month == contest_date->month &&
            record->time.day == contest_date->day) {
            mEv_fishRecord_holder1(winning_pid, (int*)winning_size,
                                   record); /* found an existing record for this fishing contest */
            return;
        }
    }

    /* No record found for this fishing contest so generate a fake one */
    mEv_fishRecord_holder2(winning_pid, (int*)winning_size);
}

static lbRTC_ymd_c* mEv_fishday_day(lbRTC_year_t year, lbRTC_month_t month, int week) {
    static lbRTC_ymd_c ymd;

    int weekday;
    int day;

    weekday = lbRTC_Week(year, month, lbRTC_WEEK);
    ymd.year = year;
    ymd.month = month;
    day = (week * lbRTC_WEEK) + lbRTC_WEEK - weekday;

    if (day > lbRTC_GetDaysByMonth(ymd.year, ymd.month)) {
        return NULL;
    } else {
        ymd.day = day;
        return &ymd;
    }
}

extern int mEv_fishday(lbRTC_ymd_c* dates, lbRTC_time_c* time) {
    lbRTC_time_c l_time;
    lbRTC_ymd_c ymd;
    int free_dates;
    int i;
    lbRTC_ymd_c* fishing_day_ymd_p;

    lbRTC_TimeCopy(&l_time, time);
    lbRTC_Add_hh(&l_time, 6);
    ymd.year = l_time.year;
    ymd.month = l_time.month;
    ymd.day = l_time.day;
    free_dates = 4;

    if (ymd.month >= lbRTC_NOVEMBER) {
        for (i = 4; i >= 0; i--) {
            fishing_day_ymd_p = mEv_fishday_day(ymd.year, lbRTC_NOVEMBER, i);

            if (fishing_day_ymd_p != NULL && (ymd.month > lbRTC_NOVEMBER || ymd.day > fishing_day_ymd_p->day)) {
                lbRTC_ymd_c* week_date = dates + free_dates;

                week_date->year = fishing_day_ymd_p->year;
                week_date->month = fishing_day_ymd_p->month;
                week_date->day = fishing_day_ymd_p->day;

                if (free_dates <= 0) {
                    return TRUE;
                }

                free_dates--;
            }
        }
    }

    if (ymd.month >= lbRTC_JUNE) {
        for (i = 4; i >= 0; i--) {
            fishing_day_ymd_p = mEv_fishday_day(ymd.year, lbRTC_JUNE, i);

            if (fishing_day_ymd_p != NULL && (ymd.month > lbRTC_JUNE || ymd.day > fishing_day_ymd_p->day)) {
                lbRTC_ymd_c* week_date = dates + free_dates;

                week_date->year = fishing_day_ymd_p->year;
                week_date->month = fishing_day_ymd_p->month;
                week_date->day = fishing_day_ymd_p->day;

                if (free_dates <= 0) {
                    return TRUE;
                }

                free_dates--;
            }
        }
    }

    /* Go through previous year */
    lbRTC_Sub_YY(&l_time, 1);
    ymd.year = l_time.year;

    for (i = 4; i >= 0; i--) {
        fishing_day_ymd_p = mEv_fishday_day(ymd.year, lbRTC_NOVEMBER, i);

        if (fishing_day_ymd_p != NULL) {
            lbRTC_ymd_c* week_date = dates + free_dates;

            week_date->year = fishing_day_ymd_p->year;
            week_date->month = fishing_day_ymd_p->month;
            week_date->day = fishing_day_ymd_p->day;

            if (free_dates <= 0) {
                return TRUE;
            }

            free_dates--;
        }
    }

    for (i = 4; i >= 0; i--) {
        fishing_day_ymd_p = mEv_fishday_day(ymd.year, lbRTC_JUNE, i);

        if (fishing_day_ymd_p != NULL) {
            lbRTC_ymd_c* week_date = dates + free_dates;

            week_date->year = fishing_day_ymd_p->year;
            week_date->month = fishing_day_ymd_p->month;
            week_date->day = fishing_day_ymd_p->day;

            if (free_dates <= 0) {
                return TRUE;
            }

            free_dates--;
        }
    }

    return FALSE;
}

static void mFR_swap_record(mFR_record_c* r0, mFR_record_c* r1) {
    mFR_record_c temp;

    bcopy(r0, &temp, sizeof(mFR_record_c));
    bcopy(r1, r0, sizeof(mFR_record_c));
    bcopy(&temp, r1, sizeof(mFR_record_c));
}

static void mFR_sort_record() {
    int i;
    int j;
    mFR_record_c* records = Save_Get(fishRecord);

    for (i = 0; i < mFR_RECORD_NUM - 1; i++) {
        for (j = i + 1; j < mFR_RECORD_NUM; j++) {
            if (records[j].size != 0 &&
                (records[j].size == 0 ||
                 lbRTC_IsEqualDate(records[i].time.year, records[i].time.month, records[i].time.day,
                                   records[j].time.year, records[j].time.month, records[j].time.day) == lbRTC_OVER)) {
                mFR_swap_record(&records[i], &records[j]);
            }
        }
    }
}

static int mFR_Fishmail_send_post(PersonalID_c* pid, Mail_c* mail) {
    int arrange_idx = mHS_get_arrange_idx(mPr_GetPrivateIdx(pid)) & 3;
    int free_mail_idx = mMl_chk_mail_free_space(Save_Get(homes[arrange_idx]).mailbox, HOME_MAILBOX_SIZE);

    if (free_mail_idx >= 0) {
        mMl_copy_mail(Save_Get(homes[arrange_idx]).mailbox + free_mail_idx, mail);
        return TRUE;
    }

    return FALSE;
}

static int mFR_Fishmail_send_postoffice(PersonalID_c* pid, Mail_c* mail) {
    if (mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE) {
        mPO_receipt_proc(mail, mPO_SENDTYPE_MAIL);
        return TRUE;
    }

    return FALSE;
}

static void mFR_GetFishPresentMail(mFR_record_c* record, Mail_c* mail) {
    mActor_name_t present;
    u8 present_name[mIN_ITEM_NAME_LEN];
    int header_back_start;

    mMl_clear_mail(mail);
    present = mSP_SelectFishginPresent(mPr_GetPrivateIdx(&record->pid));
    mIN_copy_name_str(present_name, present);
    mHandbill_Set_free_str(mHandbill_FREE_STR0, present_name, mIN_ITEM_NAME_LEN);
    mHandbill_Load_HandbillFromRom(mail->content.header, &header_back_start, mail->content.footer, mail->content.body,
                                   0x23E + (((record->time.day - 1) / 7) & 3));

    mail->content.header_back_start = header_back_start;
    mail->content.font = mMl_FONT_RECV;
    mail->content.mail_type = mMl_TYPE_FISHING_CONTENST;
    mail->present = present;
    mail->content.paper_type = 15; // deep sea paper
    mPr_CopyPersonalID(&mail->header.recipient.personalID, &record->pid);
    mail->header.recipient.type = mMl_NAME_TYPE_PLAYER;
}

static void mFR_Fishmail_send() {
    int i;
    mFR_record_c* record;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    Mail_c* mail;

    mail = (Mail_c*)zelda_malloc(sizeof(Mail_c));

    if (mail != NULL) {
        for (i = 0; i < mFR_RECORD_NUM; i++) {
            record = Save_Get(fishRecord) + i;

            if (record->size > 0 &&                      /* used record */
                mPr_GetPrivateIdx(&record->pid) != -1 && /* record holder isn't an NPC or from out of town */
                lbRTC_IsOverTime(&record->time, rtc_time) == lbRTC_OVER /* record happened in the past */
            ) {
                mFR_GetFishPresentMail(record, mail);

                /* Try sending the mail to both the recipient's mailbox and the post office */
                if (mFR_Fishmail_send_post(&record->pid, mail) != FALSE) {
                    mFR_delete_record(record);
                } else if (mFR_Fishmail_send_postoffice(&record->pid, mail) != FALSE) {
                    mFR_delete_record(record);
                }
            }
        }

        zelda_free(mail);
    }
}

static void mFR_fishRecord_last_holder() {
    mFR_record_c* record;
    int i;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    PersonalID_c record_holder;
    int record_size;

    for (i = 0; i < mFR_RECORD_NUM; i++) {
        record = Save_Get(fishRecord) + i;

        if (record->size > 0 && lbRTC_IsOverTime(&record->time, rtc_time) == lbRTC_OVER) {
            int new_record = mEv_fishRecord_local(&record_holder, &record_size, &record->time, record->size);

            if (new_record) {
                record->size = record_size;
                mPr_CopyPersonalID(&record->pid, &record_holder);
            }
        }
    }
}

extern void mFR_fishmail() {
    lbRTC_ymd_c now;

    mTM_set_renew_time(&now, Common_GetPointer(time.rtc_time));
    mFR_delete_after_record(&now);
    mFR_fishRecord_last_holder();
    mFR_delete_npc_record(&now);
    mFR_sort_record();
    mFR_Fishmail_send();
}
