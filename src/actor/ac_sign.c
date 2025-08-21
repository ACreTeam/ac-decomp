#include "ac_sign.h"

#include "m_common_data.h"
#include "m_debug.h"
#include "m_skin_matrix.h"
#include "libultra/libultra.h"
#include "m_player_lib.h"
#include "m_msg.h"
#include "m_choice.h"
#include "m_needlework_ovl.h"
#include "sys_matrix.h"
#include "m_rcp.h"

enum {
    aSIGN_ACTION_WAIT,
    aSIGN_ACTION_TALK,
    aSIGN_ACTION_TALK_END,
    aSIGN_ACTION_MENU_OPEN_WAIT,
    aSIGN_ACTION_MENU_END_WAIT,
    aSIGN_ACTION_SINGLE_BIRTH,
    aSIGN_ACTION_SINGLE_ERASE,

    aSIGN_ACTION_NUM
};

extern Vtx obj_kanban_shadow_v[];
extern Gfx obj_kanban_shadowT_model[];

static u8 aSIGN_shadow_vtx_fix_flg_table[] = { TRUE, FALSE, FALSE, TRUE };
static bIT_ShadowData_c aSIGN_shadow_data = {
    ARRAY_COUNT(aSIGN_shadow_vtx_fix_flg_table),
    aSIGN_shadow_vtx_fix_flg_table,
    50.0f,
    obj_kanban_shadow_v,
    obj_kanban_shadowT_model,
};

static void aSIGN_actor_ct(ACTOR* actorx, GAME* game);
static void aSIGN_actor_dt(ACTOR* actorx, GAME* game);
static void aSIGN_actor_move(ACTOR* actorx, GAME* game);
static void aSIGN_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Ac_Sign_Profile = {
    mAc_PROFILE_AC_SIGN,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_AC_SIGN,
    sizeof(SIGN_ACTOR),
    &aSIGN_actor_ct,
    &aSIGN_actor_dt,
    &aSIGN_actor_move,
    &aSIGN_actor_draw,
    NULL,
};
// clang-format on

static void aSIGN_setup_action(SIGN_ACTOR* sign, int action);
static void aSIGN_change_my_original(SIGN_ACTOR* sign, GAME* game, u16 design_no);
static void aSIGN_single_birth(SIGN_ACTOR* sign, GAME* game);
static void aSIGN_single_erase(SIGN_ACTOR* sign, GAME* game);

static void aSIGN_actor_ct(ACTOR* actorx, GAME* game) {
    SIGN_ACTOR* sign = (SIGN_ACTOR*)actorx;

    Common_Get(clip).sign_control_actor = sign;
    sign->is_winter = Common_Get(time.season) == mTM_SEASON_WINTER;
    aSIGN_setup_action(sign, aSIGN_ACTION_WAIT);
}

static void aSIGN_actor_dt(ACTOR* actorx, GAME* game) {
    Common_Get(clip).sign_control_actor = NULL;
}

static int aSIGN_no_cull_check(GAME_PLAY* play, int bz, int bx, int ut_z, int ut_x) {
    xyz_t center_pos;
    xyz_t clip_pos;
    f32 w;
    f32 max_dist = aSIGN_CULL_MAX_DIST;

    if (GETREG(NMREG, 5)) {
        max_dist = GETREG(NMREG, 5);
    }

    /* Get the world space of the unit */
    mFI_BkandUtNum2CenterWpos(&center_pos, bx, bz, ut_x, ut_z);
    center_pos.y = mFI_UNIT_BASE_SIZE_F + mCoBG_GetBgY_OnlyCenter_FromWpos2(center_pos, 0.0f);

    /* Transform world space to clip space */
    Skin_Matrix_PrjMulVector(&play->projection_matrix, &center_pos, &clip_pos, &w);

    /* Test that the clip space is within the camera bounds */
    if (clip_pos.z > -max_dist) {
        f32 inv_w = (w < 1.0f) ? 1.0f : (1.0f / w);

        if (inv_w * (fabsf(clip_pos.x) - max_dist) < 1.0f && inv_w * (fabsf(clip_pos.y) - max_dist) < 1.0f) {
            return TRUE;
        }
    }

    return FALSE;
}

static int aSIGN_no_cull_talk_area(GAME_PLAY* play, int bz, int bx, int ut_z, int ut_x) {
    xyz_t center_pos;

    mFI_BkandUtNum2CenterWpos(&center_pos, bx, bz, ut_x, ut_z);
    if (Camera2_CheckEnterCullingArea(center_pos.x, center_pos.z, 65.0f) == FALSE) {
        return TRUE;
    }

    return FALSE;
}

static int aSIGN_draw_anime_check(SIGN_ACTOR* sign, int ut_z, int ut_x) {
    int i;

    for (i = 0; i < aSIGN_SINGLE_NUM; i++) {
        if (sign->single[i].exist_flag && sign->single[i].unit.z == ut_z && sign->single[i].unit.x == ut_x) {
            return TRUE;
        }
    }

    return FALSE;
}

