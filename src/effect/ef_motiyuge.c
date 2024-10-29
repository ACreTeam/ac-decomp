#include "ef_effect_control.h"

static void eMotiyuge_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eMotiyuge_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eMotiyuge_mv(eEC_Effect_c* effect, GAME* game);
static void eMotiyuge_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_motiyuge = {
    // clang-format off
    &eMotiyuge_init,
    &eMotiyuge_ct,
    &eMotiyuge_mv,
    &eMotiyuge_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eMotiyuge_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eMotiyuge_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eMotiyuge_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eMotiyuge_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
