#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_player_lib.h"

static void eSwing_Net_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSwing_Net_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSwing_Net_mv(eEC_Effect_c* effect, GAME* game);
static void eSwing_Net_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_swing_net = {
    // clang-format off
    &eSwing_Net_init,
    &eSwing_Net_ct,
    &eSwing_Net_mv,
    &eSwing_Net_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSwing_Net_Hanabira_Make(eEC_Effect_c* effect, GAME* game) {
    mActor_name_t* fg_p = mFI_GetUnitFG(effect->position);
    mActor_name_t item;

    if (fg_p != NULL) {
        item = *fg_p;

        if (IS_ITEM_GROWN_FLOWER(item)) {
            int i;
            s16 arg = item - FLOWER_PANSIES0;

            for (i = 0; i < 2; i++) {
                eEC_CLIP->effect_make_proc(eEC_EFFECT_HANABIRA, effect->position, effect->prio, 0, game, effect->item_name, arg, 2);
            }
        }
    }
}


static void eSwing_Net_call_effect(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    int bush_happa_num;
    int bush_yuki_num;

    switch (arg0) {
        case mCoBG_ATTRIBUTE_BUSH:
            if (pos.y < mCoBG_GetBgY_AngleS_FromWpos(NULL, pos, 0.0f) + 10.0f) {
                bush_happa_num = 5;

                while (bush_happa_num-- != 0) {
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_HAPPA, pos, prio, angle, game, item_name, arg0, 3);
                }

                if (Common_Get(time.season) == mTM_SEASON_WINTER) {
                    bush_yuki_num = 4;

                    while (bush_yuki_num-- != 0) {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_YUKI, pos, prio, angle, game, item_name, arg0, 0);
                    }
                }
            }
        break;
    }
}

static void eSwing_Net_call_stick_effect(xyz_t pos, int prio, GAME* game, u16 item_name) {
    xyz_t player_pos = GET_PLAYER_ACTOR_GAME_ACTOR(game)->world.position;
    xyz_t effect_pos = pos;
    xyz_t d_pos;
    s16 arg0 = 1;
    int n;

    xyz_t_sub(&player_pos, &effect_pos, &d_pos);
    xyz_t_mult_v(&d_pos, 1.0f/6.0f);

    n = 3;
    while (n-- != 0) {
        effect_pos.x += d_pos.x;
        effect_pos.z += d_pos.z;

        eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, effect_pos, prio, 0, game, item_name, arg0, 0);

        if (arg0 < mCoBG_ATTRIBUTE_GRASS3) {
            arg0++;
        }
    }
}

static void eSwing_Net_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    if (eEC_CLIP != NULL) {
        if (arg1 == 0) {
            eSwing_Net_call_effect(pos, prio, angle, game, item_name, arg0, arg1);
        } else if (mCoBG_CheckWaterAttribute(arg0) || arg0 == mCoBG_ATTRIBUTE_WAVE) {
            xyz_t effect_pos = pos;
            s16 effect_angle;
            int i;
            
            effect_pos.x += sin_s(angle) * -13.0f;
            effect_pos.y += 5.0f;
            effect_pos.z += cos_s(angle) * -13.0f;
            
            for (i = 0, effect_angle = 0; i < 8; i++) {
                s16 angle2 = effect_angle + DEG2SHORT_ANGLE(RANDOM2_F(40.0f));

                eEC_CLIP->effect_make_proc(eEC_EFFECT_MIZUTAMA, effect_pos, prio, angle2, game, item_name, arg0, 0x5000);
                effect_angle += DEG2SHORT_ANGLE2(45.0f);
            }

            eEC_CLIP->effect_make_proc(eEC_EFFECT_AMI_MIZU, pos, prio, angle, game, item_name, 0, 0);
            eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, effect_pos, prio, 0, game, item_name, 0, 0);
            eSwing_Net_call_stick_effect(effect_pos, prio, game, item_name);
            sAdo_OngenTrgStart(NA_SE_AMI_HIT_WATER, &effect_pos);
        }
    }

    eEC_CLIP->make_effect_proc(eEC_EFFECT_SWING_NET, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eSwing_Net_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 0;
    eSwing_Net_Hanabira_Make(effect, game);
    effect->effect_specific[0] = *(s16*)ct_arg;
}

static void eSwing_Net_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eSwing_Net_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
