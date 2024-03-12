#include "ef_effect_control.h"

static void eAS2_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eAS2_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eAS2_mv(eEC_Effect_c* effect, GAME* game);
static void eAS2_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_ase2 = {
    // clang-format off
    &eAS2_init,
    &eAS2_ct,
    &eAS2_mv,
    &eAS2_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eAS2_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eAS2_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eAS2_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eAS2_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
