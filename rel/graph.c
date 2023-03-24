#include "graph.h"

#include "dvderr.h"
#include "game.h"
#include "irqmgr.h"
#include "libc64/malloc.h"
#include "libu64/debug.h"
#include "libultra/libultra.h"
#include "libforest/emu64/emu64_wrapper.h"
#include "m_debug.h"
#include "m_game_dlftbls.h"
#include "sys_dynamic.h"
#include "sys_ucode.h"
#include "zurumode.h"

#include "first_game.h"
#include "m_select.h"
#include "m_play.h"
#include "second_game.h"
#include "m_trademark.h"
#include "player_select.h"
#include "save_menu.h"
#include "famicom_emu.h"
#include "m_prenmi.h"

static int frame;
static BOOL SoftResetEnable;
static int skip_frame;

#define CONSTRUCT_THA_GA(tha_ga, name) \
  (THA_GA_ct((tha_ga), (Gfx*)GET_DYNAMIC_OFS(##name##_OFS), ##name##_SIZE))

static void graph_setup_double_buffer(GRAPH* this) {
  bzero(sys_dynamic, DYNAMIC_SIZE);
  *(u16*)GET_DYNAMIC_OFS(SYSDYNAMIC_HEADER_OFS) = SYSDYNAMIC_START_MAGIC;
  *(u16*)GET_DYNAMIC_OFS(SYSDYNAMIC_EPILOG_OFS) = SYSDYNAMIC_END_MAGIC;

  CONSTRUCT_THA_GA(&this->shadow_thaga, SHADOW);
  CONSTRUCT_THA_GA(&this->light_thaga, LIGHT);
  CONSTRUCT_THA_GA(&this->line_translucent_thaga, LINE_XLU);
  CONSTRUCT_THA_GA(&this->overlay_thaga, OVERLAY);
  CONSTRUCT_THA_GA(&this->line_opaque_thaga, LINE_OPA);
  CONSTRUCT_THA_GA(&this->work_thaga, WORK);
  CONSTRUCT_THA_GA(&this->polygon_opaque_thaga, POLY_OPA);
  CONSTRUCT_THA_GA(&this->polygon_translucent_thaga, POLY_XLU);
  CONSTRUCT_THA_GA(&this->font_thaga, FONT);

  this->Gfx_list10 = (Gfx*)GET_DYNAMIC_OFS(SHADOW_OFS);
  this->Gfx_list11 = (Gfx*)GET_DYNAMIC_OFS(LIGHT_OFS);
  this->Gfx_list00 = (Gfx*)GET_DYNAMIC_OFS(LINE_XLU_OFS);
  this->Gfx_list01 = (Gfx*)GET_DYNAMIC_OFS(OVERLAY_OFS);
  this->Gfx_list04 = (Gfx*)GET_DYNAMIC_OFS(LINE_OPA_OFS);
  this->Gfx_list05 = (Gfx*)GET_DYNAMIC_OFS(WORK_OFS);
  this->Gfx_list07 = (Gfx*)GET_DYNAMIC_OFS(POLY_OPA_OFS);
  this->Gfx_list08 = (Gfx*)GET_DYNAMIC_OFS(POLY_XLU_OFS);
  this->Gfx_list09 = (Gfx*)GET_DYNAMIC_OFS(FONT_OFS);

  this->gfxsave = NULL;
}

static DLFTBL_GAME* game_get_next_game_dlftbl(GAME* game) {
  void (*next_game_init_proc)(GAME*) = game_get_next_game_init(game);

  if (next_game_init_proc == first_game_init) {
    return &game_dlftbls[0];
  }
  else if (next_game_init_proc == select_init) {
    return &game_dlftbls[1];
  }
  else if (next_game_init_proc == play_init) {
    return &game_dlftbls[2];
  }
  else if (next_game_init_proc == second_game_init) {
    return &game_dlftbls[3];
  }
  else if (next_game_init_proc == trademark_init) {
    return &game_dlftbls[5];
  }
  else if (next_game_init_proc == player_select_init) {
    return &game_dlftbls[6];
  }
  else if (next_game_init_proc == save_menu_init) {
    return &game_dlftbls[7];
  }
  else if (next_game_init_proc == famicom_emu_init) {
    return &game_dlftbls[8];
  }
  else if (next_game_init_proc == prenmi_init) {
    return &game_dlftbls[9];
  }

  return NULL;
}

extern void graph_ct(GRAPH* this) {
  bzero(this, sizeof(GRAPH));
  this->frame_counter = 0;
  this->cfb_bank = 0;
  zurumode_init();
  SETREG(SREG, 33, GETREG(SREG, 33) & ~2);
  SETREG(SREG, 33, GETREG(SREG, 33) & ~1);
  GRAPH_SET_DOING_POINT(this, CT);
}

extern void graph_dt(GRAPH* this) {
  GRAPH_SET_DOING_POINT(this, DT);
  zurumode_cleanup();
}

static void graph_task_set00(GRAPH* this) {
  ucode_info ucode[2];

  GRAPH_SET_DOING_POINT(this, WAIT_TASK);
  GRAPH_SET_DOING_POINT(this, WAIT_TASK_FINISHED);
  if (ResetStatus < IRQ_RESET_DELAY) {
    ucode[0].type = UCODE_TYPE_POLY_TEXT;
    ucode[1].type = UCODE_TYPE_SPRITE_TEXT;
    ucode[0].ucode_p = ucode_GetPolyTextStart();
    ucode[1].ucode_p = ucode_GetSpriteTextStart();
    // JW_BeginFrame();
    emu64_init();
    emu64_set_ucode_info(2, ucode);
    emu64_set_first_ucode(ucode[0].ucode_p);
    emu64_taskstart(this->Gfx_list05); /* work data */
    emu64_cleanup();
    //  JW_EndFrame();
    frame++;
  }
}

static int graph_draw_finish(GRAPH* this) {
  int err = 0;
  OPEN_DISP(this);

  gSPBranchList(NOW_WORK_DISP++, this->Gfx_list10);
  gSPBranchList(NOW_SHADOW_DISP++, this->Gfx_list08);
  gSPBranchList(NOW_POLY_XLU_DISP++, this->Gfx_list11);
  gSPBranchList(NOW_LIGHT_DISP++, this->Gfx_list00);
  gSPBranchList(NOW_LINE_OPA_DISP++, this->Gfx_list01);
  gSPBranchList(NOW_OVERLAY_DISP++, this->Gfx_list09);
  gSPBranchList(NOW_FONT_DISP++, this->Gfx_list07);
  gSPBranchList(NOW_POLY_OPA_DISP++, this->Gfx_list04);
  gDPPipeSync(NOW_LINE_OPA_DISP++);
  gDPFullSync(NOW_LINE_OPA_DISP++);
  gSPEndDisplayList(NOW_LINE_OPA_DISP++);

  CLOSE_DISP(this);

  if (*(u16*)GET_DYNAMIC_OFS(SYSDYNAMIC_HEADER_OFS) != SYSDYNAMIC_START_MAGIC) {
    _dbg_hungup(__FILE__, 417);
  }

  if (*(u16*)GET_DYNAMIC_OFS(SYSDYNAMIC_EPILOG_OFS) != SYSDYNAMIC_END_MAGIC) {
    _dbg_hungup(__FILE__, 425);
    err = TRUE;
  }

  if (THA_GA_isCrash(&this->line_translucent_thaga)) {
    err = TRUE;
  }

  if (THA_GA_isCrash(&this->overlay_thaga)) {
    err = TRUE;
  }

  if (THA_GA_isCrash(&this->line_opaque_thaga)) {
    err = TRUE;
  }

  if (THA_GA_isCrash(&this->polygon_opaque_thaga)) {
    err = TRUE;
  }

  if (THA_GA_isCrash(&this->polygon_translucent_thaga)) {
    err = TRUE;
  }

  if (THA_GA_isCrash(&this->font_thaga)) {
    err = TRUE;
  }

  if (THA_GA_isCrash(&this->shadow_thaga)) {
    err = TRUE;
  }

  if (THA_GA_isCrash(&this->light_thaga)) {
    err = TRUE;
  }

  return err;
}

static void do_soft_reset(GAME* game) {
  SoftResetEnable = FALSE;
  // mBGM_reset();
  // mVibctl_reset();
  // sAdo_SoftReset();
  ResetTime = osGetTime();
  ResetStatus = IRQ_RESET_PRENMI;
}

static void reset_check(GRAPH* this, GAME* game) {
  if (SoftResetEnable && osShutdown) {
    do_soft_reset(game);
  }
}

static void graph_main(GRAPH* this, GAME* game) {
  game->disable_prenmi = FALSE;
  graph_setup_double_buffer(this);
  game_get_controller(game);
  game->disable_display = FALSE;
  GRAPH_SET_DOING_POINT(this, GAME_MAIN);
  game_main(game);
  GRAPH_SET_DOING_POINT(this, GAME_MAIN_FINISHED);
  if (ResetStatus < IRQ_RESET_DELAY) {
    if (skip_frame < GETREG(SREG, 3)) {
      skip_frame++;
      this->frame_counter++;
    } else if (game->disable_display == FALSE) {
      skip_frame = 0;
      if (graph_draw_finish(this) == FALSE) {
        GRAPH_SET_DOING_POINT(this, TASK_SET);
        graph_task_set00(this);
        GRAPH_SET_DOING_POINT(this, TASK_SET_FINISHED);
        this->frame_counter++;

        if ((GETREG(SREG, 33) & 1) != 0) {
          SETREG(SREG, 33, GETREG(SREG, 33) & ~1);
        }
      }
    }
  }

  if (GETREG(SREG, 20) < 2) {
    GRAPH_SET_DOING_POINT(this, AUDIO);
    // sAdo_GameFrame();
    GRAPH_SET_DOING_POINT(this, AUDIO_FINISHED);
  }

  reset_check(this, game);

  if (ResetStatus == IRQ_RESET_PRENMI && game->disable_prenmi == FALSE) {
    GAME_GOTO_NEXT(game, prenmi, PRENMI);
  }
}

extern void graph_proc(void* arg) {
  DLFTBL_GAME* dlftbl = &game_dlftbls[0];
  graph_ct(&graph_class);

  while (dlftbl != NULL) {
    size_t size = dlftbl->alloc_size;
    GAME* game = (GAME*)malloc(size);
    game_class_p = game;
    bzero(game, size);
    GRAPH_SET_DOING_POINT(&graph_class, GAME_CT);
    game_ct(game);
    emu64_refresh();
    GRAPH_SET_DOING_POINT(&graph_class, GAME_CT_FINISHED);

    while (game_is_doing(game)) {
      if (!dvderr_draw()) {
        graph_main(&graph_class, game);
      }
    }

    dlftbl = game_get_next_game_dlftbl(game);
    GRAPH_SET_DOING_POINT(&graph_class, GAME_DT);
    game_dt(game);
    GRAPH_SET_DOING_POINT(&graph_class, GAME_DT_FINISHED);
    free(game);
    game_class_p = NULL;
  }

  graph_dt(&graph_class);
}