static void aSIGN_draw_set(SIGN_ACTOR* sign, aSIGN_draw_c* draw, GAME_PLAY* play, int bz, int bx, int base_ut_z,
                           int base_ut_x) {
    mActor_name_t* fg_p = mFI_BkNumtoUtFGTop(bx, bz);
    int ut_z;
    int ut_x;
    int ut_z_max = 5;
    int ut_x_max = 7;

    if (GETREG(NMREG, 2)) {
        ut_z_max = GETREG(NMREG, 2);
    }

    if (GETREG(NMREG, 3)) {
        ut_x_max = GETREG(NMREG, 3);
    }

    draw->block.z = bz;
    draw->block.x = bx;

    if (fg_p != NULL) {

        for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
            u16 ut_x_bitfield = 0;
            u16 x_bit = 1;

            for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                int ut_z_local = base_ut_z - ut_z;
                int ut_x_local = base_ut_x - ut_x;

                ut_z_local = ABS(ut_z_local);
                ut_x_local = ABS(ut_x_local);

                if (ITEM_NAME_GET_TYPE(*fg_p) == NAME_TYPE_ITEM0 && ITEM_NAME_GET_CAT(*fg_p) == ITEM0_CAT_SIGN) {
                    if (aSIGN_draw_anime_check(sign, ut_z, ut_x) == FALSE) {
                        if ((ut_z_local <= ut_z_max && ut_x_local <= ut_z_max) ||
                            (ut_z_local <= ut_x_max && ut_x_local <= ut_x_max &&
                             aSIGN_no_cull_check(play, bz, bx, ut_z, ut_x))) {
                            if (Camera2_CheckCullingMode()) {
                                if (aSIGN_no_cull_talk_area(play, bz, bx, ut_z, ut_x)) {
                                    ut_x_bitfield |= x_bit;
                                }
                            } else {
                                ut_x_bitfield |= x_bit;
                            }
                        }
                    }
                }

                x_bit <<= 1;
                fg_p++;
            }

            draw->exist_bitfield[ut_z] = ut_x_bitfield;
        }
    }
}

static void aSIGN_actor_set_draw(SIGN_ACTOR* sign, GAME* game) {
    xyz_t* camera_center_pos_p = Camera2_getCenterPos_p();
    int bz_max = mFI_GetBlockZMax();
    int bx_max = mFI_GetBlockXMax();
    int bz0;
    int bx0;
    xyz_t pos;
    int ut_z;
    int ut_x;
    int t_bz;
    int t_bx;
    int bz;
    int bx;
    int base_ut_z;
    int base_ut_x;
    int t_base_ut_z;
    int t_base_ut_x;
    int i;
    int j;
    aSIGN_draw_c* draw_p;

    for (i = 0, draw_p = sign->draw; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            bzero(draw_p->exist_bitfield, sizeof(draw_p->exist_bitfield));
            draw_p++;
        }
    }

    pos = *camera_center_pos_p;
    if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_DOOR) {
        pos.z -= mFI_UT_WORLDSIZE_Z_F;
    }

    if (GETREG(NMREG, 4)) {
        pos.z -= (f32)GETREG(NMREG, 4);
    } else {
        pos.z -= 2 * mFI_UT_WORLDSIZE_Z_F;
    }

    if (mFI_Wpos2BkandUtNuminBlock(&bx0, &bz0, &ut_x, &ut_z, pos)) {
        if (ut_z < (UT_Z_NUM / 2)) {
            t_bz = bz0 - 1;
            t_base_ut_z = ut_z + UT_Z_NUM;
        } else {
            t_bz = bz0;
            t_base_ut_z = ut_z;
        }

        if (ut_x < (UT_X_NUM / 2)) {
            t_bx = bx0 - 1;
            t_base_ut_x = ut_x + UT_X_NUM;
        } else {
            t_bx = bx0;
            t_base_ut_x = ut_x;
        }

        bz = t_bz;
        base_ut_z = t_base_ut_z;
        for (i = 0, draw_p = sign->draw; i < 2; i++) {
            bx = t_bx;
            base_ut_x = t_base_ut_x;
            for (j = 0; j < 2; j++) {
                if (bz >= 0 && bz < bz_max && bx >= 0 && bx < bx_max) {
                    aSIGN_draw_set(sign, draw_p, (GAME_PLAY*)game, bz, bx, base_ut_z, base_ut_x);
                }

                bx++;
                base_ut_x -= UT_X_NUM;
                draw_p++;
            }

            bz++;
            base_ut_z -= UT_Z_NUM;
        }
    }
}

static int aSIGN_actor_BkandUtNum_formal(int* bz_p, int* bx_p, int* ut_z_p, int* ut_x_p) {
    int bz_max = mFI_GetBlockZMax();
    int bx_max = mFI_GetBlockXMax();

    if (*ut_z_p < 0) {
        (*ut_z_p) += UT_Z_NUM;
        (*bz_p)--;
    } else if (*ut_z_p >= UT_Z_NUM) {
        (*ut_z_p) -= UT_Z_NUM;
        (*bz_p)++;
    }

    if (*ut_x_p < 0) {
        (*ut_x_p) += UT_X_NUM;
        (*bx_p)--;
    } else if (*ut_x_p >= UT_X_NUM) {
        (*ut_x_p) -= UT_X_NUM;
        (*bx_p)++;
    }

    return *bz_p >= 0 && *bz_p < bz_max && *bx_p >= 0 && *bx_p < bx_max;
}

