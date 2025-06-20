#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_debug.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void eSandsplash_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSandsplash_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSandsplash_mv(eEC_Effect_c* effect, GAME* game);
static void eSandsplash_dw(eEC_Effect_c* effect, GAME* game);

extern Gfx ef_sunahane01_00_modelT[];

extern u8 ef_sunahane01_0_inta_ia8[];
extern u8 ef_sunahane01_1_inta_ia8[];
extern u8 ef_sunahane01_2_inta_ia8[];
extern u8 ef_sunahane01_3_inta_ia8[];

eEC_PROFILE_c iam_ef_sandsplash = {
    // clang-format off
    &eSandsplash_init,
    &eSandsplash_ct,
    &eSandsplash_mv,
    &eSandsplash_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static u8* eSunahane_pattern_table[] = {
    ef_sunahane01_0_inta_ia8, ef_sunahane01_0_inta_ia8, ef_sunahane01_1_inta_ia8, ef_sunahane01_1_inta_ia8,
    ef_sunahane01_2_inta_ia8, ef_sunahane01_2_inta_ia8, ef_sunahane01_3_inta_ia8, ef_sunahane01_3_inta_ia8,
};

static void eSandsplash_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    pos.y -= 3.0f;
    pos.z += 5.0f;

    eEC_CLIP->make_effect_proc(eEC_EFFECT_SANDSPLASH, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eSandsplash_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->velocity.x = 0.0f;
    effect->velocity.y = 0.5f;
    effect->velocity.z = 0.0f;

    effect->acceleration.x = 0.0f;
    effect->acceleration.y = -0.01f;
    effect->acceleration.z = 0.0f;

    if (effect->arg0 == 2) {
        effect->velocity.x = sin_s(*(s16*)ct_arg);
        effect->velocity.z = cos_s(*(s16*)ct_arg);

        effect->acceleration = ZeroVec;

        effect->offset.x = 0.005f;
        effect->offset.y = 0.01f;
    } else if (effect->arg0 == 1) {
        effect->velocity.x = sin_s(*(s16*)ct_arg);
        effect->velocity.z = cos_s(*(s16*)ct_arg);

        effect->acceleration = ZeroVec;
        effect->acceleration.y = -0.075;

        effect->offset.x = 0.008f;
        effect->offset.y = 0.012999999f;
    } else if (effect->arg0 == 3) {
        effect->velocity.x = sin_s(*(s16*)ct_arg) * 0.25f;
        effect->velocity.z = cos_s(*(s16*)ct_arg);
        effect->velocity.y = 0.0f;

        effect->acceleration = ZeroVec;
        effect->acceleration.y = -0.05;

        effect->offset.x = 0.006f;
        effect->offset.y = 0.012f;
    } else {
        effect->offset.x = 0.005f;
        effect->offset.y = 0.01f;
    }

    effect->timer = 16;
}

static void eSandsplash_mv(eEC_Effect_c* effect, GAME* game) {
    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->position, &effect->velocity, &effect->position);

    effect->scale.x = eEC_CLIP->calc_adjust_proc(effect->timer, 0, 16, effect->offset.y, effect->offset.x);
    effect->scale.y = effect->scale.z = effect->scale.x;
}

static void eSandsplash_dw(eEC_Effect_c* effect, GAME* game) {
    float scale;
    s16 idx = (16 - effect->timer) >> 1;
    idx = CLAMP(idx, 0, 7);

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);

    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_RotateX(DEG2SHORT_ANGLE2(-45.0f), MTX_MULT);

    scale = GETREG(MYKREG, 0x1b) * 0.01f + 1.0f;
    Matrix_scale(effect->scale.x * scale, effect->scale.y * scale, effect->scale.z * scale, MTX_MULT);

    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 130, 20, 20, 20, 255);
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, 205, 180, 140, 255);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, eSunahane_pattern_table[idx]);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_sunahane01_00_modelT);

    CLOSE_DISP(game->graph);
}
