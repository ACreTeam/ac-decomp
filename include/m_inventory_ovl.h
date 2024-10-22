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

#define mIV_PLAYER_JOINT_NUM (mPlayer_JOINT_NUM + 1)
#define mIV_ITEM_JOINT_NUM 8
#define mIV_PLAYER_EFFECT_NUM 20
#define mIV_COLLECT_NUM 40
#define mIV_ITEM_COLUMNS 5
#define mIV_ITEM_ROWS 3
#define mIV_MAIL_COLUMNS 2
#define mIV_MAIL_ROWS 5

enum {
    mIV_ITEM_SCALE_TYPE_NONE,
    mIV_ITEM_SCALE_TYPE_SHRINK,
    mIV_ITEM_SCALE_TYPE_GROW,
    mIV_ITEM_SCALE_TYPE_GROW_FAST,
    mIV_ITEM_SCALE_TYPE_GROW_FASTEST,
    mIV_ITEM_SCALE_TYPE_PRESENT,

    mIV_ITEM_SCALE_TYPE_NUM
};

enum {
    mIV_PAGE_FISH_COLLECTION,
    mIV_PAGE_INVENTORY,
    mIV_PAGE_INSECT_COLLECTION,

    mIV_PAGE_NUM
};

enum {
    mIV_ANIM_WALK,
    mIV_ANIM_CATCH,
    mIV_ANIM_CHANGE,
    mIV_ANIM_EAT,

    mIV_ANIM_NUM
};

enum {
    mIV_STRING_LAND_NAME,
    mIV_STRING_PLAYER_NAME,

    mIV_STRING_NUM
};

typedef struct inventory_effect_s {
    int timer;
    xyz_t pos;
    f32 scale;
    f32 speed;
} mIV_pl_eff_c;

typedef mActor_name_t (*mIV_SET_COLLECT_ITEMNO_PROC)(int, int);

/* sizeof (struct inventory_ovl_s) == 0x5EC */
struct inventory_ovl_s {
    cKF_SkeletonInfo_R_c player_main_keyframe;
    cKF_SkeletonInfo_R_c player_com_keyframe;
    s_xyz player_work[mIV_PLAYER_JOINT_NUM];
    s_xyz player_morph[mIV_PLAYER_JOINT_NUM];

    cKF_SkeletonInfo_R_c item_keyframe;
    s_xyz item_work[mIV_ITEM_JOINT_NUM];
    s_xyz item_morph[mIV_ITEM_JOINT_NUM];

    MtxF item_mtx;
    MtxF food_mtx;

    u8 _374[0x3BC - 0x374];

    u16 selectable_item_bitfield;
    u16 selectable_mail_bitfield;

    u32 disp_money;
    int disp_money_chg_step;

    xyz_t shovel_pos;
    xyz_t release_pos;
    u8 shovel_flag;
    u8 release_flag;

    u8 food_idx;
    u8 item_scale_type[mPr_POCKETS_SLOT_COUNT];
    u8 page_order[mIV_PAGE_NUM];
    u8 next_page_id;
    s16 page_move_timer;
    s16 remove_timer;
    mIV_pl_eff_c pl_eff[mIV_PLAYER_EFFECT_NUM];
    mIV_SET_COLLECT_ITEMNO_PROC set_collect_itemNo_proc;
    u16 item_mark_bitfield;
    u16 mail_mark_bitfield2;
    s16 mail_mark_flag;
    u8 _5E6[2];
    u16 mail_mark_bitfield;
    u8 original_flag;
    u8 wc_flag;
};

extern void mIV_inventory_ovl_construct(Submenu* submenu);
extern void mIV_inventory_ovl_destruct(Submenu* submenu);
extern void mIV_inventory_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
