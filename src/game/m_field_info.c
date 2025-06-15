#include "m_field_info.h"

#include "m_scene_table.h"
#include "m_random_field.h"
#include "m_common_data.h"
#include "m_name_table.h"
#include "m_play.h"
#include "libultra/libultra.h"
#include "m_player_lib.h"

static mCoBG_Collision_u l_edge_ut = { { 0, 31, 31, 31, 31, 31, mCoBG_ATTRIBUTE_GRASS0 } };

typedef struct collision_keep_s {
    int assumed_ut_x;
    int assumed_ut_z;
    int unk_C;
} mFI_col_keep_c;

static mFI_col_keep_c l_keepcld[mFI_NUM_COL_KEEP] = { { 0xFF, 0xFF, 0 }, { 0xFF, 0xFF, 0 }, { 0xFF, 0xFF, 0 },
                                                      { 0xFF, 0xFF, 0 }, { 0xFF, 0xFF, 0 }, { 0xFF, 0xFF, 0 },
                                                      { 0xFF, 0xFF, 0 }, { 0xFF, 0xFF, 0 }, { 0xFF, 0xFF, 0 } };

extern void mFI_ClearFieldData() {
    g_fdinfo = NULL;
}

extern int mFI_CheckFieldData() {
    int res = FALSE;

    if (g_fdinfo != NULL) {
        res = TRUE;
    }

    return res;
}

extern mFM_block_info_c* mFI_GetBlockTopP() {
    mFM_block_info_c* block_info = NULL;
    if (g_fdinfo != NULL) {
        block_info = g_fdinfo->block_info;
    }

    return block_info;
}

extern mActor_name_t mFI_GetFieldId() {
    mActor_name_t field_id = 0;

    if (mFI_CheckFieldData() == TRUE) {
        field_id = g_fdinfo->field_id;
    }

    return field_id;
}

extern int mFI_CheckShopFieldName(mActor_name_t field_name) {
    int res = FALSE;

    if (mFI_GET_TYPE(field_name) == mFI_FIELD_ROOM0) {
        switch (field_name) {
            case mFI_FIELD_ROOM_SHOP0:
            case mFI_FIELD_ROOM_SHOP1:
            case mFI_FIELD_ROOM_SHOP2:
            case mFI_FIELD_ROOM_SHOP3_1:
            case mFI_FIELD_ROOM_SHOP3_2:
                res = TRUE;
                break;
        }
    }

    return res;
}

extern int mFI_CheckShop() {
    int res = FALSE;

    if (mFI_CheckFieldData() == TRUE) {
        res = mFI_CheckShopFieldName(mFI_GetFieldId());
    }

    return res;
}

extern u8 mFI_GetBlockXMax() {
    u8 size = 0;

    if (mFI_CheckFieldData() == TRUE) {
        size = g_fdinfo->block_x_max;
    }

    return size;
}

extern u8 mFI_GetBlockZMax() {
    u8 size = 0;

    if (mFI_CheckFieldData() == TRUE) {
        size = g_fdinfo->block_z_max;
    }

    return size;
}

extern f32 mFI_GetBlockWidth() {
    static f32 player_room_wd[4] = { 240.0f, 320.0f, 400.0f, 400.0f };

    mActor_name_t field_id = mFI_GetFieldId();
    mActor_name_t house_owner_name = Common_Get(house_owner_name);

    switch (mFI_GET_TYPE(field_id)) {
        case mFI_FIELD_ROOM0: {
            switch (field_id) {
                case mFI_FIELD_ROOM_POLICE_BOX:
                    return 400.0f;
                case mFI_FIELD_ROOM_SHOP0:
                    return 320.0f;
                case mFI_FIELD_ROOM_SHOP1:
                    return 440.0f;
                case mFI_FIELD_ROOM_SHOP2:
                    return 440.0f;
                case mFI_FIELD_ROOM_SHOP3_1:
                    return 480.0f;
                case mFI_FIELD_ROOM_SHOP3_2:
                    return 480.0f;
                case mFI_FIELD_ROOM_MUSEUM_ENTRANCE:
                    return 320.0f;
                case mFI_FIELD_ROOM_MUSEUM_FOSSIL:
                    return 640.0f;
                case mFI_FIELD_ROOM_MUSEUM_PAINTING:
                    return 640.0f;
                case mFI_FIELD_ROOM_MUSEUM_FISH:
                    return 560.0f;
                case mFI_FIELD_ROOM_MUSEUM_INSECT:
                    return 560.0f;
                case mFI_FIELD_ROOM_NEEDLEWORK:
                    return 400.0f;
                case mFI_FIELD_ROOM_LIGHTHOUSE:
                    return 240.0f;
                case mFI_FIELD_ROOM_TENT:
                    return 240.0f;
                default:
                    return 320.0f;
            }
        }

        case mFI_FIELD_NPCROOM0: {
            return mFI_BK_WORLDSIZE_X_F / 2.0f;
        }

        case mFI_FIELD_PLAYER0_ROOM: {
            u8 size;

            if (Save_Get(scene_no) == SCENE_COTTAGE_MY) {
                return 400.0f;
            }

            if (Save_Get(scene_no) == SCENE_MY_ROOM_LL2) {
                return mFI_BK_WORLDSIZE_X_F / 2.0f;
            }

            if (Save_Get(scene_no) >= SCENE_MY_ROOM_BASEMENT_S && Save_Get(scene_no) <= SCENE_MY_ROOM_BASEMENT_LL1) {
                return 400.0f;
            }

            size = Save_Get(homes[house_owner_name]).size_info.size;
            if (size > 3) {
                size = 3;
            }

            return player_room_wd[size];
        }

        default: {
            return mFI_BK_WORLDSIZE_X_F;
        }
    }
}

extern f32 mFI_GetBlockHeight() {
    static f32 player_room_ht[4] = { 280.0f, 360.0f, 440.0f, 440.0f };

    mActor_name_t field_id = mFI_GetFieldId();
    mActor_name_t house_owner_name = Common_Get(house_owner_name);

    switch (mFI_GET_TYPE(field_id)) {
        case mFI_FIELD_ROOM0: {
            switch (field_id) {
                case mFI_FIELD_ROOM_POLICE_BOX:
                    return 400.0f;
                case mFI_FIELD_ROOM_SHOP0:
                    return 320.0f;
                case mFI_FIELD_ROOM_SHOP1:
                    return 320.0f;
                case mFI_FIELD_ROOM_SHOP2:
                    return 480.0f;
                case mFI_FIELD_ROOM_SHOP3_1:
                    return 560.0f;
                case mFI_FIELD_ROOM_SHOP3_2:
                    return 560.0f;
                case mFI_FIELD_ROOM_MUSEUM_ENTRANCE:
                    return 640.0f;
                case mFI_FIELD_ROOM_MUSEUM_FOSSIL:
                    return 640.0f;
                case mFI_FIELD_ROOM_MUSEUM_PAINTING:
                    return 640.0f;
                case mFI_FIELD_ROOM_MUSEUM_FISH:
                    return 640.0f;
                case mFI_FIELD_ROOM_MUSEUM_INSECT:
                    return 640.0f;
                case mFI_FIELD_ROOM_NEEDLEWORK:
                    return 320.0f;
                case mFI_FIELD_ROOM_LIGHTHOUSE:
                    return 260.0f;
                case mFI_FIELD_ROOM_TENT:
                    return 260.0f;
                default:
                    return 320.0f;
            }
        }

        case mFI_FIELD_NPCROOM0: {
            return mFI_BK_WORLDSIZE_X_F / 2.0f;
        }

        case mFI_FIELD_PLAYER0_ROOM: {
            u8 size;

            if (Save_Get(scene_no) == SCENE_COTTAGE_MY) {
                return 440.0f;
            }

            if (Save_Get(scene_no) == SCENE_MY_ROOM_LL2) {
                return 360.0f;
            }

            if (Save_Get(scene_no) >= SCENE_MY_ROOM_BASEMENT_S && Save_Get(scene_no) <= SCENE_MY_ROOM_BASEMENT_LL1) {
                return 440.0f;
            }

            size = Save_Get(homes[house_owner_name]).size_info.size;
            if (size > 3) {
                size = 3;
            }

            return player_room_ht[size];
        }

        default: {
            return mFI_BK_WORLDSIZE_X_F;
        }
    }
}

extern int mFI_GetBlockNum(int block_x, int block_z) {
    int num = block_x + block_z * mFI_GetBlockXMax();

    return num;
}

static int mFI_GetUtNum(int ut_x, int ut_z) {
    return ut_x + ut_z * UT_X_NUM;
}

extern int mFI_BlockCheck(int block_x, int block_z) {
    int num = mFI_GetBlockNum(block_x, block_z);

    if (block_x < 0 || block_x >= mFI_GetBlockXMax() || block_z < 0 || block_z >= mFI_GetBlockZMax() ||
        g_fdinfo->block_info[num].bg_info.bg_id.combination_type == 292) {
        return FALSE;
    }

    return TRUE;
}

extern int mFI_UtNumCheck(int ut_x, int ut_z, int bx_max, int bz_max) {
    int res = TRUE;
    int max_x = (bx_max * UT_X_NUM);
    int max_z = (bz_max * UT_Z_NUM);

    if (ut_x < 0 || ut_x >= max_x || ut_z < 0 || ut_z >= max_z) {
        res = FALSE;
    }

    return res;
}

static int mFI_WposCheck(xyz_t wpos) {
    int bx;
    int bz;

    return mFI_Wpos2BlockNum(&bx, &bz, wpos);
}

extern int mFI_WposX2UtNumX(f32 wpos_x) {
    return (int)(wpos_x / mFI_UT_WORLDSIZE_X_F);
}

extern int mFI_WposZ2UtNumZ(f32 wpos_z) {
    return (int)(wpos_z / mFI_UT_WORLDSIZE_Z_F);
}

extern int mFI_Wpos2UtNum(int* ut_x, int* ut_z, xyz_t wpos) {
    *ut_x = (int)(wpos.x / mFI_UT_WORLDSIZE_X_F);
    *ut_z = (int)(wpos.z / mFI_UT_WORLDSIZE_Z_F);

    if (wpos.x < 0.0f || wpos.x > (mFI_GetBlockXMax() * mFI_BK_WORLDSIZE_X_F) || wpos.z < 0.0f ||
        wpos.z > (mFI_GetBlockZMax() * mFI_BK_WORLDSIZE_Z_F)) {
        return FALSE;
    }

    return TRUE;
}

extern int mFI_UtNum2CenterWpos(xyz_t* wpos, int ut_x, int ut_z) {
    wpos->x = (f32)ut_x * mFI_UT_WORLDSIZE_X_F;
    wpos->z = (f32)ut_z * mFI_UT_WORLDSIZE_Z_F;

    wpos->x += mFI_UT_WORLDSIZE_HALF_X_F;
    wpos->z += mFI_UT_WORLDSIZE_HALF_Z_F;

    return mFI_UtNumCheck(ut_x, ut_z, mFI_GetBlockXMax(), mFI_GetBlockZMax());
}

extern int mFI_Wpos2UtCenterWpos(xyz_t* wpos, xyz_t src_pos) {
    f32 x = (int)(src_pos.x / mFI_UT_WORLDSIZE_X_F) * mFI_UT_WORLDSIZE_X;
    f32 z = (int)(src_pos.z / mFI_UT_WORLDSIZE_Z_F) * mFI_UT_WORLDSIZE_Z;

    wpos->x = x + mFI_UT_WORLDSIZE_HALF_Z_F;
    wpos->y = src_pos.y;
    wpos->z = z + mFI_UT_WORLDSIZE_HALF_Z_F;

    return mFI_WposCheck(src_pos);
}

extern int mFI_Wpos2UtNum_inBlock(int* ut_x, int* ut_z, xyz_t wpos) {
    int res = FALSE;

    if (wpos.x >= 0.0f && wpos.x < ((f32)mFI_GetBlockXMax() * mFI_BK_WORLDSIZE_X_F) && wpos.z >= 0.0f &&
        wpos.z < ((f32)mFI_GetBlockZMax() * mFI_BK_WORLDSIZE_Z_F)) {
        ut_x[0] = (int)(wpos.x / mFI_UT_WORLDSIZE_X_F);
        ut_z[0] = (int)(wpos.z / mFI_UT_WORLDSIZE_Z_F);

        ut_x[0] &= 0xF;
        ut_z[0] &= 0xF;

        res = TRUE;
    } else {
        ut_x[0] = 0;
        ut_z[0] = 0;
    }

    return res;
}

extern int mFI_Wpos2BlockNum(int* bx, int* bz, xyz_t wpos) {
    bx[0] = (int)(wpos.x / mFI_BK_WORLDSIZE_X_F);
    bz[0] = (int)(wpos.z / mFI_BK_WORLDSIZE_Z_F);

    return mFI_BlockCheck(*bx, *bz);
}

extern int mFI_Wpos2BkandUtNuminBlock(int* bx, int* bz, int* ut_x, int* ut_z, xyz_t wpos) {
    bx[0] = (int)(wpos.x / mFI_BK_WORLDSIZE_X_F);
    bz[0] = (int)(wpos.z / mFI_BK_WORLDSIZE_Z_F);
    ut_x[0] = (int)(wpos.x / mFI_UT_WORLDSIZE_X_F);
    ut_z[0] = (int)(wpos.z / mFI_UT_WORLDSIZE_Z_F);

    ut_x[0] &= 0xF;
    ut_z[0] &= 0xF;

    return mFI_BlockCheck(*bx, *bz);
}

static int mFI_UtNum2BlockNum(int* bx, int* bz, int ut_x, int ut_z) {
    if (ut_x < 0) {
        ut_x -= (UT_X_NUM - 1);
    }

    if (ut_z < 0) {
        ut_z -= (UT_Z_NUM - 1);
    }

    bx[0] = ut_x / UT_X_NUM;
    bz[0] = ut_z / UT_Z_NUM;

    return mFI_BlockCheck(bx[0], bz[0]);
}

static int mFI_GetUtNumInBK(int* bk_ut_x, int* bk_ut_z, int ut_x, int ut_z) {
    int res = mFI_UtNumCheck(ut_x, ut_z, mFI_GetBlockXMax(), mFI_GetBlockZMax());

    if (res) {
        bk_ut_x[0] = ut_x & 0xF;
        bk_ut_z[0] = ut_z & 0xF;
    } else {
        bk_ut_x[0] = 0;
        bk_ut_z[0] = 0;
    }

    return res;
}

extern int mFI_WpostoLposInBK(xyz_t* lpos, xyz_t wpos) {
    int bx;
    int bz;
    int res = mFI_Wpos2BlockNum(&bx, &bz, wpos);

    lpos->x = wpos.x - ((f32)bx * mFI_BK_WORLDSIZE_X_F);
    lpos->y = wpos.y;
    lpos->z = wpos.z - ((f32)bz * mFI_BK_WORLDSIZE_Z_F);
    return res;
}

extern int mFI_LposInBKtoWpos(xyz_t* wpos, xyz_t lpos, int bx, int bz) {
    wpos->x = lpos.x + (f32)(bx * mFI_BK_WORLDSIZE_X);
    wpos->y = lpos.y;
    wpos->z = lpos.z + (f32)(bz * mFI_BK_WORLDSIZE_Z);

    return mFI_BlockCheck(bx, bz);
}

