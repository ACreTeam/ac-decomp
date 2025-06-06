#include "ac_snowman.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_actor_shadow.h"
#include "m_roll_lib.h"
#include "m_handbill.h"
#include "m_malloc.h"

enum {
    aSMAN_PART0,
    aSMAN_PART1,

    aSMAN_PART_NUM
};

static void aSMAN_actor_ct(ACTOR* actorx, GAME* game);
static void aSMAN_actor_dt(ACTOR* actorx, GAME* game);
static void aSMAN_actor_move(ACTOR* actorx, GAME* game);
static void aSMAN_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Snowman_Profile = {
    mAc_PROFILE_SNOWMAN,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    ETC_SNOWMAN_BALL_A,
    ACTOR_OBJ_BANK_PSNOWMAN,
    sizeof(SNOWMAN_ACTOR),
    aSMAN_actor_ct,
    aSMAN_actor_dt,
    aSMAN_actor_move,
    aSMAN_actor_draw,
    NULL,
};
// clang-format on

// clang-format off
static ClObjPipeData_c aSMAN_CoInfoData = {
    { 0x39, 0x20, ClObj_TYPE_PIPE },
    { 0x01 },
    { 5, 5, 0, { 0, 0, 0 } }
};
// clang-format on

// clang-format off
static StatusData_c aSMAN_StatusData = {
    0,
    5,
    5,
    0,
    196,
};
// clang-format on

static void aSMAN_process_normal_init(ACTOR* actorx);
static void aSMAN_process_combine_head_jump_init(ACTOR* actorx, GAME* game);
static void aSMAN_process_combine_body_init(ACTOR* actorx);

static void aSMAN_process_player_push(ACTOR* actorx, GAME* game);
static void aSMAN_process_player_push_scroll(ACTOR* actorx, GAME* game);
static void aSMAN_process_combine_body(ACTOR* actorx, GAME* game);
static void aSMAN_process_combine_head_jump(ACTOR* actorx, GAME* game);
static void aSMAN_process_swim(ACTOR* actorx, GAME* game);
static void aSMAN_process_air(ACTOR* actorx, GAME* game);

static void aSMAN_actor_ct(ACTOR* actorx, GAME* game) {
    static int part_tbl[] = { aSMAN_PART0, aSMAN_PART1 };
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    
    if (actorx->npc_id == ETC_SNOWMAN_BALL_A) {
        f32* move_dist = (f32*)mEv_get_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART0);

        if (move_dist != NULL) {
            actor->move_dist = *move_dist;
        } else {
            mEv_reserve_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART0);
            actor->move_dist = 0.0f;
        }
    } else {
        f32* move_dist = (f32*)mEv_get_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART1);

        if (move_dist != NULL) {
            actor->move_dist = *move_dist;
        } else {
            mEv_reserve_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART1);
            actor->move_dist = 0.0f;
        }
    }

    Shape_Info_init(actorx, 0.0f, mAc_ActorShadowEllipse, 10.0f, 10.0f);
    ClObjPipe_ct(game, &actor->col_pipe);
    ClObjPipe_set5(game, &actor->col_pipe, actorx, &aSMAN_CoInfoData);
    CollisionCheck_Status_set3(&actorx->status_data, &aSMAN_StatusData);
    actor->col_actor = NULL;
    actor->timer = 0;
    actor->snowman_part = part_tbl[actorx->npc_id != ETC_SNOWMAN_BALL_A];
    actorx->max_velocity_y = -30.0f;
    actorx->gravity = 0.8f;
    actorx->speed = 0.0f;
    actor->base_speed = 0.0f;
    actor->accel = 0.1f;
    actor->roll_speed = 0.0f;
    aSMAN_process_normal_init(actorx);
    actorx->scale.x = 0.01f;
    actorx->scale.y = 0.01f;
    actorx->scale.z = 0.01f;
}

static void aSNOWMAN_Set_PSnowman_info(SNOWMAN_ACTOR* actor) {
    mSN_snowman_info_c sman_info;

    xyz_t_move(&sman_info.pos, &actor->fg_pos);
    sman_info.data.exists = TRUE;
    sman_info.data.head_size = actor->normalized_scale * 255;
    sman_info.data.body_size = actor->body_scale * 255;
    sman_info.data.score = actor->result;
    mCoBG_SetPlussOffset(actor->actor_class.world.position, 0, mCoBG_ATTRIBUTE_NONE);
    if ((actor->flags & 0x80) == 0) {
        mSN_regist_snowman_society(&sman_info);
    }
}

