extern Gfx int_sum_chikuon01_on_model[];
extern Gfx int_sum_chikuon01_onT_model[];
static void aSumChikuon01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumChikuon01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumChikuon01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumChikuon01_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aSumChikuon01_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumChikuon01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    (*Common_Get(clip).my_room_clip->mini_disk_common_move_proc)(ftr_actor, my_room_actor, game, 0.0f, 0.0f);
}

static void aSumChikuon01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumChikuon01_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumChikuon01_func = {
	&aSumChikuon01_ct,
	&aSumChikuon01_mv,
	&aSumChikuon01_dw,
	&aSumChikuon01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_chikuon01 = {
	int_sum_chikuon01_on_model,
	int_sum_chikuon01_onT_model,
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
	0,
	0,
	aFTR_INTERACTION_MUSIC_DISK,
	&aSumChikuon01_func,
};
