static void aSumReco_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumReco_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumReco_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumReco_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumReco_func = {
	&aSumReco_ct,
	&aSumReco_mv,
	&aSumReco_dw,
	&aSumReco_dt,
	NULL,
};

aFTR_PROFILE iam_sum_reco01 = {
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
	aFTR_INTERACTION_MUSIC_DISK,
	&aSumReco_func,
};
