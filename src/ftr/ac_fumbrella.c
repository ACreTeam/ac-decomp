static void aFU_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aFU_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aFU_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aFU_dt(FTR_ACTOR* ftr_actor, u8* data);
static void aFU_dma(mActor_name_t ftr_name, u8* data);

static aFTR_vtable_c aFU_func = {
	&aFU_ct,
	&aFU_mv,
	&aFU_dw,
	&aFU_dt,
	&aFU_dma,
};

aFTR_PROFILE iam_fumbrella = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	30.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	aFTR_INTERACTION_UMBRELLA,
	&aFU_func,
};