static void aSMAN_actor_dt(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    ClObjPipe_dt(game, &actor->col_pipe);
    if (actor->snowman_part == aSMAN_PART0) {
        if (actor->flags & 0x20) {
            if (actor->flags & 1) {
                if (actor->fg_pos.x != 0.0f || actor->fg_pos.z != 0.0f) {
                    aSNOWMAN_Set_PSnowman_info(actor);
                } else {
                    mCoBG_SetPlussOffset(actorx->world.position, 0, mCoBG_ATTRIBUTE_NONE);
                }
            }

            mEv_clear_common_place(mEv_EVENT_SNOWMAN_SEASON, 100 + aSMAN_PART0);
            mEv_clear_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART0);
        } else {
            if ((actor->flags & 8) || (actor->flags & 4) || !mRlib_Set_Position_Check(actorx)) {
                mEv_clear_common_place(mEv_EVENT_SNOWMAN_SEASON, 100 + aSMAN_PART0);
                mEv_clear_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART0);
            } else {
                f32* move_dist = (f32*)mEv_get_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART0);

                if (move_dist != NULL) {
                    *move_dist = actor->move_dist;
                }
            }
        }
    } else {
        if (actor->flags & 0x20) {
            if (actor->flags & 1) {
                if (actor->fg_pos.x != 0.0f || actor->fg_pos.z != 0.0f) {
                    aSNOWMAN_Set_PSnowman_info(actor);
                } else {
                    mCoBG_SetPlussOffset(actorx->world.position, 0, mCoBG_ATTRIBUTE_NONE);
                }
            }

            mEv_clear_common_place(mEv_EVENT_SNOWMAN_SEASON, 100 + aSMAN_PART1);
            mEv_clear_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART1);
        } else {
            if ((actor->flags & 8) || (actor->flags & 4) || !mRlib_Set_Position_Check(actorx)) {
                mEv_clear_common_place(mEv_EVENT_SNOWMAN_SEASON, 100 + aSMAN_PART1);
                mEv_clear_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART1);
            } else {
                f32* move_dist = (f32*)mEv_get_common_area(mEv_EVENT_SNOWMAN_SEASON, aSMAN_PART1);

                if (move_dist != NULL) {
                    *move_dist = actor->move_dist;
                }
            }
        }
    }

    mEv_actor_dying_message(mEv_EVENT_SNOWMAN_SEASON, actorx);
}

static void aSMAN_GetSnowmanPresentMail(Mail_c* mail) {
    PersonalID_c* pid = &Now_Private->player_ID;
    int mail_idx = 0x202;
    int rnd = RANDOM(12);
    mActor_name_t item;
    u8 item_name[mIN_ITEM_NAME_LEN];
    int header_back_start;
    // clang-format off
    static mActor_name_t snow_item_table[] = {
        FTR_SNOWMAN_FRIDGE,
        FTR_SNOWMAN_TABLE,
        FTR_SNOWMAN_BED,
        FTR_SNOWMAN_CHAIR,
        FTR_SNOWMAN_LAMP,
        FTR_SNOWMAN_SOFA,
        FTR_SNOWMAN_TV,
        FTR_SNOWMAN_DRESSER,
        FTR_SNOWMAN_WARDROBE,
        FTR_SNOWMAN_CLOCK,
        ITM_CARPET25,
        ITM_WALL25,
    };
    // clang-format on

    // one chance at a re-roll if the player already has the item
    if (mSP_CollectCheck(snow_item_table[rnd])) {
        rnd = RANDOM(12);
    }

    item = snow_item_table[rnd];
    mail_idx += rnd;
    mIN_copy_name_str(item_name, item);
    mHandbill_Set_free_str(mHandbill_FREE_STR0, item_name, sizeof(item_name));
    mHandbill_Load_HandbillFromRom(mail->content.header, &header_back_start, mail->content.footer, mail->content.body, mail_idx);
    mail->content.header_back_start = header_back_start;
    mail->content.font = mMl_FONT_RECV;
    mail->content.mail_type = mMl_TYPE_SNOWMAN;
    mail->present = item;
    mail->content.paper_type = (u8)ITM_PAPER12;
    mPr_CopyPersonalID(&mail->header.recipient.personalID, pid);
    mail->header.recipient.type = mMl_NAME_TYPE_PLAYER;
}

