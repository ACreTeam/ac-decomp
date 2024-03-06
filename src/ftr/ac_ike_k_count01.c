extern Gfx int_ike_k_count01_body_model[];

static void fIKC_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fIKC_func = {
    NULL, &fIKC_mv, NULL, NULL, NULL,
};

aFTR_PROFILE iam_ike_k_count01 = {
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
};
