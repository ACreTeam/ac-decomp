/**
 * @file ac_ins_hotaru.c
 * @brief Implements firefly (hotaru) behavior.
 * 
 * Handles firefly actors which appear near water at night. They emit light,
 * float around in patterns, and escape when disturbed. The fireflies' behavior
 * includes smooth animation transitions and realistic light effects.
 */

#include "ac_ins_hotaru.h"

#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"

// Actor-specific work variables
#define aIHT_TARGET_ANGLE(ins) ((ins)->s32_work0)
#define aIHT_FLOAT_ANGLE(ins) ((ins)->s32_work2)
#define aIHT_WALL_HIT(ins) ((ins)->s32_work3)

#define aIHT_TARGET_X(ins) ((ins)->f32_work0)
#define aIHT_TARGET_Z(ins) ((ins)->f32_work1) 
#define aIHT_CENTER_X(ins) ((ins)->f32_work2)
#define aIHT_CENTER_Z(ins) ((ins)->f32_work3)

enum {
    aIHT_ACT_AVOID,
    aIHT_ACT_LET_ESCAPE,
    aIHT_ACT_FLY,

    aIHT_ACT_NUM
};

static void aIHT_actor_move(ACTOR* actorx, GAME* game);
static void aIHT_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game);

/**
 * Initializes the firefly actor.
 * Handles spawn conditions near water and initial positioning.
 * 
 * @param actorx Actor to initialize
 * @param game Current game context 
 */
extern void aIHT_actor_init(ACTOR* actorx, GAME* game) {
    // Birth check positions relative to spawn point
    static xyz_t hotaru_birth_check_data[] = {
        // clang-format off
        {                      0.0f, 0.0f,                      0.0f },
        {      mFI_UT_WORLDSIZE_X_F, 0.0f,                      0.0f },
        {     -mFI_UT_WORLDSIZE_X_F, 0.0f,                      0.0f },
        {                      0.0f, 0.0f,      mFI_UT_WORLDSIZE_Z_F },
        {                      0.0f, 0.0f,     -mFI_UT_WORLDSIZE_Z_F },
        {  2 * mFI_UT_WORLDSIZE_X_F, 0.0f,                      0.0f },
        { 2 * -mFI_UT_WORLDSIZE_X_F, 0.0f,                      0.0f },
        {                      0.0f, 0.0f,  2 * mFI_UT_WORLDSIZE_Z_F },
        {                      0.0f, 0.0f, 2 * -mFI_UT_WORLDSIZE_Z_F },
        // clang-format on
    };

    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    xyz_t pos = { 0.0f, 0.0f, 0.0f };
    int spawn;

    insect->bg_type = aINS_BG_CHECK_TYPE_REG_NO_ATTR;
    actorx->mv_proc = aIHT_actor_move;
    insect->item = ITM_INSECT27;

    if (actorx->actor_specific == aINS_INIT_NORMAL) {
        if (Common_Get(weather) == mEnv_WEATHER_RAIN) {
            // Don't let fireflies exist in the rain
            CLIP(insect_clip)->dt_proc(actorx, game);
        } else {
            u32 attr;
            int i;
            xyz_t birth_pos;

            xyz_t_move(&birth_pos, &actorx->world.position);
            for (i = 0, spawn = FALSE; i < ARRAY_COUNT(hotaru_birth_check_data); i++) {
                xyz_t_move(&pos, &birth_pos);
                pos.x += hotaru_birth_check_data[i].x;
                pos.z += hotaru_birth_check_data[i].z;
                attr = mCoBG_Wpos2Attribute(pos, NULL);
                
                if (!spawn && mCoBG_CheckWaterAttribute_OutOfSea(attr) == TRUE) {
                    spawn = TRUE;
                } else if (mCoBG_ExistHeightGap_KeepAndNow(pos) != TRUE) {
                    xyz_t_move(&actorx->world.position, &pos);
                }
            }

            if (spawn && (pos.x || pos.z)) {
                actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos(actorx->world.position, -70.0f);
                actorx->home.position.y = actorx->world.position.y;
                aIHT_setupAction(insect, aIHT_ACT_FLY, game);
                aIHT_FLOAT_ANGLE(insect) = RANDOM_F(DEG2SHORT_ANGLE2(360.0f));
                actorx->world.position.x += RANDOM_F(mFI_UT_WORLDSIZE_X_F) - mFI_UT_WORLDSIZE_HALF_X_F;
                actorx->world.position.z += RANDOM_F(mFI_UT_WORLDSIZE_Z_F) - mFI_UT_WORLDSIZE_HALF_Z_F;
                aIHT_TARGET_X(insect) = actorx->world.position.x;
                aIHT_TARGET_Z(insect) = actorx->world.position.z;
                insect->speed_step = 0.0f;
                insect->target_speed = 10.0f + RANDOM_F(15.0f);
                insect->continue_timer = RANDOM_F(5.0f);
                
                // Get block center position
                mFI_BkNum2WposXZ(&aIHT_CENTER_X(insect), &aIHT_CENTER_Z(insect), actorx->block_x, actorx->block_z);
                aIHT_CENTER_X(insect) += mFI_BK_WORLDSIZE_HALF_X_F;
                aIHT_CENTER_Z(insect) += mFI_BK_WORLDSIZE_HALF_Z_F;
            } else {
                CLIP(insect_clip)->dt_proc(actorx, game);
            }
        }
    } else {
        // aINS_INIT_RELEASE
        insect->_1E0 = 0.0f;
        insect->_1E4 = 0.0f;
        insect->alpha0 = 255;
        insect->alpha1 = 255;
        insect->alpha2 = 0;
        aIHT_setupAction(insect, aIHT_ACT_LET_ESCAPE, game);
    }
}