static int aSIGN_actor_set_target(SIGN_ACTOR* sign, GAME* game) {
    xyz_t sign_pos;
    int base_bz;
    int base_bx;
    int base_ut_z;
    int base_ut_x;
    int bz;
    int bx;
    int ut_z;
    int ut_x;
    ACTOR* player_actor = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    f32 min_dist = FLT_MAX;
    int z;
    int x;
    int i;
    int j;
    aSIGN_draw_c* draw_p;
    int res = FALSE;

    if (mFI_Wpos2BkandUtNuminBlock(&base_bx, &base_bz, &base_ut_x, &base_ut_z, player_actor->world.position)) {

        for (z = -1; z < 1; z++) {

            for (x = -1; x < 2; x++) {
                bz = base_bz;
                bx = base_bx;
                ut_x = base_ut_x + x;
                ut_z = base_ut_z + z;

                if (aSIGN_actor_BkandUtNum_formal(&bz, &bx, &ut_z, &ut_x)) {
                    for (i = 0, draw_p = sign->draw; i < 2; i++) {
                        for (j = 0; j < 2; j++) {
                            if (draw_p->block.z == bz && draw_p->block.x == bx &&
                                (draw_p->exist_bitfield[ut_z] & (1 << ut_x)) != 0) {
                                mFI_BkandUtNum2CenterWpos(&sign_pos, bx, bz, ut_x, ut_z);
                                sign_pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(sign_pos, 0.0f);
                                if (player_actor->world.position.z > sign_pos.z) {
                                    s16 angle_y = search_position_angleY(&sign_pos, &player_actor->world.position);
                                    int abs_angle_y = ABS(angle_y);

                                    if (abs_angle_y < DEG2SHORT_ANGLE2(45.0f)) {
// TODO: fakematch? Why do these differ?
#if VERSION == VER_GAFU01_00
                                        s16 d_angle_y =
                                            (s16)(angle_y + DEG2SHORT_ANGLE2(180.0f)) - player_actor->shape_info.rotation.y;
#else
                                            s16 d_angle_y =
                                                (angle_y + DEG2SHORT_ANGLE2(180.0f)) - player_actor->shape_info.rotation.y;
#endif
                                        s16 diff_angle_y = ABS(d_angle_y);

                                        if (diff_angle_y <= DEG2SHORT_ANGLE2(68.83483f)) {
                                            f32 dist_sq = Math3DLengthSquare(&player_actor->world.position, &sign_pos);

                                            if (dist_sq < SQ(55.0f) && dist_sq < min_dist) {
                                                res = TRUE;
                                                min_dist = dist_sq;
                                                sign->sign_pos.x = sign_pos.x;
                                                sign->sign_pos.y = sign_pos.y;
                                                sign->sign_pos.z = sign_pos.z;
                                                sign->target_block.z = bz;
                                                sign->target_block.x = bx;
                                                sign->target_unit.z = ut_z;
                                                sign->target_unit.x = ut_x;
                                                xyz_t_move(&sign->target_pos, &sign_pos);
                                            }
                                        }
                                    }
                                }
                            }

                            draw_p++;
                        }
                    }
                }
            }
        }
    }

    return res;
}

static ACTOR* aSIGN_search_exist_npc_inCircle_forSign(GAME* game, const xyz_t* pos_p, f32 max_dist) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    Actor_info* actor_info_p = &play->actor_info;
    ACTOR* actor = actor_info_p->list[ACTOR_PART_NPC].actor;
    f32 x = pos_p->x;
    f32 z = pos_p->z;

    for (actor; actor != NULL; actor = actor->next_actor) {
        f32 dist = Math3DVecLengthSquare2D(actor->world.position.x - x, actor->world.position.z - z);

        if (dist < max_dist) {
            NPC_ACTOR* npc_actor = (NPC_ACTOR*)actor;

            if (npc_actor->condition_info.hide_flg == FALSE) {
                return actor;
            }
        }
    }

    actor = actor_info_p->list[ACTOR_PART_BG].actor;
    for (actor; actor != NULL; actor = actor->next_actor) {
        if (actor->id == mAc_PROFILE_PSNOWMAN) {
            f32 dist = Math3DVecLengthSquare2D(actor->world.position.x - x, actor->world.position.z - z);

            if (dist < max_dist) {
                return actor;
            }
        }
    }

    return NULL;
}

