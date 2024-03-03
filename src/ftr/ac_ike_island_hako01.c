static void fIIH_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fIIH_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fIIH_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fIIH_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fIIH_func = {
	&fIIH_ct,
	&fIIH_mv,
	&fIIH_dw,
	&fIIH_dt,
	NULL,
};

aFTR_PROFILE iam_ike_island_hako01 = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	15.7f,
	0.009f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	1,
	0,
	aFTR_INTERACTION_START_DISABLED,
	&fIIH_func,
};
