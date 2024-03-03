static void fIJH_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fIJH_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fIJH_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fIJH_func = {
	&fIJH_ct,
	&fIJH_mv,
	&fIJH_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_ike_jny_hariko01 = {
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
	&fIJH_func,
};
