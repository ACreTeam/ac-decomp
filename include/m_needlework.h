#ifndef M_NEEDLEWORK_H
#define M_NEEDLEWORK_H

#include "types.h"
#include "m_personal_id.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mNW_ORIGINAL_DESIGN_NAME_LEN 16
#define mNW_ORIGINAL_DESIGN_WIDTH 32
#define mNW_ORIGINAL_DESIGN_HEIGHT 32

/* sizeof(mNW_original_design_c) == 0x220 */
typedef struct original_data_s {
  /* 0x000 */ u8 name[mNW_ORIGINAL_DESIGN_NAME_LEN];
  /* 0x010 */ u8 palette;
  /* 0x011 */ u8 pad[15];

  /* 0x020 */ u8 design[mNW_ORIGINAL_DESIGN_HEIGHT * (mNW_ORIGINAL_DESIGN_WIDTH / 2)];
} mNW_original_design_c;

#ifdef __cplusplus
}
#endif

#endif
