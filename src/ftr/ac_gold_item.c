static void fGI_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fGI_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fGI_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fGI_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fGI_func = {
	&fGI_ct,
	&fGI_mv,
	&fGI_dw,
	&fGI_dt,
	NULL,
};

aFTR_PROFILE iam_gold_item = {
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
	&fGI_func,
};
