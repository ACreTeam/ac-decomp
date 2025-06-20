#include "ac_airplane.h"

#include "m_collision_bg.h"
#include "m_player.h"
#include "m_player_lib.h"
#include "sys_matrix.h"
#include "sys_math3d.h"
#include "sys_math.h"
#include "libc64/qrand.h"
#include "m_controller.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_actor_shadow.h"
#include "m_rcp.h"

static void Airplane_Actor_ct(ACTOR* actor, GAME* game);
static void Airplane_Actor_dt(ACTOR* actor, GAME* game);
static void Airplane_Actor_move(ACTOR* actor, GAME* game);
static void Airplane_Actor_draw(ACTOR* actor, GAME* game);

/* TODO: ct, dt, & draw go in this TU, while all others go in a separate TU. Probably something like
 * ac_airplane_move.c_inc */

ACTOR_PROFILE Airplane_Profile = {
    mAc_PROFILE_AIRPLANE,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    ETC_AIRPLANE,
    ACTOR_OBJ_BANK_AIRPLANE,
    sizeof(AIRPLANE_ACTOR),
    &Airplane_Actor_ct,
    &Airplane_Actor_dt,
    &Airplane_Actor_move,
    &Airplane_Actor_draw,
    NULL,
};

static void Airplane_Actor_ct(ACTOR* actor, GAME* game) {
    AIRPLANE_ACTOR* airplane = (AIRPLANE_ACTOR*)actor;

    Shape_Info_init(actor, 0.0f, &mAc_ActorShadowEllipse, 6.5f, 6.5f);
    airplane->status = 5;

    airplane->speed = 6.2f;
    airplane->y_speed = 0.0f;
    airplane->actor_class.speed = airplane->speed;

    airplane->rotY = RAD2DEG(SHORTANGLE2RAD((f32)actor->world.angle.y));
    airplane->rotY_goal = airplane->rotY;
    airplane->rotY_min = airplane->rotY;
    airplane->rotZ = 0.0f;
    airplane->rotX = 0.0f;

    airplane->ground_timer = 0;
    airplane->wind_frame = 0;
    airplane->wind_change_frame = 0;
    airplane->wind = NULL;

    actor->world.position.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, actor->world.position, -5.5f);
}

static void Airplane_Actor_dt(ACTOR* actor, GAME* game) {
}

extern Gfx glider_model[];

static void Airplane_Actor_draw(ACTOR* actor, GAME* game) {
    AIRPLANE_ACTOR* airplane = (AIRPLANE_ACTOR*)actor;

    if (airplane->status != aAp_STATUS_PLAYER_CATCH && airplane->status != aAp_STATUS_START_FLY_MOVE) {
        GRAPH* g = game->graph;

        _texture_z_light_fog_prim(g);
        Matrix_RotateX(RAD2SHORTANGLE(DEG2RAD(airplane->rotX)), MTX_MULT);
        Matrix_RotateZ(RAD2SHORTANGLE(DEG2RAD(airplane->rotZ)), MTX_MULT);
        Matrix_scale(50.0f, 50.0f, 50.0f, MTX_MULT);

        OPEN_DISP(g);
        gSPMatrix(NOW_POLY_OPA_DISP++, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NOW_POLY_OPA_DISP++, glider_model);
        CLOSE_DISP(g);
    }
}

static void aAp_RubberMove(f32* now, f32 target, f32 step) {
    *now += step * (target - *now);
}

static void aAp_FallByWall(ACTOR* actor) {
    AIRPLANE_ACTOR* airplane = (AIRPLANE_ACTOR*)actor;
    if (actor->bg_collision_check.result.hit_wall == 0) {
        return;
    }

    airplane->status = aAp_STATUS_FALL_FLY_MOVE;
}

