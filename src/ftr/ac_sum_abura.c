static void aSumAbura_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumAbura_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumAbura_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aSumAbura_func = {
	&aSumAbura_ct,
	&aSumAbura_mv,
	&aSumAbura_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sum_abura = {
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
	&aSumAbura_func,
};