static void aSMAN_SendPresentMail(void) {
    Mail_c* mail = (Mail_c*)zelda_malloc(sizeof(Mail_c));

    if (!mLd_PlayerManKindCheck() && mail != NULL && mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE) {
        mMl_clear_mail(mail);
        aSMAN_GetSnowmanPresentMail(mail);
        mPO_receipt_proc(mail, mPO_SENDTYPE_MAIL);
    }

    zelda_free(mail);
}

static int aSNOWMAN_player_block_check(ACTOR* actorx, GAME* game) {
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    int pbx;
    int pbz;
    int bx;
    int bz;

    mFI_Wpos2BlockNum(&pbx, &pbz, playerx->world.position);
    mFI_Wpos2BlockNum(&bx, &bz, actorx->world.position);
    if (pbx == bx && pbz == bz) {
        return TRUE;
    }

    return FALSE;
}

static int aSMAN_FG_Position_Get(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    // clang-format off
    static xy_t chk_pos_tbl[] = {
        {                 0.0f,                  0.0f},
        { mFI_UNIT_BASE_SIZE_F,                  0.0f},
        {-mFI_UNIT_BASE_SIZE_F,                  0.0f},
        {                 0.0f,  mFI_UNIT_BASE_SIZE_F},
        {                 0.0f, -mFI_UNIT_BASE_SIZE_F},
        { mFI_UNIT_BASE_SIZE_F,  mFI_UNIT_BASE_SIZE_F},
        {-mFI_UNIT_BASE_SIZE_F,  mFI_UNIT_BASE_SIZE_F},
        { mFI_UNIT_BASE_SIZE_F, -mFI_UNIT_BASE_SIZE_F},
        {-mFI_UNIT_BASE_SIZE_F, -mFI_UNIT_BASE_SIZE_F},
    };
    // clang-format on
    int i;

    for (i = 0; i < ARRAY_COUNT(chk_pos_tbl); i++) {
        mActor_name_t item;
        u32 attr;
        xyz_t pos;
        f32 ground_y;

        pos = actorx->world.position;
        pos.x += chk_pos_tbl[i].x;
        pos.z += chk_pos_tbl[i].y;
        pos.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, pos, 0.0f);
        // @optimization - function call inside of ABS macro...
        ground_y = ABS(pos.y - mCoBG_GetBgY_AngleS_FromWpos(NULL, actorx->world.position, 0.0f));
        item = *mFI_GetUnitFG(pos); // @BUG - they don't check for NULL here, and mFI_GetUnitFG can return a NULL pointer.
        attr = mCoBG_Wpos2Attribute(pos, NULL);

        if (!mCoBG_ExistHeightGap_KeepAndNow(pos) && item != RSV_NO && item != RSV_WALL_NO && attr != mCoBG_ATTRIBUTE_STONE && attr != mCoBG_ATTRIBUTE_WOOD && ground_y < 60.0f) {
            actor->fg_pos = pos;
            return TRUE;
        }
    }

    actor->fg_pos = ZeroVec;
    return FALSE;
}

static void aSMAN_House_Tree_Rev_Check(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    
    if (mRlib_HeightGapCheck_And_ReversePos(actorx) != TRUE) {
        actor->flags |= 4;
        Actor_delete(actorx);
    }
}

