#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void eDouzou_Light_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eDouzou_Light_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eDouzou_Light_mv(eEC_Effect_c* effect, GAME* game);
static void eDouzou_Light_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_douzou_light = {
    // clang-format off
    &eDouzou_Light_init,
    &eDouzou_Light_ct,
    &eDouzou_Light_mv,
    &eDouzou_Light_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eDouzou_Light_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_DOUZOU_LIGHT, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eDouzou_Light_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    switch (effect->arg0) {
        case 0:
            effect->offset.x = 0.012f;
            break;
        case 1:
            effect->offset.x = 0.011f;
            break;
        case 2:
            effect->offset.x = 0.010f;
            break;
        default:
            effect->offset.x = 0.009f;
            break;
    }

    effect->timer = 24;
}

static void eDouzou_Light_mv(eEC_Effect_c* effect, GAME* game) {
    if (effect->timer > 12) {
        effect->scale.x = eEC_CLIP->calc_adjust_proc(effect->timer, 12, 24, effect->offset.x, 0.0f);
    } else {
        effect->scale.x = eEC_CLIP->calc_adjust_proc(effect->timer, 0, 12, 0.0f, effect->offset.x);
    }

    effect->scale.y = effect->scale.z = effect->scale.x;
}

extern Gfx ef_carhosi01_00_modelT[];

static void eDouzou_Light_dw(eEC_Effect_c* effect, GAME* game) {
    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, &effect->scale);

    switch (effect->arg0) {
        case 0:
            gDPSetEnvColor(NEXT_POLY_XLU_DISP, 255, 255, 0, 255);
            break;
        case 1:
            gDPSetEnvColor(NEXT_POLY_XLU_DISP, 200, 255, 255, 255);
            break;
        case 2:
            gDPSetEnvColor(NEXT_POLY_XLU_DISP, 255, 100, 100, 255);
            break;
        default:
            gDPSetEnvColor(NEXT_POLY_XLU_DISP, 100, 255, 100, 255);
            break;
    }

    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_carhosi01_00_modelT);

    CLOSE_DISP(game->graph);
}
