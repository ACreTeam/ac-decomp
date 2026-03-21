/* Shadow _mem.h — use system <string.h> instead of re-declaring memcpy/memset/memcmp.
 * The original declarations conflict with Apple Clang's fortification macros. */
#ifndef _MEM_H
#define _MEM_H

#include <string.h>  /* memcpy, memset, memcmp */
#include <stddef.h>  /* size_t */

/* __fill_mem is a Metrowerks CRT function; map to memset on Clang */
#ifndef __fill_mem
static inline void __fill_mem(void* dst, int val, unsigned long n) {
    memset(dst, val, (size_t)n);
}
#endif

#endif /* _MEM_H */
