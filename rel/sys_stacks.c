#include "types.h"

#define IRQMGR_STACK_SIZE 0x1000
#define PADMGR_STACK_SIZE 0x1000
#define GRAPH_STACK_SIZE 0x2000

extern u8 irqmgrStack [IRQMGR_STACK_SIZE];
extern u8 padmgrStack [PADMGR_STACK_SIZE];
extern u8 graphStack[GRAPH_STACK_SIZE];