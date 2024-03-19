#include "bg_police_item.h"

#include "m_name_table.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_player_lib.h"
#include "m_common_data.h"

typedef struct bg_police_item_draw_pos {
    int next;
    MtxF mtx;
} bPI_draw_pos_c;

typedef struct bg_police_item_draw_data {
    u16 start_idx[mNT_ITEM_TYPE_NUM - 1];
    bPI_draw_pos_c draw_pos[UT_TOTAL_NUM + 1];
} bPI_draw_data_c;

typedef struct bg_police_item_draw_tbl {
    int draw_flag;
    bPI_draw_data_c draw_data;
} bPI_draw_tbl_c;

typedef struct bg_police_item_s {
    ACTOR actor_class;
    bPI_draw_tbl_c draw_tbl;
    mFI_item_table_c item_tbl;
} BG_POLICE_ITEM_ACTOR;

static void bPI_actor_move(ACTOR* actorx, GAME* game);
static void bPI_actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE BgPoliceItem_Profile = {
    mAc_PROFILE_BGPOLICEITEM,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(BG_POLICE_ITEM_ACTOR),
    mActor_NONE_PROC1,
    mActor_NONE_PROC1,
    &bPI_actor_move,
    &bPI_actor_draw,
    NULL,
};

#include "../src/bg_police_item_data.c_inc"

#include "../src/bg_police_item_move.c_inc"
#include "../src/bg_police_item_draw.c_inc"
