#include "ac_museum_picture.h"

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
} aMP_pos_c;

typedef struct {
    Gfx* disp_model;
    Gfx* dummy_disp_model;
    aMP_pos_c pos;
} aMP_art_data_c;

static void Museum_Picture_Actor_ct(ACTOR* actorx, GAME* game);
static void Museum_Picture_Actor_dt(ACTOR* actorx, GAME* game);
static void Museum_Picture_Actor_move(ACTOR* actorx, GAME* game);
static void Museum_Picture_Actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Museum_Picture_Profile = {
    mAc_PROFILE_MUSEUM_PICTURE,
    ACTOR_PART_BG,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_MUSEUM_PICTURE,
    sizeof(MUSEUM_PICTURE_ACTOR),
    &Museum_Picture_Actor_ct,
    &Museum_Picture_Actor_dt,
    &Museum_Picture_Actor_move,
    &Museum_Picture_Actor_draw,
    NULL,
};

extern Gfx obj_art01_model[];
extern Gfx obj_art02_model[];
extern Gfx obj_art03_model[];
extern Gfx obj_art04_model[];
extern Gfx obj_art05_model[];
extern Gfx obj_art06_model[];
extern Gfx obj_art07_model[];
extern Gfx obj_art08_model[];
extern Gfx obj_art09_model[];
extern Gfx obj_art10_model[];
extern Gfx obj_art11_model[];
extern Gfx obj_art12_model[];
extern Gfx obj_art13_model[];
extern Gfx obj_art14_model[];
extern Gfx obj_art15_model[];

extern Gfx obj_art_dummy01_model[];
extern Gfx obj_art_dummy02_model[];
extern Gfx obj_art_dummy03_model[];
extern Gfx obj_art_dummy04_model[];
extern Gfx obj_art_dummy05_model[];
extern Gfx obj_art_dummy06_model[];
extern Gfx obj_art_dummy07_model[];
extern Gfx obj_art_dummy08_model[];

static aMP_art_data_c aMP_art_data_table[mMmd_ART_NUM] = {
    { obj_art01_model, obj_art_dummy01_model, 7, 1 },  { obj_art02_model, obj_art_dummy03_model, 1, 9 },
    { obj_art03_model, obj_art_dummy01_model, 11, 5 }, { obj_art04_model, obj_art_dummy04_model, 9, 1 },
    { obj_art05_model, obj_art_dummy02_model, 5, 9 },  { obj_art06_model, obj_art_dummy05_model, 3, 1 },
    { obj_art07_model, obj_art_dummy07_model, 3, 9 },  { obj_art08_model, obj_art_dummy06_model, 1, 5 },
    { obj_art09_model, obj_art_dummy04_model, 3, 5 },  { obj_art10_model, obj_art_dummy06_model, 11, 9 },
    { obj_art11_model, obj_art_dummy07_model, 11, 1 }, { obj_art12_model, obj_art_dummy04_model, 13, 5 },
    { obj_art13_model, obj_art_dummy08_model, 13, 9 }, { obj_art14_model, obj_art_dummy08_model, 9, 5 },
    { obj_art15_model, obj_art_dummy08_model, 5, 1 },
};

static void Museum_Picture_Actor_ct(ACTOR* actorx, GAME* game) {
    // nothing
}

static void Museum_Picture_Actor_dt(ACTOR* actorx, GAME* game) {
    // nothing
}

static void aMP_DrawOneArt(aMP_pos_c* pos_xz, Gfx* disp, GAME* game) {
    GRAPH* graph = game->graph;
    xyz_t pos = { 0.0f, 0.0f, 0.0f };

    pos.x = pos_xz->x * 40.0f + 20.0f;
    pos.z = pos_xz->z * 40.0f + 20.0f;
    pos.y = 40.0f;

    Matrix_translate(pos.x, pos.y, pos.z, MTX_LOAD);
    Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

    OPEN_DISP(graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, disp);

    CLOSE_DISP(graph);
}

static void Museum_Picture_Actor_draw(ACTOR* actorx, GAME* game) {
    int i;
    aMP_art_data_c* data_table_p = aMP_art_data_table;

    for (i = 0; i < mMmd_ART_NUM; i++, data_table_p++) {
        int info = mMmd_ArtInfo(i);
        Gfx* disp_model = (&data_table_p->disp_model)[mMmd_IS_DONATED(info) == FALSE];

        aMP_DrawOneArt(&data_table_p->pos, disp_model, game);
    }
}

