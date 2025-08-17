#include "ac_rope.h"

#include "m_rcp.h"
#include "m_name_table.h"
#include "m_field_info.h"
#include "m_event.h"
#include "sys_matrix.h"

static void aRP_actor_ct(ACTOR* actor, GAME* game);
static void aRP_actor_dt(ACTOR* actor, GAME* game);
static void aRP_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE Rope_Profile = {
    mAc_PROFILE_ROPE,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_ROPE,
    sizeof(ROPE_ACTOR),
    aRP_actor_ct,
    aRP_actor_dt,
    NONE_ACTOR_PROC,
    aRP_actor_draw,
    NULL,
};

extern Vtx tol_rope_1_v[0x3C];
extern Gfx tol_rope_1T_model[];
extern Gfx tol_rope_1_shadowT_model[];

static void aRP_actor_ct(ACTOR* actor, GAME* game) {

    xyz_t world;
    xyz_t pos = actor->world.position;

    int i;
    mFI_Wpos2UtCenterWpos(&world, pos);

    world.x -= 40.0f;
    for (i = 0; i < 3; i++) {
        mCoBG_SetPlussOffset(world, 2, 100);
        world.x += 40.0f;
    }
}

static void aRP_actor_dt(ACTOR* actor, GAME* game) {

    xyz_t world;
    xyz_t pos = actor->world.position;

    int i;
    mFI_Wpos2UtCenterWpos(&world, pos);

    world.x -= 40.0f;
    for (i = 0; i < 3; i++) {
        mCoBG_SetPlussOffset(world, 0, 100);
        world.x += 40.0f;
    }
}

static void aRP_make_vtx(Vtx* vtx) {
    static u8 flg[] = {
        FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
        FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE, TRUE,
        TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
        FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,  FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
    };

    Vtx* make;
    u8* flag;
    int i;
    int fact;

    flag = flg;
    fact = (*(f32*)mEv_get_save_area(0xE, 9) * 100.0f);
    make = tol_rope_1_v;

    for (i = 0; i < ARRAY_SIZE(tol_rope_1_v, Vtx); i++) {
        vtx[0] = make[0];

        if (flag[0] == 1) {
            vtx->v.ob[0] = make->v.ob[0] + fact;
        } else {
            vtx->v.ob[0] = make->v.ob[0];
        }

        make++;
        vtx++;
        flag++;
    }
}

static void aRP_actor_draw(ACTOR* actor, GAME* game) {
    Vtx* work;
    Vtx* vtx;
    Gfx* gfxp;
    Gfx* gfxp2;
    GRAPH* graph = game->graph;

    _texture_z_light_fog_prim_npc(graph);

    vtx = GRAPH_ALLOC_TYPE(graph, Vtx, ARRAY_SIZE(tol_rope_1_v, Vtx));

    work = vtx;

    if (vtx != NULL) {
        aRP_make_vtx(vtx);
    } else {
        work = tol_rope_1_v;
    }

    OPEN_DISP(graph);

    gfxp = NOW_POLY_OPA_DISP;
    gSPMatrix(gfxp++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(gfxp++, 8, work);
    gSPDisplayList(gfxp++, tol_rope_1T_model);
    SET_POLY_OPA_DISP(gfxp);

    _texture_z_light_fog_prim_shadow(graph);
    gfxp2 = NOW_SHADOW_DISP;
    gSPMatrix(gfxp2++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxp2++, tol_rope_1_shadowT_model);
    SET_SHADOW_DISP(gfxp2);

    CLOSE_DISP(graph);
}
