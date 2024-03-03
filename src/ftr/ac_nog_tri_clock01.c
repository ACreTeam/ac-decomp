static void aNogTriClock01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aNogTriClock01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogTriClock01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogTriClock01_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aNogTriClock01_func = {
	&aNogTriClock01_ct,
	&aNogTriClock01_mv,
	&aNogTriClock01_dw,
	&aNogTriClock01_dt,
	NULL,
};

aFTR_PROFILE iam_nog_tri_clock01 = {
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
	2,
	0,
	0,
	&aNogTriClock01_func,
};
