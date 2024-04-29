#include "ac_insect.h"

#include "m_name_table.h"
#include "m_common_data.h"
#include "ac_set_ovl_insect.h"
#include "m_player_lib.h"
#include "m_actor_shadow.h"
#include "libultra/libultra.h"
#include "m_skin_matrix.h"
#include "sys_matrix.h"
#include "m_rcp.h"

static aINS_CTRL_ACTOR* aINS_ctrlActor = NULL;
static aINS_overlay_c aINS_overlay;
static aINS_Clip_c aINS_clip;

/* order .bss */
#ifdef MUST_MATCH
BSS_ORDER_GROUP_START
BSS_ORDER_ITEM(aINS_ctrlActor);
BSS_ORDER_ITEM(aINS_overlay);
BSS_ORDER_ITEM(aINS_clip);
BSS_ORDER_GROUP_END
#endif

static void aINS_actor_ct(ACTOR* actorx, GAME* game);
static void aINS_actor_dt(ACTOR* actorx, GAME* game);
static void aINS_actor_move(ACTOR* actorx, GAME* game);
static void aINS_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Insect_Profile = {
    mAc_PROFILE_INSECT,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(aINS_CTRL_ACTOR),
    &aINS_actor_ct,
    &aINS_actor_dt,
    &aINS_actor_move,
    &aINS_actor_draw,
    NULL
};
// clang-format on

static void aINS_position_move(ACTOR* actorx);

#include "../src/ac_insect_data.c_inc"
#include "../src/ac_insect_clip.c_inc"
#include "../src/ac_insect_move.c_inc"
#include "../src/ac_insect_draw.c_inc"

static void aINS_actor_ct(ACTOR* actorx, GAME* game) {
    aINS_CTRL_ACTOR* ctrl_actor = (aINS_CTRL_ACTOR*)actorx;
    aINS_INSECT_ACTOR* insect_actor;
    aINS_overlay_entry_c* overlay_p;
    int i;

    aINS_ctrlActor = ctrl_actor;
    aINS_init_dma_and_clip_area(ctrl_actor);
    insect_actor = ctrl_actor->insect_actor;
    overlay_p = aINS_overlay.entries;

    for (i = 0; i < aINS_ACTOR_NUM; i++) {
        insect_actor->exist_flag = FALSE;
        insect_actor->_254 = 0;
        insect_actor->_258 = 0;
        insect_actor++;
    }

    for (i = 0; i < 3; i++) {
        overlay_p->_1C00 = aINS_PROGRAM_NUM;
        overlay_p->_1C04 = 0;
        overlay_p++;
    }
}

static void aINS_actor_dt(ACTOR* actorx, GAME* game) {
    aINS_free_clip_area();
}
