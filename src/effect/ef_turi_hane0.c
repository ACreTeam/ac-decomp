#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern Gfx ef_turi_hane01_00_modelT[];

extern u8 ef_turi_hane01_0_int_i4[];
extern u8 ef_turi_hane01_1_int_i4[];
extern u8 ef_turi_hane01_2_int_i4[];
extern u8 ef_turi_hane01_3_int_i4[];

static void eTH0_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTH0_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTH0_mv(eEC_Effect_c* effect, GAME* game);
static void eTH0_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_turi_hane0 = {
    // clang-format off
    &eTH0_init,
    &eTH0_ct,
    &eTH0_mv,
    &eTH0_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static u8* eTuri_Hane0Ptn[] = {
    ef_turi_hane01_0_int_i4, ef_turi_hane01_0_int_i4, ef_turi_hane01_1_int_i4, ef_turi_hane01_1_int_i4,
    ef_turi_hane01_2_int_i4, ef_turi_hane01_2_int_i4, ef_turi_hane01_3_int_i4, ef_turi_hane01_3_int_i4,
};

static void eTH0_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_TURI_HANE0, pos, NULL, game, NULL, item_name, prio, 0, 0);
}

static void eTH0_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    f32 scale;

    effect->timer = 16;

    switch (effect->arg0) {
        case 1:
            scale = 0.013f;
            break;
        case 2:
            scale = 0.014f;
            break;
        case 3:
            scale = 0.009f;
            break;
        case 4:
            scale = 0.007f;
            break;
        default:
            scale = 0.01f;
            break;
    }

    effect->scale.x = scale;
    effect->scale.y = scale;
    effect->scale.z = scale;
}

static void eTH0_mv(eEC_Effect_c* effect, GAME* game) {
    return;
}

static void eTH0_dw(eEC_Effect_c* effect, GAME* game) {
    xyz_t scale = effect->scale;
    s16 counter = (s16)(16 - effect->timer) >> 1;
    counter = CLAMP(counter, 0, 8);

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);

    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, FALSE);
    Matrix_scale(scale.x, scale.y, scale.z, TRUE);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, eTuri_Hane0Ptn[counter]);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_turi_hane01_00_modelT);

    CLOSE_DISP(game->graph);
}