/**
 * Handles the firefly's animation cycles, including light intensity changes.
 * Updates alpha values for smooth transitions.
 * 
 * @param insect Pointer to the insect actor
 */
static void aIHT_anime_proc(aINS_INSECT_ACTOR* insect) {
    // Animation sequence data for light pulsing
    static f32 aIHT_anim_data[] = {
        // clang-format off
        0.0f,
        1.0f,
        2.0f,
        3.0f,
        2.0f,
        1.0f,
        // clang-format on
    };

    if (insect->timer > 0) {
        insect->timer--;
        
        insect->alpha0 += 25;
        if (insect->alpha0 > 255) {
            insect->alpha0 = 255;
        }

        insect->alpha1 -= 25;
        if (insect->alpha1 < 0) {
            insect->alpha1 = 0;
        }
    } else {
        insect->timer = 10;
        insect->_1E4 = aIHT_anim_data[insect->continue_timer];
        insect->alpha0 = 0;
        insect->alpha1 = 255;
        insect->continue_timer++;
        if (insect->continue_timer > 5) {
            insect->continue_timer = 0;
        }
        insect->_1E0 = aIHT_anim_data[insect->continue_timer];
    }
}

/**
 * Checks and handles firefly collision with background elements.
 * Adjusts position if hitting walls.
 * 
 * @param actorx Actor to check collisions for
 */
static void aIHT_BGcheck(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (actorx->bg_collision_check.result.hit_wall & mCoBG_HIT_WALL_FRONT) {
        if (aIHT_WALL_HIT(insect) == FALSE) {
            u16 angle = actorx->world.angle.y;
            f32 dx = aIHT_CENTER_X(insect) - actorx->world.position.x;
            f32 dz = aIHT_CENTER_Z(insect) - actorx->world.position.z;

            if (angle > DEG2SHORT_ANGLE2(45.0f) && angle <= DEG2SHORT_ANGLE2(135.0f)) {
                if (dx >= -200.0f) {
                    aIHT_TARGET_X(insect) -= mFI_UT_WORLDSIZE_X_F;
                }
            } else if (angle > DEG2SHORT_ANGLE2(135.0f) && angle <= DEG2SHORT_ANGLE2(225.0f)) {
                if (dz >= -200.0f) {
                    aIHT_TARGET_Z(insect) -= mFI_UT_WORLDSIZE_Z_F;
                }
            } else if (angle > DEG2SHORT_ANGLE2(225.0f) && angle <= DEG2SHORT_ANGLE2(315.0f)) {
                if (dx <= 200.0f) {
                    aIHT_TARGET_X(insect) += mFI_UT_WORLDSIZE_X_F;
                }
            } else {
                if (dz <= 200.0f) {
                    aIHT_TARGET_Z(insect) += mFI_UT_WORLDSIZE_Z_F;
                }
            }
            aIHT_WALL_HIT(insect) = TRUE;
        }
    } else {
        aIHT_WALL_HIT(insect) = FALSE;
    }
}

/**
 * Creates floating motion by manipulating Y position with sine waves.
 * 
 * @param insect Pointer to the insect actor
 * @param fuwafuwa_flag If TRUE, uses faster/higher amplitude motion
 */
