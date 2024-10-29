static void aKonAtqclock_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonAtqclock_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonAtqclock_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonAtqclock_dt(FTR_ACTOR* ftr_actor, u8* data);

extern cKF_Animation_R_c cKF_ba_r_int_kon_atqclock;
extern cKF_Skeleton_R_c cKF_bs_r_int_kon_atqclock;

static int aKonAtqclock_DwAfter(GAME* game, cKF_SkeletonInfo_R_c* keyf, int jointNum, Gfx** joint, u8* jointFlag, void* arg,
                      s_xyz* joint1, xyz_t* trans) {
    return 1;
}

static int aKonAtqclock_DwBefore(GAME* game, cKF_SkeletonInfo_R_c* keyf, int jointNum, Gfx** joint, u8* jointFlag, void* arg,
                      s_xyz* joint1, xyz_t* trans) {

    if(jointNum == 5){
        joint1->z -= Common_Get(time).rad_hour;
    }
    else if(jointNum == 7){
        joint1->z -= Common_Get(time).rad_min;
    }

    return 1;
}

static void aKonAtqclock_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
    cKF_Si3_draw_R_SV(game, &ftr_actor->keyframe, ftr_actor->skeleton_mtx[game->frame_counter & 1] , aKonAtqclock_DwBefore, aKonAtqclock_DwAfter, ftr_actor);
}

static void aKonAtqclock_ct(FTR_ACTOR* ftr_actor, u8* data){
    cKF_SkeletonInfo_R_c* keyf;

    keyf = &ftr_actor->keyframe;
    cKF_SkeletonInfo_R_ct(keyf, &cKF_bs_r_int_kon_atqclock, &cKF_ba_r_int_kon_atqclock, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyf, &cKF_ba_r_int_kon_atqclock, NULL);
    cKF_SkeletonInfo_R_play(keyf);
    keyf->frame_control.speed = 0.5f;

}

static void aKonAtqclock_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
    cKF_SkeletonInfo_R_c* keyf;
    aMR_clock_info_c* clock_info;
    
    if(Common_Get(clip).my_room_clip == NULL){
        return;
    }
    clock_info = Common_Get(clip).my_room_clip->clock_info_p;
    keyf = &ftr_actor->keyframe;

    if(clock_info->tick_stop != 0){
        cKF_SkeletonInfo_R_init_standard_repeat(keyf, &cKF_ba_r_int_kon_atqclock, NULL);
        cKF_SkeletonInfo_R_play(keyf);
        keyf->frame_control.speed = 0.5f;
    }
    else if(clock_info->tick0 == 1 || clock_info->tick1 == 1){
        if(aFTR_CAN_PLAY_SE(ftr_actor)){
            sAdo_OngenTrgStart(0x12D, &ftr_actor->position);
        }
        cKF_SkeletonInfo_R_play(keyf);
    }
    else{
        cKF_SkeletonInfo_R_play(keyf);
    }

}

static void aKonAtqclock_dt(FTR_ACTOR* ftr_actor, u8* data){
    
}

static aFTR_vtable_c aKonAtqclock_func = {
	&aKonAtqclock_ct,
	&aKonAtqclock_mv,
	&aKonAtqclock_dw,
	&aKonAtqclock_dt,
	NULL,
};

aFTR_PROFILE iam_kon_atqclock = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	18.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	2,
	0,
	0,
	&aKonAtqclock_func,
};
