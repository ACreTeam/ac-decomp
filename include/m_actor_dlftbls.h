#ifndef M_ACTOR_DLFTBLS_H
#define M_ACTOR_DLFTBLS_H

#include "types.h"
#include "m_actor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct actor_dfltbl_s {
  u32 rom_start; // unused in AC
  u32 rom_end; // unused in AC
  u8* ram_start; // used only with a check, but never set in AC
  u8* ram_end; // unused in AC
  u8* alloc_buf; // used in AC but only on free check and data is never allocated
  ACTOR_PROFILE* profile; // profile for the actor
  int unk; // unused in AC
  u16 flags; // related to memory pinning but functionally useless in AC since alloc_buf is never allocated
  s8 num_actors; // number of this type of actor that currently exist
  s8 unk2; // unused in AC
} ACTOR_DFLTBL;

extern int actor_dlftbls_num;
extern ACTOR_DFLTBL actor_dlftbls[];

extern void actor_dlftbls_init();
extern void actor_dlftbls_cleanup();

#ifdef __cplusplus
}
#endif

#endif
