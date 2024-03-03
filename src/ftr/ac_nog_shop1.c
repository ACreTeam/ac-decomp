static void fNS1_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fNS1_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNS1_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNS1_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fNS1_func = {
	&fNS1_ct,
	&fNS1_mv,
	&fNS1_dw,
	&fNS1_dt,
	NULL,
};

aFTR_PROFILE iam_nog_shop1 = {
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
	&fNS1_func,
};
