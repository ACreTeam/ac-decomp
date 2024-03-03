static void fTOOL_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fTOOL_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fTOOL_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fTOOL_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fTOOL_func = {
	&fTOOL_ct,
	&fTOOL_mv,
	&fTOOL_dw,
	&fTOOL_dt,
	NULL,
};

aFTR_PROFILE iam_tool = {
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
	&fTOOL_func,
};
