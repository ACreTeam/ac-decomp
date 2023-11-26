#ifndef GAME_H
#define GAME_H

#include "types.h"
#include "game_h.h"
#include "TwoHeadArena.h"
#include "graph.h"
#include "gamealloc.h"
#include "libu64/pad.h"
#include "m_controller.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(struct game_s) == 0xE0 */
struct game_s {
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
};

#define GAME_HYRAL_SIZE (0x100000)
#define GAME_FRAME (1)

#define GAME_NEXT_GAME(game, init_name, class_name) \
do { \
  GAME* g = (game); \
  g->next_game_init = (void (*)(struct game_s*))init_name##_init; \
  g->next_game_class_size = sizeof(GAME_##class_name); \
} while (0)

#define GAME_NEXT_GAME_NULL(game) \
do { \
  GAME* _game = (game); \
  _game->next_game_init = NULL; \
  _game->next_game_class_size = 0; \
} while (0)

#define GAME_GOTO_NEXT(game, init_name, class_name) \
do { \
  GAME* t_game = (game); \
  t_game->doing = FALSE; \
  GAME_NEXT_GAME(t_game, init_name, class_name); \
} while (0)

extern void game_debug_draw_last(GAME* game, GRAPH* graph);
extern void game_draw_last(GRAPH* graph);
extern void game_get_controller(GAME* game);
extern void SetGameFrame(int frame);
extern void game_main(GAME* game);
extern void game_resize_hyral(GAME* game, int size);
extern void game_ct(GAME* game, void (*init)(GAME*), GRAPH* graph);
extern void game_dt(GAME* game);
extern void (*game_get_next_game_init(GAME* game))(GAME*);
#ifndef MUST_MATCH
extern size_t game_get_next_game_class_size(GAME* game);
#endif
extern int game_is_doing(GAME* game);
extern int game_getFreeBytes(GAME* game);
extern void game_goto_next_game_play(GAME* game);
#ifndef MUST_MATCH
extern void game_goto_next_game_famicom_emu(GAME* game);
#endif

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
