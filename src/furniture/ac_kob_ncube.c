extern Gfx int_kob_ncube_on_model[];
extern Gfx int_kob_ncube_onT_model[];
static void aKobNcube_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKobNcube_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKobNcube_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKobNcube_dt(FTR_ACTOR* ftr_actor, u8* data);


static void aKobNcube_ct(FTR_ACTOR* ftr_actor, u8* data){

}

static void aKobNcube_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){

}

static void aKobNcube_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){

}

static void aKobNcube_dt(FTR_ACTOR* ftr_actor, u8* data){

}

static aFTR_vtable_c aKobNcube_func = {
	&aKobNcube_ct,
	&aKobNcube_mv,
	&aKobNcube_dw,
	&aKobNcube_dt,
	NULL,
};

aFTR_PROFILE iam_kob_ncube = {
	int_kob_ncube_on_model,
	int_kob_ncube_onT_model,
	NULL,
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
	&aKobNcube_func,
};