static void aAp_GroundFriction(ACTOR* actor, GAME* game) {
    AIRPLANE_ACTOR* airplane = (AIRPLANE_ACTOR*)actor;
    if (actor->bg_collision_check.result.on_ground) {
        /* slow down speed since we're on the ground */
        aAp_RubberMove(&airplane->speed, 0.0f, 0.6f);

        if (airplane->speed < 1.0f) {
            airplane->speed = 0.0f;
            airplane->status = aAp_STATUS_STOP_FLY_MOVE;

            if (airplane->ground_timer >= 5) {
                airplane->ground_timer = 0;

                (*Common_Get(clip.effect_clip)->effect_make_proc)(eEC_EFFECT_DUST, actor->world.position, 1,
                                                                  actor->world.angle.y, game, actor->npc_id, 0, 8);
            }

            airplane->ground_timer++;
        }
    }
}

static void aAp_FreeFlyMove(ACTOR* actor, GAME* game) {
    AIRPLANE_ACTOR* airplane = (AIRPLANE_ACTOR*)actor;

    aAp_RubberMove(&airplane->speed, 3.0f, 0.01f);
    aAp_RubberMove(&airplane->rotX, 19.0f, 0.045f);
    aAp_RubberMove(&airplane->rotZ, 0.0f, 0.05f);
    aAp_GroundFriction(actor, game);
    aAp_FallByWall(actor);
}

static void aAp_SomerFlyMove(ACTOR* actor, GAME* game) {
    AIRPLANE_ACTOR* airplane = (AIRPLANE_ACTOR*)actor;
    switch (airplane->tilt_status) {
        case aAp_TILT_DOWN: {
            aAp_RubberMove(&airplane->rotX, -89.0f, 0.2f);
            aAp_RubberMove(&airplane->speed, 9.0f, 0.1f);

            if (airplane->rotX < -87.0f) {
                airplane->tilt_status = aAp_TILT_UP;
                airplane->rotX = 60.0f;
            }

            break;
        }

        case aAp_TILT_UP: {
            aAp_RubberMove(&airplane->rotX, 0.0f, 0.04f);
            aAp_RubberMove(&airplane->speed, 10.0f, 0.1f);

            if (ABS(airplane->rotX) < 3.0f) {
                airplane->status = aAp_STATUS_FREE_FLY_MOVE;
                airplane->tilt_status = aAp_TILT_DOWN;
            }

            aAp_GroundFriction(actor, game);
            break;
        }
    }

    aAp_FallByWall(actor);
}

static int aAp_SelectFly(AIRPLANE_ACTOR* actor, int stick_y) {
    int mode = (int)(fqrand() * 7.0f) & 1;
    if (stick_y > 67) {
        if (mode != 0) {
            actor->status = aAp_STATUS_FALL_FLY_MOVE2;
        } else {
            actor->status = aAp_STATUS_SOMER_FLY_MOVE;
            actor->tilt_status = aAp_TILT_DOWN;
        }
    } else {
        actor->status = aAp_STATUS_FREE_FLY_MOVE;
    }

    return TRUE;
}

static void aAp_StartFlyMove(ACTOR* actor, GAME* game) {
    static s16 goal_angle_random[8] = { 2366, 2002, -1092, -2366, 0, 4368, -4186, 4186 };
    static s16 goal_angle_random2[8] = { 12740, 8190, -9100, -8190, -10920, 10920, 9100, 0 };

    AIRPLANE_ACTOR* airplane = (AIRPLANE_ACTOR*)actor;
    int now_stick_y = getJoystick_Y();
    PLAYER_ACTOR* player = get_player_actor_withoutCheck((GAME_PLAY*)game);
    int goal = fqrand() * 8.0f;
    GAME_PLAY* play = (GAME_PLAY*)game;
    int last_stick_y = airplane->joystick_y;
    s16* goal_angle_random_tbl;

    if (now_stick_y - last_stick_y > 30) {
        f32 stick_y = ABS((f32)last_stick_y);
        int adjusted_y = ABS(last_stick_y);

        airplane->speed = ABS((f32)last_stick_y) * 0.0875f + 3.0f;
        aAp_SelectFly(airplane, adjusted_y);

        goal_angle_random_tbl = adjusted_y > 50 ? goal_angle_random2 : goal_angle_random;

        actor->world.position.y = player->actor_class.world.position.y + 25.0f;
        actor->world.position.x = player->actor_class.world.position.x;
        actor->world.position.z = player->actor_class.world.position.z;

        airplane->rotY = RAD2DEG(SHORTANGLE2RAD(player->actor_class.shape_info.rotation.y));
        airplane->rotY_goal = airplane->rotY + (RAD2DEG(SHORTANGLE2RAD(goal_angle_random_tbl[goal])));
        airplane->rotX = airplane->speed * RAD2DEG(-0.14959965f) + 30.0f;
        airplane->rotZ = 0.0f;
        airplane->y_speed = 0.0f;

        mPlib_request_main_wait_type3((GAME*)play);
    }
}

