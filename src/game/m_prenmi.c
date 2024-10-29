#include "m_prenmi.h"
#include "second_game.h"
#include "irqmgr.h"
#include "sys_vimgr.h"
#include "m_rcp.h"

static void prenmi_move(GAME_PRENMI* prenmi) {    
  if (ResetStatus == IRQ_RESET_DELAY || prenmi->timer == 0) {
    prenmi->game.disable_prenmi = FALSE;
    ResetStatus = IRQ_RESET_NORMAL;
    ResetTime = 0;
    viBlack(TRUE);
    GAME_GOTO_NEXT((GAME*)prenmi, second_game, SECOND);
  }
  else{
    prenmi->timer--;
  }
}

static void prenmi_draw(GAME_PRENMI* prenmi) {    
  GRAPH* graph;
  Gfx* gfx;
  f32 timer;
  f32 y_pos;
  
  graph = prenmi->game.graph;
  OPEN_DISP(graph);
  
  DisplayList_initialize(graph, 0, 0, 0, NULL);
  gfx = NOW_POLY_OPA_DISP;
  
  gDPPipeSync(gfx++);
  gDPSetOtherMode(gfx++, G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PRIM | G_RM_XLU_SURF | G_RM_XLU_SURF2);
  gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);

  timer = prenmi->timer;
  
  // set opacity
  y_pos = (1.0f - (timer / (f32)PRENMI_TIMER)) * -240.0f + 250.0f;
  gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, (u8)y_pos);

  // adjust size
  y_pos = (1.0f - (timer / (f32)PRENMI_TIMER)) * -15.0f + 127.0f;
  gfx = gfx_gSPTextureRectangle1(gfx, 0, (u32)(y_pos * 4.0f), 0x500, (u32)((y_pos + 1.0f) * 4.0f), 0, 0, 0, 0, 0);
  
  gDPPipeSync(gfx++);
  SET_POLY_OPA_DISP(gfx);

  CLOSE_DISP(graph);
}

static void prenmi_main(GAME* game) {
  GRAPH* graph;    
  GAME_PRENMI* prenmi = (GAME_PRENMI*)game;
  
  prenmi->game.disable_prenmi = TRUE;
  prenmi_move(prenmi);
  prenmi_draw(prenmi);
  graph = game->graph;
  game_debug_draw_last(game, graph);
  game_draw_last(graph);
}

extern void prenmi_cleanup(GAME* game) {
  SoftResetEnable = TRUE;
}

extern void prenmi_init(GAME* game) {
  GAME_PRENMI* prenmi = (GAME_PRENMI*)game;
  
  prenmi->game.exec = &prenmi_main;
  prenmi->game.cleanup = &prenmi_cleanup;
  prenmi->timer = PRENMI_TIMER;
  SetGameFrame(1);
}
