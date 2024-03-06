extern Gfx int_tak_noise_on_model[];
extern Gfx int_tak_noise_onT_model[];

static void fTNM_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        if (ftr_actor->switch_changed_flag == TRUE) {
            sAdo_OngenTrgStart(0x46A, &ftr_actor->position);
        }
    }
}

static aFTR_vtable_c fTNM_func = {
    NULL, &fTNM_mv, NULL, NULL, NULL,
};

aFTR_PROFILE iam_tak_noise = {
    // clang-format off
	int_tak_noise_on_model,
	int_tak_noise_onT_model,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	15.7f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&fTNM_func,
    // clang-format on
};
