#include "ac_train1.h"
#include "ac_train0.h"

#include "graph.h"
#include "m_name_table.h"
#include "m_rcp.h"
#include "m_player.h"
#include "m_player_lib.h"
#include "sys_math3d.h"
#include "m_common_data.h"
#include "m_field_info.h"
#include "m_event.h"


static void aTR1_actor_ct(ACTOR* actor, GAME* game);
static void aTR1_actor_dt(ACTOR* actor, GAME* game);
static void aTR1_actor_move(ACTOR* actor, GAME* game);
static void aTR1_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE Train1_Profile = {
  mAc_PROFILE_TRAIN1,
  ACTOR_PART_ITEM,
  ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | 1 << 11 | ACTOR_STATE_NO_MOVE_WHILE_CULLED, //figure out flag 0x800
  TRAIN1,
  ACTOR_OBJ_BANK_3,
  sizeof(TRAIN1_ACTOR),
  &aTR1_actor_ct,
  &aTR1_actor_dt,
  &aTR1_actor_move,
  &aTR1_actor_draw,
  NULL
};

extern cKF_Skeleton_R_c cKF_bs_r_obj_train1_3;
extern cKF_Animation_R_c cKF_ba_r_obj_train1_3_open;
extern cKF_Animation_R_c cKF_ba_r_obj_train1_3_close;


static void aTR1_setupAction(ACTOR*, int);

static void aTR1_actor_ct(ACTOR* actor, GAME* game){
    TRAIN1_ACTOR* train1 = (TRAIN1_ACTOR*)actor;
    
    cKF_SkeletonInfo_R_ct(&train1->keyframe, &cKF_bs_r_obj_train1_3, NULL, train1->work, train1->morph);
    aTR1_setupAction((ACTOR*)train1, 5);
    train1->anim_state = cKF_SkeletonInfo_R_play(&train1->keyframe);
    actor->world_rotation.y = 0x4000;
    train1->tr_speed = 1.0f;
}


static void aTR1_actor_dt(ACTOR* actor, GAME* game){
    TRAIN1_ACTOR* train1 = (TRAIN1_ACTOR*)actor;

    xyz_t tr_home_pos;

    tr_home_pos = train1->actor_class.home_position;

    mFI_SetFG_common(EMPTY_NO, tr_home_pos, FALSE);
    cKF_SkeletonInfo_R_dt(&train1->keyframe);
}

static void aTR1_OngenTrgStart(ACTOR* actor, u16 id){
    TRAIN1_ACTOR* train1 = (TRAIN1_ACTOR*)actor;

    sAdo_OngenTrgStart(id, &train1->actor_class.world_position);
}

static f32 calc_speed1(ACTOR* actor0, ACTOR* actor1) {
    TRAIN0_ACTOR* train0 = (TRAIN0_ACTOR*)actor0;
    TRAIN1_ACTOR* train1 = (TRAIN1_ACTOR*)actor1;

    if (fabsf(actor1->speed) < 0.008f) {
        return 0.8f + train0->tr_speed;
    }

    if (actor1->speed < train0->tr_speed){
        return train0->tr_speed + (0.5f * - (actor1->speed - train0->tr_speed));
    }

    return train0->tr_speed;
}

static f32 calc_speed2(ACTOR* actor){
    TRAIN1_ACTOR* train1 = (TRAIN1_ACTOR*)actor;
    int should_stop = fabsf(train1->tr0_pos) < 0.008f;
    
    return should_stop == FALSE ? train1->tr0_pos : -0.23f;
}

static void aTR1_position_move(ACTOR* actor){
    TRAIN1_ACTOR* train1 = (TRAIN1_ACTOR*)actor;
    TRAIN0_ACTOR* train0 = (TRAIN0_ACTOR*)actor->parent_actor;

    f32 diff;
    f32 tr_back_calc;
    f32 base_x_pos;
    
    tr_back_calc = train1->actor_class.world_position.x;
    base_x_pos = -125.0f + train0->tr1_pos;
    tr_back_calc += 0.5f * train1->actor_class.speed;
    
    diff = tr_back_calc - base_x_pos;
    if((diff) <= 0.0f){
        train1->actor_class.speed = calc_speed1(actor->parent_actor, actor);
        train1->actor_class.world_position.x = base_x_pos;
    }
    else if((diff) > 2.0f){
        train1->actor_class.speed = calc_speed2(actor->parent_actor);
        train1->actor_class.world_position.x = 2.0f + base_x_pos;
    }
    else{
        chase_f(&train1->actor_class.speed, 0.0f, 0.0025f);
        train1->actor_class.world_position.x = tr_back_calc;
    }
}

