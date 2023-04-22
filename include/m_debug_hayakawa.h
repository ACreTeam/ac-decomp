#ifndef M_DEBUG_HAYAKAWA_H
#define M_DEBUG_HAYAKAWA_H

#include "types.h"
#include "graph.h"
#include "libu64/pad.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void debug_hayakawa_draw(GRAPH* graph);
extern void debug_hayakawa_move(pad_t* pad);
extern int hreg_init_check(const int n);

#define HREG_STATE_IDX 80
#define HREG_STATE_ARGS_START 81
#define HREG_STATE_ARGS_COUNT 14

#ifdef __cplusplus
}
#endif

#endif
