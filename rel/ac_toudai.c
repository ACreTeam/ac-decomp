#include "ac_toudai.h"

#include "m_name_table.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "bg_item.h"
#include "m_player_lib.h"
#include "m_common_data.h"
#include "m_bgm.h"


static void aTOU_actor_ct(ACTOR*, GAME*);
static void aTOU_actor_dt(ACTOR*, GAME*);
static void aTOU_actor_init(ACTOR*, GAME*);
static void aTOU_actor_draw(ACTOR*, GAME*);

ACTOR_PROFILE Toudai_Profile = {
    mAc_PROFILE_TOUDAI,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    TOUDAI,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(TOUDAI_ACTOR),
    aTOU_actor_ct,
    aTOU_actor_dt,
    aTOU_actor_init,
    aTOU_actor_draw,
    NULL,
};

extern Vtx obj_s_toudai_shadow_v[];
extern Gfx obj_s_toudai_shadow_1_model[];

u8 aTOU_shadow_vtx_fix_flg_table[] = {1,0,1,0,
                                      0,1,1,0,
                                      1,0,0,0,};
bIT_ShadowData_c aTOU_shadow_data = {
    10,
    aTOU_shadow_vtx_fix_flg_table,
    60.0f,
    obj_s_toudai_shadow_v,
    obj_s_toudai_shadow_1_model,
};


static void aTOU_set_bgOffset(TOUDAI_ACTOR*, int);
static void aTOU_setup_action(ACTOR*, int);

static void aTOU_fgunit_on(ACTOR* actor){
    TOUDAI_ACTOR* light = (TOUDAI_ACTOR*)actor;

    xyz_t pos;
    int i;
    mActor_name_t* nameptr;
    
    xyz_t_move(&pos, &light->actor_class.home.position); 

    pos.x -= 40.0f;
    pos.z -= 80.0f;
    for(i = 0; i < 2; i++){
        nameptr = mFI_GetUnitFG(pos);
        if(nameptr != NULL){
            if(mSN_ClearSnowman(nameptr) == 0){
                if (((*nameptr >= 0x2A) && (*nameptr <= 0x42)) || (*nameptr == 0x5C)) {
                    mPB_keep_item(bg_item_fg_sub_dig2take_conv(*nameptr));
                    mFI_SetFG_common(RSV_NO, pos, 1);
                    mFI_Wpos2DepositOFF(pos);
                }
                else{
                    mFI_Wpos2DepositOFF(pos);
                    mPB_keep_item(*nameptr);
                    mFI_SetFG_common(RSV_NO, pos, 1);
                }
            }
            else{
                mFI_SetFG_common(RSV_NO, pos, 1);
            }
        }
        pos.x += 40.0f;
    }
}

static void aTOU_fgunit_off(ACTOR* actor){
    TOUDAI_ACTOR* light = (TOUDAI_ACTOR*)actor;

    int i;
    xyz_t pos;
    
    xyz_t_move(&pos, &light->actor_class.home.position); 

    pos.x -= 40.0f;
    pos.z -= 80.0f;
    for (i = 0; i < 2; i++){
        mFI_SetFG_common(EMPTY_NO, pos, 1);
        pos.x += 40.0f;
    }
}

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_toudai;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_toudai;
 
static void aTOU_actor_ct(ACTOR* actor, GAME* game){
    static cKF_Skeleton_R_c* skl[] = {&cKF_bs_r_obj_s_toudai, &cKF_bs_r_obj_w_toudai};
    TOUDAI_ACTOR* light = (TOUDAI_ACTOR*)actor;

    light->season = Common_Get(time.season);
    cKF_SkeletonInfo_R_ct(&light->keyframe, skl[light->season == mTM_SEASON_WINTER], NULL, light->work, light->target);
    aTOU_set_bgOffset(light, 1);
    aTOU_fgunit_on(actor);
    aTOU_setup_action(actor, 0);
    cKF_SkeletonInfo_R_play(&light->keyframe);
    actor->world.position.x -= 20.0f;
    actor->world.position.z -= 20.0f;
}

