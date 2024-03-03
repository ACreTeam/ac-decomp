static void aNogPawnB_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aNogPawnB_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogPawnB_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogPawnB_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aNogPawnB_func = {
	&aNogPawnB_ct,
	&aNogPawnB_mv,
	&aNogPawnB_dw,
	&aNogPawnB_dt,
	NULL,
};

aFTR_PROFILE iam_nog_pawnB = {
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
	&aNogPawnB_func,
};
