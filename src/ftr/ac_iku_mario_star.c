static void fIMS_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fIMS_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fIMS_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fIMS_func = {
	&fIMS_ct,
	&fIMS_mv,
	&fIMS_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_iku_mario_star = {
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
	0,
	&fIMS_func,
};
