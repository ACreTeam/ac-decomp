#ifndef M_FIELD_MAKE_H
#define M_FIELD_MAKE_H

#include "types.h"
#include "m_actor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLOCK_X_NUM 7
#define BLOCK_Z_NUM 10

#define FG_BLOCK_X_NUM (BLOCK_X_NUM - 2) /* 5 */
#define FG_BLOCK_Z_NUM (BLOCK_Z_NUM - 4) /* 6 */

#define UT_X_NUM 16 /* Spaces per block (acre) in x direction */
#define UT_Z_NUM 16 /* Spaces per block (acre) in z direction */

/* sizeof(mFM_combination_c) == 2 */
typedef struct block_combination_s {
  /* 0x00 */ u16 combination_type:14; /* acre type index */
  /* 0x00 */ u16 height:2; /* 0, 1, 2, or 3 (unused) */
} mFM_combination_c;

/* sizeof(mFM_fg_c) == 0x200 */
typedef struct fg_items_s {
  /* 0x000 */ mActor_name_t items[UT_Z_NUM][UT_X_NUM];
} mFM_fg_c;

#ifdef __cplusplus
}
#endif

#endif
