#ifndef M_FLASHROM_H
#define M_FLASHROM_H

#include "types.h"
#include "libu64/gfxprint.h"
#include "m_time.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mFRm_SAVE_ID ('GAFE')
#define mFRm_VERSION 6

#define mFRm_ERROR_INFO_NUM 10
#define mFRm_NO_ERROR_NO 7

enum save_error_type {
    mFRm_ERROR_BAD_RTC,                     /* RTC returned abnormal value */
    mFRm_ERROR_MEMCARD_TRAVELDATA_CONFLICT, /* travel data is on the same memory card as requesting to save town data */
    mFRm_ERROR_DATA_CORRUPTED,              /* save data is corrupt */
    mFRm_ERROR_MEMCARD_NO_FILES,            /* memory card is out of "files" */
    mFRm_ERROR_MEMCARD_DAMAGED,             /* memory card is damaged */
    mFRm_ERROR_MEMCARD_FORMAT,              /* memory card requires formatting (corrupt or different region?) */
    mFRm_ERROR_MEMCARD_INVALID,             /* memory card type "cannot be used with Animal Crossing" */
    mFRm_ERROR_MEMCARD_NO_SPACE,            /* memory card has free files, but not enough free space for save */
    mFRm_ERROR_NOT_MEMCARD,                 /* device in card slot is not a memory card */
    mFRm_ERROR_NO_MEMCARD,                  /* nothing inserted in either Slot A or Slot B */

    mFRm_ERROR_NUM
};

typedef struct mFRm_chk_s {
    /* 0x00 */ int version;
    /* 0x04 */ u32 code;
    /* 0x08 */ u16 land_id;
    /* 0x0A */ lbRTC_time_c time;
    /* 0x12 */ u16 checksum;
} mFRm_chk_t;

typedef struct flashrom_error_info {
    int err_no;
    int proc_idx;
} mFRm_err_info_c;

typedef int(save_check_proc)(void);

extern MATCH_FORCESTRIP void mFRm_PrintErrInfo(gfxprint_t* gfxprint);
extern void mFRm_set_msg_idx(int idx);
extern int mFRm_get_msg_idx();
extern u16 mFRm_ReturnCheckSum(u16* data, int size);
extern u16 mFRm_GetFlatCheckSum(u16* data, int size, u16 now_checksum);
extern int mFRm_CheckSaveData_ID(mFRm_chk_t* save_check);
extern int mFRm_CheckSaveData_common(mFRm_chk_t* save_check, u16 land_id);
extern int mFRm_CheckSaveData();
extern void mFRm_ClearSaveCheckData(mFRm_chk_t* save_check);
extern void mFRm_SetSaveCheckData(mFRm_chk_t* save_check);
extern void mFRm_PrintSavedDebug(gfxprint_t* gfxprint);
extern void mFRm_clear_err_info();
extern void mFRm_save_data_check();
extern void mFRm_display_errInfo(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
