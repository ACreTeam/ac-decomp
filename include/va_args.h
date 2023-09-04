#ifndef __VA_ARG_H
#define __VA_ARG_H

#include "types.h"

#if defined(__INTELLISENSE__) && defined(__cplusplus)
#define __builtin_va_info(v) /* definition for IDEs */
#endif

typedef struct __va_list_struct {
    char gpr;
    char fpr;
    char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} _va_list_struct;

typedef _va_list_struct __va_list[1];

#define __va_start(list, fmt) __builtin_va_info(&list)
#define __va_arg(list, type) (*((type*)__va_arg(ap, _var_arg_typeof(type))))
#define va_start __va_start
#define va_arg __va_arg
#define va_end __va_end
#define va_list __va_list
#define __va_end(list) ((void)0)

#endif
