#include "ef_effect_control.h"

static void eKPun_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKPun_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKPun_mv(eEC_Effect_c* effect, GAME* game);
static void eKPun_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_kpun = {
    // clang-format off
    &eKPun_init,
    &eKPun_ct,
    &eKPun_mv,
    &eKPun_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eKPun_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eKPun_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eKPun_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eKPun_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
