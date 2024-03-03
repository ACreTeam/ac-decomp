static void fTIC_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fTIC_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fTIC_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fTIC_func = {
	&fTIC_ct,
	&fTIC_mv,
	&fTIC_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_tak_ice = {
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
	2,
	0,
	aFTR_INTERACTION_START_DISABLED,
	&fTIC_func,
};
