#include "m_play.h"

#include "m_common_data.h"
#include "libultra/libultra.h"
#include "m_fbdemo_wipe1.h"
#include "m_fbdemo_triforce.h"
#include "m_fbdemo_fade.h"
#include "m_debug.h"
#include "boot.h"
#include "version.h"
#include "m_bgm.h"
#include "m_rcp.h"
#include "m_msg.h"
#include "m_banti.h"
#include "m_event.h"
#include "m_npc.h"
#include "m_huusui_room.h"
#include "m_field_make.h"
#include "m_card.h"
#include "m_eappli.h"
#include "famicom_emu.h"
#include "Famicom/famicom.h"
#include "m_malloc.h"
#include "m_field_info.h"
#include "m_time.h"
#include "m_titledemo.h"
#include "sys_matrix.h"
#include "m_fuusen.h"
#include "m_watch_my_step.h"
#include "m_vibctl.h"
#include "m_train_control.h"
#include "gfxalloc.h"
#include "m_debug_display.h"
#include "jsyswrap.h"
#include "m_trademark.h"
#include "zurumode.h"
#include "m_scene_table.h"

u16 S_back_title_timer;
u16 S_se_endcheck_timeout;
fbdemo_c fbdemo;
u8 gxbuf[0x140] ATTRIBUTE_ALIGN(32);
u8 prbuf[0x12c000] ATTRIBUTE_ALIGN(32);

void Game_play_Reset_destiny(){
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    mPr_destiny_c* destiny = &Common_Get(now_private)->destiny;

    if (destiny->type == mPr_DESTINY_NORMAL) { 
        return;
    }
    
    if(
        (rtc_time->year != destiny->received_time.year) ||
        (rtc_time->month != destiny->received_time.month) ||
        (rtc_time->day != destiny->received_time.day)
    ) {

        Common_Set(now_private->destiny.type, mPr_DESTINY_NORMAL);
    }
}

void event_title_flag_on(){
    if(Common_Get(event_title_flags) != 0){
        Common_Set(event_notification_active,1);
    }
}

void event_title_flag_off(){

    if(Common_Get(event_title_flags) == 2){
        Common_Set(event_title_flags,0);
        Common_Set(event_notification_active,0);
         
    }
}

void Game_play_camera_proc(GAME_PLAY* play){

    Camera2_ClearActorTalking_Cull(play);
    Camera2_process(play);
}

void Game_play_fbdemo_wipe_destroy(GAME_PLAY* play){

    play->fbdemo_wipe.wipe_procs.cleanup_proc(&play->fbdemo_wipe.wipe_data);
    play->fb_wipe_mode = 0;
    play->fbdemo_wipe.wipe_type = -1;
} 

void Game_play_fbdemo_wipe_create_sub(GAME_PLAY* play){
    static void* wipe_normal_proc[] = {
        fbdemo_wipe1_init,
        none_proc1,
        fbdemo_wipe1_move,
        fbdemo_wipe1_draw,
        fbdemo_wipe1_startup,
        fbdemo_wipe1_settype,
        fbdemo_wipe1_setcolor_rgba8888,
        NULL,
        fbdemo_wipe1_is_finish,
    };
    static void* wipe_triforce_proc[] = {
        fbdemo_triforce_init,
        none_proc1,
        fbdemo_triforce_move,
        fbdemo_triforce_draw,
        fbdemo_triforce_startup,
        fbdemo_triforce_settype,
        fbdemo_triforce_setcolor_rgba8888,
        NULL,
        fbdemo_triforce_is_finish,
    };
    static void* wipe_fade_proc[] = {
        fbdemo_fade_init,
        none_proc1,
        fbdemo_fade_move,
        fbdemo_fade_draw,
        fbdemo_fade_startup,
        fbdemo_fade_settype,
        fbdemo_fade_setcolor_rgba8888,
        NULL,
        fbdemo_fade_is_finish,
    };

    static void* wipe_proc[] = {
        wipe_normal_proc,
        wipe_triforce_proc,
        wipe_fade_proc,
        wipe_fade_proc,
        wipe_triforce_proc,
        wipe_triforce_proc,
        wipe_fade_proc,
    };
    
    int type = play->fb_wipe_type;
    fbdemo_wipe_proc_c* cur;
    
    
    bzero(&play->fbdemo_wipe, sizeof(fbdemo_wipe));

    if(type >= 7){
        type = 1;
    }

    play->fbdemo_wipe.wipe_type = type;
    cur = wipe_proc[type];
    play->fbdemo_wipe.wipe_procs.init_proc = cur->init_proc;
    play->fbdemo_wipe.wipe_procs.cleanup_proc = cur->cleanup_proc;
    play->fbdemo_wipe.wipe_procs.move_proc = cur->move_proc;
    play->fbdemo_wipe.wipe_procs.draw_proc = cur->draw_proc;
    play->fbdemo_wipe.wipe_procs.startup_proc = cur->startup_proc; 
    play->fbdemo_wipe.wipe_procs.settype_proc = cur->settype_proc;
    play->fbdemo_wipe.wipe_procs.setcolor_proc = cur->setcolor_proc;
    play->fbdemo_wipe.wipe_procs.isfinished_proc = cur->isfinished_proc;
}

