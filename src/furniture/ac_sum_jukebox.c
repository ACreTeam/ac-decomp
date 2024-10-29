extern Gfx int_sum_jukebox_on_model[];
extern Gfx int_sum_jukebox_onT_model[];
extern Gfx int_sum_jukebox_evw_model[];
static void aSumJukebox_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumJukebox_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumJukebox_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumJukebox_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aSumJukebox_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumJukebox_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    (*Common_Get(clip).my_room_clip->mini_disk_common_move_proc)(ftr_actor, my_room_actor, game, 0.0f, 0.0f);
}

static void aSumJukebox_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumJukebox_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumJukebox_func = {
	&aSumJukebox_ct,
	&aSumJukebox_mv,
	&aSumJukebox_dw,
	&aSumJukebox_dt,
	NULL,
};

aFTR_PROFILE iam_sum_jukebox = {
	int_sum_jukebox_on_model,
	int_sum_jukebox_onT_model,
	int_sum_jukebox_evw_model,
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
	aFTR_INTERACTION_MUSIC_DISK,
	&aSumJukebox_func,
};
