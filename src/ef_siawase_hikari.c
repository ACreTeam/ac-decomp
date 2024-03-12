#include "ef_effect_control.h"

static void eSSHKR_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSSHKR_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSSHKR_mv(eEC_Effect_c* effect, GAME* game);
static void eSSHKR_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_siawase_hikari = {
    // clang-format off
    &eSSHKR_init,
    &eSSHKR_ct,
    &eSSHKR_mv,
    &eSSHKR_dw,
    72,
    eEC_EFFECT_SIAWASE_HANA,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSSHKR_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eSSHKR_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eSSHKR_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eSSHKR_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
