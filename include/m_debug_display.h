#ifndef M_DEBUG_DISPLAY_H
#define M_DEBUG_DISPLAY_H

#include "types.h"
#include "m_play.h"

enum {
    Debug_Display_SHAPE_O_TXT,         // 16x16 sprite with O
    Debug_Display_SHAPE_X_TXT,         // 16x16 sprite with X
    Debug_Display_SHAPE_CIRCLE_TXT,    // 16x16 sprite with circle
    Debug_Display_SHAPE_CROSSHAIR_TXT, // 16x16 sprite with crosshair
    Debug_Display_SHAPE_ARROW_MODEL,   // 3D model of an arrow
    Debug_Display_SHAPE_CAMERA_MODEL,  // 3D model of a camera

    Debug_Display_SHAPE_NUM
};

typedef struct debug_display_s Debug_display;

struct debug_display_s {
    xyz_t pos;
    s_xyz rot;
    xyz_t scale;
    rgba8888_t color;
    s16 shape;
    Debug_display* next;
};

extern void Debug_Display_init();
extern Debug_display* Debug_Display_new(f32 posX, f32 posY, f32 posZ, s16 rotX, s16 rotY, s16 rotZ, f32 scaleX,
                                        f32 scaleY, f32 scaleZ, u8 r, u8 g, u8 b, u8 alpha, s16 shape, GRAPH* graph);
extern void Debug_Display_output(GAME_PLAY* play);

extern Debug_display* debug_display;

#endif