void Game_play_fbdemo_wipe_create(GAME_PLAY* play){

    Game_play_fbdemo_wipe_create_sub(play);
    Game_play_fbdemo_wipe_init(play);
}

void Game_play_fbdemo_wipe_init(GAME_PLAY* play){
    fbdemo_wipe* wipe =  &play->fbdemo_wipe;
    u8 type;
    
    play->fbdemo_wipe.wipe_procs.init_proc(&wipe->wipe_data);
    
    Common_Set(transition.wipe_rate, 28);
    Common_Set(transition.fade_rate, 30);

    wipe->wipe_procs.setcolor_proc(&wipe->wipe_data,0);

    type = play->fb_fade_type;
    
    if(wipe->wipe_type == 4){
        type |= 0x80;
    }
    else if(wipe->wipe_type == 5){
        type |= 0x40;
    }
    wipe->wipe_procs.settype_proc(&wipe->wipe_data, type);
    wipe->wipe_procs.startup_proc(&wipe->wipe_data);
    
    play->fb_wipe_mode = 3;

    S_back_title_timer = 120;
    S_se_endcheck_timeout = 120;
}

void Game_play_fbdemo_fade_in_move_end(GAME_PLAY* play){
    Game_play_fbdemo_wipe_destroy(play);

    if(play->fb_mode == 3){
        fbdemo_cleanup(&fbdemo); 
        play->fb_mode = 0;
        SetGameFrame(3);
    }
}

void Game_play_fbdemo_fade_out_start_emu_move_end(GAME_PLAY* play){

    GAME_GOTO_NEXT(&play->game, famicom_emu, FAMICOM_EMU);
    
}

void Game_play_fbdemo_fade_out_game_end_move_end(GAME_PLAY* play){

    GAME_GOTO_NEXT(&play->game, trademark, TRADEMARK);
}

void Game_play_change_scene_move_end(GAME_PLAY* play){

    game_goto_next_game_play(&play->game);
    Common_Set(last_scene_no, Save_Get(scene_no));
    Save_Set(scene_no,play->next_scene_no);
    
}

