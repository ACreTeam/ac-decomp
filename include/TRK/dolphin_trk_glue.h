#ifndef DOLPHIN_TRK_GLUE_H
#define DOLPHIN_TRK_GLUE_H
#include "types.h"
#include "TRK/trk.h"
#ifdef __cplusplus
extern "C"{
#endif


TRKResult TRKInitializeIntDrivenUART(u32, u32, u32, void*);
void TRK_board_display(const char*);

#ifdef __cplusplus
}
#endif
#endif
