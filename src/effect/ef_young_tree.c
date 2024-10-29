#include "ef_effect_control.h"

static void eYoung_Tree_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eYoung_Tree_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eYoung_Tree_mv(eEC_Effect_c* effect, GAME* game);
static void eYoung_Tree_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_young_tree = {
    // clang-format off
    &eYoung_Tree_init,
    &eYoung_Tree_ct,
    &eYoung_Tree_mv,
    &eYoung_Tree_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eYoung_Tree_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eYoung_Tree_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eYoung_Tree_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eYoung_Tree_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