static int aSIGN_single_anime_check(aSIGN_single_c* single_p, xyz_t pos) {
    int bz;
    int bx;
    int ut_z;
    int ut_x;

    mFI_Wpos2BkandUtNuminBlock(&bx, &bz, &ut_x, &ut_z, pos);
    if (single_p->block.x == bx && single_p->block.z == bz && single_p->unit.x == ut_x && single_p->unit.z == ut_z) {
        return TRUE;
    }

    return FALSE;
}

extern int aSIGN_set_white_sign(GAME* game, xyz_t* pos_p) {
    SIGN_ACTOR* sign = Common_Get(clip).sign_control_actor;
    int no_free_single = TRUE;
    ACTOR* actor_in_circle;
    int i;

    if (sign == NULL) {
        return FALSE;
    }

    actor_in_circle = aSIGN_search_exist_npc_inCircle_forSign(game, pos_p, 20.0f);
    if (actor_in_circle != NULL) {
        return FALSE;
    }

    for (i = 0; i < aSIGN_SINGLE_NUM; i++) {
        if (sign->single[i].exist_flag == FALSE) {
            no_free_single = FALSE;
            break;
        }
    }

    if (no_free_single) {
        return FALSE;
    }

    sign->sign_birth_pos = *pos_p;
    sAdo_OngenTrgStart(NA_SE_ITEM_HORIDASHI, &sign->sign_birth_pos);
    aSIGN_setup_action(sign, aSIGN_ACTION_SINGLE_BIRTH);
    return TRUE;
}

extern int aSIGN_erase_white_sign(GAME* game, xyz_t* pos_p) {
    SIGN_ACTOR* sign = Common_Get(clip).sign_control_actor;
    int i;

    if (sign == NULL) {
        return FALSE;
    }

    for (i = 0; i < aSIGN_SINGLE_NUM; i++) {
        aSIGN_single_c* single = &sign->single[i];

        if (single->exist_flag != 0) {
            /* Check if a sign is already being erected here */
            if (aSIGN_single_anime_check(single, *pos_p) != FALSE) {
                return FALSE;
            }
        } else {
            mActor_name_t* fg_p = mFI_GetUnitFG(*pos_p);

            single->scale.x = 0.0099f;
            single->scale.y = 0.0099f;
            single->scale.z = 0.0099f;

            mFI_Wpos2BkandUtNuminBlock(&single->block.x, &single->block.z, &single->unit.x, &single->unit.z, *pos_p);
            single->exist_flag = 2;
            single->item = *fg_p;
        }
    }

    aSIGN_setup_action(sign, aSIGN_ACTION_WAIT);
    return TRUE;
}

static void aSIGN_set_talk_info(ACTOR* actorx) {
    int player_no = Common_Get(player_no);
    rgba_t window_color;

    if (player_no < PLAYER_NUM) {
        if (GETREG(NMREG, 90)) {
            mDemo_Set_msg_num(MSG_12389);
        } else {
            mDemo_Set_msg_num(MSG_12388);
        }
    } else {
        mDemo_Set_msg_num(MSG_12389);
    }

    mDemo_Set_talk_display_name(FALSE);
    mDemo_Set_ListenAble();
    window_color.r = 185;
    window_color.g = 60;
    window_color.b = 40;
    window_color.a = 255;
    mDemo_Set_talk_window_color(&window_color);
    mDemo_Set_camera(CAMERA2_PROCESS_NORMAL);
    mDemo_Set_use_zoom_sound(TRUE);
}

static void aSIGN_talk(SIGN_ACTOR* sign, GAME* game) {
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();

    if (mDemo_Check(mDemo_TYPE_SPEAK, &sign->actor_class)) {
        ACTOR* player_actor = GET_PLAYER_ACTOR_GAME_ACTOR(game);
        s_xyz player_angle = player_actor->shape_info.rotation;
        s16 target_y = search_position_angleY(&player_actor->world.position, &sign->target_pos);

        add_calc_short_angle2(&player_angle.y, target_y, 0.3f, DEG2SHORT_ANGLE2(22.5f), DEG2SHORT_ANGLE2(1.40625f));
        GET_PLAYER_ACTOR_NOW()->Set_force_position_angle_proc(gamePT, NULL, &player_angle,
                                                              mPlayer_FORCE_POSITION_ANGLE_ROTY);

        if (mMsg_Check_MainNormalContinue(msg_p) == TRUE) {
            switch (mChoice_GET_CHOSENUM()) {
                case mChoice_CHOICE0:
                    mMsg_REQUEST_MAIN_DISAPPEAR_WAIT_TYPE1();
                    aSIGN_setup_action(sign, aSIGN_ACTION_MENU_OPEN_WAIT);
                    break;
                case mChoice_CHOICE1:
                default:
                    mMsg_REQUEST_MAIN_DISAPPEAR_WAIT_TYPE1();
                    aSIGN_setup_action(sign, aSIGN_ACTION_TALK_END);
                    break;
            }
        }
    } else {
        aSIGN_setup_action(sign, aSIGN_ACTION_WAIT);
    }
}

static void aSIGN_talk_end(SIGN_ACTOR* sign, GAME* game) {
    if (mMsg_CHECK_MAIN_WAIT()) {
        aSIGN_setup_action(sign, aSIGN_ACTION_WAIT);
        mMsg_request_main_forceoff();
    }
}

