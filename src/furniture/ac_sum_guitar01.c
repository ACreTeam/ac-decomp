extern Gfx int_sum_guitar01_on_model[];
extern Gfx int_sum_guitar01_onT_model[];
static void aSumGuitar01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumGuitar01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumGuitar01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumGuitar01_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aSumGuitar01_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumGuitar01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        Common_Get(clip).my_room_clip->sound_melody_proc(ftr_actor, my_room_actor, 0);
    }
}

static void aSumGuitar01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumGuitar01_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumGuitar01_func = {
	&aSumGuitar01_ct,
	&aSumGuitar01_mv,
	&aSumGuitar01_dw,
	&aSumGuitar01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_guitar01 = {
	int_sum_guitar01_on_model,
	int_sum_guitar01_onT_model,
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
	&aSumGuitar01_func,
};
