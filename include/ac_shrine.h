#ifndef AC_SHRINE_H
#define AC_SHRINE_H

#include "types.h"
#include "libultra/libultra.h"
#include "m_actor.h"
#include "ac_structure.h"
#include "m_common_data.h"
#include "m_font.h"
#include "m_item_name.h"
#include "m_player_lib.h"
#include "m_rcp.h"
#include "m_soncho.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ac_shrine_s SHRINE_ACTOR;

typedef void (*aSHR_ANIME_PLAY_PROC)();

typedef struct ac_shrine_clip_s {
  aSHR_ANIME_PLAY_PROC anime_play_proc;
  int play_flag;
  int hem_flag;
} aSHR_Clip_c;

#define aSHR_GET_CLIP() ((aSHR_Clip_c*)(Common_Get(clip).shrine_clip))
#define aSHR_SET_CLIP(v) (Common_Get(clip).shrine_clip = (v))

typedef struct ac_shrine_present_s aSHR_Present_c;
typedef void (*aSHR_Present_PROC)(aSHR_Present_c*);

struct ac_shrine_present_s {
  xyz_t trans;
  f32 percent;
  int finish_flag;
  aSHR_Present_PROC move_proc;
};

struct ac_shrine_s {
  STRUCTURE_ACTOR structure_class;
};

extern ACTOR_PROFILE Shrine_Profile;

#ifdef __cplusplus
}
#endif

#endif

