#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_player_lib.h"

static void eDig_Scoop_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eDig_Scoop_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eDig_Scoop_mv(eEC_Effect_c* effect, GAME* game);
static void eDig_Scoop_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_dig_scoop = {
    // clang-format off
    &eDig_Scoop_init,
    &eDig_Scoop_ct,
    &eDig_Scoop_mv,
    &eDig_Scoop_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eDig_Scoop_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    ACTOR* player_actorx = (ACTOR*)GET_PLAYER_ACTOR_GAME(game);
    PLAYER_ACTOR* player;
    int i;
    s16 star_ef_angle;
    s16 sand_angle;
    xyz_t sand_pos;
    s16 dust_angle;

    pos.x += player_actorx->world.position.x + 30.0f * sin_s(angle);
    pos.z += player_actorx->world.position.z + 30.0f * cos_s(angle);
    pos.x /= 2.0f;
    pos.z /= 2.0f;

    if (eEC_CLIP != NULL) {
        if (arg1 == 1) {
            player = GET_PLAYER_ACTOR_GAME(game);
            star_ef_angle = angle + DEG2SHORT_ANGLE2(22.5f);

            switch (arg0) {
                case mCoBG_ATTRIBUTE_BUSH: {
                    int i = 4;

                    do {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_HAPPA, player->actor_class.world.position, prio,
                                                   angle, game, item_name, arg0, 1);
                    } while (i--);

                    if (Common_Get(time).season == mTM_SEASON_WINTER) {
                        int j = 4;

                        do {
                            eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_YUKI, player->actor_class.world.position, prio,
                                                       angle, game, item_name, arg0, 0);
                        } while (j--);
                    }
                    break;
                }

                case mCoBG_ATTRIBUTE_GRASS0:
                case mCoBG_ATTRIBUTE_GRASS1:
                case mCoBG_ATTRIBUTE_GRASS2:
                case mCoBG_ATTRIBUTE_SOIL0:
                case mCoBG_ATTRIBUTE_SOIL1:
                case mCoBG_ATTRIBUTE_SOIL2: {
                    f32 ground_dist = mCoBG_GetBgY_AngleS_FromWpos(NULL, pos, 0.0f);

                    if (ground_dist < (pos.y + 10.0f)) {
                        break;
                    }
                }
                /* Fallthrough */
                default: {
                    s16 i;

                    pos.y += 11.0f;
                    for (i = 0; i < 2; i++) {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_IMPACT_STAR, pos, prio, star_ef_angle, game, item_name,
                                                   arg0, (s16)i);
                    }
                    break;
                }
            }
        } else if (arg1 == 0) {
            pos.y += 10.0f;
            for (i = 0; i < 6; i++) {
                eEC_CLIP->effect_make_proc(eEC_EFFECT_DIG_MUD, pos, prio, angle, game, item_name, arg0, i);
            }
        } else if (arg1 == 3) {
            pos.y += 10.0f;
            for (i = 3; i < 6; i++) {
                eEC_CLIP->effect_make_proc(eEC_EFFECT_DIG_MUD, pos, prio, angle, game, item_name, arg0, i);
            }
        } else {
            pos.y += 5.0f;

            if (Common_Get(time).season == mTM_SEASON_WINTER) {
                if (arg0 == mCoBG_ATTRIBUTE_GRASS0 || arg0 == mCoBG_ATTRIBUTE_GRASS1 ||
                    arg0 == mCoBG_ATTRIBUTE_GRASS2) {
                    for (i = 2; i < 6; i++) {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_YUKIDAMA, pos, prio, angle, game, item_name, arg0,
                                                   (0x2000 | 0x1000) | i);
                    }
                } else if (arg0 == mCoBG_ATTRIBUTE_SAND) {
                    sand_angle = angle - DEG2SHORT_ANGLE2(45.0f);
                    for (i = 0; i < 3; i++) {
                        xyz_t sand_pos = pos;

                        sand_pos.x += 15.0f * sin_s(sand_angle);
                        sand_pos.z += 15.0f * cos_s(sand_angle);
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_SANDSPLASH, sand_pos, prio, sand_angle, game, item_name,
                                                   3, 0);
                        sand_angle += DEG2SHORT_ANGLE2(45.0f);
                    }
                } else if (mEnv_NowWeather() != mEnv_WEATHER_RAIN && arg0 != mCoBG_ATTRIBUTE_WAVE) {
                    dust_angle = angle - DEG2SHORT_ANGLE2(45.0f);
                    for (i = 0; i < 3; i++) {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_TUMBLE_DUST, pos, prio, dust_angle, game, item_name, arg0,
                                                   i);
                        dust_angle += DEG2SHORT_ANGLE2(45.0f);
                    }
                } else {
                    for (i = 2; i < 6; i++) {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_MIZUTAMA, pos, prio, angle, game, item_name, arg0,
                                                   (0x2000 | 0x1000) | i);
                    }

                    if (arg0 == mCoBG_ATTRIBUTE_WAVE) {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_AMI_MIZU, pos, prio, angle, game, item_name, 1, 0);
                    }
                }
            } else {
                if (arg0 == mCoBG_ATTRIBUTE_SAND) {
                    sand_angle = angle - DEG2SHORT_ANGLE2(45.0f);

                    for (i = 0; i < 3; i++) {
                        xyz_t sand_pos = pos;

                        sand_pos.x += 15.0f * sin_s(sand_angle);
                        sand_pos.z += 15.0f * cos_s(sand_angle);
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_SANDSPLASH, sand_pos, prio, sand_angle, game, item_name,
                                                   3, 0);
                        sand_angle += DEG2SHORT_ANGLE2(45.0f);
                    }
                } else if (mEnv_NowWeather() == mEnv_WEATHER_RAIN || arg0 == mCoBG_ATTRIBUTE_WAVE) {
                    for (i = 2; i < 6; i++) {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_MIZUTAMA, pos, prio, angle, game, item_name, arg0,
                                                   (0x2000 | 0x1000) | i);
                    }

                    if (arg0 == mCoBG_ATTRIBUTE_WAVE) {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_AMI_MIZU, pos, prio, angle, game, item_name, 1, 0);
                    }
                } else {
                    dust_angle = angle - DEG2SHORT_ANGLE2(45.0f);
                    for (i = 0; i < 3; i++) {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_TUMBLE_DUST, pos, prio, dust_angle, game, item_name, arg0,
                                                   i);
                        dust_angle += DEG2SHORT_ANGLE2(45.0f);
                    }
                }
            }
        }
    }

    eEC_CLIP->make_effect_proc(eEC_EFFECT_DIG_SCOOP, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eDig_Scoop_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 0;
}

static void eDig_Scoop_mv(eEC_Effect_c* effect, GAME* game) {
    // empty
}

static void eDig_Scoop_dw(eEC_Effect_c* effect, GAME* game) {
    // empty
}
