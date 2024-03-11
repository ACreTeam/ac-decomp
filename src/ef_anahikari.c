#include "ef_effect_control.h"

static void eAnahikari_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eAnahikari_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eAnahikari_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eAnahikari_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

eEC_PROFILE_c iam_ef_anahikari = {
    // clang-format off
    &eAnahikari_init,
    &eAnahikari_ct,
    &eAnahikari_mv,
    &eAnahikari_dw,
    60,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};
