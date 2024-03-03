static void aMFU_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aMFU_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aMFU_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aMFU_dt(FTR_ACTOR* ftr_actor, u8* data);
static void aMFU_dma(mActor_name_t ftr_name, u8* data);

static aFTR_vtable_c aMFU_func = {
	&aMFU_ct,
	&aMFU_mv,
	&aMFU_dw,
	&aMFU_dt,
	&aMFU_dma,
};

aFTR_PROFILE iam_myfumbrella = {
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
	&aMFU_func,
};
