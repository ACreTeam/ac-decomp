#ifndef GRAPH_H
#define GRAPH_H

#include "types.h"
#include "PR/mbi.h"
#include "THA_GA.h"
#include "dolphin/os/OSMessage.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  GRAPH_DOING_ZERO = 0,
  GRAPH_DOING_CT,
  GRAPH_DOING_GAME_CT,
  GRAPH_DOING_GAME_CT_FINISHED,
  GRAPH_DOING_GAME_MAIN,
  GRAPH_DOING_GAME_TIME,
  GRAPH_DOING_GAME_TIME_FINISHED,
  GRAPH_DOING_GAME_EXEC,
  GRAPH_DOING_GAME_EXEC_FINISHED,
  GRAPH_DOING_GAME_BGM,
  GRAPH_DOING_GAME_BGM_FINISHED,
  GRAPH_DOING_GAME_MAIN_FINISHED,
  GRAPH_DOING_TASK_SET,
  GRAPH_DOING_WAIT_TASK,
  GRAPH_DOING_WAIT_TASK_FINISHED,
  GRAPH_DOING_TASK_SET_FINISHED,
  GRAPH_DOING_AUDIO,
  GRAPH_DOING_AUDIO_FINISHED,
  GRAPH_DOING_GAME_18, /* Not sure what this is, relevant code removed */
  GRAPH_DOING_GAME_DT,
  GRAPH_DOING_GAME_DT_FINISHED,
  GRAPH_DOING_DT,
  GRAPH_DOING_END
} GRAPH_DOING_POINT;

#define GRAPH_MSG_BUF_COUNT 8

typedef struct graph_s {
  /* 0x0000 */ Gfx* Gfx_list00; /* line translucent */
  /* 0x0004 */ Gfx* Gfx_list01; /* overlay */
  /* 0x0008 */ void* DepthBuffer;
  /* 0x000C */ Gfx* Gfx_list03; /* unused */
  /* 0x0010 */ Gfx* Gfx_list04; /* line opaque */
  /* 0x0014 */ Gfx* Gfx_list07; /* polygon opaque */
  /* 0x0018 */ Gfx* Gfx_list08; /* polygon translucent */
  /* 0x001C */ Gfx* Gfx_list09; /* font */
  /* 0x0020 */ Gfx* gfxsave;
  /* 0x0024 */ u8 _unk24[32];
  /* 0x0044 */ OSMessage graphReplyMesgBuf[GRAPH_MSG_BUF_COUNT];
  /* 0x0064 */ OSMessageQueue* schedMesgQueue;
  /* 0x0068 */ OSMessageQueue graphReplyMesgQueue;
  /* 0x0088 */ u8 _unused_ossctask00p[0x50]; /* real type = OSScTask */
  /* 0x00D8 */ u8 _unused_ossctask01p[0x50]; /* real type = OSScTask */
  /* 0x0128 */ u8 _unused_ossctask02p[0x50]; /* real type = OSScTask */
  /* 0x0178 */ u8 _unk178[0x48]; /* If graphReplyMesgQueue is N64 type, this may be another OSScTask */
  /* 0x01C0 */ Gfx* Gfx_list05; /* work */
  /* 0x01C4 */ THA_GA work_thaga;
  /* 0x01D4 */ u8 _unk1D4[0xDC]; /* Maybe related to more OSScTask stuff? */
  /* 0x02B0 */ void* scheduler; /* Actually points to OSSched struct, only used in DnM? */
  /* 0x02B4 */ void* vimode; /* Actually points to OSViMode struct, not used in AC. */
  /* 0x02B8 */ THA_GA line_opaque_thaga;
  /* 0x02C8 */ THA_GA line_translucent_thaga;
  /* 0x02D8 */ THA_GA overlay_thaga;
  /* 0x02E8 */ THA_GA polygon_opaque_thaga;
  /* 0x02F8 */ THA_GA polygon_translucent_thaga;
  /* 0x0308 */ THA_GA font_thaga;
  /* 0x0318 */ THA_GA shadow_thaga;
  /* 0x0328 */ THA_GA light_thaga;
  /* 0x0338 */ int frame_counter;
  /* 0x033C */ u16* frameBuffer;
  /* 0x0340 */ u16* renderBuffer;
  /* 0x0344 */ u32 vispecial;
  /* 0x0348 */ u8 doing_point;
  /* 0x0349 */ u8 _unk349;
  /* 0x034A */ u8 need_viupdate;
  /* 0x034B */ u8 cfb_bank;
  /* 0x034C */ void (*taskEndCallback)(struct graph_s*, void*);
  /* 0x0350 */ void* taskEndData;
  /* 0x0354 */ f32 vixscale;
  /* 0x0358 */ f32 viyscale;
  /* 0x035C */ Gfx* last_dl;
  /* 0x0360 */ Gfx* Gfx_list10; /* shadow */
  /* 0x0364 */ Gfx* Gfx_list11; /* light */
} GRAPH ATTRIBUTE_ALIGN(8); // one of the missing structs is likely aligned to 8 bytes.