extern int mFI_ScrollCheck(xyz_t wpos, u8 dir) {
    int bx;
    int bz;

    if (mFI_Wpos2BlockNum(&bx, &bz, wpos) == FALSE) {
        return FALSE;
    }

    switch (dir) {
        case mFI_MOVEDIR_RIGHT:
            bx++;
            break;
        case mFI_MOVEDIR_LEFT:
            bx--;
            break;
        case mFI_MOVEDIR_UP:
            bz--;
            break;
        case mFI_MOVEDIR_DOWN:
            bz++;
            break;
        default:
            return FALSE;
    }

    return mFI_BlockCheck(bx, bz);
}

extern int mFI_BkNum2WposXZ(f32* wpos_x, f32* wpos_z, int bx, int bz) {
    int res = FALSE;

    wpos_x[0] = (f32)(bx * mFI_BK_WORLDSIZE_X);
    wpos_z[0] = (f32)(bz * mFI_BK_WORLDSIZE_Z);

    if (mFI_CheckFieldData() == TRUE) {
        res = mFI_BlockCheck(bx, bz);
    }

    return res;
}

extern void mFI_UtNum2PosXZInBk(f32* pos_x, f32* pos_z, int ut_x, int ut_z) {
    pos_x[0] = (f32)(ut_x * mFI_UT_WORLDSIZE_X);
    pos_z[0] = (f32)(ut_z * mFI_UT_WORLDSIZE_Z);
}

extern void mFI_BkandUtNum2Wpos(xyz_t* wpos, int bx, int bz, int ut_x, int ut_z) {
    f32 wpos_x;
    f32 wpos_z;
    f32 bpos_x;
    f32 bpos_z;

    mFI_BkNum2WposXZ(&wpos_x, &wpos_z, bx, bz);
    mFI_UtNum2PosXZInBk(&bpos_x, &bpos_z, ut_x, ut_z);

    wpos->x = wpos_x + bpos_x;
    wpos->y = 0.0f;
    wpos->z = wpos_z + bpos_z;
}

extern void mFI_BkandUtNum2CenterWpos(xyz_t* wpos, int bx, int bz, int ut_x, int ut_z) {
    mFI_BkandUtNum2Wpos(wpos, bx, bz, ut_x, ut_z);

    wpos->x += mFI_UT_WORLDSIZE_HALF_X_F;
    wpos->z += mFI_UT_WORLDSIZE_HALF_Z_F;
}

extern mFM_field_draw_info_c* mFI_BGDisplayListTop() {
    return g_fdinfo->bg_draw_info;
}

extern mFM_field_pal_c* mFI_GetFieldPal() {
    return &g_fdinfo->field_palette;
}

extern int mFI_GetPlayerHouseFloorNo(int scene) {
    int floor = -1;

    switch (scene) {
        case SCENE_MY_ROOM_S:
        case SCENE_MY_ROOM_M:
        case SCENE_MY_ROOM_L:
        case SCENE_MY_ROOM_LL1:
        case SCENE_COTTAGE_MY:
            floor = 0;
            break;

        case SCENE_MY_ROOM_LL2:
            floor = 1;
            break;

        case SCENE_MY_ROOM_BASEMENT_S:
        case SCENE_MY_ROOM_BASEMENT_M:
        case SCENE_MY_ROOM_BASEMENT_L:
        case SCENE_MY_ROOM_BASEMENT_LL1:
            floor = 2;
            break;
    }

    return floor;
}

extern int mFI_GetNowPlayerHouseFloorNo() {
    return mFI_GetPlayerHouseFloorNo(Save_Get(scene_no));
}

typedef struct register_bg_info_s {
    int dma_active;
    int bg_num;
    u32 unused_rom_start;
    u32 unused_rom_size;
} mFI_register_bg_info_c;

static mFI_register_bg_info_c l_register_bg_info[mFM_VISIBLE_BLOCK_NUM];

static void mFI_ClearRegisterBgInfo(mFI_register_bg_info_c* bg_info) {
    bg_info->dma_active = FALSE;
    bg_info->bg_num = -1;
    bg_info->unused_rom_start = 0;
    bg_info->unused_rom_size = 0;
}

static void mFI_ClearRegisterBgInfoIdx(int idx) {
    mFI_ClearRegisterBgInfo(&l_register_bg_info[idx]);
}

extern void mFI_InitRegisterBgInfo() {
    int i;

    for (i = 0; i < mFM_VISIBLE_BLOCK_NUM; i++) {
        mFI_ClearRegisterBgInfo(&l_register_bg_info[i]);
    }
}

static int mFI_CheckFreeRegisterBgInfo(mFI_register_bg_info_c* bg_info) {
    int res = FALSE;

    if (bg_info->bg_num == -1) {
        res = TRUE;
    }

    return res;
}

static int mFI_GetFreeRegisterBgInfo() {
    mFI_register_bg_info_c* bg_info = l_register_bg_info;
    int res = -1;
    int i;

    for (i = 0; i < mFM_VISIBLE_BLOCK_NUM; i++) {
        if (mFI_CheckFreeRegisterBgInfo(bg_info)) {
            res = i;
            break;
        }

        bg_info++;
    }

    return res;
}

static void mFI_SetRegisterBgInfo(int bg_num, u32 rom_start, u32 rom_size) {
    mFI_register_bg_info_c* bg_info = l_register_bg_info + bg_num;

    bg_info->dma_active = TRUE;
    bg_info->bg_num = bg_num;
    bg_info->unused_rom_start = rom_start;
    bg_info->unused_rom_size = rom_size;
}

static int mFI_CheckFinishBgDma(int bg_num) {
    int res = FALSE;

    if (l_register_bg_info[bg_num].dma_active == FALSE && l_register_bg_info[bg_num].bg_num != -1) {
        res = TRUE;
    }

    return res;
}

static void mFI_DmaBg_sub(mFI_register_bg_info_c* bg_info) {
    g_fdinfo->bg_draw_info[bg_info->bg_num].dma_loaded = TRUE;
}

static void mFI_DmaBg() {
    mFI_register_bg_info_c* bg_info = l_register_bg_info;
    int i;

    for (i = 0; i < mFM_VISIBLE_BLOCK_NUM; i++) {
        if (bg_info->dma_active == TRUE) {
            mFI_DmaBg_sub(bg_info);
            mFI_BornItemON();
            Common_Set(remove_cut_tree_info_bitfield,
                       Common_Get(remove_cut_tree_info_bitfield) | (1 << bg_info->bg_num));
            bg_info->dma_active = FALSE;

            break;
        }

        bg_info++;
    }
}

extern int mFI_CheckBgDma(int bx, int bz) {
    int res = FALSE;
    int i;

    if (mFI_CheckFieldData() == TRUE) {
        mFM_field_draw_info_c* draw_info = mFI_BGDisplayListTop();

        for (i = 0; i < mFM_VISIBLE_BLOCK_NUM; i++) {
            if (draw_info->block_x == bx && draw_info->block_z == bz && draw_info->dma_loaded) {
                res = TRUE;

                break;
            }

            draw_info++;
        }
    }

    return res;
}

extern f32 mFI_UtNum2BaseHeight(int ut_x, int ut_z) {
    int bx;
    int bz;
    int num;

    if (mFI_UtNum2BlockNum(&bx, &bz, ut_x, ut_z) == FALSE) {
        return 10000.0f;
    }

    num = mFI_GetBlockNum(bx, bz);
    return (f32)((int)g_fdinfo->block_info[num].bg_info.bg_id.height * (3 * mFI_UT_WORLDSIZE_X));
}

extern f32 mFI_BkNum2BaseHeight(int bx, int bz) {
    int num;

    if (mFI_BlockCheck(bx, bz) == FALSE) {
        return 10000.0f;
    }

    num = mFI_GetBlockNum(bx, bz);
    return (f32)((int)g_fdinfo->block_info[num].bg_info.bg_id.height * (3 * mFI_UT_WORLDSIZE_X));
}

extern u8 mFI_BkNum2BlockType(int bx, int bz) {
    u8 type = 39;

    if (mFI_CheckFieldData() && bx >= 0 && bx < BLOCK_X_NUM && bz >= 0 && bz < BLOCK_Z_NUM) {
        int idx = (bz * BLOCK_X_NUM) + bx;

        type = g_block_type_p[idx];
    }

    return type;
}

// 25%

static int mFI_GetPuleTypeIdx(u8 type) {
    u32 kind = mRF_Type2BlockInfo(type);
    int idx = -1;

    if ((kind & mRF_BLOCKKIND_POOL) == mRF_BLOCKKIND_POOL) {
        idx = type - 69;
    }

    return idx;
}

extern int mFI_GetPuleIdx() {
    int bx;
    int bz;
    u8 type;

    mFI_BlockKind2BkNum(&bx, &bz, mRF_BLOCKKIND_POOL);
    type = mFI_BkNum2BlockType(bx, bz);
    return mFI_GetPuleTypeIdx(type);
}

extern u32 mFI_BkNum2BlockKind(int bx, int bz) {
    u32 kind = mRF_BLOCKKIND_NONE;

    if (mFI_CheckFieldData() && mFI_BlockCheck(bx, bz)) {
        int num = mFI_GetBlockNum(bx, bz);

        kind = g_fdinfo->block_info[num].bg_info.block_kind;
    }

    return kind;
}

extern int mFI_CheckBlockKind(int bx, int bz, u32 block_kind) {
    int res = FALSE;
    u32 kind = mFI_BkNum2BlockKind(bx, bz);

    kind &= block_kind;
    if (block_kind == kind) {
        res = TRUE;
    }

    return res;
}

extern int mFI_CheckBlockKind_OR(int bx, int bz, u32 block_kind_OR) {
    int res = FALSE;
    u32 kind = mFI_BkNum2BlockKind(bx, bz);

    kind &= block_kind_OR;
    if (kind != mRF_BLOCKKIND_NONE) {
        res = TRUE;
    }

    return res;
}

extern int mFI_BlockKind2BkNum(int* bx, int* bz, u32 kind) {
    u32* kind_p = (u32*)g_block_kind_p;
    int res = FALSE;
    int i;

    bx[0] = 0;
    bz[0] = 0;

    if (kind_p != NULL) {
        for (i = 0; i < BLOCK_TOTAL_NUM; i++) {
            u32 k = kind_p[0];

            k &= kind;
            if (kind == k) {
                bx[0] = i % BLOCK_X_NUM;
                bz[0] = i / BLOCK_X_NUM;
                res = TRUE;

                break;
            }

            kind_p++;
        }
    }

    return res;
}

extern void mFI_GetSpecialBlockNum(int* block_pos, u32* kinds, int count) {
    int i;

    for (i = 0; i < count; i++) {
        mFI_BlockKind2BkNum(block_pos + 0, block_pos + 1, kinds[0]);
        kinds++;
        block_pos += 2;
    }
}

extern void mFI_GetIslandBlockNumX(int* island_x_blocks) {
    u32* kind_p = (u32*)g_block_kind_p;
    int found_num = 0;
    int i;

    if (island_x_blocks != NULL && kind_p != NULL) {
        bzero(island_x_blocks, 2 * sizeof(int));

        kind_p += mISL_BLOCK_Z * BLOCK_X_NUM;
        for (i = 0; i < BLOCK_X_NUM; i++) {
            if ((kind_p[0] & mRF_BLOCKKIND_ISLAND) == mRF_BLOCKKIND_ISLAND) {
                island_x_blocks[0] = i;
                island_x_blocks++;
                found_num++;
            }

            if (found_num >= mISL_FG_BLOCK_X_NUM) {
                break;
            }

            kind_p++;
        }
    }
}

extern mCoBG_Collision_u* mFI_GetBkNum2ColTop(int bx, int bz) {
    mCoBG_Collision_u* col = NULL;

    if (mFI_CheckFieldData() && mFI_BlockCheck(bx, bz)) {
        int num = mFI_GetBlockNum(bx, bz);

        col = (mCoBG_Collision_u*)g_fdinfo->block_info[num].bg_info.collision;
    }

    return col;
}

extern mCoBG_Collision_u* mFI_UtNum2UtCol(int ut_x, int ut_z) {
    int b_ut_x;
    int b_ut_z;
    int bx;
    int bz;

    if (mFI_UtNumCheck(ut_x, ut_z, mFI_GetBlockXMax(), mFI_GetBlockZMax()) == FALSE) {
        return &l_edge_ut;
    } else if (mFI_UtNum2BlockNum(&bx, &bz, ut_x, ut_z) == FALSE) {
        return &l_edge_ut;
    } else {
        mFM_bg_info_c* bg_info;
        mCoBG_Collision_u* col;
        int num;
        int idx;

        mFI_GetUtNumInBK(&b_ut_x, &b_ut_z, ut_x, ut_z);
        num = mFI_GetBlockNum(bx, bz);
        idx = b_ut_z * UT_X_NUM + b_ut_x;
        col = (mCoBG_Collision_u*)g_fdinfo->block_info[num].bg_info.collision;
        col += idx;
        return col;
    }
}

extern void mFI_ClearColKeep() {
    int i;

    for (i = 0; i < mFI_NUM_COL_KEEP; i++) {
        l_keepcld[i].assumed_ut_x = 0xFF;
        l_keepcld[i].assumed_ut_z = 0xFF;
        l_keepcld[i].unk_C = 0;
    }
}

/* @unused mFI_GetUtColGroup */

/* @unused mFI_UtNum2UtColKeep */

extern mCoBG_Collision_u* mFI_GetUnitCol(xyz_t wpos) {
    int ut_x;
    int ut_z;

    if (mFI_Wpos2UtNum(&ut_x, &ut_z, wpos) == FALSE) {
        return &l_edge_ut;
    } else {
        return mFI_UtNum2UtCol(ut_x, ut_z);
    }
}

extern u8 mFI_UtNum2UtKeepH(int ut_x, int ut_z) {
    int b_ut_x;
    int b_ut_z;
    int bx;
    int bz;

    if (mFI_UtNumCheck(ut_x, ut_z, mFI_GetBlockXMax(), mFI_GetBlockZMax()) == FALSE) {
        return mCoBG_HEIGHT_MAX;
    } else if (mFI_UtNum2BlockNum(&bx, &bz, ut_x, ut_z) == FALSE) {
        return mCoBG_HEIGHT_MAX;
    } else {
        mFM_block_info_c* block;
        u8* keep_p;
        int num;
        int idx;

        mFI_GetUtNumInBK(&b_ut_x, &b_ut_z, ut_x, ut_z);
        num = mFI_GetBlockNum(bx, bz);
        keep_p = (u8*)g_fdinfo->block_info[num].bg_info.keep_h;
        idx = b_ut_z * UT_Z_NUM + b_ut_x;
        keep_p += b_ut_z * UT_Z_NUM + b_ut_x;
        return keep_p[0];
    }
}

extern mFM_bg_sound_source_c* mFI_GetSoundSourcePBlockNum(int bx, int bz) {
    mFM_bg_sound_source_c* ss = NULL;

    if (mFI_BlockCheck(bx, bz)) {
        int num = mFI_GetBlockNum(bx, bz);
        ss = g_fdinfo->block_info[num].bg_info.sound_source;
    }

    return ss;
}

extern Gfx* mFI_GetBGDisplayListRom(int bx, int bz) {
    Gfx* gfx;
    int num = mFI_GetBlockNum(bx, bz);

    if (mFI_BlockCheck(bx, bz) == FALSE) {
        gfx = NULL;
    } else {
        gfx = g_fdinfo->block_info[num].bg_info.opaque_gfx;
    }

    return gfx;
}

