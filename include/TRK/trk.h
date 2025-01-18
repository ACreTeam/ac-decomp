#ifndef _DOLPHIN_TRK_H
#define _DOLPHIN_TRK_H

#include <dolphin/types.h>
#include "TRK/trktypes.h"
#include "TRK/ppc_reg.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

////// MSG HANDLING FUNCTIONS //////
DSError TRKDoConnect(MessageBuffer*);
DSError TRKDoDisconnect(MessageBuffer*);
DSError TRKDoReset(MessageBuffer*);
DSError TRKDoVersions(MessageBuffer*);
DSError TRKDoSupportMask(MessageBuffer*);
DSError TRKDoOverride(MessageBuffer*);
DSError TRKDoReadMemory(MessageBuffer*);
DSError TRKDoWriteMemory(MessageBuffer*);
DSError TRKDoReadRegisters(MessageBuffer*);
DSError TRKDoWriteRegisters(MessageBuffer*);
DSError TRKDoSetOption(MessageBuffer*);
DSError TRKDoContinue(MessageBuffer*);
DSError TRKDoStep(MessageBuffer*);
DSError TRKDoStop(MessageBuffer*);
DSError TRKDoUnsupported(MessageBuffer*);
DSError TRKDoCPUType(MessageBuffer*);
DSError TRKDoFlushCache(MessageBuffer*);

void SetBufferPosition(MessageBuffer*, u32);
void SetTRKConnected(int);
int GetTRKConnected(void);

DSError TRKGetFreeBuffer(int*, MessageBuffer**);
void OutputData(void* data, int length);
void TRKResetBuffer(MessageBuffer* msg, u8 keepData);

DSError TRKReadBuffer1_ui64(MessageBuffer* buffer, u64* data);
DSError TRKAppendBuffer1_ui64(MessageBuffer* buffer, const u64 data);
////////////////////////////////////

/////// DOLPHIN TRK FUNCTIONS //////
void InitMetroTRK(void);
void InitMetroTRK_BBA(void);
void EnableMetroTRKInterrupts(void);

void TRKLoadContext(OSContext* ctx, u32);
void TRKSaveExtended1Block();
void TRKRestoreExtended1Block();
int InitMetroTRKCommTable(int);
void TRK_board_display(char*);
////////////////////////////////////

////////// GDEV FUNCTIONS //////////
int gdev_cc_initialize(void* flagOut, __OSInterruptHandler handler);
int gdev_cc_shutdown();
int gdev_cc_open();
int gdev_cc_close();
int gdev_cc_read(u8* dest, int size);
int gdev_cc_write(const u8* src, int size);
int gdev_cc_pre_continue();
int gdev_cc_post_stop();
int gdev_cc_peek();
int gdev_cc_initinterrupts();
////////////////////////////////////

/////////// UDP FUNCTIONS //////////
int udp_cc_initialize(void* flagOut, __OSInterruptHandler handler);
int udp_cc_shutdown();
int udp_cc_open();
int udp_cc_close();
int udp_cc_read(u8* dest, int size);
int udp_cc_write(const u8* src, int size);
int udp_cc_pre_continue();
int udp_cc_post_stop();
int udp_cc_peek();
int udp_cc_initinterrupts();
////////////////////////////////////

/////////// DDH FUNCTIONS //////////
#define DDH_ERR_NOT_INITIALIZED     -0x2711
#define DDH_ERR_ALREADY_INITIALIZED -0x2715
#define DDH_ERR_READ_ERROR          -0x2719

int ddh_cc_initialize(void* flagOut, __OSInterruptHandler handler);
int ddh_cc_shutdown();
int ddh_cc_open();
int ddh_cc_close();
int ddh_cc_read(u8* dest, int size);
int ddh_cc_write(const u8* src, int size);
int ddh_cc_pre_continue();
int ddh_cc_post_stop();
int ddh_cc_peek();
int ddh_cc_initinterrupts();
////////////////////////////////////