static void aSIGN_wait(SIGN_ACTOR* sign, GAME* game) {
    if (mDemo_Get_talk_actor() == NULL && aSIGN_actor_set_target(sign, game) && chkTrigger(BUTTON_A) &&
        mDemo_Get_talk_actor() == NULL) {
        mDemo_Request(mDemo_TYPE_SPEAK, &sign->actor_class, &aSIGN_set_talk_info);
        aSIGN_setup_action(sign, aSIGN_ACTION_TALK);
    }
}

static void aSIGN_menu_open_wait(SIGN_ACTOR* sign, GAME* game) {
    u32 player_no = Common_Get(player_no);
    GAME_PLAY* play = (GAME_PLAY*)game;
    Submenu* submenu_p = &play->submenu;

    if (mMsg_CHECK_MAIN_WAIT()) {

        mSM_open_submenu(submenu_p, mSM_OVL_NEEDLEWORK, mNW_OPEN_DESIGN, player_no);
        aSIGN_setup_action(sign, aSIGN_ACTION_MENU_END_WAIT);
        mMsg_request_main_forceoff();
    }
}

static void aSIGN_menu_end_wait(SIGN_ACTOR* sign, GAME* game) {
    u32 player_no = Common_Get(player_no);
    GAME_PLAY* play = (GAME_PLAY*)game;
    Submenu* submenu_p = &play->submenu;

    if (submenu_p->open_flag == FALSE && mMsg_CHECK_NOT_SERIES_MAIN_WAIT() == TRUE) {
        Submenu_Item_c* sm_item_p = submenu_p->item_p;

        if (sm_item_p->item == RSV_NO) {
            int img_no = mNW_get_image_no(submenu_p, sm_item_p->slot_no);
            img_no += player_no * mPr_ORIGINAL_DESIGN_COUNT;

            aSIGN_change_my_original(sign, game, img_no);
            aSIGN_setup_action(sign, aSIGN_ACTION_WAIT);
        } else {
            aSIGN_setup_action(sign, aSIGN_ACTION_WAIT);
        }
    }
}

static void aSIGN_setup_action(SIGN_ACTOR* sign, int action) {
    // clang-format off
    static aSIGN_ACTION_PROC process[] = {
        &aSIGN_wait,
        &aSIGN_talk,
        &aSIGN_talk_end,
        &aSIGN_menu_open_wait,
        &aSIGN_menu_end_wait,
        &aSIGN_single_birth,
        &aSIGN_single_erase,
    };
    // clang-format on

    sign->action_proc = process[action];
}

static void aSIGN_change_my_original(SIGN_ACTOR* sign, GAME* game, u16 design_no) {
    mActor_name_t* fg_p = mFI_GetUnitFG(sign->sign_pos);

    if (ITEM_IS_SIGNBOARD(*fg_p)) {
        mFI_SetFG_common(SIGNBOARD_START + design_no, sign->sign_pos, TRUE);
        sAdo_OngenTrgStart(NA_SE_461, &sign->sign_pos);
    }
}

static void aSIGN_single_birth(SIGN_ACTOR* sign, GAME* game) {
    ACTOR* player_actor = GET_PLAYER_ACTOR_GAME_ACTOR(game); // unused
    xyz_t sign_birth_pos = sign->sign_birth_pos;
    int i;

    for (i = 0; i < aSIGN_SINGLE_NUM; i++) {
        if (sign->single[i].exist_flag != 0) {
            if (aSIGN_single_anime_check(&sign->single[i], sign_birth_pos)) {
                aSIGN_setup_action(sign, aSIGN_ACTION_WAIT);
                return;
            }
        } else {
            mActor_name_t* fg_p = mFI_GetUnitFG(sign_birth_pos); // unused

            sign->single[i].item = SIGNBOARD;
            sign->single[i].scale.x = 0.0001f;
            sign->single[i].scale.y = 0.0001f;
            sign->single[i].scale.z = 0.0001f;
            mFI_Wpos2BkandUtNuminBlock(&sign->single[i].block.x, &sign->single[i].block.z, &sign->single[i].unit.x,
                                       &sign->single[i].unit.z, sign_birth_pos);
            sign->single[i].exist_flag = 1;
            sign->single[i]._24 = 0;
            sign->single[i]._20 = 0.005f;
            sign->single[i]._26 = 6000;

            aSIGN_setup_action(sign, aSIGN_ACTION_WAIT);
            mFI_BkandUtNum2CenterWpos(&sign_birth_pos, sign->single[i].block.x, sign->single[i].block.z,
                                      sign->single[i].unit.x, sign->single[i].unit.z);
            mFI_SetFG_common(RSV_SIGNBOARD, sign_birth_pos, TRUE);
            mCoBG_RegistDecalCircle(&sign_birth_pos, 16.0f, 19.0f, 36);
            return;
        }
    }

    aSIGN_setup_action(sign, aSIGN_ACTION_WAIT);
}

