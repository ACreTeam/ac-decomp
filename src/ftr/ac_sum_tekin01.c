extern Gfx int_sum_tekin01_onT_model[];
static void aSumTekin01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumTekin01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumTekin01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumTekin01_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aSumTekin01_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumTekin01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        Common_Get(clip).my_room_clip->sound_melody_proc(ftr_actor, my_room_actor, 5);
    }
}

static void aSumTekin01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumTekin01_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumTekin01_func = {
	&aSumTekin01_ct,
	&aSumTekin01_mv,
	&aSumTekin01_dw,
	&aSumTekin01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_tekin01 = {
	int_sum_tekin01_onT_model,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	18.0f,
	0.01f,
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
	0,
	0,
	0,
	0,
	&aSumTekin01_func,
};
