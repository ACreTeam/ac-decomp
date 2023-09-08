#ifndef M_CAMERA2_H
#define M_CAMERA2_H

#include "types.h"
#include "m_lib.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  CAMERA2_PROCESS_STOP,
  CAMERA2_PROCESS_NORMAL,
  CAMERA2_PROCESS_WADE,
  CAMERA2_PROCESS_TALK,
  CAMERA2_PROCESS_DEMO,
  CAMERA2_PROCESS_ITEM,
  CAMERA2_PROCESS_LOCK,
  CAMERA2_PROCESS_DOOR,
  CAMERA2_PROCESS_SIMPLE,
  CAMERA2_PROCESS_CUST_TALK,
  CAMERA2_PROCESS_INTER,
  CAMERA2_PROCESS_STAFF_ROLL,
  CAMERA2_PROCESS_INTER2,

  CAMERA2_PROCESS_NUM
};

typedef struct camera_main_cust_talk_s {
  ACTOR* speaker_actor;
  ACTOR* listener_actor;
  f32 center_ratio;
  f32 cull_timer;
  s16 angle_x;
  s16 angle_y;
  f32 distance;
} CameraCustTalk;

typedef struct camera_main_demo_s {
  xyz_t starting_center_pos;
  f32 starting_distance;
  s_xyz starting_direction;

  xyz_t goal_center_pos;
  f32 goal_distance;
  s_xyz goal_direction;

  f32 goal_delta;
  f32 acceleration_delta;
  f32 braking_delta;
  f32 now_delta;
} CameraDemo;

typedef struct camera_main_door_s {
  u32 flags;
  int morph_counter;
  xyz_t center_position;
} CameraDoor;

typedef struct camera_main_inter_s {
  xyz_t starting_center_pos;
  xyz_t starting_eye_pos;
  
  xyz_t goal_center_pos;
  xyz_t goal_eye_pos;

  f32 slope0;
  f32 slope1;

  u32 flags;

  int now_delta;
  int max_delta;

  int pad[2];
} CameraInter;

typedef struct camera_main_item_s {
  int type;
  f32 cull_timer;
} CameraItem;

typedef struct camera_main_lock_s {
  xyz_t center_pos;
  xyz_t eye_pos;

  f32 fov_y;

  int morph_counter;

  f32 near;
  f32 far;
} CameraLock;

typedef struct camera_main_normal_s {
  u32 flags;

  int last_indoor_distance_addition_idx;
  int last_indoor_direction_addition_idx;

  int morph_counter;
} CameraNormal;

typedef struct camera_main_simple_s {
  xyz_t center_pos;
  xyz_t eye_pos;
  f32 distance;

  int morph_counter;
  int mode;

  f32 cull_timer;
} CameraSimple;

typedef struct camera_main_staff_roll_s {
  xyz_t last_center_pos;
  xyz_t last_eye_pos;
  f32 last_distance;

  ACTOR* speaker_actor;
  ACTOR* listener_actor;

  s16 rotation_y_delta;
  s16 r_delta;
  s16 rotation_x_delta;

  u16 flags;
  u16 morph_counter;
  u16 pad;
  u16 dist_counter;
  s_xyz last_direction;
} CameraStaffRoll;

typedef struct camera_main_talk_s {
  ACTOR* speaker_actor;
  ACTOR* listener_actor;

  xyz_t listener_pos;
  
  f32 cull_timer;
  u32 flags;

  xyz_t goal_center_pos;
} CameraTalk;

typedef struct camera_main_wade_s {
  f32 timer;

  xyz_t start_pos;
  xyz_t goal_pos;

  f32 goal_time;
} CameraWade;

typedef union camera_main_data_u {
  CameraCustTalk cust_talk;
  CameraDemo demo;
  CameraDoor door;
  CameraInter inter;
  CameraItem item;
  CameraLock lock;
  CameraNormal normal;
  CameraSimple simple;
  CameraStaffRoll staff_roll;
  CameraTalk talk;
  CameraWade wade;
  
  u64 align;
} CameraMainData;

/* request index data */

