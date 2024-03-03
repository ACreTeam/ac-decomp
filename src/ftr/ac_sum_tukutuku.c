static void aSumTukutuku_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumTukutuku_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumTukutuku_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aSumTukutuku_func = {
	&aSumTukutuku_ct,
	&aSumTukutuku_mv,
	&aSumTukutuku_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sum_tukutuku = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	30.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	2,
	0,
	aFTR_INTERACTION_INSECT,
	&aSumTukutuku_func,
};
