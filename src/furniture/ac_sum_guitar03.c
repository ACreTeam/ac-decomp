extern Gfx int_sum_guitar_03_on_model[];
extern Gfx int_sum_guitar_03_onT_model[];
static void aSumGuitar03_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumGuitar03_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumGuitar03_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumGuitar03_dt(FTR_ACTOR* ftr_actor, u8* data);


static void aSumGuitar03_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumGuitar03_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        Common_Get(clip).my_room_clip->sound_melody_proc(ftr_actor, my_room_actor, 2);
    }
}

static void aSumGuitar03_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumGuitar03_dt(FTR_ACTOR* ftr_actor, u8* data) {
}


static aFTR_vtable_c aSumGuitar03_func = {
	&aSumGuitar03_ct,
	&aSumGuitar03_mv,
	&aSumGuitar03_dw,
	&aSumGuitar03_dt,
	NULL,
};

aFTR_PROFILE iam_sum_guitar03 = {
	int_sum_guitar_03_on_model,
	int_sum_guitar_03_onT_model,
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
	&aSumGuitar03_func,
};
