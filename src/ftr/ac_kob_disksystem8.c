static void aKobDisksystem8_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKobDisksystem8_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKobDisksystem8_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKobDisksystem8_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aKobDisksystem8_func = {
	&aKobDisksystem8_ct,
	&aKobDisksystem8_mv,
	&aKobDisksystem8_dw,
	&aKobDisksystem8_dt,
	NULL,
};

aFTR_PROFILE iam_kob_disksystem8 = {
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
	0,
	0,
	0,
	&aKobDisksystem8_func,
};
