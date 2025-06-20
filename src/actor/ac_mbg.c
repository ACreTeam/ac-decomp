#include "ac_mbg.h"

#include "m_collision_bg.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_name_table.h"

static Vtx mbg_v[] = {
#include "assets/mbg_v.inc"
};

static Gfx mbg_model[] = {
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 128, 255, 255, 0, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mbg_v[0], 8, 0),
    gsSP2Triangles(5, 6, 7, 0, 4, 5, 7, 0),
    gsSP2Triangles(7, 6, 2, 0, 7, 2, 3, 0),
    gsSP2Triangles(5, 1, 6, 0, 6, 1, 2, 0),
    gsSP2Triangles(4, 0, 5, 0, 5, 0, 1, 0),
    gsSP2Triangles(4, 7, 0, 0, 0, 7, 3, 0),
    gsSPEndDisplayList(),
};

static void Mbg_Actor_ct(ACTOR* actorx, GAME* game);
static void Mbg_Actor_dt(ACTOR* actorx, GAME* game);
static void Mbg_Actor_draw(ACTOR* actorx, GAME* game);
static void Mbg_Actor_move(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Mbg_Profile = {
    mAc_PROFILE_MBG,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NONE,
    ETC_MBG,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(MBG_ACTOR),
    &Mbg_Actor_ct,
    &Mbg_Actor_dt,
    &Mbg_Actor_move,
    &Mbg_Actor_draw,
    NULL
};
// clang-format on

static void Mbg_Actor_ct(ACTOR* actorx, GAME* game) {
    MBG_ACTOR* mbg = (MBG_ACTOR*)actorx;

    mbg->move_bg_regist_idx = 0;
    mbg->original_pos = actorx->world.position;
    mbg->move_counter = 0.0f;
    actorx->shape_info.rotation.y = DEG2SHORT_ANGLE(60.0f); // 0x2AAA
    mbg->move_bg_regist_idx = mCoBG_RegistMoveBg(&mbg->move_bg_regist, &actorx->world.position,
                                                 &actorx->last_world_position, &actorx->shape_info.rotation.y, 40.0f,
                                                 NULL, NULL, NULL, NULL, 0, mCoBG_ATTRIBUTE_STONE, 80.0f);
}

static void Mbg_Actor_dt(ACTOR* actorx, GAME* game) {
    MBG_ACTOR* mbg = (MBG_ACTOR*)actorx;

    mCoBG_CrossOffMoveBg(mbg->move_bg_regist_idx);
}

static void Mbg_Actor_draw(ACTOR* actorx, GAME* game) {
    xyz_t pos = actorx->world.position;
    s16 angle_y = actorx->shape_info.rotation.y;
    GRAPH* graph = game->graph;

    OPEN_DISP(graph);

    _texture_z_light_fog_prim(graph);
    Matrix_translate(pos.x, pos.y, pos.z, MTX_LOAD);
    Matrix_RotateY(angle_y, MTX_MULT);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, mbg_model);

    CLOSE_DISP(graph);
}

static void Mbg_Actor_move(ACTOR* actorx, GAME* game) {
    MBG_ACTOR* mbg = (MBG_ACTOR*)actorx;
    f32 x_shift = sinf_table(DEG2RAD(mbg->move_counter)) * 60.0f;

    mbg->move_counter += 2.0f;

    while (mbg->move_counter > 360.0f) {
        mbg->move_counter -= 360.0f;
    }

    actorx->world.position.x = mbg->original_pos.x + x_shift;
    actorx->shape_info.rotation.y += DEG2SHORT_ANGLE(0.258179f); // 0x002F
}
