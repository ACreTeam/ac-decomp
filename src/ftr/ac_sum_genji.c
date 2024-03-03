static void aSumgenji_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumgenji_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumgenji_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumgenji_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumgenji_func = {
	&aSumgenji_ct,
	&aSumgenji_mv,
	&aSumgenji_dw,
	&aSumgenji_dt,
	NULL,
};

aFTR_PROFILE iam_sum_genji = {
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
	&aSumgenji_func,
};
