#include "m_roll_lib.h"

#include "ac_snowman.h"
#include "m_collision_bg.h"
#include "m_common_data.h"
#include "m_demo.h"
#include "m_field_info.h"
#include "m_name_table.h"
#include "m_npc.h"
#include "m_play.h"
#include "m_player_lib.h"
#include "sys_matrix.h"

extern void mRlib_spdXZ_to_spdF_Angle(xyz_t* speed_vec, f32* speedf, s16* angle_y_s) {
  f32 x = speed_vec->x;
  f32 z = speed_vec->z;

  speedf[0] = sqrtf(x * x + z * z);
  angle_y_s[0] = atans_table(z, x);
}

extern void mRlib_spdF_Angle_to_spdXZ(xyz_t* speed_vec, f32* speedf, s16* angle_y_s) {
  speed_vec->x = sin_s(angle_y_s[0]) * speedf[0];
  speed_vec->z = cos_s(angle_y_s[0]) * speedf[0];
}

extern int mRlib_position_move_for_sloop(ACTOR* actor, s_xyz* slope_angle) {
  if (actor->bg_collision_check.result.on_ground && (slope_angle->x != 0 || slope_angle->z != 0)) {
    f32 x = (actor->position_speed.x * ABS(cos_s(slope_angle->z))); // duplicates cos_s call (3x)
    f32 y = actor->position_speed.y;
    f32 z = (actor->position_speed.z * ABS(cos_s(slope_angle->x))); // duplicates cos_s call (3x)
    
    actor->world.position.x += x * 0.5f + actor->status_data.collision_vec.x;
    actor->world.position.y += y * 0.5f + actor->status_data.collision_vec.y;
    actor->world.position.z += z * 0.5f + actor->status_data.collision_vec.z;

    return TRUE;
  }
  else {
    Actor_position_move(actor);
    return FALSE;
  }
}

extern int mRlib_Get_norm_Clif(ACTOR* actor, xyz_t* normal_vec) {
  s16 angles[2];

  if (mCoBG_CheckAttribute_BallRolling(angles, &actor->world.position)) {
    int i;

    for (i = 0; i < 2; i++) {
      f32 percent = mCoBG_CheckBallRollingArea(angles[i], &actor->world.position);

      if (percent > 0.0f && percent < 0.5f) {
        xyz_t rot;
        s16 angle = angles[i] + DEG2SHORT_ANGLE(90.0f);
        xyz_t pos = *normal_vec;

        rot.x = sin_s(angle);
        rot.y = 0.0f;
        rot.z = cos_s(angle);

        Matrix_RotateVector((int)DEG2SHORT_ANGLE((0.5f - percent) * 80.0f), &rot, MTX_LOAD);
        Matrix_Position(&pos, normal_vec);

        return TRUE;
      }
    }
  }

  return FALSE;
}

extern void mRlib_Roll_Matrix_to_s_xyz(ACTOR* actor, s_xyz* rot, s16 angle) {
  MtxF matrix;
  xyz_t axis;

  axis.x = cos_s(actor->world.angle.y);
  axis.z = -sin_s(actor->world.angle.y);
  axis.y = 0.0f;

  Matrix_RotateVector(angle, &axis, MTX_LOAD);
  Matrix_rotateXYZ(rot->x, rot->y, rot->z, MTX_MULT);
  Matrix_get(&matrix);
  Matrix_to_rotate2_new(&matrix, rot, MTX_LOAD);
}

extern s16 mRlib_Get_HitWallAngleY(ACTOR* actor) {
  u16 angle = actor->bg_collision_check.wall_info[0].angleY;
  u16 angle2;
  s16 median;

  /* check if only hit one wall */
  if (actor->bg_collision_check.result.hit_wall_count != 1) {
    angle2 = actor->bg_collision_check.wall_info[1].angleY;
    median = (angle + angle2) >> 1;

    if (ABS(angle - angle2) <= 0x8000) {
      return median;
    }
    else {
      median += 0x8000;
    
      return median; /* add 180 degrees */
    }
  }

  return angle;
}

extern void mRlib_Station_step_modify_to_wall(ACTOR* actor) {
  s_xyz angle;
  mCoBG_GetBgY_AngleS_FromWpos(&angle, actor->world.position, 0.0f);

  if (angle.x >= DEG2SHORT_ANGLE(45.0f)) {
    f32 z;
    
    actor->bg_collision_check.result.hit_wall |= mCoBG_HIT_WALL | mCoBG_HIT_WALL_FRONT; /* force 'collision' with a wall in front of the actor */
    z = mFI_UT_WORLDSIZE_Z_F + (f32)((int)(actor->world.position.z / mFI_UT_WORLDSIZE_Z_F) * mFI_UT_WORLDSIZE_Z); /* move to exactly one Z unit backwards (positive Z) */
    actor->bg_collision_check.wall_info[0].angleY = DEG2SHORT_ANGLE(0.0f);
    actor->bg_collision_check.result.hit_wall_count = 1;
    actor->world.position.z = z;
  }
}

