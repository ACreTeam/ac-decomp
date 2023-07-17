#include "ac_train0.h"

#include "m_name_table.h"
#include "m_common_data.h"
#include "m_field_info.h"
#include "m_event.h"
#include "sys_matrix.h"
#include "m_play.h"

static void aTR0_actor_ct(ACTOR* actor, GAME* game);
static void aTR0_actor_dt(ACTOR* actor, GAME* game);
static void aTR0_actor_move(ACTOR* actor, GAME* game);
static void aTR0_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE Train0_Profile = {
    mAc_PROFILE_TRAIN0,
    ACTOR_PART_ITEM,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | 1 << 11 | ACTOR_STATE_NO_MOVE_WHILE_CULLED, //figure out flag 0x800
    TRAIN0,
    ACTOR_OBJ_BANK_3,
    sizeof(TRAIN0_ACTOR),
    &aTR0_actor_ct,
    &aTR0_actor_dt,
    &aTR0_actor_move,
    &aTR0_actor_draw,
    NULL
};

extern cKF_Skeleton_R_c cKF_bs_r_obj_train1_1;
extern cKF_Animation_R_c cKF_ba_r_obj_train1_1;

extern Gfx obj_train1_2_model[];

static void aTR0_actor_ct(ACTOR* actor, GAME* GAME){
    TRAIN0_ACTOR* train0 = (TRAIN0_ACTOR*)actor;

    cKF_SkeletonInfo_R_ct(&train0->keyframe, &cKF_bs_r_obj_train1_1,NULL, train0->work, train0->target);
    cKF_SkeletonInfo_R_init(&train0->keyframe, train0->keyframe.skeleton, &cKF_ba_r_obj_train1_1, 
        1.0f, 25.0f, 1.0f, 0.5f, 0.0f, 1, NULL);
    cKF_SkeletonInfo_R_play(&train0->keyframe);
    train0->actor_class.cull_width = 600.0f;
    train0->actor_class.world.angle.y = 16384;
    train0->tr_action = 5;
}

static void aTR0_actor_dt(ACTOR* actor, GAME* game){

    TRAIN0_ACTOR* train0 = (TRAIN0_ACTOR*)actor;

    xyz_t tr_home_pos;

    tr_home_pos = train0->actor_class.home.position;

    mFI_SetFG_common(0, tr_home_pos, 0);

    if(train0->tr_actor_p != NULL){
        Actor_delete(train0->tr_actor_p);
        train0->tr_actor_p = NULL; 
    }
    cKF_SkeletonInfo_R_dt(&train0->keyframe);
    Common_Set(train_exists_flag, 0);
}

static void aTR0_ctrl_engineer(ACTOR* actor, GAME* game){
    TRAIN0_ACTOR* train0 = (TRAIN0_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY* )game;

    
    ACTOR* ac_p;

    ac_p = train0->tr_actor_p;

    if(ac_p == NULL){

        if((*Common_Get(clip.npc_clip)->setupActor_proc)(play, SP_NPC_ENGINEER, -1,-1,-1,-1,-1,0,0) == 1){
            train0->tr_actor_p = Actor_info_fgName_search(&play->actor_info, SP_NPC_ENGINEER, ACTOR_PART_NPC);
        }
    }
    else{
        ac_p->world.position.x = -40.0f + train0->actor_class.world.position.x;
        ac_p->world.position.y = 47.0f + train0->actor_class.world.position.y;
        ac_p->world.position.z = 20.0f + train0->actor_class.world.position.z;
    }
}

