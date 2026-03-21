/* PAD shim: redirects PAD* calls to SDL2 Game Controller API.
 * Stage 1: PADInit initialises SDL2; PADRead returns "no controller" safely. */
#include "platform/platform.h"
#include <dolphin/pad.h>
#include <SDL2/SDL.h>
#include <string.h>

static PADSamplingCallback s_sampling_cb = nullptr;
static SDL_GameController* s_controllers[PAD_MAX_CONTROLLERS] = {};

static void open_controllers(void) {
    for (int i = 0; i < SDL_NumJoysticks() && i < PAD_MAX_CONTROLLERS; i++) {
        if (SDL_IsGameController(i) && !s_controllers[i])
            s_controllers[i] = SDL_GameControllerOpen(i);
    }
}

extern "C" {

BOOL PADInit(void) {
    if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) {
        fprintf(stderr, "[PAD] SDL_Init: %s\n", SDL_GetError());
        return FALSE;
    }
    open_controllers();
    return TRUE;
}

BOOL PADReset(u32 mask) { (void)mask; open_controllers(); return TRUE; }
BOOL PADSync(void)      { return TRUE; }

u32 PADRead(PADStatus* status) {
    if (!status) return 0;
    u32 connected = 0;
    SDL_GameControllerUpdate();
    for (int c = 0; c < PAD_MAX_CONTROLLERS; c++) {
        memset(&status[c], 0, sizeof(PADStatus));
        SDL_GameController* gc = s_controllers[c];
        if (!gc || !SDL_GameControllerGetAttached(gc)) {
            status[c].err = PAD_ERR_NO_CONTROLLER;
            continue;
        }
        connected |= (1u << c);
        status[c].err = PAD_ERR_NONE;

        /* Buttons */
        auto btn = [&](SDL_GameControllerButton b) -> bool {
            return SDL_GameControllerGetButton(gc, b) != 0;
        };
        u16 buttons = 0;
        if (btn(SDL_CONTROLLER_BUTTON_A))             buttons |= PAD_BUTTON_A;
        if (btn(SDL_CONTROLLER_BUTTON_B))             buttons |= PAD_BUTTON_B;
        if (btn(SDL_CONTROLLER_BUTTON_X))             buttons |= PAD_BUTTON_X;
        if (btn(SDL_CONTROLLER_BUTTON_Y))             buttons |= PAD_BUTTON_Y;
        if (btn(SDL_CONTROLLER_BUTTON_START))         buttons |= PAD_BUTTON_START;
        if (btn(SDL_CONTROLLER_BUTTON_DPAD_LEFT))     buttons |= PAD_BUTTON_LEFT;
        if (btn(SDL_CONTROLLER_BUTTON_DPAD_RIGHT))    buttons |= PAD_BUTTON_RIGHT;
        if (btn(SDL_CONTROLLER_BUTTON_DPAD_DOWN))     buttons |= PAD_BUTTON_DOWN;
        if (btn(SDL_CONTROLLER_BUTTON_DPAD_UP))       buttons |= PAD_BUTTON_UP;
        if (btn(SDL_CONTROLLER_BUTTON_LEFTSHOULDER))  buttons |= PAD_TRIGGER_L;
        if (btn(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) buttons |= PAD_TRIGGER_R;
        if (btn(SDL_CONTROLLER_BUTTON_BACK))          buttons |= PAD_TRIGGER_Z;
        status[c].button = buttons;

        /* Analog sticks: SDL range is -32768..32767; GC is -128..127 */
        auto axis16 = [&](SDL_GameControllerAxis a) -> int16_t {
            return SDL_GameControllerGetAxis(gc, a);
        };
        status[c].stickX  = (s8)(axis16(SDL_CONTROLLER_AXIS_LEFTX)  >> 8);
        status[c].stickY  = (s8)(-(axis16(SDL_CONTROLLER_AXIS_LEFTY) >> 8));
        status[c].substickX = (s8)(axis16(SDL_CONTROLLER_AXIS_RIGHTX) >> 8);
        status[c].substickY = (s8)(-(axis16(SDL_CONTROLLER_AXIS_RIGHTY) >> 8));

        /* Triggers: SDL 0..32767; GC 0..255 */
        status[c].triggerLeft  = (u8)(axis16(SDL_CONTROLLER_AXIS_TRIGGERLEFT)  >> 7);
        status[c].triggerRight = (u8)(axis16(SDL_CONTROLLER_AXIS_TRIGGERRIGHT) >> 7);
    }
    return connected;
}

void PADSetSamplingRate(u32 msec) { (void)msec; }

void PADControlAllMotors(const u32* cmds) {
    for (int c = 0; c < PAD_MAX_CONTROLLERS; c++) {
        if (!s_controllers[c]) continue;
        if (cmds[c] == PAD_MOTOR_RUMBLE)
            SDL_GameControllerRumble(s_controllers[c], 0xFFFF, 0xFFFF, 0);
        else
            SDL_GameControllerRumble(s_controllers[c], 0, 0, 0);
    }
}

void PADControlMotor(s32 chan, u32 cmd) {
    u32 cmds[PAD_MAX_CONTROLLERS] = { PAD_MOTOR_STOP, PAD_MOTOR_STOP,
                                       PAD_MOTOR_STOP, PAD_MOTOR_STOP };
    if (chan >= 0 && chan < PAD_MAX_CONTROLLERS) cmds[chan] = cmd;
    PADControlAllMotors(cmds);
}

void PADSetSpec(u32 spec)    { (void)spec; }
u32  PADGetSpec(void)        { return 0; }
BOOL PADGetType(s32 c, u32* type) {
    if (type) *type = 0; /* PAD_TYPE_STANDARD not defined in this SDK version */
    return s_controllers[c] != nullptr ? TRUE : FALSE;
}

void PADClamp(PADStatus* status) {
    /* Clamp analog values to valid GC range */
    if (!status) return;
    for (int c = 0; c < PAD_MAX_CONTROLLERS; c++) {
        if (status[c].stickX   >  127) status[c].stickX   =  127;
        if (status[c].stickX   < -128) status[c].stickX   = -128;
        if (status[c].stickY   >  127) status[c].stickY   =  127;
        if (status[c].stickY   < -128) status[c].stickY   = -128;
        if (status[c].substickX >  127) status[c].substickX =  127;
        if (status[c].substickX < -128) status[c].substickX = -128;
        if (status[c].substickY >  127) status[c].substickY =  127;
        if (status[c].substickY < -128) status[c].substickY = -128;
    }
}

PADSamplingCallback PADSetSamplingCallback(PADSamplingCallback cb) {
    PADSamplingCallback old = s_sampling_cb;
    s_sampling_cb = cb;
    return old;
}

} /* extern "C" */