extern int mRlib_Set_Position_Check(ACTOR* actor) {
  int set;
  int bx;
  int bz;
  int ut_x;
  int ut_z;

  mFI_Wpos2BkandUtNuminBlock(&bx, &bz, &ut_x, &ut_z, actor->world.position);

  /* check if the current unit is accessible by NPCs */
  set = mNpc_CheckNpcSet(bx, bz, ut_x, ut_z);
  if (set == FALSE) {
    /* Since it isn't, try searching the 3x3 grid around the center unit for available spots */
    int x_ofs;

    for (x_ofs = -1; x_ofs < 2; x_ofs++) {
      int z_ofs;

      for (z_ofs = -1; z_ofs < 2; z_ofs++) {
        if (
          (x_ofs != 0 || z_ofs != 0) &&
          (ut_x + x_ofs) < UT_X_NUM && (ut_x + x_ofs) > 0 &&
          (ut_z + z_ofs) < UT_Z_NUM && (ut_z + z_ofs) > 0
        ) {
          set = mNpc_CheckNpcSet(bx, bz, ut_x + x_ofs, ut_z + z_ofs);
        }

        if (set == TRUE) {
          /* found an accessible spot for an NPC/ACTOR, so use that */
          f32 y_save = actor->world.position.y;

          mFI_BkandUtNum2CenterWpos(&actor->world.position, bx, bz, ut_x + x_ofs, ut_z + z_ofs);
          actor->world.position.y = y_save;

          return set;
        }
      }
    }
  }

  return set;
}

extern int mRlib_HeightGapCheck_And_ReversePos(ACTOR* actor) {
  if (mFI_GetPlayerWade() == mFI_WADE_INPROGRESS && mCoBG_ExistHeightGap_KeepAndNow_Detail(actor->world.position)) {
    if (mRlib_Set_Position_Check(actor) != FALSE) {
      actor->position_speed.y = 0.0f;
    }
    else {
      /* We couldn't find a valid unit in the 3x3 grid around the ACTOR's current unit */

      int bx;
      int bz;
      int ut_x;
      int ut_z;

      mFI_Wpos2BkandUtNuminBlock(&bx, &bz, &ut_x, &ut_z, actor->world.position);

      /* Check all units in the current block for any valid spot to move our ACTOR to, and move there if found */
      if (mNpc_GetMakeUtNuminBlock_hard_area(&ut_x, &ut_z, bx, bz, 0)) {
        f32 y_save = actor->world.position.y;

        mFI_BkandUtNum2CenterWpos(&actor->world.position, bx, bz, ut_x, ut_z);
        actor->world.position.y = y_save;
        actor->position_speed.y = 0.0f;

        return TRUE;
      }

      return FALSE; /* no accessible unit in the entire block was found */
    }
  }

  return TRUE; /* ACTOR was in a good location or was moved to one in the 3x3 unit grid around them */
}

extern int mRlib_Hole_check(ACTOR* actor) {
  mActor_name_t* ut_fg_p = mFI_GetUnitFG(actor->world.position); // item underneath where the actor is

  if (ut_fg_p != NULL && ((ut_fg_p[0] >= HOLE_START && ut_fg_p[0] <= HOLE_END) || ut_fg_p[0] == HOLE_SHINE)) {
    return TRUE; // a hole item is under the actor
  }
  
  return FALSE; // item under the actor isn't a hole
}

extern int mRlib_Get_ground_norm_inHole(ACTOR* actor, xyz_t* normal, f32* dist, s16* angle_y, s16* angle_rate, f32 rate_mod) {
  if (mRlib_Hole_check(actor) != FALSE) {
    xyz_t center_pos;

    mFI_Wpos2UtCenterWpos(&center_pos, actor->world.position);
    dist[0] = search_position_distance(&actor->world.position, &center_pos); // distance to center of hole
    angle_rate[0] = DEG2SHORT_ANGLE((dist[0] * 90.0f) * 0.0325f);
    angle_rate[0] = (int)(angle_rate[0] * rate_mod);
    angle_y[0] = atans_table(actor->world.position.z - center_pos.z, actor->world.position.x - center_pos.x);
    
    normal->x = (-cos_s(angle_rate[0])) * sin_s(angle_y[0]);
    normal->y = -sin_s(angle_rate[0]);
    normal->z = (-cos_s(angle_rate[0])) * cos_s(angle_y[0]);
    
    return TRUE;
  }
  else {
    dist[0] = 0.0f;

    return FALSE;
  }
}