static void aSIGN_single_erase(SIGN_ACTOR* sign, GAME* game) {
    ACTOR* player_actor = GET_PLAYER_ACTOR_GAME_ACTOR(game); // unused
    xyz_t sign_birth_pos = sign->sign_birth_pos;
    int i;

    for (i = 0; i < aSIGN_SINGLE_NUM; i++) {
        aSIGN_single_c* single = &sign->single[i];

        if (single->exist_flag != 0) {
            if (aSIGN_single_anime_check(single, sign_birth_pos)) {
                aSIGN_setup_action(sign, aSIGN_ACTION_WAIT);
                return;
            }
        } else {
            mActor_name_t* fg_p = mFI_GetUnitFG(sign_birth_pos);

            single->scale.x = 0.0099f;
            single->scale.y = 0.0099f;
            single->scale.z = 0.0099f;
            mFI_Wpos2BkandUtNuminBlock(&single->block.x, &single->block.z, &single->unit.x, &single->unit.z,
                                       sign_birth_pos);
            single->exist_flag = 2;
            single->item = *fg_p;

            aSIGN_setup_action(sign, aSIGN_ACTION_WAIT);
            return;
        }
    }

    aSIGN_setup_action(sign, aSIGN_ACTION_WAIT);
}

static void aSIGN_single_all_check(SIGN_ACTOR* sign) {
    s16 prev_angle;
    s16 now_angle;
    xyz_t* scale_p;
    int i;

    for (i = 0; i < aSIGN_SINGLE_NUM; i++) {
        if (sign->single[i].exist_flag != 0) {
            f32 wobble;

            if (sign->single[i].exist_flag == 1) {

                prev_angle = sign->single[i]._24;
                sign->single[i]._24 = prev_angle + sign->single[i]._26;
                now_angle = sign->single[i]._24;
                sign->single[i].scale.y = sign->single[i]._20 * sinf_table((f32)now_angle * 0.0000958738f);
                sign->single[i].scale.x = 0.01f - sign->single[i].scale.y;
                sign->single[i].scale.y += 0.01f;
                sign->single[i].scale.z = sign->single[i].scale.x;

                if ((prev_angle < 0 && now_angle >= 0) || (prev_angle < -0x8000 && now_angle >= -0x8000)) {
                    sign->single[i]._20 *= 0.4f;
                    sign->single[i]._26 += 750;
                }
            }

            if (sign->single[i].exist_flag == 2) {
                scale_p = &sign->single[i].scale;
                add_calc(&scale_p->x, 0.0f, 0.5f, 0.0006f, 0.001f);
                add_calc(&scale_p->y, 0.0f, 0.5f, 0.0006f, 0.001f);
                add_calc(&scale_p->z, 0.0f, 0.5f, 0.0006f, 0.001f);
            }

            // wobble = ABS(sign->single[i]._20);
            if (ABS(sign->single[i]._20) < 0.0002f && sign->single[i].exist_flag == 1) {
                xyz_t center_pos;

                mFI_BkandUtNum2CenterWpos(&center_pos, sign->single[i].block.x, sign->single[i].block.z,
                                          sign->single[i].unit.x, sign->single[i].unit.z);
                mFI_SetFG_common(SIGNBOARD_END, center_pos, TRUE);
                sign->single[i].exist_flag = 0;
            }

            if (sign->single[i].scale.x <= 0.0f && sign->single[i].exist_flag == 2) {
                xyz_t center_pos;

                mFI_BkandUtNum2CenterWpos(&center_pos, sign->single[i].block.x, sign->single[i].block.z,
                                          sign->single[i].unit.x, sign->single[i].unit.z);
                center_pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(center_pos, 0.0f); // unused??
                sign->single[i].exist_flag = 0;
            }
        }
    }
}

static void aSIGN_random_set(void);
static void aSIGN_all_clear(void);

static void aSIGN_actor_move(ACTOR* actorx, GAME* game) {
    SIGN_ACTOR* sign = (SIGN_ACTOR*)actorx;

    (*sign->action_proc)(sign, game);
    aSIGN_single_all_check(sign);
    aSIGN_actor_set_draw(sign, game);

    if (GETREG(NMREG, 1)) {
        int type = GETREG(NMREG, 0);

        if (type == 1000 || type == 100) {
            aSIGN_random_set();
            SETREG(NMREG, 0, 0);
        }

        if (GETREG(NMREG, 0) == 10) {
            aSIGN_all_clear();
            SETREG(NMREG, 0, 0);
        }
    }
}

