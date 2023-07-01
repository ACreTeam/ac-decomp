#ifndef AC_STRUCTURE_H
#define AC_STRUCTURE_H

#include "types.h"
#include "m_actor.h"
#include "m_actor_dlftbls.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aSTR_ACTOR_TBL_COUNT 9
#define aSTR_OVERLAY_SIZE 0x2400

enum structure_type {
  aSTR_TYPE_HOUSE1,
  aSTR_TYPE_HOUSE2,
  aSTR_TYPE_HOUSE3,
  aSTR_TYPE_HOUSE4,
  aSTR_TYPE_HOUSE5,
  aSTR_TYPE_MYHOME,
  aSTR_TYPE_6,
  aSTR_TYPE_7,
  aSTR_TYPE_SHOP1,
  aSTR_TYPE_SHOP2,
  aSTR_TYPE_SHOP3,
  aSTR_TYPE_SHOP4,
  aSTR_TYPE_POST_OFFICE,
  aSTR_TYPE_STATION1,
  aSTR_TYPE_STATION2,
  aSTR_TYPE_STATION3,
  aSTR_TYPE_TRAIN0,
  aSTR_TYPE_TRAIN1,
  aSTR_TYPE_POLICE_BOX,
  aSTR_TYPE_FALLS,
  aSTR_TYPE_FALLSESW,
  aSTR_TYPE_SIGN,
  aSTR_TYPE_SHRINE,
  aSTR_TYPE_BRSHOP,
  aSTR_TYPE_BUGGY,
  aSTR_TYPE_S_CAR,
  aSTR_TYPE_KAMAKURA, // also used for camping tent
  aSTR_TYPE_GOZA,
  aSTR_TYPE_RADIO,
  aSTR_TYPE_YATAI,
  aSTR_TYPE_TUKIMI,
  aSTR_TYPE_TUKIMI2,
  aSTR_TYPE_MIKUJI,
  aSTR_TYPE_COUNT,
  aSTR_TYPE_COUNT02,
  aSTR_TYPE_SPORTSFAIR_A,
  aSTR_TYPE_SPORTSFAIR_B,
  aSTR_TYPE_TURI,
  aSTR_TYPE_TURI2,
  aSTR_TYPE_KOINOBORI,
  aSTR_TYPE_DUMP,
  aSTR_TYPE_WINDMILL,
  aSTR_TYPE_LOTUS,
  aSTR_TYPE_MIKANBOX,
  aSTR_TYPE_DOUZOU,
  aSTR_TYPE_TOUDAI,
  aSTR_TYPE_GHOG,
  aSTR_TYPE_HTABLE,
  aSTR_TYPE_MUSEUM,
  aSTR_TYPE_BRIDGE_A,
  aSTR_TYPE_50,
  aSTR_TYPE_NEEDLEWORK_SHOP,
  aSTR_TYPE_FLAG,
  aSTR_TYPE_BOAT,
  aSTR_TYPE_COTTAGE_MY,
  aSTR_TYPE_COTTAGE_NPC,

  aSTR_TYPE_NUM
};

typedef struct actor_structure_control_s STRUCTURE_CONTROL_ACTOR;
typedef struct actor_structure_s STRUCTURE_ACTOR;

typedef STRUCTURE_ACTOR* (*aSTR_SETUP_ACTOR_PROC)(GAME*, mActor_name_t, s16, f32, f32);
typedef void (*aSTR_GET_OVERLAY_AREA_PROC)(ACTOR_DLFTBL*);
typedef void (*aSTR_FREE_OVERLAY_AREA_PROC)(ACTOR_DLFTBL*);
typedef STRUCTURE_ACTOR* (*aSTR_GET_ACTOR_AREA_PROC)();
typedef void (*aSTR_FREE_ACTOR_AREA_PROC)(STRUCTURE_ACTOR*);
typedef u16* (*aSTR_GET_PAL_SEGMENT_PROC)(s16);

struct actor_structure_s {
  ACTOR actor_class;
  u8 _174[0x2B0 - 0x174];
  int request_type;
  u8 _2B4[0x2DC - 0x2B4];
};

typedef struct actor_overlay_info_s {
  u8* overlay_p;
  int used;
} aSTR_Overlay_info_c;

// TODO: finish clip
typedef struct actor_structure_clip_s {
  aSTR_SETUP_ACTOR_PROC setup_actor_proc;
  aSTR_GET_OVERLAY_AREA_PROC get_overlay_area_proc;
  aSTR_FREE_OVERLAY_AREA_PROC free_overlay_area_proc;
  aSTR_GET_ACTOR_AREA_PROC get_actor_area_proc;
  aSTR_FREE_ACTOR_AREA_PROC free_actor_area_proc;

  STRUCTURE_ACTOR* structure_actor_tbl[aSTR_ACTOR_TBL_COUNT];
  int structure_actor_used_tbl[aSTR_ACTOR_TBL_COUNT];

  aSTR_Overlay_info_c overlay_area[aSTR_ACTOR_TBL_COUNT];

  aSTR_GET_PAL_SEGMENT_PROC get_pal_segment_proc;
} aSTR_Clip_c;

struct actor_structure_control_s {
  ACTOR actor_class;
  int _174;
  mActor_name_t str_door_name;
  u8 reset;
};

extern ACTOR_PROFILE Structure_Profile;

#ifdef __cplusplus
}
#endif

#endif