extern Gfx* mFI_GetBGDisplayListRom_XLU(int bx, int bz) {
    Gfx* gfx;
    int num = mFI_GetBlockNum(bx, bz);

    if (mFI_BlockCheck(bx, bz) == FALSE) {
        gfx = NULL;
    } else {
        gfx = g_fdinfo->block_info[num].bg_info.translucent_gfx;
    }

    return gfx;
}

extern EVW_ANIME_DATA* mFI_GetBGTexAnimInfo(s8* anim_num, int bx, int bz) {
    EVW_ANIME_DATA* anime;
    int num = mFI_GetBlockNum(bx, bz);

    if (mFI_BlockCheck(bx, bz) == FALSE) {
        anime = NULL;
        anim_num[0] = 0;
    } else {
        anime = g_fdinfo->block_info[num].bg_info.animation;
        anim_num[0] = g_fdinfo->block_info[num].bg_info.animation_count;
    }

    return anime;
}

static int mFI_BGDispMatch(int* idx, int bx, int bz) {
    int max = g_fdinfo->bg_num;
    int res = FALSE;
    int i;

    for (i = 0; i < max; i++) {
        idx[0] = i;

        if (g_fdinfo->bg_draw_info[i].block_x == bx && g_fdinfo->bg_draw_info[i].block_z == bz) {
            res = TRUE;
            break;
        }
    }

    return res;
}

static int mFI_SearchNullDisp(int* idx) {
    int res = FALSE;
    int free_idx = mFI_GetFreeRegisterBgInfo();

    if (free_idx != -1) {
        idx[0] = free_idx;
        res = TRUE;
    } else {
        idx[0] = g_fdinfo->bg_num;
    }

    return res;
}

static void mFI_BGDispMake(u8* disp_bitfield, int bx, int bz) {
    int num = mFI_GetBlockNum(bx, bz);
    int idx;

    if (mFI_BGDispMatch(&idx, bx, bz) == FALSE) {
        if (mFI_SearchNullDisp(&idx)) {
            mFI_SetRegisterBgInfo(idx, g_fdinfo->block_info[num].bg_info.rom_start_addr,
                                  g_fdinfo->block_info[num].bg_info.rom_size);
            g_fdinfo->bg_draw_info[idx].block_x = bx;
            g_fdinfo->bg_draw_info[idx].block_z = bz;
            disp_bitfield[0] |= (1 << idx);
        }
    } else {
        disp_bitfield[0] |= (1 << idx);
    }
}

typedef struct block_area_info_s {
    int initialized;
    int _04;
    f32 area[6];
} mFI_block_area_info_c;

static mFI_block_area_info_c l_barea;

extern void mFI_InitAreaInfo() {
    static f32 area_table[6] = {
        /* X position */
        280.0f, /* x = [0,  6] */
        360.0f, /* x = [7,  8] */
        640.0f, /* x = [9, 15] */

        /* Z position */
        380.0f, /* z = [0, 9.5) */
        400.0f, /* z = [9.5, 10)*/
        640.0f  /* z = [10, 15] */
    };

    int i;

    l_barea.initialized = TRUE;
    l_barea._04 = 0;

    for (i = 0; i < 6; i++) {
        l_barea.area[i] = area_table[i];
    }
}

static void mFI_WhereisInBlock(u8* pos_bitfield, xyz_t wpos) {
    xyz_t lpos;
    int i;

    mFI_WpostoLposInBK(&lpos, wpos);

    if (lpos.x >= 0.0f) {
        for (i = 0; i < 3; i++) {
            if (lpos.x < l_barea.area[i]) {
                pos_bitfield[0] |= (1 << i);
                break;
            }
        }
    }

    if (lpos.z >= 0.0f) {
        for (i = 3; i < 6; i++) {
            if (lpos.z < l_barea.area[i]) {
                pos_bitfield[0] |= (1 << i);
                break;
            }
        }
    }
}

extern void mFI_BGDisplayListRefresh(xyz_t wpos) {
    u8 disp_bitfield;
    u8 where_bitfield;
    int bx;
    int bz;
    int i;
    int nearest_bx;
    int nearest_bz;
    int num;
    int temp;

    disp_bitfield = 0;
    where_bitfield = 0;
    Common_Set(remove_cut_tree_info_bitfield, 0);
    if (mFI_Wpos2BlockNum(&bx, &bz, wpos)) {
        num = mFI_GetBlockNum(bx, bz);

        if (g_fdinfo->block_info[num].bg_info.bg_id.combination_type != 292) {
            mFI_BGDispMake(&disp_bitfield, bx, bz);
        }
    }

    mFI_WhereisInBlock(&where_bitfield, wpos);

    /* Check if the acres to the immediate left or right should be displayed */
    nearest_bx = bx - 1;
    if ((where_bitfield & 1) != 0 && mFI_BlockCheck(nearest_bx, bz)) {
        mFI_BGDispMake(&disp_bitfield, nearest_bx, bz);
    } else {
        nearest_bx = bx + 1;
        if (((where_bitfield >> 2) & 1) != 0 && mFI_BlockCheck(nearest_bx, bz)) {
            mFI_BGDispMake(&disp_bitfield, nearest_bx, bz);
        }
    }

    nearest_bz = bz - 1;
    if (((where_bitfield >> 3) & 1) != 0 && mFI_BlockCheck(bx, nearest_bz)) {
        mFI_BGDispMake(&disp_bitfield, bx, nearest_bz); /* display acre immediately above */

        nearest_bx = bx - 1;
        if ((where_bitfield & 1) != 0 && mFI_BlockCheck(nearest_bx, nearest_bz)) {
            mFI_BGDispMake(&disp_bitfield, nearest_bx, nearest_bz); /* display acre above and to the left */
        } else {
            nearest_bx = bx + 1;
            if (((where_bitfield >> 2) & 1) != 0 && mFI_BlockCheck(nearest_bx, nearest_bz)) {
                mFI_BGDispMake(&disp_bitfield, nearest_bx, nearest_bz); /* display acre above and to the right */
            }
        }
    } else {
        nearest_bz = bz + 1;

        if (((where_bitfield >> 5) & 1) != 0 && mFI_BlockCheck(bx, nearest_bz)) {
            mFI_BGDispMake(&disp_bitfield, bx, nearest_bz); /* display acre immediately below */

            nearest_bx = bx - 1;
            if ((where_bitfield & 1) != 0 && mFI_BlockCheck(nearest_bx, nearest_bz)) {
                mFI_BGDispMake(&disp_bitfield, nearest_bx, nearest_bz); /* display acre below and to the left */
            } else {
                nearest_bx = bx + 1;
                if (((where_bitfield >> 2) & 1) != 0 && mFI_BlockCheck(nearest_bx, nearest_bz)) {
                    mFI_BGDispMake(&disp_bitfield, nearest_bx, nearest_bz); /* display acre below and to the right */
                }
            }
        }
    }

    for (i = 0; i < mFM_VISIBLE_BLOCK_NUM; i++) {
        if (((disp_bitfield >> i) & 1) != 1) {
            g_fdinfo->bg_draw_info[i].dma_loaded = FALSE;
            g_fdinfo->bg_draw_info[i].block_x = 0xFF;
            g_fdinfo->bg_draw_info[i].block_z = 0xFF;
            mFI_ClearRegisterBgInfoIdx(i);
        }
    }
}

static u32 l_mfi_player_bk_kind;

static void mFI_SetPlayerBlockKind(xyz_t wpos) {
    u32* dst = &l_mfi_player_bk_kind;
    int bx;
    int bz;

    dst[0] = mRF_BLOCKKIND_NONE;

    if (mFI_Wpos2BlockNum(&bx, &bz, wpos) == TRUE) {
        dst[0] = mFI_BkNum2BlockKind(bx, bz);
    }
}

extern int mFI_CheckInIsland() {
    int res = FALSE;

    if ((l_mfi_player_bk_kind & mRF_BLOCKKIND_OCEAN) || Save_Get(scene_no) == SCENE_COTTAGE_MY ||
        Save_Get(scene_no) == SCENE_COTTAGE_NPC) {
        res = TRUE;
    }

    return res;
}

extern int mFI_CheckInJustIslandOutdoor() {
    if (Save_Get(scene_no) == SCENE_FG && (l_mfi_player_bk_kind & mRF_BLOCKKIND_ISLAND)) {
        return TRUE;
    }

    return FALSE;
}

extern u32 mFI_CheckPlayerBlockInfo() {
    return l_mfi_player_bk_kind;
}

extern mActor_name_t* mFI_BkNumtoUtFGTop(int bx, int bz) {
    mActor_name_t* fg_top = NULL;

    if (mFI_CheckFieldData() && mFI_BlockCheck(bx, bz)) {
        int num = mFI_GetBlockNum(bx, bz);

        fg_top = g_fdinfo->block_info[num].fg_info.items_p;
    }

    return fg_top;
}

extern mActor_name_t* mFI_BkNum2UtFGTop_layer(int bx, int bz, int layer) {
    mActor_name_t* fg_layer_top = NULL;

    if (mFI_CheckFieldData() && g_fdinfo->fg2_p != NULL && bx == 0 && bz == 0) {
        if (layer == 0) {
            fg_layer_top = mFI_BkNumtoUtFGTop(bx, bz);
        } else if (layer > 0 && layer < mHm_LAYER_NUM) {
            fg_layer_top = g_fdinfo->fg2_p[layer - 1];
        }
    }

    return fg_layer_top;
}

extern mActor_name_t* mFI_UtNum2UtFG(int ut_x, int ut_z) {
    int bx;
    int bz;

    if (mFI_UtNumCheck(ut_x, ut_z, mFI_GetBlockXMax(), mFI_GetBlockZMax()) == FALSE) {
        return NULL;
    } else if (mFI_UtNum2BlockNum(&bx, &bz, ut_x, ut_z) == FALSE) {
        return NULL;
    } else {
        int b_ut_x;
        int b_ut_z;
        int num;
        mActor_name_t* fg_p;

        mFI_GetUtNumInBK(&b_ut_x, &b_ut_z, ut_x, ut_z);
        num = mFI_GetBlockNum(bx, bz);
        fg_p = g_fdinfo->block_info[num].fg_info.items_p;

        if (fg_p == NULL) {
            return NULL;
        } else {
            int idx = b_ut_z * UT_X_NUM + b_ut_x;
            fg_p += idx;
            return fg_p;
        }
    }
}

static mActor_name_t* mFI_UtNum2UtFG2(int ut_x, int ut_z) {
    mActor_name_t* fg2 = NULL;
    int bx;
    int bz;
    int b_ut_x;
    int b_ut_z;

    if (mFI_UtNumCheck(ut_x, ut_z, mFI_GetBlockXMax(), mFI_GetBlockZMax()) &&
        mFI_UtNum2BlockNum(&bx, &bz, ut_x, ut_z)) {
        mFI_GetUtNumInBK(&b_ut_x, &b_ut_z, ut_x, ut_z);
        fg2 = mFI_BkNum2UtFGTop_layer(bx, bz, 1);

        if (fg2 != NULL) {
            int idx = b_ut_z * UT_Z_NUM + b_ut_x;
            fg2 += idx;
        }
    }

    return fg2;
}

extern mActor_name_t* mFI_GetUnitFG(xyz_t wpos) {
    int ut_x;
    int ut_z;

    if (mFI_Wpos2UtNum(&ut_x, &ut_z, wpos) == FALSE) {
        return NULL;
    } else {
        return mFI_UtNum2UtFG(ut_x, ut_z);
    }
}

extern mActor_name_t* mFI_GetUnitFG2(xyz_t wpos) {
    int ut_x;
    int ut_z;

    if (mFI_Wpos2UtNum(&ut_x, &ut_z, wpos) == FALSE) {
        return NULL;
    } else {
        return mFI_UtNum2UtFG2(ut_x, ut_z);
    }
}

extern int mFI_GetBlockUtNum2FG(mActor_name_t* item, int bx, int bz, int ut_x, int ut_z) {
    int res = FALSE;

    if (mFI_BlockCheck(bx, bz) && (ut_x >= 0 && ut_x < UT_X_NUM) && (ut_z >= 0 && ut_z < UT_Z_NUM)) {
        int num = mFI_GetBlockNum(bx, bz);
        int ut_num = mFI_GetUtNum(ut_x, ut_z);

        res = TRUE;
        item[0] = g_fdinfo->block_info[num].fg_info.items_p[ut_num];
    } else {
        item[0] = RSV_NO;
    }

    return res;
}

extern int mFI_BlockUtNumtoFGSet(mActor_name_t item, int bx, int bz, int ut_x, int ut_z) {
    int res = FALSE;
    mActor_name_t* fg_p = mFI_BkNumtoUtFGTop(bx, bz);

    if (fg_p != NULL && (ut_x >= 0 && ut_x < UT_X_NUM) && (ut_z >= 0 && ut_z < UT_Z_NUM)) {
        int ut_num = mFI_GetUtNum(ut_x, ut_z);

        res = TRUE;
        fg_p[ut_num] = item;
    }

    return res;
}

extern int mFI_UtNumtoFGSet_common(mActor_name_t item, int ut_x, int ut_z, int update) {
    int bx;
    int bz;
    int b_ut_x;
    int b_ut_z;
    int block_num;
    int ut_num;

    if (mFI_UtNumCheck(ut_x, ut_z, mFI_GetBlockXMax(), mFI_GetBlockZMax()) == FALSE) {
        return FALSE;
    }

    if (mFI_UtNum2BlockNum(&bx, &bz, ut_x, ut_z) == FALSE) {
        return FALSE;
    }

    block_num = mFI_GetBlockNum(bx, bz);
    if (g_fdinfo->block_info[block_num].fg_info.fg_id == 203) {
        return FALSE;
    }

    mFI_GetUtNumInBK(&b_ut_x, &b_ut_z, ut_x, ut_z);
    ut_num = mFI_GetUtNum(b_ut_x, b_ut_z);
    g_fdinfo->block_info[block_num].fg_info.items_p[ut_num] = item;

    if (update) {
        mFI_SetFGUpData();
    }

    return TRUE;
}

static int mFI_UtNum2FGSet_layer(mActor_name_t item, int ut_x, int ut_z, int layer) {
    int bx;
    int bz;
    int b_ut_x;
    int b_ut_z;
    int num;
    int res = FALSE;

    if (mFI_UtNumCheck(ut_x, ut_z, mFI_GetBlockXMax(), mFI_GetBlockZMax()) == TRUE &&
        mFI_UtNum2BlockNum(&bx, &bz, ut_x, ut_z) == TRUE) {
        mActor_name_t* fg_layer_p = mFI_BkNum2UtFGTop_layer(bx, bz, layer);

        if (fg_layer_p != NULL) {
            mFI_GetUtNumInBK(&b_ut_x, &b_ut_z, ut_x, ut_z);
            num = mFI_GetUtNum(b_ut_x, b_ut_z);
            fg_layer_p[num] = item;
            mFI_SetFGUpData();
            res = TRUE;
        }
    }

    return res;
}

extern int mFI_SetFG_common(mActor_name_t item, xyz_t wpos, int update) {
    int ut_x;
    int ut_z;

    if (mFI_Wpos2UtNum(&ut_x, &ut_z, wpos) == FALSE) {
        return FALSE;
    }

    return mFI_UtNumtoFGSet_common(item, ut_x, ut_z, update);
}