////////// EVENT FUNCTIONS /////////
void TRKConstructEvent(TRKEvent* event, int eventType);
void TRKDestructEvent(TRKEvent* event);
DSError TRKPostEvent(TRKEvent* event);
BOOL TRKGetNextEvent(TRKEvent* event);
DSError TRKDispatchMessage(MessageBuffer*);
void* TRKGetBuffer(int);
void TRKReleaseBuffer(int);
void TRKGetInput();
////////////////////////////////////

///////// TARGET FUNCTIONS /////////
DSError TRKTargetContinue(void);
DSError TRKTargetInterrupt(TRKEvent*);
BOOL TRKTargetStopped();
void TRKTargetSetStopped(uint);
DSError TRKTargetSupportRequest();
////////////////////////////////////

////// NUB AND MEM FUNCTIONS ///////
DSError TRKAppendBuffer_ui8(MessageBuffer*, const u8*, int);
DSError TRKSetBufferPosition(MessageBuffer*, u32);

DSError TRKMessageSend(MessageBuffer*);
void TRKSwapAndGo(void);
DSError TRKInitializeNub(void);
DSError TRKTerminateNub(void);
void TRKNubWelcome(void);
void TRKNubMainLoop(void);

DSError TRKInitializeMutex(void*);
DSError TRKAcquireMutex(void*);
DSError TRKReleaseMutex(void*);
void* TRK_memcpy(void* dst, const void* src, size_t n);
////////////////////////////////////

/////// INITIALIZE FUNCTIONS ///////
DSError TRKInitializeEventQueue();
DSError TRKInitializeMessageBuffers();
DSError TRKInitializeDispatcher();
DSError InitializeProgramEndTrap();
DSError TRKInitializeSerialHandler();
DSError TRKTerminateSerialHandler();
DSError TRKInitializeTarget();
////////////////////////////////////

////////// EXI2 FUNCTIONS //////////
/* EXI2 */
void UnreserveEXI2Port(void);
void ReserveEXI2Port(void);
////////////////////////////////////

/////////// MW FUNCTIONS ///////////
void MWTRACE(u8, char*, ...);
////////////////////////////////////

//////// SUPPORT FUNCTIONS /////////
DSError TRKRequestSend();
u32 TRKAccessFile(u32, u32, u32*, u8*);
////////////////////////////////////

////////// OTHER FUNCTIONS /////////
DSError TRK_main(void);
UARTError InitializeUART(UARTBaudRate baudRate);
DSError TRKInitializeIntDrivenUART(u32, u32, u32, void*);
int TRKPollUART();
UARTError TRKReadUARTN(void*, u32);
UARTError TRKWriteUARTN(const void* bytes, u32 length);
void usr_put_initialize();
void TRKTargetSetInputPendingPtr(void*);
void SetUseSerialIO(u8);
u8 GetUseSerialIO(void);

DSError TRKTargetAddStopInfo(MessageBuffer*);
void TRKTargetAddExceptionInfo(MessageBuffer*);
void TRKInterruptHandler();
BOOL usr_puts_serial(const char* msg);
////////////////////////////////////

//////// EXTERNAL DECLARES /////////
extern BOOL gTRKBigEndian;
extern void* gTRKInputPendingPtr;
extern ProcessorState_PPC gTRKCPUState;
extern ProcessorRestoreFlags_PPC gTRKRestoreFlags;
extern u8 gTRKInterruptVectorTable[];
extern TRKState gTRKState;
extern MessageBuffer gTRKMsgBufs[3];
////////////////////////////////////

////////// USEFUL STATICS //////////
static inline DSError TRKAppendBuffer1_ui8(MessageBuffer* buffer, const u8 data)
{
	if (buffer->position >= 0x880) {
		return DS_MessageBufferOverflow;
	}

	buffer->data[buffer->position++] = data;
	buffer->length++;
	return DS_NoError;
}
////////////////////////////////////

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
