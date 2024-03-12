#include "ef_effect_control.h"

static void ePun_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void ePun_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void ePun_mv(eEC_Effect_c* effect, GAME* game);
static void ePun_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_pun = {
    // clang-format off
    &ePun_init,
    &ePun_ct,
    &ePun_mv,
    &ePun_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void ePun_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void ePun_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void ePun_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void ePun_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
