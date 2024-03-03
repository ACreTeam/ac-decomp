static void fNMM_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fNMM_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNMM_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNMM_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fNMM_func = {
	&fNMM_ct,
	&fNMM_mv,
	&fNMM_dw,
	&fNMM_dt,
	NULL,
};

aFTR_PROFILE iam_nog_museum = {
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
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
	0,
	0,
	0,
	0,
	&fNMM_func,
};
