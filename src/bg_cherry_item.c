#include "bg_item.h"
#include "bg_cherry_item.h"

#include "m_common_data.h"
#include "m_name_table.h"
#include "m_malloc.h"
#include "libultra/libultra.h"
#include "m_player_lib.h"
#include "sys_matrix.h"
#include "m_skin_matrix.h"
#include "gfxalloc.h"
#include "m_rcp.h"
#include "m_event_map_npc.h"

#define GOLD_TREE_SAPLING_EFFECT_X 12.0f
#define GOLD_TREE_SAPLING_EFFECT_Y 27.0f
#define GOLD_TREE_SAPLING_EFFECT_Z 10.0f

#define bIT_CLIP (Common_Get(clip).bg_item_clip)

static void bCI_actor_ct(ACTOR* actorx, GAME* game);
static void bCI_actor_dt(ACTOR* actorx, GAME* game);
static void bCI_actor_move(ACTOR* actorx, GAME* game);
static void bCI_actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE BgCherryItem_Profile = {
    mAc_PROFILE_BGCHERRYITEM,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_BG_CHERRY_ITEM,
    sizeof(BG_ITEM_ACTOR),
    &bCI_actor_ct,
    &bCI_actor_dt,
    &bCI_actor_move,
    &bCI_actor_draw,
    NULL,
};

static f32 pos_table[] = {
    20.0f,  60.0f,  100.0f, 140.0f, 180.0f, 220.0f, 260.0f, 300.0f,
    340.0f, 380.0f, 420.0f, 460.0f, 500.0f, 540.0f, 580.0f, 620.0f,
};

static f32 pos_table2[] = {
    0.0f,   40.0f,  80.0f,  120.0f, 160.0f, 200.0f, 240.0f, 280.0f,
    320.0f, 360.0f, 400.0f, 440.0f, 480.0f, 520.0f, 560.0f, 600.0f,
};

static void bg_item_common_draw_loop_type1(GRAPH* graph, Gfx** gfx_pp, bg_item_draw_list_c* draw_list,
                                           bg_item_draw_pos_c* draw_pos, Gfx** display_list_table);
static void bg_item_common_s_draw_loop_type1(GRAPH* graph, Gfx** gfx_pp, bg_item_draw_list_c* draw_list,
                                             int shadow_vtx_count, Vtx* shadow_vtx, bg_item_draw_pos_c* draw_pos,
                                             Gfx** display_list_table);

static int bIT_actor_drop_entry(bg_item_drop_table_c* drop_info, mActor_name_t fg_item, xyz_t* pos, xyz_t* target_pos,
                                u16 flags, s16 layer);
static void bit_cmn_single_drawS_shadow(GAME* game, bg_item_common_info_c* common_info, mActor_name_t fg_no, xyz_t* pos,
                                        s_xyz* angle, xyz_t* scale, u8 alpha, f32 shadow_pos, rgba_t* shadow_color);
static int bIT_actor_hole_effect_entry(bg_item_hole_c* hole, mActor_name_t fg_item, xyz_t* pos, u16 frames,
                                       u16 wait_frames, s16 mode, s16 wait_type);

#include "../src/bg_cherry_item_data.c_inc"
#include "../src/bg_item_clip.c_inc"
#include "../src/bg_item_common.c_inc"

extern u16 obj_g_hole_pal[];
extern u16 obj_b_hole_pal[];

static void bCI_actor_ct(ACTOR* actorx, GAME* game) {
    BG_ITEM_ACTOR* bg_item = (BG_ITEM_ACTOR*)actorx;
    bg_item_common_c* common;
    bg_item_common_info_c* common_info;
    int i;
    int max;
    int event_type;
    PLAYER_ACTOR* player;
    mFI_block_tbl_c* block_table;
    bg_item_tbl_c* info_table;

    common = &bg_item->common;
    common_info = &common->common_info;
    bIT_clip_ct(actorx);
    mFI_InitItemTable(&bg_item->common.item_table);
    player = GET_PLAYER_ACTOR((GAME_PLAY*)game);
    event_type = mEvMN_GetEventTypeMap();

    if (player != NULL) {
        mFI_GetItemTable(&bg_item->common.item_table, player->actor_class.world.position, __FILE__, 269);
        mFI_BornItemON();
    }

    for (i = 0; i < bg_item->common.item_table.count; i++) {
        bIT_common_clear_treeatr(bg_item->common.item_table.block_info_tbl[i].block_x,
                                 bg_item->common.item_table.block_info_tbl[i].block_z,
                                 &bg_item->common.block_info_table.info_tbl[i]);

        if (event_type == -1 || mEvMN_GetMapIdx(event_type) == -1) {
            mFI_ClearHoleBlock(bg_item->common.item_table.block_info_tbl[i].block_x,
                               bg_item->common.item_table.block_info_tbl[i].block_z);
        }
    }

    for (i = 0; i < mFM_VISIBLE_BLOCK_NUM; i++) {
        bg_item->common._139F4[i] = i;
    }

    bg_item->common.common_info._30 = 0x24;
    bg_item->common.common_info.draw_part_table_p = draw_part_table_a;

    common_info->pal_p[bIT_PAL_FLOWER_A] = g_fdinfo->field_palette.flower0_pal;
    common_info->pal_p[bIT_PAL_FLOWER_B] = g_fdinfo->field_palette.flower1_pal;
    common_info->pal_p[bIT_PAL_FLOWER_C] = g_fdinfo->field_palette.flower2_pal;
    common_info->pal_p[bIT_PAL_GRASS] = g_fdinfo->field_palette.grass_pal;
    common_info->pal_p[bIT_PAL_TREE] = g_fdinfo->field_palette.cedar_tree_pal;
    common_info->pal_p[bIT_PAL_PALM_TREE] = g_fdinfo->field_palette.palm_tree_pal;
    common_info->pal_p[bIT_PAL_GOLD_TREE] = g_fdinfo->field_palette.golden_tree_pal;
    common_info->pal_p[bIT_PAL_HOLE_G] = obj_g_hole_pal;
    common_info->pal_p[bIT_PAL_HOLE_S] = obj_b_hole_pal;

    bg_item->common.bg_item_actorx_p = actorx;

    for (i = 0; i < mFM_VISIBLE_BLOCK_NUM; i++) {
        bg_item->common.draw_table[i].draw_data.val = bIT_DRAW_TYPE_MAX - 1;
        bg_item->common.draw_table[i].draw_data.idx_p = bg_item->item_idx_info[i].idx;
    }

    common_info->pos_table_p = pos_table;
    bg_item_common_chg_BGDataR(common);
    bg_item_common_construct(game, common);
}

static void bCI_actor_dt(ACTOR* actorx, GAME* game) {
    BG_ITEM_ACTOR* bg_item = (BG_ITEM_ACTOR*)actorx;

    bg_item_common_destruct((GAME_PLAY*)game, actorx, &bg_item->common);
    bIT_clip_dt();
}

#include "../src/bg_cherry_item_move.c_inc"
#include "../src/bg_cherry_item_draw.c_inc"
