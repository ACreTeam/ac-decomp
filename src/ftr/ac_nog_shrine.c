static void fNSH_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fNSH_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNSH_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNSH_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fNSH_func = {
	&fNSH_ct,
	&fNSH_mv,
	&fNSH_dw,
	&fNSH_dt,
	NULL,
};

aFTR_PROFILE iam_nog_shrine = {
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
	&fNSH_func,
};
