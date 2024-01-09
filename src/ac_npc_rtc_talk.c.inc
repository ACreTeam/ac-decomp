
void aNRTC_set_slot_name(int slot_id, int str_no) {
    u8 name[mIN_ITEM_NAME_LEN];

    mString_Load_StringFromRom(name, sizeof(name), 0x6CD + slot_id);
    mMsg_Set_free_str(mMsg_Get_base_window_p(),str_no, name, sizeof(name));
}


void aNRTC_rtc_err(NPCRTC_ACTOR* rtc, GAME_PLAY*) {
    int num;
    
    if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p()) == 1) { 
        num = mChoice_Get_ChoseNum(mChoice_Get_base_window_p());
        switch (num) {                   
        case 0:
            aNRTC_change_talk_proc(rtc, 3);
            break;
        case 1:
            rtc->unk9A8 = 1;
            aNRTC_change_talk_proc(rtc, 10);
            break;
        }
    }
}


void aNRTC_timer_open_msg_wait(NPCRTC_ACTOR* rtc, GAME_PLAY*) {
    int order = mDemo_Get_OrderValue(4, 9);
    
    if (order == 1) {
        if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p()) == 1) {
            mDemo_Set_OrderValue(4, 9, 0);
            aNRTC_change_talk_proc(rtc, 4);
            mMsg_request_main_disappear_wait_type1(mMsg_Get_base_window_p());
        }
    }
}

void aNRTC_timer_open_wait(NPCRTC_ACTOR* rtc, GAME_PLAY* play){
    Submenu* submenu = &play->submenu; 
    if (mMsg_Check_main_wait(mMsg_Get_base_window_p()) == 1) {
        aNRTC_change_talk_proc(rtc, 5);
        mSM_open_submenu(submenu, 3, 1, 0);
        mMsg_request_main_appear_wait_type1(mMsg_Get_base_window_p());
    } 
}


void aNRTC_timer_close_wait(NPCRTC_ACTOR* rtc, GAME_PLAY* play) {
    if (play->submenu.open_flag == FALSE) { 
        if (mMsg_Check_not_series_main_wait(mMsg_Get_base_window_p()) == 1) {
            mMsg_Set_ForceNext(mMsg_Get_base_window_p()); 
            rtc->unk9A8 = 2;
            aNRTC_change_talk_proc(rtc, 0xA);
        }
    }
}


void aNRTC_delete_bf(NPCRTC_ACTOR* rtc, GAME_PLAY* play) {
    int order =  mDemo_Get_OrderValue(4, 9);
    
    if ((mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p()) == 1) && (order != 0)) {

        mMsg_Set_LockContinue(mMsg_Get_base_window_p());
        aNRTC_change_talk_proc(rtc, 7);
    }
}


void aNRTC_delete(NPCRTC_ACTOR* rtc, GAME_PLAY* play){
    mMsg_Window_c* window;
    int card;
    int card_ret;

    window = mMsg_Get_base_window_p();
    card_ret = mCD_EraseBrokenLand_bg(&card);

    switch(card_ret){
        case 0:
            rtc->unk9A8 = 3;
            mMsg_Set_continue_msg_num(window, 0x9DE);
            break;
        case 22:
        case 2:
            rtc->unk9A8 = 1;
            mMsg_Set_continue_msg_num(window, 0x9DF);
            break;
        case 25:
            return;
        case 15:
            rtc->unk9A8 = 3;
            mMsg_Set_continue_msg_num(window, 0x9E1);
            break;
        default:
            rtc->unk9A8 = 1;
            mMsg_Set_continue_msg_num(window, 0x9DF);
            break;
    } 

    if(card_ret != 0x19){
        mMsg_Unset_LockContinue(window);
        aNRTC_change_talk_proc(rtc,10);
    }
}


void aNRTC_format_chk(NPCRTC_ACTOR* rtc, GAME_PLAY* play) {
    int num;
    
    if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p()) == 1) {
        aNRTC_change_talk_proc(rtc, 0xA);
        num = mChoice_Get_ChoseNum(mChoice_Get_base_window_p());
        switch (num) {                         
        case 0:
            rtc->unk9A8 = 3;
            break;
        case 1:
            rtc->unk9A8 = 2;
            break;
        case 2:
            rtc->unk9A8 = 1;
            break;
        case 3:
            rtc->unk9A8 = 3;
            aNRTC_change_talk_proc(rtc, 9);
            break;
        }
    }
}

void aNRTC_format(NPCRTC_ACTOR* rtc, GAME_PLAY* play) {
    int order;
    mMsg_Window_c* window;
    int card_ret;

    window = mMsg_Get_base_window_p();
    order = mDemo_Get_OrderValue(4, 9);
    switch (order) {                              
    case 1:
        mDemo_Set_OrderValue(4, 9, 2);
        mMsg_Set_LockContinue(window);
        break;
    case 2: 
        card_ret = mCD_card_format_bg(Common_Get(memcard_slot));
        switch (card_ret) {                        
        case 1:                                     
            mMsg_Set_continue_msg_num(window, 0x9E9);
            mMsg_Unset_LockContinue(window);
            aNRTC_change_talk_proc(rtc, 0xA);
            rtc->unk9A8 = 3;
            mDemo_Set_OrderValue(4, 9, 0);
            break;
        case -1:                                   
            mMsg_Unset_LockContinue(window);
            aNRTC_change_talk_proc(rtc, 0xA);
            rtc->unk9A8 = 1;
            mMsg_Set_continue_msg_num(window, 0x9E7);
            mDemo_Set_OrderValue(4, 9, 0);
        case 0:                                   
            break;
        }
        break;
    }
}


