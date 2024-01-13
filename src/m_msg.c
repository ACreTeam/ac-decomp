#include "m_msg.h"

#include "m_font.h"
#include "m_string.h"
#include "m_common_data.h"
#include "jsyswrap.h"

static u32 Msg_table_rom_start;
static u32 Msg_rom_start;

static mMsg_Data_c mMsg_data;
static mMsg_Window_c mMsg_window;

#include "m_msg_ctrl.c_inc"
#include "m_msg_main.c_inc"