#ifndef JSYSWRAP_H
#define JSYSWRAP_H

#include "types.h"
#include "libjsys/jsyswrapper.h"
#include "dolphin/gx.h"
#include "dolphin/dvd.h"
#include "dolphin/pad.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CResTIMG {
	u8 mTextureFormat;              // _00
	u8 mTransparency; // _01
	u16 mSizeX;                     // _02
	u16 mSizeY;                     // _04
	u8 mWrapS;                      // _06
	u8 mWrapT;                      // _07
	u8 mPaletteFormat;              // _08
	u8 mColorFormat;                // _09
	u16 mPaletteEntryCount;         // _0A
	u32 mPaletteOffset;             // _0C
	GXBool mIsMIPmapEnabled;        // _10
	GXBool mDoEdgeLOD;              // _11
	GXBool mIsBiasClamp;            // _12
	GXBool mIsMaxAnisotropy;        // _13
	u8 mMinFilterType;              // _14
	u8 mMagFilterType;              // _15
	s8 mMinLOD;                     // _16
	s8 mMaxLOD;                     // _17
	u8 mTotalImageCount;            // _18
	u8 _19;                         // _19, unknown
	s16 mLODBias;                   // _1A
	u32 mImageDataOffset;           // _1C
} CResTIMG;

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
    RESOURCE_GIRL1,
    RESOURCE_GIRL2,
    RESOURCE_GIRL3,
    RESOURCE_GIRL4,
    RESOURCE_GIRL5,
    RESOURCE_GIRL6,
    RESOURCE_GIRL7,
    RESOURCE_GIRL8,
    RESOURCE_D_BG_ISLAND_SCH,

    RESOURCE_NUM
};

enum {
    JUT_MAINSTICK_UP = 0x8000000,
    JUT_MAINSTICK_DOWN = 0x4000000,
    JUT_MAINSTICK_RIGHT = 0x2000000,
    JUT_MAINSTICK_LEFT = 0x1000000,
    JUT_CSTICK_UP = 0x80000,
    JUT_CSTICK_DOWN = 0x40000,
    JUT_CSTICK_RIGHT = 0x20000,
    JUT_CSTICK_LEFT = 0x10000,
    JUT_START = 0x1000,
    JUT_Y = 0x800,
    JUT_X = 0x400,
    JUT_B = 0x200,
    JUT_A = 0x100,
    JUT_L = 0x40,
    JUT_R = 0x20,
    JUT_Z = 0x10,
    JUT_DPAD_UP = 0x8,
    JUT_DPAD_DOWN = 0x4,
    JUT_DPAD_RIGHT = 0x2,
    JUT_DPAD_LEFT = 0x1
};

extern void JW_UpdateVideoMode();
extern void JW_SetProgressiveMode(int enabled);
extern void JW_SetLowResoMode(int enabled);
extern void JW_SetFamicomMode(int enabled);
extern void JW_SetVideoPan(u16 origin_x, u16 origin_y, u16 width, u16 height);
extern void JW_SetLogoMode(int enabled);
extern void JW_JUTGamePad_read();
extern void JW_getPadStatus(PADStatus* padStatus);
extern int JW_JUTGamepad_getErrorStatus();
extern u32 JW_JUTGamepad_getButton();
extern u32 JW_JUTGamepad_getTrigger();
extern f32 JW_JUTGamepad_getSubStickValue();
extern s16 JW_JUTGamepad_getSubStickAngle();
extern void JW_BeginFrame();
extern void JW_EndFrame();
extern int JW_setClearColor(u8 r, u8 g, u8 b);
extern u32 JW_GetAramAddress(int res_no);
extern u8* _JW_GetResourceAram(u32 aram_addr, u8* dst, u32 size);
extern u32 JW_GetResSizeFileNo(int res_no);
extern void JW_Init();
extern void JW_Init2();
extern void JW_Init3();
extern void JW_Cleanup();

#ifdef __cplusplus
}
#endif

#endif
