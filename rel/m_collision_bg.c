#include "m_collision_bg.h"

#include "m_field_info.h"
#include "m_name_table.h"
#include "m_actor.h"

static xyz_t mCoBG_unit_offset[mCoBG_DIRECT_NUM] = {
  {                  0.0f, 0.0f, -mFI_UNIT_BASE_SIZE_F },
  { -mFI_UNIT_BASE_SIZE_F, 0.0f,                  0.0f },
  {                  0.0f, 0.0f,  mFI_UNIT_BASE_SIZE_F },
  {  mFI_UNIT_BASE_SIZE_F, 0.0f,                  0.0f },
  { -mFI_UNIT_BASE_SIZE_F, 0.0f, -mFI_UNIT_BASE_SIZE_F },
  { -mFI_UNIT_BASE_SIZE_F, 0.0f,  mFI_UNIT_BASE_SIZE_F },
  {  mFI_UNIT_BASE_SIZE_F, 0.0f,  mFI_UNIT_BASE_SIZE_F },
  {  mFI_UNIT_BASE_SIZE_F, 0.0f, -mFI_UNIT_BASE_SIZE_F }
};

static void mCoBG_PlussDirectOffset(xyz_t* ofs_wpos, xyz_t wpos, int direct) {
  
  if (ofs_wpos != NULL && direct >= 0 && direct < mCoBG_DIRECT_NUM) {
    ofs_wpos->x = wpos.x + mCoBG_unit_offset[direct].x;
    ofs_wpos->y = wpos.y + mCoBG_unit_offset[direct].y;
    ofs_wpos->z = wpos.z + mCoBG_unit_offset[direct].z;
  }
}

static void mCoBG_SetXyz_t(xyz_t* pos, f32 x, f32 y, f32 z) {
  pos->x = x;
  pos->y = y;
  pos->z = z;
}

static void mCoBG_SetXZ(xz_t* xz, f32 x, f32 z) {
  xz->x = x;
  xz->z = z;
}

static void mCoBG_Wpos2Upos(xyz_t* upos, xyz_t wpos, int ut_x, int ut_z) {
  upos->x = wpos.x - (ut_x * mFI_UT_WORLDSIZE_X_F);
  upos->z = wpos.z - (ut_z * mFI_UT_WORLDSIZE_Z_F);

  upos->x -= mFI_UT_WORLDSIZE_HALF_X_F;
  upos->z -= mFI_UT_WORLDSIZE_HALF_Z_F;
}

static void mCoBG_Unit2UnitInfo_OutOfUnitPos(mCoBG_UnitInfo_c* unit_info, int ut_x, int ut_z) {
  mActor_name_t* item_p;

  unit_info->ut_x = ut_x;
  unit_info->ut_z = ut_z;
  unit_info->collision = mFI_UtNum2UtCol(ut_x, ut_z);
  unit_info->base_height = mFI_UtNum2BaseHeight(ut_x, ut_z);
  unit_info->leftUp_offset = unit_info->collision->data.top_left * 10.0f + unit_info->base_height;
  unit_info->leftDown_offset = unit_info->collision->data.bot_left * 10.0f + unit_info->base_height;
  unit_info->rightUp_offset = unit_info->collision->data.top_right * 10.0f + unit_info->base_height;
  unit_info->rightDown_offset = unit_info->collision->data.bot_right * 10.0f + unit_info->base_height;
  unit_info->shape = unit_info->collision->data.shape;
  unit_info->attribute = unit_info->collision->data.unit_attribute;

  item_p = mFI_UtNum2UtFG(ut_x, ut_z);

  if (item_p != NULL) {
    unit_info->item = *item_p;
  }
  else {
    unit_info->item = EMPTY_NO;
  }
}

