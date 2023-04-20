#ifndef M_NPC_H
#define M_NPC_H

#include "types.h"
#include "libu64/gfxprint.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mNpc_PrintRemoveInfo(gfxprint_t* gfxprint);
extern void mNpc_PrintFriendship_fdebug(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
