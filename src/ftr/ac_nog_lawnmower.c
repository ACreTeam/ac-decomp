static void fNLM_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fNLM_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNLM_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fNLM_func = {
	&fNLM_ct,
	&fNLM_mv,
	&fNLM_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_nog_lawnmower = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	40.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&fNLM_func,
};
