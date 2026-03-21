#include "graph.h"

#include "audio.h"
#include "dvderr.h"
#include "famicom_emu.h"
#include "first_game.h"
#include "game.h"
#include "irqmgr.h"
#include "libc64/malloc.h"
#include "libforest/emu64/emu64_wrapper.h"
#include "jsyswrap.h"
#include "libu64/debug.h"
#include "libultra/libultra.h"
#include "m_bgm.h"
#include "m_debug.h"
#include "m_game_dlftbls.h"
#include "m_play.h"
#include "m_prenmi.h"
#include "m_select.h"
#include "m_trademark.h"
#include "m_vibctl.h"
#include "player_select.h"
#include "save_menu.h"
#include "second_game.h"
#include "sys_dynamic.h"
#include "sys_ucode.h"
#include "zurumode.h"

GRAPH graph_class;

static int skip_frame; // TODO: this is actually declared in graph_main
#if VERSION != VER_GAFU01_00
u8 SoftResetEnable;
#endif
static int frame; // TODO: this is actually declared in graph_task_set00

#define CONSTRUCT_THA_GA(tha_ga, name, name2) (THA_GA_ct((tha_ga), sys_dynamic.name, name2##_SIZE * sizeof(Gfx)))

static void graph_setup_double_buffer(GRAPH* this) {
    bzero(&sys_dynamic, sizeof(dynamic_t));
    sys_dynamic.start_magic = SYSDYNAMIC_START_MAGIC;
    sys_dynamic.end_magic = SYSDYNAMIC_END_MAGIC;

    CONSTRUCT_THA_GA(&this->bg_opaque_thaga, new0, NEW0);
    CONSTRUCT_THA_GA(&this->bg_translucent_thaga, new1, NEW1);
    CONSTRUCT_THA_GA(&this->polygon_opaque_thaga, poly_opa, POLY_OPA);
    CONSTRUCT_THA_GA(&this->polygon_translucent_thaga, poly_xlu, POLY_XLU);
    CONSTRUCT_THA_GA(&this->overlay_thaga, overlay, OVERLAY);
    CONSTRUCT_THA_GA(&this->work_thaga, work, WORK);
    CONSTRUCT_THA_GA(&this->font_thaga, font, FONT);
    CONSTRUCT_THA_GA(&this->shadow_thaga, shadow, SHADOW);
    CONSTRUCT_THA_GA(&this->light_thaga, light, LIGHT);

    this->Gfx_list10 = sys_dynamic.new0;
    this->Gfx_list11 = sys_dynamic.new1;
    this->Gfx_list00 = sys_dynamic.poly_opa;
    this->Gfx_list01 = sys_dynamic.poly_xlu;
    this->Gfx_list04 = sys_dynamic.overlay;
    this->Gfx_list05 = sys_dynamic.work;
    this->Gfx_list07 = sys_dynamic.font;
    this->Gfx_list08 = sys_dynamic.shadow;
    this->Gfx_list09 = sys_dynamic.light;

    this->gfxsave = NULL;
}

#define ARE_INIT_PROCS_EQUAL(proc0, proc1) (((void (*)(GAME*))proc0) == ((void (*)(GAME*))proc1))
static DLFTBL_GAME* game_get_next_game_dlftbl(GAME* game) {
    void (*next_game_init_proc)(GAME*) = game_get_next_game_init(game);

    if (ARE_INIT_PROCS_EQUAL(next_game_init_proc, first_game_init)) {
        return &game_dlftbls[0];
    } else if (ARE_INIT_PROCS_EQUAL(next_game_init_proc, select_init)) {
        return &game_dlftbls[1];
    } else if (ARE_INIT_PROCS_EQUAL(next_game_init_proc, play_init)) {
        return &game_dlftbls[2];
    } else if (ARE_INIT_PROCS_EQUAL(next_game_init_proc, second_game_init)) {
        return &game_dlftbls[3];
    } else if (ARE_INIT_PROCS_EQUAL(next_game_init_proc, trademark_init)) {
        return &game_dlftbls[5];
    } else if (ARE_INIT_PROCS_EQUAL(next_game_init_proc, player_select_init)) {
        return &game_dlftbls[6];
    } else if (ARE_INIT_PROCS_EQUAL(next_game_init_proc, save_menu_init)) {
        return &game_dlftbls[7];
    } else if (ARE_INIT_PROCS_EQUAL(next_game_init_proc, famicom_emu_init)) {
        return &game_dlftbls[8];
    } else if (ARE_INIT_PROCS_EQUAL(next_game_init_proc, prenmi_init)) {
        return &game_dlftbls[9];
    }

    return NULL;
}

extern void graph_ct(GRAPH* this) {
    bzero(this, sizeof(GRAPH));
    this->frame_counter = 0;
    this->cfb_bank = 0;
    SETREG(SREG, 33, GETREG(SREG, 33) & ~2);
    SETREG(SREG, 33, GETREG(SREG, 33) & ~1);
    zurumode_init();
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
        this->last_dl = this->Gfx_list05;
        if (this->taskEndCallback != NULL) {
            this->taskEndCallback(this, this->taskEndData);
        }

        if (ResetStatus < IRQ_RESET_DELAY) {
            ucode[0].type = UCODE_TYPE_POLY_TEXT;
            ucode[1].type = UCODE_TYPE_SPRITE_TEXT;
            ucode[0].ucode_p = ucode_GetPolyTextStart();
            ucode[1].ucode_p = ucode_GetSpriteTextStart();
            JW_BeginFrame();
            emu64_init();
            emu64_set_ucode_info(2, ucode);
            emu64_set_first_ucode(ucode[0].ucode_p);
            emu64_taskstart(this->Gfx_list05); /* work data */
            emu64_cleanup();
            JW_EndFrame();
            frame++;
        }
    }
}