extern int mFI_SetFG2(mActor_name_t item, xyz_t wpos) {
    int ut_x;
    int ut_z;
    int res = FALSE;

    if (mFI_Wpos2UtNum(&ut_x, &ut_z, wpos) == TRUE) {
        mFI_UtNum2FGSet_layer(item, ut_x, ut_z, 1);
        res = TRUE;
    }

    return res;
}

extern void mFI_InitItemTable(mFI_item_table_c* vis_block_info) {
    mFI_block_tbl_c* block_table = vis_block_info->block_info_tbl;
    int i;

    vis_block_info->count = 0;
    for (i = 0; i < mFM_VISIBLE_BLOCK_NUM; i++) {
        block_table->block_x = -1;
        block_table->block_z = -1;
        block_table->pos_x = 0.0f;
        block_table->pos_z = 0.0f;
        block_table->items = NULL;

/* @BUG - they forgot to increment the pointer */
#ifdef BUGFIXES
        block_table++;
#endif
    }
}

static void mFI_SetOldItemTableIdx(int n, int idx) {
    g_fdinfo->last_bg_idx[n] = idx;
}

extern int mFI_GetOldItemTableIdx(int n) {
    return g_fdinfo->last_bg_idx[n];
}

static void mFI_MakeOldItemTableIdxTable(mFI_block_tbl_c* block_table, int count, int* block_x_tbl, int* block_z_tbl,
                                         int num) {
    int i;
    int j;

    for (i = 0; i < count; i++) {
        if ((int)block_table->block_x != -1 && (int)block_table->block_z != -1) {
            int* bx_p = block_x_tbl;
            int* bz_p = block_z_tbl;

            for (j = 0; j < num; j++) {
                if (*bx_p == block_table->block_x && *bz_p == block_table->block_z) {
                    mFI_SetOldItemTableIdx(i, j);
                    break;
                }
                bx_p++;
                bz_p++;
            }

            if (j == num) {
                mFI_SetOldItemTableIdx(i, -1);
            }
        }

        block_table++;
    }
}

static void mFI_SetBlockTable(mFI_block_tbl_c* block_table, int bx, int bz) {
    f32 x = 0.0f;
    f32 z = 0.0f;
    int num = mFI_GetBlockNum(bx, bz);

    block_table->items = g_fdinfo->block_info[num].fg_info.items_p;
    block_table->block_x = bx;
    block_table->block_z = bz;

    mFI_BkNum2WposXZ(&x, &z, bx, bz);
    block_table->pos_x = x;
    block_table->pos_z = z;
}

extern int mFI_GetItemTable_NoReset(mFI_item_table_c* item_table, xyz_t wpos) {
    static int table_no[3] = { 0, 1, 1 };
    static int check_x[3] = { 0, 1, -1 };

    mFM_field_draw_info_c* bg_disp = mFI_BGDisplayListTop();
    int t_no;
    u8 _num = 0;
    u8 _bitfield = 0;
    u8 clear_tree_cut_bitfield = 0;
    int bx;
    int bz;
    int block_x_tbl[mFM_VISIBLE_BLOCK_NUM];
    int block_z_tbl[mFM_VISIBLE_BLOCK_NUM];
    int i;
    int j;

    if (mFI_Wpos2BlockNum(&bx, &bz, wpos) == FALSE) {
        return FALSE;
    }

    for (i = 0; i < mFM_VISIBLE_BLOCK_NUM; i++) {
        block_x_tbl[i] = item_table->block_info_tbl[i].block_x;
        block_z_tbl[i] = item_table->block_info_tbl[i].block_z;
    }

    for (i = 0; i < mFM_VISIBLE_BLOCK_NUM; i++) {
        if (mFI_CheckFinishBgDma(i) == TRUE && bg_disp->block_z == bz) {
            for (j = 0; j < 3; j++) {
                int bx_near = bx + check_x[j];

                t_no = table_no[j];

                if (bg_disp->block_x == bx_near) {
                    mFI_SetBlockTable(&item_table->block_info_tbl[t_no], bx_near, bz);
                    _num++;
                    _bitfield |= (1 << i);

                    if ((Common_Get(remove_cut_tree_info_bitfield) >> i) & 1) {
                        clear_tree_cut_bitfield |= (1 << t_no);
                    }

                    break;
                }
            }
        }

        if (_num >= 2) {
            break;
        }

        bg_disp++;
    }

    bg_disp = mFI_BGDisplayListTop();
    for (i = 0; i < mFM_VISIBLE_BLOCK_NUM; i++) {
        if (((_bitfield >> i) & 1) == 0 && mFI_CheckFinishBgDma(i) == TRUE && bg_disp->block_x != 0xFF &&
            bg_disp->block_z != 0xFF) {
            mFI_SetBlockTable(&item_table->block_info_tbl[_num], bg_disp->block_x, bg_disp->block_z);

            if ((Common_Get(remove_cut_tree_info_bitfield) >> i) & 1) {
                clear_tree_cut_bitfield |= (1 << _num);
            }

            _num++;
        }

        if (_num >= mFM_VISIBLE_BLOCK_NUM) {
            break;
        }

        bg_disp++;
    }

    Common_Set(remove_cut_tree_info_bitfield, clear_tree_cut_bitfield);

    /* Clear any unused entries */
    for (i = _num; i < mFM_VISIBLE_BLOCK_NUM; i++) {
        item_table->block_info_tbl[i].block_x = 0xFF;
        item_table->block_info_tbl[i].block_z = 0xFF;
    }

    mFI_MakeOldItemTableIdxTable(item_table->block_info_tbl, _num, block_x_tbl, block_z_tbl, item_table->count);
    item_table->count = _num;

    return TRUE;
}

extern int mFI_GetItemTable(mFI_item_table_c* item_table, xyz_t wpos, char* file, int line) {
    g_fdinfo->update_fg = FALSE;
    g_fdinfo->born_item = FALSE;
    return mFI_GetItemTable_NoReset(item_table, wpos);
}

extern int mFI_FGisUpDate() {
    if (mFI_CheckFieldData()) {
        return g_fdinfo->update_fg & 1;
    }

    return FALSE;
}

extern void mFI_SetFGUpData() {
    if (mFI_CheckFieldData()) {
        g_fdinfo->update_fg = TRUE;
    }
}

/* 50% */

extern void mFI_BornItemON() {
    if (mFI_CheckFieldData()) {
        g_fdinfo->born_item = TRUE;
    }
}

/* @unused @fabricated */
/*
extern MATCH_FORCESTRIP void mFI_BornItemOFF() {
  if (mFI_CheckFieldData()) {
    g_fdinfo->born_item = FALSE;
  }
}
*/

extern int mFI_ItemisBorn() {
    return g_fdinfo->born_item & 1;
}

extern int mFI_ActorisBorn() {
    return g_fdinfo->born_actor & 1;
}

extern void mFI_SetBearActor(GAME_PLAY* play, xyz_t wpos, int set_flag) {
    int bx;
    int bz;

    g_fdinfo->born_actor = TRUE;
    mFI_Wpos2BlockNum(&bx, &bz, wpos);

    if (set_flag == FALSE) {
        play->last_block_table.block_x = -1;
        play->last_block_table.block_z = -1;
        play->last_block_table.items = NULL;
    } else {
        mem_copy((u8*)&play->last_block_table, (u8*)&play->block_table, sizeof(mFI_block_tbl_c));
    }

    mFI_SetBlockTable(&play->block_table, bx, bz);
}

extern int mFI_search_unit_around(xyz_t* wpos, mActor_name_t item) {
    static f32 BI_chk_pos[9 * 2] = {
        -40.0f, -40.0f, // x - 1, z - 1 (top-left)
        -40.0f, 40.0f,  // x - 1, z + 1 (bottom-left)
        40.0f,  40.0f,  // x + 1, z + 1 (bottom-right)
        40.0f,  -40.0f, // x + 1, z - 1 (top-right)
        -40.0f, 0.0f,   // x - 1, z (left)
        0.0f,   40.0f,  // x, z + 1 (below)
        40.0f,  0.0f,   // x + 1, z (right)
        0.0f,   -40.0f, // x, z - 1 (above)
        0.0f,   0.0f    // x, z (origin)
    };
    xyz_t tpos;
    mActor_name_t* item_p;
    int i = 9;
    int res = FALSE;
    f32* around = BI_chk_pos;

    while (i != 0) {
        i--;

        tpos.x = wpos->x + around[i * 2 + 0];
        tpos.z = wpos->z + around[i * 2 + 1];

        item_p = mFI_GetUnitFG(tpos);
        if (item_p != NULL && item_p[0] == item) {
            xyz_t_move(wpos, &tpos);
            res = TRUE;
            break;
        }
    }

    return res;
}

/* @unused @frabricated */
extern MATCH_FORCESTRIP int mFI_search_unit_around2(xyz_t* wpos, mActor_name_t item) {
    static f32 BI_chk_pos[9 * 2] = {
        -40.0f, -40.0f, // x - 1, z - 1 (top-left)
        -40.0f, 40.0f,  // x - 1, z + 1 (bottom-left)
        40.0f,  40.0f,  // x + 1, z + 1 (bottom-right)
        40.0f,  -40.0f, // x + 1, z - 1 (top-right)
        -40.0f, 0.0f,   // x - 1, z (left)
        0.0f,   40.0f,  // x, z + 1 (below)
        40.0f,  0.0f,   // x + 1, z (right)
        0.0f,   -40.0f, // x, z - 1 (above)
        0.0f,   0.0f    // x, z (origin)
    };
    xyz_t tpos;
    mActor_name_t* item_p;
    int i = 9;
    int res = FALSE;
    f32* around = BI_chk_pos;

    while (i != 0) {
        i--;

        tpos.x = wpos->x + around[i * 2 + 0];
        tpos.z = wpos->z + around[i * 2 + 1];

        item_p = mFI_GetUnitFG2(tpos);
        if (item_p != NULL && item_p[0] == item) {
            xyz_t_move(wpos, &tpos);
            res = TRUE;
            break;
        }
    }

    return res;
}

extern int mFI_GetItemNumOnBlock(int bx, int bz, mActor_name_t min_item, mActor_name_t max_item) {
    mActor_name_t* fg_p = mFI_BkNumtoUtFGTop(bx, bz);
    int num = 0;
    int i;

    if (fg_p != NULL) {
        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if (fg_p[0] >= min_item && fg_p[0] <= max_item) {
                num++;
            }

            fg_p++;
        }
    }

    return num;
}

extern int mFI_GetItemNumOnBlockInField(int bx, int bz, mActor_name_t min_item, mActor_name_t max_item) {
    mActor_name_t* fg_p = NULL;
    int num = 0;
    int i;

    if (bx > 0 && bx <= FG_BLOCK_X_NUM && bz > 0 && bz <= FG_BLOCK_Z_NUM) {
        fg_p = Save_Get(fg)[bz - 1][bx - 1].items[0];
    }

    if (fg_p != NULL) {
        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if (fg_p[0] >= min_item && fg_p[0] <= max_item) {
                num++;
            }

            fg_p++;
        }
    }

    return num;
}

extern int mFI_GetItemNumField_BCT(mActor_name_t min_item, mActor_name_t max_item) {
    mFM_fg_c* fg = Save_Get(fg[0]);
    mActor_name_t* items_p;
    int num = 0;
    int bz;

    for (bz = 0; bz < FG_BLOCK_Z_NUM; bz++) {
        int bx;
        for (bx = 0; bx < FG_BLOCK_X_NUM; bx++) {
            int i;
            items_p = fg->items[0];
            for (i = 0; i < UT_TOTAL_NUM; i++) {
                if (items_p[0] >= min_item && items_p[0] <= max_item) {
                    num++;
                }

                items_p++;
            }

            fg++;
        }
    }

    return num;
}

extern int mFI_GetItemNumField(mActor_name_t min_item, mActor_name_t max_item) {
    int num = 0;

/* @BUG - they forgot to actually call the mFI_CheckFieldData func */
#ifndef BUGFIXES
    if (mFI_CheckFieldData) {
#else
    if (mFI_CheckFieldData()) {
#endif
        int bx_max = mFI_GetBlockXMax();
        int bz_max = mFI_GetBlockZMax();

        int bz;
        int bx;

        for (bz = 0; bz < bz_max; bz++) {
            for (bx = 0; bx < bx_max; bx++) {
                num += mFI_GetItemNumOnBlock(bx, bz, min_item, max_item);
            }
        }
    }

    return num;
}

extern int mFI_GetItemNumInBlock(mActor_name_t item, mActor_name_t* fg_items) {
    int num = 0;
    int i;

    if (fg_items != NULL) {
        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if (fg_items[0] == item) {
                num++;
            }

            fg_items++;
        }
    }

    return num;
}

extern int mFI_SearchFGInBlock(int* ut_x, int* ut_z, mActor_name_t item, int bx, int bz) {
    mActor_name_t* fg_p = mFI_BkNumtoUtFGTop(bx, bz);
    int res = FALSE;

    if (fg_p != NULL) {
        int i;

        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if (fg_p[0] == item) {
                ut_x[0] = i & 15;
                ut_z[0] = i >> 4;
                res = TRUE;

                break;
            }

            fg_p++;
        }
    }

    return res;
}

extern int mFI_CheckFGExist(mActor_name_t* check_items, int check_item_num) {
    mActor_name_t* check_p = check_items;

    if (mFI_CheckFieldData() == TRUE) {
        int bx_max = mFI_GetBlockXMax();
        int bz_max = mFI_GetBlockZMax();
        mActor_name_t* fg_p;

        int bz;

        for (bz = 0; bz < bz_max; bz++) {
            int bx;
            for (bx = 0; bx < bx_max; bx++) {
                fg_p = mFI_BkNumtoUtFGTop(bx, bz);

                if (fg_p != NULL) {
                    int ut;
                    for (ut = 0; ut < UT_TOTAL_NUM; ut++) {
                        int i;
                        check_items = check_p;

                        for (i = 0; i < check_item_num; i++) {
                            if (check_items[0] == fg_p[0]) {
                                return TRUE;
                            }

                            check_items++;
                        }

                        fg_p++;
                    }
                }
            }
        }
    }

    return FALSE;
}

extern u8* mFI_GetHaniwaStepBlock(int bx, int bz) {
    u8* haniwa_step_block_p = NULL;

    if (mFI_BlockCheck(bx, bz) == TRUE) {
        int num = mFI_GetBlockNum(bx, bz);

        haniwa_step_block_p = g_fdinfo->block_info[num].fg_info.haniwa_step;
    }

    return haniwa_step_block_p;
}

extern u16 mFI_GetMoveActorBitData(int bx, int bz) {
    u16 move_actor_bit_data = 0;

    if (mFI_BlockCheck(bx, bz)) {
        int num = mFI_GetBlockNum(bx, bz);

        move_actor_bit_data = g_fdinfo->block_info[num].fg_info.move_actor_bit_data;
    }

    return move_actor_bit_data;
}

static void mFI_MakeMoveActorBitData(int bx, int bz, mFM_move_actor_c* move_actor) {
    int num = mFI_GetBlockNum(bx, bz);
    u16* move_actor_bit_data_p = &g_fdinfo->block_info[num].fg_info.move_actor_bit_data;
    int i;

    if (move_actor_bit_data_p != NULL) {
        for (i = 0; i < mFM_MOVE_ACTOR_NUM; i++) {
            if (move_actor->name_id == EMPTY_NO) {
                break;
            }

            move_actor_bit_data_p[0] |= (1 << i);
            move_actor++;
        }
    }
}

