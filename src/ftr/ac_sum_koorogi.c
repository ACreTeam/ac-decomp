static void aSumKoorogi_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumKoorogi_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumKoorogi_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aSumKoorogi_func = {
	&aSumKoorogi_ct,
	&aSumKoorogi_mv,
	&aSumKoorogi_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sum_koorogi = {
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
	&aSumKoorogi_func,
};
