#include "m_debug_display.h"
#include "m_rcp.h"
#include "sys_matrix.h"

typedef void (*DEBUG_DISP_PROC)(Debug_display*, void*, GAME_PLAY*);

typedef struct debug_display_info_s{
    /* 0x0 */ s16 type;
    /* 0x4 */ void* arg;
} Debug_display_info;       

static void debug_display_output_sprite_16x16_I8(Debug_display *, void *, GAME_PLAY *);
static void debug_display_output_polygon(Debug_display *, void *, GAME_PLAY *);

Debug_display* debug_display;

void Debug_Display_init(){
    debug_display = NULL;
}

extern Debug_display* Debug_Display_new(f32 posX, f32 posY, f32 posZ, f32 scaleX, f32 scaleY, f32 scaleZ,
s16 rotX, s16 rotY, s16 rotZ, s8 r, s8 g, s8 b, s8 alpha, s16 type, GRAPH* graph){

    Debug_display* display = debug_display;

    debug_display = GRAPH_ALLOC(graph, sizeof(Debug_display) + 4);

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
    debug_display->type = type;
    debug_display->next = display;

    return debug_display; 
}

extern void* no_txt;
extern void* nx_txt;
extern void* np_txt;
extern void* nt_txt;
extern Gfx darrow_model[];
extern Gfx camera_model[];

#pragma pool_data off
extern void Debug_Display_output(GAME_PLAY* play){ 
    static DEBUG_DISP_PROC debug_display_output_proc[] = { debug_display_output_sprite_16x16_I8, debug_display_output_polygon};
    static Debug_display_info debug_display_shape_data[] = {
        {0, &no_txt}, {0, &nx_txt}, {0, &np_txt}, {0, &nt_txt}, {1, darrow_model}, {1, camera_model},
    };    

    Debug_display_info* data;
    Debug_display* display = debug_display;  

    while(display != NULL){
        data = &debug_display_shape_data[display->type]; 
        debug_display_output_proc[data->type](display, data->arg, play);
        display = display->next;
    }
}

extern Gfx RCP_debug_texture_16x16_8[];
#pragma pool_data on

static void debug_display_output_sprite_16x16_I8(Debug_display* display, void* txt, GAME_PLAY* play){

    OPEN_DISP(play->game.graph);

    softsprite_prim(play->game.graph);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 0, display->color.r, display->color.g, display->color.b, display->color.a);
 
    Matrix_translate(display->pos.x, display->pos.y, display->pos.z, 0);
    Matrix_scale(display->scale.x, display->scale.y, display->scale.z, 1);
    Matrix_mult(&play->billboard_matrix, 1);
    Matrix_rotateXYZ(display->rot.x, display->rot.y, display->rot.z, 1);
    
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
    Matrix_scale(display->scale.x, display->scale.y, display->scale.z, 1);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(play->game.graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(NEXT_POLY_XLU_DISP, dl);
    CLOSE_DISP(play->game.graph);
}

