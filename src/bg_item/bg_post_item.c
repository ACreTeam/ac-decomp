#include "bg_post_item.h"

#include "m_name_table.h"
#include "m_post_office.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_common_data.h"

static void bPTI_actor_ct(ACTOR* actorx, GAME* game);
static void bPTI_actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE BgPostItem_Profile = {
    mAc_PROFILE_BGPOSTITEM,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(BG_POST_ITEM_ACTOR),
    &bPTI_actor_ct,
    mActor_NONE_PROC1,
    mActor_NONE_PROC1,
    &bPTI_actor_draw,
    NULL,
};

static void bPTI_actor_ct(ACTOR* actorx, GAME* game) {
    BG_POST_ITEM_ACTOR* bg_post_item = (BG_POST_ITEM_ACTOR*)actorx;
    int post_girl_type;

    if (Common_Get(time.now_sec) >= (19 * mTM_SECONDS_IN_HOUR) ||
        Common_Get(time.now_sec) < (7 * mTM_SECONDS_IN_HOUR)) {
        post_girl_type = 1;
    } else {
        post_girl_type = 0;
    }

    Common_Set(post_girl_npc_type, post_girl_type);
    bg_post_item->update_mail_flag = TRUE;
}

extern Gfx obj_letterT_mat_model[];
extern Gfx obj_letterT_gfx_model[];

static void bPTI_actor_draw(ACTOR* actorx, GAME* game) {
    static float setX[mPO_MAIL_STORAGE_SIZE] = { 80.0f, 120.0f, 160.0f, 200.0f, 240.0f };
    BG_POST_ITEM_ACTOR* bg_post_item = (BG_POST_ITEM_ACTOR*)actorx;
    int keep_mail_sum;

    if (bg_post_item->update_mail_flag == TRUE) {
        bg_post_item->keep_mail_sum = mPO_get_keep_mail_sum();
        bg_post_item->update_mail_flag = FALSE;
    }

    keep_mail_sum = bg_post_item->keep_mail_sum;
    if (keep_mail_sum > 0) {
        GRAPH* graph = game->graph;
        f32* setX_p = setX;
        Gfx* gfx;

        _texture_z_light_fog_prim(graph);

        OPEN_DISP(graph);
        gfx = NOW_POLY_OPA_DISP;

        gSPDisplayList(gfx++, obj_letterT_mat_model);
        for (keep_mail_sum; keep_mail_sum != 0; keep_mail_sum--) {
            Matrix_translate(*setX_p, 60.0f, 60.0f, MTX_LOAD);
            Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

            gDPPipeSync(gfx++);
            gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfx++, obj_letterT_gfx_model);
            setX_p++;
        }

        SET_POLY_OPA_DISP(gfx);
        CLOSE_DISP(graph);
    }
}
