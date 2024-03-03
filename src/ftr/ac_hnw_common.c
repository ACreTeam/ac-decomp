static void aHnwCommon_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aHnwCommon_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aHnwCommon_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aHnwCommon_dt(FTR_ACTOR* ftr_actor, u8* data);
static void aHnwCommon_dma(mActor_name_t ftr_name, u8* data);

static aFTR_vtable_c aHnwCommon_func = {
	&aHnwCommon_ct,
	&aHnwCommon_mv,
	&aHnwCommon_dw,
	&aHnwCommon_dt,
	&aHnwCommon_dma,
};

aFTR_PROFILE iam_hnw_common = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	27.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	aFTR_INTERACTION_HANIWA,
	&aHnwCommon_func,
};
