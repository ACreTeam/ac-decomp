static void fNM2_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fNM2_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNM2_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNM2_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fNM2_func = {
	&fNM2_ct,
	&fNM2_mv,
	&fNM2_dw,
	&fNM2_dt,
	NULL,
};

aFTR_PROFILE iam_nog_myhome2 = {
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
	&fNM2_func,
};