void Game_play_fbdemo_wipe_move(GAME_PLAY* play){
    fbdemo_wipe* wipe =  &play->fbdemo_wipe;
    s16 wipet = FALSE;
    int isDone = TRUE;

    if(wipe->wipe_procs.isfinished_proc(&wipe->wipe_data) != 0) {
        if((play->fb_fade_type != 1) && (play->fb_fade_type != 11)){
            if(S_se_endcheck_timeout != 0){
                S_se_endcheck_timeout--;
            }

            if((sAdo_SeFadeoutCheck() == 0) && (S_se_endcheck_timeout != 0)){
                isDone = FALSE;
            }
            else{
                sAdo_Set_ongenpos_refuse_fg(1);  
            }
        }
        if(play->fb_fade_type == 11){
            sAdo_Set_ongenpos_refuse_fg(2);
        }

        if(isDone == TRUE){
            switch(play->fb_fade_type){
                case 1:
                Game_play_fbdemo_fade_in_move_end(play);
                break;

                case 3:
                if(S_back_title_timer != 0){
                    S_back_title_timer--;
                }

                if((sAdo_BgmFadeoutCheck() == 1) || (S_back_title_timer == 0)){
                    Game_play_fbdemo_fade_out_start_emu_move_end(play);
                }
                else{
                    wipet = TRUE;
                }
                break;

                case 4:
                case 6:
                if(S_back_title_timer == 120){
                    mBGMPsComp_make_ps_wipe(360); 
                }
                case 5:
                case 10:
                if(S_back_title_timer != 0){
                    S_back_title_timer--;
                }

                if((sAdo_BgmFadeoutCheck() == 1) || (S_back_title_timer == 0)){
                    Game_play_fbdemo_fade_out_game_end_move_end(play);
                }
                else{
                    wipet = TRUE;
                }
                break;

                case 8:
                if(S_back_title_timer != 0){
                    S_back_title_timer--;
                }

                if((sAdo_BgmFadeoutCheck() == 1) || (S_back_title_timer == 0)){
                    if((Common_Get(clip.animal_logo_clip) != NULL) &&
                    (Common_Get(clip.animal_logo_clip->data_init_proc) != NULL)){                        
                        Common_Get(clip.animal_logo_clip->data_init_proc)(play);
                        Game_play_change_scene_move_end(play);
                    }
                }
                else{
                    wipet = TRUE;
                }
                break;
                
                case 9:
                if(S_back_title_timer != 0){
                    S_back_title_timer--;
                }

                if((sAdo_BgmFadeoutCheck() == 1) || (S_back_title_timer == 0)){
                    Game_play_change_scene_move_end(play);
                }
                else{
                    wipet = TRUE;
                }
                break;

                case 11:
                case 12:
                Game_play_change_scene_move_end(play);
                break;

                
                default:
                if(S_back_title_timer != 0){
                    S_back_title_timer--;
                }

                if((sAdo_BgmFadeoutCheck() == 1) || (S_back_title_timer == 0)){
                    Game_play_change_scene_move_end(play);
                }
                else{
                    wipet = TRUE;
                }
                break;
            }
            if(!wipet){
                play->fb_fade_type = 0;
            }
        }
    }
    else {
        wipe->wipe_procs.move_proc(&wipe->wipe_data, game_GameFrame); 
    }
}


void Game_play_fbdemo_wipe_proc(GAME_PLAY* play){
    static PLAY_WIPE_PROC wipe_proc[] = {
    (PLAY_WIPE_PROC)none_proc1,Game_play_fbdemo_wipe_create,
    Game_play_fbdemo_wipe_init,Game_play_fbdemo_wipe_move
    };
     
    if((play->fb_wipe_mode == 0) && (play->fb_fade_type != 0)){
        play->fb_wipe_mode = 1;
    }

    wipe_proc[play->fb_wipe_mode](play);
}

Gfx* game_play_set_fog(GAME_PLAY* play, Gfx* gfx){

    return gfx_set_fog_nosync(gfx, play->global_light.fogColor[0], play->global_light.fogColor[1],
        play->global_light.fogColor[2], 0, play->global_light.fogNear, play->global_light.fogFar);
}

void Game_play_fbdemo_proc(GAME_PLAY* play){

    switch(play->fb_mode){
        case 2:
        if(fbdemo_init(&fbdemo, 10, 7) == 0){
            play->fb_mode = 0;
        }
        else{
            play->fb_mode = 3;
            SetGameFrame(1);
        }
        break;

        case 3:
        fbdemo_move(&fbdemo);
        break;
    }
}

