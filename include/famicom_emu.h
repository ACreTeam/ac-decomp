#ifndef FAMICOM_EMU_H
#define FAMICOM_EMU_H

#include "types.h"
#include "game.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(struct game_famicom_emu_s) == 0xE0 */
typedef struct game_famicom_emu_s {
  /* 0x00 */ GAME game;
} GAME_FAMICOM_EMU;

extern void famicom_emu_init(GAME_FAMICOM_EMU* famicom_emu);
extern void famicom_emu_cleanup(GAME_FAMICOM_EMU* famicom_emu);

#ifdef __cplusplus
}
#endif

#endif
