static void fYC_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fYC_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fYC_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fYC_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fYC_func = {
	&fYC_ct,
	&fYC_mv,
	&fYC_dw,
	&fYC_dt,
	NULL,
};

aFTR_PROFILE iam_yaz_candle = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	42.43f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	1,
	0,
	0,
	&fYC_func,
};