static void aTR0_set_effect(ACTOR* actor, GAME* game){
    TRAIN0_ACTOR* train0 = (TRAIN0_ACTOR*)actor;

    int calc; 
    xyz_t pos;
    xyz_t clip_pos;
    if(train0->effect_num <= 0){
        if(train0->actor_class.speed >= 1.0f){
            calc = (12.0f/train0->actor_class.speed);
            train0->effect_num = calc;
        }
        else{
            train0->effect_num = 12;
        }
        xyz_t_move(&pos, &train0->actor_class.world.position);
        pos.x += 36.0f;
        pos.y += 110.0f;

        if(mEv_CheckTitleDemo() == 0){
            clip_pos = pos;
            (*Common_Get(clip.effect_clip)->effect_make_proc)(35, clip_pos, 1,0, game, train0->actor_class.npc_id, 0,0);
        }
    }
    else{
        train0->effect_num--;
    }
}

static void aTR0_steam_work_sub(ACTOR* actor, GAME* game, int x_idx){
    TRAIN0_ACTOR* train0 = (TRAIN0_ACTOR*)actor;
    xyz_t pos;
    xyz_t clip_pos;
    int unk2c0;
    static f32 setX[] = {15.0f, 22.0f};
    static s16 angl[] = {0xd000, 0x0400};

    pos.x = train0->actor_class.world.position.x + setX[x_idx];
    pos.y = train0->actor_class.world.position.y + 21.0f;
    pos.z = train0->actor_class.world.position.z + 42.0f;
    unk2c0 = train0->unk2c0;
    if(mEv_CheckTitleDemo() == 0){
            clip_pos = pos;
            (*Common_Get(clip.effect_clip)->effect_make_proc)(63, clip_pos, 1,angl[x_idx], game, train0->actor_class.npc_id, 0,0);
        }
    unk2c0++;
    train0->unk2c0 = unk2c0 % 4;
}

static void aTR0_steam_work(ACTOR* actor, GAME* game){
    TRAIN0_ACTOR* train0 = (TRAIN0_ACTOR*)actor;

    if(train0->steam_available == 1){
        if((train0->steam_timer >= 2) && (train0->steam_timer <= 5)){
        aTR0_steam_work_sub(actor,game,0);
        }
        if((train0->steam_timer >= 13) && (train0->steam_timer <= 16)){
        aTR0_steam_work_sub(actor,game,1);
        }
    }
}

static f32 calc_speed1(ACTOR* actor){
    TRAIN0_ACTOR* train0 = (TRAIN0_ACTOR*)actor;

    if(fabsf(train0->tr_speed) < 0.008f){
        return 0.8f + train0->actor_class.speed;
    }

    if(train0->tr_speed < train0->actor_class.speed){
        return train0->actor_class.speed +  (0.5f * - (train0->tr_speed - train0->actor_class.speed));
    }

    return train0->actor_class.speed;
}

static f32 calc_speed2(ACTOR* actor){
    TRAIN0_ACTOR* train0 = (TRAIN0_ACTOR*)actor;
    int should_stop = fabsf(train0->actor_class.speed) < 0.008f;
    
    return should_stop == FALSE ? train0->actor_class.speed : -0.23f;
}

static void aTR0_ctrl_back_car(ACTOR* actor){
    TRAIN0_ACTOR* train0 = (TRAIN0_ACTOR*)actor;

    f32 tr_back_calc = train0->tr1_pos;
    f32 base_x_pos = -125.0f + train0->actor_class.world.position.x; 
    tr_back_calc +=  0.5f * train0->tr_speed;

    if((tr_back_calc - base_x_pos) > 2.0f){
        train0->tr_speed = calc_speed2(actor);
        train0->tr1_pos = 2.0f + base_x_pos;
    }
    else if((tr_back_calc - base_x_pos) <= 0.0f){
        train0->tr_speed = calc_speed1(actor);
        train0->tr1_pos = base_x_pos;
    }
    else{
        chase_f(&train0->tr_speed, 0.0f, 0.0025f);
        train0->tr1_pos = tr_back_calc;
    }
}

static void aTR0_animation(ACTOR* actor){
    TRAIN0_ACTOR* train0 = (TRAIN0_ACTOR*)actor;
    
    int av = 0;
    int cur_frame = train0->keyframe.frame_control.current_frame;
    cKF_SkeletonInfo_R_play(&train0->keyframe);

    if( cur_frame!= train0->steam_timer){
        train0->steam_timer = cur_frame;
        av = 1;
    }
    train0->steam_available = av; 
}

