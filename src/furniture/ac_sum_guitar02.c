extern Gfx int_sum_guitar02_on_model[];
extern Gfx int_sum_guitar02_onT_model[];
static void aSumGuitar02_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumGuitar02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumGuitar02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumGuitar02_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aSumGuitar02_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumGuitar02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        Common_Get(clip).my_room_clip->sound_melody_proc(ftr_actor, my_room_actor, 1);
    }
}

static void aSumGuitar02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumGuitar02_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumGuitar02_func = {
	&aSumGuitar02_ct,
	&aSumGuitar02_mv,
	&aSumGuitar02_dw,
	&aSumGuitar02_dt,
	NULL,
};

aFTR_PROFILE iam_sum_guitar02 = {
	int_sum_guitar02_on_model,
	int_sum_guitar02_onT_model,
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
	&aSumGuitar02_func,
};
