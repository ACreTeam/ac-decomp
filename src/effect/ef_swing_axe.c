#include "ef_effect_control.h"

#include "m_common_data.h"

static void eSwing_Axe_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSwing_Axe_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSwing_Axe_mv(eEC_Effect_c* effect, GAME* game);
static void eSwing_Axe_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_swing_axe = {
    // clang-format off
    &eSwing_Axe_init,
    &eSwing_Axe_ct,
    &eSwing_Axe_mv,
    &eSwing_Axe_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSwing_Axe_Hanabira_Make(eEC_Effect_c* effect, GAME* game) {
    mActor_name_t* fg_p = mFI_GetUnitFG(effect->position);
    mActor_name_t item;

    if (fg_p != NULL) {
        item = *fg_p;

        if (IS_ITEM_GROWN_FLOWER(item)) {
            int i;
            s16 arg = item - FLOWER_PANSIES0;

            for (i = 0; i < 2; i++) {
                eEC_CLIP->effect_make_proc(eEC_EFFECT_HANABIRA, effect->position, effect->prio, 0, game, effect->item_name, arg, 3);
            }
        }
    }
}

static void eSwing_Axe_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    if (eEC_CLIP != NULL) {
        if (arg1 == 0) {
            int kikuzu_num = 4;

            while (kikuzu_num-- != 0) {
                eEC_CLIP->effect_make_proc(eEC_EFFECT_KIKUZU, pos, prio, angle, game, item_name, arg0, arg1);
            }
        } else if (arg1 == 1) {
            switch (arg0) {
                case mCoBG_ATTRIBUTE_BUSH: {
                    int bush_happa_num = 5;

                    while (bush_happa_num-- != 0) {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_HAPPA, pos, prio, angle, game, item_name, arg0, 1);
                    }

                    if (Common_Get(time.season) == mTM_SEASON_WINTER) {
                        int bush_yuki_num = 5;

                        while (bush_yuki_num-- != 0) {
                            eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_YUKI, pos, prio, angle, game, item_name, arg0, 0);
                        }
                    }
                    break;
                }
            }
        } else if (arg1 == 2) {
            s16 i;
            s16 impact_angle = angle + DEG2SHORT_ANGLE2(22.5f);

            for (i = 0; i < 2; i++) {
                eEC_CLIP->effect_make_proc(eEC_EFFECT_IMPACT_STAR, pos, prio, impact_angle, game, item_name, arg0, i);
            }
        } else if (arg1 == 3) {
            s16 i;

            for (i = 0; i < 2; i++) {
                eEC_CLIP->effect_make_proc(eEC_EFFECT_BREAK_AXE, pos, prio, angle, game, item_name, i, 0);
            }
        }
    }

    eEC_CLIP->make_effect_proc(eEC_EFFECT_SWING_AXE, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eSwing_Axe_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 0;
    if (effect->arg1  != 3) {
        eSwing_Axe_Hanabira_Make(effect, game);
    }
}

static void eSwing_Axe_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eSwing_Axe_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
