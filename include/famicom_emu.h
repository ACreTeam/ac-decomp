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

extern void* my_malloc_func[];

void my_alloc_cleanup();
void my_zelda_getmemblocksize(void *);
void my_zelda_gettotalfreesize();
void* my_zelda_malloc_align(size_t, u32);
void my_zelda_free(void *);
void famicom_emu_main(GAME *);
void famicom_emu_init(GAME_FAMICOM_EMU *);
void famicom_emu_cleanup(GAME *);
int famicom_gba_getImage(u32, int *);
void famicom_gba_removeImage(void *);

#ifdef __cplusplus
}
#endif

#endif
