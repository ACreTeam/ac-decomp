#include "dolphin/os/OSError.h"
#include "dolphin/os/OSContext.h"
#include "dolphin/BASE/ppcarch.h"
#include "dolphin/dsp/dsp.h"
#include "dolphin/os/OSTime.h"

OSErrorHandler __OSErrorTable[16];

OSErrorHandler OSSetErrorHanlder(OSError error, OSErrorHandler handler){
	OSErrorHandler prevhandler = __OSErrorTable[error];
	__OSErrorTable[error] = handler;
	return(prevhandler);
}

void __OSUnhandledException(u8 error, OSContext* ctx, s32 sdirs, s32 dar){
	if(!(ctx->srr1) & (1 << 1))){
	OSReport("Non-recoverable exception %d", error);
}	else {
	if(__OSErrorTable[error] != NULL){
	OSDisableScheduler();
	OSErrorTable[error](error, ctx, sdirs, dar);
	OSEnableScheduler();
	__OSReschedule();
	OSLoadContext();
}
	if(error = ERROR_OS_DECREMENTER){
	OSLoadContext(ctx);
	OSReport("Unhandled Exception %d", error);
	}
	OSReport("\n");
	OSDumpContext(ctx);
	OSReport("\nDSISR = 0x%08x                   DAR  = 0X%08X\n", sdirs, dar);
	OSReport("TB = 0x%01611x\n", OSGetTime());
	switch (error) {
	case OS_ERROR_DSI:
	    OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access ""Invalid address 0x%x (read from DAR)\n", ctx->srr0, dar);
	break;
	case OS_ERROR_ISI:
	    OSReport("Attempted to fetch instruction from invalid adddress 0x%x ""(read from SRR0)\n",ctx->srr0);
	break;
	case OS_ERROR_PROGRAM:
	    OSReport("\nProgram exception : Possible illegal instruction/operation ""at or around 0x%x (read from SRR0)\n", ctx->srr0, dar);
	break;
	case 15:
	    OSReport("\n");
	    OSREport("AI DMA Address =   0x%04x%04x\n", __DSPRegs[24], __DSPRegs[25]);
	    OSReport(ARAM DMA Address = 0x%04x%04x\n", __DSPRegs[16], __DSPRegs[17]);
	    OSReport("DI DMA Address =   0x%08x\n", __DIRegs[5]);
	break;
}
	OSReport("\nLast interrupt (%d): SRR0 = 0x08x  TB = 0x%01611x\n", __OSLastInterrupt, __OSLastInterruptSrr0, __OSLastInterruptTime);
	PPCHalt();
}
