#include "ac_pterminal.h"

#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "m_house.h"
#include "m_eappli.h"
#include "m_font.h"
#include "m_player_lib.h"
#include "m_msg.h"
#include "GBA2/gba2.h"
#include "libultra/libultra.h"

enum {
    aPT_PROC_WAIT,
    aPT_PROC_FIRST_QUESTION,
    aPT_PROC_CONNECT_AGB_TO_RCV,
    aPT_PROC_CONNECT_AGB_TO_SND,
    aPT_PROC_SEND,
    aPT_PROC_READ_QUESTION,
    aPT_PROC_RECEIVE,

    aPT_PROC_NUM
};

static void Pterminal_Actor_ct(ACTOR* actorx, GAME* game);
static void Pterminal_Actor_dt(ACTOR* actorx, GAME* game);
static void Pterminal_Actor_draw(ACTOR* actorx, GAME* game);
static void Pterminal_Actor_move(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Pterminal_Profile = {
    mAc_PROFILE_PTERMINAL,
    ACTOR_PART_BG,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(PTERMINAL_ACTOR),
    Pterminal_Actor_ct,
    Pterminal_Actor_dt,
    Pterminal_Actor_move,
    Pterminal_Actor_draw,
    NULL,
};
// clang-format on

static int aPT_Setup(PTERMINAL_ACTOR* actor, GAME* game, int proc);

static u8 aPT_receive_buf[256];

#define aPT_MAIL_HEADER_OFS (0)
#define aPT_MAIL_BODY_OFS (aPT_MAIL_HEADER_OFS + MAIL_HEADER_LEN)
#define aPT_MAIL_FOOTER_OFS (aPT_MAIL_BODY_OFS + MAIL_BODY_LEN)
#define aPT_MAIL_PAPER_TYPE_OFS (aPT_MAIL_FOOTER_OFS + MAIL_FOOTER_LEN)
#define aPT_MAIL_PRESENT_OFS (aPT_MAIL_PAPER_TYPE_OFS + sizeof(u8))
#define aPT_MAIL_NPC_ID_OFS (aPT_MAIL_PRESENT_OFS + sizeof(mActor_name_t))
#define aPT_MAIL_HEADER_BACK_START_OFS (aPT_MAIL_NPC_ID_OFS + sizeof(mActor_name_t))
#define aPT_MAIL_CARD_NO_OFS (aPT_MAIL_HEADER_BACK_START_OFS + sizeof(u8))

static int aPT_CheckMailBoxVac(void) {
    int idx = mHS_get_arrange_idx(Common_Get(player_no) & 3);
    mHm_hs_c* home = Save_GetPointer(homes[idx]);

    return mMl_chk_mail_free_space(home->mailbox, HOME_MAILBOX_SIZE);
}

static int aPT_SendMail(GAME* game) {
    static u8 header[MAIL_HEADER_LEN];
    static u8 body[MAIL_BODY_LEN];
    static u8 footer[MAIL_FOOTER_LEN];
    static Mail_c mail;
    static u8 submenu_name_str[ANIMAL_NAME_LEN];

    u8* src_p;
    mActor_name_t present;
    mActor_name_t npc_id;
    u8 paper_type;
    u8 header_back_start;
    u16 card_no;
    Mail_ct_c* content;
    int npc_type;
    int idx;
    int i;
    int ret = FALSE;

    src_p = &aPT_receive_buf[aPT_MAIL_HEADER_OFS];
    for (i = 0; i < sizeof(header); i++) {
        header[i] = src_p[i];
    }

    src_p = &aPT_receive_buf[aPT_MAIL_BODY_OFS];
    for (i = 0; i < sizeof(body); i++) {
        body[i] = src_p[i];
    }

    src_p = &aPT_receive_buf[aPT_MAIL_FOOTER_OFS];
    for (i = 0; i < sizeof(footer); i++) {
        footer[i] = src_p[i];
    }

    paper_type = (u32)aPT_receive_buf[aPT_MAIL_PAPER_TYPE_OFS] % PAPER_UNIQUE_NUM;
    present = (mActor_name_t)((aPT_receive_buf[aPT_MAIL_PRESENT_OFS] << 8) | (aPT_receive_buf[aPT_MAIL_PRESENT_OFS + 1]));
    npc_id = (mActor_name_t)((aPT_receive_buf[aPT_MAIL_NPC_ID_OFS] << 8) | (aPT_receive_buf[aPT_MAIL_NPC_ID_OFS + 1]));
    header_back_start = aPT_receive_buf[aPT_MAIL_HEADER_BACK_START_OFS];
    if (header_back_start >= MAIL_HEADER_LEN) {
        header_back_start = MAIL_HEADER_LEN - 1;
    }

    card_no = (u16)((aPT_receive_buf[aPT_MAIL_CARD_NO_OFS] << 8) | (aPT_receive_buf[aPT_MAIL_CARD_NO_OFS + 1]));
    if (!mEA_CheckLetterCardE(card_no)) {
        npc_type = ITEM_NAME_GET_TYPE(npc_id);
        if (npc_type == NAME_TYPE_SPNPC || npc_type == NAME_TYPE_NPC) {
            content = &mail.content;
            mMl_clear_mail(&mail);
            mem_clear(submenu_name_str, sizeof(submenu_name_str), CHAR_SPACE);
            if (npc_type == NAME_TYPE_SPNPC) {
                mNpc_GetActorWorldName(submenu_name_str, npc_id);
            } else {
                mNpc_GetNpcWorldNameTableNo(submenu_name_str, npc_id);
            }

            for (i = 0; i < MAIL_HEADER_LEN; i++) {
                content->header[i] = header[i];
            }

            for (i = 0; i < MAIL_BODY_LEN; i++) {
                content->body[i] = body[i];
            }

            for (i = 0; i < MAIL_FOOTER_LEN; i++) {
                content->footer[i] = footer[i];
            }

            mail.content.paper_type = paper_type;
            mail.present = present;
            mail.content.header_back_start = header_back_start;
            mail.content.font = mMl_FONT_RECV;
            
            // @BUG - the '== NAME_TYPE_SPNPC' should not be in the macro call
#ifndef BUGFIXES
            if (ITEM_NAME_GET_TYPE(npc_id == NAME_TYPE_SPNPC)) {
#else
            if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_SPNPC) {
#endif
                mail.content.mail_type = mMl_TYPE_SPNPC_PASSWORD;
            }

            mail.header.recipient.personalID = Now_Private->player_ID;
            mail.header.recipient.type = mMl_NAME_TYPE_PLAYER;
            bcopy(submenu_name_str, mail.header.sender.personalID.player_name, sizeof(submenu_name_str));
            mail.header.sender.type = mMl_NAME_TYPE_NPC;
            
            idx = aPT_CheckMailBoxVac();
            if (idx != -1) {
                mMl_copy_mail(&Save_GetPointer(homes[mHS_get_arrange_idx(Common_Get(player_no) & 3)])->mailbox[idx], &mail);
                ret = TRUE;
            }
        }

        mEA_SetLetterCardE(card_no);
        return ret;
    }
    
    return FALSE;
}

static void Pterminal_Actor_ct(ACTOR* actorx, GAME* game) {
    // nothing
}

static void Pterminal_Actor_dt(ACTOR* actorx, GAME* game) {
    // nothing
}

static void Pterminal_Actor_draw(ACTOR* actorx, GAME* game) {
    // nothing
}

static int aPT_CheckTalkAble(xyz_t* pos, int direct, GAME* game, f32 dist) {
    // clang-format off
    static int direct_table[] = {
        mRmTp_DIRECT_NORTH, // 0
        -1, // 22.5
        -1, // 45
        mRmTp_DIRECT_WEST, // 67.5
        mRmTp_DIRECT_WEST, // 90
        -1, // 112.5
        -1, // 135
        mRmTp_DIRECT_SOUTH, // 157.5
        mRmTp_DIRECT_SOUTH, // 180
        -1, // 202.5
        -1, // 225
        mRmTp_DIRECT_EAST, // 247.5
        mRmTp_DIRECT_EAST, // 270
        -1, // 292.5
        -1, // 315
        mRmTp_DIRECT_NORTH, // 337.5
    };
    // clang-format on

    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

    if ((direct & 3) == (direct_table[(playerx->shape_info.rotation.y >> 12) & 0xF])) {
        f32 dx = playerx->world.position.x - pos->x;
        f32 dz = playerx->world.position.z - pos->z;

        if (sqrtf(SQ(dx) + SQ(dz)) <= dist) {
            return TRUE;
        }

        return FALSE;
    }

    return FALSE;
}

static int aPT_CheckTalkAbleDist(xyz_t* pos, GAME* game) {
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

    if (playerx->world.position.x > 90.0f) {
        return aPT_CheckTalkAble(pos, mRmTp_DIRECT_EAST, game, 43.0f);
    }

    return FALSE;
}

static void aPT_SetTalkInfo(ACTOR* actorx) {
    static rgba_t aPT_window_color = { 255, 255, 205, 255 };
    PTERMINAL_ACTOR* actor = (PTERMINAL_ACTOR*)actorx;

    mDemo_Set_msg_num(actor->msg_no);
    mDemo_Set_talk_display_name(FALSE);
    mDemo_Set_ListenAble();
    mDemo_Set_camera(CAMERA2_PROCESS_NORMAL);
    mDemo_Set_use_zoom_sound(TRUE);
    mDemo_Set_talk_window_color(&aPT_window_color);
    mMsg_SET_CONTINUE_MSG_NUM(-1);
    aPT_Setup(actor, gamePT, actor->next_proc);
}

static void aPT_SetTransSE(PTERMINAL_ACTOR* actor) {
    actor->transSE = TRUE;
}

static void aPT_SetTransSE_move(PTERMINAL_ACTOR* actor) {
    if (actor->transSE == TRUE) {
        if (!actor->transSE_active) {
            sAdo_SysLevStart(0x47);
        }
    } else {
        if (actor->transSE_active == TRUE) {
            sAdo_SysLevStop(0x47);
        }
    }

    actor->transSE_active = actor->transSE;
    actor->transSE = FALSE;
}

static void aPT_Wait_Init(PTERMINAL_ACTOR* actor, GAME* game) {
    // nothing
}

static void aPT_Wait(PTERMINAL_ACTOR* actor, GAME* game) {
    mGcgba_EndComm();
}

static void aPT_First_Question_Init(PTERMINAL_ACTOR* actor, GAME* game) {
    mChoice_CLEAR_CHOSENUM();
}

static void aPT_First_Question(PTERMINAL_ACTOR* actor, GAME* game) {
    if (mMsg_CHECK_MAINNORMALCONTINUE()) {
        switch (mChoice_GET_CHOSENUM()) {
            case mChoice_CHOICE0:
                if (aPT_CheckMailBoxVac() != -1) {
                    mMsg_SET_CONTINUE_MSG_NUM(0x3DEF);
                    aPT_Setup(actor, game, aPT_PROC_CONNECT_AGB_TO_RCV);
                } else {
                    mMsg_SET_CONTINUE_MSG_NUM(0x3DED);
                    aPT_Setup(actor, game, aPT_PROC_WAIT);
                }
                break;
            case mChoice_CHOICE1:
                mMsg_SET_CONTINUE_MSG_NUM(0x3DF2);
                aPT_Setup(actor, game, aPT_PROC_CONNECT_AGB_TO_SND);
                break;
            case mChoice_CHOICE2:
                mMsg_SET_CONTINUE_MSG_NUM(0x3DEC);
                aPT_Setup(actor, game, aPT_PROC_WAIT);
                break;
        }
    }
}

static void aPT_Connect_AGB_to_Rcv_Init(PTERMINAL_ACTOR* actor, GAME* game) {
    actor->counter = 0;
    mGcgba_InitVar();
    mGcgba_EndComm();
}

static void aPT_Connect_AGB_to_Rcv(PTERMINAL_ACTOR* actor, GAME* game) {
    if (mMsg_CHECK_MAINNORMALCONTINUE()) {
        if (mMsg_GET_MSG_NUM() == 0x3DEF) {
            int res = mGcgba_ConnectEnabled();

            mMsg_SET_LOCKCONTINUE();
            switch (res) {
                case GBA2_GBA_STATE_TRANSMITTING:
                    break;
                case GBA2_GBA_STATE_SUCCESS:
                    aPT_Setup(actor, game, aPT_PROC_RECEIVE);
                    break;
                default:
                    if (actor->counter >= 60) {
                        mMsg_UNSET_LOCKCONTINUE();
                        mMsg_SET_CONTINUE_MSG_NUM(0x3DF3);
                        aPT_Setup(actor, game, aPT_PROC_WAIT);
                    }
                    break;
            }

            actor->counter++;
            aPT_SetTransSE(actor);
        }
    }
}

static void aPT_Connect_AGB_to_Snd_Init(PTERMINAL_ACTOR* actor, GAME* game) {
    actor->counter = 0;
    mGcgba_InitVar();
    mGcgba_EndComm();
}

static void aPT_Connect_AGB_to_Snd(PTERMINAL_ACTOR* actor, GAME* game) {
    if (mMsg_CHECK_MAINNORMALCONTINUE()) {
        if (mMsg_GET_MSG_NUM() == 0x3DF2) {
            int res = mGcgba_ConnectEnabled();

            mMsg_SET_LOCKCONTINUE();
            switch (res) {
                case GBA2_GBA_STATE_TRANSMITTING:
                    break;
                case GBA2_GBA_STATE_SUCCESS:
                    aPT_Setup(actor, game, aPT_PROC_SEND);
                    break;
                default:
                    if (actor->counter >= 60) {
                        mMsg_UNSET_LOCKCONTINUE();
                        mMsg_SET_CONTINUE_MSG_NUM(0x3DF3);
                        aPT_Setup(actor, game, aPT_PROC_WAIT);
                    }
                    break;
            }

            actor->counter++;
            aPT_SetTransSE(actor);
        }
    }
}

static void aPT_Send_Init(PTERMINAL_ACTOR* actor, GAME* game) {
    mGcgba_InitVar();
}

static void aPT_Send(PTERMINAL_ACTOR* actor, GAME* game) {
    size_t eappli_size = mEA_dl_carde_program_size();
    u8* eappli_p = mEA_dl_carde_program_p();

    switch (mGcgba_send_eAppri(eappli_p, eappli_size)) {
        case GBA2_EAPPLI_SUCCESS:
            mMsg_UNSET_LOCKCONTINUE();
            mMsg_SET_CONTINUE_MSG_NUM(0x3DF4);
            aPT_Setup(actor, game, aPT_PROC_READ_QUESTION);
            mMsg_SET_FORCENEXT();
            mGcgba_InitVar();
            mGcgba_EndComm();
            break;
        case GBA2_EAPPLI_FAILURE_XFER_ERROR:
        case GBA2_EAPPLI_FAILURE_NO_GBA:
            mMsg_UNSET_LOCKCONTINUE();
            mMsg_SET_CONTINUE_MSG_NUM(0x3DF1);
            aPT_Setup(actor, game, aPT_PROC_WAIT);
            mMsg_SET_FORCENEXT();
            mGcgba_EndComm();
            break;
        default:
            aPT_SetTransSE(actor);
            break;
    }
}

static void aPT_Read_Question_Init(PTERMINAL_ACTOR* actor, GAME* game) {
    mChoice_CLEAR_CHOSENUM();
}

static void aPT_Read_Question(PTERMINAL_ACTOR* actor, GAME* game) {
    if (mMsg_CHECK_MAINNORMALCONTINUE()) {
        int chosenum = mChoice_GET_CHOSENUM();

        if (chosenum != -1) {
            switch (chosenum) {
                case mChoice_CHOICE0:
                    mMsg_SET_CONTINUE_MSG_NUM(0x3DEF);
                    aPT_Setup(actor, game, aPT_PROC_CONNECT_AGB_TO_RCV);
                    break;
                case mChoice_CHOICE1:
                    mMsg_SET_CONTINUE_MSG_NUM(0x3DF6);
                    aPT_Setup(actor, game, aPT_PROC_WAIT);
                    break;
            }
        }
    }
}

static void aPT_Receive_Init(PTERMINAL_ACTOR* actor, GAME* game) {
    // nothing
}

static void aPT_Receive(PTERMINAL_ACTOR* actor, GAME* game) {
    int res;

    switch (mGcgba_Read(aPT_receive_buf, sizeof(aPT_receive_buf), GBA2_EAPPLI_TYPE_PTERMINAL)) {
        case GBA2_GBA_STATE_SUCCESS:
            mGcgba_EndComm();

            res = aPT_SendMail(game);
            if (res != FALSE) {
                mMsg_UNSET_LOCKCONTINUE();

                // what is the point of this?? maybe there were extra checks on card validation before
                if (res == TRUE) {
                    mMsg_SET_CONTINUE_MSG_NUM(0x3DF5);
                } else {
                    mMsg_SET_CONTINUE_MSG_NUM(0x3DF5);
                }

                mMsg_SET_FORCENEXT();
                aPT_Setup(actor, game, aPT_PROC_WAIT);
            } else {
                mMsg_UNSET_LOCKCONTINUE();
                mMsg_SET_CONTINUE_MSG_NUM(0x3DF7);
                mMsg_SET_FORCENEXT();
                aPT_Setup(actor, game, aPT_PROC_WAIT);
            }
            break;
        case GBA2_GBA_STATE_TRANSMITTING:
            aPT_SetTransSE(actor);
            break;
        default:
            mGcgba_EndComm();
            mMsg_UNSET_LOCKCONTINUE();
            mMsg_SET_CONTINUE_MSG_NUM(0x3DF0);
            mMsg_SET_FORCENEXT();
            aPT_Setup(actor, game, aPT_PROC_WAIT);
            break;
    }
}

typedef void (*aPT_INIT_PROC)(PTERMINAL_ACTOR* actor, GAME* game);

// clang-format off
static aPT_INIT_PROC aPT_stat_init_proc_table[] = {
    aPT_Wait_Init,
    aPT_First_Question_Init,
    aPT_Connect_AGB_to_Rcv_Init,
    aPT_Connect_AGB_to_Snd_Init,
    aPT_Send_Init,
    aPT_Read_Question_Init,
    aPT_Receive_Init,
};
// clang-format on

// clang-format off
static aPT_PROC aPT_stat_main_proc_table[] = {
    aPT_Wait,
    aPT_First_Question,
    aPT_Connect_AGB_to_Rcv,
    aPT_Connect_AGB_to_Snd,
    aPT_Send,
    aPT_Read_Question,
    aPT_Receive,
};
// clang-format on

static int aPT_Setup(PTERMINAL_ACTOR* actor, GAME* game, int proc) {
    if (proc >= 0 && proc < aPT_PROC_NUM) {
        (*aPT_stat_init_proc_table[proc])(actor, game);
        actor->proc = proc;
        return TRUE;
    }

    return FALSE;
}

static void Pterminal_Actor_move(ACTOR* actorx, GAME* game) {
    PTERMINAL_ACTOR* actor = (PTERMINAL_ACTOR*)actorx;

    if (mDemo_Check(mDemo_TYPE_SPEAK, actorx)) {
        ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
        s_xyz player_angle = playerx->shape_info.rotation;
        
        if (actor->proc >= 0 && actor->proc < aPT_PROC_NUM) {
            (*aPT_stat_main_proc_table[actor->proc])(actor, game);
        }

        add_calc_short_angle2(&player_angle.y, DEG2SHORT_ANGLE2(-90.0f), CALC_EASE(0.3f), DEG2SHORT_ANGLE2(11.25f), 0);
        GET_PLAYER_ACTOR_GAME(gamePT)->Set_force_position_angle_proc(gamePT, NULL, &player_angle, mPlayer_FORCE_POSITION_ANGLE_ROTY);
    } else {
        if (chkTrigger(BUTTON_A) && mDemo_Get_talk_actor() == NULL && actor->proc == aPT_PROC_WAIT) {
            xyz_t pos = { 60.0f, 40.0f, 220.0f };

            if (aPT_CheckTalkAbleDist(&pos, game)) {
                int player_no = Common_Get(player_no);

                if (player_no < PLAYER_NUM) {
                    actor->msg_no = 0x3DEE;
                    actor->next_proc = aPT_PROC_FIRST_QUESTION;
                } else {
                    actor->msg_no = 0x3DEB;
                    actor->next_proc = aPT_PROC_WAIT;
                }

                mDemo_Request(mDemo_TYPE_SPEAK, actorx, aPT_SetTalkInfo);
            }
        }
    }

    aPT_SetTransSE_move(actor);
}
