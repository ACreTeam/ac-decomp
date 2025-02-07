#include "ac_museum_insect_priv.h"

ACTOR_PROFILE Museum_Insect_Profile = {
    mAc_PROFILE_MUSEUM_INSECT,
    ACTOR_PART_BG,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_408,
    sizeof(MUSEUM_INSECT_ACTOR),
    Museum_Insect_Actor_ct,
    Museum_Insect_Actor_dt,
    Museum_Insect_Actor_move,
    Museum_Insect_Actor_draw,
    NULL,
};

MUSEUM_INSECT_ACTOR* MI_Control_Actor;

int Museum_Insect_GetMsgNo(ACTOR* actorx) {
    static u8 item_name[mIN_ITEM_NAME_LEN];
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    int insect_caught_by = actor->_2F80[actor->_2F7C].insectInfo;
    s16 insect_no = ITM_INSECT_START + actor->_2F80[actor->_2F7C].insectName;
    int msgNo;
    mIN_copy_name_str(item_name, insect_no);
    mMsg_Set_item_str_art(mMsg_Get_base_window_p(), mMsg_ITEM_STR0, item_name, ARRAY_COUNT(item_name),
                          mIN_get_item_article(insect_no));

    if (insect_caught_by >= 1 && insect_caught_by <= 4) {
        mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR0,
                          common_data.save.save.private_data[insect_caught_by - 1].player_ID.player_name, 8);
    }

    if (actor->_2F7C < actor->_2F78 - 1) {
        if (insect_caught_by >= 1 && insect_caught_by <= 4) {
            msgNo = 0x2fa2;
        } else {
            msgNo = 0x2fa3;
        }
    } else {
        if (insect_caught_by >= 1 && insect_caught_by <= 4) {
            msgNo = 0x2f9f;
        } else {
            msgNo = 0x2fa0;
        }
    }

    return msgNo;
}

int Museum_Insect_Check_Talk_Distance(GAME* game, int i) {
    static xyz_t kanban_pos[6] = { { 140.f, 40.f, 60.f },  { 420.f, 40.f, 60.f },  { 220.f, 40.f, 300.f },
                                   { 380.f, 40.f, 300.f }, { 180.f, 40.f, 540.f }, { 340.f, 40.f, 540.f } };
    GAME_PLAY* play = (GAME_PLAY*)game;
    xyz_t p;
    PLAYER_ACTOR* player_actor = get_player_actor_withoutCheck(play);
    s16 newAngle = player_actor->actor_class.world.angle.y + DEG2SHORT_ANGLE(-180);
    xyz_t_sub(&player_actor->actor_class.world.position, &kanban_pos[i], &p);

    if (ABS(p.x) < 20.f && ABS(p.z) < 20.f && ABS(newAngle) < DEG2SHORT_ANGLE(67.5f)) {
        return TRUE;
    }
    return FALSE;
}

void Museum_Insect_Set_MsgInsectInfo(ACTOR* actorx, int groupNum) {
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    int i;
    static int group_max_num[6] = { 7, 6, 6, 6, 7, 7 };
    static int group_1_insect_name[7] = { 22, 4, 21, 29, 38, 20, 7 };
    static int group_2_insect_name[6] = { 31, 30, 19, 5, 23, 6 };
    static int group_3_insect_name[6] = { 0, 25, 26, 1, 27, 2 };
    static int group_4_insect_name[6] = { 32, 34, 37, 3, 24, 39 };
    static int group_5_insect_name[7] = { 35, 8, 33, 9, 10, 11, 12 };
    static int group_6_insect_name[7] = { 15, 16, 18, 17, 13, 14, 36 };
    static int* group_insect_name[6] = { group_1_insect_name, group_2_insect_name, group_3_insect_name,
                                         group_4_insect_name, group_5_insect_name, group_6_insect_name };
    actor->_2F78 = 0;
    actor->_2F7C = 0;
    for (i = 0; i < group_max_num[groupNum]; i++) {
        s16 insectName = group_insect_name[groupNum][i];
        s16 s = mMmd_InsectInfo(insectName);
        if (s) {
            actor->_2F80[actor->_2F78].insectName = insectName;
            actor->_2F80[actor->_2F78].insectInfo = s;
            actor->_2F78++;
        }
    }
}

