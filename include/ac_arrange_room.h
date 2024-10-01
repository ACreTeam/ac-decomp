#ifndef AC_ARRANGE_ROOM_H
#define AC_ARRANGE_ROOM_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct arrange_room_actor_s ARRANGE_ROOM_ACTOR;

typedef void (*aAR_REDMA_PROC)();

typedef struct arrange_room_actor_clip_s {
  ARRANGE_ROOM_ACTOR* arrange_room_actor_p;
  aAR_REDMA_PROC redma_proc;
} aAR_Clip_c;

struct arrange_room_actor_s {
  ACTOR actor_class;
  u8* vram_segment;
  u8* wall_data_p;
  int wall_num;
  u8* floor_data_p;
  int floor_num;
  aAR_Clip_c clip;
};

extern ACTOR_PROFILE Arrange_Room_Profile;

#ifdef __cplusplus
}
#endif

#endif

