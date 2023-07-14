#include "m_common_data.h"

#include "libultra/libultra.h"


extern void common_data_reinit(){

    u8 state;

    state = Common_Get(pad_connected);

    bzero(&common_data, sizeof(common_data));
    Common_Set(wipeType, 255);
    Common_Set(game_started,1);
    Common_Set(last_scene_no, -1);
    Common_Set(demo_profiles[0], 246);
    Common_Set(demo_profiles[1], 246);
    Common_Set(pad_connected, state);

    mFRm_ClearSaveCheckData(Save_GetPointer(save_check));
}

extern void common_data_init(){
    common_data_reinit();
}

extern void common_data_clear(){
    clip_clear();
}