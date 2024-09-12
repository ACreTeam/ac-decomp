#ifndef M_ACTOR_DLFTBLS_H
#define M_ACTOR_DLFTBLS_H

#include "types.h"
#include "m_actor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct actor_dlftbl_s {
    /* 0x00 */ u32 rom_start;          // unused in AC
    /* 0x04 */ u32 rom_end;            // unused in AC
    /* 0x08 */ u8* ram_start;          // used only with a check, but never set in AC
    /* 0x0C */ u8* ram_end;            // unused in AC
    /* 0x10 */ u8* alloc_buf;          // used in AC but only on free check and data is never allocated
    /* 0x14 */ ACTOR_PROFILE* profile; // profile for the actor
    /* 0x18 */ int unk;                // unused in AC
    /* 0x1C */ u16 flags; // related to memory pinning but functionally useless in AC since alloc_buf is never allocated
    /* 0x1E */ s8 num_actors; // number of this type of actor that currently exist
    /* 0x1F */ s8 unk2;       // unused in AC
} ACTOR_DLFTBL;

extern int actor_dlftbls_num;
extern ACTOR_DLFTBL actor_dlftbls[];

extern void actor_dlftbls_init();
extern void actor_dlftbls_cleanup();

#ifdef __cplusplus
}
#endif

#endif
