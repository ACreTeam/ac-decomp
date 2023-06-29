#ifndef M_COLLISION_OBJ_H
#define M_COLLISION_OBJ_H

#include "types.h"
#include "m_actor.h"
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

typedef struct collision_obj_s {
  ACTOR* owner_actor; // actor which owns this collision object
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

extern void ClObjPipe_ct(GAME_PLAY* play, ClObjPipe_c* pipe);
extern void ClObjPipe_dt(GAME_PLAY* play, ClObjPipe_c* pipe);
extern void ClObjPipe_set5(GAME_PLAY* play, ClObjPipe_c* pipe, ACTOR* owner, ClObjPipeData_c* data);
extern void CollisionCheck_Uty_ActorWorldPosSetPipeC(ACTOR* actor, ClObjPipe_c* col_pipe);
extern int CollisionCheck_setOC(GAME_PLAY* play, CollisionCheck_c* collision_check, ClObj_c* col_obj);
extern void CollisionCheck_Status_set3(Status_c* status, StatusData_c* data);

#ifdef __cplusplus
}
#endif

#endif
