static void fNBC_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fNBC_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNBC_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNBC_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fNBC_func = {
	&fNBC_ct,
	&fNBC_mv,
	&fNBC_dw,
	&fNBC_dt,
	NULL,
};

aFTR_PROFILE iam_nog_balloon_common = {
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
	1,
	0,
	0,
	&fNBC_func,
};