static void aTR1_chg_station_attr(int station){
    static xyz_t doorway_pos = { 2180.0f, 0.0f, 820.0f };
    xyz_t soil_pos;
    xyz_t unk20_pos;

    if(mEv_CheckFirstIntro() == 0){
        if(station == 5){
            soil_pos = doorway_pos;
            mCoBG_SetAttribute(&soil_pos, 7);
        }
        else if(station == 6){
            unk20_pos = doorway_pos;
            mCoBG_SetAttribute(&unk20_pos, 0x20);
        }
    }
}

static void aTR1_passenger_ctrl(ACTOR* actor){
    TRAIN1_ACTOR* train1 = (TRAIN1_ACTOR*)actor;

    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    xyz_t pos;
    s_xyz rot;

    if(train1->player_pass_exists == 1){
        pos.x = train1->actor_class.world_position.x + 60.0f;
        pos.y = train1->actor_class.world_position.y + 20.0f;
        pos.z = train1->actor_class.world_position.z + 20.0f;
        rot.x = ZeroSVec.x;
        rot.y = ZeroSVec.y;
        rot.z = ZeroSVec.z;
        get_player_actor_withoutCheck((GAME_PLAY*)gamePT)->update_Rot_Pos_actor_proc(gamePT, &pos, &rot, 46);
    }
    else if(train1->player_pass_leaving == 1){
        pos.x = train1->actor_class.world_position.x + 2.0f;
        pos.y = train1->actor_class.world_position.y + 16.0f;
        pos.z = train1->actor_class.world_position.z + 20.0f;
        get_player_actor_withoutCheck((GAME_PLAY*)gamePT)->update_Rot_Pos_actor_proc(gamePT, &pos, NULL, 14);
        
    }
}

#pragma pool_data on
static void aTR1_setupAction(ACTOR* actor, int action){
    TRAIN1_ACTOR* train1 = (TRAIN1_ACTOR*)actor;
    
    static cKF_Animation_R_c* anime_table[] = {&cKF_ba_r_obj_train1_3_open, &cKF_ba_r_obj_train1_3_close};
    static f32 anime_end[] = {24.0f, 32.0f};
    static int animeSeqNoTable[] = {0,0,0,0,0,1,1,0,0};
    static f32 anime_spd[]  = {0.0f,0.0f,0.0f,0.0f, 0.5f, 0.0f,0.5f,0.0f,0.0f};
    
    cKF_Animation_R_c* anime_pt;
    f32 speed;
    f32 end;
    f32 tr_speed;
    int seq_no = animeSeqNoTable[action];
    
    anime_pt = anime_table[seq_no];
    speed = anime_spd[action];
    end = anime_end[seq_no];

    tr_speed = 1.0f;
    train1->tr_action = action;
    
    if((train1->tr_action == 6) || (train1->tr_action == 4)){
        if((mEv_CheckTitleDemo() == 0) && (tr_speed != train1->tr_speed)){
            aTR1_OngenTrgStart(actor, 43);
        }
        else{
            tr_speed = end;
        }
    }
    cKF_SkeletonInfo_R_init(&train1->keyframe, train1->keyframe.skeleton, anime_pt,
        1.0f, end, tr_speed, speed, 0.0f, 0, NULL );
    aTR1_chg_station_attr(action);
}
#pragma pool_data reset

static void aTR1_actor_move(ACTOR* actor, GAME* game){
    TRAIN1_ACTOR* train1 = (TRAIN1_ACTOR*)actor;
    TRAIN0_ACTOR* train0 = (TRAIN0_ACTOR*)actor->parent_actor;
    cKF_SkeletonInfo_R_c* keyframe = &train1->keyframe;

    
    train1->anim_state = cKF_SkeletonInfo_R_play(keyframe);
    if(mEv_CheckTitleDemo() <= 0){
      aTR1_position_move((ACTOR*)train1);
    }
    aTR1_passenger_ctrl((ACTOR*)train1);

    if(train0->tr_action != train1->tr_action){
      aTR1_setupAction((ACTOR*)train1, train0->tr_action);
    }

    train1->tr_speed = 0.0f;
}

static void aTR1_actor_draw(ACTOR* actor, GAME* game){
    u16* pal = (*Common_Get(clip).structure_clip->get_pal_segment_proc)(0x3A);

    TRAIN1_ACTOR* train1 = (TRAIN1_ACTOR*)actor;
    
    GRAPH* graph = game->graph;
    cKF_SkeletonInfo_R_c* keyf;
    Mtx* mtx;
    Gfx* gfx;

    keyf = &train1->keyframe;
    mtx = GRAPH_ALLOC_TYPE(graph, Mtx, keyf->skeleton->num_shown_joints);

    if(mtx != NULL){
        _texture_z_light_fog_prim_npc(graph);

        OPEN_DISP(graph);

        gfx = NOW_POLY_OPA_DISP;
        gSPSegment(gfx++, 0x8, pal);
        SET_POLY_OPA_DISP(gfx);
        CLOSE_DISP(graph);

        cKF_Si3_draw_R_SV(game, keyf, mtx, NULL,NULL,train1);
    }
}