extern void mFI_SetMoveActorBitData(int bx, int bz, u16 move_actor_bit_data) {
    if (mFI_BlockCheck(bx, bz)) {
        int num = mFI_GetBlockNum(bx, bz);

        g_fdinfo->block_info[num].fg_info.move_actor_bit_data = move_actor_bit_data;
    }
}

extern void mFI_SetMoveActorBitData_ON(s16 move_actor_idx, int bx, int bz) {
    if (mFI_BlockCheck(bx, bz) && move_actor_idx >= 0 && move_actor_idx < mFM_MOVE_ACTOR_NUM) {
        int num = mFI_GetBlockNum(bx, bz);
        u16* move_actor_bit_data_p = &g_fdinfo->block_info[num].fg_info.move_actor_bit_data;
        u16 data = move_actor_bit_data_p[0];

        move_actor_bit_data_p[0] = data | (1 << move_actor_idx);
    }
}

extern void mFI_SetMoveActorBitData_OFF(s16 move_actor_idx, int bx, int bz) {
    if (mFI_BlockCheck(bx, bz) && move_actor_idx >= 0 && move_actor_idx < mFM_MOVE_ACTOR_NUM) {
        int num = mFI_GetBlockNum(bx, bz);
        u16* move_actor_bit_data_p = &g_fdinfo->block_info[num].fg_info.move_actor_bit_data;
        u16 data = move_actor_bit_data_p[0];

        move_actor_bit_data_p[0] = data & ~(1 << move_actor_idx);
    }
}

extern void mFI_MyMoveActorBitData_ON(ACTOR* actor) {
    if (actor != NULL) {
        mFI_SetMoveActorBitData_ON(actor->move_actor_list_idx, actor->block_x, actor->block_z);
    }
}

/* @unused @fabricated */
/*
extern MATCH_FORCESTRIP void mFI_MyMoveActorBitData_OFF(ACTOR* actor) {
  if (actor != NULL) {
    mFI_SetMoveActorBitData_OFF(actor->move_actor_list_idx, actor->block_x, actor->block_z);
  }
}
*/

extern int mFI_GetMoveActorListIdx(mFM_move_actor_c* move_actor_list, int list_size, mActor_name_t actor_name) {
    int idx = -1;
    int i;

    for (i = 0; i < list_size; i++) {
        if (move_actor_list->name_id == actor_name) {
            idx = i;
            break;
        }

        move_actor_list++;
    }

    return idx;
}

extern int mFI_RegistMoveActorList(mActor_name_t actor_name, int bx, int bz, int ut_x, int ut_z, int npc_info_idx,
                                   s16 arg) {
    int num = mFI_GetBlockNum(bx, bz);
    mFM_move_actor_c* move_actor_list = g_fdinfo->block_info[num].fg_info.move_actors;
    int res = FALSE;

    if (move_actor_list != NULL) {
        int idx = mFI_GetMoveActorListIdx(move_actor_list, mFM_MOVE_ACTOR_NUM, EMPTY_NO);

        if (idx != -1) {
            move_actor_list[idx].name_id = actor_name;
            move_actor_list[idx].ut_x = ut_x;
            move_actor_list[idx].ut_z = ut_z;
            move_actor_list[idx].npc_info_idx = npc_info_idx;
            move_actor_list[idx].arg = arg;
            mFI_SetMoveActorBitData_ON(idx, bx, bz);
            res = TRUE;
        }
    }

    return res;
}

extern int mFI_UnregistMoveActorList(mActor_name_t actor_name, int bx, int bz) {
    int num = mFI_GetBlockNum(bx, bz);
    mFM_move_actor_c* move_actor_list = g_fdinfo->block_info[num].fg_info.move_actors;
    int res = FALSE;

    if (move_actor_list != NULL) {
        int idx = mFI_GetMoveActorListIdx(move_actor_list, mFM_MOVE_ACTOR_NUM, actor_name);

        if (idx != -1) {
            move_actor_list[idx].name_id = EMPTY_NO;
            mFI_SetMoveActorBitData_OFF(idx, bx, bz);
            res = TRUE;
        }
    }

    return res;
}

extern int mFI_AddMoveActorList(mActor_name_t actor_name, int bx, int bz, int ut_x, int ut_z, s16 arg) {
    int res = FALSE;

    if (ITEM_NAME_GET_TYPE(actor_name) == NAME_TYPE_ITEM2 && mFI_BlockCheck(bx, bz)) {
        res = mFI_RegistMoveActorList(actor_name, bx, bz, ut_x, ut_z, -1, arg);
    }

    return res;
}

extern mFM_move_actor_c* mFI_MoveActorListDma(int bx, int bz) {
    static mFM_move_actor_c l_aclist[mFM_MOVE_ACTOR_NUM];

    mFM_move_actor_c* move_actor_list = NULL;
    int num = mFI_GetBlockNum(bx, bz);

    if (mFI_BlockCheck(bx, bz)) {
        move_actor_list = l_aclist;
        bcopy(g_fdinfo->block_info[num].fg_info.move_actors, move_actor_list,
              mFM_MOVE_ACTOR_NUM * sizeof(mFM_move_actor_c));
    }

    return move_actor_list;
}

extern void mFI_InitMoveActorBitData() {
    int bx_max = mFI_GetBlockXMax();
    int bz_max = mFI_GetBlockZMax();
    int bz;

    for (bz = 0; bz < bz_max; bz++) {
        int bx;

        for (bx = 0; bx < bx_max; bx++) {
            mFM_move_actor_c* move_actor_list = mFI_MoveActorListDma(bx, bz);

            if (move_actor_list != NULL) {
                mFI_MakeMoveActorBitData(bx, bz, move_actor_list);
            }
        }
    }
}

static int l_player_wade;

extern void mFI_SetPlayerWade(GAME* game) {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR_GAME(game);

    if (player != NULL) {
        if (mPlib_check_player_actor_main_index_AllWade(game) == TRUE) {
            if (l_player_wade == mFI_WADE_NONE || l_player_wade == mFI_WADE_END) {
                l_player_wade = mFI_WADE_START;
            } else {
                l_player_wade = mFI_WADE_INPROGRESS;
            }
        } else if (l_player_wade == mFI_WADE_INPROGRESS) {
            l_player_wade = mFI_WADE_END;
        } else {
            l_player_wade = mFI_WADE_NONE;
        }
    } else {
        l_player_wade = mFI_WADE_ERROR;
    }
}

extern int mFI_CheckPlayerWade(int wade) {
    int res = FALSE;

    if (wade == l_player_wade) {
        res = TRUE;
    }

    return res;
}

extern int mFI_GetPlayerWade() {
    return l_player_wade;
}

extern int mFI_GetNextBlockNum(int* bx, int* bz) {
    xyz_t end_pos = { 0.0f, 0.0f, 0.0f };
    int res = FALSE;
    int res2;

    if (Common_Get(player_actor_exists)) {
        res = ((*GET_PLAYER_ACTOR_NOW()->Get_WadeEndPos_proc)(gamePT, &end_pos));
    }

    res2 = mFI_Wpos2BlockNum(bx, bz, end_pos);
    res2 &= res;
    return res2;
}

extern u16* mFI_GetDepositP(int bx, int bz) {
    u16* deposit_p = NULL;

    if (mFI_CheckFieldData() == FALSE || mFI_GET_TYPE(mFI_GetFieldId()) != mFI_FIELD_FG) {
        if (bx - 1 >= 0 && bx - 1 < FG_BLOCK_X_NUM && bz - 1 >= 0 && bz - 1 < FG_BLOCK_Z_NUM) {
            deposit_p = Save_Get(deposit[(bx - 1) + (bz - 1) * FG_BLOCK_X_NUM]);
        }
    } else if (mFI_BlockCheck(bx, bz) == TRUE) {
        deposit_p = g_fdinfo->block_info[bx + bz * mFI_GetBlockXMax()].fg_info.deposit_p;
    }

    return deposit_p;
}

extern void mFI_ClearDeposit(int bx, int bz) {
    u16* deposit_p = mFI_GetDepositP(bx, bz);

    if (deposit_p != NULL) {
        int i;

        for (i = 0; i < UT_Z_NUM; i++) {
            deposit_p[0] = 0;
            deposit_p++;
        }
    }
}

static int mFI_LineDepositON(u16* deposit, int ut_x) {
    deposit[0] |= (1 << ut_x);
    return TRUE;
}

static int mFI_LineDepositOFF(u16* deposit, int ut_x) {
    deposit[0] &= ~(1 << ut_x);
    return FALSE;
}

extern int mFI_GetLineDeposit(u16* deposit, int ut_x) {
    return (deposit[0] >> ut_x) & 1;
}

typedef int (*mFI_SET_DEPOSIT_PROC)(u16*, int);

static int mFI_SetDeposit(u16* deposit, int ut_x, int ut_z, int type) {
    static mFI_SET_DEPOSIT_PROC control_proc[mFI_DEPOSIT_NUM] = { &mFI_LineDepositON, &mFI_LineDepositOFF,
                                                                  &mFI_GetLineDeposit };

    int res = FALSE;

    if (deposit != NULL && ut_x >= 0 && ut_x < UT_X_NUM && ut_z >= 0 && ut_z < UT_Z_NUM) {
        res = (*control_proc[type])(deposit + ut_z, ut_x);
    }

    return res;
}

/* @unused, @fabricated */
/*
extern MATCH_FORCESTRIP void mFI_BlockDepositON(u16* deposit_p, int ut_x, int ut_z) {
  mFI_SetDeposit(deposit_p, ut_x, ut_z, mFI_DEPOSIT_ON);
}
*/

extern void mFI_BlockDepositOFF(u16* deposit_p, int ut_x, int ut_z) {
    mFI_SetDeposit(deposit_p, ut_x, ut_z, mFI_DEPOSIT_OFF);
}

extern int mFI_GetBlockDeposit(u16* deposit_p, int ut_x, int ut_z) {
    return mFI_SetDeposit(deposit_p, ut_x, ut_z, mFI_DEPOSIT_GET);
}

static int mFI_BkUtNum2SetDeposit(int bx, int bz, int ut_x, int ut_z, int type) {
    int res = FALSE;
    u16* deposit_p = mFI_GetDepositP(bx, bz);

    if (deposit_p != NULL) {
        res = mFI_SetDeposit(deposit_p, ut_x, ut_z, type);
    }

    return res;
}

/* @unused @fabricated */
/*
extern MATCH_FORCESTRIP void mFI_BkUtNum2DepositON(int bx, int bz, int ut_x, int ut_z) {
  mFI_BkUtNum2SetDeposit(bx, bz, ut_x, ut_z, mFI_DEPOSIT_ON);
}
*/

extern void mFI_BkUtNum2DepositOFF(int bx, int bz, int ut_x, int ut_z) {
    mFI_BkUtNum2SetDeposit(bx, bz, ut_x, ut_z, mFI_DEPOSIT_OFF);
}

/* @unused @fabricated */
/*
extern MATCH_FORCESTRIP int mFI_BkUtNum2DepositGet(int bx, int bz, int ut_x, int ut_z) {
  return mFI_BkUtNum2SetDeposit(bx, bz, ut_x, ut_z, mFI_DEPOSIT_GET);
}
*/

static int mFI_UtNum2SetDeposit(int ut_x, int ut_z, int type) {
    int res = FALSE;
    int bx;
    int bz;
    int b_ut_x;
    int b_ut_z;

    if (mFI_UtNum2BlockNum(&bx, &bz, ut_x, ut_z) == TRUE && mFI_GetUtNumInBK(&b_ut_x, &b_ut_z, ut_x, ut_z) == TRUE) {
        res = mFI_BkUtNum2SetDeposit(bx, bz, b_ut_x, b_ut_z, type);
    }

    return res;
}

extern void mFI_UtNum2DepositON(int ut_x, int ut_z) {
    mFI_UtNum2SetDeposit(ut_x, ut_z, mFI_DEPOSIT_ON);
}

extern void mFI_UtNum2DepositOFF(int ut_x, int ut_z) {
    mFI_UtNum2SetDeposit(ut_x, ut_z, mFI_DEPOSIT_OFF);
}

extern int mFI_UtNum2DepositGet(int ut_x, int ut_z) {
    return mFI_UtNum2SetDeposit(ut_x, ut_z, mFI_DEPOSIT_GET);
}

extern void mFI_Wpos2DepositON(xyz_t wpos) {
    int ut_x;
    int ut_z;

    mFI_Wpos2UtNum(&ut_x, &ut_z, wpos);
    mFI_UtNum2DepositON(ut_x, ut_z);
}

extern void mFI_Wpos2DepositOFF(xyz_t wpos) {
    int ut_x;
    int ut_z;

    mFI_Wpos2UtNum(&ut_x, &ut_z, wpos);
    mFI_UtNum2DepositOFF(ut_x, ut_z);
}

extern int mFI_Wpos2DepositGet(xyz_t wpos) {
    int ut_x;
    int ut_z;

    mFI_Wpos2UtNum(&ut_x, &ut_z, wpos);
    return mFI_UtNum2DepositGet(ut_x, ut_z);
}

extern int mFI_CheckItemNoHole(mActor_name_t item) {
    int res = FALSE;

    if (item >= HOLE_START && item <= HOLE_END || item == HOLE_SHINE) {
        res = TRUE;
    }

    return res;
}

/* @unused extern int mFI_CheckCanDeposit(xyz_t wpos?) */

static int mFI_CheckNothing(mActor_name_t* item, xyz_t wpos) {
    return FALSE;
}

static int mFI_CheckDigHole(mActor_name_t* item, xyz_t wpos) {
    int res = FALSE;

    if (mFI_CheckItemNoHole(*item) == TRUE && mFI_Wpos2DepositGet(wpos) == TRUE) {
        res = TRUE;
    }

    return res;
}

static int mFI_CheckDigHoleFillin(mActor_name_t* item, xyz_t wpos) {
    int res = FALSE;

    if (mFI_CheckItemNoHole(*item) == TRUE && mFI_Wpos2DepositGet(wpos) == FALSE) {
        res = TRUE;
    }

    return res;
}

static int mFI_CheckDigNoItem(mActor_name_t* item, xyz_t wpos) {
    int res = FALSE;

    if (*item == EMPTY_NO) {
        res = TRUE;
    }

    return res;
}

static int mFI_CheckDigRemoveItem(mActor_name_t* item, xyz_t wpos) {
    int res = FALSE;

    if ((*item >= FLOWER_LEAVES_PANSIES0 && *item <= FLOWER_TULIP2) ||
        (*item >= TREE_STUMP001 && *item <= TREE_STUMP004) || (*item >= GRASS_A && *item <= GRASS_C) ||
        (*item == TREE_SAPLING) || (*item == TREE_APPLE_SAPLING) || (*item == TREE_ORANGE_SAPLING) ||
        (*item == TREE_PEACH_SAPLING) || (*item == TREE_PEAR_SAPLING) || (*item == TREE_CHERRY_SAPLING) ||
        (*item == TREE_1000BELLS_SAPLING) || (*item == TREE_10000BELLS_SAPLING) || (*item == TREE_30000BELLS_SAPLING) ||
        (*item == TREE_100BELLS_SAPLING) || (*item == DEAD_SAPLING) ||
        (*item >= TREE_PALM_STUMP001 && *item <= TREE_PALM_STUMP004) || (*item == TREE_PALM_SAPLING) ||
        (*item == DEAD_PALM_SAPLING) || (*item >= CEDAR_TREE_STUMP001 && *item <= CEDAR_TREE_STUMP004) ||
        (*item == CEDAR_TREE_SAPLING) || (*item == DEAD_CEDAR_SAPLING) ||
        (*item >= GOLD_TREE_STUMP001 && *item <= GOLD_TREE_STUMP004) || (*item == GOLD_TREE_SAPLING) ||
        (*item == DEAD_GOLD_SAPLING)) {
        res = TRUE;
    }

    return res;
}

