static void aNogFan_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aNogFan_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogFan_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogFan_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aNogFan_func = {
	&aNogFan_ct,
	&aNogFan_mv,
	&aNogFan_dw,
	&aNogFan_dt,
	NULL,
};

aFTR_PROFILE iam_nog_fan01 = {
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
	&aNogFan_func,
};
