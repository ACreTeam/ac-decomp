#include "reload_data.h"
#include "m_game_dlftbls.h"
#include <dolphin/os.h>
#include "libultra/os_thread.h"
#include "boot.h"
#include "m_scene.h"
#include "m_common_data.h"
#include "m_rcp.h"

#define RELOAD_DATA_STACK_MAGIC 123456789ll // 0x75BCD15

static void reload_data_check_stack(GAME_RELOAD_DATA* reload_data) {
    // Based on this I suspect that these are part of the stack itself,
    // and pulled out into variables.
    u64 stack_preguard = reload_data->stack_preguard;
    u64 stack_postguard = reload_data->stack_postguard;

    if (stack_preguard != RELOAD_DATA_STACK_MAGIC || stack_postguard != RELOAD_DATA_STACK_MAGIC) {
        // The stack area for reading indoor and outdoor data is overflowing
        OSReport("室内外データの読み込みの為のスタック領域があふれている\n");
    }
}

static int reload_data_check_thread(void) {
    if (gamePT != NULL && gamePT->game_dlf_no == GAME_DLFTBL_RELOAD_DATA) {
        GAME_RELOAD_DATA* reload_data = (GAME_RELOAD_DATA*)gamePT;

        if (!osIsTerminatedThread(&reload_data->thread)) {
            return TRUE;
        }
    }

    return FALSE;
}

extern void reload_data_cleanup(GAME* game) {
    GAME_RELOAD_DATA* reload_data = (GAME_RELOAD_DATA*)game;
    OSThread* thread = &reload_data->thread;

    reload_data_check_stack(reload_data);
    if (reload_data_check_thread()) {
        OSReport("室内外データの読み込みが終了していないのにスレッドを止めた\n");
        osDestroyThread(thread);
    }

    if (reload_data->reset_pending) {
        SoftResetEnable = TRUE;
    }
}

static void reload_data_ReloadLink_module(void) {
    static s8 out_data[SCENE_NUM] = {
        2, // SCENE_TEST1
        2, // SCENE_TEST2
        2, // SCENE_TEST3
        2, // SCENE_WATER_TEST
        2, // SCENE_FOOTPRINT_TEST
        2, // SCENE_NPC_TEST
        1, // SCENE_NPC_HOUSE
        2, // SCENE_FG
        2, // SCENE_RANDOM_NPC_TEST
        1, // SCENE_SHOP0
        2, // SCENE_BG_TEST_NO_RIVER
        2, // SCENE_BG_TEST_RIVER
        1, // SCENE_BROKER_SHOP
        1, // SCENE_FIELD_TOOL_INSIDE
        1, // SCENE_POST_OFFICE
        1, // SCENE_START_DEMO
        1, // SCENE_START_DEMO2
        1, // SCENE_POLICE_BOX
        1, // SCENE_BUGGY
        0, // SCENE_PLAYERSELECT
        1, // SCENE_MY_ROOM_S
        1, // SCENE_MY_ROOM_M
        1, // SCENE_MY_ROOM_L
        1, // SCENE_CONVENI
        1, // SCENE_SUPER
        1, // SCENE_DEPART
        2, // SCENE_TEST5
        0, // SCENE_PLAYERSELECT_2
        0, // SCENE_PLAYERSELECT_3
        1, // SCENE_DEPART_2
        2, // SCENE_EVENT_ANNOUNCEMENT
        1, // SCENE_KAMAKURA
        2, // SCENE_FIELD_TOOL
        2, // SCENE_TITLE_DEMO
        0, // SCENE_PLAYERSELECT_SAVE
        1, // SCENE_MUSEUM_ENTRANCE
        1, // SCENE_MUSEUM_ROOM_PAINTING
        1, // SCENE_MUSEUM_ROOM_FOSSIL
        1, // SCENE_MUSEUM_ROOM_INSECT
        1, // SCENE_MUSEUM_ROOM_FISH
        1, // SCENE_MY_ROOM_LL1
        1, // SCENE_MY_ROOM_LL2
        1, // SCENE_MY_ROOM_BASEMENT_S
        1, // SCENE_MY_ROOM_BASEMENT_M
        1, // SCENE_MY_ROOM_BASEMENT_L
        1, // SCENE_MY_ROOM_BASEMENT_LL1
        1, // SCENE_NEEDLEWORK
        1, // SCENE_COTTAGE_MY
        1, // SCENE_COTTAGE_NPC
        1, // SCENE_START_DEMO3
        1, // SCENE_LIGHTHOUSE
        1, // SCENE_TENT
    };

    ReloadLink_module_IorO(out_data[Save_Get(scene_no)]);
}

static void reload_data_proc(void* param) {
    reload_data_ReloadLink_module();
}

static void reload_data_move_main(GAME_RELOAD_DATA* reload_data) {
    if (OSIsThreadTerminated(&reload_data->thread)) {
        GAME_GOTO_NEXT(&reload_data->game, play, PLAY);
    }
}

static void reload_data_draw_main(GAME_RELOAD_DATA* reload_data) {
    GRAPH* g = reload_data->game.graph;
    
    OPEN_DISP(g);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_0, 0); // why is this here?
    CLOSE_DISP(g);

    DisplayList_initialize(g, 0, 0, 0, NULL);
    game_debug_draw_last(&reload_data->game, g);
    game_draw_last(g);
}

static void reload_data_main(GAME* game) {
    GAME_RELOAD_DATA* reload_data = (GAME_RELOAD_DATA*)game;

    reload_data_check_stack(reload_data);
    reload_data_move_main(reload_data);
    reload_data_draw_main(reload_data);
}

extern void reload_data_init(GAME* game) {
    GAME_RELOAD_DATA* reload_data = (GAME_RELOAD_DATA*)game;
    OSThread* thread;
    u64* stack_base;

    game->exec = &reload_data_main;
    game->cleanup = &reload_data_cleanup;
    
    if (SoftResetEnable) {
        SoftResetEnable = FALSE;
        reload_data->reset_pending = TRUE;
    }

    thread = &reload_data->thread;
    reload_data->stack_preguard = RELOAD_DATA_STACK_MAGIC;
    reload_data->stack_postguard = RELOAD_DATA_STACK_MAGIC;

    // @BUG - The devs seem to cast the stack pointer to a u64* which causes
    // the stack base to be 8x farther than intended. This is a fairly critical bug.
#ifndef BUGFIXES
    stack_base = (u64*)reload_data->stack + RELOAD_DATA_STACK_SIZE;
#else
    stack_base = (u64*)(reload_data->stack + RELOAD_DATA_STACK_SIZE);
#endif
    osCreateThread2(thread, 14, &reload_data_proc, game, stack_base, RELOAD_DATA_STACK_SIZE, 5);
    osStartThread(thread);
}
