#ifndef M_BG_ITEM_H
#define M_BG_ITEM_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR* mBI_search_bg_item(Actor_info* info);
extern void mBI_make_bg_item(GAME_PLAY* play);
extern void mBI_change_bg_item(GAME_PLAY* play);
extern void mBI_ct();
extern void mBI_move(GAME_PLAY* play);

typedef void (*BI_PROC)(GAME_PLAY*);

extern BI_PROC mBI_make_proc;

#ifdef __cplusplus
}
#endif

#endif
