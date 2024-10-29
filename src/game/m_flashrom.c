/**
 * @file m_flashrom.c
 * @brief Save game check and error handling functions.
 *
 * This file contains functions related to save game checks, error handling,
 * and related utility functions. The functions are responsible for verifying
 * save data integrity, managing error information, and displaying save data
 * check results and error information.
 *
 * Global Functions:
 *  - mFRm_set_msg_idx()         : Set the message index.
 *  - mFRm_get_msg_idx()         : Get the message index.
 *  - mFRm_ReturnCheckSum()      : Calculate the checksum of the given data.
 *  - mFRm_GetFlatCheckSum()     : Calculate the flat checksum for save data.
 *  - mFRm_CheckSaveData_ID()    : Check if the save data ID matches the expected ID.
 *  - mFRm_CheckSaveData_common(): Check the save data for various conditions.
 *  - mFRm_CheckSaveData()       : Perform a save data check.
 *  - mFRm_ClearSaveCheckData()  : Clear the save check data structure.
 *  - mFRm_SetSaveCheckData()    : Set the save check data structure.
 *  - mFRm_PrintSavedDebug()     : Print a debug indicator if saved debug data is found.
 *  - mFRm_clear_err_info()      : Clear the error information array.
 *  - mFRm_save_data_check()     : Perform a series of save data checks and store errors.
 *  - mFRm_display_errInfo()     : Display error information on the screen.
 *
 * File-local Functions:
 *  - mFRm_get_free_errInfo()    : Find a free slot in the error information array.
 *  - mFRm_set_errInfo()         : Set error information in the error information array.
 *  - mFRm_get_errInfoNum()      : Get the number of errors in the error information array.
 */

/* TODO: finish & include sChk_ZZZ files each programmer wrote */
/* TODO: A few removed functions need to be matched on N64 and included for proper .rodata layout */

#include "m_flashrom.h"

#include "m_common_data.h"
#include "m_time.h"
#include "m_land.h"
#include "m_name_table.h"
#include "libultra/libultra.h"
#include "zurumode.h"

static int l_mfrm_msg_idx = 0;
static int l_mfrm_now_color = 0;
static mFRm_err_info_c l_mfrm_err_info[mFRm_ERROR_INFO_NUM];
static int l_mfrm_err_debug[] = { 0, 0, 0, 0, 0, 0 };

/**
 * @brief Set the current message index value.
 *
 * This function sets the global message index value to the provided input.
 *
 * @param idx The message index value to be set.
 */
extern void mFRm_set_msg_idx(int idx) {
    l_mfrm_msg_idx = idx;
}

/**
 * @brief Get the current message index value.
 *
 * This function returns the global message index value.
 *
 * @return int The current message index value.
 */
extern int mFRm_get_msg_idx() {
    return l_mfrm_msg_idx;
}

/* @fabricated - necessary for including some strings in .data & taken from DnM */
extern MATCH_FORCESTRIP void mFRm_PrintErrInfo(gfxprint_t* gfxprint) {
    gfxprint_color(gfxprint, 250, 100, 250, 255);
    gfxprint_locate8x8(gfxprint, 22, 3);

    if (l_mfrm_err_debug[0] != 0) {
        gfxprint_printf(gfxprint, "N");
    }

    if (l_mfrm_err_debug[1] != 0) {
        gfxprint_printf(gfxprint, "A");
    }

    if (l_mfrm_err_debug[2] != 0) {
        gfxprint_printf(gfxprint, "W");
    }

    if (l_mfrm_err_debug[3] != 0) {
        gfxprint_printf(gfxprint, "R");
    }

    if (l_mfrm_err_debug[4] != 0) {
        gfxprint_printf(gfxprint, "C");
    }

    if (l_mfrm_err_debug[5] != 0) {
        gfxprint_printf(gfxprint, "O");
    }
}

/**
 * @brief Calculate the checksum of the given data.
 *
 * This function calculates the checksum of the provided data by adding
 * all the 16-bit data elements together.
 *
 * @param data A pointer to the data buffer.
 * @param size The size of the data buffer in bytes.
 * @return u16 The calculated checksum.
 */
extern u16 mFRm_ReturnCheckSum(u16* data, int size) {
    u16 checksum = 0;

    // Check if the size is even
    if ((size & 1) == 0) {
        // Calculate the checksum by adding all 16-bit data elements
        while (size != 0) {
            checksum += *data;
            data++;
            size -= sizeof(u16);
        }
    }

    return checksum;
}

/**
 * @brief Calculate the flat checksum of the given data.
 *
 * This function calculates the flat checksum of the provided data by
 * subtracting the current checksum from the calculated checksum and
 * then performing a bitwise complement and incrementing by 1.
 *
 * @param data A pointer to the data buffer.
 * @param size The size of the data buffer in bytes.
 * @param now_checksum The current checksum of the data buffer.
 * @return u16 The calculated flat checksum.
 */
