static void fIJT_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fIJT_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fIJT_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fIJT_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fIJT_func = {
	&fIJT_ct,
	&fIJT_mv,
	&fIJT_dw,
	&fIJT_dt,
	NULL,
};

aFTR_PROFILE iam_ike_jny_truth01 = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	15.7f,
	0.01f,
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
	0,
	0,
	0,
	0,
	&fIJT_func,
};
