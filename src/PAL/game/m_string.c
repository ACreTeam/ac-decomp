#include "m_string.h"

#include "m_msg.h"
#include "jsyswrap.h"
#include "m_lib.h"
#include "m_font.h"

static u32 String_rom_start;

extern void mString_aram_init() {
    String_rom_start = JW_GetAramAddress(RESOURCE_STRING);
}

static void mString_CutTag(u8* buf, int len) {
    int i = 0;
    char c;
    int sz;
    u8* buf_p;
    int cut;

    while (i < len) {
        buf_p = buf + i;
        c = *buf_p;
        sz = mFont_CodeSize_get(buf_p);
        cut = FALSE;

        if ((u8)c == CHAR_MESSAGE_TAG && mFont_Check_TagId(buf_p, 3, mFont_TAG_GROUP_GRM, mFont_TAG_GRM_STRING_INFO)) {
            mMsg_MoveDataCut(buf, i, i + sz, len, TRUE);
            cut = TRUE;
        }

        if (!cut) {
            i += sz;
        }
    }
}

extern void mString_Load_StringFromRom(u8* dst, int dst_len, int str_no) {
    mMsg_bmg_info_c bmg_info;

    mMsgLoad_bmg_init(&bmg_info, String_rom_start, str_no, dst, dst_len);
    if (mMsgLoad_bmg_load(&bmg_info)) {
        mem_clear(dst + bmg_info.load_size, dst_len - bmg_info.load_size, CHAR_SPACE);
    }
}

extern void mString_Load_StringFromRom_CutTag(u8* dst, int dst_len, int str_no) {
    u8 buffer[mString_TAG_BUFFER_SIZE];

    mString_Load_StringFromRom(buffer, sizeof(buffer), str_no);
    mString_CutTag(buffer, sizeof(buffer));
    mem_clear(dst, dst_len, CHAR_SPACE);
    if (dst_len > mString_TAG_BUFFER_SIZE) {
        dst_len = sizeof(buffer);
    }
    mFont_CopyStrings(dst, buffer, dst_len);
}

extern int mString_Load_YearStringFromRom(u8* dst, lbRTC_year_t year) {
    if (year < lbRTC_YEAR_MIN || year > lbRTC_YEAR_MAX) {
        year = GAME_YEAR_MIN;
    }

    return mFont_UnintToString(dst, mString_DEFAULT_STR_SIZE, year, mString_DEFAULT_STR_SIZE, TRUE, FALSE, FALSE);
}

extern int mString_Load_YearStringFromRom_CutTag(u8* dst, lbRTC_year_t year) {
    mString_Load_YearStringFromRom(dst, year);
    mString_CutTag(dst, mString_DEFAULT_STR_SIZE);
    return mMsg_Get_Length_String(dst, mString_DEFAULT_STR_SIZE);
}

extern int mString_Load_MonthStringFromRom(u8* dst, lbRTC_month_t month) {
    if (month < lbRTC_JANUARY || month > lbRTC_DECEMBER) {
        month = lbRTC_JANUARY;
    }

    mString_Load_StringFromRom(dst, mString_DEFAULT_STR_SIZE, mString_MONTH_START + month - 1);
    return mMsg_Get_Length_String(dst, mString_DEFAULT_STR_SIZE);
}

extern int mString_Load_MonthStringFromRom_CutTag(u8* dst, lbRTC_month_t month) {
    mString_Load_MonthStringFromRom(dst, month);
    mString_CutTag(dst, mString_DEFAULT_STR_SIZE);
    return mMsg_Get_Length_String(dst, mString_DEFAULT_STR_SIZE);
}

extern int mString_Load_WeekStringFromRom(u8* dst, lbRTC_weekday_t weekday) {
    if (weekday > lbRTC_SATURDAY) {
        weekday = lbRTC_SUNDAY;
    }

    mString_Load_StringFromRom(dst, mString_DEFAULT_STR_SIZE, mString_WEEKDAY_START + weekday);
    return mMsg_Get_Length_String(dst, mString_DEFAULT_STR_SIZE);
}

