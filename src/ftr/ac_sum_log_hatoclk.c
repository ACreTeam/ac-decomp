static void aSumLogHatoclk_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumLogHatoclk_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumLogHatoclk_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumLogHatoclk_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumLogHatoclk_func = {
	&aSumLogHatoclk_ct,
	&aSumLogHatoclk_mv,
	&aSumLogHatoclk_dw,
	&aSumLogHatoclk_dt,
	NULL,
};

aFTR_PROFILE iam_sum_log_hatoclk = {
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
	0,
	0,
	0,
	&aSumLogHatoclk_func,
};
