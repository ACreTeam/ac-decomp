/* This file is evident by the split TUs in symbol map. Unsure of proper filename. */

#include "ac_animal_logo.h"

#include "m_common_data.h"
#include "m_npc.h"
#include "m_name_table.h"
#include "m_play.h"
#include "m_time.h"
#include "m_titledemo.h"
#include "m_event.h"
#include "m_scene_table.h"
#include "libultra/libultra.h"
#include "m_cpak.h"

extern void flash_rom_and_player_info_clear() {
    Save* save = Common_GetPointer(save);
    Private_c* priv_p;
    int i;

    bzero(save, sizeof(Save));
    mFRm_ClearSaveCheckData(Save_GetPointer(save_check));

    priv_p = Save_GetPointer(private[0]);
    for (i = 0; i < PLAYER_NUM; i++) {
        mPr_ClearPrivateInfo(priv_p);
        priv_p++;
    }

    Save_Set(land_info.exists, TRUE);
}

extern int decide_next_scene_no() {
    int is_first_game;
    int bad_save;
    int next_scene_no;

    is_first_game = mFRm_CheckSaveData() == FALSE;

    // this is weird, can't get it as a ternary or a switch
    switch ((int)Common_Get(save_error_type)) {
        case mFRm_ERROR_MEMCARD_TRAVELDATA_CONFLICT:
        case mFRm_ERROR_DATA_CORRUPTED:
        case mFRm_ERROR_MEMCARD_NO_FILES:
        case mFRm_ERROR_MEMCARD_DAMAGED:
        case mFRm_ERROR_MEMCARD_FORMAT:
        case mFRm_ERROR_MEMCARD_INVALID:
        case mFRm_ERROR_MEMCARD_NO_SPACE:
        case mFRm_ERROR_NOT_MEMCARD:
        case mFRm_ERROR_NO_MEMCARD: {
            bad_save = TRUE;
            break;
        }
        default: {
            bad_save = FALSE;
            break;
        }
    }

    if (lbRTC_IsAbnormal()) {
        const lbRTC_time_c* src;

        Common_Set(time.rtc_crashed, TRUE);
        Common_Set(time.add_sec, 1);

        if (is_first_game == TRUE || bad_save == TRUE) {
            src = &mTM_rtcTime_default_code;
        } else {
            src = Save_GetPointer(save_check.time);
        }

        lbRTC_TimeCopy(Common_GetPointer(newly_set_time), src);
    }

    if (bad_save == TRUE || Common_Get(time.rtc_crashed) == TRUE) {
        if (bad_save == TRUE) {
            flash_rom_and_player_info_clear();
        }

        Common_Set(house_owner_name, RSV_NO);
        Common_Set(last_field_id, -1);
        next_scene_no = SCENE_PLAYERSELECT_3;
    } else if (is_first_game == TRUE) {
        flash_rom_and_player_info_clear();
        Common_Set(house_owner_name, RSV_NO);
        Common_Set(last_field_id, -1);
        next_scene_no = SCENE_PLAYERSELECT;
    } else {
        next_scene_no = SCENE_PLAYERSELECT_2;
    }

    return next_scene_no;
}

extern void title_action_data_init_start_select(GAME_PLAY* play) {
    mCD_LoadLand();
    mCPk_InitPak(0);

    Common_Set(now_private, Save_GetPointer(private[0]));
    Common_Set(player_no, 0);

    mTD_rtc_reserve();
    mTM_clear_renew_is();
    mNpc_ClearAnimalInfo(mNpc_GetInAnimalP());
    play->next_scene_no = decide_next_scene_no();

    {
        int rtc_enabled = Common_Get(time.rtc_enabled);
        Common_Set(time.rtc_enabled, TRUE);
        mTM_rtcTime_limit_check();
        Common_Set(time.rtc_enabled, rtc_enabled);
    }

    mEv_ClearEventInfo();
    Common_Set(scene_from_title_demo, -1);
    Common_Set(door_data.next_scene_id, 0);
    Common_Set(submenu_disabled, TRUE);
}
