#include "zurumode.h"

#include "m_nmibuf.h"
#include "padmgr.h"
#include "jsyswrap.h"
#include "types.h"

static zuru_keycheck zuruKeyCheck;
s32 zurumode_flag;

static int zerucheck_init(zuru_keycheck* key_check) {
    key_check->zurumode_enabled = FALSE;
    key_check->state = ZURUMODE_STAGE_BEGIN_e;
    key_check->progressing = ZURUMODE_RESET;
    key_check->last_controller = 0;
}

/**
 * Checks that the current controller state is correct
 * and updates zurumode enable progress accordingly
 *
 * Zurumode code:
 *    1) L + R -> L + R + Z (Hold L & R, then press Z)
 *    2) D-Pad Up
 *    3) C-Stick Down
 *    4) C-Stick Up
 *    5) D-Pad Down
 *    6) D-Pad Left
 *    7) C-Stick Left
 *    8) C-Stick Right
 *    9) D-Pad Right
 *    10) A + B
 *    11) Start
 *
 *	Params:
 * 	key_check zurumode keycheck struct
 * 	controller current controller state
 *
 *	returns int zurumodeEnabled
 */
static int zerucheck_key_check(zuru_keycheck* key_check, u32 controller) {
    u32 controller_new;                       /* Buttons pressed on the current frame only */
    int state = key_check->state;             /* Keycheck state */
    int progressing = key_check->progressing; /* Progressing through keycheck */

    if (state != ZURUMODE_STAGE_FINAL_e) {
        u16 controller_now = controller;
        controller_new = controller_now & (key_check->last_controller ^ controller_now);
        key_check->last_controller = controller_now;

        if (controller_now == BUTTON_NONE && progressing == ZURUMODE_PROGRESSING) {
            progressing = ZURUMODE_RESET;
        } else if (controller_new != BUTTON_NONE) {
            if (progressing == ZURUMODE_PROGRESSING) {
                state = ZURUMODE_STAGE_BEGIN_e;
            }

            switch (state) {
                case ZURUMODE_STAGE_BEGIN_e:
                    /* L & R must be held first, then Z */
                    if (controller_now == (BUTTON_R | BUTTON_L | BUTTON_Z) && controller_new == BUTTON_Z) {
                        state = ZURUMODE_STAGE_1_e;
                        progressing = ZURUMODE_PROGRESSING;
                    }
                    break;

                case ZURUMODE_STAGE_1_e:
                    if (controller_new == BUTTON_DUP) {
                        state = ZURUMODE_STAGE_2_e;
                    } else {
                        state = ZURUMODE_STAGE_BEGIN_e;
                    }
                    break;

                case ZURUMODE_STAGE_2_e:
                    if (controller_new == BUTTON_CDOWN) {
                        state = ZURUMODE_STAGE_3_e;
                        progressing = ZURUMODE_PROGRESSING;
                    } else {
                        state = ZURUMODE_STAGE_BEGIN_e;
                    }
                    break;

                case ZURUMODE_STAGE_3_e:
                    if (controller_new == BUTTON_CUP) {
                        state = ZURUMODE_STAGE_4_e;
                    } else {
                        state = ZURUMODE_STAGE_BEGIN_e;
                    }
                    break;

                case ZURUMODE_STAGE_4_e:
                    if (controller_new == BUTTON_DDOWN) {
                        state = ZURUMODE_STAGE_5_e;
                        progressing = ZURUMODE_PROGRESSING;
                    } else {
                        state = ZURUMODE_STAGE_BEGIN_e;
                    }
                    break;

                case ZURUMODE_STAGE_5_e:
                    if (controller_new == BUTTON_DLEFT) {
                        state = ZURUMODE_STAGE_6_e;
                    } else {
                        state = ZURUMODE_STAGE_BEGIN_e;
                    }
                    break;

                case ZURUMODE_STAGE_6_e:
                    if (controller_new == BUTTON_CLEFT) {
                        state = ZURUMODE_STAGE_7_e;
                        progressing = ZURUMODE_PROGRESSING;
                    } else {
                        state = ZURUMODE_STAGE_BEGIN_e;
                    }
                    break;

                case ZURUMODE_STAGE_7_e:
                    if (controller_new == BUTTON_CRIGHT) {
                        state = ZURUMODE_STAGE_8_e;
                    } else {
                        state = ZURUMODE_STAGE_BEGIN_e;
                    }
                    break;

                case ZURUMODE_STAGE_8_e:
                    if (controller_new == BUTTON_DRIGHT) {
                        state = ZURUMODE_STAGE_9_e;
                        progressing = ZURUMODE_PROGRESSING;
                    } else {
                        state = ZURUMODE_STAGE_BEGIN_e;
                    }
                    break;

                case ZURUMODE_STAGE_9_e:
                    if (controller_new == (BUTTON_B | BUTTON_A)) {
                        state = ZURUMODE_STAGE_10_e;
                    } else if (controller_new == BUTTON_A) {
                        state = ZURUMODE_STAGE_91_e;
                    } else if (controller_new == BUTTON_B) {
                        state = ZURUMODE_STAGE_92_e;
                    } else {
                        state = ZURUMODE_STAGE_BEGIN_e;
                    }
                    break;

                case ZURUMODE_STAGE_91_e:
                    if (controller_new == BUTTON_B) {
                        state = ZURUMODE_STAGE_10_e;
                    } else {
                        state = ZURUMODE_STAGE_BEGIN_e;
                    }
                    break;

                case ZURUMODE_STAGE_92_e:
                    if (controller_new == BUTTON_A) {
                        state = ZURUMODE_STAGE_10_e;
                    } else {
                        state = ZURUMODE_STAGE_BEGIN_e;
                    }
                    break;

                case ZURUMODE_STAGE_10_e:
                    if (controller_new == BUTTON_START) {
                        state = ZURUMODE_STAGE_FINAL_e;
                    } else {
                        state = ZURUMODE_STAGE_BEGIN_e;
                    }
                    break;
            }
        }
    }

    if (state == ZURUMODE_STAGE_FINAL_e) {
        /* Zurumode code has been correctly input */
        key_check->zurumode_enabled ^= TRUE;
        key_check->state = ZURUMODE_STAGE_BEGIN_e;
        key_check->progressing = ZURUMODE_RESET;
    } else {
        key_check->state = state;
        key_check->progressing = progressing;
    }

    return key_check->zurumode_enabled;
}

