#include "ef_effect_control.h"

#include "m_common_data.h"

static void eSwing_Rod_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSwing_Rod_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSwing_Rod_mv(eEC_Effect_c* effect, GAME* game);
static void eSwing_Rod_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_swing_rod = {
    // clang-format off
    &eSwing_Rod_init,
    &eSwing_Rod_ct,
    &eSwing_Rod_mv,
    &eSwing_Rod_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSwing_Rod_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    int bush_happa_num;
    int bush_yuki_num;

    if (eEC_CLIP != NULL) {
        switch (arg0) {
            case mCoBG_ATTRIBUTE_BUSH:
                bush_happa_num = 3;

                while (bush_happa_num-- != 0) {
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_HAPPA, pos, prio, angle, game, item_name, arg0, 1);
                }

                if (Common_Get(time.season) == mTM_SEASON_WINTER) {
                    bush_yuki_num = 3;

                    while (bush_yuki_num-- != 0) {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_YUKI, pos, prio, angle, game, item_name, arg0, 0);
                    }
                }
                break;
            }
    }

    eEC_CLIP->make_effect_proc(eEC_EFFECT_SWING_ROD, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eSwing_Rod_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 0;
}

static void eSwing_Rod_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eSwing_Rod_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
