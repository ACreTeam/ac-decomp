#include "ef_effect_control.h"

static void eSSHN_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSSHN_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSSHN_mv(eEC_Effect_c* effect, GAME* game);
static void eSSHN_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_siawase_hana = {
    // clang-format off
    &eSSHN_init,
    &eSSHN_ct,
    &eSSHN_mv,
    &eSSHN_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSSHN_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eSSHN_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eSSHN_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eSSHN_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