static s32 zurumode_update() {
    s32 flag_now;
    s32 zurumode_now;

    flag_now = zurumode_flag;
    zurumode_flag = zurumode_now = (APPNMI_ZURUMODE_GET()) ? (APPNMI_ZURUMODE2_GET() ? 2 : 1) : 0;

    if (flag_now != zurumode_now) {
        OSReport("zurumode_flag が %d から %d に変更されました\n", flag_now, zurumode_now);
        if (zurumode_flag != 0) {
            if (APPNMI_TESTMODE_GET() || APPNMI_ZURUMODE_GET()) {
                JC_JUTAssertion_changeDevice(3);
                JC_JUTDbPrint_setVisible(JC_JUTDbPrint_getManager(), 1);
            }
        } else {
            JC_JUTAssertion_changeDevice(2);
            JC_JUTDbPrint_setVisible(JC_JUTDbPrint_getManager(), 0);
        }
    }
    return zurumode_flag;
}

static void zurumode_callback(void* param) {
    zerucheck_key_check(&zuruKeyCheck, (u32)(((padmgr*)param)->cur_pads[1].button));
    if (APPNMI_DEBUGMODE_GET() || (APPNMI_TESTMODE_GET() && (padmgr_isConnectedController(1) != 0)) ||
        (zuruKeyCheck.zurumode_enabled != 0)) {
        APPNMI_ZURUMODE_SET();
    } else {
        APPNMI_ZURUMODE_CLR();
    }
    if (APPNMI_DEBUGMODE_GET() && (zuruKeyCheck.state != 0) && (zuruKeyCheck.zurumode_enabled == 0)) {
        JW_JUTReport(60, 90, 1, "ZURU %d/%d", zuruKeyCheck.state, zuruKeyCheck.progressing);
    }

    zurumode_update();
}

extern void zurumode_init(void) {
    zurumode_flag = 0;
    zerucheck_init(&zuruKeyCheck);
    zuruKeyCheck.zurumode_enabled = APPNMI_ZURUMODE_GET();
    padmgr_setClient2(zurumode_callback, &padmgr_class);
    zurumode_update();
}

extern void zurumode_cleanup(void) {
    padmgr_removeClient2(zurumode_callback, &padmgr_class);
    zurumode_flag = 0;
}
