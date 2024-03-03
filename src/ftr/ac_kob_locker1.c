static void aKobLocker1_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKobLocker1_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKobLocker1_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKobLocker1_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aKobLocker1_func = {
	&aKobLocker1_ct,
	&aKobLocker1_mv,
	&aKobLocker1_dw,
	&aKobLocker1_dt,
	NULL,
};

aFTR_PROFILE iam_kob_locker1 = {
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
	aFTR_INTERACTION_STORAGE_CLOSET,
	&aKobLocker1_func,
};