static void aTOU_actor_dt(ACTOR* actor, GAME* game){
    TOUDAI_ACTOR* light = (TOUDAI_ACTOR*)actor;
    
    aTOU_fgunit_off(&light->actor_class);
    cKF_SkeletonInfo_R_dt(&light->keyframe);
    light->actor_class.world.position.x += 20.0f;
    light->actor_class.world.position.z += 20.0f;

}

static void aTOU_rewrite_door(ACTOR* actor, GAME_PLAY* play){
    TOUDAI_ACTOR* light = (TOUDAI_ACTOR*)actor;
    
    xyz_t pos;
    Door_data_c* door_data = Common_GetPointer(structure_exit_door_data);

    if(play->fb_wipe_mode == 0){
        door_data->next_scene_id = Save_Get(scene_no);
        door_data->exit_orientation = 4;
        door_data->exit_type = 0;
        door_data->extra_data = 3;

        pos.x = light->actor_class.world.position.x;
        pos.z = light->actor_class.world.position.z - 70.0f;
        pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(pos, 0.0f);
        door_data->exit_position.x = pos.x;
        door_data->exit_position.y = pos.y;
        door_data->exit_position.z = pos.z;
        door_data->door_actor_name = light->actor_class.npc_id;
        door_data->wipe_type = 1;
        mBGMPsComp_make_ps_wipe(0x2168);
    }
}

static int aTOU_check_door_pos(ACTOR* actor, GAME_PLAY* play){
    TOUDAI_ACTOR* light = (TOUDAI_ACTOR*)actor;

    PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);
    f32 diff;

    if(player != NULL){ 
        diff = (player->actor_class.world.position.z - light->actor_class.world.position.z);
        if(fabsf(player->actor_class.world.position.x - light->actor_class.world.position.x) < 20.0f && 
            diff > -65.0f && diff < 0.0f){
            if((player->actor_class.shape_info.rotation.y > -0x2000) && 
                (player->actor_class.shape_info.rotation.y < 0x2000)){
                return 1;     
            }
        } 
    }

    return 0;
}

Door_data_c aTOU_door_data = {
    SCENE_LIGHTHOUSE,
    0,
    FALSE,
    0,
    {120,0,100},
    EMPTY_NO,
    1,
    {0,0,0},
};

static void aTOU_set_bgOffset(TOUDAI_ACTOR* light, int idx){
    static mCoBG_OffsetTable_c height_table_ct[] = { { 0x64, 16, 16, 16, 16, 16, 0 },
                                            { 0x64, 16, 16, 16, 16, 16, 0 },
                                            { 0x64, 16, 16, 16, 16, 16, 0 },
                                            { 0x64, 16, 16, 16, 16, 16, 0 } };
    static mCoBG_OffsetTable_c* height_table[] = { height_table_ct, height_table_ct };
    static f32 addX[] = { -40.0f, 0.0f };
    static f32 addZ[] = { -40.0f, 0.0f }; 
    
    mCoBG_OffsetTable_c* offset;
    int i;
    xyz_t pos;

    offset  = height_table[idx]; 

    for(i = 0; i < 2; i++){
        pos.z = light->actor_class.home.position.z + addZ[i];
        pos.x = light->actor_class.home.position.x + addX[0];
        mCoBG_SetPluss5PointOffset_file(pos, *offset, "ac_toudai_move.c_inc", 184);
        offset++;
        pos.x = light->actor_class.home.position.x + addX[1];
        mCoBG_SetPluss5PointOffset_file(pos, *offset, "ac_toudai_move.c_inc", 188);
        offset++;
    }
}

static void aTOU_color_ctrl(TOUDAI_ACTOR* light) {
    f32 factor;
    int timer;

    if (light->ready_flag == 0) {
        add_calc(&light->unk2C8, 0.0f, 1.0f - sqrtf(0.7), 50.0f, 0.5f);
        add_calc(&light->unk2CC, 0.0f, 1.0f - sqrtf(0.7), 50.0f,  0.5f);
        add_calc(&light->unk2D0, 0.0f, 1.0f - sqrtf(0.9), 50.0f,  0.5f);
        return;
    }

    timer = light->current_frame - 51;
    factor = (timer < 0) ? 1.0f : -1.0f;
    timer = ABS(timer);

    if (timer == 0) {
        light->unk2C8 = 220.0f;
        light->unk2CC = 240.0f;

    } else if (timer >= 40) {
        add_calc(&light->unk2C8, 0.0f, 1.0f - sqrtf(0.7), 50.0f, 0.5f);
        add_calc(&light->unk2CC, 0.0f, 1.0f - sqrtf(0.7), 50.0f, 0.5f);

    } else if (timer < 10) {
        light->unk2C8 += (4.5f * factor);
        light->unk2CC += (7.0f * factor);

    } else if (timer < 30) {
        light->unk2C8 += (1.25f * factor);
        light->unk2CC += (2.25f * factor);

    } else {
        light->unk2C8 += (4.0f * factor);
        light->unk2CC += (0.5f * factor);
    }

    add_calc(&light->unk2D0, 255.0f, 1.0f - sqrtf(0.9), 50.0f, 0.5f);
}

