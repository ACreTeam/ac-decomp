static void fNFL_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fNFL_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNFL_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNFL_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fNFL_func = {
	&fNFL_ct,
	&fNFL_mv,
	&fNFL_dw,
	&fNFL_dt,
	NULL,
};

aFTR_PROFILE iam_nog_flower = {
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
	aFTR_INTERACTION_NO_COLLISION,
	&fNFL_func,
};
