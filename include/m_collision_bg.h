#ifndef M_COLLISION_BG_H
#define M_COLLISION_BG_H

#include "types.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

enum field_layer {
  mCoBG_LAYER0,
  mCoBG_LAYER1,
  mCoBG_LAYER2,
  mCoBG_LAYER3,

  mCoBG_LAYER_NUM
};

enum background_attribute {
  /* TODO: finish */
  mCoBG_ATTRIBUTE_GRASS0,
  mCoBG_ATTRIBUTE_GRASS1,
  mCoBG_ATTRIBUTE_GRASS2,
  mCoBG_ATTRIBUTE_GRASS3,
  mCoBG_ATTRIBUTE_SOIL0,
  mCoBG_ATTRIBUTE_SOIL1,
  mCoBG_ATTRIBUTE_SOIL2,
  mCoBG_ATTRIBUTE_BUSH = 9,
  mCoBG_ATTRIBUTE_WAVE = 11,
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
  mCoBG_ATTRIBUTE_SAND,
  mCoBG_ATTRIBUTE_WOOD,
  mCoBG_ATTRIBUTE_SEA,
};

enum {
  mCoBG_PLANT0 = 0, /* Stay a sapling */
  mCoBG_PLANT1 = 1, /* Grow until the first stage of growth */
  mCoBG_PLANT2 = 2, /* Grow until the second stage of growth */
  mCoBG_PLANT3 = 3, /* Grow until the third stage of growth */
  mCoBG_PLANT4 = 4, /* Fully grow */

  mCoBG_KILL_PLANT = 7 /* No growth, all plants die on this unit  */
};

/* sizeof(mCoBG_CollisionData_c) == 4*/
typedef struct collision_bg_data_s {
  /* 1------- -------- -------- -------- */ u32 shape:1; /* collision shape */
  /* -11111-- -------- -------- -------- */ u32 center:5;
  /* ------11 111----- -------- -------- */ u32 top_left:5;
  /* -------- ---11111 -------- -------- */ u32 bot_left:5;
  /* -------- -------- 11111--- -------- */ u32 top_right:5;
  /* -------- -------- -----111 11------ */ u32 bot_right:5;
  /* -------- -------- -------- --111111 */ u32 unit_attribute:6; /* background_attribute type */
} mCoBG_CollisionData_c;

/* sizeof (mCoBG_Collision_u) == 4 */
typedef union collision_bg_u {
  u32 raw;
  mCoBG_CollisionData_c data;
} mCoBG_Collision_u;

typedef struct collision_bg_check_result_s {
  u32 on_ground:1;
  u32 hit_attribute_wall:5;
  u32 hit_wall:5;
  u32 hit_wall_count:3;
  u32 unk_flag0:1;
  u32 unit_attribute:6;
  u32 is_on_move_bg_obj:1;
  u32 is_in_water:1;
  u32 unk_flag1:1;
  u32 unk_flag2:1;
  u32 unk_flag3:1;
  u32 unk_flag4:1;
  u32 unk_flag5:1;
  u32 unk_flag6:4;
} mCoBG_CheckResult_c;

typedef struct wall_info_s {
  s16 angleY;
  s16 type;
} mCoBG_WallInfo_c;

typedef struct collision_bg_check_s {
  mCoBG_Collision_u collision_units[5];
  mCoBG_CheckResult_c result;
  f32 wall_top_y;
  f32 wall_bottom_y;
  f32 ground_y;
  mCoBG_WallInfo_c wall_info[2];
  s16 in_front_wall_angle_y;
} mCoBG_Check_c;

extern u32 mCoBG_Wpos2BgAttribute_Original(xyz_t wpos);
extern u32 mCoBG_Wpos2Attribute(xyz_t wpos, char* is_diggable);
extern int mCoBG_CheckWaterAttribute(u32 attribute);
extern f32 mCoBG_GetBgY_AngleS_FromWpos(s_xyz* angle_to_ground, xyz_t wpos, f32 offset_y);
extern f32 mCoBG_GetShadowBgY_AngleS_FromWpos(f32, s_xyz*, xyz_t);
extern int mCoBG_CheckWaterAttribute_OutOfSea(u32 attribute);
extern int mCoBG_CheckHole_OrgAttr(u32 attribute);
extern f32 mCoBG_GetBgY_OnlyCenter_FromWpos2(xyz_t wpos, f32 foot_dist);
extern int mCoBG_Attribute2CheckPlant(u32 attribute, const xyz_t* wpos);
extern void mCoBG_BgCheckControll(xyz_t* reverse_pos, ACTOR* actor, f32 check_range, f32 offset_y, s16 wall_attr_check, s16 no_reverse, s16 check_type);
extern int mCoBG_Height2GetLayer(f32 height);
extern void mCoBG_SetPlussOffset(xyz_t wpos, s16 offset, s16 new_attrib);
extern int mCoBG_GetLayer(const xyz_t* wpos); 
extern int mCoBG_BnumUnum2HoleNumber(int block_x, int block_z, int ut_x, int ut_z);
extern u32 mCoBG_UtNum2BgAttr(int ut_x, int ut_z);
extern f32 mCoBG_UtNum2UtCenterY(int ut_x, int ut_z);
extern int mCoBG_CheckCliffAttr(u32 attribute);
extern int mCoBG_Change2PoorAttr(mCoBG_Collision_u* col);

extern void mCoBG_InitMoveBgData();
extern void mCoBG_InitBlockBgCheckMode();
extern void mCoBG_InitDecalCircle();

extern void mCoBG_CalcTimerDecalCircle();

extern f32 mCoBG_GetWaterHeight_File(xyz_t wpos, char* file, int line);
#define mCoBG_GetWaterHeight(wpos) mCoBG_GetWaterHeight_File(wpos, __FILE__, __LINE__)

extern int mCoBG_CheckSandUt_ForFish(xyz_t* wpos);

#ifdef __cplusplus
}
#endif

#endif
