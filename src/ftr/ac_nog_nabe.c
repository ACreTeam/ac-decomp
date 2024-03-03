static void fNNB_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fNNB_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNNB_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNNB_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fNNB_func = {
	&fNNB_ct,
	&fNNB_mv,
	&fNNB_dw,
	&fNNB_dt,
	NULL,
};

aFTR_PROFILE iam_nog_nabe = {
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
	&fNNB_func,
};
