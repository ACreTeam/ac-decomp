#include "bg_item.h"
#include "bg_xmas_item.h"

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

#define GOLD_TREE_SAPLING_EFFECT_X 13.0f
#define GOLD_TREE_SAPLING_EFFECT_Y 33.0f
#define GOLD_TREE_SAPLING_EFFECT_Z 10.0f

#define bIT_CLIP (Common_Get(clip).bg_item_clip)

enum {
    bIT_DRAW_TYPE_STUMP1,
    bIT_DRAW_TYPE_STUMP2,
    bIT_DRAW_TYPE_STUMP3,
    bIT_DRAW_TYPE_STUMP4,
    bIT_DRAW_TYPE_FENCE,
    bIT_DRAW_TYPE_NOTICE,
    bIT_DRAW_TYPE_GRASS,
    bIT_DRAW_TYPE_MAPBOARD,
    bIT_DRAW_TYPE_MELODY,
    bIT_DRAW_TYPE_FENCES,
    bIT_DRAW_TYPE_HONYCOMB,
    bIT_DRAW_TYPE_HOLE00_G,
    bIT_DRAW_TYPE_HOLE00_S,
    bIT_DRAW_TYPE_CRACK00_G,
    bIT_DRAW_TYPE_CRACK00_S,
    bIT_DRAW_TYPE_HOLE00_SHIN_G,
    bIT_DRAW_TYPE_STONE_A,
    bIT_DRAW_TYPE_STONE_B,
    bIT_DRAW_TYPE_STONE_C,
    bIT_DRAW_TYPE_STONE_D,
    bIT_DRAW_TYPE_STONE_E,
    bIT_DRAW_TYPE_TANE,
    bIT_DRAW_TYPE_TREE0,
    bIT_DRAW_TYPE_TREE1,
    bIT_DRAW_TYPE_TREE2,
    bIT_DRAW_TYPE_TREE3,
    bIT_DRAW_TYPE_TREE4,
    bIT_DRAW_TYPE_TREE4_AP,
    bIT_DRAW_TYPE_TREE4_OR,
    bIT_DRAW_TYPE_TREE4_PH,
    bIT_DRAW_TYPE_TREE4_PR,
    bIT_DRAW_TYPE_TREE4_NT,
    bIT_DRAW_TYPE_TREE4_BG,
    bIT_DRAW_TYPE_TREE4_LIGHT,
    bIT_DRAW_TYPE_FLOWER_LEAF,
    bIT_DRAW_TYPE_FLOWER00,
    bIT_DRAW_TYPE_FLOWER01,
    bIT_DRAW_TYPE_FLOWER02,
    bIT_DRAW_TYPE_TREE0_DEAD,
    bIT_DRAW_TYPE_PALM000,
    bIT_DRAW_TYPE_PALM001,
    bIT_DRAW_TYPE_PALM002,
    bIT_DRAW_TYPE_PALM003,
    bIT_DRAW_TYPE_PALM004,
    bIT_DRAW_TYPE_PALM004_CC,
    bIT_DRAW_TYPE_PALM_STUMP001,
    bIT_DRAW_TYPE_PALM_STUMP002,
    bIT_DRAW_TYPE_PALM_STUMP003,
    bIT_DRAW_TYPE_PALM_STUMP004,
    bIT_DRAW_TYPE_PALM000_DEAD,
    bIT_DRAW_TYPE_CEDAR000,
    bIT_DRAW_TYPE_CEDAR001,
    bIT_DRAW_TYPE_CEDAR002,
    bIT_DRAW_TYPE_CEDAR003,
    bIT_DRAW_TYPE_CEDAR004,
    bIT_DRAW_TYPE_CEDAR004_LIGHT,
    bIT_DRAW_TYPE_CEDAR_STUMP001,
    bIT_DRAW_TYPE_CEDAR_STUMP002,
    bIT_DRAW_TYPE_CEDAR_STUMP003,
    bIT_DRAW_TYPE_CEDAR_STUMP004,
    bIT_DRAW_TYPE_CEDAR000_DEAD,
    bIT_DRAW_TYPE_GOLD_TREE000,
    bIT_DRAW_TYPE_GOLD_TREE001,
    bIT_DRAW_TYPE_GOLD_TREE002,
    bIT_DRAW_TYPE_GOLD_TREE003,
    bIT_DRAW_TYPE_GOLD_TREE004,
    bIT_DRAW_TYPE_GOLD_TREE_STUMP001,
    bIT_DRAW_TYPE_GOLD_TREE_STUMP002,
    bIT_DRAW_TYPE_GOLD_TREE_STUMP003,
    bIT_DRAW_TYPE_GOLD_TREE_STUMP004,
    bIT_DRAW_TYPE_GOLD_TREE000_DEAD,
    bIT_DRAW_TYPE_APPLE,
    bIT_DRAW_TYPE_ORANGE,
    bIT_DRAW_TYPE_PEACH,
    bIT_DRAW_TYPE_PEAR,
    bIT_DRAW_TYPE_NUTS,
    bIT_DRAW_TYPE_MATUTAKE,
    bIT_DRAW_TYPE_KABU,
    bIT_DRAW_TYPE_FISH,
    bIT_DRAW_TYPE_BAG,
    bIT_DRAW_TYPE_LEAF,
    bIT_DRAW_TYPE_ROLL,
    bIT_DRAW_TYPE_BOX,
    bIT_DRAW_TYPE_PACK,
    bIT_DRAW_TYPE_PRESENT,
    bIT_DRAW_TYPE_SEED,
    bIT_DRAW_TYPE_HANIWA,
    bIT_DRAW_TYPE_OTHER,
    bIT_DRAW_TYPE_86,
    bIT_DRAW_TYPE_TOOL,
    bIT_DRAW_TYPE_FOSSIL,
    bIT_DRAW_TYPE_TRASH,
    bIT_DRAW_TYPE_90,
    bIT_DRAW_TYPE_OTOSI,
    bIT_DRAW_TYPE_SHELL_A,
    bIT_DRAW_TYPE_SHELL_B,
    bIT_DRAW_TYPE_SHELL_C,
    bIT_DRAW_TYPE_CANDY,
    bIT_DRAW_TYPE_COCONUT,
    bIT_DRAW_TYPE_97,
    bIT_DRAW_TYPE_CLOTH,
    bIT_DRAW_TYPE_CARPET,
    bIT_DRAW_TYPE_WALL,
    bIT_DRAW_TYPE_AXE,
    bIT_DRAW_TYPE_NET,
    bIT_DRAW_TYPE_ROD,
    bIT_DRAW_TYPE_SCOOP,
    bIT_DRAW_TYPE_GOLD_AXE,
    bIT_DRAW_TYPE_GOLD_NET,
    bIT_DRAW_TYPE_GOLD_ROD,
    bIT_DRAW_TYPE_GOLD_SCOOP,
    bIT_DRAW_TYPE_UMBRELLA,
    bIT_DRAW_TYPE_PINWHEEL,
    bIT_DRAW_TYPE_FAN,
    bIT_DRAW_TYPE_PAPER,
    bIT_DRAW_TYPE_SEEDBAG,
    bIT_DRAW_TYPE_LUCKBAG,
    bIT_DRAW_TYPE_GYMCARD,
    bIT_DRAW_TYPE_MUSIC,
    bIT_DRAW_TYPE_LOTTERY,
    bIT_DRAW_TYPE_BONE,
    bIT_DRAW_TYPE_DIARY,
    bIT_DRAW_TYPE_FORK,
    bIT_DRAW_TYPE_FISH2,
    bIT_DRAW_TYPE_NONE,

