/* Shadow: replaces GC libc/stdio.h with system stdio.
 * The GC version defines _STDIO_H_ and only declares a handful of functions.
 * This shadow defines _STDIO_H_ first so the system <stdio.h> won't be guarded
 * out, then includes the full system version. */
#ifndef _STDIO_H_
#define _STDIO_H_
#endif
#include <stdio.h>
