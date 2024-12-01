#include "ac_ghog.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

// clang-format off
static u8 aGhog_shadow_vtx_fix_flg_table[] = {
    TRUE, FALSE, TRUE, FALSE,
    FALSE, FALSE, TRUE, FALSE,
    FALSE, TRUE,
};
// clang-format on

extern Vtx obj_e_ghog_shadow_v[];
extern Gfx obj_e_ghog_shadow_modelT[];

static bIT_ShadowData_c aGhog_shadow_data = {
    ARRAY_COUNT(aGhog_shadow_vtx_fix_flg_table),
    aGhog_shadow_vtx_fix_flg_table,
    20.0f,
    obj_e_ghog_shadow_v,
    obj_e_ghog_shadow_modelT,
};

static void aGhog_actor_ct(ACTOR* actorx, GAME* game);
static void aGhog_actor_init(ACTOR* actorx, GAME* game);
static void aGhog_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Ghog_Profile = {
    mAc_PROFILE_GHOG,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    GHOG,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(GHOG_ACTOR),
    &aGhog_actor_ct,
    mActor_NONE_PROC1,
    &aGhog_actor_init,
    &aGhog_actor_draw,
    NULL,
};
// clang-format on

static void aGhog_set_bgOffset(ACTOR* actorx);

static void aGhog_actor_ct(ACTOR* actorx, GAME* game) {
    aGhog_set_bgOffset(actorx);
}

static void aGhog_set_bgOffset(ACTOR* actorx) {
    static const mCoBG_OffsetTable_c rewrite_data = { mCoBG_ATTRIBUTE_NONE, 2, 2, 2, 2, 2, 0 };
    xyz_t pos = actorx->world.position;

    pos.x += mFI_UT_WORLDSIZE_X_F;
    mCoBG_SetPluss5PointOffset_file(actorx->world.position, rewrite_data, __FILE__, 163);
    mCoBG_SetPluss5PointOffset_file(pos, rewrite_data, __FILE__, 164);
}

static void aGhog_actor_move(ACTOR* actorx, GAME* game) {
    // nothing
}

static void aGhog_actor_init(ACTOR* actorx, GAME* game) {
    mFI_SetFG_common(DUMMY_GHOG, actorx->home.position, FALSE);
    aGhog_actor_move(actorx, game);
    actorx->mv_proc = &aGhog_actor_move;
}

extern Gfx obj_e_ghog_model[];
extern Gfx obj_e_ghog_modelT[];

static void aGhog_actor_draw(ACTOR* actorx, GAME* game) {
    GRAPH* graph = game->graph;

    _texture_z_light_fog_prim_npc(graph);
    _texture_z_light_fog_prim_shadow(graph);

    OPEN_DISP(graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, obj_e_ghog_modelT);
    gSPDisplayList(NEXT_POLY_OPA_DISP, obj_e_ghog_model);

    CLOSE_DISP(graph);

    CLIP(bg_item_clip)->draw_shadow_proc(game, &aGhog_shadow_data, TRUE);
}
