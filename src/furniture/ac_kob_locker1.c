static void aKobLocker1_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKobLocker1_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKobLocker1_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKobLocker1_dt(FTR_ACTOR* ftr_actor, u8* data);

extern cKF_Animation_R_c cKF_ba_r_int_kob_locker1;
extern cKF_Skeleton_R_c cKF_bs_r_int_kob_locker1;

static void aKobLocker1_ct(FTR_ACTOR* ftr_actor, u8* data){
    cKF_SkeletonInfo_R_c* keyf;

    keyf = &ftr_actor->keyframe;
    cKF_SkeletonInfo_R_ct(keyf, &cKF_bs_r_int_kob_locker1, &cKF_ba_r_int_kob_locker1, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_stop(keyf, &cKF_ba_r_int_kob_locker1, NULL);
    keyf->frame_control.speed = 0.0f;
    cKF_SkeletonInfo_R_play(keyf);
}

static void aKobLocker1_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){

    if(Common_Get(clip).my_room_clip != NULL){
        Common_Get(clip).my_room_clip->open_close_common_move_proc(ftr_actor,my_room_actor,game,1.0f,16.0f);
    }
}

static void aKobLocker1_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
    cKF_Si3_draw_R_SV(game, &ftr_actor->keyframe, ftr_actor->skeleton_mtx[game->frame_counter & 1] , NULL, NULL, NULL);
}

static void aKobLocker1_dt(FTR_ACTOR* ftr_actor, u8* data){
    
}

static aFTR_vtable_c aKobLocker1_func = {
	&aKobLocker1_ct,
	&aKobLocker1_mv,
	&aKobLocker1_dw,
	&aKobLocker1_dt,
	NULL,
};

aFTR_PROFILE iam_kob_locker1 = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	40.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	aFTR_INTERACTION_STORAGE_CLOSET,
	&aKobLocker1_func,
};
