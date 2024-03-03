static void fNYB_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fNYB_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNYB_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNYB_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fNYB_func = {
	&fNYB_ct,
	&fNYB_mv,
	&fNYB_dw,
	&fNYB_dt,
	NULL,
};

aFTR_PROFILE iam_nog_yubin = {
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
	&fNYB_func,
};
