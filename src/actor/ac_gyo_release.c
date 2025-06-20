#include "ac_gyo_release.h"

#include "ac_gyoei.h"
#include "m_name_table.h"
#include "m_play.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "m_actor_shadow.h"
#include "m_common_data.h"

static void aGYR_actor_ct(ACTOR* actorx, GAME* game);
static void aGYR_actor_dt(ACTOR* actorx, GAME* game);
static void aGYR_actor_move(ACTOR* actorx, GAME* game);
static void aGYR_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Gyo_Release_Profile = {
    mAc_PROFILE_GYO_RELEASE,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(GYO_RELEASE_ACTOR),
    &aGYR_actor_ct,
    &aGYR_actor_dt,
    &aGYR_actor_move,
    &aGYR_actor_draw,
    NULL,
};
// clang-format on

#include "../src/actor/ac_gyoei_type.c_inc"
#include "../src/actor/ac_gyoei_model.c_inc"

static f32 aGYO_shadow_scale[aGYO_SIZE_NUM] = { 0.3f, 0.4f, 0.5f, 0.5f, 0.6f, 0.8f, 1.2f, 10.0f };

static int aGYR_empty_area(ACTOR* actorx);

static void aGYR_actor_ct(ACTOR* actorx, GAME* game) {
    GYO_RELEASE_ACTOR* gyo_release = (GYO_RELEASE_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 water_y;
    f32 speed_xz;
    f32 speed_y;
    s16 angle_y;
    xyz_t pos;

    gyo_release->gyo_type = actorx->actor_specific - ITM_FISH_START;
    gyo_release->gyoei_actor_p = Actor_info_name_search(&play->actor_info, mAc_PROFILE_GYOEI, ACTOR_PART_CONTROL);
    gyo_release->segment = aGYR_empty_area(gyo_release->gyoei_actor_p);
    ((GYOEI_ACTOR*)gyo_release->gyoei_actor_p)->segment_type[gyo_release->segment] = gyo_release->gyo_type;
    actorx->drawn = TRUE;
    actorx->shape_info.draw_shadow = TRUE;
    gyo_release->size_type = gyoei_type[gyo_release->gyo_type].size;
    actorx->scale.x = 0.0126f;
    actorx->scale.y = 0.0126f;
    actorx->scale.z = 0.0126f;

    dx = play->submenu.water_pos.x - actorx->world.position.x;
    dz = play->submenu.water_pos.z - actorx->world.position.z;
    water_y = mCoBG_GetWaterHeight_File(play->submenu.water_pos, __FILE__, 213);
    dy = water_y - actorx->world.position.y;
    dist = sqrtf(SQ(dx) + SQ(dz));

    if (dist > mFI_UNIT_BASE_SIZE_F) {
        speed_xz = (dist / 60.0f) / 0.5f;
        speed_y = (dy - -450.0f) / 60.0f;
        if (speed_y < 0.0f) {
            speed_y = 0.0f;
        }
    } else {
        speed_xz = 2.5f;
        speed_y = ABS(dist) * 0.18f;
    }

    angle_y = atans_table(dz, dx);
    actorx->world.angle.y = angle_y;
    actorx->shape_info.rotation.y = angle_y;
    actorx->position_speed.y = speed_y;
    actorx->position_speed.x = speed_xz * sin_s(angle_y);
    actorx->position_speed.z = speed_xz * cos_s(angle_y);

    gyo_release->angle_xz = 0;
    gyo_release->angle_y = 0;
    gyo_release->angle_y_add = 180;
    gyo_release->exist_timer = 0;
    gyo_release->shadow_scale = 1.0f;
    gyo_release->exist_flag = TRUE;
    gyo_release->_1B5 = FALSE;
}

static void aGYR_actor_dt(ACTOR* actorx, GAME* game) {
    GYO_RELEASE_ACTOR* gyo_release = (GYO_RELEASE_ACTOR*)actorx;

    gyo_release->exist_flag = FALSE;
    ((GYOEI_ACTOR*)gyo_release->gyoei_actor_p)->segment_type[gyo_release->segment] = aGYO_TYPE_INVALID;
    ClObjPipe_dt(game, &gyo_release->col_pipe);
}

static int aGYR_anime_frame(GYO_RELEASE_ACTOR* gyo_release) {
    static int aGYR_frame_ptn1[] = { 1, 1, 0, 0, 2, 2, 0, 0 };
    static int aGYR_frame_ptn2[] = { 1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0 };
    static int aGYR_anime_ptn[] = {
        1, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 1, 1, 2, 1, 1, 1, 2, 2, 2, 2,
        1, 1, 2, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    };

    int cur_frame = gyo_release->anime_frame;
    int next_frame;

    cur_frame++;
    if (aGYR_anime_ptn[gyo_release->gyo_type] == 1) {
        if (cur_frame >= ARRAY_COUNT(aGYR_frame_ptn1)) {
            cur_frame = 0;
        }

        next_frame = aGYR_frame_ptn1[cur_frame];
    } else if (aGYR_anime_ptn[gyo_release->gyo_type] == 2) {
        if (cur_frame >= ARRAY_COUNT(aGYR_frame_ptn2)) {
            cur_frame = 0;
        }

        next_frame = aGYR_frame_ptn2[cur_frame];
    } else {
        cur_frame = 0;
        next_frame = 0;
    }

    gyo_release->anime_frame = cur_frame;
    return next_frame;
}

static int aGYR_empty_area(ACTOR* actorx) {
    GYOEI_ACTOR* gyoei = (GYOEI_ACTOR*)actorx;
    int i;
    int n = 0;

    for (i = 2; i < 4; i++) {
        if (gyoei->segment_type[i] == aGYO_TYPE_INVALID) {
            n = i;
            break;
        }
    }

    return n;
}

static s16 aGYR_Get_flow_angle(ACTOR* actorx) {
    xyz_t flow;
    s16 angle;

    mCoBG_GetWaterFlow(&flow, mCoBG_Wpos2BgAttribute_Original(actorx->world.position));
    angle = atans_table(flow.z, flow.x);
    return angle;
}

static void aGYR_effect_hamon(ACTOR* actorx, GAME* game, s16 arg) {
    xyz_t pos = actorx->world.position;
    f32 water_height = mCoBG_GetWaterHeight_File(actorx->world.position, __FILE__, 401);
    s16 angle = aGYR_Get_flow_angle(actorx);

    pos.y = water_height;
    eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, pos, 1, angle, game, EMPTY_NO, arg, 0);
}

