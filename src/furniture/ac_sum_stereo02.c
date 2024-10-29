extern Gfx int_sum_stereo02_on_model[];
static void aSumStereo02_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumStereo02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumStereo02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumStereo02_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aSumStereo02_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumStereo02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        (*Common_Get(clip).my_room_clip->mini_disk_common_move_proc)(ftr_actor, my_room_actor, game, 0.0f, 0.0f);
    }
}

static void aSumStereo02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumStereo02_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumStereo02_func = {
	&aSumStereo02_ct,
	&aSumStereo02_mv,
	&aSumStereo02_dw,
	&aSumStereo02_dt,
	NULL,
};

aFTR_PROFILE iam_sum_stereo02 = {
	int_sum_stereo02_on_model,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	18.0f,
	0.01f,
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
	0,
	0,
	0,
	aFTR_INTERACTION_MUSIC_DISK,
	&aSumStereo02_func,
};