static void mCoBG_Wpos2UnitInfo(mCoBG_UnitInfo_c* unit_info, xyz_t wpos) {
  xyz_t upos = { 0.0f, 0.0f, 0.0f };
  int ut_x;
  int ut_z;

  mFI_Wpos2UtNum(&ut_x, &ut_z, wpos);
  mCoBG_Unit2UnitInfo_OutOfUnitPos(unit_info, ut_x, ut_z);
  mCoBG_Wpos2Upos(&upos, wpos, ut_x, ut_z);
  unit_info->pos_x = upos.x;
  unit_info->pos_z = upos.z;
}


/*
Area unit triangle

0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 
1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 
1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 
1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 
1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 3 
1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 3 3 3 3 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 
1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 
1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 
1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 3 3 3 3 
1 1 1 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 3 3 3 
1 1 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 3 3 
1 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 3 

Bias towards the top and left triangles.
Top:    440
Left:   419
Bottom: 361
Right:  380

NOTE: The top of the triangle is denoted as the "bottom" by the devs as it is in the -Z direction.
*/

/* This function works on a "unit position" which is [-20.0f, 20.0f) in XZ */
static void mCoBG_GetUnitArea(mCoBG_UnitInfo_c* unit_info, s16* unit_area) {
  f32 x = unit_info->pos_x;
  f32 z = unit_info->pos_z;

  // Determine the triangle based on the x and z coordinates
  if (x < z) {
    if (z > -x) {
      unit_area[0] = mCoBG_AREA_S;
    }
    else {
      unit_area[0] = mCoBG_AREA_W;
    }
  }
  else if (z > -x) {
    unit_area[0] = mCoBG_AREA_E;
  }
  else { // z <= x && z <= -x
    unit_area[0] = mCoBG_AREA_N;
  }
}


static void mCoBG_GetGroundAngleFromVtx3(s_xyz* ground_angle, xyz_t* v0, xyz_t* v1, xyz_t* v2, s16 unit_area) {
  if (ground_angle != NULL) {
    xyz_t avg;
    f32 a0;
    f32 a1;
    
    ground_angle->y = 0;
    avg.x = 0.5f * (v1->x + v2->x);
    avg.y = 0.5f * (v1->y + v2->y);
    avg.z = 0.5f * (v1->z + v2->z);

    switch (unit_area) {
      case mCoBG_AREA_N:
      {
        a0 = v0->z - avg.z;
        a1 = v0->y - avg.y;
        ground_angle->x = atans_table(a0, -a1);

        a0 = v1->x - v2->x;
        a1 = v1->y - v2->y;
        ground_angle->z = atans_table(a0, a1);
        break;
      }

      case mCoBG_AREA_S:
      {
        a0 = avg.z - v0->z;
        a1 = -(avg.y - v0->y);
        ground_angle->x = atans_table(a0, a1);

        a0 = v2->x - v1->x;
        a1 = v2->y - v1->y;
        ground_angle->z = atans_table(a0, a1);
        break;
      }

      case mCoBG_AREA_W:
      {
        a0 = v2->z - v1->z;
        a1 = v2->y - v1->y;
        ground_angle->x = atans_table(a0, -a1);
        
        a0 = v0->x - avg.x;
        a1 = v0->y - avg.y;
        ground_angle->z = atans_table(a0, a1);
        break;
      }

      case mCoBG_AREA_E:
      {
        a0 = v1->z - v2->z;
        a1 = -(v1->y - v2->y);
        ground_angle->x = atans_table(a0, a1);

        a0 = avg.x - v0->x;
        a1 = avg.y - v0->y;
        ground_angle->z = atans_table(a0, a1);
        break;
      }
    }
  }
}

