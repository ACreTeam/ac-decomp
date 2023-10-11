#ifndef M_MARK_ROOM_H
#define M_MARK_ROOM_H

#include "types.h"
#include "game_h.h"
#include "m_mark_room_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mMkRm_HINT_NUM 19

extern void mMkRm_ReportChangePlayerRoom();
extern void mMkRm_MarkRoom(GAME* game);

#ifdef __cplusplus
}
#endif

#endif