extern u16 mFRm_GetFlatCheckSum(u16* data, int size, u16 now_checksum) {
    // Calculate the checksum
    u16 checksum = mFRm_ReturnCheckSum(data, size) - now_checksum;

    // Perform bitwise complement and increment by 1
    return (u16)(((~checksum & 0xFFFF) + 1) & 0xFFFF);
}

/**
 * @brief Check if the save data ID is valid.
 *
 * This function checks if the provided save_check structure contains a valid
 * save data ID.
 *
 * @param save_check A pointer to the mFRm_chk_t structure containing the save data ID.
 * @return int Returns TRUE if the save data ID is valid, otherwise FALSE.
 */
extern int mFRm_CheckSaveData_ID(mFRm_chk_t* save_check) {
    int ret = FALSE;

    // Check if the save data ID is valid
    if ((save_check->code == mFRm_SAVE_ID)) {
        ret = TRUE;
    }

    return ret;
}

/**
 * @brief Check if the save data is valid.
 *
 * This function checks if the provided save_check structure contains valid save data,
 * comparing the land ID with the provided land_id parameter.
 *
 * @param save_check A pointer to the mFRm_chk_t structure containing the save data.
 * @param land_id The land ID to check against the save data.
 * @return int Returns TRUE if the save data is valid, otherwise FALSE.
 */
extern int mFRm_CheckSaveData_common(mFRm_chk_t* save_check, u16 land_id) {
    int ret = FALSE;

    // Check if the save data ID is valid and land IDs match
    if (mFRm_CheckSaveData_ID(save_check) != 0 && mLd_CHECK_LAND_ID(save_check->land_id) &&
        save_check->land_id == land_id) {
        ret = TRUE;
    }

    return ret;
}

/**
 * @brief Check if the current save data is valid.
 *
 * This function checks if the current save data is valid using mFRm_CheckSaveData_common.
 *
 * @return int Returns TRUE if the save data is valid, otherwise FALSE.
 */
extern int mFRm_CheckSaveData() {
    return mFRm_CheckSaveData_common(Save_GetPointer(save_check), Save_Get(land_info.id));
}

/**
 * @brief Clear the save check data.
 *
 * This function clears the provided save_check structure by setting its fields to their
 * default values.
 *
 * @param save_check A pointer to the mFRm_chk_t structure to be cleared.
 */
extern void mFRm_ClearSaveCheckData(mFRm_chk_t* save_check) {
    // Set the save check data fields to their default values
    save_check->code = -1;
    save_check->land_id = 0xFFFF;
    bcopy((lbRTC_time_c*)&mTM_rtcTime_clear_code, &save_check->time, sizeof(lbRTC_time_c));
    save_check->checksum = 0;
}

/**
 * @brief Set the save check data.
 *
 * This function sets the save check data fields based on the current save data
 * and real-time clock values.
 *
 * @param save_check A pointer to the mFRm_chk_t structure to be set.
 */
extern void mFRm_SetSaveCheckData(mFRm_chk_t* save_check) {
    u16 land_id = Save_Get(land_info.id);

    // Set the save check data fields
    save_check->code = mFRm_SAVE_ID;
    save_check->land_id = land_id;
    lbRTC_TimeCopy(&save_check->time, &common_data.time.rtc_time);
}

/**
 * @brief Print the saved debug information.
 *
 * This function prints an 'X' to the screen if the saved debug information is available.
 *
 * @param gfxprint A pointer to the gfxprint_t structure for screen printing.
 */
extern void mFRm_PrintSavedDebug(gfxprint_t* gfxprint) {
    // Check if the saved debug information is available
    if (Save_Get(saved_rom_debug) == TRUE) {
        // Set the print color and location
        gfxprint_color(gfxprint, 50, 250, 100, 255);
        gfxprint_locate8x8(gfxprint, 29, 3);
        // Print an 'X' to the screen
        gfxprint_printf(gfxprint, "X");
    }
}

/* Color table for displaying error information */
static u32 l_mfrm_color_table[7][3] = {
    { 0, 0, 0 },       /* Black */
    { 255, 0, 0 },     /* Red */
    { 255, 255, 255 }, /* White */
    { 0, 190, 0 },     /* Green */
    { 100, 100, 100 }, /* Gray */
    { 0, 0, 255 },     /* Blue */
    { 255, 0, 255 }    /* Magenta */
};

/**
 * @brief Clear the error information.
 *
 * This function clears the error information by setting all error numbers
 * to mFRm_NO_ERROR_NO.
 */
extern void mFRm_clear_err_info() {
    int i;
    // Zero out the error information array
    bzero(l_mfrm_err_info, sizeof(mFRm_err_info_c) * mFRm_ERROR_INFO_NUM);

    // Set all error numbers to mFRm_NO_ERROR_NO
    for (i = 0; i < mFRm_ERROR_INFO_NUM; i++) {
        l_mfrm_err_info[i].err_no = mFRm_NO_ERROR_NO;
    }
}

/**
 * @brief Get a free error information slot.
 *
 * This function returns a pointer to the first available error information slot.
 *
 * @param err_info A pointer to the error information array.
 * @param count The number of error information slots.
 * @return mFRm_err_info_c* A pointer to the first available error information slot or NULL if none are available.
 */
