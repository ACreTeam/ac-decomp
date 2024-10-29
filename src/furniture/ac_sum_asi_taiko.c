extern Gfx int_sum_asi_taiko_on_model[];
extern Gfx int_sum_asi_taiko_onT_model[];
static void aSumasitaiko_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumasitaiko_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumasitaiko_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumasitaiko_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aSumasitaiko_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumasitaiko_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        Common_Get(clip).my_room_clip->sound_melody_proc(ftr_actor, my_room_actor, 12);
    }
}

static void aSumasitaiko_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumasitaiko_dt(FTR_ACTOR* ftr_actor, u8* data) {
}


static aFTR_vtable_c aSumasitaiko_func = {
	&aSumasitaiko_ct,
	&aSumasitaiko_mv,
	&aSumasitaiko_dw,
	&aSumasitaiko_dt,
	NULL,
};

aFTR_PROFILE iam_sum_asi_taiko = {
	int_sum_asi_taiko_on_model,
	int_sum_asi_taiko_onT_model,
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
	&aSumasitaiko_func,
};
