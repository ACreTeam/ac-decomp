static void aSumKirigirisu_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumKirigirisu_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumKirigirisu_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aSumKirigirisu_func = {
	&aSumKirigirisu_ct,
	&aSumKirigirisu_mv,
	&aSumKirigirisu_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sum_kirigirisu = {
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
	&aSumKirigirisu_func,
};