static void aSMAN_Make_Effect_Ground(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    
    if (actor->normalized_scale < 0.2f) {
        return;
    }

    if ((game->frame_counter & 0xF) == 0 && actorx->bg_collision_check.result.unit_attribute == mCoBG_ATTRIBUTE_BUSH && actorx->speed > 1.0f) {
        xyz_t pos = actorx->world.position;
        s16 arg;
        s16 angle;

        angle = DEG2SHORT_ANGLE2(45.0f + RANDOM_F(45.0f));
        if (game->frame_counter & 0x10) {
            angle = -angle;
        }

        arg = actorx->speed > 4.0f ? 1 : 0;
        pos.x += (actor->normalized_scale * 20.0f + 10.0f) * sin_s(angle);
        pos.z += (actor->normalized_scale * 20.0f + 10.0f) * cos_s(angle);
        pos.y -= (actor->normalized_scale * 20.0f + 10.0f);
        eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_HAPPA, pos, 1, actorx->world.angle.y, game, actorx->npc_id, 0, arg);
        eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_YUKI, pos, 1, actorx->world.angle.y, game, actorx->npc_id, 0, 0);
    }
}

static void aSMAN_get_hole_offset(ACTOR* actorx, f32 hole_dist) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    static f32 small_offset = -875.0f;
    static f32 middle_offset = -750.0f;
    static f32 large_offset = -250.0f;
    f32 ofs;
    f32 rate;
    f32 clamped_rate;

    rate = (hole_dist * 2.0f) / mFI_UNIT_BASE_SIZE_F;
    clamped_rate = M_CLAMP(rate, 0.0f, 1.0f);

    if (actor->normalized_scale < 0.2f) {
        ofs = small_offset + actor->normalized_scale * 3.0f * (middle_offset - small_offset);
    } else {
        ofs = middle_offset + (actor->normalized_scale * 1.5f - 0.5f) * (large_offset - middle_offset);
    }

    ofs *= clamped_rate;
    add_calc(&actor->y_ofs, ofs, 1.0f - sqrtf(0.5f), 100.0f, 2.5f);
}

static int aSMAN_get_ground_norm(ACTOR* actorx, xyz_t* norm, xyz_t* pos) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    mCoBG_GetBgNorm_FromWpos(norm, *pos);
    if (Math3d_normalizeXyz_t(norm)) {
        f32 hole_dist;
        s16 norm_rate;
        s16 angle;

        if (mRlib_Get_ground_norm_inHole(actorx, norm, &hole_dist, &angle, &norm_rate, 1.0f - actor->normalized_scale * 0.5f)) {
            aSMAN_get_hole_offset(actorx, hole_dist);
            if ((actor->flags & 8) == 0) {
                s16 angle_mod;
                f32 cos = cos_s(angle);
                f32 sin = sin_s(angle);
                f32 norm_f;

                angle_mod = norm_rate + (int)(actor->ground_angle.z * sin * sin + actor->ground_angle.x * cos * cos);
                norm_rate = (int)angle_mod;
                norm_rate = M_CLAMP((int)angle_mod, DEG2SHORT_ANGLE(90.0f), DEG2SHORT_ANGLE(-90.0f));

                if (actor->normalized_scale < 0.5f) {
                    actorx->position_speed.x *= 0.9f;
                    actorx->position_speed.z *= 0.9f;
                } else if (actor->ground_angle.x == 0 && actor->ground_angle.z == 0) {
                    actorx->position_speed.x *= 0.95f;
                    actorx->position_speed.z *= 0.95f;
                }

                norm_f = -cos_s(norm_rate);
                mRlib_spdF_Angle_to_spdXZ(norm, &norm_f, &angle);
                norm->y = sin_s(norm_rate);
                if (hole_dist < 1.0f) {
                    if (ABS(actorx->position_speed.x) < 1.0f && ABS(actorx->position_speed.z) < 1.0f) {
                        actor->flags |= 8;
                        actorx->state_bitfield &= ~ACTOR_STATE_NO_MOVE_WHILE_CULLED;
                        actorx->status_data.weight = MASSTYPE_HEAVY;
                        actorx->speed = 0.0f;
                    }
                }
            }
        } else {
            mRlib_Get_norm_Clif(actorx, norm);
            add_calc0(&actor->y_ofs, 1.0f - sqrtf(0.5f), 50.0f);
        }

        return TRUE;
    }

    return FALSE;
}

static void aSMAN_player_push_free(GAME* game) {
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

    playerx->speed = 0.0f;
    mPlib_request_main_push_snowball_end_type1(game);
}