static int mRlib_PSnowmanTouchCheck(const xyz_t* wpos) {
  if (
    ABS(wpos->x) < mFI_UT_WORLDSIZE_X_F &&
    ABS(wpos->z) < mFI_UT_WORLDSIZE_Z_F &&
    ABS(wpos->y) < mFI_UNIT_BASE_SIZE_F
  ) {
    return TRUE;
  }

  return FALSE;
}

extern int mRlib_PSnowmanBreakCheck(ACTOR* actor, GAME_PLAY* play, f32* speed) {
  PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);
  f32 actor_y_pos_save = actor->world.position.y;
  xyz_t pos_diff;
  
  /* Move actor to ground level for calc */
  actor->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(actor->world.position, 0.0f);
  xyz_t_sub(&actor->world.position, &player->actor_class.world.position, &pos_diff);
  actor->world.position.y = actor_y_pos_save; // restore y position after calculation

  if (mRlib_PSnowmanTouchCheck(&pos_diff)) {    
    if (Math3d_normalizeXyz_t(&pos_diff)) {
      xyz_t player_speed = player->actor_class.position_speed;
      f32 sq_dist = pos_diff.x * player_speed.x + pos_diff.z * player_speed.z;

      if (sq_dist > 0.0f) {
        speed[0] += sq_dist * 0.5f;
      }
      else {
        add_calc0(speed, 1.0f - sqrtf(0.7), 10.0f);
      }

      if (speed[0] > 200.0f) {
        return TRUE;
      }
    }
    else {
      add_calc0(speed, 1.0f - sqrtf(0.7), 10.0f);
    }
  }
  else {
    add_calc0(speed, 1.0f - sqrtf(0.7), 10.0f);
  }

  return FALSE;
}

extern int mRlib_PSnowmanBreakNeckSwing(s16* head_angle_y, f32 f0, f32 scale) {
  if (f0 > 20.0f) {
    s16 rot_x;
    s16 rot_z;
    s16 angle;

    head_angle_y[0] += (s16)((f0 * 40.0f) * 0.5f);
    angle = head_angle_y[0] & 0x7000;
    rot_x = (f0 * 4.5f) * sin_s(angle);
    rot_z = (f0 * 4.5f) * cos_s(angle);

    Matrix_translate(0.0f, scale * -1400.0f, 0.0f, MTX_MULT); // move to neck location?
    Matrix_rotateXYZ(rot_x, 0, rot_z, MTX_MULT); // rotate at location
    Matrix_translate(0.0f, scale * 1400.0f, 0.0f, MTX_MULT); // restore original location
  }
}

extern int mRlib_PSnowman_NormalTalk(ACTOR* actor, GAME_PLAY* play, f32* speed, mDemo_REQUEST_PROC demo_req_proc) {
  if (mDemo_Check(mDemo_TYPE_TALK, actor) == FALSE) {
    f32 actor_y_save;

    /* Don't talk if the snowman broke */
    if (mRlib_PSnowmanBreakCheck(actor, play, speed) != FALSE) {
      return FALSE;
    }

    /* Update actor position temporarily */
    actor_y_save = actor->world.position.y;
    actor->world.position.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, actor->world.position, 0.0f);
    mDemo_Request(mDemo_TYPE_TALK, actor, demo_req_proc);
    actor->world.position.y = actor_y_save; // restore original Y position
  }
  else {
    add_calc0(speed, 1.0f - sqrtf(0.7), 10.0f);
  }

  return TRUE;
}

extern int mRlib_snowman_ball_unit_check_from_pos(GAME_PLAY* play, const xyz_t* wpos) {
  ACTOR* actor;

  /* Search out snowman actor & check distance to any found */
  for (actor = play->actor_info.list[ACTOR_PART_BG].actor; actor != NULL; actor = actor->next_actor) {
    if (actor->id == mAc_PROFILE_SNOWMAN) {
      xyz_t diff;
      SNOWMAN_ACTOR* snowman = (SNOWMAN_ACTOR*)actor;
      xyz_t* snowman_pos = &snowman->actor_class.world.position;
      f32 max_dist = MIN(snowman->normalized_scale * 20.0f + 10.0f, 19.0f);

      xyz_t_sub(snowman_pos, wpos, &diff);

      max_dist += 19.0f;

      if (Math3DVecLengthSquare2D(diff.x, diff.z) < max_dist * max_dist) {
        return TRUE;
      }
    }
  }

  /* If a snowman actor doesn't exist, try using the ball position */
  if (Common_Get(ball_pos).x != 0.0f || Common_Get(ball_pos).y != 0.0f || Common_Get(ball_pos).z != 0.0f) {
    xyz_t diff;
    f32 max_dist = 20.0f;

    xyz_t_sub(Common_GetPointer(ball_pos), wpos, &diff);
    max_dist += 19.0f;

    if (Math3DVecLengthSquare2D(diff.x, diff.z) < max_dist * max_dist) {
      return TRUE;
    }
  }

  return FALSE;
}
