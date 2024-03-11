#include "ef_effect_control.h"

static void eYukidama_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eYukidama_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eYukidama_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eYukidama_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

eEC_PROFILE_c iam_ef_yukidama = {
    // clang-format off
    &eYukidama_init,
    &eYukidama_ct,
    &eYukidama_mv,
    &eYukidama_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};
