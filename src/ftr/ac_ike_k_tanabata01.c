static void fITN_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fITN_func = {
	NULL,
	NULL,
	&fITN_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_ike_k_tanabata01 = {
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
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&fITN_func,
};