void Museum_Insect_set_talk_info(ACTOR* actorx) {
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    int x;
    if (actor->_2F78 > 0) {
        x = Museum_Insect_GetMsgNo(actorx);
        actor->_2F7C++;
    } else {
        x = 0x2fa1;
    }
    mDemo_Set_talk_window_color(&window_color);
    mDemo_Set_msg_num(x);
    mDemo_Set_talk_display_name(FALSE);
    mDemo_Set_ListenAble();
    mDemo_Set_camera(CAMERA2_PROCESS_NORMAL);
    mDemo_Set_use_zoom_sound(TRUE);
}

void Museum_Insect_Talk_process(ACTOR* actorx, GAME* game) {
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    if (mDemo_Check(mDemo_TYPE_SPEAK, actorx)) {
        s_xyz rot = get_player_actor_withoutCheck((GAME_PLAY*)game)->actor_class.shape_info.rotation;
        add_calc_short_angle2(&rot.y, DEG2SHORT_ANGLE(-180), 0.3f, DEG2SHORT_ANGLE(22.5), DEG2SHORT_ANGLE(0));
        get_player_actor_withoutCheck((GAME_PLAY*)gamePT)
            ->Set_force_position_angle_proc(gamePT, NULL, &rot, mPlayer_FORCE_POSITION_ANGLE_ROTY);
        if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p())) {
            int choice = mChoice_Get_ChoseNum(mChoice_Get_base_window_p());
            if (choice != -1) {
                if (choice == 0) {
                    int msgNum = Museum_Insect_GetMsgNo(actorx);
                    actor->_2F7C++;
                    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), msgNum);
                    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
                } else {
                    mMsg_Set_CancelNormalContinue(mMsg_Get_base_window_p());
                    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
                }
            }
        }
    } else if (chkTrigger(BUTTON_A) && !mDemo_Get_talk_actor()) {
        int i;
        for (i = 0; i < 6; i++) {
            if (Museum_Insect_Check_Talk_Distance(game, i)) {
                Museum_Insect_Set_MsgInsectInfo(actorx, i);
                mDemo_Request(mDemo_TYPE_SPEAK, actorx, Museum_Insect_set_talk_info);
            }
        }
    }
}

void Museum_Insect_Actor_ct(ACTOR* actorx, GAME* game) {
    int i;
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    MI_Control_Actor = actor;
    for (i = 0; i < 5; i++) {
        actor->_2F9C[i] = 0;
    }
    for (i = 0; i < aINS_INSECT_TYPE_NUM; i++) {
        if (mMmd_InsectInfo(i)) {
            actor->privInsects[i]._8C |= 1;
            actor->privInsects[i]._00 = i;
            actor->privInsects[i]._14 = minsect_scale_tbl[i];
            set_relax_active_time(&actor->privInsects[i], game);
            minsect_ct[i](&actor->privInsects[i], game);
        }
    }
}

void Museum_Insect_Actor_dt(ACTOR* actor, GAME* game) {
    return;
}

void Museum_Insect_Actor_move(ACTOR* actorx, GAME* game) {
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    int i;
    actor->actor.world.position.y = 4000.f;
    Museum_Insect_Talk_process(actorx, game);
    for (i = 0; i < aINS_INSECT_TYPE_NUM; i++) {
        if (actor->privInsects[i]._8C & 1) {
            minsect_mv[i](&actor->privInsects[i], game);
        }
    }
}

extern EVW_ANIME_DATA obj_museum4_water_evw_anime;
extern Gfx obj_museum4_water_modelT[];

void Museum_Insect_Actor_draw(ACTOR* actorx, GAME* game) {
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    GRAPH* graph;
    int i;
    _texture_z_light_fog_prim_xlu(game->graph);
    Evw_Anime_Set((GAME_PLAY*)game, &obj_museum4_water_evw_anime);
    graph = game->graph;
    Matrix_translate(100.0f, 0.0f, 0.0f, FALSE);
    Matrix_scale(0.01f, 0.01f, 0.01f, TRUE);
    OPEN_DISP(graph);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_XLU_DISP, obj_museum4_water_modelT);
    CLOSE_DISP(graph);
    for (i = 0; i < aINS_INSECT_TYPE_NUM; i++) {
        if (actor->privInsects[i]._8C & 1) {
            if (GETREG(TAKREG, 0) == i + 1) {
                actor->privInsects[i]._14 = (GETREG(TAKREG, 1) * 0.0001f) + minsect_scale_tbl[i];
            }
            minsect_dw[i](&actor->privInsects[i], game);
            if (GETREG(TAKREG, 0) == i + 1) {
                actor->privInsects[i]._14 = minsect_scale_tbl[i];
            }
        }
    }
}

#include "../src/actor/ac_museum_insect_base.c_inc"