    bIT_DRAW_TYPE_MAX
};

#define bIT_TYPE_BASE bIT_DRAW_TYPE_GOLD_TREE000_DEAD

typedef struct bg_item_idx_info_s {
    s16 v0;
    s16 v1;
} bg_item_idx_info_c;

typedef struct blk_idx_info_s {
    bg_item_idx_info_c info[UT_TOTAL_NUM + 1];
    u16 idx[bIT_DRAW_TYPE_MAX];
} bg_item_blk_idx_info_c;

typedef struct bg_xmas_item_actor_s BG_XMAS_ITEM_ACTOR;

struct bg_xmas_item_actor_s {
    ACTOR actor_class;
    bg_item_blk_idx_info_c item_idx_info[mFM_VISIBLE_BLOCK_NUM];
    bg_item_common_c common;
};

#define bIT_GET_COMMON(actorx) (&((BG_XMAS_ITEM_ACTOR*)(actorx))->common)

static void bXI_actor_ct(ACTOR* actorx, GAME* game);
static void bXI_actor_dt(ACTOR* actorx, GAME* game);
static void bXI_actor_move(ACTOR* actorx, GAME* game);
static void bXI_actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE BgXmasItem_Profile = {
    mAc_PROFILE_BGXMASITEM,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_BG_XMAS_ITEM,
    sizeof(BG_XMAS_ITEM_ACTOR),
    &bXI_actor_ct,
    &bXI_actor_dt,
    &bXI_actor_move,
    &bXI_actor_draw,
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
static void bXI_draw_loop_type1_xtree(GRAPH* graph, Gfx** gfx_pp, bg_item_draw_list_c* draw_list,
                                      bg_item_draw_pos_c* draw_pos, Gfx** display_list_table);

#include "../src/bg_xmas_item_data.c_inc"
#include "../src/bg_item_clip.c_inc"
#include "../src/bg_item_common.c_inc"

extern u16 obj_g_hole_pal[];
extern u16 obj_b_hole_pal[];

static void bXI_actor_ct(ACTOR* actorx, GAME* game) {
    BG_XMAS_ITEM_ACTOR* bg_item = (BG_XMAS_ITEM_ACTOR*)actorx;
    bg_item_common_c* common;
    bg_item_common_info_c* common_info;
    int i;
    int max;
    int event_type;
    PLAYER_ACTOR* player;

    common = &bg_item->common;
    common_info = &common->common_info;
    bIT_clip_ct(actorx);
    mFI_InitItemTable(&common->item_table);
    player = GET_PLAYER_ACTOR((GAME_PLAY*)game);
    event_type = mEvMN_GetEventTypeMap();

    if (player != NULL) {
        mFI_GetItemTable(&common->item_table, player->actor_class.world.position, __FILE__, 288);
        mFI_BornItemON();
    }

    for (i = 0; i < common->item_table.count; i++) {
        bIT_common_clear_treeatr(common->item_table.block_info_tbl[i].block_x,
                                 common->item_table.block_info_tbl[i].block_z, &common->block_info_table.info_tbl[i]);

        if (event_type == -1 || mEvMN_GetMapIdx(event_type) == -1) {
            mFI_ClearHoleBlock(common->item_table.block_info_tbl[i].block_x,
                               common->item_table.block_info_tbl[i].block_z);
        }
    }

    for (i = 0; i < mFM_VISIBLE_BLOCK_NUM; i++) {
        int j;

        common->draw_table[i].draw_data.val = bIT_DRAW_TYPE_MAX - 1;
        common->draw_table[i].draw_data.idx_p = bg_item->item_idx_info[i].idx;

        for (j = 0; j < (UT_TOTAL_NUM + 1); j++) {
            common->draw_table[i].draw_data.draw_pos[j]._04 = &bg_item->item_idx_info[i].info[j];
        }

        for (j = 0; j < (UT_TOTAL_NUM + 1); j++) {
            int shift = ((j - 1) & 0xF) + (((j - 1) >> 4) & 0xF);

            bg_item->item_idx_info[i].info[j].v0 = shift % 3;
            bg_item->item_idx_info[i].info[j].v1 = 0;
        }
    }

    for (i = 0; i < mFM_VISIBLE_BLOCK_NUM; i++) {
        common->_139F4[i] = i;
    }

    common_info->_30 = ACTOR_OBJ_BANK_BG_XMAS_ITEM;
    common_info->draw_part_table_p = draw_part_table_a;

    common_info->pal_p[bIT_PAL_FLOWER_A] = g_fdinfo->field_palette.flower0_pal;
    common_info->pal_p[bIT_PAL_FLOWER_B] = g_fdinfo->field_palette.flower1_pal;
    common_info->pal_p[bIT_PAL_FLOWER_C] = g_fdinfo->field_palette.flower2_pal;
    common_info->pal_p[bIT_PAL_GRASS] = g_fdinfo->field_palette.grass_pal;
    common_info->pal_p[bIT_PAL_TREE] = g_fdinfo->field_palette.cedar_tree_pal;
    common_info->pal_p[bIT_PAL_PALM_TREE] = g_fdinfo->field_palette.palm_tree_pal;
    common_info->pal_p[bIT_PAL_GOLD_TREE] = g_fdinfo->field_palette.golden_tree_pal;
    common_info->pal_p[bIT_PAL_HOLE_G] = obj_g_hole_pal;
    common_info->pal_p[bIT_PAL_HOLE_S] = obj_b_hole_pal;

    common->bg_item_actorx_p = actorx;

    common_info->pos_table_p = pos_table;
    bg_item_common_chg_BGDataR(common);
    bg_item_common_construct(game, common);
}

static void bXI_actor_dt(ACTOR* actorx, GAME* game) {
    BG_XMAS_ITEM_ACTOR* bg_item = (BG_XMAS_ITEM_ACTOR*)actorx;

    bg_item_common_destruct((GAME_PLAY*)game, actorx, &bg_item->common);
    bIT_clip_dt();
}

#include "../src/bg_xmas_item_move.c_inc"
#include "../src/bg_xmas_item_draw.c_inc"
