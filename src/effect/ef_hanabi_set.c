#include "ef_effect_control.h"

static void eHanabiSet_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eHanabiSet_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eHanabiSet_mv(eEC_Effect_c* effect, GAME* game);
static void eHanabiSet_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_hanabi_set = {
    // clang-format off
    &eHanabiSet_init,
    &eHanabiSet_ct,
    &eHanabiSet_mv,
    &eHanabiSet_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eHanabiSet_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eHanabiSet_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eHanabiSet_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eHanabiSet_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
