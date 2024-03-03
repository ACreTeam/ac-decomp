static void fITF02_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fITF02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fITF02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fITF02_func = {
	&fITF02_ct,
	&fITF02_mv,
	&fITF02_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_ike_tent_fire02 = {
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
	aFTR_SHAPE_TYPEC,
	mCoBG_FTR_TYPEC,
	0,
	0,
	0,
	0,
	&fITF02_func,
};