static void aTR0_move(ACTOR* actor){
    TRAIN0_ACTOR* train0 = (TRAIN0_ACTOR*)actor;
    xyz_t pos;

    if(train0->tr_action != Common_Get(train_action)){
        train0->tr_action = Common_Get(train_action);
    }
    pos = Common_Get(train_position);
    train0->actor_class.world.position.x = pos.x;
    train0->actor_class.world.position.z = pos.z;
    train0->actor_class.speed = Common_Get(train_speed);
}

static void aTR0_delcheck(ACTOR* actor,GAME* game){
    GAME_PLAY* play = (GAME_PLAY* )game;
    TRAIN0_ACTOR* train0 = (TRAIN0_ACTOR*)actor;  

    int x;
    int z;
    int abs_x;
    xyz_t pos;

    pos = train0->actor_class.world.position;
    
    mFI_Wpos2BlockNum(&x,&z,pos);
    x -= play->block_table.block_x;
    abs_x = x >= 0 ? x: -x;

    if((abs_x >= 2) || (z != play->block_table.block_z) || (train0->tr_action == 0)){
        if((int)train0->tr_actor_p != 0){
            Actor_delete(train0->tr_actor_p);
        } 
        Actor_delete(actor->child_actor);
        Actor_delete(actor);
    }
}

static void aTR0_actor_move(ACTOR* actor, GAME* game){
    TRAIN0_ACTOR* train0 = (TRAIN0_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY* )game;

    f32 speed;
    aTR0_animation(actor);
    aTR0_move(actor);

    if(!(fabsf(train0->actor_class.speed) < 0.008f)){
        aTR0_set_effect(actor,game);
        aTR0_steam_work(actor,game);
    }

    if(mEv_CheckTitleDemo() == 1){
        train0->tr1_pos = -125.0f + train0->actor_class.world.position.x;
    }
    else{
        aTR0_ctrl_back_car(actor);
    }

    aTR0_ctrl_engineer(actor,game);

    speed = (train0->actor_class.speed / 40.0f) * 10.0f;

    if(speed >= 0.5f){
        speed = 0.5f;
    }

    train0->keyframe.frame_control.speed = speed;
    aTR0_delcheck(&train0->actor_class, game);
}

static void aTR0_actor_draw(ACTOR* actor, GAME* game){
    u16* pal = (*Common_Get(clip).structure_clip->get_pal_segment_proc)(0x39);
    GRAPH* graph = game->graph;
    cKF_SkeletonInfo_R_c* keyf;
    TRAIN0_ACTOR* train0 = (TRAIN0_ACTOR*)actor;

    Mtx* mtx;
    Gfx* gfx;

    keyf = &train0->keyframe;
    mtx = GRAPH_ALLOC_TYPE(graph, Mtx, keyf->skeleton->num_shown_joints);

    if (mtx != NULL){
        _texture_z_light_fog_prim_npc(graph);
        Matrix_push();
        Matrix_translate(train0->tr1_pos, train0->actor_class.world.position.y, 
            train0->actor_class.world.position.z, 0);
        Matrix_scale(train0->actor_class.scale.x, train0->actor_class.scale.y, 
            train0->actor_class.scale.z, 1);

        OPEN_DISP(graph);
        gfx = NOW_POLY_OPA_DISP;
        
        gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(gfx++, G_MWO_SEGMENT_8, pal); 
        gDPLoadTLUT_Dolphin(gfx++, 15, 16, 1, pal);
        gSPDisplayList(gfx++, obj_train1_2_model);
        
        SET_POLY_OPA_DISP(gfx);
        CLOSE_DISP(graph);
        
        Matrix_pull();
        cKF_Si3_draw_R_SV(game, keyf, mtx, NULL,NULL,train0);
    }
}