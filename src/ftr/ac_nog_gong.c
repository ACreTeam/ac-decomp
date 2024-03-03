static void aNogG_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aNogG_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogG_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aNogG_func = {
	&aNogG_ct,
	&aNogG_mv,
	&aNogG_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_nog_gong = {
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
	&aNogG_func,
};
