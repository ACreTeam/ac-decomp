static void fNYS_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fNYS_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNYS_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNYS_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fNYS_func = {
	&fNYS_ct,
	&fNYS_mv,
	&fNYS_dw,
	&fNYS_dt,
	NULL,
};

aFTR_PROFILE iam_nog_yamishop = {
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
	&fNYS_func,
};
