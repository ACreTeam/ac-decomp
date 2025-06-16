#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void eTurnAsimoto_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTurnAsimoto_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTurnAsimoto_mv(eEC_Effect_c* effect, GAME* game);
static void eTurnAsimoto_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_turn_asimoto = {
    // clang-format off
    &eTurnAsimoto_init,
    &eTurnAsimoto_ct,
    &eTurnAsimoto_mv,
    &eTurnAsimoto_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eTurn_Hanabira_Make(eEC_Effect_c* effect, GAME* game) {
    mActor_name_t* fg_p = mFI_GetUnitFG(effect->position);
    mActor_name_t item;

    if (fg_p != NULL) {
        item = *fg_p;

        if (IS_ITEM_GROWN_FLOWER(item)) {
            xyz_t pos = effect->position;
            int i;
            s16 arg = item - FLOWER_PANSIES0;

            pos.x += sin_s(effect->effect_specific[0]) * 30.0f;
            pos.z += cos_s(effect->effect_specific[0]) * 30.0f;

            for (i = 0; i < 3; i++) {
                eEC_CLIP->effect_make_proc(eEC_EFFECT_HANABIRA, pos, effect->prio, 0, game, effect->item_name, arg, 4);
            }
        }
    }
}

// @cleanup - this is some really horrible code
static void eTurnAsimoto_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    f32 sin = sin_s(angle);
    f32 cos = cos_s(angle);
    int i;
    
    if (eEC_CLIP != NULL) {
        u32 season = Common_Get(time.season);
        s16 now_weather = mEnv_NowWeather();

        if (arg0 == mCoBG_ATTRIBUTE_BUSH) {
            for (i = 0; i < 4; i++) {
                eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_HAPPA, pos, prio, angle, game, item_name, arg0, 1);
            }

            if (season == mTM_SEASON_WINTER) {
                for (i = 0; i < 4; i++) {
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_YUKI, pos, prio, angle, game, item_name, arg0, 0);
                }
            }
        } else if (arg0 == mCoBG_ATTRIBUTE_SAND) {
            pos.x += sin * 5.0f;
            pos.z += cos * 5.0f;
            eEC_CLIP->effect_make_proc(eEC_EFFECT_SANDSPLASH, pos, prio, angle, game, item_name, 2, 0);
        } else if (arg0 == mCoBG_ATTRIBUTE_WAVE) {
            pos.x += sin * 5.0f;
            pos.z += cos * 5.0f;
            pos.y += 5.0f;

            if (arg1 == 0) {
                for (i = 0; i < 5; i++) {
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_MIZUTAMA, pos, prio, angle, game, item_name, arg0, 0x1000 | i);
                }
            } else {
                for (i = 0; i < 5; i++) {
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_MIZUTAMA, pos, prio, angle, game, item_name, arg0, 0x2000 | i);
                }
            }
        } else if (season == mTM_SEASON_WINTER && (arg0 == mCoBG_ATTRIBUTE_GRASS0 || arg0 == mCoBG_ATTRIBUTE_GRASS1 || arg0 == mCoBG_ATTRIBUTE_GRASS2 || arg0 == mCoBG_ATTRIBUTE_GRASS3)) {
            pos.x += sin * 5.0f;
            pos.z += cos * 5.0f;
            pos.y += 5.0f;

            if (arg1 == 0) {
                for (i = 0; i < 5; i++) {
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_YUKIDAMA, pos, prio, angle, game, item_name, arg0, 0x1000 | i);
                }
            } else {
                for (i = 0; i < 5; i++) {
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_YUKIDAMA, pos, prio, angle, game, item_name, arg0, 0x2000 | i);
                }
            }
        } else if (arg0 != mCoBG_ATTRIBUTE_FLOOR) {
            if (now_weather == mEnv_WEATHER_RAIN) {
                pos.x += sin * 5.0f;
                pos.z += cos * 5.0f;
                pos.y += 5.0f;

                if (arg1 == 0) {
                    for (i = 0; i < 5; i++) {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_MIZUTAMA, pos, prio, angle, game, item_name, arg0, 0x1000 | i);
                    }
                } else {
                    for (i = 0; i < 5; i++) {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_MIZUTAMA, pos, prio, angle, game, item_name, arg0, 0x2000 | i);
                    }
                }
            } else {
                if (arg1 == 0) {
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_TUMBLE_DUST, pos, prio, angle, game, item_name, arg0, 5);
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_DUST, pos, prio, angle, game, item_name, arg0, 1);
                } else {
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_TUMBLE_DUST, pos, prio, angle, game, item_name, arg0, 6);
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_DUST, pos, prio, angle, game, item_name, arg0, 2);
                }
            }
        }
    }

    eEC_CLIP->make_effect_proc(eEC_EFFECT_TURN_ASIMOTO, pos, NULL, game, &angle, item_name, prio, arg0, arg1);;
}

static void eTurnAsimoto_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16* angle_p = (s16*)ct_arg;

    effect->effect_specific[0] = *angle_p;
    eTurn_Hanabira_Make(effect, game);
    effect->timer = 0;
}

static void eTurnAsimoto_mv(eEC_Effect_c* effect, GAME* game) {
    // nothing
}

static void eTurnAsimoto_dw(eEC_Effect_c* effect, GAME* game) {
    // nothing
}
