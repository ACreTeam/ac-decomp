#include "dolphin/os/OSMemory.h"

u32 OSGetConsoleSimulatedMemSize(void){
	return(SIM_MEM);
}
static bool OnReset(bool final){
	if (final) {
		__MEMRegs[8] = 0xff;
		__OSMaskInterrupts(0xF0000000);
	}
	return true;
}
static void MEMInterruptsHandler(__OSInterrupt interrupt, OSContext* ctx){
	u32 cause = __MEMRegs[0xf];
	u32 addr  =  (((u32) __MEMRegs[0x12] & 0x3ff) << 16) | __MEMRegs[0x11];
	__MEMRegs[0x10] = 0;
	
	if(__OSErrorTable[OS_ERROR_PROTECTION]) {
		__OSErrorTable[OS_ERROR_PROTECTION](OS_ERROR_PROTECTION, ctx, cause, adr);
		return;
	}
		__OSUnhandledException(OS_ERROR_PROTECTION, ctx, cause, addr);
}