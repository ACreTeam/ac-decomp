#include "m_bg_item.h"

#include "m_common_data.h"
#include "m_name_table.h"

BI_PROC mBI_make_proc;


ACTOR* mBI_search_bg_item(Actor_info* info){
    static const s16 name_data[] = {
        0x4f, 0x1, 0x50,0x51
    };
    
    int i;
    for( i = 0; i < 4; i++){
        if(Actor_info_name_search(info,name_data[i], ACTOR_PART_ITEM) != 0){
            return;
        }
    }
}

void mBI_make_bg_item(GAME_PLAY* play){


    if(mBI_search_bg_item(&play->actor_info) == NULL){

        Actor_info_make_actor(&play->actor_info, &play->game, Common_Get(bg_item_profile),0,
            0.0f,0.0f,0,0,0 ,-1, -1,-1, EMPTY_NO,-1,-1,-1);
        mBI_make_proc = NULL;
    }
}

void mBI_change_bg_item(GAME_PLAY* play){

    ACTOR* actor = mBI_search_bg_item(&play->actor_info);
    
    if(actor != NULL){
        Actor_delete(actor);
        mBI_make_proc = mBI_make_bg_item;
        Common_Set(bg_item_profile, Common_Get(time.bgitem_profile));
    }
}

void mBI_ct(){

    mBI_make_proc = NULL;
    
}

void mBI_move(GAME_PLAY* play){

    if(mBI_make_proc != NULL){
        mBI_make_proc(play);
    }
}