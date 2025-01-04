#ifndef M_NPC_DEF_H
#define M_NPC_DEF_H

#include "types.h"
#include "m_land_h.h"
#include "m_actor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  mNpc_LOOKS_GIRL, // 'normal'
  mNpc_LOOKS_KO_GIRL, // 'peppy'
  mNpc_LOOKS_BOY, // 'lazy'
  mNpc_LOOKS_SPORT_MAN, // 'jock'
  mNpc_LOOKS_GRIM_MAN, // 'cranky'
  mNpc_LOOKS_NANIWA_LADY, // 'snooty'
  mNpc_LOOKS_UNSET,

  mNpc_LOOKS_NUM = mNpc_LOOKS_UNSET
};

/* sizeof(AnmPersonalID_c) == 0xE */
typedef struct animal_personal_id_s {
  /* 0x00 */ mActor_name_t npc_id; /* id */
  /* 0x02 */ u16 land_id; /* town id */
  /* 0x04 */ u8 land_name[LAND_NAME_SIZE]; /* town name */
  /* 0x0C */ u8 name_id; /* lower byte of the id */
  /* 0x0D */ u8 looks; /* internal name for personality */
} AnmPersonalID_c;

#ifdef __cplusplus
}
#endif

#endif
