#ifndef M_GAME_DLFTBLS_H
#define M_GAME_DLFTBLS_H

/* Display List Function TaBLe */

#ifdef __cplusplus
extern "C" {
#endif

#include "game.h"
#include "types.h"

enum {
    GAME_DLFTBL_FIRST_GAME,
    GAME_DLFTBL_SELECT,
    GAME_DLFTBL_PLAY,
    GAME_DLFTBL_SECOND_GAME,
    GAME_DLFTBL_4,
    GAME_DLFTBL_TRADEMARK,
    GAME_DLFTBL_PLAYER_SELECT,
    GAME_DLFTBL_SAVE_MENU,
    GAME_DLFTBL_FAMICOM_EMU,
    GAME_DLFTBL_PRENMI,
    GAME_DLFTBL_RELOAD_DATA,

    GAME_DLFTBL_NUM
};

typedef void (*GAME_CT_PROC)(GAME* game);
typedef void (*GAME_DT_PROC)(GAME* game);

/* TODO: Research the unknown function pointers & unknown value */
typedef struct {
    void* loaded_address;
    u32 SegmentRomStart;	/* _nameSegmentRomStart */
    u32 SegmentRomEnd;		/* _nameSegmentRomEnd */
    char *SegmentStart;		/* _nameSegmentStart */
    char *SegmentEnd;		/* _nameSegmentEnd */
    void* unk_14;
    GAME_CT_PROC init;
    GAME_DT_PROC cleanup;
    void* unk_20;
    void* unk_24;
    void* unk_28;
    size_t alloc_size;
} Game_dlftbl;
typedef Game_dlftbl DLFTBL_GAME;

extern unsigned int game_dlftbls_num;
extern DLFTBL_GAME game_dlftbls[];

#ifdef __cplusplus
}
#endif

#endif
