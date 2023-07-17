#include "ac_train_door.h"

#include "audio.h"
#include "m_rcp.h"
#include "m_name_table.h"

static void aTRD_actor_ct(ACTOR* actor, GAME* game);
static void aTRD_actor_dt(ACTOR* actor, GAME* game);
static void aTRD_actor_move(ACTOR* actor, GAME* game);
static void aTRD_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE TrainDoor_Profile = {
    mAc_PROFILE_TRAINDOOR,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    TRAIN_DOOR,
    ACTOR_OBJ_BANK_11,
    sizeof(TRAINDOOR_ACTOR),
    &aTRD_actor_ct,
    &aTRD_actor_dt,
    &aTRD_actor_move,
    &aTRD_actor_draw,
    NULL
};

extern cKF_Skeleton_R_c cKF_bs_r_obj_romtrain_door;
extern cKF_Animation_R_c cKF_ba_r_obj_romtrain_door;

static void aTRD_actor_ct(ACTOR* actor, GAME* game){
    TRAINDOOR_ACTOR* traindoor = (TRAINDOOR_ACTOR*)actor;

    cKF_SkeletonInfo_R_ct(&traindoor->keyframe, &cKF_bs_r_obj_romtrain_door, NULL, &traindoor->work, &traindoor->target);
    cKF_SkeletonInfo_R_init(&traindoor->keyframe,traindoor->keyframe.skeleton, &cKF_ba_r_obj_romtrain_door,1.0f,51.0f,1.0f,
    0.0f,0.0f,0,NULL);
    traindoor->keyframe.morph_counter = 0.0f;
    cKF_SkeletonInfo_R_play(&traindoor->keyframe);
}

static void aTRD_actor_dt(ACTOR* actor, GAME* game){
    TRAINDOOR_ACTOR* traindoor = (TRAINDOOR_ACTOR*)actor;

    cKF_SkeletonInfo_R_dt(&traindoor->keyframe);
}

static void aTRD_set_door_SE(ACTOR* actor){
    TRAINDOOR_ACTOR* traindoor = (TRAINDOOR_ACTOR*)actor;

    static f32 chk_pat[] = {2.0f, 27.0f};
    static u16 se_no[] = {1042, 1043,0, 0,0,0, 0,0,0};
    int i;

    for(i = 0; i < 2; i++){

        if(cKF_FrameControl_passCheck_now(&traindoor->keyframe.frame_control,chk_pat[i]) != 0){
            sAdo_OngenTrgStart(se_no[i], &traindoor->actor_class.world.position);
            return;
        }
    }
}

static void aTRD_actor_move(ACTOR* actor, GAME* game){
    TRAINDOOR_ACTOR* traindoor = (TRAINDOOR_ACTOR*)actor;

    if(traindoor->idle == 1){
        traindoor->idle = 0;
        traindoor->keyframe.frame_control.speed = 0.5f;
    }

    if(cKF_SkeletonInfo_R_play(&traindoor->keyframe) == 1){
        traindoor->keyframe.frame_control.current_frame = traindoor->keyframe.frame_control.start_frame;
        traindoor->keyframe.frame_control.speed = 0.0f;
    }
    aTRD_set_door_SE(actor);
}

static void aTRD_actor_draw(ACTOR* actor, GAME* game){
    TRAINDOOR_ACTOR* traindoor = (TRAINDOOR_ACTOR*)actor;

    cKF_SkeletonInfo_R_c* keyf = &traindoor->keyframe;
    Gfx* mtx;
    Mtx* mtxp;
    
    mtx = GRAPH_ALLOC(game->graph, (u32) keyf->skeleton->num_shown_joints * 64);

    mtxp = (Mtx*)mtx;
    if(mtxp != NULL){
        _texture_z_light_fog_prim(game->graph);
        texture_z_light_prim_xlu_disp(game->graph);
        cKF_Si3_draw_R_SV(game,keyf, mtxp, NULL,NULL,NULL);
    }
}