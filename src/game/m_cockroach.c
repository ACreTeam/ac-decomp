#include "m_cockroach.h"

#include "m_home.h"
#include "m_house.h"
#include "m_private.h"
#include "m_field_info.h"
#include "m_scene_table.h"
#include "m_common_data.h"

/**
 * @brief Clamps the input cockroach count between [0, mCkRh_MAX_NUM].
 *
 * @param count The new cockroach count
 * @return The clamped cockroach count
 **/
static int mCkRh_GokiFamilyCount2Good(int count) {
    if (count < 0) {
        return 0;
    }

    return (count <= mCkRh_MAX_NUM ? count : mCkRh_MAX_NUM);
}

/**
 * @brief Initializes all house cockroach save data for unclaimed houses
 * when a new Player is created.
 **/
extern void mCkRh_InitGokiSaveData_InitNewPlayer() {
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        if (mHS_get_pl_no_detail(i) == -1) {
            mCkRh_InitGokiSaveData_1Room(i);
        }
    }
}

/**
 * @brief Initializes a single house's cockroach data by house index.
 *
 * @param home_no The house index whose cockroach data will be initialized
 **/
extern void mCkRh_InitGokiSaveData_1Room(int home_no) {
    mCkRh_InitGokiSaveData_1Room_ByHomeData(Save_GetPointer(homes[home_no]));
}

/**
 * @brief Initializes a single house's cockroach data.
 *
 * @param home The mHm_hs_c house whose cockroach data wil be initialized.
 **/
extern void mCkRh_InitGokiSaveData_1Room_ByHomeData(mHm_hs_c* home) {
    home->goki.num = 0;
    home->goki.pad = 0;

    home->goki.time = Common_Get(time.rtc_time);
}

// Aus changed init time to all 0
#if VERSION >= VER_GAFU01_00
/**
 * @brief Initializes island cottage cockroach data.
 **/
extern void mCkRh_InitGokiSaveData_IslandPlayerRoom() {
    Save_Set(island.cottage.goki.num, 0);
    Save_Set(island.cottage.goki.pad, 0);
    Save_Set(island.cottage.goki.time.year, 0);
    Save_Set(island.cottage.goki.time.month, 0);
    Save_Set(island.cottage.goki.time.day, 0);
}
#else
/**
 * @brief Initializes island cottage cockroach data.
 **/
extern void mCkRh_InitGokiSaveData_IslandPlayerRoom() {
    const lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    Save_Set(island.cottage.goki.num, 0);
    Save_Set(island.cottage.goki.pad, 0);
    Save_Set(island.cottage.goki.time.year, rtc_time->year);
    Save_Set(island.cottage.goki.time.month, rtc_time->month);
    Save_Set(island.cottage.goki.time.day, rtc_time->day);
}
#endif

/**
 * @brief Initializes all houses' cockroach data even if a player owns it.
 **/
extern void mCkRh_InitGokiSaveData_AllRoom() {
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        mCkRh_InitGokiSaveData_1Room(i);
    }
}

/**
 * @brief Updates the cockroach 'last entered' time for the island cottage.
 *
 * @param scene_id The current scene id
 **/
extern void mCkRh_SetGoingOutCottageTime(int scene_id) {
    if (scene_id == SCENE_COTTAGE_MY) {
        Save_Set(island.cottage.goki.time.year, Common_Get(time.rtc_time.year));
        Save_Set(island.cottage.goki.time.month, Common_Get(time.rtc_time.month));
        Save_Set(island.cottage.goki.time.day, Common_Get(time.rtc_time.day));
    }
}

/**
 * @brief Updates the cockroach 'last entered' time for a player's house.
 *
 * @param player_no The index of the player whose cockroach data will be updated
 **/
extern void mCkRh_SavePlayTime(int player_no) {
    if (player_no < PLAYER_NUM) {
        int home_no = mHS_get_arrange_idx(player_no);
        Save_Set(homes[home_no & 3].goki.time, Common_Get(time.rtc_time));
    }
}

/**
 * @brief Returns the inverval in days between the current time and
 * the last time that the player's cockroach 'last enter time'.
 *
 * @param player_no The index of the player whose 'days gap' will be calculated
 * @return When a foriegner, 0, otherwise day interval
 **/
