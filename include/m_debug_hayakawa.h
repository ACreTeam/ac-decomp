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

#ifdef __cplusplus
}
#endif

#endif
