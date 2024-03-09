extern Gfx int_sum_x_piano_on_model[];
extern Gfx int_sum_x_piano_onT_model[];
static void aSumX_Piano_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumX_Piano_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumX_Piano_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumX_Piano_dt(FTR_ACTOR* ftr_actor, u8* data);

void aSumX_Piano_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumX_Piano_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    Common_Get(clip).my_room_clip->sound_melody_proc(ftr_actor, my_room_actor, 8);
}

void aSumX_Piano_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

void aSumX_Piano_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumX_Piano_func = {
	&aSumX_Piano_ct,
	&aSumX_Piano_mv,
	&aSumX_Piano_dw,
	&aSumX_Piano_dt,
	NULL,
};

aFTR_PROFILE iam_sum_x_piano = {
	int_sum_x_piano_on_model,
	int_sum_x_piano_onT_model,
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
	&aSumX_Piano_func,
};
