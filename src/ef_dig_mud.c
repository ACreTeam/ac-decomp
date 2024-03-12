#include "ef_effect_control.h"

static void eDig_Mud_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eDig_Mud_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eDig_Mud_mv(eEC_Effect_c* effect, GAME* game);
static void eDig_Mud_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_dig_mud = {
    // clang-format off
    &eDig_Mud_init,
    &eDig_Mud_ct,
    &eDig_Mud_mv,
    &eDig_Mud_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eDig_Mud_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eDig_Mud_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eDig_Mud_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eDig_Mud_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