static int aSMAN_player_push_HitWallCheck(ACTOR* actorx, GAME* game) {
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    u32 hit_wall = playerx->bg_collision_check.result.hit_wall;
    u32 hit_attr_wall = playerx->bg_collision_check.result.hit_attribute_wall;
    s16 wall_angle;
    s16 dAngle;
    
    if ((hit_wall & mCoBG_HIT_WALL) || (hit_attr_wall & mCoBG_HIT_WALL)) {
        wall_angle = mRlib_Get_HitWallAngleY(actorx);
        dAngle = (wall_angle - playerx->world.angle.y) + DEG2SHORT_ANGLE2(180.0f);
        if (ABS(dAngle) > DEG2SHORT_ANGLE2(45.0f)) {
            return TRUE;
        }
    }

    return FALSE;
}

static s16 aSMAN_get_norm_push_angle_distance(ACTOR* actorx, xyz_t* norm, s16 push_angle) {
    s16 norm_angle;

    mCoBG_GetBgNorm_FromWpos(norm, actorx->world.position);
    norm_angle = atans_table(norm->z, norm->x);
    return norm_angle - push_angle;
}

static void aSMAN_player_push_scroll_request(ACTOR* actorx, GAME* game) {
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    int dir;
    xyz_t snowball_ofs;
    xyz_t rev;

    rev = mCoBG_UniqueWallCheck(playerx, 18.0f, 0.0f);
    dir = mPlib_CheckCondition_forWadeSnowball(&playerx->world.position, playerx->world.angle.y);
    if (dir != mFI_MOVEDIR_NONE) {
        xyz_t_sub(&actorx->world.position, &playerx->world.position, &snowball_ofs);
        mPlib_Set_ScrollDemo_forWade_snowball(dir, &snowball_ofs);
    } else if (!F32_IS_ZERO(rev.x) || !F32_IS_ZERO(rev.z)) {
        aSMAN_player_push_free(game);
        aSMAN_process_normal_init(actorx);
    }
}

static void aSMAN_set_speed_relations_norm_player_push(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    s16 dAngle = ABS(actorx->world.angle.y - playerx->world.angle.y);
    xyz_t norm;

    if (aSMAN_get_ground_norm(actorx, &norm, &actorx->world.position) && (!F32_IS_ZERO(norm.x) || !F32_IS_ZERO(norm.z))) {
        if (dAngle < DEG2SHORT_ANGLE2(90.0f)) {
            f32 accel = 0.3f + actor->normalized_scale * 0.099999994f;
            f32 norm_speed;

            accel *= 0.2f;
            actorx->position_speed.x += norm.x * accel;
            actorx->position_speed.z += norm.z * accel;
            mRlib_spdXZ_to_spdF_Angle(&actorx->position_speed, &norm_speed, &actorx->world.angle.y);
            actor->base_speed = norm_speed + (actor->normalized_scale * 0.02f + 0.01f) * (actor->base_speed - norm_speed);
        } else if (actorx->speed > 0.5f) {
            actor->base_speed = 0.0f;
            actor->accel = 0.0f;
        }
    }
}

static ACTOR* aSMAN_get_oc_actor(SNOWMAN_ACTOR* actor) {
    if (ClObj_DID_COLLIDE(actor->col_pipe.collision_obj)) {
        ACTOR* oc_actor = actor->col_pipe.collision_obj.collided_actor;

        if (oc_actor != NULL) {
            return oc_actor;
        }
    }

    return NULL;
}

static void aSMAN_MakeBreakEffect(SNOWMAN_ACTOR* actor, GAME* game) {
    xyz_t pos = actor->actor_class.world.position;
    s16 arg = (s16)(actor->normalized_scale * 100.0f);

    pos.y -= actor->normalized_scale * 20.0f + 10.0f;
    eEC_CLIP->effect_make_proc(eEC_EFFECT_YUKIDARUMA, pos, 1, 0, game, actor->actor_class.npc_id, arg, 0);
    sAdo_OngenTrgStart(0x143, &actor->actor_class.world.position);
}

