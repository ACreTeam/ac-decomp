#include "ef_effect_control.h"

#include "m_common_data.h"

static void eSlip_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSlip_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSlip_mv(eEC_Effect_c* effect, GAME* game);
static void eSlip_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_slip = {
    // clang-format off
    &eSlip_init,
    &eSlip_ct,
    &eSlip_mv,
    &eSlip_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSlip_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    s16 weather;

    if (eEC_CLIP != NULL) {
        weather = mEnv_NowWeather();
        pos.y += 2.0f;

        switch (Common_Get(time).season) {
            case mTM_SEASON_WINTER: {
                switch (arg0) {
                    case mCoBG_ATTRIBUTE_GRASS0:
                    case mCoBG_ATTRIBUTE_GRASS1:
                    case mCoBG_ATTRIBUTE_GRASS2:
                        if (((arg1 & 3) == 0) && (arg1 < 14)) {
                            pos.x -= sin_s(angle) * 10.0f;
                            pos.z -= cos_s(angle) * 10.0f;
                            pos.y += 5.0f;
                            eEC_CLIP->effect_make_proc(eEC_EFFECT_YUKIHANE, pos, prio, angle, game, item_name, arg0, 0);
                        }
                        break;

                    case mCoBG_ATTRIBUTE_BUSH:
                        break;

                    case mCoBG_ATTRIBUTE_SAND:
                        if (((arg1 & 3) == 0) && (arg1 < 10)) {
                            pos.x -= sin_s(angle) * 13.0f;
                            pos.z -= cos_s(angle) * 13.0f;
                            pos.y += 6.0f;
                            eEC_CLIP->effect_make_proc(eEC_EFFECT_SANDSPLASH, pos, prio, angle, game, item_name, 2, 0);
                        }
                        break;

                    default:
                        if ((weather == mEnv_WEATHER_RAIN) || (arg0 == mCoBG_ATTRIBUTE_WAVE)) {
                            if (((arg1 & 3) == 0) && (arg1 < 10)) {
                                pos.x -= sin_s(angle) * 13.0f;
                                pos.z -= cos_s(angle) * 13.0f;
                                pos.y += 6.0f;
                                eEC_CLIP->effect_make_proc(eEC_EFFECT_SIBUKI, pos, prio, angle, game, item_name, arg0,
                                                           0);
                            }
                        } else if (((arg1 & 3) == 0) && (arg1 < 10)) {
                            pos.y += 7.0f;
                            eEC_CLIP->effect_make_proc(eEC_EFFECT_DUST, pos, prio, angle, game, item_name, arg0, 8);
                        }
                        break;
                }
                break;
            }

            default: {
                switch (arg0) {
                    case mCoBG_ATTRIBUTE_BUSH:
                        break;

                    case mCoBG_ATTRIBUTE_SAND:
                        if (((arg1 & 3) == 0) && (arg1 < 10)) {
                            pos.x -= sin_s(angle) * 13.0f;
                            pos.z -= cos_s(angle) * 13.0f;
                            pos.y += 6.0f;
                            eEC_CLIP->effect_make_proc(eEC_EFFECT_SANDSPLASH, pos, prio, angle, game, item_name, 2, 0);
                        }
                        break;

                    default:
                        if ((weather == mEnv_WEATHER_RAIN) || (arg0 == mCoBG_ATTRIBUTE_WAVE)) {
                            if (((arg1 & 3) == 0) && (arg1 < 10)) {
                                pos.x -= sin_s(angle) * 13.0f;
                                pos.z -= cos_s(angle) * 13.0f;
                                pos.y += 6.0f;
                                eEC_CLIP->effect_make_proc(eEC_EFFECT_SIBUKI, pos, prio, angle, game, item_name, arg0,
                                                           0);
                            }
                            break;
                        }
                        if (((arg1 & 3) == 0) && (arg1 < 10)) {
                            pos.y += 7.0f;
                            eEC_CLIP->effect_make_proc(eEC_EFFECT_DUST, pos, prio, angle, game, item_name, arg0, 8);
                        }
                        break;
                }
                break;
            }
        }
    }

    eEC_CLIP->make_effect_proc(eEC_EFFECT_SLIP, pos, NULL, game, NULL, item_name, prio, 0, 0);
}

static void eSlip_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 0;
}

static void eSlip_mv(eEC_Effect_c* effect, GAME* game) {
    return;
}

static void eSlip_dw(eEC_Effect_c* effect, GAME* game) {
    return;
}
