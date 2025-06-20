#include "ac_museum_indoor.h"

#include "m_name_table.h"
#include "m_scene.h"
#include "m_kankyo.h"
#include "sys_matrix.h"
#include "m_play.h"
#include "m_common_data.h"

static void Museum_Indoor_Actor_ct(ACTOR* actorx, GAME* game);
static void Museum_Indoor_Actor_draw(ACTOR* actorx, GAME* game);
static void Museum_Indoor_Actor_dt(ACTOR* actorx, GAME* game);
static void Museum_Indoor_Actor_move(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Museum_Indoor_Profile = {
    mAc_PROFILE_MUSEUM_INDOOR,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(MUSEUM_INDOOR_ACTOR),
    Museum_Indoor_Actor_ct,
    Museum_Indoor_Actor_dt,
    Museum_Indoor_Actor_move,
    Museum_Indoor_Actor_draw,
    NULL,
};

typedef struct museum_indoor_cull_info_s {
    int scene;
    int type;
    Gfx* cull_gfx;
} aMI_cull_info_c;

extern Gfx rom_museum4_wall_model[];
extern Gfx rom_museum5_wall_model[];

static aMI_cull_info_c aMI_museum_indoor_cull_info[] = {
    { SCENE_MUSEUM_ROOM_INSECT, 1, rom_museum4_wall_model },
    { SCENE_MUSEUM_ROOM_FISH, 0, rom_museum5_wall_model },
};

static void aMI_AlphaToON(f32* alpha_p) {
    (*alpha_p) += 24.0f;
    if (*alpha_p < 0.0f) {
        *alpha_p = 0.0f;
    } else if (*alpha_p > 255.0f) {
        *alpha_p = 255.0f;
    }
}

static void aMI_AlphaToOFF(f32* alpha_p) {
    (*alpha_p) -= 24.0f;
    if (*alpha_p < 0.0f) {
        *alpha_p = 0.0f;
    } else if (*alpha_p > 255.0f) {
        *alpha_p = 255.0f;
    }
}

static int aMI_GetThisSceneCullIndex(void) {
    int i;
    
    for (i = 0; i < ARRAY_COUNT(aMI_museum_indoor_cull_info); i++) {
        if (Save_Get(scene_no) == aMI_museum_indoor_cull_info[i].scene) {
            return i;
        }
    }

    return -1;
}

static void Museum_Indoor_Actor_ct(ACTOR* actorx, GAME* game) {
    MUSEUM_INDOOR_ACTOR* museum_indoor = (MUSEUM_INDOOR_ACTOR*)actorx;

    museum_indoor->alpha = 255.0f;
    museum_indoor->cull_index = aMI_GetThisSceneCullIndex();
}

static void Museum_Indoor_Actor_dt(ACTOR* actorx, GAME* game) {
    // nothing
}

static void Museum_Indoor_Actor_draw(ACTOR* actorx, GAME* game) {
    MUSEUM_INDOOR_ACTOR* museum_indoor = (MUSEUM_INDOOR_ACTOR*)actorx;

    if (museum_indoor->cull_index != -1) {
        Gfx* cull_gfx = aMI_museum_indoor_cull_info[museum_indoor->cull_index].cull_gfx;
        u8 r;
        u8 g;
        u8 b;
        u8 a = (int)museum_indoor->alpha;

        mEnv_GetRoomPrimColor(&r, &g, &b, (GAME_PLAY*)game);
        OPEN_DISP(game->graph);

        Matrix_translate(0.0f, 0.0f, 0.0f, MTX_LOAD);
        Matrix_RotateY(0, MTX_MULT);
        Matrix_scale(0.0625f, 0.0625f, 0.0625f, MTX_MULT);

        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 0, r, g, b, a);
        gSPDisplayList(NEXT_POLY_XLU_DISP, cull_gfx);

        CLOSE_DISP(game->graph);
    }
}

static void aMI_SetAlpha(MUSEUM_INDOOR_ACTOR* museum_indoor, GAME* game) {
    int cull_idx = museum_indoor->cull_index;

    if (cull_idx != -1) {
        int camera_state = Camera2NormalState_get((GAME_PLAY*)game);
        f32* alpha_p = &museum_indoor->alpha;

        switch (aMI_museum_indoor_cull_info[cull_idx].type) {
            case 0:
                if (camera_state == 3 || camera_state == 7) {
                    aMI_AlphaToOFF(alpha_p);
                } else {
                    aMI_AlphaToON(alpha_p);
                }
                break;
            case 1:
                if (camera_state == 1 || camera_state == 5) {
                    aMI_AlphaToOFF(alpha_p);
                } else {
                    aMI_AlphaToON(alpha_p);
                }
                break;
        }
    }
}

static void Museum_Indoor_Actor_move(ACTOR* actorx, GAME* game) {
    MUSEUM_INDOOR_ACTOR* museum_indoor = (MUSEUM_INDOOR_ACTOR*)actorx;

    aMI_SetAlpha(museum_indoor, game);
}
