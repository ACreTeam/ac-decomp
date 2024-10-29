#include "ef_effect_control.h"

static void eHanabiBotan2_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eHanabiBotan2_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eHanabiBotan2_mv(eEC_Effect_c* effect, GAME* game);
static void eHanabiBotan2_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_hanabi_botan2 = {
    // clang-format off
    &eHanabiBotan2_init,
    &eHanabiBotan2_ct,
    &eHanabiBotan2_mv,
    &eHanabiBotan2_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eHanabiBotan2_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eHanabiBotan2_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eHanabiBotan2_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eHanabiBotan2_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