static int mCkRh_DaysGapCompareWithSaveTime(int player_no) {
    int homeid;
    lbRTC_time_c goki_time;
    int interval;

    if (player_no < PLAYER_NUM) {
        homeid = mHS_get_arrange_idx(player_no) & 3;
        goki_time.year = Save_Get(homes[homeid].goki.time.year);
        goki_time.month = Save_Get(homes[homeid].goki.time.month);
        goki_time.day = Save_Get(homes[homeid].goki.time.day);
        goki_time.weekday = lbRTC_Week(goki_time.year, goki_time.month, goki_time.day);
        goki_time.hour = 1;
        goki_time.min = 1;
        goki_time.sec = 1;

        interval = lbRTC_GetIntervalDays(&goki_time, Common_GetPointer(time.rtc_time));
    } else {
        interval = 0;
    }

    return interval;
}

/**
 * @brief Gets the day interval between current time and the island cottage
 * cockroach last enter time.
 *
 * @return days between current time and last island cottage enter time
 **/
static int mCkRh_DaysGapCompareWithCottageSaveTime() {
    lbRTC_time_c goki_time;

    goki_time.year = Save_Get(island.cottage.goki.time.year);
    goki_time.month = Save_Get(island.cottage.goki.time.month);
    goki_time.day = Save_Get(island.cottage.goki.time.day);
    goki_time.weekday = lbRTC_Week(goki_time.year, goki_time.month, goki_time.day);
    goki_time.hour = 1;
    goki_time.min = 1;
    goki_time.sec = 1;

    return lbRTC_GetIntervalDays(&goki_time, Common_GetPointer(time.rtc_time));
}

/**
 * @brief Determines and updates the saved cockroach number for a player.
 *
 * The minimum day interval between the current time and the cockroach's
 * 'last entered time' is 7 days. The amount you get scales linearly,
 * starting with 1 new cockroach on day 7, 2 new on day 8, ...
 *
 * The maximum number of cockroaches is clamped to mCkRh_MAX_NUM which stock
 * is 10 cockroaches.
 *
 * @param player_no The inex of the player whose cockroach data will be updated
 **/
extern void mCkRh_DecideNowGokiFamilyCount(int player_no) {
    int count;
    int day_gap;
    int home_no;
    int goki_num;

    /* player must live in town */
    if (player_no < PLAYER_NUM) {
        day_gap = mCkRh_DaysGapCompareWithSaveTime(player_no);
        home_no = mHS_get_arrange_idx(player_no) & 3;
        if (day_gap > mCkRh_INTERVAL_DAYS) {
            goki_num = Save_Get(homes[home_no].goki.num);
            count = goki_num > 0 ? day_gap : day_gap - mCkRh_INTERVAL_DAYS;
            Save_Set(homes[home_no].goki.num, mCkRh_GokiFamilyCount2Good(count + goki_num));
        }
    }

// Aus checks the year isn't set to 0
#if VERSION >= VER_GAFU01_00
    if (Save_Get(island).cottage.goki.time.year != 0) {
        day_gap = mCkRh_DaysGapCompareWithCottageSaveTime();
        if (day_gap > mCkRh_INTERVAL_DAYS) {
            u8* goki_num = Save_GetPointer(island.cottage.goki.num);
            count = (int)*goki_num > 0 ? day_gap : day_gap - mCkRh_INTERVAL_DAYS;
            *goki_num = mCkRh_GokiFamilyCount2Good(count + (int)*goki_num);
        }
    }
#else
    day_gap = mCkRh_DaysGapCompareWithCottageSaveTime();
    if (day_gap > mCkRh_INTERVAL_DAYS) {
        u8* goki_num = Save_GetPointer(island.cottage.goki.num);
        count = (int)*goki_num > 0 ? day_gap : day_gap - mCkRh_INTERVAL_DAYS;
        *goki_num = mCkRh_GokiFamilyCount2Good(count + (int)*goki_num);
    }
#endif
}

/**
 * @brief Adds a specific amount of cockroaches to the current player's house.
 *
 * @param count The number of cockroaches to add (total clamped to mCkRh_MAX_NUM)
 * @return TRUE/FALSE cockroach data was updated
 **/
