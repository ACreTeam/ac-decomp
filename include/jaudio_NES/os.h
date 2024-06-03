#ifndef OS_H
#define OS_H

#include "types.h"
#include "libultra/libultra.h"

extern int Z_osSendMesg(OSMesgQueue* mq, OSMesg msg, s32 block);

#endif
