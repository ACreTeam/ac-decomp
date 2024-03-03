static void aSumSlot_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumSlot_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumSlot_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumSlot_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumSlot_func = {
	&aSumSlot_ct,
	&aSumSlot_mv,
	&aSumSlot_dw,
	&aSumSlot_dt,
	NULL,
};

aFTR_PROFILE iam_sum_slot = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	40.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&aSumSlot_func,
};
