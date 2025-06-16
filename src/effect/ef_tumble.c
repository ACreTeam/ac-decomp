#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void eTumble_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTumble_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTumble_mv(eEC_Effect_c* effect, GAME* game);
static void eTumble_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_tumble = {
    // clang-format off
    &eTumble_init,
    &eTumble_ct,
    &eTumble_mv,
    &eTumble_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eTumble_Hanabira_Make(eEC_Effect_c* effect, GAME* game) {
    mActor_name_t* fg_p = mFI_GetUnitFG(effect->position);
    mActor_name_t item;

    if (fg_p != NULL) {
        item = *fg_p;

        if (IS_ITEM_GROWN_FLOWER(item)) {
            int i;
            s16 arg = item - FLOWER_PANSIES0;

            for (i = 0; i < 3; i++) {
                eEC_CLIP->effect_make_proc(eEC_EFFECT_HANABIRA, effect->position, effect->prio, 0, game, effect->item_name, arg, 1);
            }
        }
    }
}

static void eTumble_CallEffect(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    u32 season = Common_Get(time.season);
    s16 bush_happa_num;
    s16 bush_yuki_num;
    s16 mizutama_num;
    s16 yukidama_num;
    s16 bush_arg1;
    f32 sin = sin_s(angle);
    f32 cos = cos_s(angle);

    if (arg1 == 0) {
        bush_happa_num = 3;
        bush_yuki_num = 3;
    } else {
        bush_happa_num = 7;
        bush_yuki_num = 7;
    }

    mizutama_num = 10;
    yukidama_num = 10;

    switch (arg0) {
        case mCoBG_ATTRIBUTE_GRASS0:
        case mCoBG_ATTRIBUTE_GRASS1:
        case mCoBG_ATTRIBUTE_GRASS2:
        case mCoBG_ATTRIBUTE_GRASS3:
            if (season == mTM_SEASON_WINTER) {
                if (arg1 == 1) {
                    pos.x += sin * 7.0f;
                    pos.z += cos * 7.0f;
                    pos.y += 5.0f;

                    while (yukidama_num-- != 0) {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_YUKIDAMA, pos, prio, angle, game, item_name, arg0, yukidama_num);
                    }
                } else {
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_YUKIHANE, pos, prio, angle, game, item_name, arg0, arg1);
                }
            } else if (arg1 == 1) {
                if (mEnv_NowWeather() != mEnv_WEATHER_RAIN) {
                    s16 i;
                    s16 dust_angle = angle - DEG2SHORT_ANGLE2(74.0f) + 1;

                    pos.x += sin * 15.0f;
                    pos.z += cos * 15.0f;
                    pos.y += 10.0f;

                    for (i = 0; i < 5; i++) {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_TUMBLE_DUST, pos, prio, dust_angle, game, item_name, arg0, i);
                        dust_angle += DEG2SHORT_ANGLE2(37.0f);
                    }
                } else {
                    pos.y += 5.0f;
                    while (mizutama_num-- != 0) {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_MIZUTAMA, pos, prio, angle, game, item_name, arg0, mizutama_num);
                    }
                }
            }

            break;

        case mCoBG_ATTRIBUTE_FLOOR:
            break;
        
        case mCoBG_ATTRIBUTE_BUSH:
            pos.x += sin * 15.0f;
            pos.z += cos * 15.0f;
            
            if (arg1 == 0) {
                bush_arg1 = 1;
            } else {
                bush_arg1 = 2;
            }

            while (bush_happa_num-- != 0) {
                eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_HAPPA, pos, prio, angle, game, item_name, arg0, bush_arg1);
            }

            if (season == mTM_SEASON_WINTER) {
                while (bush_yuki_num-- != 0) {
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_YUKI, pos, prio, angle, game, item_name, arg0, 0);
                }
            }

            break;

        case mCoBG_ATTRIBUTE_SAND:
            if (arg1 == 1) {
                int n = 5;
                s16 sand_angle = angle - DEG2SHORT_ANGLE2(74.0f) + 1;

                pos.y += 10.0f;
                while (n-- != 0) {
                    xyz_t sand_pos = pos;

                    sand_pos.x += sin_s(sand_angle) * 20.0f;
                    sand_pos.z += cos_s(sand_angle) * 20.0f;
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_SANDSPLASH, sand_pos, prio, sand_angle, game, item_name, 1, 0);
                    sand_angle += DEG2SHORT_ANGLE2(37.0f);
                }
            }

            break;

        case mCoBG_ATTRIBUTE_WAVE:
            pos.y += 5.0f;
            while (mizutama_num-- != 0) {
                eEC_CLIP->effect_make_proc(eEC_EFFECT_MIZUTAMA, pos, prio, angle, game, item_name, arg0, mizutama_num);
            }
            break;

        default:
            if (arg1 == 1) {
                if (mEnv_NowWeather() != mEnv_WEATHER_RAIN) {
                    s16 dust_angle = angle - DEG2SHORT_ANGLE2(74.0f) + 1;
                    s16 i;

                    pos.x += sin * 15.0f;
                    pos.z += cos * 15.0f;
                    pos.y += 10.0f;

                    for (i = 0; i < 5; i++) {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_TUMBLE_DUST, pos, prio, dust_angle, game, item_name, arg0, i);
                        dust_angle += DEG2SHORT_ANGLE2(37.0f);
                    }
                } else {
                    pos.y += 5.0f;
                    while (mizutama_num-- != 0) {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_MIZUTAMA, pos, prio, angle, game, item_name, arg0, mizutama_num);
                    }
                }
            }

            break;
    }
}

static void eTumble_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    if (eEC_CLIP != NULL) {
        eTumble_CallEffect(pos, prio, angle, game, item_name, arg0, arg1);
    }

    eEC_CLIP->make_effect_proc(eEC_EFFECT_TUMBLE, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eTumble_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    eTumble_Hanabira_Make(effect, game);
    effect->timer = 0;
}

static void eTumble_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eTumble_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
