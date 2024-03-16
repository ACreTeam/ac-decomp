#include "bg_item.h"

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

#define bIT_CLIP (Common_Get(clip).bg_item_clip)

static void bIT_actor_ct(ACTOR* actorx, GAME* game);
static void bIT_actor_dt(ACTOR* actorx, GAME* game);
static void bIT_actor_move(ACTOR* actorx, GAME* game);
static void bIT_actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE BgItem_Profile = {
    mAc_PROFILE_BGITEM,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_BGITEM,
    sizeof(BG_ITEM_ACTOR),
    &bIT_actor_ct,
    &bIT_actor_dt,
    &bIT_actor_move,
    &bIT_actor_draw,
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

#include "bg_item_data.c_inc"

// TODO:
static bg_item_draw_part_table_c draw_part_table_a[];

#include "../src/bg_item_clip.c_inc"
#include "../src/bg_item_common.c_inc"

extern u16 obj_g_hole_pal[];
extern u16 obj_s_hole_pal[];

static void bIT_actor_ct(ACTOR* actorx, GAME* game) {
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
    mFI_InitItemTable(&common->item_table);
    player = GET_PLAYER_ACTOR((GAME_PLAY*)game);
    event_type = mEvMN_GetEventTypeMap();

    if (player != NULL) {
        mFI_GetItemTable(&bg_item->common.item_table, player->actor_class.world.position, __FILE__, 257);
        mFI_BornItemON();
    }

    max = common->item_table.count;
    block_table = common->item_table.block_info_tbl;
    info_table = common->block_info_table.info_tbl;
    for (i = 0; i < max; i++, block_table++, info_table++) {
        bIT_common_clear_treeatr(block_table->block_x, block_table->block_z, info_table);

        if (event_type == -1 || mEvMN_GetMapIdx(event_type) == -1) {
            mFI_ClearHoleBlock(block_table->block_x, block_table->block_z);
        }
    }

    for (i = 0; i < mFM_VISIBLE_BLOCK_NUM; i++) {
        common->_139F4[i] = i;
    }

    common_info->_30 = 4;
    common_info->draw_part_table_p = draw_part_table_a;

    common_info->pal_p[bIT_PAL_FLOWER_A] = g_fdinfo->field_palette.flower0_pal;
    common_info->pal_p[bIT_PAL_FLOWER_B] = g_fdinfo->field_palette.flower1_pal;
    common_info->pal_p[bIT_PAL_FLOWER_C] = g_fdinfo->field_palette.flower2_pal;
    common_info->pal_p[bIT_PAL_GRASS] = g_fdinfo->field_palette.grass_pal;
    common_info->pal_p[bIT_PAL_TREE] = g_fdinfo->field_palette.cedar_tree_pal;
    common_info->pal_p[bIT_PAL_PALM_TREE] = g_fdinfo->field_palette.palm_tree_pal;
    common_info->pal_p[bIT_PAL_GOLD_TREE] = g_fdinfo->field_palette.golden_tree_pal;
    common_info->pal_p[bIT_PAL_HOLE_G] = obj_g_hole_pal;
    common_info->pal_p[bIT_PAL_HOLE_S] = obj_s_hole_pal;

    common->bg_item_actorx_p = actorx;

    {
        bg_item_draw_table_c* draw_tbl = common->draw_table;
        bg_item_idx_info_c* start_idx = bg_item->item_idx_info;

        for (i = 0; i < mFM_VISIBLE_BLOCK_NUM; i++, draw_tbl++, start_idx++) {
            draw_tbl->draw_data.val = bIT_DRAW_TYPE_MAX - 1;
            draw_tbl->draw_data.idx_p = start_idx->idx;
        }
    }

    common_info->pos_table_p = pos_table;
    bg_item_common_chg_BGDataR(common);
    bg_item_common_construct(game, common);
}

static void bIT_actor_dt(ACTOR* actorx, GAME* game) {
    BG_ITEM_ACTOR* bg_item = (BG_ITEM_ACTOR*)actorx;

    bg_item_common_destruct((GAME_PLAY*)game, actorx, &bg_item->common);
    bIT_clip_dt();
}

#include "../src/bg_item_move.c_inc"
#include "../src/bg_item_draw.c_inc"
