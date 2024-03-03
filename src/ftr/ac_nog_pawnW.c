static void aNogpawnW_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aNogpawnW_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogpawnW_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogpawnW_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aNogpawnW_func = {
	&aNogpawnW_ct,
	&aNogpawnW_mv,
	&aNogpawnW_dw,
	&aNogpawnW_dt,
	NULL,
};

aFTR_PROFILE iam_nog_pawnW = {
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
	&aNogpawnW_func,
};
