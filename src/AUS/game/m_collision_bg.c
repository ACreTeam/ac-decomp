#include "m_collision_bg.h"

#include "m_field_info.h"
#include "m_name_table.h"
#include "m_actor.h"
#include "libultra/libultra.h"
#include "m_common_data.h"
#include "m_random_field.h"
#include "sys_matrix.h"

typedef struct {
    xyz_t pos;
    f32 height;
    f32 radius;
    s16 atr_wall;
    int ux;
    int uz;
} mCoBG_column_c;

typedef struct {
    f32 start_top;
    f32 start_btm;
    f32 end_top;
    f32 end_btm;
 }mCoBG_WallBounds_c;

typedef struct {
    f32 start[2];
    f32 end[2];
    mCoBG_WallBounds_c wall_bounds;
    f32 normal[2];
    s16 normal_angle;
    u8 wall_name;
    mCoBG_bg_regist_c* regist_p;
    u8 atr_wall;
} mCoBG_unit_vec_info_c;

typedef struct {
    f32 start[2];
    f32 end[2];
} mCoBG_angle_vec_info_c;

#define mCoBG_UNIT_VEC_INFO_MAX 128

typedef struct {
    int unit_count;
    mCoBG_unit_vec_info_c unit[mCoBG_UNIT_VEC_INFO_MAX];
    int col_count;
    mCoBG_column_c column[16];
    mCoBG_angle_vec_info_c angle_vec;
} mCoBG_vec_info_c;

typedef struct {
    f32 t0;
    f32 t1;
} mCoBG_tab_c;

static mCoBG_tab_c mCoBG_tab_data[] = { { 5.0f, 10.0f }, { 0.000001f, 0.000002f } };

static mCoBG_vec_info_c l_VecInf;
static mCoBG_ActorInf_c l_ActorInf;
static mCoBG_mBgMgr_c l_mBgMgr;

static void mCoBG_SetMoveBgContactSide(mCoBG_bg_regist_c* regist_p, ACTOR* actorx, s16 angle);
static void mCoBG_MakeUnitVector(mCoBG_vec_info_c* vec_info, mCoBG_UnitInfo_c* ut_info, s16 unit_count, u8 check_type, s16 atr_wall, s16 old_on_ground, s16 old_in_water);
static void mCoBG_MakeMoveBgVector(mCoBG_vec_info_c* vec_info, mCoBG_mBgMgr_c* mbg_mgr, const xyz_t* pos, u8 check_type);
static void mCoBG_MakeColumnCollisionData(mCoBG_column_c* column, int* column_count, mCoBG_UnitInfo_c* ut_info, int unit_count, int old_on_ground, mCoBG_COLUMN_CHECK_ITEM_TYPE_PROC check_item_proc, int start, int end);
static void mCoBG_MakeCircleDefenceWall(mCoBG_ActorInf_c* actor_info, s16 attr_wall);
static void mCoBG_ColumnWallCheck(xyz_t* rev, mCoBG_ActorInf_c* actor_info, const xyz_t* pos, mCoBG_column_c* column, int column_count, s16 atr_wall);
static f32 mCoBG_GetBGHeight_Column(const xyz_t* pos, mCoBG_UnitInfo_c* unit_info);
static void mCoBG_MoveBgGroundCheck(xyz_t* rev_pos, mCoBG_ActorInf_c* actor_info, ACTOR* actorx, mCoBG_CheckResult_c* result, s_xyz* angle);

static u8 mCoBG_bridge_search_water[] = { 3, 6, 12, 9, 240, 1, 8, 2, 4, 3, 6, 12, 9 };
static u8 mCoBG_grass3_search_water[] = { 3, 6, 12, 9 };

typedef struct {
    s16 norm_angle;
    f32 norm[2];
    u8 wall_name;
} mCoBG_forbid_vec_data_c;

static mCoBG_forbid_vec_data_c mCoBG_make_vector_table[] = {
    {DEG2SHORT_ANGLE2(0.0f), {0.0f, 1.0f}, mCoBG_WALL_UP},
    {DEG2SHORT_ANGLE2(-90.0f), {-1.0f, 0.0f}, mCoBG_WALL_RIGHT},
    {DEG2SHORT_ANGLE2(90.0f), {1.0f, 0.0f}, mCoBG_WALL_LEFT},
    {DEG2SHORT_ANGLE2(180.0f), {0.0f, -1.0f}, mCoBG_WALL_DOWN},
    {DEG2SHORT_ANGLE2(45.0f), {SQRT_OF_2_DIV_2, SQRT_OF_2_DIV_2}, mCoBG_WALL_SLATE_UP},
    {DEG2SHORT_ANGLE2(135.0f), {SQRT_OF_2_DIV_2, -SQRT_OF_2_DIV_2}, mCoBG_WALL_SLATE_DOWN},
    {DEG2SHORT_ANGLE2(225.0f), {-SQRT_OF_2_DIV_2, -SQRT_OF_2_DIV_2}, mCoBG_WALL_SLATE_UP},
    {DEG2SHORT_ANGLE2(315.0f), {-SQRT_OF_2_DIV_2, SQRT_OF_2_DIV_2}, mCoBG_WALL_SLATE_DOWN},
};

static s16 mCoBG_forbid_vector_idx[][2] = {
   {4, -1}, {5, -1}, {6, -1}, {7, -1}, {-1, -1}, {0, -1}, {1, -1}, {2, -1},
   {3, -1}, {3, -1}, {6, -1}, {5, -1}, {4, -1}, {5, -1}, {6, -1}, {7, -1},
   {0, -1}, {1, -1}, {2, -1}, {3, -1}, {0, -1}, {1, -1}, {2, -1}, {3, -1},
   {0, 2}, {3, 2}, {3, 1}, {0, 1}, {4, -1}, {5, -1}, {6, -1}, {7, -1},
   {0, 2}, {3, 2}, {3, 1}, {0, 1},
};

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

static void mCoBG_SetXZ(f32* xz, f32 x, f32 z) {
  xz[0] = x;
  xz[1] = z;
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
  unit_info->rightDown_offset = unit_info->collision->data.bot_right * 10.0f + unit_info->base_height;
  unit_info->rightUp_offset = unit_info->collision->data.top_right * 10.0f + unit_info->base_height;
  unit_info->slate_flag = unit_info->collision->data.slate_flag;
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
  unit_info->unit_pos[0] = upos.x;
  unit_info->unit_pos[1] = upos.z;
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
  f32 x = unit_info->unit_pos[0];
  f32 z = unit_info->unit_pos[1];

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


static void mCoBG_GetGroundAngleFromVtx3(s_xyz* ground_angle, f32* v0, f32* v1, f32* v2, s16 unit_area) {
  if (ground_angle != NULL) {
    xyz_t avg;
    f32 a0;
    f32 a1;
    
    ground_angle->y = 0;
    avg.x = 0.5f * (v1[0] + v2[0]);
    avg.y = 0.5f * (v1[1] + v2[1]);
    avg.z = 0.5f * (v1[2] + v2[2]);

    switch (unit_area) {
      case mCoBG_AREA_N:
      {
        a0 = v0[2] - avg.z;
        a1 = v0[1] - avg.y;
        ground_angle->x = atans_table(a0, -a1);

        a0 = v1[0] - v2[0];
        a1 = v1[1] - v2[1];
        ground_angle->z = atans_table(a0, a1);
        break;
      }

      case mCoBG_AREA_S:
      {
        a0 = avg.z - v0[2];
        a1 = -(avg.y - v0[1]);
        ground_angle->x = atans_table(a0, a1);

        a0 = v2[0] - v1[0];
        a1 = v2[1] - v1[1];
        ground_angle->z = atans_table(a0, a1);
        break;
      }

      case mCoBG_AREA_W:
      {
        a0 = v2[2] - v1[2];
        a1 = v2[1] - v1[1];
        ground_angle->x = atans_table(a0, -a1);
        
        a0 = v0[0] - avg.x;
        a1 = v0[1] - avg.y;
        ground_angle->z = atans_table(a0, a1);
        break;
      }

      case mCoBG_AREA_E:
      {
        a0 = v1[2] - v2[2];
        a1 = -(v1[1] - v2[1]);
        ground_angle->x = atans_table(a0, a1);

        a0 = avg.x - v0[0];
        a1 = avg.y - v0[1];
        ground_angle->z = atans_table(a0, a1);
        break;
      }
    }
  }
}

static void mCoBG_GetArea3Point(s16 area, f32* v0, f32* v1, f32* v2, mCoBG_Collision_u* col) {
  switch (area) {
    case mCoBG_AREA_N:
    {
      v0[1] = col->data.center * 10.0f;
      v1[0] = mFI_UT_WORLDSIZE_HALF_X_F;
      v1[1] = col->data.top_right * 10.0f;
      v1[2] = -mFI_UT_WORLDSIZE_HALF_Z_F;
      v2[0] = -mFI_UT_WORLDSIZE_HALF_X_F;
      v2[1] = col->data.top_left * 10.0f; /* BUG? Shouldn't this be bot_left (top = +Z, bot = -Z) of the triangle */
      v2[2] = -mFI_UT_WORLDSIZE_HALF_Z_F;
      break;
    }

    case mCoBG_AREA_W:
    {
      v0[1] = col->data.center * 10.0f;
      v1[0] = -mFI_UT_WORLDSIZE_HALF_X_F;
      v1[1] = col->data.top_left * 10.0f;
      v1[2] = -mFI_UT_WORLDSIZE_HALF_Z_F;
      v2[0] = -mFI_UT_WORLDSIZE_HALF_X_F;
      v2[1] = col->data.bot_left * 10.0f;
      v2[2] = mFI_UT_WORLDSIZE_HALF_Z_F;
      break;
    }

    case mCoBG_AREA_S:
    {
      v0[1] = col->data.center * 10.0f;
      v1[0] = -mFI_UT_WORLDSIZE_HALF_X_F;
      v1[1] = col->data.bot_left * 10.0f;  /* BUG? Shouldn't this be top_left (top = +Z, bot = -Z) of the triangle */
      v1[2] = mFI_UT_WORLDSIZE_HALF_Z_F;
      v2[0] = mFI_UT_WORLDSIZE_HALF_X_F;
      v2[1] = col->data.bot_right * 10.0f;
      v2[2] = mFI_UT_WORLDSIZE_HALF_Z_F;
      break;
    }

    case mCoBG_AREA_E:
    {
      v0[1] = col->data.center * 10.0f;
      v1[0] = mFI_UT_WORLDSIZE_HALF_X_F;
      v1[1] = col->data.bot_right * 10.0f;
      v1[2] = mFI_UT_WORLDSIZE_HALF_Z_F;
      v2[0] = mFI_UT_WORLDSIZE_HALF_X_F;
      v2[1] = col->data.top_right * 10.0f;
      v2[2] = -mFI_UT_WORLDSIZE_HALF_Z_F;
      break;
    }
  }
}

static void mCoBG_GetNormTriangle(xyz_t* norm, s_xyz* ground_angle, mCoBG_Collision_u* col, s16 area) {
  f32 v0[3] = { 0.0f, 0.0f, 0.0f };
  f32 v1[3] = { 0.0f, 0.0f, 0.0f };
  f32 v2[3] = { 0.0f, 0.0f, 0.0f };

  mCoBG_GetArea3Point(area, v0, v1, v2, col);
  mCoBG_GetNorm_By3Point(norm, v0, v1, v2);
  mCoBG_GetGroundAngleFromVtx3(ground_angle, v0, v1, v2, area);
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
    else if (actor_info->old_on_ground && actor_info->old_ground_y > actor_info->ground_y) {
      f32 dist_to_ground = ABS(ground_y - actor_foot_y);
      f32 xz_vel = sqrtf(SQ(actor_info->speed_xz0[0]) + SQ(actor_info->speed_xz0[1]));

      if (dist_to_ground <= xz_vel) {
        rev_pos->y = (ground_y - ground_dist) - actor->world.position.y;
        check_res->on_ground = TRUE;
        actor->position_speed.y = 0.0f;
      }
    }
  }
}

