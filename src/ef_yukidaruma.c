#include "ef_effect_control.h"

static void eYukidaruma_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eYukidaruma_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eYukidaruma_mv(eEC_Effect_c* effect, GAME* game);
static void eYukidaruma_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_yukidaruma = {
    // clang-format off
    &eYukidaruma_init,
    &eYukidaruma_ct,
    &eYukidaruma_mv,
    &eYukidaruma_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eYukidaruma_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eYukidaruma_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eYukidaruma_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eYukidaruma_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
