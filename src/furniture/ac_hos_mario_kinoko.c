extern Gfx int_hos_mario_kinoko_all_model[];

static void fIMK_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        if (ftr_actor->switch_changed_flag == TRUE) {
            sAdo_OngenTrgStart(SE_SINGLETON(0x179), &ftr_actor->position);
        }
    }
}

static aFTR_vtable_c fIMK_func = {
    NULL, &fIMK_mv, NULL, NULL, NULL,
};

aFTR_PROFILE iam_hos_mario_kinoko = {
    // clang-format off
	int_hos_mario_kinoko_all_model,
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
	&fIMK_func,
    // clang-format on
};
