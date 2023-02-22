#include "libc64/aprintf.h"
#include "libultra/xprintf.h" /* _Printf */

extern int vaprintf(aprout_func_t* func, const char* fmt, va_list ap) {
  return _Printf(func->prout_func, func, fmt, ap);
}