static int aMP_CheckTalkAble(xyz_t* pos, int direct, GAME* game, f32 dist) {
    static int direct_table[] = { mRmTp_DIRECT_NORTH, -1, -1, mRmTp_DIRECT_WEST,
                                  mRmTp_DIRECT_WEST,  -1, -1, mRmTp_DIRECT_SOUTH,
                                  mRmTp_DIRECT_SOUTH, -1, -1, mRmTp_DIRECT_EAST,
                                  mRmTp_DIRECT_EAST,  -1, -1, mRmTp_DIRECT_NORTH };

    PLAYER_ACTOR* player = GET_PLAYER_ACTOR((GAME_PLAY*)game);

    if ((direct & 3) == direct_table[(player->actor_class.shape_info.rotation.y >> 12) & 0xF]) {
        f32 dx = player->actor_class.world.position.x - pos->x;
        f32 dz = player->actor_class.world.position.z - pos->z;

        if (sqrtf(dx * dx + dz * dz) <= dist) {
            return TRUE;
        } else {
            return FALSE;
        }
    }

    return FALSE;
}

static int aMP_CheckTalkAbleDist(aMP_pos_c* ut_pos, GAME* game) {
    xyz_t pos = { 0.0f, 0.0f, 0.0f };

    pos.x = (f32)(ut_pos->x & 15) * 40.0f + 60.0f;
    pos.z = (f32)(ut_pos->z & 15) * 40.0f + 40.0f;
    pos.y = 40.0f;

    return aMP_CheckTalkAble(&pos, mRmTp_DIRECT_SOUTH, game, 33.0f);
}

static void aMP_SetTalkInfo(ACTOR* actorx) {
    static rgba_t aMP_window_color = { 255, 255, 205, 255 };
    MUSEUM_PICTURE_ACTOR* museum_picture = (MUSEUM_PICTURE_ACTOR*)actorx;

    mDemo_Set_msg_num(museum_picture->msg_no);
    mDemo_Set_talk_display_name(FALSE);
    mDemo_Set_ListenAble();
    mDemo_Set_camera(CAMERA2_PROCESS_NORMAL);
    mDemo_Set_use_zoom_sound(TRUE);
    mDemo_Set_talk_window_color(&aMP_window_color);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), -1);
}

static void Museum_Picture_Actor_move(ACTOR* actorx, GAME* game) {
    static u8 item_name[mIN_ITEM_NAME_LEN];
    MUSEUM_PICTURE_ACTOR* museum_picture = (MUSEUM_PICTURE_ACTOR*)actorx;

    if (mDemo_Check(mDemo_TYPE_SPEAK, actorx)) {
        PLAYER_ACTOR* player = GET_PLAYER_ACTOR((GAME_PLAY*)game);
        s_xyz angle = player->actor_class.shape_info.rotation;

        add_calc_short_angle2(&angle.y, DEG2SHORT_ANGLE(-180.0f), 1.0f - sqrtf(0.7), 0x800, 0);
        GET_PLAYER_ACTOR_NOW()->Set_force_position_angle_proc(gamePT, NULL, &angle, mPlayer_FORCE_POSITION_ANGLE_ROTY);
    } else if (chkTrigger(BUTTON_A) && mDemo_Get_talk_actor() == NULL) {
        int i;

        for (i = 0; i < mMmd_ART_NUM; i++) {
            int donator = mMmd_ArtInfo(i);

            if (aMP_CheckTalkAbleDist(&aMP_art_data_table[i].pos, game)) {
                museum_picture->msg_no = (donator == mMmd_DONATOR_NONE)
                                             ? MSG_12193
                                             : ((donator == mMmd_DONATOR_DELETED_PLAYER) ? MSG_12192 : MSG_12191);
                if (mDemo_Request(mDemo_TYPE_SPEAK, actorx, &aMP_SetTalkInfo) && mMmd_IS_DONATED(donator)) {
                    mActor_name_t item = (i >= 0 && i < mMmd_ART_NUM)
                                             ? (mActor_name_t)(FTR_PAINTING0 + (mActor_name_t)(i << 2))
                                             : FTR_PAINTING0;

                    /* Copy the art item's name */
                    mIN_copy_name_str(item_name, item);
                    mMsg_Set_item_str_art(mMsg_Get_base_window_p(), mMsg_ITEM_STR0, item_name, mIN_ITEM_NAME_LEN,
                                          mIN_get_item_article(item));

                    /* If the donator still lives in town we need to copy their name */
                    if (mMmd_DONATOR_EXISTS(donator)) {
                        mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR0,
                                          Save_Get(private_data[mMmd_DONATOR_PLR_IDX(donator)]).player_ID.player_name,
                                          PLAYER_NAME_LEN);
                    }
                }
            }
        }
    }
}