static int mFI_CheckDigGetItem(mActor_name_t* item, xyz_t wpos) {
    int res = FALSE;

    if (mFI_Wpos2DepositGet(wpos) == TRUE) {
        if (mFI_CheckItemNoHole(*item) == FALSE) {
            res = TRUE;
        }
    } else {
        int valid = (*item >= BURIED_PITFALL_HOLE_START && *item <= BURIED_PITFALL_HOLE_END) || *item == SHINE_SPOT;

        if (valid == TRUE) {
            item[0] = bg_item_fg_sub_dig2take_conv(*item);
            res = TRUE;
        }
    }

    return res;
}

static int mFI_CheckDigDiffPosArea(xyz_t wpos0, xyz_t wpos1) {
    int res = FALSE;

    if ((wpos0.x > wpos1.x + mFI_UT_WORLDSIZE_HALF_X_F) || (wpos0.x < wpos1.x - mFI_UT_WORLDSIZE_HALF_X_F) ||
        (wpos0.z > wpos1.z + mFI_UT_WORLDSIZE_HALF_Z_F) || (wpos0.z < wpos1.z - mFI_UT_WORLDSIZE_HALF_Z_F)) {
        res = TRUE;
    }

    return res;
}

typedef int (*mFI_DIG_CHECK_PROC)(mActor_name_t*, xyz_t);

extern int mFI_GetDigStatus(mActor_name_t* item, xyz_t wpos, int golden_shovel) {
    int status = mFI_DIGSTATUS_CANCEL;
    mActor_name_t* dig_item_p = mFI_GetUnitFG(wpos);
    item[0] = EMPTY_NO;

    if (dig_item_p != NULL) {
        item[0] = dig_item_p[0];

        if (mCoBG_CheckHole(wpos) == TRUE) {
            static mFI_DIG_CHECK_PROC dig_check[mFI_DIGSTATUS_NUM] = { &mFI_CheckNothing,       &mFI_CheckDigHole,
                                                                       &mFI_CheckDigHoleFillin, &mFI_CheckDigNoItem,
                                                                       &mFI_CheckDigRemoveItem, &mFI_CheckDigGetItem };

            static xyz_t old_pos = { 0.0f, 0.0f, 0.0f };

            int i;

            for (i = 0; i < mFI_DIGSTATUS_NUM; i++) {
                int res = (*dig_check[i])(item, wpos);

                if (res == TRUE) {
                    status = i;

                    if (i != mFI_DIGSTATUS_DIG) {
                        break;
                    }

                    if (golden_shovel == TRUE) {

                        /* 10% chance of getting 100 bells with golden shovel */
                        if (mFI_CheckDigDiffPosArea(wpos, old_pos) == TRUE && RANDOM(10) == 1) {
                            status = mFI_DIGSTATUS_GET_ITEM;
                            item[0] = ITM_MONEY_100;
                        }
                    }

                    old_pos = wpos;
                    break;
                }
            }
        } else if (mCoBG_CheckSkySwing(wpos) == TRUE) {
            status = mFI_DIGSTATUS_MISS;
        }
    }

    return status;
}

static void mFI_ClearHoleBlock_sub(mActor_name_t* fg_items_p) {
    int i;

    if (fg_items_p == NULL) {
        return;
    }

    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if (*fg_items_p >= HOLE_START && *fg_items_p <= HOLE_END) {
            fg_items_p[0] = EMPTY_NO;
        } else if (*fg_items_p == HOLE_SHINE) {
            fg_items_p[0] = EMPTY_NO;
        }

        fg_items_p++;
    }
}

extern void mFI_ClearHoleBlock(int bx, int bz) {
    mFI_ClearHoleBlock_sub(mFI_BkNumtoUtFGTop(bx, bz));
}

extern void mFI_ClearBeecomb(int bx, int bz) {
    mActor_name_t* fg_items_p = mFI_BkNumtoUtFGTop(bx, bz);
    int i;

    if (fg_items_p != NULL) {
        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if (*fg_items_p == HONEYCOMB) {
                fg_items_p[0] = EMPTY_NO;
            }

            fg_items_p++;
        }
    }
}

static void mFI_SetFGStructureKeep(mActor_name_t* item_p, mActor_name_t replace_item, int destroy_item) {
    if (destroy_item == FALSE) {
        mPB_keep_item(*item_p);
    }

    item_p[0] = replace_item;
}

static mActor_name_t l_set_fg_table[3 * 3];

static int mFI_SetStructure11(mActor_name_t* fg_items_p, mActor_name_t replace_item, mActor_name_t fill_item, int bx,
                              int bz, int ut_x, int ut_z, int destroy_item) {
    fg_items_p += mFI_GetUtNum(ut_x, ut_z);
    mFI_SetFGStructureKeep(fg_items_p, replace_item, destroy_item);
    mFI_BkUtNum2DepositOFF(bx, bz, ut_x, ut_z);
    mCoBG_Ut2SetDefaultOffset(ut_x + bx * UT_X_NUM, ut_z + bz * UT_Z_NUM);
    return TRUE;
}

static int mFI_SetStructure21(mActor_name_t* fg_items_p, mActor_name_t replace_item, mActor_name_t fill_item, int bx,
                              int bz, int ut_x, int ut_z, int destroy_item) {
    mActor_name_t* set_fg_table = l_set_fg_table;
    int res = FALSE;

    if (ut_x >= 0 && ut_x < UT_X_NUM - 1 && ut_z >= 0 && ut_z < UT_Z_NUM - 1) {
        int i;

        for (i = 0; i < 2; i++) {
            set_fg_table[i] = fill_item;
        }

        set_fg_table[0] = replace_item;
        for (i = 0; i < 2; i++) {
            mFI_SetStructure11(fg_items_p, *set_fg_table, fill_item, bx, bz, ut_x + i, ut_z, destroy_item);
            set_fg_table++;
        }

        res = TRUE;
    }

    return res;
}

static int mFI_SetStructure22(mActor_name_t* fg_items_p, mActor_name_t replace_item, mActor_name_t fill_item, int bx,
                              int bz, int ut_x, int ut_z, int destroy_item) {
    mActor_name_t* set_fg_table = l_set_fg_table;
    int res = FALSE;

    if (ut_x >= 0 && ut_x < UT_X_NUM - 1 && ut_z >= 0 && ut_z < UT_Z_NUM - 1) {
        int i;
        int j;

        for (i = 0; i < 2 * 2; i++) {
            set_fg_table[i] = fill_item;
        }

        set_fg_table[0] = replace_item;
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                mFI_SetStructure11(fg_items_p, *set_fg_table, fill_item, bx, bz, ut_x + j, ut_z + i, destroy_item);
                set_fg_table++;
            }
        }

        res = TRUE;
    }

    return res;
}

static int mFI_SetStructure23(mActor_name_t* fg_items_p, mActor_name_t replace_item, mActor_name_t fill_item, int bx,
                              int bz, int ut_x, int ut_z, int destroy_item) {
    mActor_name_t* set_fg_table = l_set_fg_table;
    int res = FALSE;

    if (ut_x >= 0 && ut_x < UT_X_NUM - 1 && ut_z > 0 && ut_z < UT_Z_NUM - 1) {
        int i;
        int j;

        for (i = 0; i < 2 * 3; i++) {
            set_fg_table[i] = fill_item;
        }

        set_fg_table[2] = replace_item;
        for (i = -1; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                mFI_SetStructure11(fg_items_p, *set_fg_table, fill_item, bx, bz, ut_x + j, ut_z + i, destroy_item);
                set_fg_table++;
            }
        }

        res = TRUE;
    }

    return res;
}

static int mFI_SetStructure32(mActor_name_t* fg_items_p, mActor_name_t replace_item, mActor_name_t fill_item, int bx,
                              int bz, int ut_x, int ut_z, int destroy_item) {
    mActor_name_t* set_fg_table = l_set_fg_table;
    int res = FALSE;

    if (ut_x >= 0 && ut_x < UT_X_NUM - 1 && ut_z > 0 && ut_z < UT_Z_NUM - 1) {
        int i;
        int j;

        for (i = 0; i < 3 * 2; i++) {
            set_fg_table[i] = fill_item;
        }

        set_fg_table[1] = replace_item;
        for (i = 0; i < 2; i++) {
            for (j = -1; j < 2; j++) {
                mFI_SetStructure11(fg_items_p, *set_fg_table, fill_item, bx, bz, ut_x + j, ut_z + i, destroy_item);
                set_fg_table++;
            }
        }

        res = TRUE;
    }

    return res;
}

static int mFI_SetStructure33(mActor_name_t* fg_items_p, mActor_name_t replace_item, mActor_name_t fill_item, int bx,
                              int bz, int ut_x, int ut_z, int destroy_item) {
    mActor_name_t* set_fg_table = l_set_fg_table;
    int res = FALSE;

    if (ut_x > 0 && ut_x < UT_X_NUM - 1 && ut_z > 0 && ut_z < UT_Z_NUM - 1) {
        int i;
        int j;

        for (i = 0; i < 3 * 3; i++) {
            set_fg_table[i] = fill_item;
        }

        set_fg_table[4] = replace_item;
        for (i = -1; i < 2; i++) {
            for (j = -1; j < 2; j++) {
                mFI_SetStructure11(fg_items_p, *set_fg_table, fill_item, bx, bz, ut_x + j, ut_z + i, destroy_item);
                set_fg_table++;
            }
        }

        res = TRUE;
    }

    return res;
}

static int mFI_SetStructure33_main_back(mActor_name_t* fg_items_p, mActor_name_t replace_item, mActor_name_t fill_item,
                                        int bx, int bz, int ut_x, int ut_z, int destroy_item) {
    mActor_name_t* set_fg_table = l_set_fg_table;
    int res = FALSE;

    if (ut_x > 0 && ut_x < UT_X_NUM - 1 && ut_z > 0 && ut_z < UT_Z_NUM - 1) {
        int i;
        int j;

        for (i = 0; i < 3 * 3; i++) {
            set_fg_table[i] = fill_item;
        }

        set_fg_table[1] = replace_item;
        for (i = -1; i < 2; i++) {
            for (j = -1; j < 2; j++) {
                mFI_SetStructure11(fg_items_p, *set_fg_table, fill_item, bx, bz, ut_x + j, ut_z + i, destroy_item);
                set_fg_table++;
            }
        }

        res = TRUE;
    }

    return res;
}

static u8 l_structure_set_type[STRUCTURE_END - STRUCTURE_START] = {
    0x0c, 0x0c, 0x0c, 0x0c, 0x05, 0x05, 0x05, 0x05, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0c, 0x0a, 0x0a, 0x0a, 0x0a, 0x05, 0x05, 0x00, 0x06, 0x06, 0x05, 0x05, 0x06, 0x05,
    0x00, 0x06, 0x06, 0x00, 0x00, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x05, 0x05, 0x04, 0x0a, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c
};

typedef int (*mFI_SET_STRUCTURE_PROC)(mActor_name_t*, mActor_name_t, mActor_name_t, int, int, int, int, int);

extern int mFI_SetFGStructure_common(mActor_name_t structure_name, int bx, int bz, int ut_x, int ut_z, int set_type) {
    static mFI_SET_STRUCTURE_PROC set_structure[12] = {
        &mFI_SetStructure11,          &mFI_SetStructure21, &mFI_SetStructure22,           &mFI_SetStructure23,
        &mFI_SetStructure32,          &mFI_SetStructure33, &mFI_SetStructure33_main_back,

        &mFI_SetStructure11,          &mFI_SetStructure22, &mFI_SetStructure23,           &mFI_SetStructure33,
        &mFI_SetStructure33_main_back
    };

    static mActor_name_t fill_name_table[mFI_SET_STRUCTURE_NUM] = { RSV_NO, EMPTY_NO };
    static int keep_status_table[mFI_SET_STRUCTURE_NUM] = { FALSE, TRUE };

    mActor_name_t* fg_p = NULL;
    int keep_status = keep_status_table[set_type];
    int res = FALSE;

    if (mFI_CheckFieldData() == TRUE) {
        if (mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELD_FG) {
            if (mFI_BlockCheck(bx, bz) == TRUE && ITEM_NAME_GET_TYPE(structure_name) == NAME_TYPE_STRUCT) {
                fg_p = mFI_BkNumtoUtFGTop(bx, bz);
            }
        } else {
            int fg_bx = bx - 1;
            int fg_bz = bz - 1;

            if (fg_bx >= 0 && fg_bx < FG_BLOCK_X_NUM && fg_bz >= 0 && fg_bz < FG_BLOCK_Z_NUM) {
                fg_p = Save_Get(fg[fg_bz][fg_bx]).items[0];
            }
        }

        if (fg_p != NULL) {
            u8 structure_type = l_structure_set_type[(int)(structure_name - STRUCTURE_START)];

            if (structure_type < 0xC) {
                mActor_name_t fill_name = fill_name_table[set_type];

                if (set_type == mFI_SET_STRUCTURE_REMOVE) {
                    if (structure_type >= 7) {
                        structure_name = mFM_GetReseveName(bx, bz);
                    } else {
                        structure_name = fill_name;
                    }
                }

                res =
                    (*set_structure[structure_type])(fg_p, structure_name, fill_name, bx, bz, ut_x, ut_z, keep_status);

                if (res == TRUE) {
                    mFI_SetFGUpData();
                }
            }
        }
    }

    return res;
}

