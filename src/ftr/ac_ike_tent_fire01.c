static void fITF_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fITF_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fITF_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fITF_func = {
	&fITF_ct,
	&fITF_mv,
	&fITF_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_ike_tent_fire01 = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	41.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&fITF_func,
};
