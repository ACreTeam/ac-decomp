static void aIkeJnyRosia01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aIkeJnyRosia01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aIkeJnyRosia01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aIkeJnyRosia01_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aIkeJnyRosia01_func = {
	&aIkeJnyRosia01_ct,
	&aIkeJnyRosia01_mv,
	&aIkeJnyRosia01_dw,
	&aIkeJnyRosia01_dt,
	NULL,
};

aFTR_PROFILE iam_ike_jny_rosia01 = {
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
	&aIkeJnyRosia01_func,
};
