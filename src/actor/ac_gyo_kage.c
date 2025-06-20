#include "ac_gyo_kage.h"

#include "ac_gyoei.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_rcp.h"

static void aGYO_KAGE_actor_ct(ACTOR* actorx, GAME* game);
static void aGYO_KAGE_actor_dt(ACTOR* actorx, GAME* game);
static void aGYO_KAGE_actor_move(ACTOR* actorx, GAME* game);
static void aGYO_KAGE_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Gyo_Kage_Profile = {
    mAc_PROFILE_GYO_KAGE,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(GYO_KAGE_ACTOR),
    &aGYO_KAGE_actor_ct,
    &aGYO_KAGE_actor_dt,
    &aGYO_KAGE_actor_move,
    &aGYO_KAGE_actor_draw,
    NULL,
};
// clang-format on

#include "../src/actor/ac_gyoei_data.c_inc"

f32 aGYO_KAGE_shadow_scale[aGYO_SIZE_NUM] = { 0.3f, 0.4f, 0.5f, 0.5f, 0.6f, 0.8f, 1.2f, 10.0f };

static s16 aGYO_KAGE_Get_flow_angle(ACTOR* actorx) {
    xyz_t flow;
    s16 angle;

    mCoBG_GetWaterFlow(&flow, actorx->bg_collision_check.result.unit_attribute);
    angle = atans_table(flow.z, flow.x);
    return angle;
}

static void aGYO_KAGE_effect_hamon(ACTOR* actorx, GAME* game, s16 arg) {
    xyz_t pos = actorx->world.position;
    f32 water_height = mCoBG_GetWaterHeight_File(actorx->world.position, __FILE__, 139);
    s16 angle = aGYO_KAGE_Get_flow_angle(actorx);

    pos.y = water_height;
    eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, pos, 1, angle, game, EMPTY_NO, arg, 0);
}

static u8 aGYO_KAGE_Wall_Check(ACTOR* actorx) {
    GYO_KAGE_ACTOR* gyo_kage = (GYO_KAGE_ACTOR*)actorx;
    u8 res = FALSE;

    if ((actorx->bg_collision_check.result.hit_wall & mCoBG_HIT_WALL_FRONT) != 0) {
        int hit_count = actorx->bg_collision_check.result.hit_wall_count;

        if (hit_count != 0) {
            int i;

            for (i = 0; i < hit_count; i++) {
                if (actorx->bg_collision_check.wall_info[i].type == mCoBG_WALL_TYPE0) {
                    s16 wall_angle = actorx->bg_collision_check.wall_info[i].angleY;
                    s16 goal_angle = wall_angle - (DEG2SHORT_ANGLE2(180.0f) + actorx->world.angle.y);

                    if (goal_angle < 0) {
                        actorx->world.angle.y += DEG2SHORT_ANGLE2(90.0f);
                    } else {
                        actorx->world.angle.y -= DEG2SHORT_ANGLE2(90.0f);
                    }

                    actorx->shape_info.rotation.y = actorx->world.angle.y;
                    gyo_kage->wall_flag = TRUE;
                    res = TRUE;
                    break;
                }
            }
        }
    }

    return res;
}

