#ifndef M_LIGHTS_H
#define M_LIGHTS_H

#include "types.h"
#include "libforest/gbi_extensions.h"
#include "m_lib.h"
#include "m_play_h.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ u8 color[3];
    /* 0x9 */ u8 drawGlow;
    /* 0xA */ s16 radius;
} LightPoint; // size = 0xC

typedef struct {
    /* 0x0 */ s8 x;
    /* 0x1 */ s8 y;
    /* 0x2 */ s8 z;
    /* 0x3 */ u8 color[3];
} LightDiffuse; // size = 0x6

typedef union {
    LightPoint point;
    LightDiffuse diffuse;
} LightParams; // size = 0xC

typedef struct lights_s {
    u8 type;
    LightParams lights;
} Lights; // size = 0xE

typedef struct light_list {
    /* 0x0 */ Lights* info;
    /* 0x4 */ struct light_list* prev;
    /* 0x8 */ struct light_list* next;
} Light_list; // size = 0xC

typedef struct light_buf_s {
    int current;
    int idx;
    Light_list lights[32];
} Light_buffer;

typedef struct lightsn_s {
    u8 diffuse_count;
    Ambient a;
    Light_new l[7];
} LightsN;

typedef struct global_light_s {
    /* 0x0 */ Light_list* list;
    /* 0x4 */ u8 ambientColor[3];
    /* 0x7 */ u8 fogColor[3];
    /* 0xA */ s16 fogNear;
    /* 0xC */ s16 fogFar;
} Global_light; // size = 0x10

typedef void (*light_point_proc)(LightsN*, LightParams*, xyz_t*);
typedef void (*light_P_point_proc)(LightsN*, LightParams*, xyz_t*);

extern void Light_point_ct(Lights* lights, s16 x, s16 y, s16 z, u8 r, u8 g, u8 b, s16 radius);
extern void Light_diffuse_ct(Lights* lights, s8 x, s8 y, s8 z, u8 r, u8 g, u8 b);
extern void LightsN_disp_BG(LightsN* lights, GRAPH* graph);
extern void LightsN_disp(LightsN* lights, GRAPH* graph);
extern void LightsN_list_check(LightsN* lights, Light_list* node, xyz_t* pos);
extern void Global_light_ct(Global_light* glight);
extern LightsN* Global_light_read(Global_light* glight, GRAPH* graph);
extern Light_list* Global_light_list_new(GAME* game, Global_light* glight, Lights* light);
extern void Global_light_list_delete(Global_light* glight, Light_list* light);
extern void Light_list_point_draw(GAME_PLAY* play);

#ifdef __cplusplus
}
#endif

#endif
