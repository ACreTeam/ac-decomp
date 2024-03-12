#include "ef_effect_control.h"

static void eTH_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTH_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTH_mv(eEC_Effect_c* effect, GAME* game);
static void eTH_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_turi_hamon = {
    // clang-format off
    &eTH_init,
    &eTH_ct,
    &eTH_mv,
    &eTH_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eTH_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eTH_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eTH_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eTH_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
