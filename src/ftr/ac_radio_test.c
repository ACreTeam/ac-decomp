static void fRT_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fRT_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fRT_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fRT_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fRT_func = {
	&fRT_ct,
	&fRT_mv,
	&fRT_dw,
	&fRT_dt,
	NULL,
};

aFTR_PROFILE iam_radio_test = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	18.0f,
	0.009f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&fRT_func,
};