static void aGYR_cull_check(ACTOR* actorx, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (actorx->block_x != play->block_table.block_x || actorx->block_z != play->block_table.block_z) {
        Actor_delete(actorx);
    }
}

static void aGYR_Shadow_size(ACTOR* actorx) {
    GYO_RELEASE_ACTOR* gyo_release = (GYO_RELEASE_ACTOR*)actorx;
    f32 ground_y;
    f32 height;
    f32 ofs_y;
    /* @BUG - the devs forgot to add a size for the new size types added in AC - XXL for Arapaima & WHALE size */
    static f32 hoseix[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.5f };
    static f32 hoseiz[] = { 3.0f, 2.5f, 2.5f, 2.5f, 2.5f, 7.0f };
    f32 correction_x;
    f32 correction_z;

    ground_y = mCoBG_GetBgY_AngleS_FromWpos(NULL, actorx->world.position, 0.0f);
    height = actorx->world.position.y - ground_y;
    ofs_y = 10.0f + (50.0f - height) * 0.2f;
    if (height < 0.0f) {
        ofs_y = 0.0f;
    }

    if (gyo_release->gyo_type == aGYO_TYPE_EEL) {
        correction_x = 9.0f;
        correction_z = 3.5f;
    } else {
        correction_x = hoseix[gyo_release->size_type];
        correction_z = hoseiz[gyo_release->size_type];
    }

    actorx->shape_info.shadow_size_x =
        aGYO_shadow_scale[gyo_release->size_type] * ofs_y * gyo_release->shadow_scale + correction_x;
    actorx->shape_info.shadow_size_z =
        aGYO_shadow_scale[gyo_release->size_type] * ofs_y * gyo_release->shadow_scale - correction_z;
}

static void aGYR_position_move(ACTOR* actorx) {
    GYO_RELEASE_ACTOR* gyo_release = (GYO_RELEASE_ACTOR*)actorx;
    u32 atr;

    xyz_t_move(&actorx->last_world_position, &actorx->world.position);
    actorx->position_speed.y += -0.25f;
    Actor_position_move(actorx);

    atr = mCoBG_Wpos2BgAttribute_Original(actorx->world.position);
    gyo_release->revert_position_timer--;
    if (gyo_release->revert_position_timer <= 0) {
        gyo_release->revert_position_timer = 0;
    }

    if (mCoBG_CheckWaterAttribute(atr)) {
        if (!gyo_release->revert_position_flag) {
            gyo_release->revert_position_flag = TRUE;
            gyo_release->revert_position_timer = 3;
        }
    } else {
        if (gyo_release->revert_position_flag == TRUE && gyo_release->revert_position_timer <= 0) {
            actorx->world.position.x = actorx->last_world_position.x;
            actorx->world.position.z = actorx->last_world_position.z;
        }
    }
}

