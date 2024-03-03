extern aFTR_rig_c &aSumMezaClock_sklkey;
static void aSumMezaClock_Dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aSumMezaClock_func = {
	NULL,
	NULL,
	&aSumMezaClock_Dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sum_mezaclock = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aSumMezaClock_sklkey,
	NULL,
	18.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&aSumMezaClock_func,
};
