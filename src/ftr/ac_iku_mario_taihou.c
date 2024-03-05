extern Gfx int_iku_mario_taihou_model[];

static void fIMT_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        if (ftr_actor->switch_changed_flag == TRUE) {
            aMR_contact_info_c* contact_info = aMR_GetContactInfoLayer1();

            switch (contact_info->contact_direction) {
                case aMR_CONTACT_DIR_BACK:
                    (*Common_Get(clip).effect_clip->effect_make_proc)(eEC_EFFECT_KILLER, ftr_actor->position, 2,
                                                                      ftr_actor->s_angle_y, game, RSV_NO, 0, 0);
                    break;
                case aMR_CONTACT_DIR_FRONT:
                    (*Common_Get(clip).effect_clip->effect_make_proc)(eEC_EFFECT_KILLER, ftr_actor->position, 2,
                                                                      ftr_actor->s_angle_y + DEG2SHORT_ANGLE(180.0f),
                                                                      game, RSV_NO, 0, 0);
                    break;
            }
        }
    }
}

static aFTR_vtable_c fIMT_func = {
    NULL, &fIMT_mv, NULL, NULL, NULL,
};

aFTR_PROFILE iam_iku_mario_taihou = {
    // clang-format off
    int_iku_mario_taihou_model,
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
    &fIMT_func,
    // clang-format on
};