static int aGYR_check_timer(ACTOR* actorx) {
    GYO_RELEASE_ACTOR* gyo_release = (GYO_RELEASE_ACTOR*)actorx;
    int res = TRUE;

    gyo_release->exist_timer++;
    if (gyo_release->exist_timer > 140) {
        f32 scale_rate;

        if (actorx->scale.x > 0.006f) {
            scale_rate = 0.89f;
        } else {
            scale_rate = 0.98f;
        }

        actorx->scale.x *= scale_rate;
        actorx->scale.y = actorx->scale.z = actorx->scale.x;
        gyo_release->shadow_scale *= scale_rate;
        if (gyo_release->exist_timer > 160) {
            Actor_delete(actorx);
            res = FALSE;
        }
    }

    return res;
}

static void aGYR_in_water_move(ACTOR* actorx, GAME* game) {
    GYO_RELEASE_ACTOR* gyo_release = (GYO_RELEASE_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    aGYR_effect_hamon(actorx, game, 3);
    sAdo_OngenTrgStart(NA_SE_437, &actorx->world.position);
    Actor_info_make_actor(&play->actor_info, game, mAc_PROFILE_GYO_KAGE, actorx->world.position.x,
                          actorx->world.position.y, actorx->world.position.z, 0, actorx->world.angle.y, 0,
                          play->block_table.block_x, play->block_table.block_z, -1, EMPTY_NO, gyo_release->size_type,
                          -1, ACTOR_OBJ_BANK_KEEP);
    Actor_delete(actorx);
}

static void aGYR_move_sub(ACTOR* actorx, GAME* game) {
    GYO_RELEASE_ACTOR* gyo_release = (GYO_RELEASE_ACTOR*)actorx;

    chase_s(&gyo_release->angle_xz, DEG2SHORT_ANGLE2(90.0f), 0x800);
    if (aGYR_check_timer(actorx) == TRUE) {
        if (mCoBG_CheckWaterAttribute(mCoBG_Wpos2BgAttribute_Original(actorx->world.position))) {
            f32 water_y = mCoBG_GetWaterHeight_File(actorx->world.position, __FILE__, 635);

            if (water_y >= actorx->world.position.y) {
                aGYR_in_water_move(actorx, game);
                return;
            }
        }

        chase_s(&gyo_release->angle_y_add, 180, 32);
        if (gyo_release->gyo_type == aGYO_TYPE_LOACH || gyo_release->gyo_type == aGYO_TYPE_EEL) {
            gyo_release->angle_y = 0;
        } else {
            gyo_release->angle_y = DEG2SHORT_ANGLE2(30.0f * sin_s(DEG2SHORT_ANGLE2(gyo_release->angle_y_add)));
        }

        aGYR_Shadow_size(actorx);
    }
}

static void aGYR_actor_move(ACTOR* actorx, GAME* game) {
    GYO_RELEASE_ACTOR* gyo_release = (GYO_RELEASE_ACTOR*)actorx;
    
    if (gyo_release->gyoei_actor_p != NULL) {
        GYOEI_ACTOR* gyoei = (GYOEI_ACTOR*)gyo_release->gyoei_actor_p;

        if (gyoei->exist[gyo_release->segment] != 0) {
            gyoei->exist[gyo_release->segment] = 0;
        }
    }

    actorx->state_bitfield &= ~ACTOR_STATE_24;
    if ((actorx->state_bitfield & ACTOR_STATE_NO_MOVE_WHILE_CULLED) != 0) {
        aGYR_position_move(actorx);
        aGYR_move_sub(actorx, game);
        aGYR_cull_check(actorx, game);
    }
}

static void aGYR_actor_draw(ACTOR* actorx, GAME* game) {
    GYO_RELEASE_ACTOR* gyo_release = (GYO_RELEASE_ACTOR*)actorx;
    GRAPH* graph = game->graph;
    int frame;

    Matrix_push();
    _texture_z_light_fog_prim(graph);
    Matrix_translate(actorx->world.position.x, actorx->world.position.y, actorx->world.position.z, MTX_LOAD);
    Matrix_RotateX(-gyo_release->angle_xz, MTX_MULT);
    Matrix_RotateY(gyo_release->angle_y, MTX_MULT);
    Matrix_RotateZ(gyo_release->angle_xz, MTX_MULT);
    Matrix_scale(actorx->scale.x * 1.2f, actorx->scale.y, actorx->scale.z, MTX_MULT);

    OPEN_DISP(graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (actorx->bg_collision_check.result.on_ground) {
        frame = 0;
    } else {
        frame = aGYR_anime_frame(gyo_release);
    }
    gSPDisplayList(NEXT_POLY_OPA_DISP, ((Gfx**)aGYO_displayList[gyo_release->gyo_type])[(int)(frame * 0.5f)]);

    CLOSE_DISP(graph);

    {
        static xyz_t offset = { 0.0f, 0.0f, 0.0f };
        
        actorx->shape_info.shadow_alpha_change_rate = 0.5f;
        mAc_UnagiActorShadow(actorx, game, offset);
    }

    Matrix_pull();
}
