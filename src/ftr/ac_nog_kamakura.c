static void fNogKamakura_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fNogKamakura_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNogKamakura_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNogKamakura_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fNogKamakura_func = {
	&fNogKamakura_ct,
	&fNogKamakura_mv,
	&fNogKamakura_dw,
	&fNogKamakura_dt,
	NULL,
};

aFTR_PROFILE iam_nog_kamakura = {
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
	&fNogKamakura_func,
};
