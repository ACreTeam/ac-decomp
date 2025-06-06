#include "m_snowman.h"

#include "m_common_data.h"
#include "libultra/libultra.h"
#include "m_field_info.h"
#include "m_police_box.h"
#include "m_name_table.h"
#include "m_time.h"


extern int mSN_check_life(mActor_name_t* ac, int idx){
    int ret = 0;

    if(Common_Get(time.season) == mTM_SEASON_WINTER){
        if((((*ac - SNOWMAN0) % 3) + idx) < mSN_SAVE_COUNT){
            ret = 1;
        }
    }
    return ret;
}

extern int mSN_ClearSnowmanData(mActor_name_t* ac, int idx){

    bzero(Save_GetPointer(snowmen.snowmen_data[idx]), sizeof(mSN_snowman_data_c));
    *ac = 0;
}

int mSN_ClearSnowman(u16* ac){
    int ret = 0;
    u32 snowId = *ac;

    if((snowId >= SNOWMAN0) && (snowId <= SNOWMAN8)){
        mSN_ClearSnowmanData(ac, (int)(snowId - SNOWMAN0) / mSN_SAVE_COUNT);
        ret = 1;
    }
    return ret;
}

extern int mSN_MeltSnowman(mActor_name_t* ac, int days){
    int ret;
    u32 snowId;
    int snowmelt;
    mSN_snowman_data_c* snowman;
    snowId = *ac;
    ret = 0;

    if((snowId >= SNOWMAN0) && (snowId <= SNOWMAN8)){
        snowmelt = ((int)(snowId - SNOWMAN0) / mSN_SAVE_COUNT);
        if(days < 0){
            days = 1;
            Save_Set(snowman_year, 0);
            Save_Set(snowman_month, 0);
            Save_Set(snowman_day, 0);
            Save_Set(snowman_hour, 0);
            
        }
        if(mSN_check_life(ac, days) == 0){
            mSN_ClearSnowmanData(ac, snowmelt);
        }
        else{
            snowman = Save_GetPointer(snowmen.snowmen_data[snowmelt]);
            *ac += days;
            for(; days != 0; days--){
                snowman->head_size = 0.8f * snowman->head_size;
                snowman->body_size = 0.8f * snowman->body_size;
            }
        }
        ret = 1;
    }

    return ret;
}

extern int mSN_get_free_space(void){
    int ret = 0;
    int i;
    mSN_snowman_data_c* snowman = Save_GetPointer(snowmen.snowmen_data[0]);;
    
    for(i = mSN_SAVE_COUNT; i != 0; i--){
        if(snowman->exists == 0){
            return ret;
        }
        snowman++;
        ret++;
    }
    return -1;
}

extern void mSN_regist_snowman_society(mSN_snowman_info_c* info){

    xyz_t spos = info->pos;
    mActor_name_t ac = *mFI_GetUnitFG(spos);
    int snowId = mSN_get_free_space();
    xyz_t npos;
    xyz_t ypos;
    if(snowId != -1){
        mem_copy((u8*)Save_GetPointer(snowmen.snowmen_data[snowId]), (u8*)&info->data, sizeof(info->data));
        if(ac != 0){
            mPB_keep_item(ac);
            npos = info->pos;
            mFI_Wpos2DepositOFF(npos);
        }
        ypos = info->pos;
        mFI_SetFG_common((u16)(snowId * mSN_SAVE_COUNT + SNOWMAN0),info->pos,1);
    }
    
} 

extern void mSN_decide_msg(){

    Common_Set(snowman_msg_id, fqrand() * 3.0f);
}

extern void mSN_snowman_init(){

    bzero(Save_GetPointer(snowmen), sizeof(mSN_snowman_save_c));
    mSN_decide_msg();
}
