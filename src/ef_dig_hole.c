#include "ef_effect_control.h"

static void eDig_Hole_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eDig_Hole_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eDig_Hole_mv(eEC_Effect_c* effect, GAME* game);
static void eDig_Hole_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_dig_hole = {
    // clang-format off
    &eDig_Hole_init,
    &eDig_Hole_ct,
    &eDig_Hole_mv,
    &eDig_Hole_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eDig_Hole_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eDig_Hole_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eDig_Hole_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eDig_Hole_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
