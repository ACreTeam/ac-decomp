extern Gfx int_kob_mastersword_onT_model[];
extern Gfx int_kob_mastersword_on_model[];
extern Gfx int_kob_mastersword_onT_model[];
static void aKobMasterSword_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKobMasterSword01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aKobMasterSword01_func = {
	NULL,
	&aKobMasterSword_mv,
	&aKobMasterSword01_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_kob_mastersword = {
	int_kob_mastersword_onT_model,
	int_kob_mastersword_on_model,
	int_kob_mastersword_onT_model,
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
	0,
	&aKobMasterSword01_func,
};
