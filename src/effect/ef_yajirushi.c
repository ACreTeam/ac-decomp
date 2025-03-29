#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"

static void eYajirushi_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eYajirushi_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eYajirushi_mv(eEC_Effect_c* effect, GAME* game);
static void eYajirushi_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_yajirushi = {
    // clang-format off
    &eYajirushi_init,
    &eYajirushi_ct,
    &eYajirushi_mv,
    &eYajirushi_dw,
    6,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

#define eYajirushi_ALPHA effect->effect_specific[0]

static void eYajirushi_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_YAJIRUSHI, pos, NULL, game, NULL, item_name, prio, 0, 0);
}

static void eYajirushi_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    eYajirushi_ALPHA = 0;
    effect->timer = 4;
}

static void eYajirushi_mv(eEC_Effect_c* effect, GAME* game) {
    eEC_CLIP->set_continious_env_proc(effect, 4, 60);

    if (effect->state == eEC_STATE_NORMAL) {
        eYajirushi_ALPHA = eEC_CLIP->calc_adjust_proc(4 - effect->timer, 0, 3, 0.0f, 255.0f);
    } else if (effect->state == eEC_STATE_CONTINUOUS) {
        eYajirushi_ALPHA = 255;
    } else if (effect->state == eEC_STATE_FINISHED) {
        eYajirushi_ALPHA = eEC_CLIP->calc_adjust_proc(6 - effect->timer, 0, 6, 255.0f, 0.0f);
    }
}

extern Gfx ef_kore_modelT[];

static void eYajirushi_dw(eEC_Effect_c* effect, GAME* game) {
    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);
    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, &effect->scale);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 80, 30, eYajirushi_ALPHA);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_kore_modelT);

    CLOSE_DISP(game->graph);
}
