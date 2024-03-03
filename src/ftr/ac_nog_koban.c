static void fNKN_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fNKN_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNKN_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNKN_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fNKN_func = {
	&fNKN_ct,
	&fNKN_mv,
	&fNKN_dw,
	&fNKN_dt,
	NULL,
};

aFTR_PROFILE iam_nog_koban = {
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
	&fNKN_func,
};
