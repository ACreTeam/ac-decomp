#ifndef RELOAD_DATA_H
#define RELOAD_DATA_H

#include "game.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RELOAD_DATA_STACK_SIZE 0xC800

typedef struct reload_data_s GAME_RELOAD_DATA;

struct reload_data_s {
    /* 0x0000 */ GAME game;
    /* 0x00E4 */ u8 _E4[0x00E8 - 0x00E4]; // implicit padding for OSThread
    /* 0x00E8 */ OSThread thread;
    /* 0x0400 */ u64 stack_preguard;
    /* 0x0408 */ u8 stack[RELOAD_DATA_STACK_SIZE];
    /* 0xCC08 */ u64 stack_postguard;
    /* 0xCC10 */ int reset_pending;
};

extern void reload_data_init(GAME* game);
extern void reload_data_cleanup(GAME* game);

#ifdef __cplusplus
}
#endif

#endif