typedef struct camera_request_cust_talk_s {
  ACTOR* speaker_actor;
  ACTOR* listener_actor;
  f32 center_ratio;
  f32 cull_timer;
  s16 angle_x;
  s16 angle_y;
  f32 distance;
} CameraRequestCustTalk;

typedef struct camera_request_demo_s {
  xyz_t starting_center_pos;
  f32 starting_distance;
  s_xyz starting_direction;

  xyz_t goal_center_pos;
  f32 goal_distance;
  s_xyz goal_direction;

  f32 goal_delta;
  f32 acceleration_delta;
  f32 braking_delta;
} CameraRequestDemo;

typedef struct camera_request_door_s {
  ACTOR* door_actor;
  u32 flags;
} CameraRequestDoor;

typedef struct camera_request_inter_s {
  xyz_t starting_center_pos;
  xyz_t starting_eye_pos;
  
  xyz_t goal_center_pos;
  xyz_t goal_eye_pos;

  f32 slope0;
  f32 slope1;

  u32 flags;

  int morph_counter;

  int pad[2];
} CameraRequestInter;

typedef struct camera_request_item_s {
  int type;
} CameraRequestItem;

typedef struct camera_request_lock_s {
  xyz_t center_pos;
  xyz_t eye_pos;

  f32 fov_y;

  int morph_counter;

  f32 near;
  f32 far;
} CameraRequestLock;

typedef struct camera_request_normal_s {
  xyz_t position;

  int flags;
} CameraRequestNormal;

typedef struct camera_request_simple_s {
  xyz_t center_pos;
  s_xyz angle;
  f32 distance;

  int morph_counter;
  int mode;
} CameraRequestSimple;

typedef struct camera_request_staff_roll_s {
  ACTOR* speaker_actor;
  ACTOR* listener_actor;
} CameraRequestStaffRoll;

typedef struct camera_request_talk_s {
  ACTOR* speaker_actor;
  ACTOR* listener_actor;

  xyz_t listener_pos;

  u32 flags;
} CameraRequestTalk;

typedef struct camera_request_wade_s {
  xyz_t goal_pos;
  f32 goal_time;
} CameraRequestWade;

typedef union camera_request_data_u {
  CameraRequestCustTalk cust_talk;
  CameraRequestDemo demo;
  CameraRequestDoor door;
  CameraRequestInter inter;
  CameraRequestItem item;
  CameraRequestLock lock;
  CameraRequestNormal normal;
  CameraRequestSimple simple;
  CameraRequestStaffRoll staff_roll;
  CameraRequestTalk talk;
  CameraRequestWade wade;
  
  u64 align;
} CameraRequestData;

typedef struct camera_s {
  struct {
    xyz_t eye;
    xyz_t center;
    xyz_t up;
  } lookat;

  struct {
    f32 fov_y;
    f32 aspect_ratio;
    f32 near;
    f32 far;
    f32 scale;
  } perspective;

  s_xyz direction; /* camera orientation */
  s_xyz direction_velocity; /* camera orentation rate of change */

  xyz_t movement_velocity; /* camera world position velocity */

  f32 focus_distance; /* distance to the camera focal point/subject */
  f32 focus_distance_velocity; /* rate of change of the camera focus */

  int indoor_distance_addition_idx; /* index of indoor distance adjustment LUT value to apply */
  int indoor_direction_addition_idx; /* index of indoor direction adjustment LUT value to apply */

  int now_main_index; /* current main index type */
  int last_main_index; /* previous main index type */
  int requested_main_index; /* requested main index type */
  int requested_main_index_priority; /* requested main index priority value */
  int requested_main_index_flag; /* TRUE/FALSE requested main index has been set */

  CameraMainData main_data; /* current main index data */
  CameraRequestData request_data; /* requested index data */

  xyz_t mic_pos; /* mic position */
  u32 flags; /* camera flags */

  xyz_t unused[2]; // potentially unused, idk if it's even xyz_t
} Camera2;


xyz_t* Camera2_getMicPos_p(GAME_PLAY*);
void Camera2_ClearActorTalking_Cull(GAME_PLAY*);
void Camera2_process(GAME_PLAY*);
void Init_Camera2(GAME_PLAY*);
void Camera2_draw(GAME_PLAY*);

#ifdef __cplusplus
}
#endif

#endif