extern int mCkRh_PlussGokiN_NowRoom(int count, int scene_no) {
    mActor_name_t fieldid = mFI_GetFieldId();

    if (mFI_IS_PLAYER_ROOM(fieldid)) {
        int player_no = Common_Get(player_no);
        int house_field_id = mFI_GET_PLAYER_ROOM_NO(fieldid);
        int home_id = mHS_get_arrange_idx(player_no) & 3;
        if ((player_no < PLAYER_NUM) && (house_field_id == home_id)) {
            Save_Set(homes[home_id].goki.num, mCkRh_GokiFamilyCount2Good(count + Save_Get(homes[home_id].goki.num)));
            return TRUE;
        }
    } else if (scene_no == SCENE_COTTAGE_MY) {
        u8* goki_num = Save_GetPointer(island.cottage.goki.num);
        *goki_num = mCkRh_GokiFamilyCount2Good(count + *goki_num);
    }

    return FALSE;
}

/**
 * @brief Removes a specific amount of cockroaches to the current player's house.
 *
 * @param count The number of cockroaches to remove (minimum clamped to 0)
 * @return TRUE/FALSE cockroach data was updated
 **/
extern int mCkRh_MinusGokiN_NowRoom(int count, int scene_id) {
    mActor_name_t field_id = mFI_GetFieldId();
    if (mFI_IS_PLAYER_ROOM(field_id)) {
        int player_no = Common_Get(player_no);
        int house_field_id = mFI_GET_PLAYER_ROOM_NO(field_id);
        int home_no = mHS_get_arrange_idx(player_no) & 3;
        if (player_no < PLAYER_NUM && house_field_id == home_no) {
            Save_Set(homes[home_no].goki.num, mCkRh_GokiFamilyCount2Good(Save_Get(homes[home_no].goki.num) - count));
            return TRUE;
        }
    } else if (scene_id == SCENE_COTTAGE_MY) {
        u8* goki_num = Save_GetPointer(island.cottage.goki.num);
        *goki_num = mCkRh_GokiFamilyCount2Good(*goki_num - count);
    }

    return FALSE;
}

/**
 * @brief Gets the cockroach count for the current scene id.
 *
 * @return
 *  - in player house: house cockroach count
 *  - in island octtage: island cottage cockroach count
 *  - elsewhere: 0
 **/
extern int mCkRh_NowSceneGokiFamilyCount() {
    mActor_name_t fieldid = mFI_GetFieldId();
    if (mFI_IS_PLAYER_ROOM(fieldid)) {
        return Save_Get(homes[mFI_GET_PLAYER_ROOM_NO(fieldid)].goki.num);
    } else if (Save_Get(scene_no) == SCENE_COTTAGE_MY) {
        return Save_Get(island.cottage.goki.num);
    }

    return 0;
}

/**
 * @brief Initializes the 'can_look_goki_count' variable to 0.
 *
 * This variable controls how many cockroaches are currently
 * visible to the player in a room.
 **/
extern void mCkRh_InitCanLookGokiCount() {
    Common_Set(can_look_goki_count, 0);
}

/**
 * @brief Changes the 'can_look_goki_count' variable by 'count'.
 *
 * 'can_look_goki_count' is clamped between
 *
 * @param count The number of visible cockroaches to add/remove
 * @return TRUE/FALSE were number of visible cockroaches updated?
 **/
extern int mCkRh_CalcCanLookGokiCount(int count) {
    count += Common_Get(can_look_goki_count);

    if (count < 0) {
        Common_Set(can_look_goki_count, 0);
        return FALSE;
    }

    if (count > mCkRh_CAN_LOOK_GOKI_NUM) {
        Common_Set(can_look_goki_count, mCkRh_CAN_LOOK_GOKI_NUM);
        return FALSE;
    }

    Common_Set(can_look_goki_count, count);
    return TRUE;
}

/**
 * @brief Retrieves the 'can_look_gooki_count' value.
 *
 * @return number of cockroaches currently visible to the player
 **/
extern int mCkRh_GetCanLookGokiCount() {
    return Common_Get(can_look_goki_count);
}
