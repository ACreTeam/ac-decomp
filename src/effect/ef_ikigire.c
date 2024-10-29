#include "ef_effect_control.h"

static void eIkigire_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eIkigire_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eIkigire_mv(eEC_Effect_c* effect, GAME* game);
static void eIkigire_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_ikigire = {
    // clang-format off
    &eIkigire_init,
    &eIkigire_ct,
    &eIkigire_mv,
    &eIkigire_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eIkigire_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eIkigire_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eIkigire_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eIkigire_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
