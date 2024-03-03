static void fNS_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fNS_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNS_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNS_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fNS_func = {
	&fNS_ct,
	&fNS_mv,
	&fNS_dw,
	&fNS_dt,
	NULL,
};

aFTR_PROFILE iam_nog_sprinkler = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	18.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	aFTR_INTERACTION_START_DISABLED,
	&fNS_func,
};
