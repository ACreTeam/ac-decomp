#include "ef_effect_control.h"

static void eSSHNC_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSSHNC_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSSHNC_mv(eEC_Effect_c* effect, GAME* game);
static void eSSHNC_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_siawase_hana_ch = {
    // clang-format off
    &eSSHNC_init,
    &eSSHNC_ct,
    &eSSHNC_mv,
    &eSSHNC_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSSHNC_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eSSHNC_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eSSHNC_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eSSHNC_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
