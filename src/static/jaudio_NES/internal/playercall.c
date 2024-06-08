#include "jaudio_NES/playercall.h"
#include "jaudio_NES/audiostruct.h"

static PLAYER_CALL PLAYER_CALLLIST[16];

extern void ResetPlayerCallback(){
    int i;

    for(i = 0; i < 16; i++){
        PLAYER_CALLLIST[i].callback = nullptr;
    }
}

static s32 Jac_CheckPlayerCallback(PlayerCallBack callback, void* arg){
     int i;

    for(i = 0; i < 16; i++){
        if(PLAYER_CALLLIST[i].callback == callback && PLAYER_CALLLIST[i].arg == arg){
            return i;
        }
    }   
    return -1;
}

extern s32 Jac_RegisterDspPlayerCallback(PlayerCallBack callback, void* arg){
    s32 idx = Jac_RegisterPlayerCallback(callback,arg);

    if(idx == -1){
        return -1;
    }

    PLAYER_CALLLIST[idx].DSP_mode = true;

    return idx;
}

extern s32 Jac_RegisterPlayerCallback(PlayerCallBack callback, void* arg){
     u32 i;

    for(i = 0; i < 16; i++){
        if(PLAYER_CALLLIST[i].callback == nullptr){
            break;
        }
    }    

    if(i == 16){
        return -1;
    }
    
    if(Jac_CheckPlayerCallback(callback,arg) != -1){
        return -1;
    }
    else{
        PLAYER_CALLLIST[i].callback = callback;
        PLAYER_CALLLIST[i].arg = arg;
        PLAYER_CALLLIST[i].DSP_mode = false;
        return i;
    }

    return -1;
}

extern void PlayerCallback(){
     u32 i;

    for(i = 0; i < 16; i++){
        PlayerCallBack callback = PLAYER_CALLLIST[i].callback;
        if(callback != nullptr && PLAYER_CALLLIST[i].DSP_mode == false && callback(PLAYER_CALLLIST[i].arg) == -1){
            PLAYER_CALLLIST[i].callback = nullptr;
        }
    }   
}

extern void DspPlayerCallback(){
     u32 i;

    for(i = 0; i < 16; i++){
        PlayerCallBack callback = PLAYER_CALLLIST[i].callback;
        if(callback != nullptr && PLAYER_CALLLIST[i].DSP_mode == true && callback(PLAYER_CALLLIST[i].arg) == -1){
            PLAYER_CALLLIST[i].callback = nullptr;
        }
    }
}