static void mCoBG_GetArea3Point(s16 area, xyz_t* v0, xyz_t* v1, xyz_t* v2, mCoBG_Collision_u* col) {
  switch (area) {
    case mCoBG_AREA_N:
    {
      v0->y = col->data.center * 10.0f;
      v1->x = mFI_UT_WORLDSIZE_HALF_X_F;
      v1->y = col->data.bot_right * 10.0f;
      v1->z = -mFI_UT_WORLDSIZE_HALF_Z_F;
      v2->x = -mFI_UT_WORLDSIZE_HALF_X_F;
      v2->y = col->data.top_left * 10.0f; /* BUG? Shouldn't this be bot_left (top = +Z, bot = -Z) of the triangle */
      v2->z = -mFI_UT_WORLDSIZE_HALF_Z_F;
      break;
    }

    case mCoBG_AREA_W:
    {
      v0->y = col->data.center * 10.0f;
      v1->x = -mFI_UT_WORLDSIZE_HALF_X_F;
      v1->y = col->data.top_left * 10.0f;
      v1->z = -mFI_UT_WORLDSIZE_HALF_Z_F;
      v2->x = -mFI_UT_WORLDSIZE_HALF_X_F;
      v2->y = col->data.bot_left * 10.0f;
      v2->z = mFI_UT_WORLDSIZE_HALF_Z_F;
      break;
    }

    case mCoBG_AREA_S:
    {
      v0->y = col->data.center * 10.0f;
      v1->x = -mFI_UT_WORLDSIZE_HALF_X_F;
      v1->y = col->data.bot_left * 10.0f;  /* BUG? Shouldn't this be top_left (top = +Z, bot = -Z) of the triangle */
      v1->z = mFI_UT_WORLDSIZE_HALF_Z_F;
      v2->x = mFI_UT_WORLDSIZE_HALF_X_F;
      v2->y = col->data.top_right * 10.0f;
      v2->z = mFI_UT_WORLDSIZE_HALF_Z_F;
      break;
    }

    case mCoBG_AREA_E:
    {
      v0->y = col->data.center * 10.0f;
      v1->x = mFI_UT_WORLDSIZE_HALF_X_F;
      v1->y = col->data.top_right * 10.0f;
      v1->z = mFI_UT_WORLDSIZE_HALF_Z_F;
      v2->x = mFI_UT_WORLDSIZE_HALF_X_F;
      v2->y = col->data.bot_right * 10.0f;
      v2->z = -mFI_UT_WORLDSIZE_HALF_Z_F;
      break;
    }
  }
}

static void mCoBG_GetNormTriangle(xyz_t* norm, s_xyz* ground_angle, mCoBG_Collision_u* col, s16 area) {
  xyz_t v0 = { 0.0f, 0.0f, 0.0f };
  xyz_t v1 = { 0.0f, 0.0f, 0.0f };
  xyz_t v2 = { 0.0f, 0.0f, 0.0f };

  mCoBG_GetArea3Point(area, &v0, &v1, &v2, col);
  mCoBG_GetNorm_By3Point(norm, &v0, &v1, &v2);
  mCoBG_GetGroundAngleFromVtx3(ground_angle, &v0, &v1, &v2, area);
}

static mCoBG_ActorInf_c l_ActorInf;

static void mCoBG_AdjustActorY(xyz_t* rev_pos, ACTOR* actor, f32 ground_y, f32 water_y, f32 ground_dist, mCoBG_CheckResult_c* check_res, mCoBG_ActorInf_c* actor_info, int check_water) {
  actor->bg_collision_check.ground_y = ground_y;

  if (check_water) {
    f32 actor_y = actor->world.position.y;
    f32 actor_foot_y = actor_y + ground_dist;
    f32 water_ground_y = (water_y - (mFI_UNIT_BASE_SIZE_F / 2.0f));

    if (water_ground_y >= actor_foot_y) {
      rev_pos->y = (water_ground_y - ground_dist) - actor_y;
      check_res->is_in_water = TRUE;
      check_res->on_ground = TRUE;
      actor->position_speed.y = 0.0f;
    }
    else if (water_y >= actor_foot_y) {
      check_res->is_in_water = TRUE;
    }
  }
  else {
    f32 actor_y = actor->world.position.y;
    f32 actor_foot_y = actor_y + ground_dist;

    if (ground_y >= actor_foot_y) {
      rev_pos->y = (ground_y - ground_dist) - actor_y;
      check_res->on_ground = TRUE;
      actor->position_speed.y = 0.0f; // stop actor from moving downward anymore
    }
    else if (actor_info->on_ground && actor_info->_48 > actor_info->_4C) {
      f32 dist_to_ground = ABS(ground_y - actor_foot_y);
      f32 xz_vel = sqrtf(actor_info->speed_xz0.x * actor_info->speed_xz0.x + actor_info->speed_xz0.z * actor_info->speed_xz0.z);

      if (dist_to_ground <= xz_vel) {
        rev_pos->y = (ground_y - ground_dist) - actor->world.position.y;
        check_res->on_ground = TRUE;
        actor->position_speed.y = 0.0f;
      }
    }
  }
}

