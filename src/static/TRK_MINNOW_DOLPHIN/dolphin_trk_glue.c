#include "PowerPC_EABI_Support/MetroTRK/trk.h"
#include "OdemuExi2/odemuexi/DebuggerDriver.h"
#include "amcstubs/AmcExi2Stubs.h"

#define BUFF_LEN 4362

u8 gWriteBuf[BUFF_LEN];
u8 gReadBuf[BUFF_LEN];
s32 _MetroTRK_Has_Framing;
s32 gReadCount;
s32 gReadPos;
s32 gWritePos;

DBCommTable gDBCommTable = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

/*
 * --INFO--
 * Address:	80220460
 * Size:	000088
 */
asm void TRKLoadContext(OSContext* ctx, u32 a)
{
#ifdef __MWERKS__ // clang-format off
    nofralloc
    lwz r0, OSContext.gpr[0](r3)
    lwz r1, OSContext.gpr[1](r3)
    lwz r2, OSContext.gpr[2](r3)
    lhz r5, OSContext.state(r3)
    rlwinm. r6, r5, 0, 0x1e, 0x1e
    beq lbl_80371C1C
    rlwinm r5, r5, 0, 0x1f, 0x1d
    sth r5, OSContext.state(r3)
    lmw r5, OSContext.gpr[5](r3)
    b lbl_80371C20
lbl_80371C1C:
    lmw r13, OSContext.gpr[13](r3)
lbl_80371C20:
    mr r31, r3
    mr r3, r4
    lwz r4, OSContext.cr(r31)
    mtcrf 0xff, r4
    lwz r4, OSContext.lr(r31)
    mtlr r4
    lwz r4, OSContext.ctr(r31)
    mtctr r4
    lwz r4, OSContext.xer(r31)
    mtxer r4
    mfmsr r4
    rlwinm r4, r4, 0, 0x11, 0xf //Turn off external exceptions
    rlwinm r4, r4, 0, 0x1f, 0x1d //Turn off recoverable exception flag
    mtmsr r4
    mtsprg 1, r2
    lwz r4, OSContext.gpr[3](r31)
    mtsprg 2, r4
    lwz r4, OSContext.gpr[4](r31)
    mtsprg 3, r4
    lwz r2, OSContext.srr0(r31)
    lwz r4, OSContext.srr1(r31)
    lwz r31, OSContext.gpr[31](r31)
    b TRKInterruptHandler
#endif // clang-format on
}
/*
 * --INFO--
 * Address:	802204E8
 * Size:	000038
 */
void TRKEXICallBack(__OSInterrupt param_0, OSContext* ctx)
{
	OSEnableScheduler();
	TRKLoadContext(ctx, 0x500);
}

/*
 * --INFO--
 * Address:	80220520
 * Size:	0000E8
 */
int InitMetroTRKCommTable(int hwId)
{
	int result;

	if (hwId == HARDWARE_GDEV) {
        OSReport("MetroTRK : Set to GDEV hardware\n");
		result = Hu_IsStub();

		gDBCommTable.initialize_func      = (DBCommInitFunc)DBInitComm;
		gDBCommTable.init_interrupts_func = (DBCommFunc)DBInitInterrupts;
		gDBCommTable.peek_func            = (DBCommFunc)DBQueryData;
		gDBCommTable.read_func            = (DBCommReadFunc)DBRead;
		gDBCommTable.write_func           = (DBCommWriteFunc)DBWrite;
		gDBCommTable.open_func            = (DBCommFunc)DBOpen;
		gDBCommTable.close_func           = (DBCommFunc)DBClose;
	} else {
        OSReport("MetroTRK : Set to AMC DDH hardware\n");
		result = AMC_IsStub();

		gDBCommTable.initialize_func      = (DBCommInitFunc)EXI2_Init;
		gDBCommTable.init_interrupts_func = (DBCommFunc)EXI2_EnableInterrupts;
		gDBCommTable.peek_func            = (DBCommFunc)EXI2_Poll;
		gDBCommTable.read_func            = (DBCommReadFunc)EXI2_ReadN;
		gDBCommTable.write_func           = (DBCommWriteFunc)EXI2_WriteN;
		gDBCommTable.open_func            = (DBCommFunc)EXI2_Reserve;
		gDBCommTable.close_func           = (DBCommFunc)EXI2_Unreserve;
	}

	return result;
}

/*
 * --INFO--
 * Address:	8022060C
 * Size:	000040
 */
DSError TRKInitializeIntDrivenUART(u32 param_0, u32 param_1, u32 param_2, volatile u8** param_3)
{
	gDBCommTable.initialize_func(param_3, TRKEXICallBack);
	return DS_NoError;
}

/*
 * --INFO--
 * Address:	8022064C
 * Size:	000030
 */
void EnableEXI2Interrupts(void)
{
	gDBCommTable.init_interrupts_func();
}

/*
 * --INFO--
 * Address:	8022067C
 * Size:	000030
 */
int TRKPollUART(void)
{
	return gDBCommTable.peek_func();
}

/*
 * --INFO--
 * Address:	802206AC
 * Size:	000044
 */
UARTError TRKReadUARTN(void* bytes, u32 length)
{
	int readErr = gDBCommTable.read_func(bytes, length);
	return readErr == 0 ? 0 : -1;
}

/*
 * --INFO--
 * Address:	802206F0
 * Size:	000044
 */
UARTError TRKWriteUARTN(const void* bytes, u32 length)
{
	int writeErr = gDBCommTable.write_func(bytes, length);
	return writeErr == 0 ? 0 : -1;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000050
 */
UARTError WriteUARTFlush(void)
{
	UARTError readErr = 0;

	while (gWritePos < 0x800) {
		gWriteBuf[gWritePos] = 0;
		gWritePos++;
	}
	if (gWritePos != 0) {
		readErr   = TRKWriteUARTN(gWriteBuf, gWritePos);
		gWritePos = 0;
	}
	return readErr;
}
/*
 * --INFO--
 * Address:	........
 * Size:	00002C
 */
UARTError WriteUART1(u8 arg0)
{
	gWriteBuf[gWritePos++] = arg0;
	return 0;
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000F8
 */
UARTError TRKReadUARTPoll(u8* arg0)
{
	UARTError readErr = 4;
	s32 cnt;

	if (gReadPos >= gReadCount) {
		gReadPos = 0;
		cnt = gReadCount = TRKPollUART();
		if (cnt > 0) {
			if (cnt > BUFF_LEN) {
				gReadCount = BUFF_LEN;
			}
			readErr = TRKReadUARTN(gReadBuf, gReadCount);
			if (readErr != 0) {
				gReadCount = 0;
			}
		}
	}
	if (gReadPos < gReadCount) {
		*arg0   = gReadBuf[gReadPos++];
		readErr = 0;
	}
	return readErr;
}

/*
 * --INFO--
 * Address:	80220734
 * Size:	000030
 */
void ReserveEXI2Port(void)
{
	gDBCommTable.open_func();
}

/*
 * --INFO--
 * Address:	80220764
 * Size:	000030
 */
void UnreserveEXI2Port(void)
{
	gDBCommTable.close_func();
}

/*
 * --INFO--
 * Address:	80220794
 * Size:	000024
 */
void TRK_board_display(char* str)
{
	OSReport(str);
}

/*
 * --INFO--
 * Address:	80220608
 * Size:	000004
 */
void TRKUARTInterruptHandler(void)
{
}