static int aSMAN_status_check_in_move(SNOWMAN_ACTOR* actor, GAME* game) {
    int ret = FALSE;

    if ((actor->flags & 2) != 0 && (actor->flags & 0x20) == 0) {
        actor->flags |= 4;
        aSMAN_MakeBreakEffect(actor, game);
        Actor_delete((ACTOR*)actor);
        ret = TRUE;
    }

    if (actor->flags & 0x20) {
        ret = TRUE;
    }

    if (actor->flags & 8) {
        ret = TRUE;
    }

    if (ret == TRUE && (actor->process == aSMAN_process_player_push || actor->process == aSMAN_process_player_push_scroll)) {
        aSMAN_player_push_free(game);
    }

    return ret;
}

static void aSMAN_position_move(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    mCoBG_GetBgY_AngleS_FromWpos(&actor->ground_angle, actorx->world.position, 0.0f);
    chase_f(&actorx->speed, actor->base_speed, actor->accel);
    
    if ((actor->flags & 0x20) != 0 || (actor->flags & 8) != 0 ||
        actor->process == aSMAN_process_combine_body || actor->process == aSMAN_process_player_push_scroll) {
        return;
    }

    Actor_position_speed_set(actorx);
    mRlib_position_move_for_sloop(actorx, &actor->ground_angle);
}

static int aSMAN_BGcheck(ACTOR* actorx, GAME* game) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    f32 r = actor->normalized_scale * 20.0f + 10.0f;

    if ((actor->flags & 0x20) != 0 || actor->process == aSMAN_process_combine_head_jump || actor->process == aSMAN_process_combine_body) {
        return FALSE;
    }

    if (actor->process == aSMAN_process_swim) {
        mCoBG_BgCheckControll(&actor->rev_pos, actorx, r, -r, mCoBG_WALL_TYPE0, mCoBG_REVERSE_TYPE_NO_REVERSE, mCoBG_CHECK_TYPE_NORMAL);
        actorx->world.position.x += actor->rev_pos.x;
        actorx->world.position.z += actor->rev_pos.z;
    } else {
        mCoBG_BgCheckControll(&actor->rev_pos, actorx, r, -r, mCoBG_WALL_TYPE0, mCoBG_REVERSE_TYPE_REVERSE, mCoBG_CHECK_TYPE_NORMAL);
        mRlib_Station_step_modify_to_wall(actorx);

        if (actorx->world.position.y - actorx->last_world_position.y > 60.0f) {
            actorx->world.position = actorx->last_world_position;
            actor->flags |= 0x4;
            actor->flags |= 0x2;
            return FALSE;
        }
    }

    if ((actorx->bg_collision_check.result.hit_wall & mCoBG_HIT_WALL) != 0) {
        s16 angle = mRlib_Get_HitWallAngleY(actorx);
        s16 colAngle = (angle - DEG2SHORT_ANGLE2(90.0f)) - actorx->world.angle.y;
        int diff;
        f32 speed = actorx->speed * sin_s(colAngle);

        if (ABS(speed) > 5.0f) {
            actor->flags |= 0x4;
            actor->flags |= 0x2;
            return FALSE;
        }


        diff = actorx->world.angle.y - (angle - DEG2SHORT_ANGLE2(-180.0f));
        if (speed > 0.0f) {
            f32 speed2 = actorx->speed * cos_s(colAngle);

            actorx->world.angle.y = angle - diff;
            speed *= 0.7f;
            actorx->speed = sqrtf(SQ(speed) + SQ(speed2));

            if (actor->process != aSMAN_process_player_push && !actorx->bg_collision_check.result.is_in_water && actorx->speed > 0.5f) {
                sAdo_OngenTrgStartSpeed(actorx->speed, 0x103, &actorx->world.position);
            }
        } else {
            if (actor->process == aSMAN_process_air) {
                sAdo_OngenTrgStartSpeed(actorx->speed, 0x103, &actorx->world.position);
                actorx->world.angle.y = angle;
                actorx->speed *= 1.2f;
                actorx->position_speed.y = 0.0f;
            }
        }

        mRlib_spdF_Angle_to_spdXZ(&actorx->position_speed, &actorx->speed, &actorx->world.angle.y);
    }

    return TRUE;
}