static void aAp_PlayerCatch(ACTOR* actor, GAME* game) {
}

static void aAp_StopFlyMove(ACTOR* actor, GAME* game) {
    AIRPLANE_ACTOR* airplane = (AIRPLANE_ACTOR*)actor;
    airplane->speed = 0.0f;

    if (actor->player_distance_xz <= 30.0f && chkTrigger(BUTTON_A)) {
        airplane->status = aAp_STATUS_PLAYER_CATCH; // player is now "holding" the airplane
    }
}

static void aAp_FallFlyMove(ACTOR* actor, GAME* game) {
    AIRPLANE_ACTOR* airplane = (AIRPLANE_ACTOR*)actor;
    aAp_RubberMove(&airplane->rotX, 60.0f, 0.04f);
    aAp_RubberMove(&airplane->speed, 5.0f, 0.02f);

    actor->world.position.y -= 0.15f;

    if (actor->bg_collision_check.result.on_ground) {
        Common_Get(clip.effect_clip)
            ->effect_make_proc(eEC_EFFECT_DUST, actor->world.position, 1, actor->world.angle.y, game, actor->npc_id, 0,
                               8);
        airplane->status = aAp_STATUS_STOP_FLY_MOVE;
    }
}

static void aAp_FallFlyMove2(ACTOR* actor, GAME* game) {
    AIRPLANE_ACTOR* airplane = (AIRPLANE_ACTOR*)actor;
    aAp_RubberMove(&airplane->rotX, 70.0f, 0.15f);
    aAp_RubberMove(&airplane->speed, 10.0f, 0.02f);

    actor->world.position.y -= 0.15f;

    if (actor->bg_collision_check.result.on_ground) {
        Common_Get(clip.effect_clip)
            ->effect_make_proc(eEC_EFFECT_DUST, actor->world.position, 1, actor->world.angle.y, game, actor->npc_id, 0,
                               8);
        airplane->status = aAp_STATUS_STOP_FLY_MOVE;
    }
}

static void aAp_LeanAirplane(AIRPLANE_ACTOR* airplane) {
    if (airplane->status == aAp_STATUS_FREE_FLY_MOVE) {
        aAp_RubberMove(&airplane->rotZ, 0.0f, 0.05f);
    } else if (airplane->rotY_min - airplane->rotY > 0.0f) {
        aAp_RubberMove(&airplane->rotZ, 50.0f, 0.05f);
    } else {
        aAp_RubberMove(&airplane->rotZ, -50.0f, 0.05f);
    }
}

static xyz_t wind1 = { 2.0f, 1.0f, 4.0f };
static xyz_t wind2 = { -3.0f, -4.0f, -7.0f };
static xyz_t wind3 = { 4.0f, -3.0f, 1.0f };
static xyz_t wind4 = { -1.0f, 3.0f, -4.0f };

static xyz_t* wind_table[4] = { &wind1, &wind2, &wind3, &wind4 };

static int wind_change_frame_table[10] = { 300, 20, 500, 1000, 100, 700, 20, 200, 80, 70 };

