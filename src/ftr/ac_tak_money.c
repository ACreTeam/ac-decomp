static void fTMny_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fTMny_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fTMny_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fTMny_func = {
	&fTMny_ct,
	&fTMny_mv,
	&fTMny_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_tak_money = {
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
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
	0,
	0,
	0,
	0,
	&fTMny_func,
};
