extern Gfx int_ike_k_count01_body_model[];

#define fIKC_MIN_TIME (f32)(20 + GETREG(TAKREG, 72))
#define fIKC_MAX_TIME (f32)(40 + GETREG(TAKREG, 73))

static void fIKC_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        if (ftr_actor->dynamic_work_s[0] < 0) {
            xyz_t pos = ftr_actor->position;

            pos.y += 13.0f;
            (*Common_Get(clip).effect_clip->effect_make_proc)(eEC_EFFECT_SOBA_YUGE, pos, 1, 0, game, RSV_NO, 6, 0);

            ftr_actor->dynamic_work_s[0] = (int)(fIKC_MIN_TIME + RANDOM_F(fIKC_MAX_TIME - fIKC_MIN_TIME));
        } else {
            ftr_actor->dynamic_work_s[0]--;
        }
    }
}

static aFTR_vtable_c fIKC_func = {
    NULL, &fIKC_mv, NULL, NULL, NULL,
};

aFTR_PROFILE iam_ike_k_count01 = {
    // clang-format off
    int_ike_k_count01_body_model,
    NULL,
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
    &fIKC_func,
    // clang-format on
};