void play_cleanup(GAME* game){
    GAME_PLAY* play = (GAME_PLAY*)game;

    mMsg_dt(play);
    banti_dt();
    
    play->game.graph->taskEndCallback = NULL;
    play->game.graph->taskEndData = NULL;
    play->submenu.mode = 0;
    
    PreRender_cleanup(&play->prerender);
    CollisionCheck_dt(&play->game, &play->collision_check);
    
    if(play->fb_mode == 3){
        fbdemo_cleanup(&fbdemo);
        play->fb_mode = 0;
    }
    
    if(play->fb_wipe_mode == 3){
        Game_play_fbdemo_wipe_destroy(play);
    }

    Actor_info_dt(&play->actor_info, play);
    mEv_finish(&play->event);
    mNpc_ClearEventNpc();
    mNpc_ClearMaskNpc();
    
    mSM_submenu_dt(&play->submenu);
    play->submenu_ground_idx = -1;
    mSM_submenu_ovlptr_cleanup(&play->submenu);

    mPlib_Object_Exchange_keep_Player_dt(play);

    mHsRm_GetHuusuiRoom(NULL, Common_Get(player_no));
    mFM_Field_dt();
    mCD_toNextLand();
    mEA_CleanCardDLProgram();

    if(my_malloc_current == my_malloc_func){
        my_malloc_current = NULL;
    }

    zelda_CleanupArena();
    
} 

void VR_Box_ct(GAME_PLAY* play){
    
    Global_kankyo_ct(play, &play->kankyo);
}

void play_init(GAME* game){
    GAME_PLAY* play = (GAME_PLAY*)game;

    GRAPH* graph = play->game.graph;
    int type;
    fbdemo_fade* fade;
    int freebytes;
    u32 alloc;
    u32 aligned;
    u32 size;

    game_resize_hyral(&play->game, 0xFFFC1800);
    Common_Set(rhythym_updated,0);
    
    mFI_ChangeClimate_ForEventNotice();
    mTM_time_init(); 
    sAdo_Set_ongenpos_refuse_fg(0);
    event_title_flag_on();
    mTD_rtc_set();
    mTM_set_season();
    mPlib_Clear_controller_data_for_title_demo();

    mSM_submenu_ovlptr_init(play);
    mDemo_Init(play);
    mEv_init(&play->event);

    initView(&play->view, graph);
    Init_Camera2(play);
    CollisionCheck_ct(&play->game, &play->collision_check);
    
    mCoBG_InitMoveBgData();
    mCoBG_InitBlockBgCheckMode();
    mCoBG_InitDecalCircle();

    play->submenu_ground_idx = -1;
    
    Gameplay_Scene_Read(play, Save_Get(scene_no));

    mSM_submenu_ct(&play->submenu);
    play->submenu.mode = 0; 

    PreRender_init(&play->prerender);
    PreRender_setup_savebuf(&play->prerender, SCREEN_WIDTH * 2 ,SCREEN_HEIGHT * 2, 0, 0, 0 );
    PreRender_setup_renderbuf(&play->prerender, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, 0,0);

    play->fb_mode = 0;
    type = 1;

    play->fb_wipe_mode = 0;
    play->fb_fade_type = 1;
    
    if(Common_Get(transition.wipe_type) != 0xFF){
        type = Common_Get(transition.wipe_type);
        Common_Set(transition.wipe_type, 0xFF); 
    }

    play->fb_wipe_type = type;
    
    Pause_ct(&play->pause);
    new_Matrix(&play->game);

    fade = &play->color_fade;

    play->game.exec = play_main;
    play->game.cleanup = play_cleanup;
    fbdemo_fade_init(fade);  
    fbdemo_fade_settype(fade, 7);
    fbdemo_fade_setcolor_rgba8888(fade, 0xA0A0A0FF);
    fbdemo_fade_startup(fade);

    play->fade_color_value.rgba8888 = 0;
    
    freebytes = game_getFreeBytes(&play->game);
    alloc = (u32)THA_alloc16(&play->game.tha, freebytes);
    aligned = ALIGN_NEXT(alloc, 16);
    size = aligned - alloc;

    zelda_InitArena((void*)aligned, freebytes - size);

    if(my_malloc_current == NULL){
        my_malloc_current = my_malloc_func;
    }

    mFM_FieldInit(play);
    VR_Box_ct(play);
    mMmd_MakeMuseumDisplayData();
    Actor_info_ct(&play->game, &play->actor_info, play->player_data);
    play->draw_chk_proc = none_proc1;
    mMsg_ct(play);
    mEv_2nd_init(&play->event);
    mTD_player_keydata_init(play); 
    Balloon_init(play);
    mNtc_set_auto_nwrite_data();
    banti_ct();
    watch_my_step_ct();
    event_title_flag_off();
    mEA_GetCardDLProgram();    
}