static int graph_draw_finish(GRAPH* this) {
    int err;
    OPEN_DISP(this);

    gSPBranchList(NOW_WORK_DISP++, this->Gfx_list10);
    gSPBranchList(NOW_BG_OPA_DISP++, this->Gfx_list08);
    gSPBranchList(NOW_SHADOW_DISP++, this->Gfx_list11);
    gSPBranchList(NOW_BG_XLU_DISP++, this->Gfx_list00);
    gSPBranchList(NOW_POLY_OPA_DISP++, this->Gfx_list01);
    gSPBranchList(NOW_POLY_XLU_DISP++, this->Gfx_list09);
    gSPBranchList(NOW_LIGHT_DISP++, this->Gfx_list07);
    gSPBranchList(NOW_FONT_DISP++, this->Gfx_list04);
    gDPPipeSync(NOW_OVERLAY_DISP++);
    gDPFullSync(NOW_OVERLAY_DISP++);
    gSPEndDisplayList(NOW_OVERLAY_DISP++);

    CLOSE_DISP(this);
    err = FALSE;

    SYSDYNAMIC_OPEN();
    if (!SYSDYNAMIC_CHECK_START()) {
#if VERSION == VER_GAFU01_00
        _dbg_hungup(__FILE__, 416);
#elif VERSION == VER_GAFE01_00
        _dbg_hungup(__FILE__, 417);
#endif
    }

    if (!SYSDYNAMIC_CHECK_END()) {
        err = TRUE;
#if VERSION == VER_GAFU01_00
        _dbg_hungup(__FILE__, 424);
#elif VERSION == VER_GAFE01_00
        _dbg_hungup(__FILE__, 425);
#endif
    }
    SYSDYNAMIC_CLOSE();

    if (THA_GA_isCrash(&this->polygon_opaque_thaga)) {
        err = TRUE;
    }

    if (THA_GA_isCrash(&this->polygon_translucent_thaga)) {
        err = TRUE;
    }

    if (THA_GA_isCrash(&this->overlay_thaga)) {
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

    if (THA_GA_isCrash(&this->bg_opaque_thaga)) {
        err = TRUE;
    }

    if (THA_GA_isCrash(&this->bg_translucent_thaga)) {
        err = TRUE;
    }

    return err;
}

static void do_soft_reset(GAME* game) {
    SoftResetEnable = FALSE;
    mBGM_reset();
    mVibctl_reset();
    sAdo_SoftReset();
    ResetTime = osGetTime();
    ResetStatus = IRQ_RESET_PRENMI;
}

static void reset_check(GRAPH* this, GAME* game) {
    if (SoftResetEnable && osShutdown) {
        do_soft_reset(game);
    }
}

// Aus version removes debug frame skip logic
#if VERSION >= VER_GAFU01_00
static void graph_main(GRAPH* this, GAME* game) {
    game->disable_prenmi = FALSE;
    graph_setup_double_buffer(this);
    game_get_controller(game);
    game->disable_display = FALSE;
    GRAPH_SET_DOING_POINT(this, GAME_MAIN);
    game_main(game);
    GRAPH_SET_DOING_POINT(this, GAME_MAIN_FINISHED);
    if (ResetStatus < IRQ_RESET_DELAY) {
        if (game->disable_display == FALSE) {
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
        sAdo_GameFrame();
        GRAPH_SET_DOING_POINT(this, AUDIO_FINISHED);
    }

    reset_check(this, game);

    if (ResetStatus == IRQ_RESET_PRENMI && game->disable_prenmi == FALSE) {
        GAME_GOTO_NEXT(game, prenmi, PRENMI);
    }
}
#else
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
        sAdo_GameFrame();
        GRAPH_SET_DOING_POINT(this, AUDIO_FINISHED);
    }

    reset_check(this, game);

    if (ResetStatus == IRQ_RESET_PRENMI && game->disable_prenmi == FALSE) {
        GAME_GOTO_NEXT(game, prenmi, PRENMI);
    }
}
#endif

extern void graph_proc(void* arg) {
    GRAPH* __graph = &graph_class;
    DLFTBL_GAME* dlftbl = &game_dlftbls[0];
    graph_ct(&graph_class);

    while (dlftbl != NULL) {
        size_t size = dlftbl->alloc_size;
        GAME* game = (GAME*)malloc(size);
        game_class_p = game;
        bzero(game, size);
        GRAPH_SET_DOING_POINT(__graph, GAME_CT);
        game_ct(game, dlftbl->init, __graph);
        emu64_refresh();
        GRAPH_SET_DOING_POINT(__graph, GAME_CT_FINISHED);

        while (game_is_doing(game)) {
            if (!dvderr_draw()) {
                graph_main(__graph, game);
            }
        }

        dlftbl = game_get_next_game_dlftbl(game);
        GRAPH_SET_DOING_POINT(__graph, GAME_18);
        GRAPH_SET_DOING_POINT(__graph, GAME_DT);
        game_dt(game);
        GRAPH_SET_DOING_POINT(__graph, GAME_DT_FINISHED);
        free(game);
        game_class_p = NULL;
    }

    graph_dt(__graph);
}