extern int mFI_CheckStructureArea(int ut_x, int ut_z, mActor_name_t structure_name, int structure_ut_x,
                                  int structure_ut_z) {
    static s8 set_area_table[12][4] = { { 0, 0, 0, 0 },   { 0, 1, 0, 0 },   { 0, 1, 0, 1 },   { -1, 1, 0, 1 },
                                        { -1, 1, -1, 1 }, { -1, 1, -1, 1 }, { 0, 0, 0, 0 },

                                        { 0, 1, 0, 1 },   { -1, 1, -1, 1 }, { -1, 1, -1, 1 }, { 0, 0, 0, 0 },
                                        { 0, 0, 0, 0 } };

    int start_x = structure_ut_x;
    int start_z = structure_ut_z;
    u8 structure_type;
    s8* set_area;
    int end_x = structure_ut_x;
    int end_z = structure_ut_z;
    int z;

    if (ITEM_NAME_GET_TYPE(structure_name) == NAME_TYPE_STRUCT) {
        structure_type = l_structure_set_type[(int)(structure_name - STRUCTURE_START)];

        if (structure_type < 12) {
            set_area = set_area_table[structure_type];

            start_x += set_area[0];
            end_x += set_area[1];
            start_z += set_area[2];
            end_z += set_area[3];
        }
    }

    for (z = start_z; z < end_z + 1; z++) {
        int x;
        for (x = start_x; x < end_x + 1; x++) {
            if (ut_x == x && ut_z == z) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

/*
 * @BUG: The RNG call will only be in the range [0, 3],
 * meaning you can never get an orange unless your town's
 * fruit is peaches and you roll a 3 (peach).
 *
 * Additionally, this function is "bad" because it gives a 50% chance
 * for the next fruit to be rolled if you have apples, pears, or cherries.
 * The other two fruits are 25% each.
 */
#ifndef BUGFIXES
extern mActor_name_t mFI_GetOtherFruit() {
    mActor_name_t other_fruit = ITM_FOOD_START | RANDOM(4);

    if (other_fruit == Save_Get(fruit)) {
        other_fruit++;
    }

    return other_fruit;
}
#else
/* This implementation gives an equal 25% chance for all non-native fruit to be rolled */
extern mActor_name_t mFI_GetOtherFruit() {
    mActor_name_t other_fruit = ITM_FOOD_START | RANDOM(4);

    /* simple fix is to add one if the random fruit is also greater than the town fruit */
    if (other_fruit >= Save_Get(fruit)) {
        other_fruit++;
    }

    return other_fruit;
}
#endif

extern int mFI_CheckFGNpcOn(mActor_name_t item) {
    int res = FALSE;

    if (item == EMPTY_NO) {
        res = TRUE;
    } else {
        switch (ITEM_NAME_GET_TYPE(item)) {
            case NAME_TYPE_ITEM0: {
                if ((item == TREE_SAPLING) || (item == TREE_APPLE_SAPLING) || (item == TREE_ORANGE_SAPLING) ||
                    (item == TREE_PEACH_SAPLING) || (item == TREE_PEAR_SAPLING) || (item == TREE_CHERRY_SAPLING) ||
                    (item == TREE_1000BELLS_SAPLING) || (item == TREE_10000BELLS_SAPLING) ||
                    (item == TREE_30000BELLS_SAPLING) || (item == TREE_100BELLS_SAPLING) ||
                    (item == TREE_PALM_SAPLING) || (item == CEDAR_TREE_SAPLING) || (item == GOLD_TREE_SAPLING) ||
                    (item >= FLOWER_LEAVES_PANSIES0 && item <= FLOWER_TULIP2) || (item >= GRASS_A && item <= GRASS_C)) {
                    res = TRUE;
                }

                break;
            }

            case NAME_TYPE_FTR0:
            case NAME_TYPE_ITEM1:
            case NAME_TYPE_FTR1:
            case NAME_TYPE_WARP:
            case NAME_TYPE_ITEM2: {
                res = TRUE;
                break;
            }
        }
    }

    return res;
}

extern int mFI_CheckLapPolice(int bx, int bz, int ut_x, int ut_z) {
    int p_bx;
    int p_bz;
    int p_ut_x;
    int p_ut_z;

    int res = FALSE;

    if (mFI_CheckFieldData() == TRUE && mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELD_FG) {
        mFM_GetPolicePos(&p_bx, &p_bz, &p_ut_x, &p_ut_z);

        if (bx == p_bx && bz == p_bz && ut_x == p_ut_x && ut_z == p_ut_z) {
            res = TRUE;
        }
    }

    return res;
}

extern int mFI_GetWaveUtinBlock(int* ut_x, int* ut_z, int bx, int bz) {
    mCoBG_Collision_u* col_p;
    mCoBG_Collision_u* col;
    int num;
    int sel;
    int i;
    int res;

    num = 0;
    res = FALSE;
    ut_x[0] = 0;
    ut_z[0] = 0;

    col_p = mFI_GetBkNum2ColTop(bx, bz);
    col = col_p;

    if (col_p != NULL) {
        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if (mCoBG_CheckWaveAttr(col_p->data.unit_attribute) == TRUE) {
                num++;
            }

            col_p++;
        }

        if (num > 0) {
            col_p = col;
            sel = RANDOM(num);

            for (i = 0; i < UT_TOTAL_NUM; i++) {
                if (mCoBG_CheckWaveAttr(col_p->data.unit_attribute) == TRUE) {
                    if (sel <= 0) {
                        ut_x[0] = i & 0xF;
                        ut_z[0] = i >> 4;
                        res = TRUE;

                        break;
                    } else {
                        sel--;
                    }
                }

                col_p++;
            }
        }
    }

    return res;
}

extern int mFI_ClearBlockItemRandom_common(mActor_name_t item, int clear_num, mActor_name_t* fg_p, u16* deposit_p,
                                           int delete_buried) {
    static u16 candidate[UT_Z_NUM];

    u16* candidate_p = candidate;
    mActor_name_t* fg_p2 = fg_p;
    u16* deposit_p2 = deposit_p;
    int num = 0;
    int selected;
    int cleared_num = 0;
    int ut_z;
    int ut_x;

    if (clear_num > 0 && clear_num <= UT_TOTAL_NUM) {
        if (fg_p != NULL) {
            bzero(candidate, sizeof(candidate));

            for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
                for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                    if (*fg_p == item && (delete_buried == TRUE ||
                                          (deposit_p != NULL && mFI_GetLineDeposit(deposit_p, ut_x) == FALSE))) {
                        num++;
                        candidate_p[0] |= (1 << ut_x);
                    }

                    fg_p++;
                }

                deposit_p++;
                candidate_p++;
            }
        }

        if (num > 0) {
            if (num <= clear_num) {
                fg_p = fg_p2;
                deposit_p = deposit_p2;
                candidate_p = candidate;

                for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
                    for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                        if (((candidate_p[0] >> ut_x) & 1) == 1) {
                            fg_p[0] = EMPTY_NO;

                            if (delete_buried == TRUE && deposit_p != NULL) {
                                mFI_LineDepositOFF(deposit_p, ut_x);
                            }
                        }

                        fg_p++;
                    }

                    deposit_p++;
                    candidate_p++;
                }

                cleared_num = num;
            } else {
                while (clear_num != 0 && num != 0) {
                    fg_p = fg_p2;
                    deposit_p = deposit_p2;
                    candidate_p = candidate;

                    selected = RANDOM(num);

                    for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
                        for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                            if (((candidate_p[0] >> ut_x) & 1) == 1) {
                                if (selected <= 0) {
                                    fg_p[0] = EMPTY_NO;

                                    if (delete_buried == TRUE && deposit_p != NULL) {
                                        mFI_LineDepositOFF(deposit_p, ut_x);
                                    }

                                    ut_z = UT_Z_NUM;
                                    num--;
                                    break;
                                } else {
                                    selected--;
                                }
                            }

                            fg_p++;
                        }

                        deposit_p++;
                        candidate_p++;
                    }

                    cleared_num++;
                    clear_num--;
                }
            }
        }
    }

    return cleared_num;
}

static int l_reserve_set_shell;

extern void mFI_SetFirstSetShell() {
    l_reserve_set_shell = mFI_SET_SHELL_NUM;
}

static int mFI_CheckSetShell() {
    int res = FALSE;

    /* Refresh shells every 10th minute */
    if (Common_Get(time.rtc_time.min) % 10 == 0) {
        res = TRUE;
    }

    return res;
}

static int mFI_GetCanSetShellNum(u8* shell_num, int bx, int bz) {
    mCoBG_Collision_u* col_p;
    mActor_name_t* fg_p;
    u16* deposit_p;
    int valid_ut_num = 0;
    int ut_z;
    int ut_x;

    fg_p = mFI_BkNumtoUtFGTop(bx, bz);
    col_p = mFI_GetBkNum2ColTop(bx, bz);
    deposit_p = mFI_GetDepositP(bx, bz);

    if (fg_p != NULL && col_p != NULL && deposit_p != NULL) {
        for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
            for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                if (*fg_p == EMPTY_NO && mCoBG_CheckWaveAttr(col_p->data.unit_attribute) == TRUE) {
                    valid_ut_num++;
                } else if (((*fg_p >= ITM_SHELL0 && *fg_p <= ITM_SHELL7) || *fg_p == ITM_FOOD_COCONUT) &&
                           mFI_GetBlockDeposit(deposit_p, ut_x, ut_z) == FALSE) {
                    shell_num[0]++;
                }

                fg_p++;
                col_p++;
            }
        }
    }

    return valid_ut_num;
}

static u8 l_sandy_beach_bx[7] = { 1, 2, 3, 4, 5, mISL_BLOCK_X0, mISL_BLOCK_X1 };
static u8 l_sandy_beach_bz[7] = { 6, 6, 6, 6, 6, mISL_BLOCK_Z, mISL_BLOCK_Z };

static void mFI_ResearchShell(u8* can_set_ut_num, u8* on_shell_num, int* total_set_num, int* total_blocks,
                              xyz_t player_pos) {
    int player_bx;
    int player_bz;
    int i;

    mFI_Wpos2BlockNum(&player_bx, &player_bz, player_pos);
    for (i = 0; i < 7; i++) {
        int bx = l_sandy_beach_bx[i];
        int bz = l_sandy_beach_bz[i];
        /* Don't refresh shells if the player is in the acre */
        if (bx != player_bx || bz != player_bz) {
            u8 can_set_num;

            can_set_ut_num[0] = mFI_GetCanSetShellNum(on_shell_num, bx, bz);
            can_set_num = *can_set_ut_num;

            if (can_set_num != 0) {
                u8 on_num = *on_shell_num;

                if (on_shell_num[0] < mFI_MAX_SHELLS_PER_BLOCK) {
                    int add_shell_num = mFI_MAX_SHELLS_PER_BLOCK - on_num;

                    if (add_shell_num > can_set_num) {
                        u8 add = add_shell_num - can_set_num;

                        on_shell_num[0] = on_num + add;
                        total_set_num[0] += *can_set_ut_num;
                    } else {
                        total_set_num[0] += add_shell_num;
                    }

                    total_blocks[0]++;
                } else {
                    can_set_ut_num[0] = 0;
                }
            }
        }

        can_set_ut_num++;
        on_shell_num++;
    }
}

static void mFI_DivideShellSameSum(u8* can_set_ut_num, u8* shell_num_inblock, u8* on_shell_num, int* set_num,
                                   int* block_num) {
    while (set_num[0] > 0 && block_num[0] > 0 && set_num[0] > block_num[0]) {
        int i;

        for (i = 0; i < 7; i++) {
            if (can_set_ut_num[0] != 0 && on_shell_num[0] < mFI_MAX_SHELLS_PER_BLOCK) {
                shell_num_inblock[0]++;
                on_shell_num[0]++;
                set_num[0]--;

                if (on_shell_num[0] >= mFI_MAX_SHELLS_PER_BLOCK) {
                    block_num[0]--;
                }
            }

            shell_num_inblock++;
            on_shell_num++;
            can_set_ut_num++;
        }

        shell_num_inblock -= 7;
        on_shell_num -= 7;
        can_set_ut_num -= 7;
    }
}

static void mFI_DivideShellRandom(u8* can_set_ut_num, u8* shell_num_inblock, u8* on_shell_num, int set_num,
                                  int block_num) {
    u8* can_set_ut_num_p = can_set_ut_num;
    u8* shell_num_inblock_p = shell_num_inblock;
    u8* on_shell_num_p = on_shell_num;

    while (block_num > 0 && set_num > 0) {
        int selected_block;
        int i;

        can_set_ut_num_p = can_set_ut_num;
        shell_num_inblock_p = shell_num_inblock;
        on_shell_num_p = on_shell_num;
        selected_block = RANDOM(block_num);

        for (i = 0; i < 7; i++) {
            if ((int)can_set_ut_num_p[0] > 0 && on_shell_num_p[0] < mFI_MAX_SHELLS_PER_BLOCK) {
                if (selected_block <= 0) {
                    shell_num_inblock_p[0]++;
                    on_shell_num_p[0]++;

                    if (on_shell_num_p[0] >= mFI_MAX_SHELLS_PER_BLOCK) {
                        block_num--;
                    }

                    break;
                } else {
                    selected_block--;
                }
            }

            can_set_ut_num_p++;
            on_shell_num_p++;
            shell_num_inblock_p++;
        }

        set_num--;
    }
}

static void mFI_DivideShell(u8* can_set_ut_num, u8* shell_num_inblock, u8* on_shell_num, int set_num, int block_num) {
    mFI_DivideShellSameSum(can_set_ut_num, shell_num_inblock, on_shell_num, &set_num,
                           &block_num); // divide shells evenly amongst acres first
    mFI_DivideShellRandom(can_set_ut_num, shell_num_inblock, on_shell_num, set_num,
                          block_num); // randomly place remaining shells
}

static mActor_name_t mFI_GetShell(int is_island) {
    static mActor_name_t normal_shell[6] = {
        ITM_SHELL0, // lion's paw
        ITM_SHELL1, // wentletrap
        ITM_SHELL2, // venus comb
        ITM_SHELL3, // prceletta
        ITM_SHELL4, // sand dollar
        ITM_SHELL7  // coral
    };

    static mActor_name_t rare_shell[2] = {
        ITM_SHELL6, // conch
        ITM_SHELL5  // white scallop
    };

    static mActor_name_t island_rare_shell[3] = { ITM_SHELL6, // conch
                                                  ITM_SHELL5, // white scallop
                                                  ITM_FOOD_COCONUT };

    static mActor_name_t* shell_table[3] = { normal_shell, rare_shell, island_rare_shell };

    static f32 shell_max[3] = { 6.0f, 2.0f,
/* @BUG - this is supposed to be 3.0f, the devs messed up. Coconuts are supposed to wash up on the beach */
#ifndef BUGFIXES
                                2.0f
#else
                                3.0f
#endif
    };

    int table = 0;
    int index;

    /* 25% chance for a rare shell */
    if (RANDOM(4) == 3) {
        if (is_island == TRUE) {
            table = 2;
        } else {
            table = 1;
        }
    }

    /* Return a random shell from the selected table */
    index = (int)RANDOM_F(shell_max[table]);
    return shell_table[table][index];
}

static void mFI_SetShellBlock(mActor_name_t* fg_p, mCoBG_Collision_u* col_p, int shell_num, u8* can_set_ut_num,
                              int is_island) {
    mActor_name_t* fg = fg_p;
    mCoBG_Collision_u* col = col_p;

    if (fg_p != NULL && col_p != NULL) {
        while (shell_num != 0 && can_set_ut_num[0] != 0) {
            int selected = RANDOM(can_set_ut_num[0]);
            int i;

            fg_p = fg;
            col_p = col;

            for (i = 0; i < UT_TOTAL_NUM; i++) {
                if (fg_p[0] == EMPTY_NO && mCoBG_CheckWaveAttr(col_p->data.unit_attribute) == TRUE) {
                    if (selected <= 0) {
                        fg_p[0] = mFI_GetShell(is_island);
                        shell_num--;
                        can_set_ut_num[0]--;

                        break;
                    } else {
                        selected--;
                    }
                }

                fg_p++;
                col_p++;
            }

            if (i == UT_TOTAL_NUM) {
                break;
            }
        }
    }
}

static void mFI_SetShellSandyBeachBlock(u8* can_set_ut_num, u8* shell_num_inblock) {
    int bz;
    int shell_num;
    int bx;
    int i;

    for (i = 0; i < 7; i++) {
        if (can_set_ut_num[0] != 0) {
            shell_num = shell_num_inblock[0];

            if (shell_num > 0) {
                bx = l_sandy_beach_bx[i];
                bz = l_sandy_beach_bz[i];

                mFI_SetShellBlock(mFI_BkNumtoUtFGTop(bx, bz), mFI_GetBkNum2ColTop(bx, bz), shell_num, can_set_ut_num,
                                  bz == mISL_BLOCK_Z);
            }
        }

        can_set_ut_num++;
        shell_num_inblock++;
    }
}

