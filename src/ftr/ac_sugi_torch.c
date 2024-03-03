static void fSGT_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fSGT_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fSGT_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fSGT_func = {
	&fSGT_ct,
	&fSGT_mv,
	&fSGT_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sugi_torch = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	41.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&fSGT_func,
};
