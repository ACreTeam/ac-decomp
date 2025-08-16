#ifndef M_COLLISION_BG_H
#define M_COLLISION_BG_H

#include "types.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mCoBG_HEIGHT_MAX 31

#define mCoBG_ATR_NO_PLACE (0 << 3)
#define mCoBG_ATR_PLACE (1 << 3)

#define mCoBG_ATR_NO_NPC (0 << 4)
#define mCoBG_ATR_NPC (1 << 4)

enum {
    mCoBG_PLANT0 = 0, /* Stay a sapling */
    mCoBG_PLANT1 = 1, /* Grow until the first stage of growth */
    mCoBG_PLANT2 = 2, /* Grow until the second stage of growth */
    mCoBG_PLANT3 = 3, /* Grow until the third stage of growth */
    mCoBG_PLANT4 = 4, /* Fully grow */

    mCoBG_KILL_PLANT = 7 /* No growth, all plants die on this unit  */
};

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

    mCoBG_ATTRIBUTE_25, // wave_se2
    mCoBG_ATTRIBUTE_26, // wave_sw2
    mCoBG_ATTRIBUTE_27, // wood bridge nw
    mCoBG_ATTRIBUTE_28, // wood bridge sw
    mCoBG_ATTRIBUTE_29, // wood bridge se
    mCoBG_ATTRIBUTE_30, // wood bridge ne
    mCoBG_ATTRIBUTE_31, // wood bridge center
    mCoBG_ATTRIBUTE_32, // stone bridge n
    mCoBG_ATTRIBUTE_33, // stone bridge e
    mCoBG_ATTRIBUTE_34, // stone bridge w
    mCoBG_ATTRIBUTE_35, // stone bridge s
    mCoBG_ATTRIBUTE_36, // wave_s
    mCoBG_ATTRIBUTE_37, // wave_se
    mCoBG_ATTRIBUTE_38, // wave_sw
    mCoBG_ATTRIBUTE_39, // river bank nw
    mCoBG_ATTRIBUTE_40, // river bank sw
    mCoBG_ATTRIBUTE_41, // river bank se
    mCoBG_ATTRIBUTE_42, // river bank ne
    mCoBG_ATTRIBUTE_43, // grass 3 north (river)
    mCoBG_ATTRIBUTE_44, // grass 3 east (river)
    mCoBG_ATTRIBUTE_45, // grass 3 west (river)
    mCoBG_ATTRIBUTE_46, // grass 3 south (river)
    mCoBG_ATTRIBUTE_47, // grass 4 north (cliff)
    mCoBG_ATTRIBUTE_48, // grass 4 east (cliff)
    mCoBG_ATTRIBUTE_49, // grass 4 west (cliff)
    mCoBG_ATTRIBUTE_50, // grass 4 south (cliff)
    mCoBG_ATTRIBUTE_51, // grass 4 tunnel left upper
    mCoBG_ATTRIBUTE_52, // grass 4 tunnel left lower
    mCoBG_ATTRIBUTE_53, // grass 4 tunnel right lower
    mCoBG_ATTRIBUTE_54, // grass 4 tunnel right upper
    mCoBG_ATTRIBUTE_55, // grass 3 north west (cliff)
    mCoBG_ATTRIBUTE_56, // grass 3 south west (cliff)
    mCoBG_ATTRIBUTE_57, // grass 3 south east (cliff)
    mCoBG_ATTRIBUTE_58, // grass 3 north east (cliff)
    mCoBG_ATTRIBUTE_59, // grass 3 north west (river bank)
    mCoBG_ATTRIBUTE_60, // grass 3 south west (river bank)
    mCoBG_ATTRIBUTE_61, // grass 3 south east (river bank)
    mCoBG_ATTRIBUTE_62, // grass 3 north east (river bank)
    mCoBG_ATTRIBUTE_63, // slate (slope)
    // ...

    mCoBG_ATTRIBUTE_NONE = 100
};

