static void fIJHOUI_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fIJHOUI_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fIJHOUI_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fIJHOUI_func = {
	&fIJHOUI_ct,
	&fIJHOUI_mv,
	&fIJHOUI_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_ike_jny_houi01 = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	40.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	2,
	0,
	0,
	&fIJHOUI_func,
};
