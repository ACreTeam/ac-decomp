#ifndef M_DEBUG_MODE_H
#define M_DEBUG_MODE_H

#include "types.h"
#include "graph.h"
#include "m_debug.h"
#include "libu64/pad.h"
#include "game.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void Debug_mode_input(pad_t* pad);
extern void Debug_mode_output(GRAPH* graph);

/* Defines for debug mode output colors */
#define DEBUG_PRINT_COLOR_BLACK 0
#define DEBUG_PRINT_COLOR_BLUE 1
#define DEBUG_PRINT_COLOR_RED 2
#define DEBUG_PRINT_COLOR_MAGENTA 3
#define DEBUG_PRINT_COLOR_GREEN 4
#define DEBUG_PRINT_COLOR_CYAN 5
#define DEBUG_PRINT_COLOR_YELLOW 6
#define DEBUG_PRINT_COLOR_WHITE 7

/* Defines for debug mode 2 output colors */
#define DEBUG_PRINT2_COLOR_YELLOW 0
#define DEBUG_PRINT2_COLOR_PINK 1
#define DEBUG_PRINT2_COLOR_BROWN 2
#define DEBUG_PRINT2_COLOR_DARKORANGE 3
#define DEBUG_PRINT2_COLOR_LIGHTORANGE 4
#define DEBUG_PRINT2_COLOR_GRAY 5
#define DEBUG_PRINT2_COLOR_LILAC 6
#define DEBUG_PRINT2_COLOR_LIMEGREEN 7

#define DEBUG_MODE_CHECK_TRIGGER(game, btn) (((game)->pads[1].on.button & (btn)) == (btn))
#define DEBUG_MODE_CHECK_TRIGGER_GAME(btn) (DEBUG_MODE_CHECK_TRIGGER(gamePT, btn))

#ifdef __cplusplus
}
#endif

#endif