static void aIHT_fuwafuwa(aINS_INSECT_ACTOR* insect, int fuwafuwa_flag) {
    f32 pos_y;
    f32 sin;
    f32 ofs_y;

    if (fuwafuwa_flag == FALSE) {
        aIHT_FLOAT_ANGLE(insect) += (int)((RANDOM_F((f32)0x600) + (f32)0x200) * 0.5f);
    } else {
        aIHT_FLOAT_ANGLE(insect) += 0x400;
        insect->tools_actor.actor_class.speed = 1.5f;
    }

    sin = sin_s(aIHT_FLOAT_ANGLE(insect));
    pos_y = insect->tools_actor.actor_class.world.position.y;
    ofs_y = sin * 10.0f;
    insect->tools_actor.actor_class.position_speed.y = (insect->tools_actor.actor_class.home.position.y + ofs_y) - pos_y;
}

/**
 * Handles the firefly's light effect processing.
 * Controls light radius, color and transitions.
 * 
 * @param insect Pointer to the insect actor
 * @param game Current game context
 */
static void aIHT_light_proc(aINS_INSECT_ACTOR* insect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (insect->tools_actor.init_matrix == TRUE || insect->insect_flags.bit_1 == TRUE) {
        s16 radius;

        if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_PUTAWAY_NET) {
            if ((play->game_frame & 1) == 0 && (int)insect->_1E0 > 0) {
                insect->_1E0 -= 1.0f;
            }
        } else {
            insect->light_step = 0;
        }

        switch (insect->light_flag) {
            case 0:
                radius = fabsf(sin_s(insect->light_counter)) * 15.0f + 25.0f;

                // clang-format off
                Light_point_ct(
                    &insect->point_light,
                    insect->tools_actor.actor_class.world.position.x,
                    insect->tools_actor.actor_class.world.position.y - 35.0f,
                    insect->tools_actor.actor_class.world.position.z,
                    120, 255, 180,
                    radius
                );
                // clang-format on
                insect->light_list = Global_light_list_new(game, &play->global_light, &insect->point_light);
                insect->light_flag++;
                break;
            case 1:
                insect->timer = 0;
                insect->continue_timer = 0;
                insect->light_flag++;
                break;
            case 2:
                radius = fabsf(sin_s(insect->light_counter)) * 15.0f + 25.0f;

                // clang-format off
                Light_point_ct(
                    &insect->point_light,
                    insect->tools_actor.actor_class.world.position.x,
                    insect->tools_actor.actor_class.world.position.y - 35.0f,
                    insect->tools_actor.actor_class.world.position.z,
                    120, 255, 180,
                    radius
                );
                // clang-format on
                break;
        }

        add_calc_short_angle2(&insect->light_counter, (s16)(insect->_1E0 * 0x1555), 1.0f - sqrtf(0.7f), 2500, 0);
    }
}

/**
 * Avoidance behavior when the firefly is disturbed.
 * 
 * @param actorx Actor performing avoidance
 * @param game Current game context
 */
static void aIHT_avoid(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    aIHT_fuwafuwa(insect, TRUE);
    actorx->gravity += 0.75f;
    actorx->position_speed.y += actorx->gravity;
}

/**
 * Normal flying behavior for the firefly.
 * Handles movement patterns and maintains position within valid area.
 * 
 * @param actorx Actor to update
 * @param game Current game context
 */
static void aIHT_fly(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    aIHT_BGcheck(actorx);
    actorx->scale.x = 0.01f;
    actorx->scale.y = 0.01f;
    actorx->scale.z = 0.01f;
    insect->target_speed = 1.5f;
    insect->speed_step = 0.1f;
    aIHT_fuwafuwa(insect, FALSE);

    if ((fabsf(aIHT_TARGET_X(insect) - actorx->world.position.x) > 30.0f) || (fabsf(aIHT_TARGET_Z(insect) - actorx->world.position.z) > 30.0f)) {
        xyz_t pos;

        pos.x = aIHT_TARGET_X(insect);
        pos.y = actorx->world.position.y;
        pos.z = aIHT_TARGET_Z(insect);

        aIHT_TARGET_ANGLE(insect) = search_position_angleY(&actorx->world.position, &pos) + (s16)(DEG2SHORT_ANGLE2(67.5f) - (int)RANDOM_F(DEG2SHORT_ANGLE2(135.0f)));

        if (insect->patience > 90.0f) {
            // The firefly is scared so fly away from the player if not too far from
            // center of the block. Otherwise, fly towards center of the block.
            f32 dx = aIHT_CENTER_X(insect) - actorx->world.position.x;
            f32 dz = aIHT_CENTER_Z(insect) - actorx->world.position.z;

            if (ABS(dx) > 240.0f || ABS(dz) > 240.0f) {
                aIHT_TARGET_ANGLE(insect) = atans_table(dz, dx);
            } else {
                aIHT_TARGET_ANGLE(insect) = actorx->player_angle_y + DEG2SHORT_ANGLE2(180.0f);
            }

            insect->flag = TRUE;
        } else if (insect->flag == TRUE && insect->patience < 10.0f) {
            // If the firefly is not disturbed, fly towards
            // the center of the current unit.
            xyz_t center_pos;

            if (mFI_Wpos2UtCenterWpos(&center_pos, actorx->world.position) == TRUE) {
                aIHT_TARGET_X(insect) = center_pos.x;
                aIHT_TARGET_Z(insect) = center_pos.z;
            }

            insect->flag = FALSE;
        }
    }

    add_calc_short_angle2(&actorx->world.angle.y, aIHT_TARGET_ANGLE(insect), 1.0f - sqrtf(0.9f), 250, 0);
}