extern void graph_proc(void* arg);
extern void graph_ct(GRAPH* this);
extern void graph_dt(GRAPH* this);

#define GRAPH_SET_DOING_POINT(g, point) ((g)->doing_point = GRAPH_DOING_##point)

/* Graph display list macros for style and correctness enforcement */

#define OPEN_DISP(graph) 			        \
  {						                        \
    GRAPH* __graph = (graph); 		    \
    int __gfx_opened = 0;             \
	while (0)

#define CLOSE_DISP(graph) 			      \
	  (void)__gfx_opened; 		          \
  }						                        \
  while (0)

#define NEXT_DISP(thaga) ((thaga)->thaGfx.head_p++)
#define NOW_DISP(thaga) ((thaga)->thaGfx.head_p)

#define NEXT_LINE_XLU_DISP NEXT_DISP(&__graph->line_translucent_thaga)
#define NEXT_LINE_OPA_DISP NEXT_DISP(&__graph->line_opaque_thaga)
#define NEXT_POLY_OPA_DISP NEXT_DISP(&__graph->polygon_opaque_thaga)
#define NEXT_POLY_XLU_DISP NEXT_DISP(&__graph->polygon_translucent_thaga)
#define NEXT_OVERLAY_DISP NEXT_DISP(&__graph->overlay_thaga)
#define NEXT_WORK_DISP NEXT_DISP(&__graph->work_thaga)
#define NEXT_FONT_DISP NEXT_DISP(&__graph->font_thaga)
#define NEXT_SHADOW_DISP NEXT_DISP(&__graph->shadow_thaga)
#define NEXT_LIGHT_DISP	NEXT_DISP(&__graph->light_thaga)

#define NOW_LINE_XLU_DISP (Gfx*)NOW_DISP(&__graph->line_translucent_thaga)
#define NOW_LINE_OPA_DISP (Gfx*)NOW_DISP(&__graph->line_opaque_thaga)
#define NOW_POLY_OPA_DISP (Gfx*)NOW_DISP(&__graph->polygon_opaque_thaga)
#define NOW_POLY_XLU_DISP (Gfx*)NOW_DISP(&__graph->polygon_translucent_thaga)
#define NOW_OVERLAY_DISP (Gfx*)NOW_DISP(&__graph->overlay_thaga)
#define NOW_WORK_DISP (Gfx*)NOW_DISP(&__graph->work_thaga)
#define NOW_FONT_DISP (Gfx*)NOW_DISP(&__graph->font_thaga)
#define NOW_SHADOW_DISP (Gfx*)NOW_DISP(&__graph->shadow_thaga)
#define NOW_LIGHT_DISP (Gfx*)NOW_DISP(&__graph->light_thaga)

extern u8 SoftResetEnable;
extern GRAPH graph_class;

#ifdef __cplusplus
};
#endif

#endif
