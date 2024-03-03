static void fFC_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fFC_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fFC_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fFC_func = {
	&fFC_ct,
	&fFC_mv,
	&fFC_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_famicom_common = {
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
	aFTR_INTERACTION_FAMICOM,
	&fFC_func,
};
