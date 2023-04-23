#ifndef GAME_H
#define GAME_H

#include "types.h"
#include "TwoHeadArena.h"
#include "graph.h"
#include "gamealloc.h"
#include "libu64/pad.h"
#include "m_controller.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(struct game_s) == 0xE0 */
typedef struct game_s {
  /* 0x0000 */ GRAPH* graph;
  /* 0x0004 */ void (*exec)(struct game_s* );
  /* 0x0008 */ void (*cleanup)(struct game_s*);
  /* 0x000C */ void (*next_game_init)(struct game_s*);
  /* 0x0010 */ size_t next_game_class_size;
  /* 0x0014 */ pad_t pads[MAXCONTROLLERS];
  /* 0x0074 */ int pad_initialized;
  /* 0x0078 */ THA tha;
  /* 0x0088 */ GameAlloc gamealloc;
  /* 0x009C */ u8 doing_point;
  /* 0x009D */ u8 doing_point_specific; /* game class specific? */
  /* 0x009E */ u8 disable_display;
  /* 0x009F */ u8 doing;
  /* 0x00A0 */ u32 frame_counter;
  /* 0x00A4 */ int disable_prenmi;
  /* 0x00A8 */ MCON mcon;
} GAME;

extern void game_ct(GAME*, void (*)(GAME*), GRAPH*);
extern void game_dt(GAME* game);
extern void game_main(GAME* game);
extern int game_is_doing(GAME* game);
extern void (*game_get_next_game_init(GAME* game))(GAME*);

#define GAME_NEXT_GAME(game, init_name, class_name) \
do { \
  GAME* g = (game); \
  g->next_game_init = (void (*)(struct game_s*))init_name##_init; \
  g->next_game_class_size = sizeof(GAME_##class_name); \
} while (0)

#define GAME_GOTO_NEXT(game, init_name, class_name) \
do { \
  GAME* t_game = (game); \
  t_game->doing = FALSE; \
  GAME_NEXT_GAME(t_game, init_name, class_name); \
} while (0)

extern void game_get_controller(GAME* game);

extern GAME* gamePT;

extern GAME* game_class_p;
extern u8 game_GameFrame;
extern float game_GameFrameF;
extern float game_GameFrame_2F;
extern float game_GameFrame__1F;

#ifdef __cplusplus
};
#endif

#endif
