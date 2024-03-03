static void fHF_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fHF_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fHF_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fHF_dt(FTR_ACTOR* ftr_actor, u8* data);
static void fHF_dma(mActor_name_t ftr_name, u8* data);

static aFTR_vtable_c fHF_func = {
	&fHF_ct,
	&fHF_mv,
	&fHF_dw,
	&fHF_dt,
	&fHF_dma,
};

aFTR_PROFILE iam_hayakawa_famicom = {
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
	aFTR_INTERACTION_FAMICOM,
	&fHF_func,
};
