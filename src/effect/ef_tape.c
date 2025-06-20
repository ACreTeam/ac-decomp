#include "ef_effect_control.h"
#include "graph.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_debug.h"

static void eTape_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTape_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTape_mv(eEC_Effect_c* effect, GAME* game);
static void eTape_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_tape = {
    // clang-format off
    &eTape_init,
    &eTape_ct,
    &eTape_mv,
    &eTape_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};
extern Gfx ef_tape01_01_model[];

static void eTape_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    (*eEC_CLIP->make_effect_proc)(eEC_EFFECT_TAPE, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eTape_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16 angle;
    f32 ofs_x;
    xyz_t pos;

    angle = *(s16*)ct_arg;
    effect->timer = 80;
    effect->effect_specific[0] = DEG2SHORT_ANGLE2(20.0f); //3640;
    effect->effect_specific[1] = angle;
    ofs_x = sin_s(effect->effect_specific[0]) * 2.0f;
    pos.x = ofs_x * sin_s(effect->effect_specific[1]);
    pos.z = ofs_x * cos_s(effect->effect_specific[1]);
    pos.y = cos_s(effect->effect_specific[0]) * 2.0f;
    Matrix_RotateY(effect->arg0, MTX_LOAD);
    Matrix_RotateX(effect->arg1, MTX_MULT);
    Matrix_Position(&pos, &effect->velocity);
    effect->acceleration = ZeroVec;
    effect->acceleration.y = -0.025f;
}

static void eTape_mv(eEC_Effect_c* effect, GAME* game) {
    if (effect->timer < 74) {
        xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
        xyz_t_add(&effect->position, &effect->velocity, &effect->position);
        effect->velocity.x *= sqrtf(0.9f);
        effect->velocity.y *= sqrtf(0.9f);
        effect->velocity.z *= sqrtf(0.9f);
    }
}

static void eTape_dw(eEC_Effect_c* effect, GAME* game) {
    s16 now_timer = effect->timer;
    f32 scale_y;
    f32 scale_z;
    f32 scale;
    u8 a;

    if (now_timer > 68) {
        scale_y = eEC_CLIP->calc_adjust_proc(now_timer, 68, 80, 1.0f, 0.0f) * 0.01f;
        scale_z = 0.0f;
    } else if (now_timer > 56) {
        scale_y = 0.01f;
        scale_z = 0.0f;
    } else {
        scale_y = eEC_CLIP->calc_adjust_proc(now_timer, 0, 56, 0.7f, 1.0f) * 0.01f;
        scale_z = eEC_CLIP->calc_adjust_proc(effect->timer, 0, 56, 1.0f, 0.0f) * 0.01f;
    }

    if (effect->timer > 14) {
        a = 255;
    } else {
        a = (int)eEC_CLIP->calc_adjust_proc(effect->timer, 0, 28, 0.0f, 255.0f);
    }

    OPEN_DISP(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);
    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_RotateY(effect->arg0, MTX_MULT);
    Matrix_RotateX(effect->arg1, MTX_MULT);
    Matrix_rotateXYZ(effect->effect_specific[0], effect->effect_specific[1], 0, MTX_MULT);
    scale = GETREG(MYKREG, 27) * 0.01f + 1.0f;
    Matrix_scale(0.01f * scale, scale_y * scale, scale_z * scale, MTX_MULT);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 155, 155, 0, a);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_tape01_01_model);
    CLOSE_DISP(game->graph);
}
