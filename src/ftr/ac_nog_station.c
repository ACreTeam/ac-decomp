static void fNSN_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fNSN_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNSN_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNSN_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fNSN_func = {
	&fNSN_ct,
	&fNSN_mv,
	&fNSN_dw,
	&fNSN_dt,
	NULL,
};

aFTR_PROFILE iam_nog_station = {
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
	&fNSN_func,
};
