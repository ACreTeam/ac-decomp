#include "ac_tools.h"

#include "m_common_data.h"
#include "libultra/libultra.h"
#include "m_scene.h"
#include "m_name_table.h"

static void aTOL_actor_ct(ACTOR* actor, GAME* play);
static void aTOL_actor_dt(ACTOR*, GAME*);
static void aTOL_init_clip_area(GAME* play);
static void aTOL_free_clip_area();


ACTOR_PROFILE Tools_Profile = {
    mAc_PROFILE_TOOLS,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_3,
    sizeof(ACTOR),
    aTOL_actor_ct,
    aTOL_actor_dt,
    NONE_ACTOR_PROC,
    NONE_ACTOR_PROC,
    NULL,
};

aTOL_Clip_c aTOL_clip; 



static void aTOL_actor_ct(ACTOR* actor, GAME* game){

    aTOL_init_clip_area(game);
}

static void aTOL_actor_dt(ACTOR*, GAME*){

    aTOL_free_clip_area();
}

static void aTOL_check_data_bank(int id, ACTOR* actor){
    
    ACTOR* kill;
    aTOL_Clip_c* clip;

    if((actor->part == ACTOR_PART_PLAYER) && (id <= 0x1F)){

        clip = Common_Get(clip.tools_clip);

        if(clip->bank_id != -1){

            kill = actor->child_actor;

            if((kill != NULL) && (kill->data_bank_id == clip->bank_id)){
                Actor_delete(kill);
            }
        }
    }
}

static ACTOR_TOOLS* aTOL_birth_proc(ToolName name, int id, ACTOR_TOOLS* tool, 
    GAME_PLAY* play, s16 arg, int* arg5){
    static s16 profile_table[] = {
        mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA,
        mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, 
        mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA,
        mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA,
        mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA,
        mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA,
        mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, 
        mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, 
        mAc_PROFILE_T_KEITAI,   mAc_PROFILE_T_UTIWA,    mAc_PROFILE_T_HANABI,   mAc_PROFILE_T_CRACKER,  mAc_PROFILE_T_PISTOL,   
        mAc_PROFILE_T_FLAG,     mAc_PROFILE_T_TUMBLER,  mAc_PROFILE_T_NPCSAO,   mAc_PROFILE_T_TAMA,     mAc_PROFILE_T_TAMA,
        mAc_PROFILE_T_TAMA,     mAc_PROFILE_T_TAMA,     mAc_PROFILE_T_ANRIUM1,  mAc_PROFILE_T_BAG1,     mAc_PROFILE_T_BAG2,     
        mAc_PROFILE_T_BISCUS1,  mAc_PROFILE_T_BISCUS2,  mAc_PROFILE_T_BISCUS3,  mAc_PROFILE_T_BISCUS4,  mAc_PROFILE_T_HASU1,
        mAc_PROFILE_T_HAT1,     mAc_PROFILE_T_HAT2,     mAc_PROFILE_T_HAT3,     mAc_PROFILE_T_REI1,     mAc_PROFILE_T_REI2,
        mAc_PROFILE_T_ZINNIA1,  mAc_PROFILE_T_ZINNIA2,  mAc_PROFILE_T_COBRA1, 
    };
    
    ACTOR_TOOLS* child;

    aTOL_check_data_bank(name, &tool->actor_class); 

    child = (ACTOR_TOOLS*)Actor_info_make_child_actor(&play->actor_info, &tool->actor_class, &play->game,
        profile_table[name], 0.0f, 0.0f, 0.0f, 0, 0, 0, -1, 0, arg, -1); 

    if(child != NULL){
        child->process_id = id;
        child->tool_name = name;
    }


    if(arg5 != NULL){
        *arg5 = -1;
    }
    
}

static int aTOL_chg_request_mode_proc(ACTOR* actor ,ACTOR_TOOLS* tool, int id){

    if(actor != tool->actor_class.parent_actor){
        return 0;
    }

    tool->process_id = id;
    return 1;
}

static void aTOL_secure_pl_umbrella_bank_area(GAME* game){
    GAME_PLAY* play = (GAME_PLAY*)game;

    Object_Exchange_c* exchange;
    int id;
    
    exchange = &play->object_exchange;
    id = exchange->bank_id;

    if(mSc_secure_exchange_keep_bank(exchange, NULL, 0xC00) != 0U){
        Common_Set(clip.tools_clip->bank_id, id);
    }
    else{
        Common_Set(clip.tools_clip->bank_id, -1);
        
    }
    
}

static void aTOL_init_clip_area(GAME* game){

    if(Common_Get(clip.tools_clip) == NULL){

        Common_Set(clip.tools_clip, &aTOL_clip);
        bzero(&aTOL_clip, sizeof(aTOL_Clip_c));
        Common_Set(clip.tools_clip->aTOL_birth_proc,aTOL_birth_proc);
        Common_Set(clip.tools_clip->aTOL_chg_request_mode_proc,aTOL_chg_request_mode_proc);
        aTOL_secure_pl_umbrella_bank_area(game);
    }
}


static void aTOL_free_clip_area(){

    if(Common_Get(clip.tools_clip) != NULL){
    
        Common_Set(clip.tools_clip, NULL);
    }
}