static void aAp_WindSystem(ACTOR* actor, GAME* game) {
    AIRPLANE_ACTOR* airplane = (AIRPLANE_ACTOR*)actor;
    xyz_t dir = { 0.0f, 1.0f, 0.0f };

    airplane->wind_frame++;
    if (airplane->wind_frame > airplane->wind_change_frame) {
        int table_rng = fqrand() * 4.0f;
        int change_frame_rng = fqrand() * 10.0f;

        airplane->wind_frame = 0;
        airplane->wind_change_frame = wind_change_frame_table[change_frame_rng];
        airplane->wind = wind_table[table_rng];
    }

    if (airplane->status != aAp_STATUS_STOP_FLY_MOVE && airplane->status != aAp_STATUS_START_FLY_MOVE &&
        airplane->status != aAp_STATUS_PLAYER_CATCH && airplane->wind != NULL) {
        sMath_RotateX(&dir, DEG2RAD(airplane->rotX));
        sMath_RotateZ(&dir, DEG2RAD(airplane->rotZ));
        sMath_RotateY(&dir, DEG2RAD(airplane->rotY));
    }
}

static void aAp_CommonHandle(ACTOR* actor, AIRPLANE_ACTOR* airplane, GAME* game) {
    aAp_LeanAirplane(airplane);

    actor->speed = airplane->speed * cosf_table(DEG2RAD(airplane->rotX));
    airplane->y_speed = airplane->speed * sinf_table(DEG2RAD(airplane->rotX));

    actor->world.position.y -= airplane->y_speed;
    actor->world.angle.y = RAD2SHORTANGLE(DEG2RAD(airplane->rotY));
    actor->shape_info.rotation.y = RAD2SHORTANGLE(DEG2RAD(airplane->rotY));

    Actor_position_moveF(actor);

    airplane->joystick_x = getJoystick_X();
    airplane->joystick_y = getJoystick_Y();

    switch (airplane->status) {
        case aAp_STATUS_START_FLY_MOVE:
        case aAp_STATUS_PLAYER_CATCH: {
            actor->shape_info.draw_shadow = FALSE;
            break;
        }

        case aAp_STATUS_FREE_FLY_MOVE:
        case aAp_STATUS_FALL_FLY_MOVE:
        case aAp_STATUS_FALL_FLY_MOVE2:
        case aAp_STATUS_SOMER_FLY_MOVE: {
            aAp_RubberMove(&airplane->rotY, airplane->rotY_goal, 0.07f);
            actor->shape_info.draw_shadow = TRUE;
            break;
        }

        default: {
            actor->shape_info.draw_shadow = TRUE;
            break;
        }
    }

    aAp_WindSystem(actor, game);
}

static void aAp_ZbuttonChangeStatus(AIRPLANE_ACTOR* actor, GAME* game) {
    if (chkButton(BUTTON_Z)) {
        if (actor->status == aAp_STATUS_PLAYER_CATCH) {
            mPlib_request_main_refuse_type1(game);
            actor->status = aAp_STATUS_START_FLY_MOVE;
        }
    } else if (actor->status == aAp_STATUS_START_FLY_MOVE) {
        mPlib_request_main_wait_type3(game);
        actor->status = aAp_STATUS_PLAYER_CATCH;
    }
}

static f32 aAp_GetBgCheckOffsetY(s16 status) {
    if (status == aAp_STATUS_FALL_FLY_MOVE || status == aAp_STATUS_STOP_FLY_MOVE) {
        return -5.5f;
    }

    return 0.0f;
}

typedef void (*AIRPLANE_ACTOR_MOVE_PROC)(ACTOR*, GAME*);
static void Airplane_Actor_move(ACTOR* actor, GAME* game) {
    static AIRPLANE_ACTOR_MOVE_PROC AirplaneMove[aAp_STATUS_NUM] = { &aAp_FreeFlyMove,  &aAp_FallFlyMove,
                                                                     &aAp_FallFlyMove2, &aAp_SomerFlyMove,
                                                                     &aAp_StartFlyMove, &aAp_StopFlyMove,
                                                                     &aAp_PlayerCatch };

    AIRPLANE_ACTOR* airplane = (AIRPLANE_ACTOR*)actor;
    f32 offset_y;

    airplane->rotY_min = airplane->rotY;
    (*AirplaneMove[airplane->status])(actor, game);
    aAp_ZbuttonChangeStatus(airplane, game);
    aAp_CommonHandle(actor, airplane, game);

    offset_y = aAp_GetBgCheckOffsetY(airplane->status);
    mCoBG_BgCheckControll(NULL, actor, 15.0f, offset_y, FALSE, FALSE, 0);
}