static void mFI_SetShellWave(int set_num, xyz_t player_pos) {
    static u8 can_set_ut_num[7];
    static u8 shell_num_inblock[7];
    static u8 on_shell_num[7];

    int total_blocks = 0;
    int total_set_num = 0;

    bzero(can_set_ut_num, sizeof(can_set_ut_num));
    bzero(shell_num_inblock, sizeof(shell_num_inblock));
    bzero(on_shell_num, sizeof(on_shell_num));

    mFI_ResearchShell(can_set_ut_num, on_shell_num, &total_set_num, &total_blocks, player_pos);

    if (set_num > total_set_num) {
        set_num = total_set_num;
    }

    if (total_blocks > 0 && set_num > 0) {
        mFI_DivideShell(can_set_ut_num, shell_num_inblock, on_shell_num, set_num, total_blocks);
        mFI_SetShellSandyBeachBlock(can_set_ut_num, shell_num_inblock);
    }
}

static void mFI_SetShell(xyz_t player_pos) {
    static int set_flag;

    if (mFI_CheckSetShell() == TRUE) {
        if (set_flag == FALSE) {
            set_flag = TRUE;
            l_reserve_set_shell++;
        }
    } else {
        set_flag = FALSE;
    }

    if (mFI_CheckFieldData() == TRUE) {
        mActor_name_t field_id = mFI_GetFieldId();

        if (Save_Get(scene_no) == SCENE_FG && mFI_GET_TYPE(field_id) == mFI_FIELD_FG && l_reserve_set_shell > 0) {
            mFI_SetShellWave(l_reserve_set_shell, player_pos);
            l_reserve_set_shell = 0;
        }
    }
}

static int mFI_now_bg_num;

extern void mFI_FieldMove(xyz_t player_pos) {
    mFI_BGDisplayListRefresh(player_pos);
    mFI_DmaBg();
    mFI_SetPlayerBlockKind(player_pos);
    mFI_SetShell(player_pos);
    mMsr_SetMushroom(player_pos);
    mFRm_save_data_check();

    if (mFI_CheckFieldData() == TRUE) {
        int bx;
        int bz;

        if (mFI_Wpos2BlockNum(&bx, &bz, player_pos) == TRUE) {
            int num = mFI_GetBlockNum(bx, bz);
            mFM_block_info_c* block_info = g_fdinfo->block_info + num;

            if (block_info != NULL) {
                mFI_now_bg_num = block_info->bg_info.bg_id.combination_type;
            }
        }
    }
}

extern void mFI_PrintNowBGNum(gfxprint_t* gfxprint) {
    gfxprint_color(gfxprint, 200, 200, 250, 255);
    gfxprint_locate8x8(gfxprint, 3, 7);
    gfxprint_printf(gfxprint, "%d", mFI_now_bg_num);
}

extern void mFI_PrintFgAttr(gfxprint_t* gfxprint) {
    if (mFI_CheckFieldData() && gamePT != NULL) {
        int ut_x;
        int ut_z;
        u32 attribute;

        PLAYER_ACTOR* player = GET_PLAYER_ACTOR_NOW();
        mActor_name_t item = EMPTY_NO;
        mActor_name_t* fg_item_p = mFI_GetUnitFG(player->actor_class.world.position);
        int plant = mCoBG_CheckPlant(player->actor_class.world.position);

        if (fg_item_p != NULL) {
            item = fg_item_p[0];
        }

        mFI_Wpos2UtNum_inBlock(&ut_x, &ut_z, player->actor_class.world.position);
        attribute = mCoBG_Wpos2BgAttribute_Original(player->actor_class.world.position);

        gfxprint_color(gfxprint, 200, 200, 250, 255);
        gfxprint_locate8x8(gfxprint, 3, 8);
        gfxprint_printf(gfxprint, "%d,%d - %4x - %d - %d", ut_x, ut_z, item, attribute, plant);
    }
}

extern int mFI_SetOyasiroPos(s16* oyasiro_p) {
    int bx;
    int bz;

    if (mFI_BlockKind2BkNum(&bx, &bz, mRF_BLOCKKIND_SHRINE) == TRUE) {
        int ut_x;
        int ut_z;

        if (mFI_SearchFGInBlock(&ut_x, &ut_z, WISHING_WELL, bx, bz) == FALSE &&
            mFI_SearchFGInBlock(&ut_x, &ut_z, DUMMY_SHRINE, bx, bz) == FALSE) {
            return FALSE;
        } else {
            xyz_t pos;

            mFI_BkandUtNum2CenterWpos(&pos, bx, bz, ut_x, ut_z);
            oyasiro_p[0] = (s16)pos.x;
            oyasiro_p[1] = (s16)pos.z; // @BUG - maybe a bug? You'd think it'd be .y then .z
            oyasiro_p[2] = (s16)pos.y;

            return TRUE;
        }
    } else {
        return FALSE;
    }
}

static int mFI_CheckBlockSetTreasure(int* block, int bx, int bz) {
    int i;

    for (i = 0; i < 4; i++) {
        if (bx == block[0] && bz == block[1]) {
            return FALSE;
        }

        block += 2;
    }

    return TRUE;
}

extern int mFI_SetTreasure(int* selected_bx, int* selected_bz, mActor_name_t item) {
    static int no_check_block_table[2 * 4] = {
        3, 1, /* train station */
        3, 2, /* player house */
        0, 0, /* wishing well/shrine (dynamic) */
        0, 0  /* lake (dynamic) */
    };

    u8 depositable_num_block[FG_BLOCK_TOTAL_NUM];
    mFM_fg_c* fg_block;
    mFM_fg_c* fg_block_p;
    u8* depositable_num_p2;
    u8* depositable_num_p;
    u8 depositable_blocks;
    int res;

    fg_block = Save_Get(fg[0]);
    fg_block_p = fg_block;
    depositable_num_p = depositable_num_block;
    depositable_blocks = 0;
    res = FALSE;

    if (Save_Get(scene_no) == SCENE_FG) {
        int bz;

        bzero(depositable_num_p, FG_BLOCK_TOTAL_NUM);
        mFI_BlockKind2BkNum(&no_check_block_table[4], &no_check_block_table[5], mRF_BLOCKKIND_SHRINE);
        mFI_BlockKind2BkNum(&no_check_block_table[6], &no_check_block_table[7], mRF_BLOCKKIND_POOL);

        for (bz = 0; bz < FG_BLOCK_Z_NUM; bz++) {
            int bx;

            for (bx = 0; bx < FG_BLOCK_X_NUM; bx++) {
                if (mFI_CheckBlockSetTreasure(no_check_block_table, bx + 1, bz + 1) == TRUE) {
                    mCoBG_Collision_u* col_p = mFI_GetBkNum2ColTop(bx + 1, bz + 1);

                    depositable_num_p[0] = mMsm_GetDepositAbleNum(fg_block_p->items[0], col_p);

                    if (depositable_num_p[0] != 0) {
                        depositable_blocks++;
                    }
                }

                depositable_num_p++;
                fg_block_p++;
            }
        }

        if (depositable_blocks != 0) {
            u8* depositable_num_p; // removing this line fixes regalloc but causes regswaps
            int selected_block;
            int i;

            depositable_num_p2 = depositable_num_block;
            selected_block = RANDOM(depositable_blocks);
            for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++) {
                if (depositable_num_p2[0] != 0) {
                    if (selected_block <= 0) {
                        selected_bx[0] = (i % FG_BLOCK_X_NUM) + 1;
                        selected_bz[0] = (i / FG_BLOCK_X_NUM) + 1;
                        mMsm_DepositItemBlock(fg_block->items[0], item, selected_bx[0], selected_bz[0],
                                              Save_Get(deposit[i]), depositable_num_p2[0]);
                        res = TRUE;

                        break;
                    } else {
                        selected_block--;
                    }
                }

                depositable_num_p2++;
                fg_block++;
            }
        }
    }

    return res;
}

static int l_mFI_climate;

extern int mFI_GetClimate() {
    switch (l_mFI_climate) {
        case mFI_CLIMATE_2:
        case mFI_CLIMATE_3:
        case mFI_CLIMATE_4:
        case mFI_CLIMATE_5:
            return FALSE;
        default:
            return l_mFI_climate & 1;
    }
}

extern void mFI_SetClimate(int climate) {
    if (climate == mFI_CLIMATE_NUM) {
        switch (l_mFI_climate) {
            case mFI_CLIMATE_0:
                l_mFI_climate = mFI_CLIMATE_2;
                break;
            case mFI_CLIMATE_ISLAND:
                l_mFI_climate = mFI_CLIMATE_3;
                break;
        }
    } else {
        l_mFI_climate = climate;
    }
}

extern int mFI_CheckBeforeScenePerpetual() {
    switch (l_mFI_climate) {
        case mFI_CLIMATE_3:
        case mFI_CLIMATE_5:
            return TRUE;
        default:
            return FALSE;
    }
}

extern void mFI_ChangeClimate_ForEventNotice() {
    switch (l_mFI_climate) {
        case mFI_CLIMATE_2:
            l_mFI_climate = mFI_CLIMATE_4;
            break;
        case mFI_CLIMATE_4:
            l_mFI_climate = mFI_CLIMATE_0;
            break;
        case mFI_CLIMATE_3:
            l_mFI_climate = mFI_CLIMATE_5;
            break;
        case mFI_CLIMATE_5:
            l_mFI_climate = mFI_CLIMATE_ISLAND;
            break;
    }

    mCoBG_InitBoatCollision();
}

extern void mFI_PullTanukiPathTrees() {
    static u8 ut_table[6] = { 0x07, 0x08, 0x17, 0x18, 0x27, 0x28 };

    mActor_name_t* fg_p = Save_Get(fg[2][2]).items[0];
    int i;

    for (i = 0; i < 6; i++) {
        int ut = ut_table[i];

        if ((fg_p[ut] == TREE_S0) || (fg_p[ut] == TREE_S1) || (fg_p[ut] == TREE_S2) || (fg_p[ut] == TREE) ||
            (fg_p[ut] == TREE_1000BELLS_S0) || (fg_p[ut] == TREE_1000BELLS_S1) || (fg_p[ut] == TREE_1000BELLS_S2) ||
            (fg_p[ut] == TREE_1000BELLS) || (fg_p[ut] == TREE_10000BELLS_S0) || (fg_p[ut] == TREE_10000BELLS_S1) ||
            (fg_p[ut] == TREE_10000BELLS_S2) || (fg_p[ut] == TREE_10000BELLS) || (fg_p[ut] == TREE_30000BELLS_S0) ||
            (fg_p[ut] == TREE_30000BELLS_S1) || (fg_p[ut] == TREE_30000BELLS_S2) || (fg_p[ut] == TREE_30000BELLS) ||
            (fg_p[ut] == TREE_100BELLS_S0) || (fg_p[ut] == TREE_100BELLS_S1) || (fg_p[ut] == TREE_100BELLS_S2) ||
            (fg_p[ut] == TREE_100BELLS) || (fg_p[ut] == CEDAR_TREE_S0) || (fg_p[ut] == CEDAR_TREE_S1) ||
            (fg_p[ut] == CEDAR_TREE_S2) || (fg_p[ut] == CEDAR_TREE) || (fg_p[ut] == GOLD_TREE_S0) ||
            (fg_p[ut] == GOLD_TREE_S1) || (fg_p[ut] == GOLD_TREE_S2) || (fg_p[ut] == GOLD_TREE) ||
            (fg_p[ut] == GOLD_TREE_SHOVEL) || (fg_p[ut] == TREE_APPLE_S0) || (fg_p[ut] == TREE_APPLE_S1) ||
            (fg_p[ut] == TREE_APPLE_S2) || (fg_p[ut] == TREE_APPLE_NOFRUIT_0) || (fg_p[ut] == TREE_APPLE_NOFRUIT_1) ||
            (fg_p[ut] == TREE_APPLE_NOFRUIT_2) || (fg_p[ut] == TREE_APPLE_FRUIT) || (fg_p[ut] == TREE_ORANGE_S0) ||
            (fg_p[ut] == TREE_ORANGE_S1) || (fg_p[ut] == TREE_ORANGE_S2) || (fg_p[ut] == TREE_ORANGE_NOFRUIT_0) ||
            (fg_p[ut] == TREE_ORANGE_NOFRUIT_1) || (fg_p[ut] == TREE_ORANGE_NOFRUIT_2) ||
            (fg_p[ut] == TREE_ORANGE_FRUIT) || (fg_p[ut] == TREE_PEACH_S0) || (fg_p[ut] == TREE_PEACH_S1) ||
            (fg_p[ut] == TREE_PEACH_S2) || (fg_p[ut] == TREE_PEACH_NOFRUIT_0) || (fg_p[ut] == TREE_PEACH_NOFRUIT_1) ||
            (fg_p[ut] == TREE_PEACH_NOFRUIT_2) || (fg_p[ut] == TREE_PEACH_FRUIT) || (fg_p[ut] == TREE_PEAR_S0) ||
            (fg_p[ut] == TREE_PEAR_S1) || (fg_p[ut] == TREE_PEAR_S2) || (fg_p[ut] == TREE_PEAR_NOFRUIT_0) ||
            (fg_p[ut] == TREE_PEAR_NOFRUIT_1) || (fg_p[ut] == TREE_PEAR_NOFRUIT_2) || (fg_p[ut] == TREE_PEAR_FRUIT) ||
            (fg_p[ut] == TREE_CHERRY_S0) || (fg_p[ut] == TREE_CHERRY_S1) || (fg_p[ut] == TREE_CHERRY_S2) ||
            (fg_p[ut] == TREE_CHERRY_NOFRUIT_0) || (fg_p[ut] == TREE_CHERRY_NOFRUIT_1) ||
            (fg_p[ut] == TREE_CHERRY_NOFRUIT_2) || (fg_p[ut] == TREE_CHERRY_FRUIT) || (fg_p[ut] == TREE_PALM_S0) ||
            (fg_p[ut] == TREE_PALM_S1) || (fg_p[ut] == TREE_PALM_S2) || (fg_p[ut] == TREE_PALM_NOFRUIT_0) ||
            (fg_p[ut] == TREE_PALM_NOFRUIT_1) || (fg_p[ut] == TREE_PALM_NOFRUIT_2) || (fg_p[ut] == TREE_PALM_FRUIT) ||
            (fg_p[ut] == TREE_BEES) || (fg_p[ut] == TREE_FTR) || (fg_p[ut] == TREE_LIGHTS) ||
            (fg_p[ut] == TREE_PRESENT) || (fg_p[ut] == TREE_BELLS) || (fg_p[ut] == CEDAR_TREE_BELLS) ||
            (fg_p[ut] == CEDAR_TREE_FTR) || (fg_p[ut] == CEDAR_TREE_BEES) || (fg_p[ut] == CEDAR_TREE_LIGHTS) ||
            (fg_p[ut] == GOLD_TREE_BELLS) || (fg_p[ut] == GOLD_TREE_FTR) || (fg_p[ut] == GOLD_TREE_BEES)) {
            fg_p[ut] = EMPTY_NO;
        }
    }
}
