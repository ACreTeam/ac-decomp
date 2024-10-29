static void fGI_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void fGI_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    // nothing
}

static void fGI_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

extern Gfx obj_net2T_gfx_model[];
extern Gfx obj_net2T_mat_model[];

extern Gfx obj_axe2T_gfx_model[];
extern Gfx obj_axe2T_mat_model[];

extern Gfx obj_shovel2T_gfx_model[];
extern Gfx obj_shovel2T_mat_model[];

extern Gfx obj_rod2T_gfx_model[];
extern Gfx obj_rod2T_mat_model[];

extern Gfx obj_rod2_lineT_gfx_model[];
extern Gfx obj_rod2_lineT_mat_model[];

static Gfx* fGI_mat_table[] = {
    obj_net2T_mat_model,
    obj_axe2T_mat_model,
    obj_shovel2T_mat_model,
    obj_rod2_lineT_mat_model,
};

static Gfx* fGI_gfx_table[] = {
    obj_net2T_gfx_model,
    obj_axe2T_gfx_model,
    obj_shovel2T_gfx_model,
    obj_rod2_lineT_gfx_model,
};

static void fGI_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    int tool_idx = (ftr_actor->name - 0x44F) & 3;

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, fGI_mat_table[tool_idx]);
    gSPDisplayList(NEXT_POLY_OPA_DISP, fGI_gfx_table[tool_idx]);

    if (ftr_actor->name == 0x452) {
        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_XLU_DISP, obj_rod2T_mat_model);
        gSPDisplayList(NEXT_POLY_XLU_DISP, obj_rod2T_gfx_model);
    }

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fGI_func = {
    &fGI_ct, &fGI_mv, &fGI_dw, &fGI_dt, NULL,
};

aFTR_PROFILE iam_gold_item = {
    // clang-format off
	NULL,
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
	&fGI_func,
    // clang-format on
};
