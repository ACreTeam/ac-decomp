extern Gfx int_iku_mario_koura_model[];

static void fIMKoura_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        if (ftr_actor->switch_changed_flag == TRUE) {
            sAdo_OngenTrgStart(0x464, &ftr_actor->position);
        }
    }
}

static aFTR_vtable_c fIMKoura_func = {
    NULL, &fIMKoura_mv, NULL, NULL, NULL,
};

aFTR_PROFILE iam_iku_mario_koura = {
    // clang-format off
	int_iku_mario_koura_model,
	NULL,
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
	&fIMKoura_func,
    // clang-format on
};
