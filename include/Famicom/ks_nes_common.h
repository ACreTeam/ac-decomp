#ifndef KS_NES_COMMON_H
#define KS_NES_COMMON_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CHR_TO_I8_BUF_SIZE 0x100000
#define KS_NES_NESFILE_HEADER_SIZE 0x10
#define KS_NES_PRGROM_SIZE 0x8000 // not certain, generally 32kb (0x8000)
#define KS_NES_CHRROM_SIZE 0x4000 // not certain, usually only 8kb (0x2000)

#define KS_NES_CHRRAM_SIZE 0x2000 // 8kb
#define KS_NES_BBRAM_SIZE 0x8000 // 32kb, battery backed-up ram
#define KS_NES_NOISE_DATA_SIZE 0x7F000
#define KS_NES_DRAW_RESULT_SIZE 0x1C800

#define KS_NES_SAVE_DATA_HEADER_SIZE

#define KS_NES_BYTES_PER_KB (1024)
#define KS_NES_TO_KB(b) ((f32)b / (1.0f / (f32)KS_NES_BYTES_PER_KB))

typedef struct ks_nes_common_work_obj_s {
  u8 _temp[0x8F78];
} ksNesCommonWorkObj;

typedef struct ks_nes_state_obj_s {
  u8 _temp[0x1A78];
} ksNesStateObj;

#ifdef __cplusplus
}
#endif

#endif
