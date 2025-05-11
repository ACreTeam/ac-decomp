#ifndef AC_NEEDLEWORK_INDOOR_CLIP_H
#define AC_NEEDLEWORK_INDOOR_CLIP_H

#include "types.h"
#include "m_actor_type.h"
#include "m_needlework.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*aNI_REQUESTCOPYCLOTHDATA_PROC)(int manekin_idx, mNW_original_design_c* design);
typedef int (*aNI_REQUESTCOPYUMBDATA_PROC)(int umbrella_idx, mNW_original_design_c* design);
typedef int (*aNI_REQUESTEXCHANGECLOTHDATA_PROC)(int manekin_idx, int player_org_idx);
typedef int (*aNI_REQUESTEXCHANGEUMBDATA_PROC)(int umbrella_idx, int player_org_idx);

typedef struct needlework_indoor_clip_s {
    ACTOR* needlework_indoor_actor_p;
    int copy_cloth_data_requested;
    aNI_REQUESTCOPYCLOTHDATA_PROC request_copy_cloth_data_proc;
    int copy_cloth_data_idx;
    mNW_original_design_c* copy_cloth_data_design_p;
    int exchange_cloth_data_requested;
    aNI_REQUESTEXCHANGECLOTHDATA_PROC request_exchange_cloth_data_proc;
    int exchange_cloth_data_idx;
    int exchange_cloth_data_player_org_idx;
    int copy_umb_data_requested;
    aNI_REQUESTCOPYUMBDATA_PROC request_copy_umb_data_proc;
    int copy_umb_data_idx;
    mNW_original_design_c* copy_umb_data_design_p;
    int exchange_umb_data_requested;
    aNI_REQUESTEXCHANGEUMBDATA_PROC request_exchange_umb_data_proc;
    int exchange_umb_data_idx;
    int exchange_umb_data_player_org_idx;
    int _44;
} aNI_Clip_c;

#ifdef __cplusplus
}
#endif

#endif /* AC_NEEDLEWORK_INDOOR_CLIP_H */