extern int mString_Load_WeekStringFromRom_CutTag(u8* dst, lbRTC_weekday_t weekday) {
    mString_Load_WeekStringFromRom(dst, weekday);
    mString_CutTag(dst, mString_DEFAULT_STR_SIZE);
    return mMsg_Get_Length_String(dst, mString_DEFAULT_STR_SIZE);
}

extern int mString_Load_DayStringFromRom(u8* dst, lbRTC_day_t day) {
    if (day < 1 || day > 31) {
        day = 1;
    }

    mString_Load_StringFromRom(dst, mString_DEFAULT_STR_SIZE, mString_DAY_START + day - 1);
    return mMsg_Get_Length_String(dst, mString_DEFAULT_STR_SIZE);
}

extern int mString_Load_DayStringFromRom_CutTag(u8* dst, lbRTC_day_t day) {
    mString_Load_DayStringFromRom(dst, day);
    mString_CutTag(dst, mString_DEFAULT_STR_SIZE);
    return mMsg_Get_Length_String(dst, mString_DEFAULT_STR_SIZE);
}

extern int mString_Load_HourStringFromRom(u8* dst, lbRTC_hour_t hour) {
    return mString_Load_HourStringFromRom2(dst, hour);
}

extern int mString_Load_HourStringFromRom2(u8* dst, lbRTC_hour_t hour) {
    if (hour >= 24) {
        hour = 0;
    }

    return mFont_UnintToString(dst, mString_DEFAULT_STR_SIZE, hour, 2, TRUE, FALSE, FALSE);
}

extern int mString_Load_HourStringFromRom2_CutTag(u8* dst, lbRTC_hour_t hour) {
    mString_Load_HourStringFromRom2(dst, hour);
    mString_CutTag(dst, mString_DEFAULT_STR_SIZE);
    return mMsg_Get_Length_String(dst, mString_DEFAULT_STR_SIZE);
}

extern int mString_Load_MinStringFromRom(u8* dst, lbRTC_min_t min) {
    if (min > 59) {
        min = 0;
    }

    return mFont_UnintToString(dst, mString_DEFAULT_STR_SIZE, min, 2, TRUE, TRUE, TRUE);
}

extern int mString_Load_MinStringFromRom_CutTag(u8* dst, lbRTC_min_t min) {
    mString_Load_MinStringFromRom(dst, min);
    mString_CutTag(dst, mString_DEFAULT_STR_SIZE);
    return mMsg_Get_Length_String(dst, mString_DEFAULT_STR_SIZE);
}

extern int mString_Load_SecStringFromRom(u8* dst, lbRTC_sec_t sec) {
    if (sec > 59) {
        sec = 0;
    }

    return mFont_UnintToString(dst, mString_DEFAULT_STR_SIZE, sec, 2, TRUE, TRUE, TRUE);
}

extern int mString_Load_SecStringFromRom_CutTag(u8* dst, lbRTC_sec_t sec) {
    mString_Load_SecStringFromRom(dst, sec);
    mString_CutTag(dst, mString_DEFAULT_STR_SIZE);
    return mMsg_Get_Length_String(dst, mString_DEFAULT_STR_SIZE);
}

extern int mString_Load_NumberStringAddUnitFromRom(u8* dst, u16 num, int str_no) {
    int num_len = mFont_UnintToString(dst, mString_DEFAULT_STR_SIZE, num, mString_DEFAULT_STR_SIZE, TRUE, FALSE, TRUE);
    dst[num_len] = CHAR_SPACE;
    num_len++;

    /* Add the unit */
    mString_Load_StringFromRom(dst + num_len, mString_DEFAULT_STR_SIZE - num_len, str_no);
    return mMsg_Get_Length_String(dst, mString_DEFAULT_STR_SIZE);
}
