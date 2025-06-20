#include "ac_t_flag.h"

#include "m_rcp.h"
#include "evw_anime.h"
#include "sys_matrix.h"
#include "m_name_table.h"

static void aTFL_actor_draw(ACTOR*, GAME*);

ACTOR_PROFILE T_Flag_Profile = {
    mAc_PROFILE_T_FLAG,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_6,
    sizeof(FLAG_ACTOR),
    NONE_ACTOR_PROC,
    NONE_ACTOR_PROC,
    NONE_ACTOR_PROC,
    aTFL_actor_draw,
    NULL,
};

extern Vtx tol_hata_01_v[15];
extern Gfx tol_hata_e_model[];
extern Gfx tol_hata_hataT_model[];
extern EVW_ANIME_DATA tol_hata_01_evw_anime[];

static void aTFL_calc_angl(s16* dst, s16 fact, s16* addend, s16 addval){

    if(fact < *dst){
        *addend -= 0x3C0;
        if(*addend < -addval){
            *addend = -addval;
        }
    }
    else{
        *addend += 0x1E0;
        if(*addend > addval){
            *addend = addval;
        }
        
    }

    *dst += *addend;
}


static void aTFL_make_vtx(Vtx* v, ACTOR* actor){
    FLAG_ACTOR* flag = (FLAG_ACTOR*)actor;
    TOOLS_ACTOR* tools = (TOOLS_ACTOR*)actor;
    
    xyz_t pos;
    s16 fact;

    s16 obx;
    f32 sins;
    s16 pre;
    s16 t;


    fact = 0;
    if(tools->init_matrix == 1){
        Matrix_put(&flag->tools_class.matrix_work);
        Matrix_translate(0.0f, 0.0f, 48.0999984741f, MTX_MULT);
        Matrix_Position_Zero(&pos);
        if(flag->unk1D0 == 0){
            xyz_t_move(&flag->work, &pos);
            flag->unk1D0 = 1;
        }
        else{
            fact = atans_table( pos.y - flag->work.y, -(pos.x - flag->work.x));
            xyz_t_move(&flag->work, &pos);
        }
    }

    mem_copy((u8*)v, (u8*)tol_hata_01_v, sizeof(tol_hata_01_v));
    aTFL_calc_angl(&flag->angle, fact, &flag->addendedang, 0x9C4);
    obx = (v[9].v.ob[0] * cos_s(flag->angle));
    sins = sin_s(flag->angle);
    pre = v[9].v.ob[0];

    v[9].v.ob[0] = obx; 
    t = pre * sins;
    v[9].v.ob[1] = t; 
    v[12].v.ob[0] = obx; 
    v[12].v.ob[1] = t;

    obx = (v[10].v.ob[0] * cos_s(flag->angle));
    sins = sin_s(flag->angle);
    pre = v[10].v.ob[0];

    v[10].v.ob[0] = obx; 
    t = pre * sins;
    v[10].v.ob[1] = t; 
    v[11].v.ob[0] = obx; 
    v[11].v.ob[1] = t;
}

static void aTFL_actor_draw(ACTOR* actor, GAME* game){
    FLAG_ACTOR* flag = (FLAG_ACTOR*)actor;
    TOOLS_ACTOR* tools = (TOOLS_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;
    GRAPH* graph = game->graph;
    
    Vtx* buf;
    
    buf = GRAPH_ALLOC_TYPE(graph, Vtx, 15);

    if(buf != NULL){
        aTFL_make_vtx(buf, &tools->actor_class); 
    }
    else{
        buf = tol_hata_01_v;
    }

    if(tools->init_matrix == 1){
        Matrix_put(&flag->tools_class.matrix_work);
        Matrix_Position_Zero(&actor->world.position);
        tools->init_matrix = 0;
    }
    else{
        Matrix_translate(actor->world.position.x, actor->world.position.y, 
        actor->world.position.z, MTX_LOAD);
        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);
    }

    OPEN_DISP(graph);
    {
        Gfx* gfxp;        
        
        _texture_z_light_fog_prim_npc(graph);
        gfxp = NOW_POLY_OPA_DISP;
        gSPMatrix(gfxp++, _Matrix_to_Mtx_new(graph),G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxp++, tol_hata_e_model);
        SET_POLY_OPA_DISP(gfxp);
        
        Evw_Anime_Set(play, tol_hata_01_evw_anime);
    }
    {
        Gfx* gfxp;
        _texture_z_light_fog_prim_xlu(graph);
        gfxp = NOW_POLY_XLU_DISP;
        gSPMatrix(gfxp++, _Matrix_to_Mtx_new(graph),G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    
        gSPSegment(gfxp++, 0x0A, buf); 
        gSPDisplayList(gfxp++, tol_hata_hataT_model);
    
        SET_POLY_XLU_DISP(gfxp);
        
    }
    CLOSE_DISP(graph);

}
