#include "ef_effect_control.h"

#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "m_debug.h"

static void eYukihane_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eYukihane_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eYukihane_mv(eEC_Effect_c* effect, GAME* game);
static void eYukihane_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_yukihane = {
    // clang-format off
    &eYukihane_init,
    &eYukihane_ct,
    &eYukihane_mv,
    &eYukihane_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eYukihane_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_YUKIHANE, pos, NULL, game, NULL, item_name, prio, 0, 0);
}

static void eYukihane_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 16;
    effect->position.y += 0.5f;

    effect->scale.x = 0.008f;
    effect->scale.y = 0.008f;
    effect->scale.z = 0.008f;

    effect->velocity.x = 0.0f;
    effect->velocity.y = 0.5f;
    effect->velocity.z = 0.0f;

    effect->acceleration.x = 0.0f;
    effect->acceleration.y = -0.02f;
    effect->acceleration.z = 0.0f;
}

static void eYukihane_mv(eEC_Effect_c* effect, GAME* game) {
    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->position, &effect->velocity, &effect->position);
}

extern u8 ef_yukihane01_0_inta_ia8[];
extern u8 ef_yukihane01_1_inta_ia8[];
extern u8 ef_yukihane01_2_inta_ia8[];
extern u8 ef_yukihane01_3_inta_ia8[];

static u8* eYukihane_pattern_table[] = {
    ef_yukihane01_0_inta_ia8, ef_yukihane01_0_inta_ia8, ef_yukihane01_1_inta_ia8, ef_yukihane01_1_inta_ia8,
    ef_yukihane01_2_inta_ia8, ef_yukihane01_2_inta_ia8, ef_yukihane01_3_inta_ia8, ef_yukihane01_3_inta_ia8,
};

extern Gfx ef_yukihane01_00_modelT[];

static void eYukihane_dw(eEC_Effect_c* effect, GAME* game) {
    s16 elapsed_time = (s16)(16 - effect->timer) >> 1;
    s16 frame = elapsed_time < 0 ? 0 : (elapsed_time <= 7 ? elapsed_time : 7);
    f32 scale;

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);
    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_RotateX(DEG2SHORT_ANGLE(-45.0f), MTX_MULT);
    scale = 1.0f + ((f32)(int)GETREG(MYKREG, 27)) * 0.01f;
    Matrix_scale(effect->scale.x * scale, effect->scale.y * scale, effect->scale.z * scale, MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, eYukihane_pattern_table[frame]);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 130, 50, 80, 120, 230);
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, 0, 0, 0, 255);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_yukihane01_00_modelT);

    CLOSE_DISP(game->graph);
}
