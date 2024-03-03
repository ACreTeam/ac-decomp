static void aMyfmanekin_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aMyfmanekin_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aMyfmanekin_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aMyfmanekin_dt(FTR_ACTOR* ftr_actor, u8* data);
static void aMyfmanekin_dma(mActor_name_t ftr_name, u8* data);

static aFTR_vtable_c aMyfmanekin_func = {
	&aMyfmanekin_ct,
	&aMyfmanekin_mv,
	&aMyfmanekin_dw,
	&aMyfmanekin_dt,
	&aMyfmanekin_dma,
};

aFTR_PROFILE iam_myfmanekin = {
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
	aFTR_INTERACTION_MANNEKIN,
	&aMyfmanekin_func,
};