static void aTOU_init(ACTOR* actor, GAME_PLAY* play){
    aTOU_setup_action(actor, 1);
}

static void aTOU_wait(ACTOR* actor, GAME_PLAY* play){
    TOUDAI_ACTOR* light = (TOUDAI_ACTOR*)actor;
    int sec = Common_Get(time.now_sec);
    
    if(mSC_LightHouse_Switch_Check() != 0 && (sec >= 64800 || sec < 18000)){
            light->keyframe.frame_control.speed = 0.5f;
            light->ready_flag = TRUE; 
            aTOU_setup_action(actor, 2);
        }
}
 
static void aTOU_lighting(ACTOR* actor, GAME_PLAY* play){
    TOUDAI_ACTOR* light = (TOUDAI_ACTOR*)actor;
    int sec = Common_Get(time.now_sec);
    
    if((mSC_LightHouse_Switch_Check() == 0) || ((sec < 64800) 
        && (sec >= 18000))){   
            aTOU_setup_action(actor, 3);
        }
}

static void aTOU_lightout(ACTOR* actor, GAME_PLAY* play){
    TOUDAI_ACTOR* light = (TOUDAI_ACTOR*)actor; 

    if(light->current_frame == 0x33){
            light->keyframe.frame_control.speed = 0.0f;
            light->ready_flag = 0; 
            aTOU_setup_action(actor, 1);
        }
}

extern cKF_Animation_R_c cKF_ba_r_obj_s_toudai;
extern cKF_Animation_R_c cKF_ba_r_obj_w_toudai;

static void aTOU_setup_action(ACTOR* actor, int action) {
    TOUDAI_ACTOR* light = (TOUDAI_ACTOR*)actor; 
    static cKF_Animation_R_c* ani[] = { &cKF_ba_r_obj_s_toudai, &cKF_ba_r_obj_w_toudai };
    static TOUDAI_PROC process[] = { aTOU_init, aTOU_wait, aTOU_lighting, aTOU_lightout };

    int type;
    
    if(action == 0){
        type = light->season == mTM_SEASON_WINTER;
        cKF_SkeletonInfo_R_init(&light->keyframe, light->keyframe.skeleton, ani[type], 
            1.0f, 100.0f, 51.0f, 0.0f, 0.0f, cKF_FRAMECONTROL_REPEAT, NULL);
    }

    light->proc = process[action];
    light->current_proc = action;
}

static void aTOU_actor_move(ACTOR* actor, GAME* game){
    GAME_PLAY* play = (GAME_PLAY*)game;
    TOUDAI_ACTOR* light = (TOUDAI_ACTOR*)actor; 

    light->keyframe_state = cKF_SkeletonInfo_R_play(&light->keyframe);
    light->current_frame = light->keyframe.frame_control.current_frame;

    if(get_player_actor_withoutCheck((GAME_PLAY*)gamePT)->get_door_label_proc(gamePT) == light){
        aTOU_rewrite_door(&light->actor_class, play);
        goto_other_scene(play, &aTOU_door_data, 0);
    }
    else{
        light->proc(actor,play);

        if((mSC_LightHouse_In_Check() != 0) && (aTOU_check_door_pos(actor,play) != 0)){
            xyz_t pos;
            pos.x = light->actor_class.world.position.x;
            pos.y = light->actor_class.world.position.y;
            pos.z = light->actor_class.world.position.z - 60.0f;
            mPlib_request_main_door_type1(play, &pos, 0, 1, light); 
        }
    } 
    aTOU_color_ctrl(light); 
}

