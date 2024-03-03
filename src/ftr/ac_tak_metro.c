static void aTakMetro_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aTakMetro_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aTakMetro_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aTakMetro_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aTakMetro_func = {
	&aTakMetro_ct,
	&aTakMetro_mv,
	&aTakMetro_dw,
	&aTakMetro_dt,
	NULL,
};

aFTR_PROFILE iam_tak_metro = {
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
	&aTakMetro_func,
};
