#include "ef_effect_control.h"

#include "m_common_data.h"

static void eKyousou_Onpu_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKyousou_Onpu_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKyousou_Onpu_mv(eEC_Effect_c* effect, GAME* game);
static void eKyousou_Onpu_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_kyousou_onpu = {
    // clang-format off
    &eKyousou_Onpu_init,
    &eKyousou_Onpu_ct,
    &eKyousou_Onpu_mv,
    &eKyousou_Onpu_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eKyousou_Onpu_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    if (eEC_CLIP != NULL) {
        eEC_CLIP->effect_make_proc(eEC_EFFECT_KONPU, pos, prio, angle, game, item_name, 2, 0);
    }

    eEC_CLIP->make_effect_proc(eEC_EFFECT_KYOUSOU_ONPU, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eKyousou_Onpu_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 0;
}

static void eKyousou_Onpu_mv(eEC_Effect_c* effect, GAME* game) {
    return;
}

static void eKyousou_Onpu_dw(eEC_Effect_c* effect, GAME* game) {
    return;
}
