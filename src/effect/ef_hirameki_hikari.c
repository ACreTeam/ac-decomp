#include "ef_effect_control.h"

#include "m_common_data.h"

extern Gfx ef_hirameki01_hikari_modelT[];

static void eHiramekiH_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eHiramekiH_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eHiramekiH_mv(eEC_Effect_c* effect, GAME* game);
static void eHiramekiH_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_hirameki_hikari = {
    // clang-format off
    &eHiramekiH_init,
    &eHiramekiH_ct,
    &eHiramekiH_mv,
    &eHiramekiH_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eHiramekiH_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    pos.y += 24.0f;
    eEC_CLIP->make_effect_proc(eEC_EFFECT_HIRAMEKI_HIKARI, pos, NULL, game, NULL, item_name, prio, 0, 0);
}

static void eHiramekiH_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 12;
    effect->offset.x = effect->offset.y = effect->offset.z = 0.0f;
}

static void eHiramekiH_mv(eEC_Effect_c* effect, GAME* game) {
    return;
}

static void eHiramekiH_dw(eEC_Effect_c* effect, GAME* game) {
    u8 alpha;
    s16 timer = 12 - effect->timer;
    xyz_t* pos = &effect->position;
    xyz_t* offset = &effect->offset;
    xyz_t* scale = &effect->scale;

    scale->z = scale->y = scale->x = eEC_CLIP->calc_adjust_proc(timer, 0, 12, 0.014f, 0.0175f);

    switch (timer) {
        case 0:
        case 1:
        case 2:
        case 3:
            alpha = timer * 50;
            break;

        default:
            alpha = (s8)eEC_CLIP->calc_adjust_proc(timer, 4, 12, 255.0f, 0.0f);
            break;
    }

    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_offset_proc(game, pos, scale, offset);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 100, alpha);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_hirameki01_hikari_modelT);

    CLOSE_DISP(game->graph);
}