static int aSMAN_snowman_hit_check(SNOWMAN_ACTOR* actor, GAME* game, ACTOR* oc_actorx) {
    int b_ux;
    int b_uz;
    
    actor->col_actor = oc_actorx;
    if (oc_actorx->id == mAc_PROFILE_SNOWMAN) {
        SNOWMAN_ACTOR* oc_actor = (SNOWMAN_ACTOR*)oc_actorx;
        u32 attr;
        xyz_t center_pos;

        if ((F32_IS_ZERO(actor->actor_class.speed) && F32_IS_ZERO(oc_actorx->speed))) {
            return FALSE;
        }

        if (actor->actor_class.speed >= oc_actorx->speed) {
            mFI_Wpos2UtCenterWpos(&center_pos, oc_actorx->world.position);
        } else {
            mFI_Wpos2UtCenterWpos(&center_pos, actor->actor_class.world.position);
        }

        attr = mCoBG_Wpos2Attribute(center_pos, NULL);
        mFI_Wpos2UtNum_inBlock(&b_ux, &b_uz, center_pos);
        if (attr == mCoBG_ATTRIBUTE_STONE || attr == mCoBG_ATTRIBUTE_WOOD || mCoBG_Wpos2CheckSlateCol(&center_pos, FALSE) || b_ux == 0 || b_ux == (UT_X_NUM - 1) || b_uz == 0 || b_uz == (UT_Z_NUM - 1) || (oc_actor->flags & 0x8) != 0 || oc_actor->ground_angle.x != 0 || oc_actor->ground_angle.z != 0 || !aSNOWMAN_player_block_check((ACTOR*)actor, game)) {
            return FALSE;
        }

        if (actor->snowman_part != oc_actor->snowman_part && actor->normalized_scale > 0.2f && oc_actor->normalized_scale > 0.2f) {
            actor->actor_class.status_data.weight = MASSTYPE_HEAVY;
            oc_actorx->status_data.weight = MASSTYPE_HEAVY;
            
            if (oc_actor->process == aSMAN_process_player_push || actor->process == aSMAN_process_player_push) {
                aSMAN_player_push_free(game);
            }

            if (actor->actor_class.speed >= oc_actorx->speed) {
                oc_actor->col_actor = (ACTOR*)actor;
                aSMAN_process_combine_head_jump_init((ACTOR*)actor, game);
                aSMAN_process_combine_body_init(oc_actorx);
            } else {
                oc_actor->col_actor = (ACTOR*)actor;
                aSMAN_process_combine_body_init((ACTOR*)actor);
                aSMAN_process_combine_head_jump_init(oc_actorx, game);
            }

            return TRUE;
        }

        return FALSE;
    }

    return FALSE;
}

static void aSMAN_OBJcheck(SNOWMAN_ACTOR* actor, GAME* game) {
    if ((actor->flags & 0x20) != 0) {
        return;
    }

    if (ClObj_DID_COLLIDE(actor->col_pipe.collision_obj)) {
        ACTOR* oc_actorx = actor->col_pipe.collision_obj.collided_actor;

        actor->col_pipe.collision_obj.collision_flags0 &= ~ClObj_FLAG_COLLIDED;
        if (oc_actorx != NULL) {
            xyz_t tmp;

            if (actor->col_actor != oc_actorx && !aSMAN_snowman_hit_check(actor, game, oc_actorx)) {
                f32 rate = (1.0f - actor->normalized_scale) * 0.4f;
                
                tmp = oc_actorx->position_speed;
                xyz_t_mult_v(&tmp, rate);
                if (oc_actorx->speed > 0.5f) {
                    sAdo_OngenTrgStartSpeed(oc_actorx->speed, 0x102, &actor->actor_class.world.position);
                }
            } else {
                f32 add = 0.16f - actor->normalized_scale * 0.14f;
                s16 angle = oc_actorx->world.angle.y;

                if (actor->normalized_scale > 0.2f) {
                    add *= 0.2f;
                }

                mRlib_spdF_Angle_to_spdXZ(&tmp, &add, &angle);
                tmp.y = 0.0f;
            }

            if (tmp.x * (actor->actor_class.world.position.x - oc_actorx->world.position.x) > 0.0f) {
                actor->actor_class.position_speed.x += tmp.x;
            }

            if (tmp.z * (actor->actor_class.world.position.z - oc_actorx->world.position.z) > 0.0f) {
                actor->actor_class.position_speed.z += tmp.z;
            }
        } else {
            actor->col_actor = NULL;
        }
    } else {
        actor->col_actor = NULL;
    }
}