static mFRm_err_info_c* mFRm_get_free_errInfo(mFRm_err_info_c* err_info, int count) {
    mFRm_err_info_c* ret = NULL;

    // Iterate through the error information slots
    while (count != 0) {
        // Check if the current slot is available
        if (err_info->err_no == mFRm_NO_ERROR_NO) {
            ret = err_info;
            break;
        }
        err_info++;
        count--;
    }
    return ret;
}

/**
 * @brief Set the error information for a specific process.
 *
 * This function sets the error information for the specified process index and error number.
 *
 * @param err_info A pointer to the error information array.
 * @param proc_idx The process index for which the error occurred.
 * @param err_no The error number to be set.
 */
static void mFRm_set_errInfo(mFRm_err_info_c* err_info, int proc_idx, int err_no) {
    // Get a free error information slot
    mFRm_err_info_c* free = mFRm_get_free_errInfo(err_info, mFRm_ERROR_INFO_NUM);

    // Set the error information if a free slot is available
    if (free != NULL) {
        free->err_no = err_no;
        free->proc_idx = proc_idx;
    }
}

/**
 * @brief Get the number of error information slots with errors.
 *
 * This function returns the number of error information slots with error numbers
 * different from mFRm_NO_ERROR_NO.
 *
 * @param err_info A pointer to the error information array.
 * @param count The number of error information slots.
 * @return int The number of error information slots with errors.
 */
static int mFRm_get_errInfoNum(mFRm_err_info_c* err_info, int count) {
    int ret = 0;

    // Loop through the error information slots
    while (count != 0) {
        // Increment the count if the error number is not mFRm_NO_ERROR_NO
        if (err_info->err_no != mFRm_NO_ERROR_NO) {
            ret++;
        }
        err_info++;
        count--;
    }
    return ret;
}

#define mFRm_ERRORLINE(line) mFRm_set_errInfo(l_mfrm_err_info, (line), l_mfrm_now_color)
#define mFRm_ERROR() mFRm_ERRORLINE(__LINE__)

#include "../src/save_check.c_inc"
#include "../src/save_check_gen.c_inc"
#include "../src/save_check_MYK.c_inc"
#include "../src/save_check_NSW.c_inc"
#include "../src/save_check_take.c_inc"
#include "../src/save_check_YSD.c_inc"
#include "../src/save_check_komatu.c_inc"

/**
 * @brief Perform save data checks.
 *
 * This function performs save data checks for different procedures and
 * increments the color index upon each check.
 */
extern void mFRm_save_data_check() {
    // Define save data check procedures
    static save_check_proc* proc[] = { &sChk_check_save_data,     &sChk_check_save_gen,  &sChk_CheckSaveData_MYK,
                                       &sChk_CheckSaveData_NSW,   &sChk_check_save_take, &sChk_CheckSaveData_YSD,
                                       &sChk_CheckSaveData_komatu };

    int i = 0;
    mFRm_err_info_c* err_info = l_mfrm_err_info;
    l_mfrm_now_color = 0;

    // If zurumode_flag is greater or equal to 2 and scene_no is 7, perform save data checks
    if ((zurumode_flag >= 2) && (Save_Get(scene_no) == 7)) {
        // If there are no errors, perform the save data checks
        if (mFRm_get_errInfoNum(err_info, mFRm_ERROR_INFO_NUM) == 0) {
            while (i < 7) {
                (*proc[i])();
                l_mfrm_now_color++;
                i++;
            }
        }
    }
}

/**
 * @brief Display error information on the screen.
 *
 * This function displays the error information on the screen if there are
 * any errors and if the zurumode_flag is greater than or equal to 2.
 *
 * @param gfxprint A pointer to the gfxprint_t structure for screen printing.
 */
extern void mFRm_display_errInfo(gfxprint_t* gfxprint) {
    mFRm_err_info_c* err_info = l_mfrm_err_info;
    int i;

    // If zurumode_flag is greater or equal to 2 and scene_no is 7, display
    // error information
    if ((zurumode_flag >= 2) && (Save_Get(scene_no) == 7)) {
        gfxprint_locate8x8(gfxprint, 37, 17);
        gfxprint_color(gfxprint, 255, 255, 255, 255);
        gfxprint_printf(gfxprint, "-");

        // If there are errors, display them on the screen
        if (mFRm_get_errInfoNum(err_info, mFRm_ERROR_INFO_NUM) > 0) {
            for (i = 0; i < 10; i++) {
                gfxprint_locate8x8(gfxprint, 30, i + 18);

                // Break the loop if no error is found
                if (err_info->err_no == mFRm_NO_ERROR_NO) {
                    break;
                }

                // Set the color for displaying the error information
                gfxprint_color(gfxprint, l_mfrm_color_table[err_info->err_no][0],
                               l_mfrm_color_table[err_info->err_no][1], l_mfrm_color_table[err_info->err_no][2], 255);

                // Display the error information
                gfxprint_printf(gfxprint, "x%dx %d", err_info->err_no, err_info->proc_idx);
                err_info++;
            }
        }
    }
}
