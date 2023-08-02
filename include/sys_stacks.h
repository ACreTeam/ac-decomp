#ifndef SYS_STACKS_H
#define SYS_STACKS_H

#include "types.h"

#define IRQMGR_STACK_SIZE 0x1000
#define PADMGR_STACK_SIZE 0x1000
#define GRAPH_STACK_SIZE 0x2000

extern u8 graphStack[];
extern u8 padmgrStack[];
extern u8 irqmgrStack[];



#endif