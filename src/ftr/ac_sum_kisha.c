static void aSumKisha_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumKisha_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumKisha_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumKisha_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumKisha_func = {
	&aSumKisha_ct,
	&aSumKisha_mv,
	&aSumKisha_dw,
	&aSumKisha_dt,
	NULL,
};

aFTR_PROFILE iam_sum_kisha = {
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
	aFTR_SHAPE_TYPEC,
	mCoBG_FTR_TYPEC,
	0,
	0,
	0,
	0,
	&aSumKisha_func,
};
