static int fNM2_GetPalletIndex(FTR_ACTOR* ftr_actor) {
    if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
        mActor_name_t field_id = mFI_GetFieldId();

        if (Save_Get(scene_no) == SCENE_COTTAGE_MY) {
            return 0;
        }

        if (mFI_GET_TYPE(field_id) == mFI_FIELD_PLAYER0_ROOM) {
            int arrange_idx = mFI_GetFieldId() - mFI_FIELD_PLAYER0_ROOM;

            return Save_Get(homes[arrange_idx & 3]).outlook_pal;
        }
    } else {
        int player_no = Common_Get(player_no);

        if (player_no >= 0 && player_no < PLAYER_NUM) {
            int arrange_idx = mHS_get_arrange_idx(player_no);

            return Save_Get(homes[arrange_idx]).outlook_pal;
        }
    }

    return 0;
}

static void fNM2_ct(FTR_ACTOR* ftr_actor, u8* data) {
    int pallet_idx = fNM2_GetPalletIndex(ftr_actor);

    ftr_actor->pal_p = (u16*)zelda_malloc_align(16 * sizeof(u16), 32);
    fFTR_MorphHousepaletteCt(ftr_actor->pal_p, fFTR_myhome_off_pal_table[pallet_idx],
                             fFTR_myhome_on_pal_table[pallet_idx], ftr_actor);
}

static void fNM2_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    int pallet_idx = fNM2_GetPalletIndex(ftr_actor);

    fFTR_MorphHousePalette(ftr_actor->pal_p, fFTR_myhome_off_pal_table[pallet_idx],
                           fFTR_myhome_on_pal_table[pallet_idx], ftr_actor);
}

static void fNM2_dt(FTR_ACTOR* ftr_actor, u8* data) {
    if (ftr_actor->pal_p != NULL) {
        zelda_free(ftr_actor->pal_p);
    }
}

extern Gfx int_nog_myhome2_on_model[];
extern Gfx int_nog_myhome2_onT_model[];
extern Gfx int_nog_myhome2_off_model[];

static void fNM2_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    u16* pal_p = ftr_actor->pal_p;

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, pal_p);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_nog_myhome2_on_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_nog_myhome2_off_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_nog_myhome2_onT_model);

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fNM2_func = {
    &fNM2_ct, &fNM2_mv, &fNM2_dw, &fNM2_dt, NULL,
};

aFTR_PROFILE iam_nog_myhome2 = {
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
	aFTR_INTERACTION_TOGGLE,
	&fNM2_func,
    // clang-format on
};