void Game_play_move_fbdemo_not_move(GAME_PLAY* play){

    play->game.doing_point = 0;
    play->game.doing_point_specific = 0x8F;
    play->game.doing_point = 1;

    mSM_submenu_ctrl(play);

    if(play->submenu.process_status == 0){

        play->game.doing_point = 2;
        mDemo_Main(play);
        play->game.doing_point = 3;
        mEv_run(&play->event);
    }

    play->game.doing_point = 4;
    mDemo_stock_clear();
    play->game.doing_point = 5;
    mSc_dmacopy_data_bank(&play->object_exchange);
    play->game.doing_point = 6;
    mSM_submenu_move(&play->submenu);
    
    if(play->submenu.process_status == 0){

        play->game_frame++;
        mVibctl_clr_force_stop(2);
        play->game.doing_point = 7;
        CollisionCheck_OC(&play->game, &play->collision_check);
        play->game.doing_point = 8;
        CollisionCheck_clear(&play->game, &play->collision_check);
        play->game.doing_point = 9;
        play->game.doing_point = 0;
        play->game.doing_point_specific = 0x90;
        Actor_info_call_actor(play, &play->actor_info);
        play->game.doing_point = 0;
        play->game.doing_point_specific = 0x91;
        play->game.doing_point = 1;
        mCoBG_CalcTimerDecalCircle();
        play->game.doing_point = 2;
        mMsg_Main(play);
    }
    else{
        mVibctl_set_force_stop(2);
    }
    
    fbdemo_fade_move(&play->color_fade, game_GameFrame);
    
}

void Game_play_move(GAME_PLAY* play){

    int debug;

    play->game.doing_point = 0;
    play->game.doing_point_specific = 0x8D;
    play->game.doing_point = 1;
    Game_play_Reset_destiny();
    play->game.doing_point = 2;

    debug = (zurumode_flag >= 2) ? (Pause_proc(&play->pause, &play->game.pads[1]) == 0) : 0;

    play->game.doing_point = 0;
    play->game.doing_point_specific = 0x8E;

    if(debug == 0){

        play->game.doing_point = 1;
        Game_play_fbdemo_wipe_proc(play);
        play->game.doing_point = 2;
        Game_play_fbdemo_proc(play);
        play->game.doing_point = 3;

        if(play->fb_mode != 3){
            Game_play_move_fbdemo_not_move(play);
        }
    }

    if(play->submenu.process_status == 0){

        play->game.doing_point = 0;
        play->game.doing_point_specific = 0x92;
        play->game.doing_point = 1;
        Game_play_camera_proc(play);
        play->game.doing_point = 2;
        mPO_business_proc(play);
        play->game.doing_point = 3;
        mTRC_move(play);
        play->game.doing_point = 4;
        Balloon_move(play);
        mEnv_ManagePointLight(play, &play->kankyo, &play->global_light);

    }

    play->game.doing_point = 0;
    play->game.doing_point_specific = 0x93;
    play->game.doing_point = 1;
    Global_kankyo_set(play, &play->kankyo, &play->global_light);
    play->game.doing_point = 2;
    mEnv_WindMove();
    play->game.doing_point = 3;
    watch_my_step_move(play);
    play->game.doing_point = 4;
    banti_move(play);
    play->game.doing_point = 5;
    title_demo_move(play);
    play->game.doing_point = 0;
    play->game.doing_point_specific = 0x95;

}


void setupFog(GAME_PLAY* play, GRAPH* graph){

    OPEN_DISP(graph);

    SET_POLY_OPA_DISP(game_play_set_fog(play, NOW_POLY_OPA_DISP)); 
    SET_POLY_XLU_DISP(game_play_set_fog(play, NOW_POLY_XLU_DISP));  
    

    CLOSE_DISP(graph);
}

void setupViewer(GAME_PLAY* play) {
    
    showView(&play->view, 0xF); 
}

