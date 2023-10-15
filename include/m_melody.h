#ifndef M_MELODY_H
#define M_MELODY_H

#include "types.h"
#include "m_actor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mMld_MELODY_LEN 16

extern void mMld_SetDefaultMelody();
extern void mMld_TransformMelodyData_u64_2_u8(u8* dst, u64 src);
extern void mMld_TransformMelodyData_u8_2_u64(u64* dst, u8* src);
extern void mMld_GetMelody(u8* dst);
extern void mMld_SetSaveMelody(u8* melody);
extern void mMld_MakeMelody(u16 inst);
extern void mMld_ActorMakeThisMelody(u8* melody, ACTOR* actor);
extern void mMld_ActorMakeMelody(ACTOR* actor);

#ifdef __cplusplus
}
#endif

#endif
