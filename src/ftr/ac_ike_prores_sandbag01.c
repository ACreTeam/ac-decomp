static void aIPS_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aIPS_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aIPS_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aIPS_func = {
	&aIPS_ct,
	&aIPS_mv,
	&aIPS_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_ike_prores_sandbag01 = {
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
	1,
	0,
	0,
	&aIPS_func,
};
