#include "jaudio_NES/staff.h"

#include "jaudio_NES/game64.h"
#include "jaudio_NES/sub_sys.h"
#include "jaudio_NES/audiowork.h"

static BOOL start_flag = FALSE;
static s32 mouth_num = 0;
static u32 seq_num = 0;

extern void Na_StaffRollInit(void) {
    start_flag = FALSE;
    mouth_num = 0;
    seq_num = -1;
}

extern void Na_StaffRollStart(s16 seq_no) {
    Nap_SetS8(NA_MAKE_COMMAND(AUDIOCMD_OP_GRP_SET_PORT, sou_now_bgm_handle, 0, 0), 0);
    Nap_SetS8(NA_MAKE_COMMAND(AUDIOCMD_OP_GRP_SET_PORT, sou_now_bgm_handle, 0, 1), 0);
    Nap_SetS8(NA_MAKE_COMMAND(AUDIOCMD_OP_GRP_SET_PORT, sou_now_bgm_handle, 0, 2), -1);

    seq_num = seq_no;
    start_flag = TRUE;
}

extern void Na_GetStaffRollInfo(StaffRollInfo_c* info) {
    group* group = nullptr;
    sub* subtrack = nullptr;
    note* note = nullptr;
    channel* channel = nullptr;
    s32 temp;
    s32 mouth_type = 0;
    s32 blink;
    s32 counter;
    s32 i;

    if (AG.groups[sou_now_bgm_handle].flags.enabled) {

        start_flag = FALSE;
        group = &AG.groups[sou_now_bgm_handle];

        if (group->port[2] == 0) {
            info->staffroll_part = STAFFROLL_PART_MAIN;
        } else if (group->port[2] == 1) {
            info->staffroll_part = STAFFROLL_PART_FADEOUT;
        } else {
            info->staffroll_part = STAFFROLL_PART_INTRO;
        }
    } else {
        if (start_flag) {
            info->staffroll_part = STAFFROLL_PART_START;
        } else {
            info->staffroll_part = STAFFROLL_PART_FINISH;
        }

        return;
    }

    for (i = 2; i < AUDIO_SUBTRACK_NUM; i++) {
        subtrack = group->subtracks[i];
        if (subtrack != nullptr) {
            note = subtrack->note_layers[0];
            if (note != nullptr && note->_00bit3) {
                channel = note->channel;
                if (channel != nullptr && channel->common_ch.enabled) {
                    /* Found our enabled note channel, get mouth type */
                    switch (i) {
                        case 2:
                        case 7:
                        case 12:
                            mouth_type = 4;
                            break;
                        case 6:
                            mouth_type = 1;
                            break;
                        case 4:
                        case 13:
                            mouth_type = 5;
                            break;
                        case 10:
                            mouth_type = 3;
                            break;
                        case 11:
                            mouth_type = 0;
                            break;
                        default:
                            mouth_type = 2;
                            break;
                    }

                    /* stop searching */
                    break;
                }
            }
        }
    }

    /* update mouth num */
    if (mouth_type != mouth_num) {
        switch (mouth_type) {
            case 4:
                switch (mouth_num) {
                    case 0:
                    case 1:
                        mouth_num = 3;
                        break;
                    case 3:
                        mouth_num = 4;
                        break;
                    default:
                        mouth_num = 1;
                        break;
                }

                break;

            case 1:
                switch (mouth_num) {
                    case 4:
                        mouth_num = 3;
                        break;
                    default:
                        mouth_num = 1;
                        break;
                }

                break;

            case 3:
                switch (mouth_num) {
                    case 2:
                    case 5:
                        mouth_num = 1;
                        break;
                    default:
                        mouth_num = 3;
                        break;
                }

                break;

            case 5:
                switch (mouth_num) {
                    case 4:
                        mouth_num = 3;
                        break;
                    case 1:
                        mouth_num = 5;
                        break;
                    default:
                        mouth_num = 1;
                        break;
                }

                break;

            case 2:
                switch (mouth_num) {
                    case 4:
                        mouth_num = 3;
                        break;
                    case 1:
                        mouth_num = 2;
                        break;
                    default:
                        mouth_num = 1;
                        break;
                }

                break;

            case 0:
                switch (mouth_num) {
                    case 1:
                    case 3:
                        mouth_num = 0;
                        break;
                    case 4:
                        mouth_num = 3;
                        break;
                    default:
                        mouth_num = 1;
                        break;
                }
        }
    }

    info->mouth_num = mouth_num;

    /* sequence script itself controls blink flag? */
    if (group->port[1] == 1) {
        blink = TRUE;
    } else {
        blink = FALSE;
    }

    info->blink_flag = blink;
    counter = group->counter;

    switch (seq_num) {
        case 1:
        case 2:
        case 3:
        case 14:
        case 17:
        case 19:
        case 31:
        case 32:
        case 39:
        case 44:
        case 49:
        case 52:
            info->beat = 3;
            break;
        default:
            info->beat = 4;
            break;
    }

    temp = info->beat * 48;
    info->_01 = counter / temp;
    counter -= info->_01 * temp;
    info->percent = (f32)counter / temp;
}
