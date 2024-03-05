static void fNLM_ct(FTR_ACTOR* ftr_actor, u8* data) {
    ftr_actor->dynamic_work_f[0] = 0.0f;
}

static void fNLM_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    aMR_contact_info_c* contact_info = aMR_GetContactInfoLayer1();
    f32 grass_alpha = 0.0f;

    /* If pushed from the back and floor is backyard lawn or daisy meadow, show grass being cut */
    if ((Common_Get(floor_idx) == FLOOR_NPC026 || Common_Get(floor_idx) == FLOOR_NPC048) && contact_info != NULL) {
        switch (ftr_actor->state) {
            case aFTR_STATE_WAIT_PUSH:
            case aFTR_STATE_WAIT_PUSH2:
            case aFTR_STATE_WAIT_PUSH3:
            case aFTR_STATE_PUSH:
                if (contact_info->contact_direction == aMR_CONTACT_DIR_BACK) {
                    grass_alpha = 1.0f;
                }
                break;
        }
    }

    if (grass_alpha != ftr_actor->dynamic_work_f[0]) {
        add_calc(&ftr_actor->dynamic_work_f[0], grass_alpha, 0.04f, 0.1f, 0.001f);
    }
}

extern Gfx int_nog_lawnmower_bodyT_model[];
extern Gfx int_nog_lawnmower_grass_model[];

static void fNLM_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    Gfx* scroll_gfx;
    u8 grass_alpha = (u8)(ftr_actor->dynamic_work_f[0] * 255.0f);

    scroll_gfx = fFTR_GetTwoTileGfx(16, 16, 0, 0, 16, 16, 0, 10, play, ftr_actor, 0);

    if (scroll_gfx != NULL) {
        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_OPA_DISP, int_nog_lawnmower_bodyT_model);
        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, scroll_gfx);
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 120, 255, 180, grass_alpha);
        gSPDisplayList(NEXT_POLY_XLU_DISP, int_nog_lawnmower_grass_model);

        CLOSE_DISP(game->graph);
    }
}

static aFTR_vtable_c fNLM_func = {
    &fNLM_ct, &fNLM_mv, &fNLM_dw, NULL, NULL,
};

aFTR_PROFILE iam_nog_lawnmower = {
    // clang-format off
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	40.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&fNLM_func,
    // clang-format on
};