enum {
    mCoBG_DIM_XY,
    mCoBG_DIM_XZ,
    mCoBG_DIM_YZ,
    mCoBG_DIM_ALL,

    mCoBG_DIM_NUM
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

enum {
    mCoBG_BLOCK_BGCHECK_MODE_NORMAL,
    mCoBG_BLOCK_BGCHECK_MODE_INTRO_DEMO,

    mCoBG_BLOCK_BGCHECK_MODE_NUM
};

extern int mCoBG_block_bgcheck_mode;

/* sizeof(mCoBG_CollisionData_c) == 4*/
typedef struct collision_bg_data_s {
    /* 1------- -------- -------- -------- */ u32 slate_flag : 1; /* collision shape */
    /* -11111-- -------- -------- -------- */ u32 center : 5;
    /* ------11 111----- -------- -------- */ u32 top_left : 5;
    /* -------- ---11111 -------- -------- */ u32 bot_left : 5;
    /* -------- -------- 11111--- -------- */ u32 bot_right : 5;
    /* -------- -------- -----111 11------ */ u32 top_right : 5;
    /* -------- -------- -------- --111111 */ u32 unit_attribute : 6; /* background_attribute type */
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
    f32 unit_pos[2];
    int ut_x;
    int ut_z;
    u32 slate_flag;
    u8 attribute;
    mActor_name_t item;
} mCoBG_UnitInfo_c;

#define mCoBG_DIDNT_HIT_WALL 0
#define mCoBG_HIT_WALL (1 << 0)       /* in contact with *any* wall        */
#define mCoBG_HIT_WALL_FRONT (1 << 1) /* in contact with wall to the front */
#define mCoBG_HIT_WALL_RIGHT (1 << 2) /* in contact with wall to the right */
#define mCoBG_HIT_WALL_LEFT (1 << 3)  /* in contact with wall to the left  */
#define mCoBG_HIT_WALL_BACK (1 << 4)  /* in contact with wall to the back  */

typedef struct collision_bg_check_result_s {
    u32 on_ground : 1;
    u32 hit_attribute_wall : 5;
    //
    u32 hit_wall : 5; // 2 bits in prev byte
    u32 hit_wall_count : 3;
    u32 jump_flag : 1;
    //
    u32 unit_attribute : 6; // 1 bit in prev byte
    u32 is_on_move_bg_obj : 1;
    u32 is_in_water : 1;
    u32 unk_flag1 : 1;
    //
    u32 unk_flag2 : 1;
    u32 unk_flag3 : 1;
    u32 unk_flag4 : 1;
    u32 unk_flag5 : 1;
    u32 unk_flag6 : 4;
} mCoBG_CheckResult_c;

typedef struct wall_info_s {
    s16 angleY;
    s16 type;
} mCoBG_WallInfo_c;

enum {
    mCoBG_WALL_TYPE0,
    mCoBG_WALL_TYPE1,

    // TODO
    mCoBG_WALL_TYPE_NUM
};

enum {
    mCoBG_WALL_UP,
    mCoBG_WALL_LEFT,
    mCoBG_WALL_DOWN,
    mCoBG_WALL_RIGHT,
    mCoBG_WALL_SLATE_UP,
    mCoBG_WALL_SLATE_DOWN,

    mCoBG_WALL_NUM
};

enum {
    mCoBG_NORM_DIRECT_UP,
    mCoBG_NORM_DIRECT_LEFT,
    mCoBG_NORM_DIRECT_DOWN,
    mCoBG_NORM_DIRECT_RIGHT,