static void aTOU_actor_init(ACTOR* actor, GAME* game){
    TOUDAI_ACTOR* light = (TOUDAI_ACTOR*)actor; 
    
    mFI_SetFG_common(0xF11E, light->actor_class.home.position, 0);
    aTOU_actor_move(actor, game);
    light->actor_class.mv_proc = aTOU_actor_move;
}

static int aTOU_actor_draw_before(GAME*,cKF_SkeletonInfo_R_c*, int idx, Gfx** gfxp,u8* dispbuf, void* actor, s_xyz* rotation, xyz_t* translation){

    if(idx == 4){
        *gfxp = NULL;
    }

    return 1;
}

extern Gfx obj_s_toudai_light_model[];
extern Gfx obj_w_toudai_light_model[];

static int aTOU_actor_draw_after(GAME* game,cKF_SkeletonInfo_R_c* info, int idx, Gfx** gfxp,
u8* dispbuf, void* actor, s_xyz* rotation, xyz_t* translation){
    static Gfx* mdl[] = {obj_s_toudai_light_model, obj_w_toudai_light_model};
    static rgba_t prmcol = {255,255,150,120};
    TOUDAI_ACTOR* light = (TOUDAI_ACTOR*)actor; 
    
    GRAPH* graph = game->graph;
    Mtx* work;
    u16* pal;
    Gfx* gfx; 
    int type;

    if((idx == 4) && ((int)light->unk2CC != 0)){
        work = _Matrix_to_Mtx_new(graph);

        if(work != NULL){
           type = light->season == mTM_SEASON_WINTER;
            pal = Common_Get(clip.structure_clip)->get_pal_segment_proc(aSTR_PAL_TOUDAI);
            _texture_z_light_fog_prim_light(graph);

            OPEN_DISP(graph);
            
            gfx = NOW_LIGHT_DISP; 
            gSPSegment(gfx++, 0x8, pal); 

            prmcol.b = light->unk2C8;
            prmcol.a = light->unk2CC;

            if(prmcol.a > (u8)light->unk2D0){
                prmcol.a = light->unk2D0; 
            }
 
            gDPPipeSync(gfx++); 
            gDPSetPrimColor(gfx++, 0, (s8)light->unk2D0, prmcol.r, prmcol.g, prmcol.b, prmcol.a);
            gSPMatrix(gfx++, work, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfx++, mdl[type]);

            SET_LIGHT_DISP(gfx);
            CLOSE_DISP(graph);
        }
    }

    return 1;
}


static void aTOU_actor_draw(ACTOR* actor, GAME* game){
    GAME_PLAY* play = (GAME_PLAY*)game;
    GRAPH* graph;

    Gfx* gfx;
    u16* pal;
    cKF_SkeletonInfo_R_c* keyf;
    Mtx* mtx;
    xyz_t* pos;
    TOUDAI_ACTOR* light = (TOUDAI_ACTOR*)actor;
    
    graph = game->graph;
    pos = &light->actor_class.world.position;
    keyf = &light->keyframe;
    mtx = GRAPH_ALLOC_TYPE(graph, Mtx, keyf->skeleton->num_shown_joints);
 
    if(mtx != NULL){
        pal = Common_Get(clip.structure_clip)->get_pal_segment_proc(aSTR_PAL_TOUDAI);
        
        OPEN_DISP(graph);

        _texture_z_light_fog_prim_npc(graph);
            
        gfx = NOW_POLY_OPA_DISP; 
        gSPSegment(gfx++, 0x8, pal); 
        SET_POLY_OPA_DISP(gfx); 

        _texture_z_light_fog_prim_xlu(graph);

        gfx = NOW_POLY_XLU_DISP; 
        gSPSegment(gfx++, 0x8, pal);  
        SET_POLY_XLU_DISP(gfx); 

        Setpos_HiliteReflect_init(pos, play);
        Setpos_HiliteReflect_xlu_init(pos, play);
        
        cKF_Si3_draw_R_SV(game, keyf, mtx, aTOU_actor_draw_before, aTOU_actor_draw_after, light);
        (*Common_Get(clip).bg_item_clip->draw_shadow_proc)(game, &aTOU_shadow_data, TRUE);
        CLOSE_DISP(graph);
    }
}