void setupViewMatrix(GAME_PLAY* play, GRAPH* graph1, GRAPH* graph2){
    Mtx* t;
 
    OPEN_DISP(graph1);

    
    Matrix_MtxtoMtxF(&play->view.mtx_viewing, &play->billboard_matrix);
    Matrix_MtxtoMtxF(&play->view.mtx_projection, &play->projection_matrix); 
    Skin_Matrix_MulMatrix(&play->projection_matrix, &play->billboard_matrix, &play->projection_matrix);

    play->billboard_matrix.mf[0][3] = 0.0f;
    play->billboard_matrix.mf[1][3] = 0.0f;
    play->billboard_matrix.mf[2][3] = 0.0f;
    play->billboard_matrix.mf[3][0] = 0.0f;
    play->billboard_matrix.mf[3][1] = 0.0f; 
    play->billboard_matrix.mf[3][2] = 0.0f;
 
    Matrix_reverse(&play->billboard_matrix);

    t = _MtxF_to_Mtx(&play->billboard_matrix, GRAPH_ALLOC(graph2, sizeof(MtxF) * 1));
    play->_208C = t; 

    gSPSegment(NEXT_BG_OPA_DISP, 7, play->_208C);
    gSPSegment(NEXT_POLY_OPA_DISP, 7, play->_208C);
    
    
    CLOSE_DISP(graph1); 
} 
 
 void copy_efb_to_texture(Gfx** graph, void* buf){
     u32 dl;
     
     GXBeginDisplayList(gxbuf, sizeof(gxbuf));
     GXSetTexCopySrc(0,0,SCREEN_WIDTH * 2,SCREEN_HEIGHT * 2); 
     GXSetTexCopyDst(SCREEN_WIDTH * 2, SCREEN_HEIGHT *2, GX_TF_RGB565, 0);
     GXSetCopyFilter(0,0,0,0);
     GXCopyTex(buf, 0);
     dl = GXEndDisplayList();
     gGXCallDisplayList((*graph)++, gxbuf ,dl); 
 }

int makeBumpTexture(GAME_PLAY* play, GRAPH* graph1, GRAPH* graph2){

    Gfx* newdisp;
    Gfx* polydisp;
    Gfx* rect_disp;
    View* v;
    Gfx* fbdemo_disp;
    Gfx* fb_disp;
    Gfx* old_fb;
    Gfx* poly;
    View view;
    rect rect;
 
    OPEN_DISP(graph1);

    if((GETREG(HREG, 80) != 10) || (GETREG(HREG, 92) != 0)){
 
        newdisp = NOW_POLY_OPA_DISP;
        polydisp = gfxopen(newdisp);
        
        gSPDisplayList(NEXT_OVERLAY_DISP, polydisp);

        if(play->fb_wipe_mode == 3){
            v = &view;
            initView(v, graph2);
            v->flag = 10;
            rect.top = 0;
            rect.bottom = SCREEN_HEIGHT;
            rect.l = 0;
            rect.r = SCREEN_WIDTH;
            setScissorView(v, &rect);
            showView1(v, 15, &polydisp); 
            play->fbdemo_wipe.wipe_procs.draw_proc(&play->fbdemo_wipe.wipe_data, &polydisp);
        }

        fbdemo_fade_draw(&play->color_fade, &polydisp);
        fade_rgba8888_draw(&polydisp, play->fade_color_value.rgba8888);  
        
        gSPEndDisplayList(polydisp++);

        gfxclose(newdisp, polydisp);

        SET_POLY_OPA_DISP(polydisp);
    }

    if(play->fb_mode == 3){
        fbdemo_disp = NOW_POLY_OPA_DISP;
        fbdemo_draw(&fbdemo, &fbdemo_disp);
        SET_POLY_OPA_DISP(fbdemo_disp);
        return 1;
    }

    if(play->submenu.mode == 2){
        play->submenu.mode = 3;
        SETREG(SREG, 3, -(GETREG(SREG, 3)));
    }
    else if(play->submenu.mode >= 5){
        play->submenu.mode = 0;
    }
    
    if(play->submenu.mode == 3){ 
        poly = NOW_POLY_OPA_DISP;
        
        gDPPipeSync(poly++); 
        rect_disp = gfx_rect_moji(poly++);
        gDPSetOtherMode(rect_disp++, G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_CONV | G_TF_POINT | 
            G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_COPY | G_PM_NPRIMITIVE, 
            G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2);
        gDPSetTextureImage_Dolphin(rect_disp++, G_IM_FMT_I, G_IM_SIZ_16b, 480, 640, prbuf);
        gDPSetTile_Dolphin(rect_disp++, G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, 0, 0, 0, 0);
        gSPTextureRectangle(rect_disp++, 0, 0, (640-1) << 2, (480-1) << 2, G_TX_RENDERTILE, 0, 0, (256) << 2, (256) << 2);

        SET_POLY_OPA_DISP(rect_disp); 
        return 1;
    }

    if((GETREG(HREG, 80) != 10) || (GETREG(HREG, 85) != 0)){
        Actor_info_draw_actor(play, &play->actor_info);
        Camera2_draw(play);
        mMsg_Draw(play);
    }

    if((GETREG(HREG, 80) != 10) || (GETREG(HREG, 93) != 0)){
        Debug_Display_output(play); 
    }

    if((play->submenu.mode == 1) || (play->fb_mode == 1)){

        old_fb = NOW_POLY_OPA_DISP;
        fb_disp = gfxopen(old_fb);

        gSPDisplayList(NEXT_LIGHT_DISP, fb_disp);
        copy_efb_to_texture(&fb_disp, &prbuf);
        gSPEndDisplayList(fb_disp++);

        gfxclose(old_fb, fb_disp);

        SET_POLY_OPA_DISP(fb_disp);

        if(play->submenu.mode == 1){
            play->submenu.mode = 2;
            SETREG(SREG, 3, -(GETREG(SREG, 3)));
        }
        else {
            play->fb_mode = 2;
        }
        return 1;
    }
    return 1;
    CLOSE_DISP(graph1);
}