    mCoBG_NORM_DIRECT_NUM
};

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

typedef struct bg_on_contact_s {
    s16 name;
} mCoBG_on_contact_c;

typedef struct bg_on_contact_inf_s {
    mCoBG_on_contact_c contact[5];
    int count;
} mCoBG_on_contact_info_c;

typedef struct bg_contact_s {
    mCoBG_side_contact_c side_contact[5];
    int side_count;
    mCoBG_on_contact_info_c on_contact;
} mCoBG_bg_contact_c;

typedef struct bg_size_s {
    f32 right_size; // x |   *->
    f32 left_size;  //  x | <-*
    f32 up_size;    //   z | ^
    f32 down_size;  // z | v
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

#define mCoBG_MOVE_REGIST_MAX 64
typedef struct bg_mgr_s {
    mCoBG_bg_regist_c* regist_p[mCoBG_MOVE_REGIST_MAX];
    int count;
} mCoBG_mBgMgr_c;

typedef struct collision_offset_table_s {
    u8 unit_attribute;
    s8 centerRight_offset;
    s8 leftUp_offset;
    s8 leftDown_offset;
    s8 rightDown_offset;
    s8 rightUp_offset;
    s8 shape;
} mCoBG_OffsetTable_c;

typedef struct wall_height_s {
    f32 top;
    f32 bot;
} mCoBG_WallHeight_c;

#define mCoBG_WALL_COL_NUM 2

typedef struct collision_actor_info_s {
    s16 name;
    u8 check_type;
    u8 old_on_ground;
    u8 _04;
    u8 old_in_water;
    // u8 _06[2]; // alignment?
    mCoBG_CheckResult_c* check_res_p;
    f32 speed_xz0[2];
    f32 speed_xz1[2];
    xyz_t center_pos;
    xyz_t old_center_pos;
    xyz_t rev_pos;
    f32 range;
    f32 ground_dist;
    f32 old_ground_y;
    f32 ground_y;
    mCoBG_WallHeight_c wall_height;
    mCoBG_WallInfo_c wall_info[mCoBG_WALL_COL_NUM];
    s16 ut_count;
    u32 _64;
    int _68;
    int _6C;
} mCoBG_ActorInf_c;

enum {
    mCoBG_UNIT_RADIAN,
    mCoBG_UNIT_DEGREE,
    mCoBG_UNIT_SHORT,

    mCoBG_UNIT_NUM
};

enum {
    mCoBG_CHECK_TYPE_NORMAL,
    mCoBG_CHECK_TYPE_PLAYER,

    mCoBG_CHECK_TYPE_NUM
};

enum {
    mCoBG_REVERSE_TYPE_REVERSE,
    mCoBG_REVERSE_TYPE_NO_REVERSE,

    mCoBG_REVERSE_TYPE_NUM
};

#define mCoBG_LINE_CHECK_WALL (1 << 0)
#define mCoBG_LINE_CHECK_GROUND (1 << 1)
#define mCoBG_LINE_CHECK_WATER (1 << 2)
#define mCoBG_LINE_CHECK_UNDERWATER (1 << 3)

typedef int (*mCoBG_COLUMN_CHECK_ITEM_TYPE_PROC)(mActor_name_t item);

extern u32 mCoBG_Wpos2Attribute(xyz_t pos, s8* cant_dig);
extern void mCoBG_InitBgCheckResult(mCoBG_CheckResult_c* result);
extern void mCoBG_BgCheckControll_RemoveDirectedUnitColumn(xyz_t* actor_revpos, ACTOR* actorx, f32 range, f32 ground_dist, s16 attr_wall, s16 rev_type, s16 check_type, int ux, int uz);
extern void mCoBG_BgCheckControll(xyz_t* actor_revpos, ACTOR* actorx, f32 range, f32 ground_dist, s16 attr_wall, s16 rev_type, s16 check_type);
extern void mCoBG_WallCheckOnly(xyz_t* actor_revpos, ACTOR* actorx, f32 range, f32 ground_dist, s16 rev_type, s16 check_type);
extern void mCoBG_GroundCheckOnly(xyz_t* actor_revpos, ACTOR* actorx, f32 range, f32 ground_dist, s16 rev_type);
extern void mCoBG_VirtualBGCheck(xyz_t* rev_pos_p, mCoBG_Check_c* bg_check, const xyz_t* start_pos_p,
                                 const xyz_t* end_pos_p, s16 angle_y, s16 water_flag, s16 ground_flag, f32 range,
                                 f32 ground_dist, s16 attr_wall, s16 rev_type, s16 check_type);

extern void mCoBG_RotateY(f32* pos, f32 rad);
extern f32 mCoBG_GetVectorProductin2D(f32* vec0_xz, f32* vec1_xz);
extern int mCoBG_JudgeCrossTriangleAndLine2D(xyz_t v0, xyz_t v1, xyz_t v2, xyz_t p, int dim);
extern int mCoBG_GetDimension2Idx(f32 p0, f32 p1, f32 p2);
extern int mCoBG_GetCrossTriangleAndLine3D(xyz_t* cross, xyz_t v0, xyz_t v1, xyz_t v2, xyz_t line0, xyz_t line1);
extern f32 mCoBG_GetVectorScalar2D(f32* v0, f32* v1);
extern int mCoBG_GetCrossJudge_2Vector(f32* vec0_p0, f32* vec0_p1, f32* vec1_p0, f32* vec1_p1);
extern void mCoBG_GetCross2Line(f32* cross, f32* line0_p0, f32* line0_p1, f32* line1_p0, f32* line1_p1);
extern f32 mCoBG_Get2VectorAngleF(f32* v0, f32* v1, u8 unit);
extern s16 mCoBG_Get2VectorAngleS(f32* v0, f32* v1);
extern int mCoBG_GetCrossLineAndPerpendicular(f32* cross, f32* p0, f32* p1, f32* target);
extern int mCoBG_GetPointInfoFrontLine(f32* start, f32* point, f32* normal);
extern int mCoBG_GetDistPointAndLine2D(f32* dist, f32* line0, f32* line1, f32* point);
extern int mCoBG_GetDistPointAndLine2D_Norm(f32* dist, f32* line0, f32* line1, f32* normal, f32* point);
extern int mCoBG_GetCrossCircleAndLine2Dvector(f32* cross0, f32* cross1, f32* point, f32* vec, f32* center, f32 radius);
extern int mCoBG_GetCrossCircleAndLine2D(f32* cross0, f32* cross1, f32* p0, f32* p1, f32* center, f32 radius);
extern void mCoBG_GetReverseVector2D(f32* vec);
extern void mCoBG_GetUnitVector2D(f32* vec);
extern int mCoBG_JudgePointInCircle_Xyz(const xyz_t* p, const xyz_t* center, f32 radius);
extern int mCoBG_JudgePointInCircle(f32* p, f32* center, f32 radius);
extern f32 mCoBG_GetAbsBiggerF(f32 a, f32 b);
extern void mCoBG_GetNorm_By2Vector(f32* v0, f32* v1, xyz_t* normal);
extern void mCoBG_GetNorm_By3Point(xyz_t* normal, f32* v0, f32* v1, f32* v2);
extern int mCoBG_RangeCheckLinePoint(f32* start, f32* end, f32* point);

extern void mCoBG_CalcTimerDecalCircle(void);
extern int mCoBG_RegistDecalCircle(const xyz_t* pos, f32 start_radius, f32 end_radius, s16 timer);
extern void mCoBG_InitDecalCircle(void);
extern void mCoBG_CrossOffDecalCircle(int idx);

extern int mCoBG_JudgeMoveBgGroundCheck(f32* point, f32* goal, f32 dist);
extern int mCoBG_GetMoveBgHeight(f32* move_bg_height, xyz_t* pos_p);
extern void mCoBG_InitMoveBgContact(mCoBG_bg_contact_c* contact);
extern int mCoBG_RegistMoveBg(mCoBG_bg_regist_c* regist, xyz_t* wpos, xyz_t* old_wpos, s16* angleY, f32 height,
                              mCoBG_bg_size_c* size, f32* scale_percent, mCoBG_bg_contact_c* contact, xyz_t* base_ofs,
                              int type, u32 attribute, f32 check_dist);
extern mCoBG_bg_regist_c* mCoBG_Idx2RegistPointer(int move_bg_idx);
extern void mCoBG_CrossOffMoveBg(int move_bg_idx);
extern void mCoBG_InitMoveBgData(void);
extern void mCoBG_InitBoatCollision(void);
extern void mCoBG_MakeBoatCollision(ACTOR* actor, xyz_t* pos, s16* angle_y);
extern void mCoBG_DeleteBoatCollision(ACTOR* actor);

extern void mCoBG_GetSlopeSlideVector(xyz_t* vec, xyz_t pos);
extern f32 mCoBG_GetBgY_AngleS_FromWpos(s_xyz* ground_angle, xyz_t pos, f32 ground_dist);
extern f32 mCoBG_GetBgY_OnlyCenter_FromWpos(xyz_t pos, f32 ground_dist);
extern f32 mCoBG_Wpos2BgUtCenterHeight_AddColumn(xyz_t pos);
extern f32 mCoBG_GetBgY_OnlyCenter_FromWpos2(xyz_t pos, f32 ground_dist);
extern void mCoBG_GetBgNorm_FromWpos(xyz_t* norm, xyz_t wpos);
extern int mCoBG_ScrollCheck(xyz_t start, xyz_t end, f32 radius);
extern int mCoBG_CheckPlace(xyz_t pos);
extern int mCoBG_UtCheckPlace(int ux, int uz);
extern int mCoBG_Attribute2CheckPlant(u32 attr, const xyz_t* pos);
extern int mCoBG_CheckPlant(xyz_t pos);
extern int mCoBG_Unit2CheckNpc(int ux, int uz);
extern int mCoBG_Wpos2CheckNpc(xyz_t pos);
extern int mCoBG_Attr2CheckPoorGround(u32 attr);
extern int mCoBG_Attr2CheckPlaceNpc(u32 attr);
extern int mCoBG_UtNum2BgAttr(int ux, int uz);
extern f32 mCoBG_UtNum2UtCenterY(int ux, int uz);
extern f32 mCoBG_UtNum2UtCenterY_Keep(int ux, int uz);
extern u32 mCoBG_Wpos2BgAttribute_Original(xyz_t pos);
extern int mCoBG_GetHoleNumber_ClData(mCoBG_Collision_u* col);
extern int mCoBG_GetHoleNumber(xyz_t pos);
extern int mCoBG_BnumUnum2HoleNumber(int bx, int bz, int b_ux, int b_uz);
extern int mCoBG_CheckHole_OrgAttr(u32 attr);
extern int mCoBG_CheckSandUt_ForFish(xyz_t* pos);
extern int mCoBG_CheckSandHole_ClData(mCoBG_Collision_u* col);
extern int mCoBG_BnumUnum2SandHole(int bx, int bz, int b_ux, int b_uz);
extern int mCoBG_CheckHole(xyz_t pos);
#if VERSION >= VER_GAFU01_00
extern int mCoBG_CheckAirSwing(xyz_t pos);
#else
extern int mCoBG_CheckAirSwing(xyz_t pos);
#endif
extern int mCoBG_CheckGrassX_ClData(mCoBG_Collision_u* col);
extern int mCoBG_CheckGrassX(const xyz_t* pos);
extern int mCoBG_CheckWave_ClData(mCoBG_Collision_u* col);
extern int mCoBG_CheckWave(const xyz_t* pos);
extern int mCoBG_CheckAcceptDesignSign(const xyz_t* pos_p);
extern f32 mCoBG_GetBgHeightGapBetweenNowDefault(xyz_t pos);
extern int mCoBG_ExistHeightGap_KeepAndNow(xyz_t pos);
extern int mCoBG_SearchWaterLimitDistN(xyz_t* water_pos, xyz_t pos, s16 angle, f32 dist_limit, int divide);
extern int mCoBG_CheckRoughPathInRoom(const xyz_t* pos);
extern f32 mCoBG_GetBalloonGroundY(const xyz_t* pos);
extern int mCoBG_CheckAttribute_BallRolling(s16* angle, const xyz_t* pos);
extern f32 mCoBG_CheckBallRollingArea(s16 angle, const xyz_t* pos);
extern f32 mCoBG_Wpos2GroundCheckOnly(const xyz_t* pos, f32 ground_dist);
extern int mCoBG_ExistHeightGap_KeepAndNow_Detail(xyz_t pos);
extern int mCoBG_Wpos2CheckSlateCol(const xyz_t* pos, int check_attr);
extern int mCoBG_WoodSoundEffect(const xyz_t* pos);
extern int mCoBG_CheckCliffAttr(u32 attr);
extern f32 mCoBG_GetShadowBgY_AngleS_FromWpos(s_xyz* ground_angle, xyz_t pos, f32 ground_dist);
extern int mCoBG_CheckUtFlat(const xyz_t* pos);
extern int mCoBG_Height2GetLayer(f32 height);
extern int mCoBG_GetLayer(const xyz_t* pos);

extern void mCoBG_InitBlockBgCheckMode(void);
extern int mCoBG_ChangeBlockBgCheckMode(int mode);
extern int mCoBG_GetBlockBgCheckMode(void);
extern xyz_t mCoBG_UniqueWallCheck(ACTOR* actorx, f32 range, f32 y_ofs);
extern xyz_t mCoBG_ScopeWallCheck(ACTOR* actorx, const xyz_t* base_pos, f32 x, f32 z, f32 range, f32 y_ofs);

extern void mCoBG_Ut2SetPlussOffset(int ux, int uz, s16 change_ofs, s16 attr);
extern void mCoBG_SetPlussOffset(xyz_t wpos, s16 change_ofs, s16 attr);
extern void mCoBG_SetAttribute(xyz_t pos, s16 attr);
extern void mCoBG_Ut2SetPluss5PointOffset_file(int ux, int uz, mCoBG_OffsetTable_c ofs_data, char* file, int line);
extern void mCoBG_SetPluss5PointOffset_file(xyz_t pos, mCoBG_OffsetTable_c ofs_data, char* file, int line);
extern int mCoBG_Change2PoorAttr(mCoBG_Collision_u* col);
extern void mCoBG_Ut2SetDefaultOffset(int ux, int uz);

extern int mCoBG_LineCheck_RemoveFg(xyz_t* rev, xyz_t start_pos, xyz_t end_pos, mCoBG_COLUMN_CHECK_ITEM_TYPE_PROC check_proc, int line_check_type);

#if VERSION >= VER_GAFU01_00
extern f32 mCoBG_Wpos2BgHeight_AngleSXXX(s_xyz* ground_angle, xyz_t pos, f32 ground_dist);
#else
extern f32 mCoBG_GetBgY_AngleS_FromWpos2(s_xyz* ground_angle, xyz_t pos, f32 ground_dist);
#endif
extern f32 mCoBG_GetWaterHeight_File(xyz_t pos, char* file, int line);
#define mCoBG_GetWaterHeight(wpos) mCoBG_GetWaterHeight_File(wpos, __FILE__, __LINE__)
extern int mCoBG_CheckWaterAttribute(u32 attr);
extern int mCoBG_CheckWaterAttribute_OutOfSea(u32 attr);
extern void mCoBG_WaveCos2BgCheck(f32 value);
extern f32 mCoBG_WaveCos(void);
extern int mCoBG_GetWaterFlow(xyz_t* flow, u32 attr);
extern int mCoBG_CheckWaveAttr(u32 attr);
extern int mCoBG_CheckSand2Sea(xyz_t* pos);

#if VERSION == VER_GAFU01_00
extern int mCoBG_GetCrossCircleAndLine2DvectorPlaneXZ_Xyz(xyz_t* cross1, xyz_t* cross2, const xyz_t* point, const xyz_t* vec, const xyz_t* center, f32 radius);
#endif

#ifdef __cplusplus
}
#endif

#endif
