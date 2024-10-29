#include "m_melody.h"

#include "ac_npc.h"
#include "m_common_data.h"

extern void mMld_SetDefaultMelody() {
  static u8 melody[mMld_MELODY_LEN] = {
    0x7, 0xC, 0xF, 0x7, 0x6, 0xB, 0xF, 0x9,
    0xA, 0xE, 0xD, 0xE, 0x3, 0xF, 0xE, 0xE
  };

  mMld_SetSaveMelody(melody);
}

extern void mMld_TransformMelodyData_u64_2_u8(u8* dst, u64 src) {
  int i;

  for (i = 0; i < mMld_MELODY_LEN; i++) {
    *dst++ = (src >> (60 - i * 4)) & 0xF;
  }
}

extern void mMld_TransformMelodyData_u8_2_u64(u64* dst, u8* src) {
  int i;

  dst[0] = 0;

  for (i = 0; i < mMld_MELODY_LEN; i++) {
    dst[0] |= (u64)(src[0] & 0xF) << (60 - i * 4);
    src++;
  }
}

extern void mMld_GetMelody(u8* dst) {
  mMld_TransformMelodyData_u64_2_u8(dst, Save_Get(melody));
}

extern void mMld_SetSaveMelody(u8* melody) {
  mMld_TransformMelodyData_u8_2_u64(Save_GetPointer(melody), melody);
}

extern void mMld_MakeMelody(u16 inst) {
  static u8 melody[mMld_MELODY_LEN];

  mMld_GetMelody(melody);
  sAdo_Inst(inst, melody);
}

extern void mMld_ActorMakeThisMelody(u8* melody, ACTOR* actor) {
  if (actor != NULL && actor->part == ACTOR_PART_NPC) {
    NPC_ACTOR* npc_actor = (NPC_ACTOR*)actor;
    int melody_inst = npc_actor->talk_info.melody_inst;

    if (melody_inst != 0) {
      sAdo_Inst(melody_inst, melody);
    }
  }
}

extern void mMld_ActorMakeMelody(ACTOR* actor) {
  if (actor != NULL && actor->part == ACTOR_PART_NPC) {
    NPC_ACTOR* npc_actor = (NPC_ACTOR*)actor;
    int melody_inst = npc_actor->talk_info.melody_inst;

    if (melody_inst != 0) {
      mMld_MakeMelody(melody_inst);
    }
  }
}