void draw_version(GRAPH* graph) {
    JW_JUTReport(0x82, 0x172, 1, "[CopyDate:%.19s]", boot_copyDate);
    JW_JUTReport(0x82, 0x180, 1, "[Date:%s]" , &__DateTime__);
    JW_JUTReport(0x82, 0x18E, 1, "[Creator:%s]", &__Creator__);
}

void Game_play_draw(GAME* game){
    GRAPH* graph = game->graph;
    GAME_PLAY* play = (GAME_PLAY*)game;

    
    DisplayList_initialize(graph, 0,0,0,&play->game);  

    if((GETREG(HREG, 80) != 10) || (GETREG(HREG, 82) != 0)){ 
    
        setupFog(play, graph);
        setupViewer(play);
        setupViewMatrix(play, graph, graph);

        if((makeBumpTexture(play, graph, graph) == 1) && ((GETREG(HREG, 80) != 10) || (GETREG(HREG, 89) != 0))){

            watch_my_step_draw(play); 
            banti_draw(play); 
            mSM_submenu_draw(&play->submenu, (GAME*)play);
        }
    }
    if (zurumode_flag != 0) {
        switch (mEv_CheckTitleDemo()) {
            case -9:
            case -1:
            default:
                draw_version(graph);
                break;

            case 0:
                break;
        }
    }
}

void play_main(GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    GRAPH* graph;

    game->doing_point = 0;
    game->doing_point_specific = 0x6E;
    fqrand(); 
    game->doing_point = 0;
    game->doing_point_specific = 0x78;
    mCon_main(game);
    game->doing_point = 0;
    game->doing_point_specific = 0x82; 
    Debug_Display_init();

    if((GETREG(HREG, 80) == 10) && (GETREG(HREG, 94) != 10)){ 
        SETREG(HREG, 81,1);
        SETREG(HREG, 82,1);
        SETREG(HREG, 83,1);
        SETREG(HREG, 84,3);
        SETREG(HREG, 85,1);
        SETREG(HREG, 86,1);
        SETREG(HREG, 87,1);
        SETREG(HREG, 88,1);
        SETREG(HREG, 89,1);
        SETREG(HREG, 90,15);
        SETREG(HREG, 91,1);
        SETREG(HREG, 92,1);
        SETREG(HREG, 93,1);
        SETREG(HREG, 94,10);

    }
    
    game->doing_point = 0;
    game->doing_point_specific = 0x8C;
    
    if((GETREG(HREG, 80) != 10) || (GETREG(HREG, 81) != 0)){
        Game_play_move(play); 
    }
    game->doing_point = 0;
    game->doing_point_specific = 0xAA;
    Game_play_draw(game);
    
    game->doing_point = 0;
    game->doing_point_specific = 0xB4;
    
    graph = game->graph;
    game_debug_draw_last(game, graph);
    game_draw_last(graph);
    
    game->doing_point = 0;
    game->doing_point_specific = 0XBe;
}

