#include "m_debug_display.h"
#include "m_rcp.h"
#include "sys_matrix.h"

enum {
    Debug_Display_DRAW_SPRITE,
    Debug_Display_DRAW_POLYGON,

    Debug_Display_DRAW_TYPE_NUM
};

typedef void (*DEBUG_DISP_PROC)(Debug_display*, void*, GAME_PLAY*);

typedef struct debug_display_info_s {
    /* 0x0 */ s16 type;
    /* 0x4 */ void* arg;
} Debug_display_info;

static void debug_display_output_sprite_16x16_I8(Debug_display*, void*, GAME_PLAY*);
static void debug_display_output_polygon(Debug_display*, void*, GAME_PLAY*);

Debug_display* debug_display;

extern void Debug_Display_init(void) {
    debug_display = NULL;
}

extern Debug_display* Debug_Display_new(f32 posX, f32 posY, f32 posZ, s16 rotX, s16 rotY, s16 rotZ, f32 scaleX,
                                        f32 scaleY, f32 scaleZ, u8 r, u8 g, u8 b, u8 alpha, s16 shape, GRAPH* graph) {

    Debug_display* prev_display = debug_display;

    // allocate new debug display, aligned to 8 bytes to match Gfx size
    debug_display = GRAPH_ALLOC(graph, ALIGN_NEXT(sizeof(Debug_display), 8));
    debug_display->pos.x = posX;
    debug_display->pos.y = posY;
    debug_display->pos.z = posZ;
    debug_display->rot.x = rotX;
    debug_display->rot.y = rotY;
    debug_display->rot.z = rotZ;
    debug_display->scale.x = scaleX;
    debug_display->scale.y = scaleY;
    debug_display->scale.z = scaleZ;
    debug_display->color.r = r;
    debug_display->color.g = g;
    debug_display->color.b = b;
    debug_display->color.a = alpha;
    debug_display->shape = shape;
    debug_display->next = prev_display;

    return debug_display;
}

extern u8 no_txt[];
extern u8 nx_txt[];
extern u8 np_txt[];
extern u8 nt_txt[];
extern Gfx darrow_model[];
extern Gfx camera_model[];

extern void Debug_Display_output(GAME_PLAY* play) {
    static DEBUG_DISP_PROC debug_display_output_proc[] = { debug_display_output_sprite_16x16_I8,
                                                           debug_display_output_polygon };
    static Debug_display_info debug_display_shape_data[] = {
        { Debug_Display_DRAW_SPRITE, no_txt },        { Debug_Display_DRAW_SPRITE, nx_txt },
        { Debug_Display_DRAW_SPRITE, np_txt },        { Debug_Display_DRAW_SPRITE, nt_txt },
        { Debug_Display_DRAW_POLYGON, darrow_model }, { Debug_Display_DRAW_POLYGON, camera_model },
    };

    Debug_display_info* data;
    Debug_display* display = debug_display;

    while (display != NULL) {
        data = &debug_display_shape_data[display->shape];
        debug_display_output_proc[data->type](display, data->arg, play);
        display = display->next;
    }
}

extern Gfx RCP_debug_texture_16x16_8[];

static void debug_display_output_sprite_16x16_I8(Debug_display* display, void* txt, GAME_PLAY* play) {

    OPEN_DISP(play->game.graph);

    softsprite_prim(play->game.graph);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 0, display->color.r, display->color.g, display->color.b, display->color.a);

    Matrix_translate(display->pos.x, display->pos.y, display->pos.z, MTX_LOAD);
    Matrix_scale(display->scale.x, display->scale.y, display->scale.z, MTX_MULT);
    Matrix_mult(&play->billboard_matrix, MTX_MULT);
    Matrix_rotateXYZ(display->rot.x, display->rot.y, display->rot.z, MTX_MULT);

    gDPLoadTextureBlock(NEXT_POLY_XLU_DISP, txt, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(play->game.graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(NEXT_POLY_XLU_DISP, RCP_debug_texture_16x16_8);
    CLOSE_DISP(play->game.graph);
}

static void debug_display_output_polygon(Debug_display* display, void* dl, GAME_PLAY* play) {
    static Lights1 material = gdSPDefLights1(128, 128, 128, 255, 255, 255, 73, 73, 73);

    OPEN_DISP(play->game.graph);

    polygon_z_light_prim(play->game.graph);

    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 0, display->color.r, display->color.g, display->color.b, display->color.a);

    gSPSetLights1(NEXT_POLY_XLU_DISP, material);

    Matrix_softcv3_load(&display->rot, display->pos.x, display->pos.y, display->pos.z);
    Matrix_scale(display->scale.x, display->scale.y, display->scale.z, MTX_MULT);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(play->game.graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(NEXT_POLY_XLU_DISP, dl);
    CLOSE_DISP(play->game.graph);
}