static void aGYO_KAGE_actor_ct(ACTOR* actorx, GAME* game) {
    GYO_KAGE_ACTOR* gyo_kage = (GYO_KAGE_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    u32 atr;
    f32 scale;

    actorx->drawn = TRUE;
    actorx->shape_info.draw_shadow = FALSE;
    gyo_kage->data_id = -1;
    gyo_kage->gyoei_actor = NULL;
    
    scale = aGYO_KAGE_shadow_scale[actorx->actor_specific] * 0.02f;
    actorx->scale.x = scale;
    actorx->scale.y = scale;
    actorx->scale.z = scale;
    actorx->speed = 2.0f;
    actorx->shape_info.rotation.y = actorx->world.angle.y;
    gyo_kage->delete_timer = 100;
    gyo_kage->draw_frame = 38;
    gyo_kage->exist_flag = TRUE;
    gyo_kage->wall_flag = FALSE;
    
    atr = mCoBG_Wpos2BgAttribute_Original(actorx->world.position);
    if (mCoBG_CheckWaterAttribute(atr)) {
        actorx->world.position.y = mCoBG_GetWaterHeight_File(actorx->world.position, __FILE__, 244) - 8.0f;
    }

    gyo_kage->gyoei_actor = Actor_info_name_search(&play->actor_info, mAc_PROFILE_GYOEI, ACTOR_PART_CONTROL);
}

static void aGYO_KAGE_actor_dt(ACTOR* actorx, GAME* game) {
    GYO_KAGE_ACTOR* gyo_kage = (GYO_KAGE_ACTOR*)actorx;

    gyo_kage->exist_flag = FALSE;
    ClObjPipe_dt(game, &gyo_kage->col_pipe);
}

static void aGYO_KAGE_BGcheck(ACTOR* actorx) {
    mCoBG_BgCheckControll(NULL, actorx, 40.0f, 0.0f, FALSE, FALSE, 1);
}

static void aGYO_KAGE_Cullcheck(ACTOR* actorx, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (actorx->block_x != play->block_table.block_x || actorx->block_z != play->block_table.block_z) {
        Actor_delete(actorx);
    }
}

static void aGYO_KAGE_position_move(ACTOR* actorx) {
    GYO_KAGE_ACTOR* gyo_kage = (GYO_KAGE_ACTOR*)actorx;

    xyz_t_move(&actorx->last_world_position, &actorx->world.position);
    if (gyo_kage->draw_frame <= 0) {
        gyo_kage->draw_frame = 38;
    } else {
        gyo_kage->draw_frame--;
    }

    Actor_position_moveF(actorx);
    actorx->world.position.y = mCoBG_GetWaterHeight_File(actorx->world.position, __FILE__, 339) - 8.0f;
}

static void aGYO_KAGE_actor_move(ACTOR* actorx, GAME* game) {
    GYO_KAGE_ACTOR* gyo_kage = (GYO_KAGE_ACTOR*)actorx;
    int timer;

    if (gyo_kage->gyoei_actor != NULL && ((GYOEI_ACTOR*)gyo_kage->gyoei_actor)->exist[0] != 0) {
        ((GYOEI_ACTOR*)gyo_kage->gyoei_actor)->exist[0] = 0;
    }

    actorx->state_bitfield &= ~ACTOR_STATE_24;
    if ((actorx->state_bitfield & ACTOR_STATE_NO_MOVE_WHILE_CULLED) == 0) {
        return;
    }

    aGYO_KAGE_position_move(actorx);
    aGYO_KAGE_BGcheck(actorx);

    if (gyo_kage->delete_timer == 96) {
        switch (actorx->actor_specific) {
            case 0:
            case 1:
                aGYO_KAGE_effect_hamon(actorx, game, 2);
                break;
            case 3:
                aGYO_KAGE_effect_hamon(actorx, game, 1);
                break;
            case 2:
            case 4:
            case 5:
                aGYO_KAGE_effect_hamon(actorx, game, 0);
                break;
            default:
                break;
        }
    }

    if (gyo_kage->delete_timer == 0) {
        timer = 0;
    } else {
        timer = --gyo_kage->delete_timer;
    }

    if (timer == 0) {
        Actor_delete(actorx);
    } else {
        if (aGYO_KAGE_Wall_Check(actorx) && gyo_kage->wall_flag == FALSE) {
            return;
        }

        chase_f(&actorx->speed, 0.0f, 0.02f);
        gyo_kage->wall_flag = FALSE;
    }

    aGYO_KAGE_Cullcheck(actorx, game);
}

extern Gfx act_gyoei02_00_modelT[];

static void aGYO_KAGE_actor_draw(ACTOR* actorx, GAME* game) {
    GYO_KAGE_ACTOR* gyo_kage = (GYO_KAGE_ACTOR*)actorx;
    GRAPH* graph = game->graph;
    int tex_idx0;
    int tex_idx1;
    int alpha = ((int)(gyo_kage->delete_timer * 0.5f) - 10) * 6;
    s16 angle_x = actorx->shape_info.rotation.x;
    s16 angle_y = actorx->shape_info.rotation.y + DEG2SHORT_ANGLE2(180.0f);
    int frame = (int)(gyo_kage->draw_frame * 0.5f);

    Matrix_push();
    _texture_z_light_fog_prim_xlu(graph);
    tex_idx0 = aGYO_2tile_texture_idx[frame][0];
    tex_idx1 = aGYO_2tile_texture_idx[frame][1];
    if (alpha <= 0) {
        alpha = 0;
    }
    gyo_kage->alpha = alpha;

    Matrix_translate(actorx->world.position.x, actorx->world.position.y, actorx->world.position.z, MTX_LOAD);
    Matrix_RotateX(angle_x, MTX_MULT);
    Matrix_RotateY(angle_y, MTX_MULT);
    Matrix_scale(actorx->scale.x * 0.4f, actorx->scale.y, actorx->scale.z, MTX_MULT);

    OPEN_DISP(graph);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, aGYO_texture_table[tex_idx0]);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_2_TXT_SEG, aGYO_texture_table[tex_idx1]);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, aGYO_prim_f[frame], 0, 0, 0, gyo_kage->alpha);
    gSPDisplayList(NEXT_POLY_XLU_DISP, act_gyoei02_00_modelT);

    CLOSE_DISP(graph);

    Matrix_pull();
}
