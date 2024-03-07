extern aFTR_rig_c aSumMizunomi_sklkey;
static void aSumMizunomi_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumMizunomi_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumMizunomi_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumMizunomi_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumMizunomi_func = {
	&aSumMizunomi_ct,
	&aSumMizunomi_mv,
	&aSumMizunomi_dw,
	&aSumMizunomi_dt,
	NULL,
};

aFTR_PROFILE iam_sum_mizunomi = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aSumMizunomi_sklkey,
	NULL,
	40.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	2,
	0,
	0,
	&aSumMizunomi_func,
};
