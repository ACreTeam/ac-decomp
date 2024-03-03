static void fTTnt_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fTTnt_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fTTnt_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fTTnt_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fTTnt_func = {
	&fTTnt_ct,
	&fTTnt_mv,
	&fTTnt_dw,
	&fTTnt_dt,
	NULL,
};

aFTR_PROFILE iam_tak_tent = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	15.7f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&fTTnt_func,
};