static void aSMAN_set_speed_relations_norm(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    xyz_t norm;

    if (aSMAN_get_ground_norm(actorx, &norm, &actorx->world.position) && (!F32_IS_ZERO(norm.x) || !F32_IS_ZERO(norm.z))) {
        f32 vel = actor->normalized_scale * 0.099999994f + 0.3f;

        actorx->position_speed.x += norm.x * vel;
        actorx->position_speed.z += norm.z * vel;
        actorx->world.angle.y = atans_table(actorx->position_speed.z, actorx->position_speed.x);
        actor->base_speed = fsqrt(SQ(actorx->position_speed.z) + SQ(actorx->position_speed.x));
        actor->accel = 0.0f;
    } else {
        actor->base_speed = 0.0f;
        actor->accel = 0.1f - actor->normalized_scale * 0.05f;
    }

    actorx->max_velocity_y = -30.0f;
    actorx->gravity = 0.8f;
    actor->roll_speed = actorx->speed;
}

static void aSMAN_set_speed_relations_swim(ACTOR* actorx) {
    static s16 angl_add_table[] = { DEG2SHORT_ANGLE2(1.40625f), DEG2SHORT_ANGLE2(5.625f) };
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    xyz_t flow;
    s16 flow_angle;
    f32 water_height;

    water_height = mCoBG_GetWaterHeight_File(actorx->world.position, __FILE__, 1362);
    mCoBG_GetWaterFlow(&flow, actorx->bg_collision_check.result.unit_attribute);
    flow_angle = atans_table(flow.z, flow.x);
    chase_angle(&actorx->world.angle.y, flow_angle, angl_add_table[ABS(DIFF_SHORT_ANGLE(actorx->world.angle.y, flow_angle)) > DEG2SHORT_ANGLE2(90.0f)]);
    if (actorx->world.position.y < water_height) {
        actorx->max_velocity_y = 1.0f;
    } else {
        actorx->max_velocity_y = -1.0f;
    }

    actorx->gravity = 0.1f;
    actor->base_speed = 1.0f;
    actor->accel = 0.1f;
    add_calc0(&actor->roll_speed, 1.0f - sqrtf(0.5f), 0.25f);
}

static void aSMAN_calc_axis(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;

    if (!F32_IS_ZERO(actor->roll_speed) && actor->process != aSMAN_process_player_push_scroll) {
        s16 dAngle = (s16)(actor->roll_speed * (DEG2SHORT_ANGLE3(180.0f) / (((actor->normalized_scale * 20.0f + 10.0f) * 2.0f) * 3.14f)));

        if (actor->process == aSMAN_process_swim) {
            f32 rate = (-1.0f - actorx->position_speed.y) / -2.0f;
            dAngle *= rate;
        }

        mRlib_Roll_Matrix_to_s_xyz(actorx, &actor->head_vec, dAngle);
    }
}

static void aSMAN_calc_scale(ACTOR* actorx) {
    SNOWMAN_ACTOR* actor = (SNOWMAN_ACTOR*)actorx;
    f32 scale;
    u32 attr = mCoBG_Wpos2Attribute(actorx->world.position, NULL);

    if (attr <= mCoBG_ATTRIBUTE_GRASS3) {
        actor->move_dist += actorx->speed;
    } else {
        actor->move_dist -= actorx->speed * 0.75f;
    }

    if (actor->move_dist > aSMAN_SCALE_MAX) {
        actor->move_dist = aSMAN_SCALE_MAX;
    } else if (actor->move_dist < 0.0f) {
        actor->move_dist = 0.0f;
    }

    actor->normalized_scale = actor->move_dist / aSMAN_SCALE_MAX;
    scale = actor->normalized_scale * 0.02f + 0.01f;

    if (scale > 0.03f) {
        scale = 0.03f;
    }

    actorx->scale.x = actorx->scale.y = actorx->scale.z = scale;
    actorx->shape_info.shadow_size_x = actorx->shape_info.shadow_size_z = actor->normalized_scale * 20.0f + 10.0f;
}

static void aSMAN_actor_move(ACTOR* actorx, GAME* game);
static void aSMAN_actor_draw(ACTOR* actorx, GAME* game);