static f32 mCoBG_GroundPolygonInfo2BgHeight(xyz_t* norm, mCoBG_UnitInfo_c* unit_info) {
  f32 dot = -(norm->y * (unit_info->collision->data.center * 10.0f)) + (norm->x * unit_info->unit_pos[0] + norm->z * unit_info->unit_pos[1]);
  return dot / -norm->y; // dot product scaled by y normal
}

static void mCoBG_GetSpeedByWpos(f32* speed, ACTOR* actor) {
  speed[0] = actor->world.position.x - actor->last_world_position.x;
  speed[1] = actor->world.position.z - actor->last_world_position.z;
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
    if ((pos.y + l_ActorInf.ground_dist) <= water_height) {
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


static void mCoBG_MakeTab2MoveTail(f32* dst_xz, f32* src_xz) {
  f32 x_bias = ABS(src_xz[0]) / (ABS(src_xz[0]) + ABS(src_xz[1]));
  f32 z_bias = 1.0f - x_bias;

  if (src_xz[0] > 0.0f) {
    dst_xz[0] -= x_bias * 0.2f;
  }
  else if (src_xz[0] < 0.0f) {
    dst_xz[0] += x_bias * 0.2f;
  }

  if (src_xz[1] > 0.0f) {
    dst_xz[1] -= z_bias * 0.2f;
  }
  else if (src_xz[1] < 0.0f) {
    dst_xz[1] += z_bias * 0.2f;
  }
}

static u32 mCoBG_SearchAttribute(xyz_t wpos, int direct, s8* cant_dig) {
  xyz_t next_ut;

  wpos.y = 0.0f;
  mCoBG_PlussDirectOffset(&next_ut, wpos, direct);
  return mCoBG_Wpos2Attribute(next_ut, cant_dig);
}

static void mCoBG_RegistCollisionWallInfo(mCoBG_ActorInf_c* actor_inf, mCoBG_WallInfo_c* wall_info, mCoBG_WallHeight_c* wall_height, s16 angle_y, s16 atr) {
    int i;
    int count;
    
    if (wall_height != NULL) {
        actor_inf->wall_height = *wall_height;
    }

    count = 0;
    for (i = 0; i < mCoBG_WALL_COL_NUM; i++) {
        if (angle_y == wall_info[i].angleY) {
            count++;
        }
    }

    if (count == 0) {
        for (i = 0; i < mCoBG_WALL_COL_NUM; i++) {
            if (wall_info[i].angleY == 0xB6) {
                wall_info[i].angleY = angle_y;
                wall_info[i].type = atr;
                break;
            }
        }
    }
}

#include "../src/AUS/game/m_collision_bg_wall.c_inc"
#include "../src/AUS/game/m_collision_bg_move.c_inc"
#include "../src/AUS/game/m_collision_bg_column.c_inc"

static int mCoBG_JudgeWallFromVector(f32* speed, f32* normal) {
    f32 y = mCoBG_Get2VectorAngleF(speed, normal, mCoBG_UNIT_DEGREE);

    if (ABS(y) > 89.5f) {
        return TRUE;
    }

    return FALSE;
}

static int mCoBG_RoughCheckWallHeight(f32 bot_y, mCoBG_WallBounds_c* bounds) {
    f32 y = bot_y + 3.0f;

    if (y <= bounds->start_top || y <= bounds->end_top) {
        return TRUE;
    }

    return FALSE;
}

static void mCoBG_GetWallHeight(mCoBG_WallHeight_c* wall_height, mCoBG_unit_vec_info_c* unit_vec, f32* point) {
    mCoBG_WallBounds_c* bounds = &unit_vec->wall_bounds;
    f32* start = unit_vec->start;
    f32* end = unit_vec->end;
    f32 cross[2];

    if (mCoBG_GetCrossLineAndPerpendicular(cross, unit_vec->start, unit_vec->end, point)) {
        xyz_t vec;
        f32 p;
        f32 t;
        
        vec.x = end[0] - start[0];
        vec.z = end[1] - start[1];

        if (F32_IS_ZERO(vec.x)) {
            p = (cross[1] - start[1]) / vec.z;
        } else {
            p = (cross[0] - start[0]) / vec.x;
        }

        // not sure what's up the need for 't' on z but not on x
        vec.x = bounds->end_top - bounds->start_top;
        vec.x *= p;
        wall_height->top = bounds->start_top + vec.x;

        t = bounds->start_btm;
        vec.z = bounds->end_btm - t;
        vec.z *= p;
        wall_height->bot = t + vec.z;
    }
}

static int mCoBG_CheckHeightExactly(mCoBG_WallHeight_c* wall_height, f32 pos_y, mCoBG_unit_vec_info_c* unit_vec, f32* point) {
    mCoBG_WallBounds_c* bounds = &unit_vec->wall_bounds;
    f32* start = unit_vec->start;
    f32* end = unit_vec->end;
    f32 div;

    if (unit_vec->regist_p != NULL) {
        wall_height->top = bounds->end_top;
        wall_height->bot = bounds->end_btm;

        if (pos_y + 3.0f <= wall_height->top) {
            return TRUE;
        }
    } else {
        switch(unit_vec->wall_name) {
            case mCoBG_WALL_LEFT:
            case mCoBG_WALL_RIGHT:
                div = end[1] - start[1];
                if (!F32_IS_ZERO(div)) {
                    wall_height->top = bounds->start_top + (point[1] - start[1]) * ((bounds->end_top - bounds->start_top) / (end[1] - start[1]));
                    wall_height->bot = bounds->start_btm + (point[1] - start[1]) * ((bounds->end_btm - bounds->start_btm) / (end[1] - start[1]));

                    if (pos_y + 3.0f <= wall_height->top) {
                        return TRUE;
                    }
                }
                break;
            case mCoBG_WALL_UP:
            case mCoBG_WALL_DOWN:
                div = end[0] - start[0];
                if (!F32_IS_ZERO(div)) {
                    wall_height->top = bounds->start_top + (point[0] - start[0]) * ((bounds->end_top - bounds->start_top) / (end[0] - start[0]));
                    wall_height->bot = bounds->start_btm + (point[0] - start[0]) * ((bounds->end_btm - bounds->start_btm) / (end[0] - start[0]));

                    if (pos_y + 3.0f <= wall_height->top) {
                        return TRUE;
                    }
                }
                break;
            case mCoBG_WALL_SLATE_UP:
            case mCoBG_WALL_SLATE_DOWN:
                mCoBG_GetWallHeight(wall_height, unit_vec, point);
                if (pos_y + 3.0f <= wall_height->top) {
                    return TRUE;
                }
                break;
        }
    }

    return FALSE;
}

static int mCoBG_SearchWallFront(f32* point, mCoBG_unit_vec_info_c* unit_vec) {
    return mCoBG_GetPointInfoFrontLine(unit_vec->start, point, unit_vec->normal);
}

static int mCoBG_Check45Angle(s16 angle0, s16 angle1) {
    if (ABS(angle1 - angle0) <= (u16)DEG2SHORT_ANGLE(45.0f) || ABS(angle1 - angle0) >= (u16)(DEG2SHORT_ANGLE(-45.0f) - 1)) {
        return TRUE;
    }

    return FALSE;
}

static void mCoBG_RegistWallCount(mCoBG_CheckResult_c* col_res, mCoBG_WallInfo_c* info, s16 angle) {
    int i;
    u32 count;

    count = 0;
    for (i = 0; i < mCoBG_WALL_COL_NUM; i++) {
        if (info[i].angleY != 0xB6) {
            count++;
        }
    }

    col_res->hit_wall_count = count;
    if (count == 2) {
        f32 r0 = SHORT2RAD_ANGLE2(info[0].angleY);
        f32 x0 = sinf_table(r0);
        f32 z0 = cosf_table(r0);
        f32 r1 = SHORT2RAD_ANGLE2(info[1].angleY);
        f32 x1 = sinf_table(r1);
        f32 z1 = cosf_table(r1);
        s16 avg_angle = atans_table((z0 + z1) * 0.5f, (x0 + x1) * 0.5f);

        if (mCoBG_Check45Angle((DEG2SHORT_ANGLE2(180.0f)-1) + avg_angle, angle)) {
            col_res->unk_flag4 = TRUE;
        }
    }
}

static void mCoBG_MakeHitWallFalg(mCoBG_CheckResult_c* col_res, mCoBG_WallInfo_c* wall_info) {
    int i;

    for (i = 0; i < mCoBG_WALL_COL_NUM; i++) {
        switch (wall_info[i].type) {
            case mCoBG_WALL_TYPE0:
                col_res->hit_wall |= mCoBG_HIT_WALL;
                break;
            case mCoBG_WALL_TYPE1:
                col_res->hit_attribute_wall |= mCoBG_HIT_WALL;
                break;
        }
    }
}

static void mCoBG_SearchColOwnPart(s16 actor_angleY, s16 wall_angleY, mCoBG_Check_c* check_p, s16 wall_type) {
    if (mCoBG_Check45Angle((wall_angleY + DEG2SHORT_ANGLE2(180.0f)-1), actor_angleY)) {
        if (wall_type == mCoBG_WALL_TYPE0) {
            check_p->result.hit_wall |= mCoBG_HIT_WALL_FRONT;
            check_p->in_front_wall_angle_y = wall_angleY;
            check_p->result.unk_flag4 = TRUE;
        } else {
            check_p->result.hit_attribute_wall |= mCoBG_HIT_WALL_FRONT;
            check_p->in_front_wall_angle_y = wall_angleY;
            check_p->result.unk_flag4 = TRUE;
        }
    } else if (mCoBG_Check45Angle((wall_angleY + DEG2SHORT_ANGLE2(-90.0f)), actor_angleY)) {
        if (wall_type == mCoBG_WALL_TYPE0) {
            check_p->result.hit_wall |= mCoBG_HIT_WALL_RIGHT;
        } else {
            check_p->result.hit_attribute_wall |= mCoBG_HIT_WALL_RIGHT;
        }
    } else if (mCoBG_Check45Angle((wall_angleY + DEG2SHORT_ANGLE2(90.0f)), actor_angleY)) {
        if (wall_type == mCoBG_WALL_TYPE0) {
            check_p->result.hit_wall |= mCoBG_HIT_WALL_LEFT;
        } else {
            check_p->result.hit_attribute_wall |= mCoBG_HIT_WALL_LEFT;
        }
    } else if (mCoBG_Check45Angle(wall_angleY, actor_angleY)) {
        if (wall_type == mCoBG_WALL_TYPE0) {
            check_p->result.hit_wall |= mCoBG_HIT_WALL_BACK;
        } else {
            check_p->result.hit_attribute_wall |= mCoBG_HIT_WALL_BACK;
        }
    }
}

static void mCoBG_MakePartDirectHitWallFlag(ACTOR* actorx) {
    mCoBG_Check_c* check_p = &actorx->bg_collision_check;
    int count = check_p->result.hit_wall_count;
    s16 wall_angleY;
    s16 wall_type;
    s16 actor_angleY = actorx->shape_info.rotation.y;
    int i;

    if (check_p->result.hit_wall != mCoBG_DIDNT_HIT_WALL || check_p->result.hit_attribute_wall != mCoBG_DIDNT_HIT_WALL) {
        for (i = 0; i < count; i++) {
            wall_angleY = check_p->wall_info[i].angleY;
            wall_type = check_p->wall_info[i].type;
            mCoBG_SearchColOwnPart(actor_angleY, wall_angleY, check_p, wall_type);
        }
    }

    if (count == 2) {
        u16 dangle = check_p->wall_info[0].angleY - check_p->wall_info[1].angleY;

        if (dangle > (DEG2SHORT_ANGLE2(180.0f)-3) && dangle < (DEG2SHORT_ANGLE2(180.0f)+3)) {
            check_p->result.unk_flag2 = TRUE;
        }

        if (check_p->wall_info[0].type == mCoBG_WALL_TYPE0 && check_p->wall_info[1].type == mCoBG_WALL_TYPE0 && dangle < DEG2SHORT_ANGLE2(67.5f)) {
            check_p->result.unk_flag2 = TRUE;
        }
    }
}

enum {
    mCoBG_WALL_KIND_NORMAL,
    mCoBG_WALL_KIND_ATTRIBUTE,
    mCoBG_WALL_KIND_MOVE,

    mCoBG_WALL_KIND_NUM
};

static s16 mCoBG_GetWallKind(mCoBG_unit_vec_info_c* unit_vec) {
    if (unit_vec->regist_p != NULL) {
        return mCoBG_WALL_KIND_MOVE;
    }

    if (unit_vec->atr_wall) {
        return mCoBG_WALL_KIND_ATTRIBUTE;
    }

    return mCoBG_WALL_KIND_NORMAL;
}

static void mCoBG_Cross2Reverse_NormalWall(f32* reverse, mCoBG_unit_vec_info_c* unit_vec, f32* actor_start, f32* actor_end, mCoBG_ActorInf_c* actor_inf, ACTOR* actorx) {

    if (mCoBG_RoughCheckWallHeight(actor_inf->old_ground_y - 5.0f, &unit_vec->wall_bounds)) {
        mCoBG_WallHeight_c height;

        if (mCoBG_CheckHeightExactly(&height, actor_inf->old_ground_y - 5.0f, unit_vec, actor_start)) {
            if (mCoBG_GetCrossJudge_2Vector(actor_start, actor_end, unit_vec->start, unit_vec->end)) {
                f32 dist;
                f32 rev_dist;

                mCoBG_GetDistPointAndLine2D_Norm(&dist, unit_vec->start, unit_vec->end, unit_vec->normal, actor_end);
                rev_dist = actor_inf->range + dist + 0.00001f;

                reverse[0] = unit_vec->normal[0] * rev_dist;
                reverse[1] = unit_vec->normal[1] * rev_dist;
                mCoBG_RegistCollisionWallInfo(actor_inf, actor_inf->wall_info, &height, unit_vec->normal_angle, unit_vec->atr_wall);
                if (unit_vec->regist_p != NULL) {
                    mCoBG_SetMoveBgContactSide(unit_vec->regist_p, actorx, unit_vec->normal_angle);
                }
            }
        }
    }
}

static void mCoBG_Cross2Reverse_AttributeWall(f32* reverse, mCoBG_unit_vec_info_c* unit_vec, f32* actor_start, f32* actor_end, mCoBG_ActorInf_c* actor_inf, ACTOR* actorx) {
    if (mCoBG_GetCrossJudge_2Vector(actor_start, actor_end, unit_vec->start, unit_vec->end)) {
        f32 cross[2];
        
        mCoBG_GetCross2Line(cross, actor_start, actor_end, unit_vec->start, unit_vec->end);
        reverse[0] = cross[0] - actor_end[0];
        reverse[1] = cross[1] - actor_end[1];
        mCoBG_RegistCollisionWallInfo(actor_inf, actor_inf->wall_info, NULL, unit_vec->normal_angle, unit_vec->atr_wall);
    }
}

typedef void (*mCoBG_CROSS_REV_PROC)(f32* reverse, mCoBG_unit_vec_info_c* unit_vec, f32* actor_start, f32* actor_end, mCoBG_ActorInf_c* actor_inf, ACTOR* actorx);

static void mCoBG_Cross2Reverse(f32* reverse, mCoBG_unit_vec_info_c* unit_vec, int unit, f32* actor_start, f32* actor_end, mCoBG_ActorInf_c* actor_info, ACTOR* actorx) {
    f32 speed[2];

    speed[0] = actor_end[0] - actor_start[0];
    speed[1] = actor_end[1] - actor_start[1];

    if (mCoBG_GetPointInfoFrontLine(unit_vec->start, actor_start, unit_vec->normal) && mCoBG_JudgeWallFromVector(speed, unit_vec->normal)) {
        static mCoBG_CROSS_REV_PROC cross_rev_proc[] = { &mCoBG_Cross2Reverse_NormalWall, &mCoBG_Cross2Reverse_AttributeWall, &mCoBG_Cross2Reverse_NormalWall };
        s16 kind = mCoBG_GetWallKind(unit_vec);

        (*cross_rev_proc[kind])(reverse, unit_vec, actor_start, actor_end, actor_info, actorx);
    }
}

static int mCoBG_Distance2Reverse_NormalWall(f32* reverse, mCoBG_unit_vec_info_c* unit_vec, f32* actor_start, f32* actor_end, mCoBG_ActorInf_c* actor_info, ACTOR* actorx) {
    f32 dist;

    if (mCoBG_GetDistPointAndLine2D_Norm(&dist, unit_vec->start, unit_vec->end, unit_vec->normal, actor_end)) {
        mCoBG_WallHeight_c height;

        if (dist < actor_info->range) {

            if (mCoBG_RoughCheckWallHeight(actor_info->old_ground_y - 5.0f, &unit_vec->wall_bounds) && mCoBG_CheckHeightExactly(&height, actor_info->old_ground_y - 5.0f, unit_vec, actor_end)) {
                f32 rev_dist = (actor_info->range - dist) + 0.00001f;

                reverse[0] = unit_vec->normal[0] * rev_dist;
                reverse[1] = unit_vec->normal[1] * rev_dist;
                mCoBG_RegistCollisionWallInfo(actor_info, actor_info->wall_info, &height, unit_vec->normal_angle, unit_vec->atr_wall);

                if (unit_vec->regist_p != NULL) {
                    mCoBG_SetMoveBgContactSide(unit_vec->regist_p, actorx, unit_vec->normal_angle);
                }

                return TRUE;
            }
        } else if (ABS(dist - actor_info->range) < 2.7f && mCoBG_RoughCheckWallHeight(actor_info->old_ground_y - 5.0f, &unit_vec->wall_bounds) && mCoBG_CheckHeightExactly(&height, actor_info->old_ground_y - 5.0f, unit_vec, actor_end)) {
            mCoBG_RegistCollisionWallInfo(actor_info, actor_info->wall_info, &height, unit_vec->normal_angle, unit_vec->atr_wall);

            if (unit_vec->regist_p != NULL) {
                mCoBG_SetMoveBgContactSide(unit_vec->regist_p, actorx, unit_vec->normal_angle);
            }

            return TRUE;
        }
    }

    return FALSE;
}

static void mCoBG_GetSpecialDistanceReverse(f32* reverse, f32* actor_end, mCoBG_unit_vec_info_c* unit_vec, f32* cross0, f32* cross1, f32* edge) {
    if (!mCoBG_GetPointInfoFrontLine(unit_vec->start, cross0, unit_vec->normal)) {
        reverse[0] = edge[0] - cross0[0];
        reverse[1] = edge[1] - cross0[1];
    } else if (!mCoBG_GetPointInfoFrontLine(unit_vec->start, cross1, unit_vec->normal)) {
        reverse[0] = edge[0] - cross1[0];
        reverse[1] = edge[1] - cross1[1];
    }
}

static int mCoBG_CheckDistSPCheck(mCoBG_unit_vec_info_c* unit_vec, f32* point) {
    int count = l_VecInf.unit_count;
    mCoBG_unit_vec_info_c* cur_unit_vec_p = l_VecInf.unit;
    f32* start;
    f32* end;
    int i;

    for (i = 0; i < count; i++) {
        if (cur_unit_vec_p != unit_vec) {
            start = cur_unit_vec_p->start;
            end = cur_unit_vec_p->end;

            if ((ABS(start[0] - point[0]) < 0.1f && ABS(start[1] - point[1]) < 0.1f) ||
                (ABS(end[0] - point[0]) < 0.1f && ABS(end[1] - point[1]) < 0.1f)) {
                if ((u16)(unit_vec->normal_angle - cur_unit_vec_p->normal_angle) < (DEG2SHORT_ANGLE2(90.0f)-0x100)) {
                    return FALSE;
                }
            }
        }

        cur_unit_vec_p++;
    }

    return TRUE;
}

static int mCoBG_Distance2Reverse_NormalWall_Special(f32* reverse, mCoBG_unit_vec_info_c* unit_vec, f32* actor_start, f32* actor_end, mCoBG_ActorInf_c* actor_info, ACTOR* actorx) {
    if (mCoBG_GetPointInfoFrontLine(unit_vec->start, actor_end, unit_vec->normal) && mCoBG_GetPointInfoFrontLine(unit_vec->start, actor_start, unit_vec->normal)) {
        f32 dist;

        mCoBG_GetDistPointAndLine2D_Norm(&dist, unit_vec->start, unit_vec->end, unit_vec->normal, actor_end);
        if (dist < actor_info->range) {
            f32 cross0[2];
            f32 cross1[2];

            if (mCoBG_JudgePointInCircle(unit_vec->start, actor_end, actor_info->range)) {
                if (!mCoBG_CheckDistSPCheck(unit_vec, actor_end)) {
                    return FALSE;
                }

                if (mCoBG_GetCrossCircleAndLine2Dvector(cross0, cross1, unit_vec->start, unit_vec->normal, actor_end, actor_info->range)) {
                    mCoBG_WallHeight_c height;

                    height.top = unit_vec->wall_bounds.start_top;
                    height.bot = unit_vec->wall_bounds.start_btm;
                    if ((actor_info->old_ground_y - 5.0f) + 3.0f <= height.top) {
                        mCoBG_GetSpecialDistanceReverse(reverse, actor_end, unit_vec, cross0, cross1, unit_vec->start);
                        mCoBG_RegistCollisionWallInfo(actor_info, actor_info->wall_info, &height, unit_vec->normal_angle, unit_vec->atr_wall);
                        if (unit_vec->regist_p != NULL) {
                            mCoBG_SetMoveBgContactSide(unit_vec->regist_p, actorx, unit_vec->normal_angle);
                        }

                        return TRUE;
                    }
                }
            } else if (mCoBG_JudgePointInCircle(unit_vec->end, actor_end, actor_info->range)) {
                if (!mCoBG_CheckDistSPCheck(unit_vec, actor_end)) {
                    return FALSE;
                }

                if (mCoBG_GetCrossCircleAndLine2Dvector(cross0, cross1, unit_vec->end, unit_vec->normal, actor_end, actor_info->range)) {
                    mCoBG_WallHeight_c height;

                    height.top = unit_vec->wall_bounds.end_top;
                    height.bot = unit_vec->wall_bounds.end_btm;
                    if ((actor_info->old_ground_y - 5.0f) + 3.0f <= height.top) {
                        mCoBG_GetSpecialDistanceReverse(reverse, actor_end, unit_vec, cross0, cross1, unit_vec->end);
                        mCoBG_RegistCollisionWallInfo(actor_info, actor_info->wall_info, &height, unit_vec->normal_angle, unit_vec->atr_wall);
                        if (unit_vec->regist_p != NULL) {
                            mCoBG_SetMoveBgContactSide(unit_vec->regist_p, actorx, unit_vec->normal_angle);
                        }

                        return TRUE;
                    }
                }
            }
        }
    }

    return FALSE;
}

static int mCoBG_Distance2Reverse_AttributeWall(f32* reverse, mCoBG_unit_vec_info_c* unit_vec, f32* actor_start, f32* actor_end, mCoBG_ActorInf_c* actor_info, ACTOR* actorx) {
    f32 dist;

    if (mCoBG_GetDistPointAndLine2D_Norm(&dist, unit_vec->start, unit_vec->end, unit_vec->normal, actor_end)) {
        if (dist < actor_info->range) {
            f32 rev_dist = (actor_info->range - dist) + 0.00001f;

            reverse[0] = unit_vec->normal[0] * rev_dist;
            reverse[1] = unit_vec->normal[1] * rev_dist;
            mCoBG_RegistCollisionWallInfo(actor_info, actor_info->wall_info, NULL, unit_vec->normal_angle, unit_vec->atr_wall);
            return TRUE;
        } else if (ABS(dist - actor_info->range) < 2.7f) {
            mCoBG_RegistCollisionWallInfo(actor_info, actor_info->wall_info, NULL, unit_vec->normal_angle, unit_vec->atr_wall);
            return TRUE;
        }
    }

    return FALSE;
}

static int mCoBG_Distance2Reverse_AttributeWall_Special(f32* reverse, mCoBG_unit_vec_info_c* unit_vec, f32* actor_start, f32* actor_end, mCoBG_ActorInf_c* actor_info, ACTOR* actorx) {
    if (mCoBG_GetPointInfoFrontLine(unit_vec->start, actor_end, unit_vec->normal) && mCoBG_GetPointInfoFrontLine(unit_vec->start, actor_start, unit_vec->normal)) {
        f32 dist;

        mCoBG_GetDistPointAndLine2D_Norm(&dist, unit_vec->start, unit_vec->end, unit_vec->normal, actor_end);
        if (dist < actor_info->range) {
            f32 cross0[2];
            f32 cross1[2];

            if (mCoBG_JudgePointInCircle(unit_vec->start, actor_end, actor_info->range)) {
                if (!mCoBG_CheckDistSPCheck(unit_vec, actor_end)) {
                    return FALSE;
                }

                if (mCoBG_GetCrossCircleAndLine2Dvector(cross0, cross1, unit_vec->start, unit_vec->normal, actor_end, actor_info->range)) {
                    mCoBG_GetSpecialDistanceReverse(reverse, actor_end, unit_vec, cross0, cross1, unit_vec->start);
                    mCoBG_RegistCollisionWallInfo(actor_info, actor_info->wall_info, NULL, unit_vec->normal_angle, unit_vec->atr_wall);
                    return TRUE;
                }
            } else if (mCoBG_JudgePointInCircle(unit_vec->end, actor_end, actor_info->range)) {
                if (!mCoBG_CheckDistSPCheck(unit_vec, actor_end)) {
                    return FALSE;
                }

                if (mCoBG_GetCrossCircleAndLine2Dvector(cross0, cross1, unit_vec->end, unit_vec->normal, actor_end, actor_info->range)) {
                    mCoBG_GetSpecialDistanceReverse(reverse, actor_end, unit_vec, cross0, cross1, unit_vec->end);
                    mCoBG_RegistCollisionWallInfo(actor_info, actor_info->wall_info, NULL, unit_vec->normal_angle, unit_vec->atr_wall);
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

typedef int (*mCoBG_DIST_REV_PROC)(f32* reverse, mCoBG_unit_vec_info_c* unit_vec, f32* actor_start, f32* actor_end, mCoBG_ActorInf_c* actor_info, ACTOR* actorx);
typedef int (*mCoBG_DIST_REV_PLAYER_PROC)(f32* reverse, mCoBG_unit_vec_info_c* unit_vec, f32* actor_start, f32* actor_end, mCoBG_ActorInf_c* actor_info, ACTOR* actorx);

static void mCoBG_Distance2Reverse(f32* reverse, mCoBG_unit_vec_info_c* unit_vec, int unit, f32* actor_start, f32* actor_end, mCoBG_ActorInf_c* actor_info, ACTOR* actorx) {
    static mCoBG_DIST_REV_PROC dist_rev_proc[] = { &mCoBG_Distance2Reverse_NormalWall, &mCoBG_Distance2Reverse_AttributeWall, &mCoBG_Distance2Reverse_NormalWall };
    static mCoBG_DIST_REV_PLAYER_PROC dist_rev_proc_player[] = { &mCoBG_Distance2Reverse_NormalWall_Special, &mCoBG_Distance2Reverse_AttributeWall_Special, &mCoBG_Distance2Reverse_NormalWall_Special };
    s16 kind;

    if (mCoBG_GetPointInfoFrontLine(unit_vec->start, actor_start, unit_vec->normal)) {
        switch (actor_info->check_type) {
            case mCoBG_CHECK_TYPE_NORMAL:
                if (mCoBG_RangeCheckLinePoint(unit_vec->start, unit_vec->end, actor_start)) {
                    kind = mCoBG_GetWallKind(unit_vec);
                    (*dist_rev_proc[kind])(reverse, unit_vec, actor_start, actor_end, actor_info, actorx);
                }
                break;
            default:
                kind = mCoBG_GetWallKind(unit_vec);
                (*dist_rev_proc_player[kind])(reverse, unit_vec, actor_start, actor_end, actor_info, actorx);
                break;
        }
    }
}

static f32 pre_work[65];
static f32 bk_work[65];

static void mCoBG_MergeSortFloat(f32* data, int first, int last) {
    if (first < last) {
        int middle = (first + last) >> 1;
        int pre_count = 0;
        int bk_count = 0;
        int set = first;
        int pre;
        int bk;

        mCoBG_MergeSortFloat(data, first, middle);
        mCoBG_MergeSortFloat(data, middle + 1, last);

        // load in the obttom half of the data
        for (pre = first; pre <= middle; pre++) {
            pre_work[pre_count++] = data[pre];
        }

        // load in the top half of the data
        for (bk = middle + 1; bk <= last; bk++) {
            bk_work[bk_count++] = data[bk];
        }

        // compare each item that was pre sorted
        pre = 0;
        bk = 0;
        while (pre < pre_count && bk < bk_count) {
            if (pre_work[pre] <= bk_work[bk]) {
                data[set++] = pre_work[pre++]; 
            } else {
                data[set++] = bk_work[bk++];             
            }
        }

        while (pre < pre_count) {
            data[set++] = pre_work[pre++];
        }

        while (bk < bk_count) {
            data[set++] = bk_work[bk++];
        }
    }
}

static void mCoBG_GetWallPriority(u8* prio_tbl, mCoBG_vec_info_c* vec_info, f32* actor_start) {
    static f32 dist_table[mCoBG_UNIT_VEC_INFO_MAX];
    static f32 merge_dist_table[mCoBG_UNIT_VEC_INFO_MAX];
    u64 flag = 0;
    mCoBG_unit_vec_info_c* unit_vec = vec_info->unit;
    int count = vec_info->unit_count;
    int unit = 0;
    int i;
    f32 center[2];
    f32 dist[2];
    f32* start;
    f32* end;

    for (unit = 0; unit < count; unit++) {
        start = unit_vec->start;
        end = unit_vec->end;

        center[0] = (start[0] + end[0]) * 0.5f;
        center[1] = (start[1] + end[1]) * 0.5f;
        dist[0] = center[0] - actor_start[0];
        dist[1] = center[1] - actor_start[1];
        dist_table[unit] = SQ(dist[0]) + SQ(dist[1]);
        merge_dist_table[unit] = dist_table[unit];
        unit_vec++;
    }

    mCoBG_MergeSortFloat(merge_dist_table, 0, count - 1);

    for (unit = 0; unit < count; unit++) {
        prio_tbl[unit] = 0;
    }

    for (i = 0; i < count; i++) {
        prio_tbl[i] = 0;
        for (unit = 0; unit < count; unit++) {
            if (dist_table[unit] == merge_dist_table[i] && ((flag >> (u64)unit) & 1) == 0) {
                flag |= 1 << (u64)unit;
                prio_tbl[i] = unit;
                break;
            }
        }
    }
}

static void mCoBG_GetWallReverse(mCoBG_ActorInf_c* actor_info, const xyz_t* pos, mCoBG_vec_info_c* vec_info, ACTOR* actorx) {
    mCoBG_unit_vec_info_c* unit_vec;
    f32 actor_start[2];
    f32 actor_end[2];
    f32 speed[2];
    f32 end[2];
    int count = vec_info->unit_count;
    int unit;

    actor_start[0] = actorx->last_world_position.x;
    actor_start[1] = actorx->last_world_position.z;
    actor_end[0] = pos->x;
    actor_end[1] = pos->z;
    speed[0] = actor_end[0] - actor_start[0];
    speed[1] = actor_end[1] - actor_start[1];
    mCoBG_MakeTab2MoveTail(actor_start, speed);
    end[0] = actor_end[0];
    end[1] = actor_end[1];

    if (actor_info->check_type == mCoBG_CHECK_TYPE_PLAYER) {
        u8 prio_tbl[mCoBG_UNIT_VEC_INFO_MAX];
        int i;
        int j;
        f32 rev[2];

        actor_info->check_type = mCoBG_CHECK_TYPE_NORMAL;
        unit_vec = vec_info->unit;
        for (i = 0; i < count; i++) {
            rev[0] = 0.0f;
            rev[1] = 0.0f;
            mCoBG_Distance2Reverse(rev, unit_vec, i, actor_start, actor_end, actor_info, actorx);
            actor_end[0] += rev[0];
            actor_end[1] += rev[1];
            unit_vec++;
        }

        mCoBG_GetWallPriority(prio_tbl, vec_info, actor_start);
        actor_info->check_type = mCoBG_CHECK_TYPE_PLAYER;
        unit_vec = vec_info->unit;
        for (j = 0; j < count; j++) {
            rev[0] = 0.0f;
            rev[1] = 0.0f;
            mCoBG_Distance2Reverse(rev, &unit_vec[prio_tbl[j]], prio_tbl[j], actor_start, actor_end, actor_info, actorx);
            actor_end[0] += rev[0];
            actor_end[1] += rev[1];
        }


        unit_vec = vec_info->unit;
        for (i = 0; i < count; i++) {
            rev[0] = 0.0f;
            rev[1] = 0.0f;
            mCoBG_Cross2Reverse(rev, unit_vec, i, actor_start, actor_end, actor_info, actorx);
            actor_end[0] += rev[0];
            actor_end[1] += rev[1];
            unit_vec++;
        }
    } else {
        f32 rev[2];
        f32 spd = sqrtf(SQ(speed[0]) + SQ(speed[1]));
        
        if (spd > actor_info->range * 0.5f) {
            unit_vec = vec_info->unit;
            for (unit = 0; unit < count; unit++) {
                rev[0] = 0.0f;
                rev[1] = 0.0f;
                mCoBG_Cross2Reverse(rev, unit_vec, unit, actor_start, actor_end, actor_info, actorx);
                actor_end[0] += rev[0];
                actor_end[1] += rev[1];
                unit_vec++;
            }
        }

        unit_vec = vec_info->unit;
        for (unit = 0; unit < count; unit++) {
            if (unit_vec->regist_p == NULL) {
                rev[0] = 0.0f;
                rev[1] = 0.0f;
                mCoBG_Distance2Reverse(rev, unit_vec, unit, actor_start, actor_end, actor_info, actorx);
                actor_end[0] += rev[0];
                actor_end[1] += rev[1];
            }
            unit_vec++;
        }

        unit_vec = vec_info->unit;
        for (unit = 0; unit < count; unit++) {
            if (unit_vec->regist_p != NULL) {
                rev[0] = 0.0f;
                rev[1] = 0.0f;
                mCoBG_Distance2Reverse(rev, unit_vec, unit, actor_start, actor_end, actor_info, actorx);
                actor_end[0] += rev[0];
                actor_end[1] += rev[1];
            }
            unit_vec++;
        }
    }

    actor_info->rev_pos.x = actor_end[0] - end[0];
    actor_info->rev_pos.z = actor_end[1] - end[1];
}

static mCoBG_UnitInfo_c l_crtutInf[50];

static void mCoBG_WallCheck(ACTOR* actorx, mCoBG_ActorInf_c* actor_info, s16 atr_wall, mCoBG_Check_c* check_p) {
    int ux;
    int uz;

    bzero(l_crtutInf, sizeof(l_crtutInf));
    bzero(&l_VecInf, sizeof(l_VecInf));
    mCoBG_GetSpeedByWpos(l_ActorInf.speed_xz0, actorx);
    mFI_Wpos2UtNum(&ux, &uz, actor_info->center_pos);
    mCoBG_MakeSizeUnitInfo(l_crtutInf, ux, uz, actor_info->ut_count);
    if (actorx->id == mAc_PROFILE_PLAYER && (ABS(l_ActorInf.speed_xz0[0]) > 100.0f || ABS(l_ActorInf.speed_xz0[1]) > 100.0f)) {
        return;
    }

    mCoBG_MakeUnitVector(&l_VecInf, l_crtutInf, actor_info->ut_count, actor_info->check_type, atr_wall, actor_info->old_on_ground, actor_info->old_in_water);
    if (actorx->id != mAc_PROFILE_GYOEI) {
        mCoBG_MakeMoveBgVector(&l_VecInf, &l_mBgMgr, &actorx->world.position, actor_info->check_type);
    }

    mCoBG_MakeColumnCollisionData(l_VecInf.column, &l_VecInf.col_count, l_crtutInf, actor_info->ut_count, actor_info->old_on_ground, NULL, l_ActorInf._68, l_ActorInf._6C);
    mCoBG_MakeCircleDefenceWall(actor_info, atr_wall);

    {
        xyz_t pos;
        xyz_t rev0 = { 0.0f, 0.0f, 0.0f };
        xyz_t rev1 = { 0.0f, 0.0f, 0.0f };

        pos.x = actorx->world.position.x + actor_info->rev_pos.x;
        pos.y = actorx->world.position.y + actor_info->rev_pos.y;
        pos.z = actorx->world.position.z + actor_info->rev_pos.z;
        mCoBG_ColumnWallCheck(&rev0, actor_info, &pos, l_VecInf.column, l_VecInf.col_count, atr_wall);
        actor_info->rev_pos.x += rev0.x;
        actor_info->rev_pos.y += rev0.y;
        actor_info->rev_pos.z += rev0.z;

        pos.x = actorx->world.position.x + actor_info->rev_pos.x;
        pos.y = actorx->world.position.y + actor_info->rev_pos.y;
        pos.z = actorx->world.position.z + actor_info->rev_pos.z;
        mCoBG_ColumnWallCheck(&rev1, actor_info, &pos, mCoBG_decal_circle, mCoBG_regist_decal_circle_count, atr_wall);
        actor_info->rev_pos.x += rev1.x;
        actor_info->rev_pos.y += rev1.y;
        actor_info->rev_pos.z += rev1.z;

        actorx->world.position.x += actor_info->rev_pos.x;
        actorx->world.position.y += actor_info->rev_pos.y;
        actorx->world.position.z += actor_info->rev_pos.z;
        mCoBG_GetWallReverse(actor_info, &actorx->world.position, &l_VecInf, actorx);
        mCoBG_MakeHitWallFalg(&actorx->bg_collision_check.result, actor_info->wall_info);
        
        actorx->bg_collision_check.wall_bottom_y = actor_info->wall_height.bot;
        actorx->bg_collision_check.wall_top_y = actor_info->wall_height.top;
        actorx->bg_collision_check.wall_info[0].angleY = actor_info->wall_info[0].angleY;
        actorx->bg_collision_check.wall_info[1].angleY = actor_info->wall_info[1].angleY;
        actorx->bg_collision_check.wall_info[0].type = actor_info->wall_info[0].type;
        actorx->bg_collision_check.wall_info[1].type = actor_info->wall_info[1].type;

        mCoBG_RegistWallCount(&actorx->bg_collision_check.result, actor_info->wall_info, actorx->shape_info.rotation.y);
        mCoBG_MakePartDirectHitWallFlag(actorx);
    }
}

static f32 mCoBG_GetAreaYSlatingUnit(mCoBG_UnitInfo_c* unit_info, s16 type, s16 area) {
    switch (type) {
        case mCoBG_WALL_SLATE_UP:
            switch (area) {
                case mCoBG_AREA_S:
                case mCoBG_AREA_E:
                    return unit_info->collision->data.bot_right * 10.0f;
                case mCoBG_AREA_N:
                case mCoBG_AREA_W:
                    return unit_info->collision->data.top_left * 10.0f;
                default:
                    break;
            }
        // fallthrough
        case mCoBG_WALL_SLATE_DOWN:
            switch (area) {
                case mCoBG_AREA_N:
                case mCoBG_AREA_E:
                    return unit_info->collision->data.top_right * 10.0f;
                case mCoBG_AREA_W:
                case mCoBG_AREA_S:
                    return unit_info->collision->data.bot_left * 10.0f;
                default:
                    break;
            }
            break;
    }
    
    return 0.0f;
}

static void mCoBG_GetCurrentCenterPosition(xyz_t* current_center_pos, ACTOR* actorx) {
    *current_center_pos = actorx->world.position;
}

static void mCoBG_GetOldCenterPosition(xyz_t* old_center_pos, ACTOR* actorx) {
    *old_center_pos = actorx->last_world_position;
}

static f32 mCoBG_GetBGHeight_Normal_NormalGround(s_xyz* angle, mCoBG_UnitInfo_c* unit_info) {
    xyz_t normal;
    s16 area;
    f32 ground_normal_y;

    if (
        unit_info->collision->data.center != unit_info->collision->data.top_left ||
        unit_info->collision->data.center != unit_info->collision->data.bot_left ||
        unit_info->collision->data.center != unit_info->collision->data.bot_right ||
        unit_info->collision->data.center != unit_info->collision->data.top_right
    ) {
        mCoBG_GetUnitArea(unit_info, &area);
        mCoBG_GetNormTriangle(&normal, angle, unit_info->collision, area);
        ground_normal_y = mCoBG_GroundPolygonInfo2BgHeight(&normal, unit_info) + mFI_UtNum2BaseHeight(unit_info->ut_x, unit_info->ut_z);
    } else {
        ground_normal_y = unit_info->collision->data.center * 10.0f + mFI_UtNum2BaseHeight(unit_info->ut_x, unit_info->ut_z);
        if (angle != NULL) {
            angle->x = 0;
            angle->y = 0;
            angle->z = 0;
        }
    }

    return ground_normal_y;
}

static f32 mCoBG_GetBGHeight_Normal_SlateGround(s_xyz* angle, mCoBG_UnitInfo_c* unit_info) {
    s16 area;
    f32 ground_normal_y;

    if (unit_info->collision->data.top_left != unit_info->collision->data.bot_right) {
        mCoBG_GetUnitArea(unit_info, &area);
        ground_normal_y = mCoBG_GetAreaYSlatingUnit(unit_info, mCoBG_WALL_SLATE_UP, area) + mFI_UtNum2BaseHeight(unit_info->ut_x, unit_info->ut_z);
    } else {
        mCoBG_GetUnitArea(unit_info, &area);
        ground_normal_y = mCoBG_GetAreaYSlatingUnit(unit_info, mCoBG_WALL_SLATE_DOWN, area) + mFI_UtNum2BaseHeight(unit_info->ut_x, unit_info->ut_z);
    }

    if (angle != NULL) {
        angle->x = 0;
        angle->y = 0;
        angle->z = 0;
    }

    return ground_normal_y;
}

typedef f32 (*mCoBG_GET_BG_Y_NORMAL_PROC)(s_xyz* angle, mCoBG_UnitInfo_c* unit_info);

static f32 mCoBG_GetBGHeight_Normal(s_xyz* angle, mCoBG_UnitInfo_c* unit_info) {
    static mCoBG_GET_BG_Y_NORMAL_PROC get_bg_y_normal_proc[] = { &mCoBG_GetBGHeight_Normal_NormalGround, &mCoBG_GetBGHeight_Normal_SlateGround };

    return (*get_bg_y_normal_proc[unit_info->collision->data.slate_flag])(angle, unit_info);
}

static void mCoBG_MakeJumpFlag_NotOldOnGround(mCoBG_CheckResult_c* result, mCoBG_ActorInf_c* actor_info, xyz_t* rev, f32 ground_normal_y) {
    // nothing
}

static void mCoBG_MakeJumpFlag_OldOnGround(mCoBG_CheckResult_c* result, mCoBG_ActorInf_c* actor_info, xyz_t* rev, f32 ground_normal_y) {
    if (actor_info->ground_y + rev->y > (ground_normal_y + 0.01f)) {
        result->jump_flag = TRUE;
    }
}

typedef void (*mCoBG_MAKE_JUMP_FLAG_PROC)(mCoBG_CheckResult_c* result, mCoBG_ActorInf_c* actor_info, xyz_t* rev, f32 ground_normal_y);

static void mCoBG_MakeJumpFlag(mCoBG_CheckResult_c* result, mCoBG_ActorInf_c* actor_info, xyz_t* rev, f32 ground_normal_y) {
    static mCoBG_MAKE_JUMP_FLAG_PROC make_jump_flag_proc[] = { &mCoBG_MakeJumpFlag_NotOldOnGround, &mCoBG_MakeJumpFlag_OldOnGround };

    (*make_jump_flag_proc[actor_info->old_on_ground & 1])(result, actor_info, rev, ground_normal_y);
}

static int mCoBG_Pos2UnitPos(xyz_t* unit_pos, const xyz_t* pos) {
    static const xyz_t pos0 = { 0.0f, 0.0f, 0.0f };
    xyz_t center_pos = pos0;

    *unit_pos = pos0;
    if (mFI_Wpos2UtCenterWpos(&center_pos, *pos)) {
        unit_pos->x = pos->x - center_pos.x;
        unit_pos->z = pos->z - center_pos.z;
        return TRUE;
    }

    return FALSE;
}

typedef struct {
    xyz_t low;
    xyz_t high;
} mCoBG_wave_c;

static u32 mCoBG_CheckWaveAtrDetail(xyz_t* point, mCoBG_wave_c* wave_p) {
    f32 wave_cos = mCoBG_WaveCos();
    f32 rate = (1.0f + wave_cos) * 0.5f;
    f32 cross[2];
    f32 high[2];
    f32 low[2];
    f32 p[2];

    high[0] = wave_p->high.x;
    high[1] = wave_p->high.z;
    low[0] = wave_p->low.x;
    low[1] = wave_p->low.z;
    p[0] = point->x;
    p[1] = point->z;

    if (mCoBG_GetCrossLineAndPerpendicular(cross, high, low, p)) {
        f32 dx = SQ(high[0] - low[0]);
        f32 dz = SQ(high[1] - low[1]);
        f32 dist = sqrtf(dx + dz);
        f32 dpx = SQ(cross[0] - low[0]);
        f32 dpz = SQ(cross[1] - low[1]);
        f32 dist_point = sqrtf(dpx + dpz);
        f32 pos_rate;

        if (F32_IS_ZERO(dist) == FALSE) {
            pos_rate = 1.1f * (dist_point / dist);
        } else {
            pos_rate = -1.0f;
        }

        if (pos_rate <= 0.0f) {
            return mCoBG_ATTRIBUTE_SEA;
        }

        if (pos_rate >= 1.1f) {
            return mCoBG_ATTRIBUTE_SAND;
        }

        if (pos_rate <= rate) {
            return mCoBG_ATTRIBUTE_WAVE;
        }

        return mCoBG_ATTRIBUTE_SAND;
    }

    return mCoBG_ATTRIBUTE_SEA;
}

static u32 mCoBG_GetWaveDynamicAttr(u32 orig_attr, xyz_t* pos) {
    if (orig_attr == mCoBG_ATTRIBUTE_36) {
        static mCoBG_wave_c wave_s_info = { { 0.0f, 0.0f, mFI_UT_WORLDSIZE_HALF_Z_F }, { 0.0f, 0.0f, -mFI_UT_WORLDSIZE_HALF_Z_F } };

        return mCoBG_CheckWaveAtrDetail(pos, &wave_s_info);
    }

    if (orig_attr == mCoBG_ATTRIBUTE_37) {
        static mCoBG_wave_c wave_se_info = { { 0.0f, 0.0f, 0.0f }, { -mFI_UT_WORLDSIZE_HALF_X_F, 0.0f, -mFI_UT_WORLDSIZE_HALF_Z_F } };

        return mCoBG_CheckWaveAtrDetail(pos, &wave_se_info);
    }

    if (orig_attr == mCoBG_ATTRIBUTE_38) {
        static mCoBG_wave_c wave_sw_info = { { 0.0f, 0.0f, 0.0f }, { mFI_UT_WORLDSIZE_HALF_X_F, 0.0f, mFI_UT_WORLDSIZE_HALF_Z_F } };

        return mCoBG_CheckWaveAtrDetail(pos, &wave_sw_info);
    }

    if (orig_attr == mCoBG_ATTRIBUTE_25) {
        static mCoBG_wave_c wave_se2_info = { { mFI_UT_WORLDSIZE_HALF_X_F, 0.0f, mFI_UT_WORLDSIZE_HALF_Z_F }, { 0.0f, 0.0f, 0.0f } };

        return mCoBG_CheckWaveAtrDetail(pos, &wave_se2_info);
    }

    if (orig_attr == mCoBG_ATTRIBUTE_26) {
        static mCoBG_wave_c wave_sw2_info = { { -mFI_UT_WORLDSIZE_HALF_X_F, 0.0f, mFI_UT_WORLDSIZE_HALF_Z_F }, { 0.0f, 0.0f, 0.0f } };

        return mCoBG_CheckWaveAtrDetail(pos, &wave_sw2_info);
    }

    return mCoBG_ATTRIBUTE_SEA;
}

// clang-format off
static u8 mCoBG_woodb_water_info[][4] = {
    { mCoBG_ATTRIBUTE_RIVER_NW, mCoBG_ATTRIBUTE_RIVER_NW, mCoBG_ATTRIBUTE_WOOD, mCoBG_ATTRIBUTE_WOOD },
    { mCoBG_ATTRIBUTE_WOOD, mCoBG_ATTRIBUTE_RIVER_SW, mCoBG_ATTRIBUTE_RIVER_SW, mCoBG_ATTRIBUTE_WOOD },
    { mCoBG_ATTRIBUTE_WOOD, mCoBG_ATTRIBUTE_WOOD, mCoBG_ATTRIBUTE_RIVER_SE, mCoBG_ATTRIBUTE_RIVER_SE },
    { mCoBG_ATTRIBUTE_RIVER_NE, mCoBG_ATTRIBUTE_WOOD, mCoBG_ATTRIBUTE_WOOD, mCoBG_ATTRIBUTE_RIVER_NE },
    { mCoBG_ATTRIBUTE_WOOD, mCoBG_ATTRIBUTE_WOOD, mCoBG_ATTRIBUTE_WOOD, mCoBG_ATTRIBUTE_WOOD },
    { mCoBG_ATTRIBUTE_WOOD, mCoBG_ATTRIBUTE_WOOD, mCoBG_ATTRIBUTE_WOOD, mCoBG_ATTRIBUTE_WOOD },
};
// clang-format on

// clang-format off
static u8 mCoBG_grass3_water_info[][4] = {
    { mCoBG_ATTRIBUTE_RIVER_NW, mCoBG_ATTRIBUTE_RIVER_NW, mCoBG_ATTRIBUTE_GRASS2, mCoBG_ATTRIBUTE_GRASS2 },
    { mCoBG_ATTRIBUTE_GRASS2, mCoBG_ATTRIBUTE_RIVER_SW, mCoBG_ATTRIBUTE_RIVER_SW, mCoBG_ATTRIBUTE_GRASS2 },
    { mCoBG_ATTRIBUTE_GRASS2, mCoBG_ATTRIBUTE_GRASS2, mCoBG_ATTRIBUTE_RIVER_SE, mCoBG_ATTRIBUTE_RIVER_SE },
    { mCoBG_ATTRIBUTE_RIVER_NE, mCoBG_ATTRIBUTE_GRASS2, mCoBG_ATTRIBUTE_GRASS2, mCoBG_ATTRIBUTE_RIVER_NE },
};
// clang-format on

extern u32 mCoBG_Wpos2Attribute(xyz_t pos, s8* cant_dig) {
    mCoBG_UnitInfo_c unit_info;
    u32 attr;
    s16 area;
    
    pos.y = 0.0f;
    mCoBG_Wpos2UnitInfo(&unit_info, pos);
    attr = unit_info.collision->data.unit_attribute;
    if (cant_dig != NULL) {
        *cant_dig = FALSE;
    }

    if (attr == mCoBG_ATTRIBUTE_HOLE) {
        if (Common_Get(field_type) != mFI_FIELDTYPE2_FG) {
            return mCoBG_ATTRIBUTE_FLOOR;
        } else {
            return mCoBG_ATTRIBUTE_GRASS2;
        }
    }

    if (attr == mCoBG_ATTRIBUTE_63) {
        mCoBG_GetUnitArea(&unit_info, &area);
        return mCoBG_SearchAttribute(pos, area, cant_dig);
    }

    if (attr >= mCoBG_ATTRIBUTE_25 && attr <= mCoBG_ATTRIBUTE_26) {
        xyz_t unit_pos;

        if (mCoBG_Pos2UnitPos(&unit_pos, &pos)) {
            return mCoBG_GetWaveDynamicAttr(attr, &unit_pos);
        } else {
            return mCoBG_ATTRIBUTE_SAND;
        }
    }

    if (attr >= mCoBG_ATTRIBUTE_27 && attr <= mCoBG_ATTRIBUTE_62) {
        if (cant_dig != NULL) {
            *cant_dig = TRUE;
        }

        if (attr >= mCoBG_ATTRIBUTE_43 && attr <= mCoBG_ATTRIBUTE_62) {
            if (Common_Get(field_type) != mFI_FIELDTYPE2_FG) {
                return mCoBG_ATTRIBUTE_FLOOR;
            } else {
                return mCoBG_ATTRIBUTE_GRASS2;
            }
        }

        if (attr >= mCoBG_ATTRIBUTE_27 && attr <= mCoBG_ATTRIBUTE_31) {
            int idx;

            mCoBG_GetUnitArea(&unit_info, &area);
            idx = attr - mCoBG_ATTRIBUTE_27;
            return mCoBG_woodb_water_info[idx][area];
        }

        if (attr >= mCoBG_ATTRIBUTE_32 && attr <= mCoBG_ATTRIBUTE_35) {
            return mCoBG_ATTRIBUTE_STONE;
        }

        if (attr >= mCoBG_ATTRIBUTE_36 && attr <= mCoBG_ATTRIBUTE_38) {
            xyz_t unit_pos;

            if (mCoBG_Pos2UnitPos(&unit_pos, &pos)) {
                return mCoBG_GetWaveDynamicAttr(attr, &unit_pos);
            }

            return mCoBG_ATTRIBUTE_SAND;
        }

        if (attr >= mCoBG_ATTRIBUTE_39 && attr <= mCoBG_ATTRIBUTE_42) {
            int idx;

            mCoBG_GetUnitArea(&unit_info, &area);
            idx = attr - mCoBG_ATTRIBUTE_39;

            if ((mCoBG_grass3_water_info[idx][area] <= mCoBG_ATTRIBUTE_GRASS3 && Common_Get(field_type) != mFI_FIELDTYPE2_FG) == FALSE) {
                return mCoBG_grass3_water_info[idx][area];
            } else {
                return mCoBG_ATTRIBUTE_FLOOR;
            }
        }
    }

    if ((attr <= mCoBG_ATTRIBUTE_GRASS3 && Common_Get(field_type) != mFI_FIELDTYPE2_FG) == FALSE) {
        return attr;
    } else {
        return mCoBG_ATTRIBUTE_FLOOR;
    }
}

// clang-format off
static u8 mCoBG_unit_attribute_water_info[] = {
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_WATER,
    mCoBG_ATTRIBUTE_WATERFALL,
    mCoBG_ATTRIBUTE_RIVER_N,
    mCoBG_ATTRIBUTE_RIVER_NW,
    mCoBG_ATTRIBUTE_RIVER_W,
    mCoBG_ATTRIBUTE_RIVER_SW,
    mCoBG_ATTRIBUTE_RIVER_S,
    mCoBG_ATTRIBUTE_RIVER_SE,
    mCoBG_ATTRIBUTE_RIVER_E,
    mCoBG_ATTRIBUTE_RIVER_NE,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_RIVER_NW,
    mCoBG_ATTRIBUTE_RIVER_SW,
    mCoBG_ATTRIBUTE_RIVER_SE,
    mCoBG_ATTRIBUTE_RIVER_NE,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_RIVER_NW,
    mCoBG_ATTRIBUTE_RIVER_SW,
    mCoBG_ATTRIBUTE_RIVER_SE,
    mCoBG_ATTRIBUTE_RIVER_NE,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
    mCoBG_ATTRIBUTE_GRASS0,
};
// clang-format on

static u32 mCoBG_SearchWaterAttributeFrom4Area(xyz_t pos) {
    mCoBG_UnitInfo_c unit_info;
    u32 attr;

    mCoBG_Wpos2UnitInfo(&unit_info, pos);
    attr = unit_info.collision->data.unit_attribute;
    return mCoBG_unit_attribute_water_info[attr];
}

#include "../src/AUS/game/m_collision_bg_info.c_inc"
#include "../src/AUS/game/m_collision_bg_rewrite.c_inc"

static f32 mCoBG_GetBGHeight_NormalColumn(mCoBG_UnitInfo_c* unit_info, s_xyz* ground_angle, const xyz_t* pos) {
    static s_xyz ground_angle0; // @BUG - shouldn't this be initialized?
    s_xyz normal_ground_angle;
    f32 normal_ground_y = mCoBG_GetBGHeight_Normal(&normal_ground_angle, unit_info);
    f32 column_ground_y;

    if (unit_info->ut_x == l_ActorInf._68 && unit_info->ut_z == l_ActorInf._6C) {
        column_ground_y = 0.0f;
    } else {
        column_ground_y = mCoBG_GetBGHeight_Column(pos, unit_info);
    }

    if (normal_ground_y > column_ground_y) {
        if (ground_angle != NULL) {
            *ground_angle = normal_ground_angle;
        }
        return normal_ground_y;
    } else {
        if (ground_angle != NULL) {
            *ground_angle = ground_angle0;
        }
        return column_ground_y;
    }
}

static void mCoBG_GroundCheck(xyz_t* rev, mCoBG_ActorInf_c* actor_info, ACTOR* actorx, f32 actor_ground_dist, mCoBG_CheckResult_c* result, s_xyz* angle, s16 attribute_wall) {
    mCoBG_UnitInfo_c unit_info;
    xyz_t pos;
    f32 ground_y;
    u32 attr;
    u32 next_unit_attr = mCoBG_ATTRIBUTE_GRASS0;
    BOOL water_flag = FALSE;
    f32 water_y = 0.0f;

    pos.x = actorx->world.position.x + rev->x;
    pos.y = 0.0f;
    pos.z = actorx->world.position.z + rev->z;
    mCoBG_Wpos2UnitInfo(&unit_info, pos);
    attr = unit_info.collision->data.unit_attribute;

    if (attr == mCoBG_ATTRIBUTE_63 || (attr >= mCoBG_ATTRIBUTE_27 && attr <= mCoBG_ATTRIBUTE_62)) {
        if (attribute_wall == FALSE && actor_info->old_in_water == TRUE && (attr >= mCoBG_ATTRIBUTE_27 && attr <= mCoBG_ATTRIBUTE_35)) {
            int idx = attr - mCoBG_ATTRIBUTE_27;
            int flags = mCoBG_bridge_search_water[idx];
            xyz_t next_pos;
            int i;

            for (i = 0; i < 8; i++) {
                if ((flags & (1 << i)) != 0) {
                    mCoBG_PlussDirectOffset(&next_pos, pos, i);
                    next_unit_attr = mCoBG_SearchWaterAttributeFrom4Area(next_pos);
                    if (next_unit_attr >= mCoBG_ATTRIBUTE_WATER && next_unit_attr <= mCoBG_ATTRIBUTE_RIVER_NE) {
                        water_flag = TRUE;
                        water_y = mCoBG_GetWaterHeight_File(pos, __FILE__, 3883);
                    }
                }

                if (water_flag) {
                    actorx->bg_collision_check.result.unit_attribute = next_unit_attr;
                    break;
                }
            }
        } else {
            actorx->bg_collision_check.result.unit_attribute = mCoBG_Wpos2Attribute(pos, NULL);
        }
    } else {
        if (attr >= mCoBG_ATTRIBUTE_WATER && attr <= mCoBG_ATTRIBUTE_RIVER_NE) {
            water_flag = TRUE;
            water_y = 20.0f + mCoBG_GetBgY_AngleS_FromWpos(NULL, pos, 0.0f);
        } else if (attr == mCoBG_ATTRIBUTE_SEA) {
            water_flag = TRUE;
            water_y = 20.0f;
        } else {
            attr = mCoBG_Wpos2Attribute(pos, NULL);
        }

        actorx->bg_collision_check.result.unit_attribute = attr;
    }

    ground_y = mCoBG_GetBGHeight_NormalColumn(&unit_info, angle, &pos);
    mCoBG_AdjustActorY(rev, actorx, ground_y, water_y, actor_ground_dist, result, actor_info, water_flag);
    mCoBG_MakeJumpFlag(result, actor_info, rev, ground_y);
}

#include "../src/AUS/game/m_collision_bg_block.c_inc"
#include "../src/AUS/game/m_collision_bg_line.c_inc"
#include "../src/AUS/game/m_collision_bg_water.c_inc"

extern void mCoBG_InitBgCheckResult(mCoBG_CheckResult_c* result) {
    result->on_ground = FALSE;
    result->is_on_move_bg_obj = FALSE;
    result->hit_wall = 0;
    result->hit_attribute_wall = 0;
    result->jump_flag = FALSE;
    result->is_in_water = FALSE;
    result->unit_attribute = 0;
    result->hit_wall_count = 0;
    // result->unk_flag1 = FALSE;
    result->unk_flag2 = FALSE;
    result->unk_flag3 = FALSE;
    result->unk_flag4 = FALSE;
    result->unk_flag5 = FALSE;
}

static void mCoBG_InitBgCheckClass(mCoBG_Check_c* check) {
    check->wall_bottom_y = 0.0f;
    check->wall_top_y = 0.0f;
    check->ground_y = 0.0f;
    check->wall_info[0].angleY = 0xB6;
    check->wall_info[1].angleY = 0xB6;
    check->wall_info[0].type = mCoBG_WALL_TYPE_NUM;
    check->wall_info[1].type = mCoBG_WALL_TYPE_NUM;
}

static s16 mCoBG_ActorFearture2CheckRange(mCoBG_ActorInf_c* actor_info) {
    f32 range = actor_info->range;

    if (range <= 40.0f) {
        return 3;
    }

    if (range <= 80.0f) {
        return 5;
    }

    return 7;
}

static void mCoBG_MakeActorInf(mCoBG_ActorInf_c* actor_info, ACTOR* actorx, f32 range, f32 ground_dist, s16 check_type, int ux, int uz) {
    actor_info->_68 = ux;
    actor_info->_6C = uz;
    actor_info->old_in_water = actorx->bg_collision_check.result.is_in_water;
    actor_info->old_on_ground = actorx->bg_collision_check.result.on_ground;
    mCoBG_InitBgCheckResult(&actorx->bg_collision_check.result);
    mCoBG_InitBgCheckClass(&actorx->bg_collision_check);
    actor_info->name = actorx->id;
    actor_info->check_res_p = &actorx->bg_collision_check.result;
    mCoBG_GetSpeedByWpos(l_ActorInf.speed_xz1, actorx);
    actor_info->range = range;
    actor_info->ground_dist = ground_dist;
    actor_info->old_ground_y = actorx->last_world_position.y + ground_dist;
    actor_info->ground_y = actorx->world.position.y + ground_dist;
    actor_info->ut_count = mCoBG_ActorFearture2CheckRange(actor_info);
    actor_info->wall_height.top = 0.0f;
    actor_info->wall_height.bot = 0.0f;
    actor_info->wall_info[0].angleY = 0xB6;
    actor_info->wall_info[1].angleY = 0xB6;
    actor_info->wall_info[0].type = mCoBG_WALL_TYPE_NUM;
    actor_info->wall_info[1].type = mCoBG_WALL_TYPE_NUM;
    actor_info->check_type = check_type;
    if (F32_IS_ZERO(actor_info->speed_xz1[0]) && F32_IS_ZERO(actor_info->speed_xz1[1])) {
        actor_info->_64 = 1;
    } else {
        actor_info->_64 = 0;
    }
}

static void mCoBG_GiveRevposToActor(xyz_t* actor_revpos, xyz_t revpos) {
    if (actor_revpos != NULL) {
        *actor_revpos = revpos;
    }
}

static void mCoBG_MoveActorWithMoveBg_NotOnMoveBg(ACTOR* actorx) {
    // nothing
}

static void mCoBG_MoveActorWithMoveBg_OnMoveBg(ACTOR* actorx) {
    mCoBG_bg_regist_c* regist = mCoBG_Idx2RegistPointer(actorx->shape_info.move_bg_idx);

    if (regist != NULL) {
        xyz_t move;
        xyz_t* pos_p = regist->wpos;
        xyz_t* last_pos_p = regist->last_wpos;

        if (pos_p != NULL && last_pos_p != NULL) {
            move.x = pos_p->x - last_pos_p->x;
            move.y = pos_p->y - last_pos_p->y;
            move.z = pos_p->z - last_pos_p->z;

            actorx->world.position.x += move.x;
            actorx->world.position.y += move.y;
            actorx->world.position.z += move.z;
        }
    }
}

typedef void (*mCoBG_MOVE_BG_MOVE_ACTOR_PROC)(ACTOR* actorx);

static void mCoBG_MoveActorWithMoveBg(ACTOR* actorx) {
    static mCoBG_MOVE_BG_MOVE_ACTOR_PROC move_bg_move_actor_proc[] = { &mCoBG_MoveActorWithMoveBg_NotOnMoveBg, &mCoBG_MoveActorWithMoveBg_OnMoveBg };

    (*move_bg_move_actor_proc[actorx->bg_collision_check.result.is_on_move_bg_obj])(actorx);
}

static void mCoBG_RoomScopeCheck(ACTOR* actorx, f32 range, f32 ground_dist) {
    if (actorx->id == mAc_PROFILE_HOUSE_GOKI) {
        int scene = Save_Get(scene_no);
        static xyz_t base_pos = { mFI_UT_WORLDSIZE_X_F, 0.0f, mFI_UT_WORLDSIZE_Z_F };

        if (scene == SCENE_MY_ROOM_S) {
            mCoBG_ScopeWallCheck(actorx, &base_pos, 160.0f, 160.0f, range, ground_dist);
        } else if (scene == SCENE_MY_ROOM_M || scene == SCENE_MY_ROOM_LL2) {
            mCoBG_ScopeWallCheck(actorx, &base_pos, 240.0f, 240.0f, range, ground_dist);
        } else if (scene == SCENE_MY_ROOM_L || scene == SCENE_MY_ROOM_LL1) {
            mCoBG_ScopeWallCheck(actorx, &base_pos, 320.0f, 320.0f, range, ground_dist);
        }
    }
}

extern void mCoBG_BgCheckControll_RemoveDirectedUnitColumn(xyz_t* actor_revpos, ACTOR* actorx, f32 range, f32 ground_dist, s16 attr_wall, s16 rev_type, s16 check_type, int ux, int uz) {
    s_xyz angle = { 0.0f, 0.0f, 0.0f };
    mCoBG_Check_c prev_check = actorx->bg_collision_check;

    mCoBG_MoveActorWithMoveBg(actorx);
    mCoBG_InitRevpos(&l_ActorInf.rev_pos);
    mCoBG_GetCurrentCenterPosition(&l_ActorInf.center_pos, actorx);
    mCoBG_GetOldCenterPosition(&l_ActorInf.old_center_pos, actorx);
    mCoBG_MakeActorInf(&l_ActorInf, actorx, range, ground_dist, check_type, ux, uz);
    mCoBG_WallCheck(actorx, &l_ActorInf, attr_wall, &prev_check);
    actorx->bg_collision_check.result.unk_flag1 = l_ActorInf._64;
    mCoBG_GroundCheck(&l_ActorInf.rev_pos, &l_ActorInf, actorx, ground_dist, &actorx->bg_collision_check.result, &angle, attr_wall);
    mCoBG_MoveBgGroundCheck(&l_ActorInf.rev_pos, &l_ActorInf, actorx, &actorx->bg_collision_check.result, &angle);
    mCoBG_CarryOutReverse(actorx, l_ActorInf.rev_pos, rev_type);
    mCoBG_GiveRevposToActor(actor_revpos, l_ActorInf.rev_pos);
    mCoBG_RoomScopeCheck(actorx, range, ground_dist);
    l_ActorInf._68 = -1;
    l_ActorInf._6C = -1;
}

extern void mCoBG_BgCheckControll(xyz_t* actor_revpos, ACTOR* actorx, f32 range, f32 ground_dist, s16 attr_wall, s16 rev_type, s16 check_type) {
    mCoBG_BgCheckControll_RemoveDirectedUnitColumn(actor_revpos, actorx, range, ground_dist, attr_wall, rev_type, check_type, -1, -1);
}

extern void mCoBG_WallCheckOnly(xyz_t* actor_revpos, ACTOR* actorx, f32 range, f32 ground_dist, s16 rev_type, s16 check_type) {
    s16 attr_wall = FALSE;
    mCoBG_Check_c prev_check = actorx->bg_collision_check;

    mCoBG_InitRevpos(&l_ActorInf.rev_pos);
    mCoBG_GetCurrentCenterPosition(&l_ActorInf.center_pos, actorx);
    mCoBG_GetOldCenterPosition(&l_ActorInf.old_center_pos, actorx);
    mCoBG_MakeActorInf(&l_ActorInf, actorx, range, ground_dist, check_type, -1, -1);
    mCoBG_WallCheck(actorx, &l_ActorInf, attr_wall, &prev_check);
    actorx->bg_collision_check.result.unk_flag1 = l_ActorInf._64;
    mCoBG_CarryOutReverse(actorx, l_ActorInf.rev_pos, rev_type);
    mCoBG_GiveRevposToActor(actor_revpos, l_ActorInf.rev_pos);
    mCoBG_RoomScopeCheck(actorx, range, ground_dist);
}

extern void mCoBG_GroundCheckOnly(xyz_t* actor_revpos, ACTOR* actorx, f32 range, f32 ground_dist, s16 rev_type) {
    s_xyz angle = { 0.0f, 0.0f, 0.0f };

    mCoBG_MoveActorWithMoveBg(actorx);
    mCoBG_InitRevpos(&l_ActorInf.rev_pos);
    mCoBG_GetCurrentCenterPosition(&l_ActorInf.center_pos, actorx);
    mCoBG_GetOldCenterPosition(&l_ActorInf.old_center_pos, actorx);
    mCoBG_GetSpeedByWpos(l_ActorInf.speed_xz0, actorx);
    mCoBG_MakeActorInf(&l_ActorInf, actorx, 0.0f, ground_dist, mCoBG_CHECK_TYPE_NORMAL, -1, -1);
    mCoBG_GroundCheck(&l_ActorInf.rev_pos, &l_ActorInf, actorx, ground_dist, &actorx->bg_collision_check.result, &angle, FALSE);
    mCoBG_CarryOutReverse(actorx, l_ActorInf.rev_pos, rev_type);
    mCoBG_GiveRevposToActor(actor_revpos, l_ActorInf.rev_pos);
}

static ACTOR Virtual_Actor;

extern void mCoBG_VirtualBGCheck(xyz_t* rev_pos_p, mCoBG_Check_c* bg_check, const xyz_t* start_pos_p,
                                 const xyz_t* end_pos_p, s16 angle_y, s16 water_flag, s16 ground_flag, f32 range,
                                 f32 ground_dist, s16 attr_wall, s16 rev_type, s16 check_type) {
    ACTOR* actorx = &Virtual_Actor;

    bzero(actorx, sizeof(ACTOR));
    actorx->world.position = *end_pos_p;
    actorx->last_world_position = *start_pos_p;
    actorx->bg_collision_check.result.is_in_water = (s16)water_flag;
    actorx->bg_collision_check.result.on_ground = (s16)ground_flag;
    actorx->shape_info.rotation.y = angle_y;
    mCoBG_BgCheckControll(rev_pos_p, actorx, range, ground_dist, attr_wall, rev_type, check_type);
    *bg_check = actorx->bg_collision_check;
}