static void aSIGN_random_set(void) {
    mActor_name_t* fg_p;
    int ut_z;
    int ut_x;
    int bz;
    int bx;
    int bx_max = mFI_GetBlockXMax();
    int bz_max = mFI_GetBlockZMax();

    for (bz = 0; bz < bz_max; bz++) {

        for (bx = 0; bx < bx_max; bx++) {
            fg_p = mFI_BkNumtoUtFGTop(bx, bz);
            for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
                for (ut_x = 0; ut_x < UT_X_NUM; ut_x++, fg_p++) {
                    if (*fg_p == TREE && GETREG(NMREG, 0) == 1000) {
                        mFI_UtNumtoFGSet_common(SIGNBOARD_START + (qrand() >> 27), bx * UT_X_NUM + ut_x,
                                                bz * UT_Z_NUM + ut_z, TRUE);
                    } else if (*fg_p == EMPTY_NO && GETREG(NMREG, 0) == 100) {
                        if ((ut_z & 1) != 0 && (ut_x & 1) != 0) {
                            mFI_UtNumtoFGSet_common(SIGNBOARD_START + (u16)(qrand() >> 27), bx * UT_X_NUM + ut_x,
                                                    bz * UT_Z_NUM + ut_z, TRUE);
                        }
                    }
                }
            }
        }
    }
}

static void aSIGN_all_clear(void) {
    mActor_name_t* fg_p;
    int ut_z;
    int ut_x;
    int bz;
    int bx;
    int bx_max = mFI_GetBlockXMax();
    int bz_max = mFI_GetBlockZMax();

    for (bz = 0; bz < bz_max; bz++) {
        for (bx = 0; bx < bx_max; bx++) {
            fg_p = mFI_BkNumtoUtFGTop(bx, bz);
            for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
                for (ut_x = 0; ut_x < UT_X_NUM; ut_x++, fg_p++) {
                    if (*fg_p >= SIGNBOARD_START && *fg_p < (SIGNBOARD_END + 1)) {
                        mFI_UtNumtoFGSet_common(EMPTY_NO, bx * UT_X_NUM + ut_x, bz * UT_Z_NUM + ut_z, TRUE);
                    }
                }
            }
        }
    }
}

static void aSIGN_draw_shadow(GAME* game, bIT_ShadowData_c* shadow_data);

extern u8 hakushi_tex[];
extern u16 hakushi_pal[];
extern Gfx write_model[];
extern Gfx obj_sign_s_model[];
extern Gfx obj_sign_w_model[];

static void aSIGN_single_all_draw(SIGN_ACTOR* sign, GAME* game) {
    static Gfx* mdl[] = { obj_sign_s_model, obj_sign_w_model };

    GRAPH* graph = game->graph;
    int i;

    _texture_z_light_fog_prim_npc(graph);

    OPEN_DISP(graph);
    gDPSetTextureAdjustMode(NEXT_POLY_OPA_DISP, G_TA_DOLPHIN);
    CLOSE_DISP(graph);

    for (i = 0; i < aSIGN_SINGLE_NUM; i++) {
        if (sign->single[i].exist_flag != 0) {
            xyz_t sign_pos;
            u32 player_no;
            int my_original_idx;
            u16* pal_p;
            u8* tex_p;

            Matrix_push();
            mFI_BkandUtNum2CenterWpos(&sign_pos, sign->single[i].block.x, sign->single[i].block.z,
                                      sign->single[i].unit.x, sign->single[i].unit.z);
            sign_pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(sign_pos, 0.0f);
            player_no = (sign->single[i].item >> 3) & 3;
            my_original_idx = sign->single[i].item & 7;

            Matrix_translate(sign_pos.x, sign_pos.y, sign_pos.z - 1.0f, MTX_LOAD);
            Matrix_scale(sign->single[i].scale.x, sign->single[i].scale.y, sign->single[i].scale.z, MTX_MULT);

            OPEN_POLY_OPA_DISP(graph);

            if ((sign->single[i].item >> 5) & 1) {
                pal_p = hakushi_pal;
                tex_p = hakushi_tex;
            } else {
                pal_p = mNW_PaletteIdx2Palette(Save_Get(private_data[player_no]).my_org[my_original_idx].palette);
                tex_p = Save_Get(private_data[player_no]).my_org[my_original_idx].design.data;
            }

            gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, pal_p);
            gSPSegment(POLY_OPA_DISP++, ANIME_2_TXT_SEG, tex_p);
            gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, write_model);
            gSPDisplayList(POLY_OPA_DISP++, mdl[sign->is_winter]);

            CLOSE_POLY_OPA_DISP(graph);

            aSIGN_draw_shadow(game, &aSIGN_shadow_data);
            Matrix_pull();
        }
    }

    OPEN_DISP(graph);
    gDPSetTextureAdjustMode(NEXT_POLY_OPA_DISP, G_TA_N64);
    CLOSE_DISP(graph);
}

