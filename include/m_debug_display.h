#ifndef M_DEBUG_DISPLAY_H
#define M_DEBUG_DISPLAY_H

#include "types.h"
#include "m_play.h"

typedef struct debug_display_s Debug_display;

struct debug_display_s{
    xyz_t pos;
    s_xyz rot;
    xyz_t scale;
    rgba8888_t color;
    s16 type;
    Debug_display* next;
};
extern void Debug_Display_init();
extern Debug_display* Debug_Display_new(f32 posX, f32 posY, f32 posZ, f32 scaleX, f32 scaleY, f32 scaleZ,
s16 rotX, s16 rotY, s16 rotZ, s8 r, s8 g, s8 b, s8 alpha, s16 type, GRAPH* graph);
extern void Debug_Display_output(GAME_PLAY* play);



extern Debug_display* debug_display;

#endif