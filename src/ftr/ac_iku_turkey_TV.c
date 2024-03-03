static void fITT_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fITT_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fITT_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fITT_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fITT_func = {
	&fITT_ct,
	&fITT_mv,
	&fITT_dw,
	&fITT_dt,
	NULL,
};

aFTR_PROFILE iam_iku_turkey_TV = {
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
	&fITT_func,
};