void aNRTC_break_data(NPCRTC_ACTOR* rtc, GAME_PLAY* play) {
    int num;

    if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p()) == 1) {
        aNRTC_change_talk_proc(rtc, 0xA);
        num = mChoice_Get_ChoseNum(mChoice_Get_base_window_p());
        switch (num) {                        
        case 0:
            rtc->unk9A8 = 3;
            break;
        case 1:
            aNRTC_change_talk_proc(rtc, 6);
            break;
        }
    }
}

void aNRTC_break_data_2(NPCRTC_ACTOR* rtc, GAME_PLAY* play) {
    int num;

    if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p()) == 1) {
        aNRTC_change_talk_proc(rtc, 0xA);
        num = mChoice_Get_ChoseNum(mChoice_Get_base_window_p());
        switch (num) {                         
        case 0:
            rtc->unk9A8 = 3;
            break;
        case 1:
            rtc->unk9A8 = 2;
            break;
        case 2:
            rtc->unk9A8 = 1;
            break;
        case 3:
            rtc->unk9A8 = 4;
            break;
        }
    } 
}



void aNRTC_change_talk_proc(NPCRTC_ACTOR* rtc, int idx) {
    static aNPCRTC_SUB_PROC process[] = {
        aNRTC_break_data,      aNRTC_break_data_2,     aNRTC_rtc_err,   aNRTC_timer_open_msg_wait,
        aNRTC_timer_open_wait, aNRTC_timer_close_wait, aNRTC_delete_bf, aNRTC_delete,
        aNRTC_format_chk,      aNRTC_format,           (aNPCRTC_SUB_PROC)none_proc1,
    };
    rtc->unk994 = idx;
    rtc->unk99C = process[idx];  
}


void aNRTC_set_talk_info_talk_request(){
    int msg;
    
    switch(Common_Get(save_error_type)){
        case 0:
            msg = 0x9CC;
            break; 
        case 2:
            msg = 0x9D1;
            break;
        case 6:
            msg = 0x9DA;
            break;
        case 7:
            msg = 0x9D8;
            break;
        case 9:
            msg = 0x9D4;
            break;
        case 1:
            msg = 0x9E2;
            break;
        case 4:
            msg = 0x9E4;
            break;
        case 3:
            msg = 0x9E3;
            break;
        case 5:
            msg = 0x9E5;
            break;
        case 8:
            msg = 0x9E6;
            break;
        default:
            msg = 0x9D4;
            break;
    }
    mDemo_Set_msg_num(msg); 
    mDemo_Set_camera(1);
}


void aNRTC_talk_request(ACTOR* actor,GAME*) {
    mDemo_Request(8, actor, aNRTC_set_talk_info_talk_request);
}


int aNRTC_talk_init(ACTOR* actor, GAME* game) {
    NPCRTC_ACTOR* rtc = (NPCRTC_ACTOR*)actor;
    
    mDemo_Set_ListenAble();
    aNRTC_set_slot_name(Common_Get(memcard_slot), mMsg_FREE_STR4);
    switch (Common_Get(save_error_type)) {     
    case 0:
        aNRTC_change_talk_proc(rtc, 2);
        break;
    case 2:
        aNRTC_change_talk_proc(rtc, 0);
        break;
    case 5:
        aNRTC_change_talk_proc(rtc, 8);
        break;
    default:
        aNRTC_change_talk_proc(rtc, 1);
        break;
    }
    rtc->npc_class.talk_info.talk_request_proc = mActor_NONE_PROC1;
    mMsg_Get_base_window_p(); 
    mMsg_Set_idling_req();
    return 1;
}


int aNRTC_talk_end_chk(ACTOR* actor,GAME* game){
    NPCRTC_ACTOR* rtc = (NPCRTC_ACTOR*)actor; 
    GAME_PLAY* play = (GAME_PLAY*)game;  
    int res = 0; 
    mMsg_Window_c* window;  

    window = mMsg_Get_base_window_p();
    rtc->unk99C(rtc,play);
 
    if(mMsg_Check_idling_now(window) == 1){ 
        mMsg_request_main_disappear_wait_type1(window);
        aNRTC_think_init_proc(&rtc->npc_class,play);
        rtc->unk9A0 = 0; 
        res = 1;
        rtc->unk9B4 = 0x32;  
        rtc->unk9B0 = 0x4B; 
        bzero(&play->fade_color_value, sizeof(rgba8888_t)); 
    }
    else{     
        int unk9AC; 
        unk9AC = rtc->unk9AC;
        if ((mMsg_Check_MainNormal(mMsg_Get_base_window_p()) == 1) || (((mChoice_check_main_normal(mChoice_Get_base_window_p()) == 1) != 0))) {
            unk9AC++;
            if (unk9AC > 0x258) {
                unk9AC = 0x258;
            }
        } else {
            unk9AC = 0;
        }  
        if (mDemo_Get_OrderValue(4, 0) == 0) {
            if (unk9AC >= 0x258) { 
                if ( rtc->npc_class.draw.animation_id != 0x76) {
                    mDemo_Set_OrderValue(4, 0, 0xFF);
                }
            } else if (rtc->npc_class.draw.animation_id == 0x76) {
                mDemo_Set_OrderValue(4, 0, 0xFD);
            }
        }
        rtc->unk9AC = unk9AC; 
    }
    return res;
}

