#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void eKT_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKT_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKT_mv(eEC_Effect_c* effect, GAME* game);
static void eKT_dw(eEC_Effect_c* effect, GAME* game);

extern Gfx ef_kantanhu01_00_modelT[];

// clang-format off
eEC_PROFILE_c iam_ef_kantanhu = {
    &eKT_init,
    &eKT_ct,
    &eKT_mv,
    &eKT_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
};

f32 eKT_scale_data[][2] = { 
    { 0.5f, 0.5f },
    { 0.5f, 1.2f },
    { 0.5f, 2.0f },
    { 1.2f, 1.4f },
    { 2.0f, 0.7f },
    { 1.5f, 0.8f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 1.0f }
};
// clang-format on

static void eKT_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    xyz_t vec = { 0.0f, 15.0f, -3.0f };

    sMath_RotateY(&vec, SHORT2RAD_ANGLE2(angle));
    pos.x += vec.x;
    pos.y += vec.y;
    pos.z += vec.z;

    eEC_CLIP->make_effect_proc(eEC_EFFECT_KANTANHU, pos, NULL, game, NULL, item_name, prio, 0, 0);
}

static void eKT_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 72;
    sAdo_OngenTrgStart(0x14b, &effect->position);
}

static void eKT_mv(eEC_Effect_c* effect, GAME* game) {
    return;
}

static void eKT_dw(eEC_Effect_c* effect, GAME* game) {
    s16 frame_index;
    s16 timer = 72 - effect->timer;
    u16 alpha = (u8)eEC_CLIP->calc_adjust_proc(timer, 64, 72, 255.0f, 0.0f);

    if (timer > 50) {
        timer = 50;
    }
    frame_index = timer >> 1;
    effect->scale.x = eKT_scale_data[frame_index][0] * 0.008f;
    effect->scale.y = eKT_scale_data[frame_index][1] * 0.008f;
    effect->scale.z = 0.008f;

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);
    eEC_CLIP->auto_matrix_xlu_offset_proc(game, &effect->position, &effect->scale, &effect->offset);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 128, 255, 255, 255, alpha);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_kantanhu01_00_modelT);

    CLOSE_DISP(game->graph);
}
