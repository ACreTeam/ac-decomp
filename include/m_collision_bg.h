#ifndef M_COLLISION_BG_H
#define M_COLLISION_BG_H

#include "types.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mCoBG_HEIGHT_MAX 31

enum field_layer {
  mCoBG_LAYER0,
  mCoBG_LAYER1,
  mCoBG_LAYER2,
  mCoBG_LAYER3,

  mCoBG_LAYER_NUM
};

enum {
  mCoBG_FTR_TYPEA,
  mCoBG_FTR_TYPEB_0,
  mCoBG_FTR_TYPEB_180,
  mCoBG_FTR_TYPEB_270,
  mCoBG_FTR_TYPEB_90,
  mCoBG_FTR_TYPEC,

  mCoBG_FTR_TYPE_NUM
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
  mCoBG_ATTRIBUTE_STONE,
  mCoBG_ATTRIBUTE_FLOOR,
  mCoBG_ATTRIBUTE_BUSH,
  mCoBG_ATTRIBUTE_HOLE,
  mCoBG_ATTRIBUTE_WAVE,
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
  // ...
};

enum {
  mCoBG_PLANT0 = 0, /* Stay a sapling */
  mCoBG_PLANT1 = 1, /* Grow until the first stage of growth */
  mCoBG_PLANT2 = 2, /* Grow until the second stage of growth */
  mCoBG_PLANT3 = 3, /* Grow until the third stage of growth */
  mCoBG_PLANT4 = 4, /* Fully grow */

  mCoBG_KILL_PLANT = 7 /* No growth, all plants die on this unit  */
};

enum {
  mCoBG_DIRECT_N,
  mCoBG_DIRECT_W,
  mCoBG_DIRECT_S,
  mCoBG_DIRECT_E,
  mCoBG_DIRECT_NW,
  mCoBG_DIRECT_NE,
  mCoBG_DIRECT_SE,
  mCoBG_DIRECT_SW,

  mCoBG_DIRECT_NUM
};

enum {
  mCoBG_AREA_N,
  mCoBG_AREA_W,
  mCoBG_AREA_S,
  mCoBG_AREA_E,

  mCoBG_AREA_NUM
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
  mCoBG_CollisionData_c data;
  u32 raw;
} mCoBG_Collision_u;

typedef struct collision_unit_info_s {
  mCoBG_Collision_u* collision;
  f32 leftUp_offset;
  f32 leftDown_offset;
  f32 rightDown_offset;
  f32 rightUp_offset;
  f32 base_height;
  f32 pos_x;
  f32 pos_z;
  int ut_x;
  int ut_z;
  int shape;
  u8 attribute;
  mActor_name_t item;
} mCoBG_UnitInfo_c;

#define mCoBG_HIT_WALL       (1 << 0) /* in contact with *any* wall        */
#define mCoBG_HIT_WALL_FRONT (1 << 1) /* in contact with wall to the front */
#define mCoBG_HIT_WALL_RIGHT (1 << 2) /* in contact with wall to the right */
#define mCoBG_HIT_WALL_LEFT  (1 << 3) /* in contact with wall to the left  */
#define mCoBG_HIT_WALL_BACK  (1 << 4) /* in contact with wall to the back  */

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

typedef struct bg_side_contact_s {
  s16 name;
  s16 angle;
} mCoBG_side_contact_c;

typedef struct bg_contact_s {
  mCoBG_side_contact_c side_contact[5];
  int side_count;
  s16 on_contact_names[5];
  int on_count;
} mCoBG_bg_contact_c;

typedef struct bg_size_s {
  f32 right_size; // x |   *->
  f32 left_size; //  x | <-*
  f32 up_size; //   z | ^
  f32 down_size; // z | v
} mCoBG_bg_size_c;

typedef struct bg_register_s {
  xyz_t* wpos;
  xyz_t* last_wpos;
  s16* angle_y;
  mCoBG_bg_contact_c* contact;
  mCoBG_bg_size_c* bg_size;
  xyz_t* base_ofs;
  f32 height;
  u32 attribute;
  f32 active_dist;
  f32* scale_percent;
} mCoBG_bg_regist_c;

typedef struct collision_offset_table_s {
  u8 unit_attribute;
  s8 centerRight_offset; 
  s8 leftUp_offset;
  s8 leftDown_offset;
  s8 rightDown_offset;
  s8 rightUp_offset;
  s8 shape;
} mCoBG_OffsetTable_c;

typedef struct collision_actor_info_s {
  mActor_name_t name_id;
  u8 _02;
  u8 on_ground;
  u8 _04;
  u8 in_water;
  u8 _06[2]; // alignment?
  mCoBG_CheckResult_c* check_res_p;
  xz_t speed_xz0;
  xz_t speed_xz1;
  xyz_t center_pos;
  xyz_t old_center_pos;
  xyz_t rev_pos;
  u8 _40[4];
  f32 _44;
  f32 _48;
  f32 _4C;
  u8 _50[0x20];
} mCoBG_ActorInf_c;

extern u32 mCoBG_Wpos2BgAttribute_Original(xyz_t wpos);
extern u32 mCoBG_Wpos2Attribute(xyz_t wpos, s8* is_diggable);
extern int mCoBG_CheckWaterAttribute(u32 attribute);
extern f32 mCoBG_GetBgY_AngleS_FromWpos(s_xyz* angle_to_ground, xyz_t wpos, f32 offset_y);
extern f32 mCoBG_GetShadowBgY_AngleS_FromWpos(f32, s_xyz*, xyz_t);
extern int mCoBG_CheckWaterAttribute_OutOfSea(u32 attribute);
extern int mCoBG_CheckHole_OrgAttr(u32 attribute);
extern f32 mCoBG_GetBgY_OnlyCenter_FromWpos(xyz_t wpos, f32 dist);
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
extern void mCoBG_SetPluss5PointOffset_file(xyz_t pos, mCoBG_OffsetTable_c offsetptr, const char* file, int line);
extern int mCoBG_Change2PoorAttr(mCoBG_Collision_u* col);
extern int mCoBG_CheckHole(xyz_t wpos);
extern int mCoBG_CheckSkySwing(xyz_t wpos);
extern void mCoBG_Ut2SetDefaultOffset(int ut_x, int ut_z);
extern int mCoBG_CheckWaveAttr(u32 attribute);
extern int mCoBG_CheckPlant(xyz_t wpos);
extern void mCoBG_InitBoatCollision();
extern int mCoBG_CheckAttribute_BallRolling(s16* angles, const xyz_t* wpos);
extern f32 mCoBG_CheckBallRollingArea(s16 angle, const xyz_t* wpos);
extern int mCoBG_ExistHeightGap_KeepAndNow_Detail(xyz_t wpos);
extern int mCoBG_GetHoleNumber(xyz_t wpos);
extern int mCoBG_Attr2CheckPlaceNpc(u32 attribute);
extern int mCoBG_ExistHeightGap_KeepAndNow(xyz_t wpos);
extern void mCoBG_GetNorm_By3Point(xyz_t* norm, xyz_t* p0, xyz_t* p1, xyz_t* p2);
extern int mCoBG_SearchWaterLimitDistN(xyz_t* water_pos, xyz_t wpos, s16 angle, float max_dist, int divisor);
extern f32 mCoBG_GetBalloonGroundY(const xyz_t* pos);
extern void mCoBG_MakeBoatCollision(ACTOR* actor, xyz_t* pos, s16* angle_y);
extern void mCoBG_DeleteBoatCollision(ACTOR* actor);
extern void mCoBG_WaveCos2BgCheck(f32 wave_cos);

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