static void aSIGN_actor_draw(ACTOR* actorx, GAME* game) {
    static Gfx* mdl[] = { obj_sign_s_model, obj_sign_w_model };

    GRAPH* graph = game->graph;
    SIGN_ACTOR* sign = (SIGN_ACTOR*)actorx;
    MtxF* mtxf = get_Matrix_now();
    mActor_name_t* fg_p;
    int ut_z;
    int ut_x;
    int i;
    int j;
    aSIGN_draw_c* draw_p;
    u16 exist_bitfield;
    u16 ut_bit;

    aSIGN_single_all_draw(sign, game);
    _texture_z_light_fog_prim_npc(graph);

    draw_p = sign->draw;

    OPEN_DISP(graph);
    gDPSetTextureAdjustMode(NEXT_POLY_OPA_DISP, G_TA_DOLPHIN);
    CLOSE_DISP(graph);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            fg_p = mFI_BkNumtoUtFGTop(draw_p->block.x, draw_p->block.z);
            for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
                exist_bitfield = draw_p->exist_bitfield[ut_z];

                if (exist_bitfield == 0) {
                    fg_p += UT_X_NUM;
                } else {
                    for (ut_x = 0, ut_bit = 1; ut_x < UT_X_NUM; ut_x++) {
                        if ((exist_bitfield & ut_bit) != 0) {
                            mActor_name_t item = *fg_p;

                            if (ITEM_NAME_GET_TYPE(item) == NAME_TYPE_ITEM0 &&
                                ITEM_NAME_GET_CAT(item) == ITEM0_CAT_SIGN) {
                                xyz_t sign_pos;
                                u32 player_no;
                                int my_original_idx;
                                u16* pal_p;
                                u8* tex_p;

                                mFI_BkandUtNum2CenterWpos(&sign_pos, draw_p->block.x, draw_p->block.z, ut_x, ut_z);
                                sign_pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(sign_pos, 0.0f);

                                player_no = (item >> 3) & 3;
                                my_original_idx = item & 7;

                                OPEN_POLY_OPA_DISP(graph);

                                /* Copy sign position to world matrix translation */
                                mtxf->mf[3][0] = sign_pos.x;
                                mtxf->mf[3][1] = sign_pos.y;
                                mtxf->mf[3][2] = sign_pos.z;

                                if ((item >> 5) & 1) {
                                    pal_p = hakushi_pal;
                                    tex_p = hakushi_tex;
                                } else {
                                    pal_p = mNW_PaletteIdx2Palette(
                                        Save_Get(private_data[player_no]).my_org[my_original_idx].palette);
                                    tex_p = Save_Get(private_data[player_no]).my_org[my_original_idx].design.data;
                                }

                                gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, pal_p);
                                gSPSegment(POLY_OPA_DISP++, ANIME_2_TXT_SEG, tex_p);
                                gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph),
                                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                                gSPDisplayList(POLY_OPA_DISP++, write_model);
                                gSPDisplayList(POLY_OPA_DISP++, mdl[sign->is_winter]);

                                CLOSE_POLY_OPA_DISP(graph);

                                /* Draw shadow behind the sign */
                                mtxf->mf[3][0] = sign_pos.x;
                                mtxf->mf[3][1] = sign_pos.y;
                                mtxf->mf[3][2] = sign_pos.z - 1.0f;
                                aSIGN_draw_shadow(game, &aSIGN_shadow_data);
                            }
                        }

                        ut_bit <<= 1;
                        fg_p++;
                    }
                }
            }

            draw_p++;
        }
    }

    OPEN_DISP(graph);
    gDPSetTextureAdjustMode(NEXT_POLY_OPA_DISP, G_TA_N64);
    CLOSE_DISP(graph);
}

static void aSIGN_copy_vtx(Vtx* dst, Vtx* src, u32 n_vtx, u8* vtx_fix_flg_table, int fix_ofs) {
    int i;

    for (i = 0; i != n_vtx; i++) {
        *dst = *src;

        if (*vtx_fix_flg_table == TRUE) {
            dst->v.ob[0] = src->v.ob[0] + fix_ofs;
        } else {
            dst->v.ob[0] = src->v.ob[0];
        }

        src++;
        dst++;
        vtx_fix_flg_table++;
    }
}

static void aSIGN_draw_shadow(GAME* game, bIT_ShadowData_c* shadow_data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    GRAPH* graph = game->graph;
    Vtx* vtx = (Vtx*)GRAPH_ALLOC_TYPE(graph, Vtx, shadow_data->vtx_num);
    rgba_t color;
    u8 l;
    u8 r;
    u8 g;
    u8 b;
    u8 a;

    if (vtx != NULL) {
        aSIGN_copy_vtx(vtx, shadow_data->vtx, shadow_data->vtx_num, shadow_data->vtx_fix_flags,
                       play->kankyo.shadow_pos * shadow_data->size);
    } else {
        vtx = shadow_data->vtx;
    }

    OPEN_SHADOW_DISP(graph);

    gDPPipeSync(SHADOW_DISP++);
    gSPMatrix(SHADOW_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(SHADOW_DISP++, ANIME_3_TXT_SEG, vtx);
    l = play->kankyo.shadow_alpha;
    r = play->kankyo.base_light.shadow_color[0];
    g = play->kankyo.base_light.shadow_color[1];
    b = play->kankyo.base_light.shadow_color[2];
    a = play->kankyo.shadow_alpha;
    gDPSetPrimColor(SHADOW_DISP++, 0, l, r, g, b, a);
    gSPDisplayList(SHADOW_DISP++, shadow_data->gfx);

    CLOSE_SHADOW_DISP(graph);
}
