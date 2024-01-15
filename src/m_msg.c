#include "m_msg.h"

#include "m_font.h"
#include "m_string.h"
#include "m_common_data.h"
#include "jsyswrap.h"
#include "m_bgm.h"
#include "libforest/emu64/emu64_wrapper.h"

static u32 Msg_table_rom_start;
static u32 Msg_rom_start;

static mMsg_Data_c mMsg_data;
static mMsg_Window_c mMsg_window;

typedef int (*mMsg_CONTROL_CODE_PROC)(mMsg_Window_c*, int*);

static void mMsg_MainSetup_Window(mMsg_Window_c* msg_p, GAME* game);

#include "m_msg_ctrl.c_inc"

static void mMsg_sound_MessageSpeedForce(f32 timer);
static void mMsg_sound_MessageStatus(u8 status);

#include "m_msg_main.c_inc"
#include "m_msg_sound.c_inc"
#include "m_msg_hide.c_inc"
#include "m_msg_appear.c_inc"
#include "m_msg_normal.c_inc"
#include "m_msg_cursol.c_inc"
