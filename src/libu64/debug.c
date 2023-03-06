#include "libu64/debug.h"
#include "libultra/osThread.h"

void _dbg_hungup(const char* name, s32 line) {
char dbg_tbuf[0x100];

sprintf(dbg_tbuf, "*** HungUp in thread %d, [%s:%d] ***\n",osGetThreadId(0), name, line);
}
