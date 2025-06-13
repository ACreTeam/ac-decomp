#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_debug.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern Gfx ef_nagare01_modelT[];

static void eShooting_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eShooting_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eShooting_mv(eEC_Effect_c* effect, GAME* game);
static void eShooting_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_shooting = {
    // clang-format off
    &eShooting_init,
    &eShooting_ct,
    &eShooting_mv,
    &eShooting_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eShooting_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_SHOOTING, pos, NULL, game, NULL, item_name, prio, arg0, angle);
}

static void eShooting_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 320;

    effect->effect_specific[0] = RANDOM_F(30.0f) + 70.0f;
    effect->effect_specific[1] = 0;
}

static void eShooting_mv(eEC_Effect_c* effect, GAME* game) {
    s16 timer = 320 - effect->timer;

    effect->effect_specific[1] += 256;

    if (timer == (GETREG(MYKREG, 6) + 76)) {
        eEC_CLIP->effect_make_proc(eEC_EFFECT_SHOOTING_KIRA, effect->position, effect->prio, effect->arg1, game,
                                   (u16)effect->item_name, effect->effect_specific[0], 0);
    }
}

static Gfx* eShooting_GetTwoTileGfx(int x, int y, GAME* game) {
    return two_tex_scroll_dolphin(game->graph, 0, x, y, 8, 256, 1, 0, 0, 8, 32);
}

static void eShooting_dw(eEC_Effect_c* effect, GAME* game) {
    GRAPH* graph;
    f32 scale_z = effect->effect_specific[0] * 0.01f;
    s16 timer = 320 - effect->timer;
    Gfx* two_tile = eShooting_GetTwoTileGfx(0, -((timer - 120) * 6), game);

    graph = game->graph;
    OPEN_DISP(graph);

    _texture_z_light_fog_prim_xlu(graph);

    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, FALSE);
    Matrix_RotateY(-effect->effect_specific[1], TRUE);
    Matrix_scale(1.035f, 1.0f, 1.0f, TRUE);
    Matrix_RotateY(effect->effect_specific[1], TRUE);
    Matrix_RotateY(effect->arg1, TRUE);
    Matrix_scale(0.01f, 0.01f, 0.01f * scale_z, TRUE);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_9, two_tile);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_nagare01_modelT);

    CLOSE_DISP(graph);
}
