#include "ef_effect_control.h"

static void eAmi_Mizu_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eAmi_Mizu_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eAmi_Mizu_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eAmi_Mizu_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

eEC_PROFILE_c iam_ef_ami_mizu = {
    // clang-format off
    &eAmi_Mizu_init,
    &eAmi_Mizu_ct,
    &eAmi_Mizu_mv,
    &eAmi_Mizu_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};