void Gameplay_Scene_Init(GAME_PLAY* play){

    play->player_data = NULL;
    play->actor_data_num = 0;
    play->ctrl_actor_data_num = 0;
    play->obj_bank_data_num = 0;
    play->_20A8 = 0;
    
    mSc_data_bank_ct(play, &play->object_exchange);
    Global_light_ct(&play->global_light);
    Door_info_ct(&play->door_info);
    common_data_clear();
    Scene_ct(play, play->current_scene_data);
    mSc_decide_exchange_bank(&play->object_exchange);
    
}

u8 mPl_SceneNo2SoundRoomType(int scene) {
    switch (scene) {
        case SCENE_MY_ROOM_S:
            return 1;

        case SCENE_NPC_HOUSE:
        case SCENE_SHOP0:
        case SCENE_BROKER_SHOP:
        case SCENE_POST_OFFICE:
        case SCENE_BUGGY:
        case SCENE_MY_ROOM_M:
        case SCENE_KAMAKURA:
        case SCENE_MY_ROOM_LL2:
        case SCENE_TENT:
            return 2;

        case SCENE_MY_ROOM_L:
        case SCENE_CONVENI:
        case SCENE_SUPER:
        case SCENE_DEPART:
        case SCENE_DEPART_2:
        case SCENE_MY_ROOM_LL1:
        case SCENE_COTTAGE_MY:
        case SCENE_POLICE_BOX:
            return 3;

        default:
            return 0;
    } 
}

void Gameplay_Scene_Read(GAME_PLAY* play, s16 idx){
    static Scene_Word_u* scene_word_data[SCENE_NUM] = {
       test01_info,
       test02_info,
       test03_info,
       water_test_info,
       test_step01_info,
       test04_info,
       npc_room01_info,
       test_fd_npc_land_info,
       field_tool_field_info,
       shop01_info,
       BG_TEST01_info,
       BG_TEST01_XLU_info,
       broker_shop_info,
       fg_tool_in_info,
       post_office_info,
       start_demo1_info,
       start_demo2_info,
       police_box_info,
       buggy_info,
       player_select_info,
       player_room_s_info,
       player_room_m_info,
       player_room_l_info,
       shop02_info,
       shop03_info,
       shop04_1f_info,
       test05_info,
       PLAYER_SELECT2_info,
       PLAYER_SELECT3_info,
       shop04_2f_info,
       event_notification_info,
       kamakura_info,
       field_tool_field_info,
       title_demo_info,
       PLAYER_SELECT4_info,
       museum_entrance_info,
       museum_picture_info,
       museum_fossil_info,
       museum_insect_info,
       museum_fish_info,
       player_room_ll1_info,
       player_room_ll2_info,
       p_room_bm_s_info,
       p_room_bm_m_info,
       p_room_bm_l_info,
       p_room_bm_ll1_info,
       NEEDLEWORK_info,
       player_room_island_info,
       npc_room_island_info,
       start_demo3_info,
       lighthouse_info,
       tent_info,
    };

    Scene_data_status_c* current = &scene_data_status[idx];
    
    current->unk13 = 0; 
    play->scene_data_status = current;
    play->scene_id = idx;
    play->current_scene_data = scene_word_data[idx];
    current->unk13 = 0; 
    Gameplay_Scene_Init(play);
    sAdo_RoomType(mPl_SceneNo2SoundRoomType(Save_Get(scene_no)));
    
}