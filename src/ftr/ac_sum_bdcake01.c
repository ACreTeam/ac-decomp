extern u8 int_sum_bdcake01_a_candol1_TA_tex_txt[];
extern u8 int_sum_bdcake01_a_candol2_TA_tex_txt[];

extern u8 int_sum_bdcake01_b_candol1_TA_tex_txt[];
extern u8 int_sum_bdcake01_b_candol2_TA_tex_txt[];

extern Gfx int_sum_bdcake01_on_model[];
extern Gfx int_sum_bdcake01_off_model[];
extern Gfx int_sum_bdcake01_off1_model[];

static void aSB_SumBdcake01Draw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    s16 frame = ftr_actor->dynamic_work_s[0] & 1;

    OPEN_DISP(game->graph);

    if (frame == 0) {
        gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, int_sum_bdcake01_a_candol2_TA_tex_txt);
        gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_9, int_sum_bdcake01_b_candol1_TA_tex_txt);
    } else {
        gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, int_sum_bdcake01_a_candol1_TA_tex_txt);
        gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_9, int_sum_bdcake01_b_candol2_TA_tex_txt);
    }

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_XLU_DISP, int_sum_bdcake01_on_model);
    gSPDisplayList(NEXT_POLY_XLU_DISP, int_sum_bdcake01_off1_model);
    gSPDisplayList(NEXT_POLY_XLU_DISP, int_sum_bdcake01_off_model);

    CLOSE_DISP(game->graph);
}

static void aSB_SumBdcake01Move(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    ftr_actor->dynamic_work_s[0]++;
}

static void aSB_SumBdcake01Ct(FTR_ACTOR* ftr_actor, u8* data) {
    ftr_actor->dynamic_work_s[0] = 0;
}

static aFTR_vtable_c sum_bdcake01_func = {
    &aSB_SumBdcake01Ct, &aSB_SumBdcake01Move, &aSB_SumBdcake01Draw, NULL, NULL,
};

aFTR_PROFILE iam_sum_bdcake01 = {
    NULL,
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
    &sum_bdcake01_func,
};
