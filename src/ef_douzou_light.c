#include "ef_effect_control.h"

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
    // TODO
}

static void eDouzou_Light_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eDouzou_Light_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eDouzou_Light_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
