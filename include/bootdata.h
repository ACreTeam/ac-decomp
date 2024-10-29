#ifndef BOOTDATA_H
#define BOOTDATA_H

#include "types.h"
#include "PR/gbi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LOGO_COLOR_R 220
#define LOGO_COLOR_G 0
#define LOGO_COLOR_B 0

extern Gfx gam_win1_winT_model[];
extern Gfx gam_win2_winT_model[];

extern Gfx gam_win1_cursor_model[];

extern Gfx gam_win1_moji_model[];
extern Gfx gam_win1_moji2_model[];
extern Gfx gam_win1_moji3_model[];

extern Gfx gam_win2_moji_model[];
extern Gfx gam_win3_moji_model[];

extern u8 nintendo_376x104[];
extern Vtx logo_nin_v[];
extern Gfx logo_ninT_model[];

#ifdef __cplusplus
}
#endif

#endif
