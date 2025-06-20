#include "ac_museum_fossil.h"

#include "m_camera2.h"
#include "m_demo.h"
#include "m_name_table.h"
#include "m_museum_display.h"
#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_player_lib.h"
#include "m_room_type.h"
#include "m_msg.h"
#include "m_common_data.h"

typedef struct {
    s16 x;
    s16 z;
} aMF_pos_c;

typedef struct {
    aMF_pos_c pos;
    int direct;
} aMF_fossil_data_c;

static void Museum_Fossil_Actor_ct(ACTOR* actorx, GAME* game);
static void Museum_Fossil_Actor_dt(ACTOR* actorx, GAME* game);
static void Museum_Fossil_Actor_move(ACTOR* actorx, GAME* game);
static void Museum_Fossil_Actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Museum_Fossil_Profile = {
    mAc_PROFILE_MUSEUM_FOSSIL,
    ACTOR_PART_BG,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(MUSEUM_FOSSIL_ACTOR),
    &Museum_Fossil_Actor_ct,
    &Museum_Fossil_Actor_dt,
    &Museum_Fossil_Actor_move,
    &Museum_Fossil_Actor_draw,
    NULL,
};

static aMF_fossil_data_c aMF_fossil_data_table[mMmd_FOSSIL_NUM] = {
    { 6, 3, mRmTp_DIRECT_SOUTH },  { 2, 3, mRmTp_DIRECT_SOUTH },   { 4, 3, mRmTp_DIRECT_SOUTH },
    { 9, 3, mRmTp_DIRECT_SOUTH },  { 13, 3, mRmTp_DIRECT_SOUTH },  { 11, 3, mRmTp_DIRECT_SOUTH },
    { 6, 11, mRmTp_DIRECT_SOUTH }, { 2, 11, mRmTp_DIRECT_SOUTH },  { 4, 11, mRmTp_DIRECT_SOUTH },
    { 10, 6, mRmTp_DIRECT_SOUTH }, { 13, 6, mRmTp_DIRECT_SOUTH },  { 11, 6, mRmTp_DIRECT_SOUTH },
    { 6, 6, mRmTp_DIRECT_WEST },   { 6, 5, mRmTp_DIRECT_WEST },    { 6, 7, mRmTp_DIRECT_WEST },
    { 9, 11, mRmTp_DIRECT_SOUTH }, { 11, 11, mRmTp_DIRECT_SOUTH }, { 13, 11, mRmTp_DIRECT_SOUTH },
    { 3, 8, mRmTp_DIRECT_EAST },   { 3, 6, mRmTp_DIRECT_EAST },    { 6, 8, mRmTp_DIRECT_SOUTH },
    { 7, 8, mRmTp_DIRECT_SOUTH },  { 8, 8, mRmTp_DIRECT_SOUTH },   { 9, 8, mRmTp_DIRECT_SOUTH },
    { 10, 8, mRmTp_DIRECT_SOUTH },
};

static void Museum_Fossil_Actor_ct(ACTOR* actorx, GAME* game) {
    // nothing
}

static void Museum_Fossil_Actor_dt(ACTOR* actorx, GAME* game) {
    // nothing
}

static void Museum_Fossil_Actor_draw(ACTOR* actorx, GAME* game) {
    // nothing
}

static void aMF_SetTalkInfo(ACTOR* actorx) {
    static rgba_t aMF_window_color = { 255, 255, 205, 255 };
    MUSEUM_FOSSIL_ACTOR* museum_fossil = (MUSEUM_FOSSIL_ACTOR*)actorx;

    mDemo_Set_msg_num(museum_fossil->msg_no);
    mDemo_Set_talk_display_name(FALSE);
    mDemo_Set_ListenAble();
    mDemo_Set_camera(CAMERA2_PROCESS_NORMAL);
    mDemo_Set_use_zoom_sound(TRUE);
    mDemo_Set_talk_window_color(&aMF_window_color);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), -1);
}

static void Museum_Fossil_Actor_move(ACTOR* actorx, GAME* game) {
    static u8 item_name[mIN_ITEM_NAME_LEN];
    MUSEUM_FOSSIL_ACTOR* museum_fossil = (MUSEUM_FOSSIL_ACTOR*)actorx;

    if (mDemo_Check(mDemo_TYPE_SPEAK, actorx)) {
        PLAYER_ACTOR* player = GET_PLAYER_ACTOR((GAME_PLAY*)game);
        s_xyz angle = player->actor_class.shape_info.rotation;

        add_calc_short_angle2(&angle.y, museum_fossil->target_angle, 1.0f - sqrtf(0.7), 0x800, 0);
        GET_PLAYER_ACTOR_NOW()->Set_force_position_angle_proc(gamePT, NULL, &angle, mPlayer_FORCE_POSITION_ANGLE_ROTY);
    } else if (chkTrigger(BUTTON_A) && mDemo_Get_talk_actor() == NULL) {
        xyz_t pos;
        s16 angle;
        int i;

        for (i = 0; i < mMmd_FOSSIL_NUM; i++) {
            int donator = mMmd_FossilInfo(i);
            int res;

            pos.x = (aMF_fossil_data_table[i].pos.x & 0xF) * 40.0f + 20.0f;
            pos.z = (aMF_fossil_data_table[i].pos.z & 0xF) * 40.0f + 20.0f;
            pos.y = 40.0f;

            res = mRmTp_CheckTalkAble(&angle, &pos, aMF_fossil_data_table[i].direct, 42.5f, (GAME_PLAY*)game);
            if (res != FALSE) {
                museum_fossil->msg_no = (donator == mMmd_DONATOR_NONE)
                                            ? MSG_12193
                                            : ((donator == mMmd_DONATOR_DELETED_PLAYER) ? MSG_12192 : MSG_12191);
                museum_fossil->target_angle = angle;
                if (mDemo_Request(mDemo_TYPE_SPEAK, actorx, &aMF_SetTalkInfo)) {
                    if (mMmd_IS_DONATED(donator)) {
                        mActor_name_t item = (i >= 0 && i < mMmd_FOSSIL_NUM)
                                                 ? (mActor_name_t)(FTR_DINO_START + (mActor_name_t)(i << 2))
                                                 : FTR_DINO_START;

                        /* Copy the art item's name */
                        mIN_copy_name_str(item_name, item);
                        mMsg_Set_item_str_art(mMsg_Get_base_window_p(), mMsg_ITEM_STR0, item_name, mIN_ITEM_NAME_LEN,
                                              mIN_get_item_article(item));

                        /* If the donator still lives in town we need to copy their name */
                        if (mMmd_DONATOR_EXISTS(donator)) {
                            mMsg_Set_free_str(
                                mMsg_Get_base_window_p(), mMsg_FREE_STR0,
                                Save_Get(private_data[mMmd_DONATOR_PLR_IDX(donator)]).player_ID.player_name,
                                PLAYER_NAME_LEN);
                        }
                    }

                    break;
                }
            }
        }
    }
}
