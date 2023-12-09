#include "m_pause.h"
#include "m_controller.h"
void Pause_ct(pause_t* pause){
    pause->timer = 0;
    pause->enabled = 0;
}

int Pause_proc(pause_t* pause, pad_t* pad){

    if(CHECK_BTN_ALL(pad->now.button, BUTTON_R) && CHECK_BTN_ALL(pad->on.button, BUTTON_DDOWN)){
        pause->enabled = !pause->enabled;
    }

    if((!pause->enabled) || (CHECK_BTN_ALL(pad->now.button, BUTTON_Z) && 
        (CHECK_BTN_ALL(pad->on.button, BUTTON_R) || (CHECK_BTN_ALL(pad->now.button, BUTTON_R) 
        && (++pause->timer > 8))))){
        pause->timer = 0;
        return 1;
        }
    return 0;
}