/**
 * Common initialization for avoidance behaviors.
 * 
 * @param insect Pointer to the insect actor
 * @param game Current game context
 */
static void aIHT_avoid_init_sub(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->life_time = 0;
    insect->alpha_time = 80;
    insect->tools_actor.actor_class.shape_info.rotation.x = 0;

    if (insect->insect_flags.bit_1 == FALSE) {
        ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

        if (playerx != NULL) {
            insect->tools_actor.actor_class.world.angle.y = playerx->shape_info.rotation.y + (s16)RANDOM_CENTER_F(DEG2SHORT_ANGLE2(120.0f));
        }
    }

    insect->insect_flags.bit_1 = TRUE;
    aIHT_FLOAT_ANGLE(insect) = 0;
    aIHT_TARGET_ANGLE(insect) = 0;
    insect->tools_actor.actor_class.shape_info.draw_shadow = TRUE;
}

/**
 * Initializes the avoid state.
 * 
 * @param insect Pointer to the insect actor
 * @param game Current game context
 */
static void aIHT_avoid_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    aIHT_avoid_init_sub(insect, game);
    insect->_1E0 = 0.0f;
    insect->_1E4 = insect->_1E0;
    insect->alpha0 = 255;
    insect->alpha1 = 255;
    insect->alpha2 = 0;
}

/**
 * Initializes the escape state.
 * 
 * @param insect Pointer to the insect actor
 * @param game Current game context
 */
static void aIHT_let_escape_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    aIHT_avoid_init_sub(insect, game);
    insect->insect_flags.bit_2 = TRUE;
}

/**
 * Initializes the normal flying state.
 * 
 * @param insect Pointer to the insect actor
 * @param game Current game context
 */
static void aIHT_fly_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->flag = FALSE;
    insect->tools_actor.actor_class.world.angle.x = 0;
}

typedef void (*aIHT_INIT_PROC)(aINS_INSECT_ACTOR* insect, GAME* game);

/**
 * Sets up a new action state for the firefly.
 * 
 * @param insect Pointer to the insect actor
 * @param action New action to perform
 * @param game Current game context
 */
static void aIHT_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game) {
    static aIHT_INIT_PROC init_proc[] = {
        aIHT_avoid_init,
        aIHT_let_escape_init,
        aIHT_fly_init,
    };

    static aINS_ACTION_PROC act_proc[] = {
        aIHT_avoid,
        aIHT_avoid,
        aIHT_fly,
    };

    insect->action = action;
    insect->action_proc = act_proc[action];
    (*init_proc[action])(insect, game);
}

/**
 * Main movement update function for firefly actors.
 * Handles state transitions and updates light effects.
 * 
 * @param actorx Actor to update
 * @param game Current game context
 */
static void aIHT_actor_move(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    aIHT_light_proc(insect, game);
    if (mPlib_get_player_actor_main_index(game) != mPlayer_INDEX_PUTAWAY_NET) {
        aIHT_anime_proc(insect);
    }

    if ((ACTOR*)mPlib_Get_item_net_catch_label() == actorx) {
        aIHT_setupAction(insect, aIHT_ACT_LET_ESCAPE, game);
    } else if (insect->insect_flags.bit_3 == TRUE && insect->insect_flags.bit_2 == FALSE) {
        aIHT_setupAction(insect, aIHT_ACT_LET_ESCAPE, game);
    } else {
        insect->action_proc(actorx, game);
    }
}
