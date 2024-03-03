static void fTTR_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fTTR_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fTTR_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fTTR_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fTTR_func = {
	&fTTR_ct,
	&fTTR_mv,
	&fTTR_dw,
	&fTTR_dt,
	NULL,
};

aFTR_PROFILE iam_tak_tailor = {
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
	&fTTR_func,
};
