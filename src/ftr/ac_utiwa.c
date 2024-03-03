static void fUW_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fUW_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fUW_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fUW_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fUW_func = {
	&fUW_ct,
	&fUW_mv,
	&fUW_dw,
	&fUW_dt,
	NULL,
};

aFTR_PROFILE iam_utiwa = {
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
	&fUW_func,
};
