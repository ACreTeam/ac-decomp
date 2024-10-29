#include "ef_effect_control.h"

static void eHanabiSwitch_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eHanabiSwitch_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eHanabiSwitch_mv(eEC_Effect_c* effect, GAME* game);
static void eHanabiSwitch_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_hanabi_switch = {
    // clang-format off
    &eHanabiSwitch_init,
    &eHanabiSwitch_ct,
    &eHanabiSwitch_mv,
    &eHanabiSwitch_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eHanabiSwitch_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eHanabiSwitch_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eHanabiSwitch_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eHanabiSwitch_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
