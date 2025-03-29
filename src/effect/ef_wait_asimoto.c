#include "ef_effect_control.h"

#include "m_common_data.h"

static void eWait_Asimoto_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eWait_Asimoto_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eWait_Asimoto_mv(eEC_Effect_c* effect, GAME* game);
static void eWait_Asimoto_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_wait_asimoto = {
    // clang-format off
    &eWait_Asimoto_init,
    &eWait_Asimoto_ct,
    &eWait_Asimoto_mv,
    &eWait_Asimoto_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eWait_Asimoto_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    if (arg0 == mCoBG_ATTRIBUTE_WAVE || arg0 == mCoBG_ATTRIBUTE_SEA) {
        eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, pos, prio, 0, game, item_name, 3, 0);
    }

    eEC_CLIP->make_effect_proc(eEC_EFFECT_WAIT_ASIMOTO, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eWait_Asimoto_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 0;
}

static void eWait_Asimoto_mv(eEC_Effect_c* effect, GAME* game) {
    // nothing
}

static void eWait_Asimoto_dw(eEC_Effect_c* effect, GAME* game) {
    // nothing
}
