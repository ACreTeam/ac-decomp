/**
 * @file m_land.c
 * @brief Functions and definitions for handling town name, town ID, and
 *        determining if a player is a foreigner or not.
 *
 * This file contains functions for manipulating town names and IDs, checking
 * if a player is a foreigner, and initializing land and home data.
 *
 * Note: "Mura" (むら/村) is the Japanese word for village. Functions which contain that
 * word were used to concatenate the town name with it. Since this does not happen
 * in inernational releases, these functions essentially do nothing.
 *
 * Functions:
 * - mLd_StartFlagOn(): Turns on the start flag.
 * - mLd_CheckStartFlag(): Checks the start flag.
 * - mLd_NullCheckLandName(): Checks if a given town name is empty or filled with spaces.
 * - mLd_CheckId(): Checks if a given land ID has the correct bitmask.
 * - mLd_CheckCmpLandName(): Compares two town names for equality.
 * - mLd_CheckCmpLand(): Compares two town names and their IDs for equality.
 * - mLd_ClearLandName(): Clears the town name by filling it with spaces.
 * - mLd_CopyLandName(): Copies a source town name to a destination.
 * - mLd_AddMuraString(): Adds the "Mura" (むら/村) string to the town name.
 * - mLd_GetLandNameStringAddMura(): Gets the town name with "Mura" (むら/村) added.
 * - mLd_SetFreeStrLandMuraName(): Sets the town name with "Mura" (むら/村) added as a free string.
 * - mLd_GetLandName(): Retrieves the town name from the save data.
 * - mLd_MakeLandId(): Generates a new land ID with the correct bitmask.
 * - mLd_PlayerManKindCheckNo(): Checks if a player is a foreigner based on their player number.
 * - mLd_PlayerManKindCheck(): Checks if the current player is a foreigner.
 * - mLd_CheckThisLand(): Checks if a given town name and ID match the current town.
 * - mLd_LandInfoInit(): Initializes the land information in the save data.
 * - mLd_LandDataInit(): Initializes the land data and clears all home information.
 */

#include "m_land.h"

#include "libc64/qrand.h"
#include "m_common_data.h"
#include "m_font.h"
#include "m_home.h"
#include "m_lib.h"
#include "m_msg.h"
#include "m_private.h"
#include "m_string.h"
#include "types.h"

static int l_mld_start_flag = FALSE;

/**
 * @brief Turns on the start flag.
 */
extern void mLd_StartFlagOn() {
    l_mld_start_flag = TRUE;
}

/**
 * @brief Checks the start flag.
 * @return The value of l_mld_start_flag.
 */
extern int mLd_CheckStartFlag() {
    return l_mld_start_flag;
}

/**
 * @brief Checks if the given town name is empty or filled with spaces.
 * @param land_name Pointer to the town name.
 * @return TRUE if the town name is empty, FALSE otherwise.
 */
extern int mLd_NullCheckLandName(u8* land_name) {
    int null_name = FALSE;
    int i;

    for (i = 0; i < LAND_NAME_SIZE; i++) {
        if (*land_name != CHAR_SPACE) {
            break;
        }
        land_name++;
    }

    if (i == LAND_NAME_SIZE) {
        null_name = TRUE;
    }
    return null_name;
}

/**
 * @brief Checks if the given land ID has the correct bitmask.
 * @param land_id Land ID to be checked.
 * @return TRUE if the land ID has the correct bitmask, FALSE otherwise.
 */
extern int mLd_CheckId(u16 land_id) {
    int res = FALSE;
    if (mLd_CHECK_ID(land_id)) {
        res = TRUE;
    }

    return res;
}

/**
 * @brief Compares two town names for equality.
 * @param name_a First town name.
 * @param name_b Second town name.
 * @return TRUE if both town names are equal, FALSE otherwise.
 */
extern int mLd_CheckCmpLandName(u8* name_a, u8* name_b) {
    int equal = FALSE;

    if (mLd_NullCheckLandName(name_a) == FALSE && mLd_NullCheckLandName(name_b) == FALSE) {
        equal = mem_cmp(name_a, name_b, LAND_NAME_SIZE);
    }

    return equal;
}

/**
 * @brief Compares two town names and their IDs for equality.
 * @param name_a First town name.
 * @param id_a First town ID.
 * @param name_b Second town name.
 * @param id_b Second town ID.
 * @return TRUE if both town names and IDs are equal, FALSE otherwise.
 */
extern int mLd_CheckCmpLand(u8* name_a, u16 id_a, u8* name_b, u16 id_b) {
    int equal = FALSE;

    if (id_a == id_b && mLd_CheckCmpLandName(name_a, name_b) == TRUE) {
        equal = TRUE;
    }

    return equal;
}

