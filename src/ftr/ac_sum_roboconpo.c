static void aSumRoboconpo_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumRoboconpo_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumRoboconpo_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumRoboconpo_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumRoboconpo_func = {
	&aSumRoboconpo_ct,
	&aSumRoboconpo_mv,
	&aSumRoboconpo_dw,
	&aSumRoboconpo_dt,
	NULL,
};

aFTR_PROFILE iam_sum_roboconpo = {
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
	&aSumRoboconpo_func,
};
