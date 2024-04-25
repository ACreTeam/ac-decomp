#ifndef M_INVENTORY_OVL_H
#define M_INVENTORY_OVL_H

#include "types.h"
#include "m_inventory_ovl_h.h"
#include "m_submenu_ovl.h"
#include "c_keyframe.h"
#include "libultra/ultratypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mIV_PLAYER_JOINT_NUM 27
#define mIV_ITEM_JOINT_NUM 8

/* sizeof (struct inventory_ovl_s) == 0x5EC */
struct inventory_ovl_s {
    cKF_SkeletonInfo_R_c player_keyframe0;
    cKF_SkeletonInfo_R_c player_keyframe1;
    s_xyz player_work[mIV_PLAYER_JOINT_NUM];
    s_xyz player_morph[mIV_PLAYER_JOINT_NUM];

    cKF_SkeletonInfo_R_c item_keyframe;
    s_xyz item_work[mIV_ITEM_JOINT_NUM];
    s_xyz item_morph[mIV_ITEM_JOINT_NUM];

    MtxF item_mtx;
    MtxF food_mtx;

    u8 _374[0x3BC - 0x374];

    u16 selected_item_bitfield;
    u16 selected_mail_bitfield;

    u32 disp_money;
    int disp_money_change_frames;

    xyz_t shovel_pos;
    xyz_t release_pos;
    u8 shovel_flag;
    u8 release_flag;

    u8 food_idx;

    u8 _3E3[0x5EC - 0x3E3];
};

#ifdef __cplusplus
}
#endif

#endif
