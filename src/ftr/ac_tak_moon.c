static void fTMN_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fTMN_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fTMN_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fTMN_func = {
	&fTMN_ct,
	&fTMN_mv,
	&fTMN_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_tak_moon = {
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
	aFTR_SHAPE_TYPEC,
	mCoBG_FTR_TYPEC,
	0,
	2,
	0,
	0,
	&fTMN_func,
};