/**
 * @brief Clears the town name by filling it with spaces.
 * @param name Pointer to the town name.
 */
extern void mLd_ClearLandName(u8* name) {
    mem_clear(name, LAND_NAME_SIZE, CHAR_SPACE);
}

/**
 * @brief Copies the source town name to the destination.
 * @param dst Pointer to the destination town name.
 * @param src Pointer to the source town name.
 */
extern void mLd_CopyLandName(u8* dst, u8* src) {
    mem_copy(dst, src, LAND_NAME_SIZE);
}

/**
 * @brief Adds the "Mura" (むら/村) string to the town name.
 * @param name Pointer to the town name.
 * @param name_len Length of the town name.
 * @return The length of the new town name with "Mura" (むら/村) added.
 */
extern int mLd_AddMuraString(u8* name, int name_len) {
    u8 buf[16];
    int size;

    mString_Load_StringFromRom(buf, 16, 484); /* TODO: str_no should probably be enum or something */
    size = mMsg_Get_Length_String(buf, 16);
    mem_copy(name + name_len, buf, size);

    return size + name_len;
}

/**
 * @brief Gets the town name with "Mura" (むら/村) added.
 * @param buf Buffer to store the town name with "Mura" (むら/村) added.
 */
extern int mLd_GetLandNameStringAddMura(u8* buf) {
    int mura_size;
    int i;

    u8* name = mLd_GetLandName();
    int size = mMsg_Get_Length_String(name, LAND_NAME_SIZE);
    mem_copy(buf, name, size);
    mura_size = mLd_AddMuraString(buf, size);

    for (i = mura_size; i < LAND_NAME_MURA_SIZE; i++) {
        buf[i] = CHAR_SPACE;
    }

    return mura_size;
}

/**
 * @brief Sets the town name with "Mura" (むら/村) added as a free string.
 * @param name Pointer to the town name.
 * @param free_str_no The number of the free string.
 */
extern void mLd_SetFreeStrLandMuraName(u8* name, int free_str_no) {
    u8 str[16];
    int name_len;
    int mura_len;
    int i;

    for (i = 0; i < LAND_NAME_MURA_SIZE; i++) {
        str[i] = CHAR_SPACE;
    }

    name_len = mMsg_Get_Length_String(name, LAND_NAME_SIZE);
    mem_copy(str, name, name_len);
    mura_len = mLd_AddMuraString(str, name_len);
    mMsg_Set_free_str(mMsg_Get_base_window_p(), free_str_no, str, mura_len);
}

/**
 * @brief Retrieves the town name from the save data.
 * @return Pointer to the town name.
 */
extern u8* mLd_GetLandName() {
    return Save_Get(land_info.name);
}

/**
 * @brief Generates a new land ID with the correct bitmask.
 * @return The newly generated land ID.
 */
extern u16 mLd_MakeLandId() {
    return (int)(fqrand() * 256.0f) | mLd_BITMASK;
}

/**
 * @brief Checks if a player is a foreigner based on their player number.
 * @param player_no The player number.
 * @return TRUE if the player is a foreigner, FALSE otherwise.
 */
extern int mLd_PlayerManKindCheckNo(u8 player_no) {
    int foreigner = TRUE;
    if (player_no < PLAYER_NUM) {
        foreigner = FALSE;
    }

    return foreigner;
}

/**
 * @brief Checks if the current player is a foreigner.
 * @return TRUE if the current player is a foreigner, FALSE otherwise.
 */
extern int mLd_PlayerManKindCheck() {
    return mLd_PlayerManKindCheckNo(Common_Get(player_no));
}

/*
 * @brief Checks if the given town name and ID match the current town.
 * @param other_name Pointer to the town name to be checked.
 * @param other_id Town ID to be checked.
 * @return TRUE if the town name and ID match the current town, FALSE otherwise.
 */
extern int mLd_CheckThisLand(u8* other_name, u16 other_id) {
    return mLd_CheckCmpLand(other_name, other_id, Save_Get(land_info.name), Save_Get(land_info.id));
}

/**
 * @brief Initializes the land information in the save data.
 */
extern void mLd_LandInfoInit() {
    mLd_land_info_c* land_info = Save_GetPointer(land_info);

    land_info->id = mLd_MakeLandId();
    land_info->exists = TRUE;
}

/**
 * @brief Initializes the land data and clears all home information.
 */
extern void mLd_LandDataInit() {
    mLd_LandInfoInit();
    mHm_ClearAllHomeInfo();
}
