#include "stdarg.h"

void* __va_arg(va_list v_list, int type) {
    char* addr;
    char* reg = &(v_list->gpr);
    long g_reg = v_list->gpr;
    long maxsize = 8;
    long size = 4;
    long increment = 1;
    long even = 0;
    long fpr_offset = 0;
    long regsize = 4;

    if (type == 3) {
        reg = &(v_list->fpr);
        g_reg = v_list->fpr;
        size = 8;
        fpr_offset = 32;
        regsize = 8;
    }
    if (type == 2) {
        size = 8;
        maxsize--;
        if (g_reg & 1)
            even = 1;
        increment = 2;
    }
    if (g_reg < maxsize) {
        g_reg += even;
        addr = v_list->reg_save_area + fpr_offset + (g_reg * regsize);
        *reg = g_reg + increment;
    } else {
        *reg = 8;
        addr = v_list->input_arg_area;
        addr = (char*)(((unsigned long)(addr) + ((size)-1)) & ~((size)-1));
        v_list->input_arg_area = addr + size;
    }
    if (type == 0)
        addr = *((char**)addr);

    return addr;
}
