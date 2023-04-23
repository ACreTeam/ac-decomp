#ifndef M_FLASHROM_H
#define M_FLASHROM_H

#include "types.h"
#include "libu64/gfxprint.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mFRm_SAVE_ID ('GAFE')

extern void mFRm_set_msg_idx(int idx);
extern int mFRm_get_msg_idx();
extern u16 mFRm_ReturnCheckSum(u16* data, s32 size);
extern u16 mFRm_GetFlatCheckSum(u16* data, s32 size, s16 now_checksum);
extern int mFRm_CheckSaveData_ID(mFRm_chk_t* save_check);
extern int mFRm_CheckSaveData_common(mFRm_chk_t* save_check, u16 land_id);
extern int mFRm_CheckSaveData();
extern void mFRm_ClearSaveCheckData(mFRm_chk_t* save_check);
extern void mFRm_SetSaveCheckData(mFRm_chk_t* save_check);
extern void mFRm_PrintSavedDebug(gfxprint_t* gfxprint);
extern void mFRm_clear_err_info();
extern void mFRm_save_data_check();
extern void mFRm_display_errInfo(gfxprint_t* gfxprint);

#define mFRm_ERROR_INFO_NUM 10
#define mFRm_NO_ERROR_NO 7

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

typedef int (save_check_proc)(void);

#ifdef __cplusplus
}
#endif

#endif
