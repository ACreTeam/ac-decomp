static void fYMF_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        if (ftr_actor->switch_changed_flag == TRUE) {
            sAdo_OngenTrgStart(0x17B, &ftr_actor->position);
        }
    }
}

extern u16 int_yaz_mario_flower_a_pal[];
extern u16 int_yaz_mario_flower_b_pal[];
extern u16 int_yaz_mario_flower_c_pal[];
extern u16 int_yaz_mario_flower_d_pal[];

static u16* fYMF_palette_table[] = {
    int_yaz_mario_flower_a_pal,
    int_yaz_mario_flower_b_pal,
    int_yaz_mario_flower_c_pal,
    int_yaz_mario_flower_d_pal,
};

extern Gfx int_yaz_mario_flower_hana_model[];
extern Gfx int_yaz_mario_flower_body_model[];

static void fYMF_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    u32 ctr_ofs;

    if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
        ctr_ofs = play->game_frame;
    } else {
        ctr_ofs = game->frame_counter;
    }

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_9, fYMF_palette_table[(ctr_ofs / 20) & 3]);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_yaz_mario_flower_hana_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_yaz_mario_flower_body_model);

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fYMF_func = {
    NULL, &fYMF_mv, &fYMF_dw, NULL, NULL,
};

aFTR_PROFILE iam_yaz_mario_flower = {
    // clang-format off
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
	&fYMF_func,
    // clang-format on
};
