extern Gfx int_sum_viola01_on_model[];
extern Gfx int_sum_viola01_onT_model[];
static void aSumViola01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumViola01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumViola01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumViola01_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aSumViola01_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumViola01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        Common_Get(clip).my_room_clip->sound_melody_proc(ftr_actor, my_room_actor, 11);
    }
}

void aSumViola01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumViola01_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumViola01_func = {
	&aSumViola01_ct,
	&aSumViola01_mv,
	&aSumViola01_dw,
	&aSumViola01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_viola01 = {
	int_sum_viola01_on_model,
	int_sum_viola01_onT_model,
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
	&aSumViola01_func,
};