static f32 mCoBG_GroundPolygonInfo2BgHeight(xyz_t* norm, mCoBG_UnitInfo_c* unit_info) {
  f32 dot = -(norm->y * (unit_info->collision->data.center * 10.0f)) + (norm->x * unit_info->pos_x + norm->z * unit_info->pos_z);
  return dot / -norm->y; // dot product scaled by y normal
}

static void mCoBG_GetSpeedByWpos(xz_t* speed, ACTOR* actor) {
  speed->x = actor->world.position.x - actor->last_world_position.x;
  speed->z = actor->world.position.z - actor->last_world_position.z;
}

static void mCoBG_CarryOutReverse(ACTOR* actor, xyz_t rev_pos, s16 type) {
  if (type == 0) {
    actor->world.position.x += rev_pos.x;
    actor->world.position.y += rev_pos.y;
    actor->world.position.z += rev_pos.z;
  }

  if (actor->bg_collision_check.result.unit_attribute >= mCoBG_ATTRIBUTE_WATER && actor->bg_collision_check.result.unit_attribute <= mCoBG_ATTRIBUTE_RIVER_NE) {
    xyz_t pos = actor->world.position;

    f32 water_height = mCoBG_GetWaterHeight_File(pos, __FILE__, 1303);
    if ((pos.y + l_ActorInf._44) <= water_height) {
      actor->bg_collision_check.result.is_in_water = TRUE;
    }
  }
}

static void mCoBG_InitRevpos(xyz_t* rev_pos) {
  rev_pos->x = 0.0f;
  rev_pos->y = 0.0f;
  rev_pos->z = 0.0f;
}

static void mCoBG_MakeSizeUnitInfo(mCoBG_UnitInfo_c *unit_info, int ut_x, int ut_z, s16 size) {
  int x;
  int z;
  int start_x;
  int start_z;
  int end_x;
  int end_z;
  
  start_z = ut_z - (size >> 1);
  start_x = ut_x - (size >> 1);
  end_z = start_z + size;
  end_x = start_x + size;

  for (z = start_z; z < end_z; z++) {
    for (x = start_x; x < end_x; x++) {
      mCoBG_Unit2UnitInfo_OutOfUnitPos(unit_info, x, z);
      unit_info++;
    }
  }
}


static void mCoBG_MakeTab2MoveTail(xz_t* dst_xz, xz_t* src_xz) {
  f32 x_bias = ABS(src_xz->x) / (ABS(src_xz->x) + ABS(src_xz->z));
  f32 z_bias = 1.0f - x_bias;

  if (src_xz->x > 0.0f) {
    dst_xz->x -= x_bias * 0.2f;
  }
  else if (src_xz->x < 0.0f) {
    dst_xz->x += x_bias * 0.2f;
  }

  if (src_xz->z > 0.0f) {
    dst_xz->z -= z_bias * 0.2f;
  }
  else if (src_xz->z < 0.0f) {
    dst_xz->z += z_bias * 0.2f;
  }
}

static void mCoBG_SearchAttribute(xyz_t wpos, int direct, s8* can_dig) {
  xyz_t next_ut;

  wpos.y = 0.0f;
  mCoBG_PlussDirectOffset(&next_ut, wpos, direct);
  mCoBG_Wpos2Attribute(next_ut, can_dig);
}
