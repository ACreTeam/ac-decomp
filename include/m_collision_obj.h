#ifndef M_COLLISION_OBJ_H
#define M_COLLISION_OBJ_H

#include "types.h"
#include "m_actor_type.h"
#include "sys_math3d.h"
#include "m_play_h.h"

#ifdef __cplusplus
extern "C" {
#endif

enum collision_type {
    ClObj_TYPE_JNT_SPH,
    ClObj_TYPE_PIPE,
    ClObj_TYPE_TRIS,

    ClObj_TYPE_NUM
};

#define CollisionCheck_FLAG_SKIP (1 << 0)

#define ClObj_GROUP_PLAYER (1 << 3) // 0x08
#define ClObj_GROUP_2 (1 << 4) // 0x10
#define ClObj_GROUP_3 (1 << 5) // 0x20
#define ClObj_GROUP_ALL (ClObj_GROUP_PLAYER | ClObj_GROUP_2 | ClObj_GROUP_3) // 0x38

#define ClObj_FLAG_CHECK (1 << 0) // 0x01
#define ClObj_FLAG_COLLIDED (1 << 1) // 0x02
#define ClObj_FLAG_DONT_UPDATE_POS (1 << 2) // 0x04
#define ClObj_FLAG_COLLIDE_PLAYER ClObj_GROUP_PLAYER
#define ClObj_FLAG_COLLIDE_GROUP_2 ClObj_GROUP_2
#define ClObj_FLAG_COLLIDE_GROUP_3 ClObj_GROUP_3
#define ClObj_FLAG_COLLISION_PRIORITY (1 << 6)
#define ClObj_FLAG_7 (1 << 7)

#define ClObj_FLAG2_PLAYER_WAS_HIT (1 << 0) // 0x01
#define ClObj_FLAG2_OCC_CHECK (1 << 1) // 0x02
#define ClObj_FLAG2_TRIS_HIT (1 << 2) // 0x04
#define ClObj_FLAG2_IS_PLAYER ClObj_GROUP_PLAYER
#define ClObj_FLAG2_IS_GROUP_2 ClObj_GROUP_2
#define ClObj_FLAG2_IS_GROUP_3 ClObj_GROUP_3

#define ClObjElem_FLAG_CHECK (1 << 0)
#define ClObjElem_FLAG_HIT (1 << 1)

#define ClObj_DID_COLLIDE(obj) ((obj).collision_flags0 & ClObj_FLAG_COLLIDED)

enum weight { MASS_IMMOVABLE, MASS_HEAVY, MASS_NORMAL };

#define MASSTYPE_IMMOVABLE 0xFF
#define MASSTYPE_HEAVY 0xFE

typedef struct collision_obj_s {
    ACTOR* owner_actor;    // actor which owns this collision object
    ACTOR* collided_actor; // actor which the owner collided with or NULL

    u8 collision_flags0;
    u8 collision_flags1;

    u8 collision_type;
} ClObj_c;

typedef struct collision_elem_s {
    u8 flags;
} ClObjElem_c;

typedef struct collision_pipe_attribute_s {
    Math3D_pipe_c pipe;
} ClObjPipeAttr_c;

typedef struct collision_pipe_s {
    ClObj_c collision_obj;
    ClObjElem_c element;
    ClObjPipeAttr_c attribute;
} ClObjPipe_c;

/* static data */

typedef struct collision_obj_data_s {
    u8 collision_flags0;
    u8 collision_flags1;
    u8 type;
} ClObjData_c;

typedef struct collision_obj_elem_data_s {
    u8 flags;
} ClObjElemData_c;

typedef struct collision_obj_pipe_attr_data_s {
    Math3D_pipe_c pipe;
} ClObjPipeAttrData_c;

typedef struct collision_obj_pipe_data_s {
    ClObjData_c collision_data;
    ClObjElemData_c element_data;
    ClObjPipeAttrData_c attribute_data;
} ClObjPipeData_c;

typedef struct collision_check_tris_element_attr_data_s {
    xyz_t vtx[3];
} ClObjTrisElemAttrData_c;

typedef struct collision_check_tris_element_data_s {
    ClObjElemData_c element;
    ClObjTrisElemAttrData_c data;
} ClObjTrisElemData_c;

typedef struct collision_check_tris_element_s {
    Math3D_triangle_c tri;
    xyz_t t;
} ClObjTrisElemAttr_c;

typedef struct collision_tris_elem_s {
    ClObjElem_c element;
    ClObjTrisElemAttr_c attribute;
} ClObjTrisElem_c;

typedef struct collision_tris_s {
    ClObj_c collision_obj;
    int count;
    ClObjTrisElem_c* elements;
} ClObjTris_c;

typedef struct ClObjTris_Init {
    ClObjData_c data;
    int count;
    ClObjTrisElemData_c* elem_data;
} ClObjTrisData_c;

typedef struct collision_obj_joint_sphere_elem_attribute_s {
    Math3D_sphere_c s1;
    Math3D_sphere_c s2;
    f32 unk8;
    u8 unk14;
} ClObjJntSphElemAttr_c;

typedef struct collision_joint_sphere_elem_s {
    ClObjElem_c element;
    ClObjJntSphElemAttr_c attribute;
} ClObjJntSphElem_c;

typedef struct collision_joint_sphere_s {
    ClObj_c collision_obj;
    int count;
    ClObjJntSphElem_c* elements;
} ClObjJntSph_c;

#define Cl_COLLIDER_NUM 50
typedef struct collision_check_s {
    u16 flags;
    int collider_num;
    ClObj_c* collider_table[Cl_COLLIDER_NUM];
} CollisionCheck_c;

/* This appears to again be copy-paste from OoT? */
typedef struct status_s {
    xyz_t collision_vec;
    s16 radius;
    s16 height;
    s16 offset;

    u8 weight;
    u8 hp;
    u8 damage;

    u8 damage_effect;
    u8 at_hit_effect;
    u8 ac_hit_effect;
} Status_c;

typedef struct status_data_s {
    u8 health; // assuming this is inherited from OoT, seems largely unused
    s16 radius;
    s16 height;
    s16 offset;
    u8 weight;
} StatusData_c;

typedef struct mco_work_s {
    int count;
    ClObj_c* colliders[10];
} McoWork;

extern McoWork mco_work;

typedef void (*CollisionOCFunction)(GAME*, CollisionCheck_c*, ClObj_c*, ClObj_c*);
typedef int (*CollisionOCClear)(GAME*, ClObj_c*);
typedef int (*CollisionClearFunction)(GAME*, ClObj_c*);

extern void CollisionCheck_workTrisElemCenter(ClObjTrisElem_c*, xyz_t*);
extern int ClObj_ct(GAME*, ClObj_c*);
extern int ClObj_dt(GAME*, ClObj_c*);
extern int ClObj_set4(GAME*, ClObj_c*, ACTOR*, ClObjData_c*);
extern void ClObj_OCClear(GAME*, ClObj_c*);
extern int ClObjElem_ct(ClObjElem_c*);
extern int ClObjElem_set(ClObjElem_c*, ClObjElemData_c*);
extern void ClObjElem_OCClear(GAME*, ClObjElem_c*);
extern int ClObjJntSphElem_OCClear(GAME*, ClObjJntSphElem_c*);
extern int ClObjJntSph_OCClear(GAME*, ClObj_c*);
extern int ClObjPipeAttr_ct(GAME*, ClObjPipeAttr_c*);
extern int ClObjPipeAttr_dt(GAME*, ClObjPipeAttr_c*);
extern int ClObjPipeAttr_set(GAME*, ClObjPipeAttr_c*, ClObjPipeAttr_c*);
extern int ClObjPipe_ct(GAME*, ClObjPipe_c*);
extern int ClObjPipe_dt(GAME*, ClObjPipe_c*);
extern int ClObjPipe_set5(GAME*, ClObjPipe_c*, ACTOR*, ClObjPipeData_c*);
extern int ClObjPipe_OCClear(GAME*, ClObj_c*);
extern int ClObjTrisElemAttr_ct(GAME*, ClObjTrisElemAttr_c*);
extern int ClObjTrisElemAttr_dt(GAME*, ClObjTrisElemAttr_c*);
extern int ClObjTrisElemAttr_set(GAME*, ClObjTrisElemAttr_c*, ClObjTrisElemAttrData_c*);
extern int ClObjTrisElem_ct(GAME*, ClObjTrisElem_c*);
extern int ClObjTrisElem_dt(GAME*, ClObjTrisElem_c*);
extern int ClObjTrisElem_set(GAME*, ClObjTrisElem_c*, ClObjTrisElemData_c*);
extern int ClObjTrisElem_OCClear(GAME*, ClObjTrisElem_c*);
extern int ClObjTris_ct(GAME*, ClObjTris_c*);
extern int ClObjTris_dt_nzf(GAME*, ClObjTris_c*);
extern int ClObjTris_set5_nzm(GAME*, ClObjTris_c*, ACTOR*, ClObjTrisData_c*, ClObjTrisElem_c*);
extern int ClObjTris_OCClear(GAME*, ClObj_c*);
extern void CollisionCheck_ct(GAME*, CollisionCheck_c*);
extern void CollisionCheck_dt(GAME*, CollisionCheck_c*);
extern void CollisionCheck_clear(GAME*, CollisionCheck_c*);
extern int CollisionCheck_setOC(GAME*, CollisionCheck_c*, ClObj_c*);
extern int get_type(u8);
extern void CollisionCheck_setOC_HitInfo(ClObj_c*, ClObjElem_c*, xyz_t*, ClObj_c*, ClObjElem_c*, xyz_t*, f32);
extern void CollisionCheck_OC_JntSph_Vs_JntSph(GAME*, CollisionCheck_c*, ClObj_c*, ClObj_c*);
extern void CollisionCheck_OC_JntSph_Vs_Pipe(GAME*, CollisionCheck_c*, ClObj_c*, ClObj_c*);
extern void CollisionCheck_OC_Pipe_Vs_JntSph(GAME*, CollisionCheck_c*, ClObj_c*, ClObj_c*);
extern void CollisionCheck_OC_Pipe_Vs_Pipe(GAME*, CollisionCheck_c*, ClObj_c*, ClObj_c*);
extern int CollisionCheck_Check1ClObjNoOC(ClObj_c*);
extern int CollisionCheck_Check2ClObjNoOC(ClObj_c*, ClObj_c*);
extern void CollisionCheck_OC(GAME*, CollisionCheck_c*);
extern void CollisionCheck_setOCC_HitInfo(GAME*, ClObj_c*, ClObjTrisElem_c*, xyz_t*, ClObj_c*, ClObjElem_c*, xyz_t*,
                                          xyz_t*);
extern void CollisionCheck_OCC_Tris_Vs_JntSph(GAME*, CollisionCheck_c*, ClObjTris_c*, ClObjJntSph_c*);
extern void CollisionCheck_OCC_Tris_Vs_Pipe(GAME*, CollisionCheck_c*, ClObjTris_c*, ClObjPipe_c*);
extern int CollisionCheck_Check1ClObjNoOCC(ClObj_c*);
extern void CollisionCheck_OCC(GAME*, CollisionCheck_c*);
extern int ClObjTrisElem_OCCClear(GAME*, ClObjTrisElem_c*);
extern int ClObj_OCCClear(GAME*, ClObj_c*);
extern int ClObjTris_OCCClear(GAME*, ClObj_c*);
extern int CollisionCheck_setOCC(GAME*, CollisionCheck_c*, ClObj_c*);
extern void CollisionCheck_Status_ct(Status_c*);
extern void CollisionCheck_Status_Clear(Status_c*);
extern void CollisionCheck_Status_set3(Status_c*, StatusData_c*);
extern int CollisionCheck_Uty_ActorWorldPosSetPipeC(ACTOR*, ClObjPipe_c*);

#ifdef __cplusplus
}
#endif

#endif
