extern Gfx int_sum_piano01_on_model[];
extern Gfx int_sum_piano01_onT_model[];
static void aSumPiano01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumPiano01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumPiano01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumPiano01_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aSumPiano01_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumPiano01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        Common_Get(clip).my_room_clip->sound_melody_proc(ftr_actor, my_room_actor, 8);
    }
}

static void aSumPiano01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumPiano01_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumPiano01_func = {
	&aSumPiano01_ct,
	&aSumPiano01_mv,
	&aSumPiano01_dw,
	&aSumPiano01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_piano01 = {
	int_sum_piano01_on_model,
	int_sum_piano01_onT_model,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	18.0f,
	0.01f,
	aFTR_SHAPE_TYPEC,
	mCoBG_FTR_TYPEC,
	0,
	0,
	0,
	0,
	&aSumPiano01_func,
};
