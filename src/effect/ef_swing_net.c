#include "ef_effect_control.h"

static void eSwing_Net_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSwing_Net_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSwing_Net_mv(eEC_Effect_c* effect, GAME* game);
static void eSwing_Net_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_swing_net = {
    // clang-format off
    &eSwing_Net_init,
    &eSwing_Net_ct,
    &eSwing_Net_mv,
    &eSwing_Net_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSwing_Net_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eSwing_Net_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eSwing_Net_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eSwing_Net_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
