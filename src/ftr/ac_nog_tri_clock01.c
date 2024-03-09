static void aNogTriClock01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aNogTriClock01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogTriClock01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogTriClock01_dt(FTR_ACTOR* ftr_actor, u8* data);

extern cKF_Animation_R_c cKF_ba_r_int_nog_tri_clock01;
extern cKF_Skeleton_R_c cKF_bs_r_int_nog_tri_clock01;

static int aNogTriClock01_DwAfter(GAME* game, cKF_SkeletonInfo_R_c* keyf, int jointNum, Gfx** joint, u8* jointFlag, void* arg,
                      s_xyz* joint1, xyz_t* trans) {
    return 1;
}

static int aNogTriClock01_DwBefore(GAME* game, cKF_SkeletonInfo_R_c* keyf, int jointNum, Gfx** joint, u8* jointFlag, void* arg,
                      s_xyz* joint1, xyz_t* trans) {

    if(jointNum == 3){
        joint1->z -= Common_Get(time).rad_hour;
    }
    else if(jointNum == 4){
        joint1->z -= Common_Get(time).rad_min;
    }

    return 1;
}

static void aNogTriClock01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
    cKF_Si3_draw_R_SV(game, &ftr_actor->keyframe, ftr_actor->skeleton_mtx[game->frame_counter & 1] , aNogTriClock01_DwBefore, aNogTriClock01_DwAfter, ftr_actor);
}

static void aNogTriClock01_ct(FTR_ACTOR* ftr_actor, u8* data){
    cKF_SkeletonInfo_R_c* keyf;

    keyf = &ftr_actor->keyframe;
    cKF_SkeletonInfo_R_ct(keyf, &cKF_bs_r_int_nog_tri_clock01, &cKF_ba_r_int_nog_tri_clock01, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyf, &cKF_ba_r_int_nog_tri_clock01, NULL);
    cKF_SkeletonInfo_R_play(keyf);
    keyf->frame_control.speed = 0.5f;

}
static void aNogTriClock01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
    cKF_SkeletonInfo_R_c* keyf;

    keyf = &ftr_actor->keyframe;
    cKF_SkeletonInfo_R_play(keyf);
}

static void aNogTriClock01_dt(FTR_ACTOR* ftr_actor, u8* data){
    
}

static aFTR_vtable_c aNogTriClock01_func = {
	&aNogTriClock01_ct,
	&aNogTriClock01_mv,
	&aNogTriClock01_dw,
	&aNogTriClock01_dt,
	NULL,
};

aFTR_PROFILE iam_nog_tri_clock01 = {
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
	&aNogTriClock01_func,
};
