#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern Gfx ef_ongen_mouth_model[];
extern Gfx ef_ongen_mic_model[];

static void eOngen_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eOngen_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eOngen_mv(eEC_Effect_c* effect, GAME* game);
static void eOngen_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_ongen = {
    // clang-format off
    &eOngen_init,
    &eOngen_ct,
    &eOngen_mv,
    &eOngen_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eOngen_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_ONGEN, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eOngen_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    static s16 timer_table[] = { 2, 1, 10 };
    effect->timer = timer_table[effect->arg0];
}

static void eOngen_mv(eEC_Effect_c* effect, GAME* game) {
    return;
}

static void eOngen_TidyArgData(s16* arg0) {
    if (*arg0 < 0) {
        *arg0 = 0;
    } else if (*arg0 >= 3) {
        *arg0 = 2;
    }
}

static void eOngen_dw(eEC_Effect_c* effect, GAME* game) {
    static f32 scale_table[] = { 0.027f, 0.0139999999f, 0.027f };
    static Gfx* disp_table[] = { ef_ongen_mouth_model, ef_ongen_mic_model, ef_ongen_mouth_model };
    f32 scale;

    OPEN_DISP(game->graph);

    eOngen_TidyArgData(&effect->arg0);
    scale = scale_table[effect->arg0];

    _texture_z_light_fog_prim_xlu(game->graph);

    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_mult(&((GAME_PLAY*)game)->billboard_matrix, MTX_MULT);
    Matrix_scale(scale, scale, scale, MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 128, 255, 255, 255, 190);
    gSPDisplayList(NEXT_POLY_XLU_DISP, disp_table[effect->arg0]);

    CLOSE_DISP(game->graph);
}
