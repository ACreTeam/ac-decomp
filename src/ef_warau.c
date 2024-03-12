#include "ef_effect_control.h"

static void eWU_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eWU_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eWU_mv(eEC_Effect_c* effect, GAME* game);
static void eWU_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_warau = {
    // clang-format off
    &eWU_init,
    &eWU_ct,
    &eWU_mv,
    &eWU_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eWU_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eWU_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eWU_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eWU_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
