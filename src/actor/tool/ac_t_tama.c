#include "ac_t_tama.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"
#include "m_common_data.h"

static void aTTM_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE T_Tama_Profile = {
    mAc_PROFILE_T_TAMA,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_TAMA,
    sizeof(T_TAMA_ACTOR),
    NONE_ACTOR_PROC,
    NONE_ACTOR_PROC,
    NONE_ACTOR_PROC,
    &aTTM_actor_draw,
    NULL
};

extern Gfx tama01_model[];
extern Gfx tol_tamaire_model[];

extern u8 tama01_r_tex[];
extern u8 tama01_w_tex[];
extern u8 tol_tamaire_r1_tex[];
extern u8 tol_tamaire_r2_tex[];
extern u8 tol_tamaire_r3_tex[];
extern u8 tol_tamaire_w1_tex[];
extern u8 tol_tamaire_w2_tex[];
extern u8 tol_tamaire_w3_tex[];

void aTTM_actor_draw(ACTOR* actor, GAME* game) {
    static Gfx* displayList[] = {
        tama01_model,
        tama01_model,
        tol_tamaire_model,
        tol_tamaire_model,
    };

    static u8* texture[4][3] = {
        { tama01_r_tex, tama01_r_tex, tama01_r_tex },
        { tama01_w_tex, tama01_w_tex, tama01_w_tex },
        { tol_tamaire_r1_tex, tol_tamaire_r2_tex, tol_tamaire_r3_tex },
        { tol_tamaire_w1_tex, tol_tamaire_w2_tex, tol_tamaire_w3_tex },
    };

    T_TAMA_ACTOR* tama;
    int work2;
    ACTOR* parent;
    xyz_t position1;
    xyz_t position2;
    int tool_name;
    GRAPH* graph;
    Gfx* gfx;

    tama = (T_TAMA_ACTOR*)actor;
    parent = actor->parent_actor;
    work2 = tama->tools_class.work2;
    if (work2 > 0 && tama->tools_class.init_matrix == TRUE) {
        graph = game->graph;
        tool_name = (tama->tools_class.tool_name - 0x30);
        switch (tool_name) {
            case 0:
            case 1:
                Matrix_put(&tama->tools_class.matrix_work);
                Matrix_scale(0.5f, 0.5f, 0.5f, MTX_MULT);
                break;
            case 2:
            case 3:
                Matrix_RotateY(parent->shape_info.rotation.y - 0x4000, MTX_LOAD);
                Matrix_translate(6.0f, 3.0f, 3.0f, MTX_MULT);
                Matrix_Position_Zero(&position1);
                Matrix_put(&tama->tools_class.matrix_work);
                Matrix_Position_Zero(&position2);

                position2.x += position1.x;
                position2.y += position1.y;
                position2.z += position1.z;
                Matrix_translate(position2.x, position2.y, position2.z, MTX_LOAD);
                Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);
                break;
            default:
                return;
        }
        tama->tools_class.init_matrix = FALSE;
        _texture_z_light_fog_prim_npc(graph);

        OPEN_DISP(graph);
        gfx = NOW_POLY_OPA_DISP;
        gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        work2--;
        gSPSegment(gfx++, G_MWO_SEGMENT_8, texture[tool_name][work2]);
        gSPDisplayList(gfx++, displayList[tool_name]);

        SET_POLY_OPA_DISP(gfx);
        CLOSE_DISP(graph);
    }
}
