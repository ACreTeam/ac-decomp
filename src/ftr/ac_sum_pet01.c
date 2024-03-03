static void aSumPet01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumPet01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumPet01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aSumPet01_func = {
	&aSumPet01_ct,
	&aSumPet01_mv,
	&aSumPet01_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sum_pet01 = {
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
	1,
	0,
	aFTR_INTERACTION_INSECT,
	&aSumPet01_func,
};
