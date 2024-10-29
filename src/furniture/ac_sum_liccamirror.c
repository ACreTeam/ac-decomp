extern Gfx int_sum_liccamirror_on_model[];
extern Gfx int_sum_liccamirror_onT_model[];
extern Gfx int_sum_liccamirror_env_model[];

static void aSumLiccaMirror_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim(game->graph);
    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_sum_liccamirror_env_model);

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c aSumLiccaMirror_func = {
    NULL, NULL, &aSumLiccaMirror_dw, NULL, NULL,
};

aFTR_PROFILE iam_sum_liccamirror = {
    // clang-format off
    int_sum_liccamirror_on_model,
    int_sum_liccamirror_onT_model,
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
    1,
    0,
    0,
    &aSumLiccaMirror_func,
    // clang-format on
};
