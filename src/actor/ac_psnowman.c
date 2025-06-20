#include "ac_psnowman.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_actor_shadow.h"
#include "m_collision_bg.h"
#include "m_demo.h"
#include "m_player_lib.h"
#include "audio.h"
#include "m_roll_lib.h"
#include "m_field_info.h"
#include "m_snowman.h"
#include "m_quest.h"
#include "sys_matrix.h"
#include "m_rcp.h"

static void aPSM_actor_ct(ACTOR* actor, GAME* game);
static void aPSM_actor_dt(ACTOR* actor, GAME* game);
static void aPSM_actor_move(ACTOR* actor, GAME* game);
static void aPSM_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE Psnowman_Profile = {
    mAc_PROFILE_PSNOWMAN,
    ACTOR_PART_BG,
    ACTOR_STATE_NONE,
    SNOWMAN0,
    ACTOR_OBJ_BANK_PSNOWMAN,
    sizeof(PSNOWMAN_ACTOR),
    aPSM_actor_ct,
    aPSM_actor_dt,
    aPSM_actor_move,
    aPSM_actor_draw,
    NULL,
};

extern Gfx act_darumaB_model[];
extern Gfx act_darumaA_model[];

static void aPSM_actor_ct(ACTOR* actor, GAME* game) {
    int id;
    f32 shadow_size;
    mSN_snowman_data_c* current_data;
    PSNOWMAN_ACTOR* snowman = (PSNOWMAN_ACTOR*)actor;
    f32 scale;

    id = (actor->npc_id - SNOWMAN0) / 3;
    snowman->current_id = id;

    current_data = Save_GetPointer(snowmen.snowmen_data[id]);

    snowman->body = current_data->body_size / 255.0f;
    snowman->body_scale = 0.01f + (0.02f * snowman->body);

    snowman->head = current_data->head_size / 255.0f;
    snowman->head_scale = 0.01f + (0.02f * snowman->head);

    scale = snowman->body_scale;

    actor->scale.z = scale;
    actor->scale.y = scale;
    actor->scale.x = scale;

    snowman->eye_heigth = (0.6f * (10.0f + (20.0f * snowman->head) + (10.0f + (20.0f * snowman->body))));

    actor->world.position.y =
        mCoBG_GetBgY_OnlyCenter_FromWpos2(actor->world.position, -(10.0f + (20.0f * snowman->body)));

    Actor_world_to_eye(actor, snowman->eye_heigth);

    shadow_size = 10.0f + (20.0f * snowman->body);

    Shape_Info_init(actor, 0.0f, mAc_ActorShadowEllipse, shadow_size, shadow_size);

    snowman->message_num = MSG_2209 + ((Common_Get(snowman_msg_id) + id) % 3) + (current_data->score * 3);

    mCoBG_SetPlussOffset(actor->home.position, 3, 100);
}

static void aPSM_actor_dt(ACTOR* actor, GAME* game) {
    mCoBG_SetPlussOffset(actor->home.position, 0, 100);
}

static void aPSM_set_talk_info(ACTOR* actor) {
    PSNOWMAN_ACTOR* snowman = (PSNOWMAN_ACTOR*)actor;

    mDemo_Set_msg_num(snowman->message_num);
    mDemo_Set_ListenAble();
    mDemo_Set_camera(TRUE);
    mPlib_Set_able_hand_all_item_in_demo(TRUE);
}

static void aPSMAN_MakeBreakEffect(PSNOWMAN_ACTOR* actor, GAME* game) {
    xyz_t head_pos;
    xyz_t body_pos;
    s16 angle;

    head_pos = actor->actor_class.world.position;
    body_pos = actor->actor_class.world.position;

    angle = actor->body * 100.0f;
    body_pos.y -= actor->body * 20.0f + 10.0f;

    Common_Get(clip).effect_clip->effect_make_proc(99, body_pos, 1, 0, game, actor->actor_class.npc_id, angle, 0);

    angle = actor->head * 100.0f;
    head_pos.y += actor->eye_heigth - (actor->head * 20.0f + 10.0f);

    Common_Get(clip).effect_clip->effect_make_proc(99, head_pos, 1, 0, game, actor->actor_class.npc_id, angle, 0);

    sAdo_OngenTrgStart(0x143, &actor->actor_class.world.position);
}

static void aPSM_actor_move(ACTOR* actor, GAME* game) {
    PSNOWMAN_ACTOR* snowman = (PSNOWMAN_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (mRlib_PSnowman_NormalTalk(actor, play, &snowman->speed, aPSM_set_talk_info) == FALSE) {
        if (mFI_GetUnitFG(actor->world.position) != NULL) {
            mSN_ClearSnowman(&actor->npc_id);
        }
        aPSMAN_MakeBreakEffect(snowman, game);
        mQst_BackSnowman(actor->world.position);
        Actor_delete(actor);
    }
}

static void aPSM_actor_draw(ACTOR* actor, GAME* game) {
    PSNOWMAN_ACTOR* snowman = (PSNOWMAN_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;

    GRAPH* graph = game->graph;
    Gfx* gfx;

    OPEN_DISP(graph);

    _texture_z_light_fog_prim(graph);
    gfx = NOW_POLY_OPA_DISP;
    gDPPipeSync(gfx++);
    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, act_darumaB_model);
    Matrix_translate(actor->world.position.x, actor->world.position.y + snowman->eye_heigth, actor->world.position.z,
                     FALSE);
    Matrix_RotateX(0xF380, TRUE);
    Matrix_scale(snowman->head_scale, snowman->head_scale, snowman->head_scale, TRUE);

    if (snowman->speed > 20.0f) {
        mRlib_PSnowmanBreakNeckSwing(&snowman->head_angle, snowman->speed, snowman->head);
    }
    gDPPipeSync(gfx++);
    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, act_darumaA_model);

    NOW_POLY_OPA_DISP = gfx;
    CLOSE_DISP(graph);
}
