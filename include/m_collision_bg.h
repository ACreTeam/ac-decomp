#ifndef M_COLLISION_BG_H
#define M_COLLISION_BG_H

#include "types.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

enum background_attribute {
  /* TODO: finish */
  mCoBG_ATTRIBUTE_WAVE = 11,
  mCoBG_ATTRIBUTE_WATERFALL = 13,
  mCoBG_ATTRIBUTE_SEA = 24
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

extern u32 mCoBG_Wpos2BgAttribute_Original(xyz_t wpos);
extern u32 mCoBG_Wpos2Attribute(xyz_t wpos, char* is_diggable);
extern int mCoBG_CheckWaterAttribute(u32 attribute);
extern f32 mCoBG_GetBgY_AngleS_FromWpos(s_xyz* angle_to_ground, xyz_t wpos, f32 offset);
extern int mCoBG_CheckWaterAttribute_OutOfSea(u32 attribute);

extern f32 mCoBG_GetWaterHeight_File(xyz_t wpos, char* file, int line);
#define mCoBG_GetWaterHeight(wpos) mCoBG_GetWaterHeight_File(wpos, __FILE__, __LINE__)

extern int mCoBG_CheckSandUt_ForFish(xyz_t* wpos);

#ifdef __cplusplus
}
#endif

#endif
