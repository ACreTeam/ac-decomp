#ifndef JSYSWRAPPER_H
#define JSYSWRAPPER_H

#include "types.h"
#include "JSystem/JKernel/JKREnum.h"
#include "JSystem/JUtility/JUTEnum.h"

#ifdef __cplusplus
extern "C" {
#endif

enum resource_index {
  RESOURCE_FGDATA,
  RESOURCE_MAIL,
  RESOURCE_MAIL_TABLE,
  RESOURCE_MAILA,
  RESOURCE_MAILA_TABLE,
  RESOURCE_MAILB,
  RESOURCE_MAILB_TABLE,
  RESOURCE_MAILC,
  RESOURCE_MAILC_TABLE,
  RESOURCE_PALLET_BOY,
  RESOURCE_PS,
  RESOURCE_PS_TABLE,
  RESOURCE_PSZ,
  RESOURCE_PSZ_TABLE,
  RESOURCE_SELECT,
  RESOURCE_SELECT_TABLE,
  RESOURCE_STRING,
  RESOURCE_STRING_TABLE,
  RESOURCE_SUPERZ,
  RESOURCE_SUPERZ_TABLE,
  RESOURCE_SUPER,
  RESOURCE_SUPER_TABLE,
  RESOURCE_TEX_BOY,
  RESOURCE_FACE_BOY,
  RESOURCE_FGNPCDATA,
  RESOURCE_MESSAGE,
  RESOURCE_MESSAGE_TABLE,
  RESOURCE_MY_ORIGINAL,
  RESOURCE_NEEDLEWORK_JOYBOOT,
  RESOURCE_PLAYER_ROOM_FLOOR,
  RESOURCE_PLAYER_ROOM_WALL,
  RESOURCE_NPC_NAME_STR_TABLE,
  RESOURCE_D_OBJ_NPC_STOCK_SCH,
  RESOURCE_D_OBJ_NPC_STOCK_SCL,
  RESOURCE_TITLE,
  RESOURCE_MURA_SPRING,
  RESOURCE_MURA_SUMMER,
  RESOURCE_MURA_FALL,
  RESOURCE_MURA_WINTER,
  RESOURCE_ODEKAKE,
  RESOURCE_OMAKE,
  RESOURCE_EKI1,
  RESOURCE_EKI1_2,
  RESOURCE_EKI1_3,
  RESOURCE_EKI1_4,
  RESOURCE_EKI1_5,
  RESOURCE_EKI2,
  RESOURCE_EKI2_2,
  RESOURCE_EKI2_3,
  RESOURCE_EKI2_4,
  RESOURCE_EKI2_5,
  RESOURCE_EKI3,
  RESOURCE_EKI3_2,
  RESOURCE_EKI3_3,
  RESOURCE_EKI3_4,
  RESOURCE_EKI3_5,
  RESOURCE_TEGAMI,
  RESOURCE_TEGAMI2,
  RESOURCE_FAMIKON,
  RESOURCE_BOY1,
  RESOURCE_BOY2,
  RESOURCE_BOY3,
  RESOURCE_BOY4,
  RESOURCE_BOY5,
  RESOURCE_BOY6,
  RESOURCE_BOY7,
  RESOURCE_BOY8,
  RESOURCE_GIRL11,
  RESOURCE_GIRL12,
  RESOURCE_GIRL13,
  RESOURCE_GIRL14,
  RESOURCE_GIRL15,
  RESOURCE_GIRL16,
  RESOURCE_GIRL17,
  RESOURCE_GIRL18,
  RESOURCE_D_BG_ISLAND_SCH,

  RESOURCE_NUM
};

extern void JW_Init();
extern void JW_Init2();
extern void JW_Init3();
extern void* JW_Alloc(size_t size, int align);
extern void JW_Free(void* ptr);
extern s32 JW_Resize(void* ptr, size_t new_size);
extern size_t JW_GetMemBlockSize(void* ptr);
extern size_t JW_GetResSizeFileNo(int file_no);
extern void JW_BeginFrame();
extern void JW_EndFrame();
extern void JW_JUTReport(int x, int y, int show_count, const char* fmt, ...);
extern void JW_SetLowResoMode(BOOL enable);
extern void JW_SetProgressiveMode(BOOL enable);
extern u32 JW_GetAramAddress(int resource_no);
extern u8* _JW_GetResourceAram(u32 aram_addr, u8* dst, size_t size);
extern void JW_SetFamicomMode(int enabled);
extern void JW_SetLogoMode(int mode);
extern void JW_Cleanup();

extern void* JC_JFWSystem_getSystemConsole();
extern void* JC_JFWSystem_getRootHeap();
extern void* JC_JFWSystem_getSystemHeap();

extern void* JC_JFWDisplay_getManager();
extern void JC_JFWDisplay_startFadeOut(void* manager, int len);
extern void JC_JFWDisplay_startFadeIn(void* manager, int len);
extern void JC_JFWDisplay_setFrameRate(void* manager, u16 framerate);

extern void JC_JKRAramHeap_dump(void* heap);
extern void* JC_JKRAram_getAramHeap();

extern int JC_JKRHeap_dump(void* heap);
extern s32 JC_JKRHeap_getTotalFreeSize(void* heap);

extern void JC_JKRExpHeap_changeGroupID(void* expheap, u8 groupId);

extern void* JC__JKRDvdToMainRam_byName(const char* name, u8* buf, JKRExpandSwitch expandSwitch);
extern BOOL JC__JKRDetachResource(void* ptr);

extern int JC_JUTConsole_isVisible(void* console);
extern void JC_JUTConsole_setVisible(void* console, BOOL visible);
extern void JC_JUTConsole_clear(void* console);
extern void JC_JUTConsole_scroll(void* console, int scroll);
extern int JC_JUTConsole_getPositionX(void* console);
extern void JC_JUTConsole_setPosition(void* console, int x, int y);
extern int JC_JUTConsole_getOutput(void* console);
extern int JC_JUTConsole_getLineOffset(void* console);
extern void JC_JUTConsole_dumpToTerminal(void* console, int lines);
extern void JC_JUTConsole_setOutput(void* console, int output);
extern void JC_JUTConsole_scrollToLastLine(void* console);
extern void JC_JUTConsole_scrollToFirstLine(void* console);
extern void JC_JUTConsole_scroll(void* console, int amount);
extern u32 JC_JUTConsole_getHeight(void* console);
extern u32 JC_JUTConsole_getUsedLine(void* console);

extern void* JC_JUTConsoleManager_getManager();
extern void JC_JUTConsoleManager_drawDirect(void* manager, int direct);

extern void* JC_JUTDbPrint_getManager();
extern void JC_JUTDbPrint_setVisible(void* dbprint, BOOL visible);

extern void* JC_JUTProcBar_getManager();
extern void JC_JUTProcBar_setVisible(void* procbar, BOOL visible);
extern void JC_JUTProcBar_setVisibleHeapBar(void* procbar, BOOL visible);

extern void* JC_JUTException_getManager();
extern void* JC_JUTException_getConsole();
extern BOOL JC_JUTException_isEnablePad(void* manager);
extern void JC_JUTException_readPad(void* mgr, u32* trigger, u32* button);
extern void JC_JUTException_waitTime(u32 time);
extern void JC_JUTException_enterAllPad(void* manager);
extern void JC_JUTException_setMapFile(const char* path);

extern void JC_JUTAssertion_changeDevice(int device);
extern void JC_JUTAssertion_changeDisplayTime(int displayTime);

extern void JC_JUTGamePad_read();

extern u32 JW_JUTGamepad_getButton();
extern u32 JW_JUTGamepad_getTrigger();
extern u32 JW_JUTGamepad_getErrorStatus();

#ifdef __cplusplus
}
#endif

#endif
