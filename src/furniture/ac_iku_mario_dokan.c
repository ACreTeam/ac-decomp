extern Gfx int_iku_mario_dokan_model_a_model[];
extern Gfx int_iku_mario_dokan_model_b_model[];

static void fIMD_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        if (ftr_actor->switch_changed_flag == TRUE) {
            sAdo_OngenTrgStart(0x178, &ftr_actor->position);
        }
    }
}

static aFTR_vtable_c fIMD_func = {
    NULL, &fIMD_mv, NULL, NULL, NULL,
};

aFTR_PROFILE iam_iku_mario_dokan = {
    // clang-format off
    int_iku_mario_dokan_model_a_model,
    int_iku_mario_dokan_model_b_model,
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
    1,
    0,
    0,
    &fIMD_func,
    // clang-format on
};
