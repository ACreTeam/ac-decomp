extern s32 __DSPCheckMXICBoot2(DSPTaskInfo2* task) {
    u32 mail;

    while (DSPCheckMailFromDSP() == 0);
    mail = DSPReadMailFromDSP();

    if((mail + 0x7F8F0000) == 0xFEED){
        DSPSendMailToDSP(0x80F3A001);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP((u32)task->iram_mmem_addr);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP(0x80F3A002);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP(task->iram_length);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP(0x80F3C002);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP(task->iram_addr);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP(0x80F3B002);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP(0x80F3D001);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP(task->dsp_init_vector);
        while (DSPCheckMailToDSP() != 0);

        return 1;
    }

    if((mail + 0x3F010000) == 0 || (mail + 0x3F010000) == 1){
        DSPSendMailToDSP(0xC0028073);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP(0xC000FFCE);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP((u32)task->iram_mmem_addr >> 16 | 0xC0010000);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP(0xC000FFCF);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP((u16)task->iram_mmem_addr | 0xC0010000);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP(0xC000FFCD);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP(task->iram_addr | 0xC0010000); 
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP(0xC000FFC9);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP(0xC0010002);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP(0xC000FFCB);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP(task->iram_length | 0xC0010000);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP(0xC0028073);
        while (DSPCheckMailToDSP() != 0);

        DSPSendMailToDSP(task->dsp_init_vector | 0xC0020000);
        while (DSPCheckMailToDSP() != 0);

        return 1;
    }

    return 0;
}


extern void DSPInit() {

}


extern void DSPInit2 (DSPTaskInfo2* task){
    BOOL enable;
    u16 tmp;
    
    enable = OSDisableInterrupts();
    __OSUnmaskInterrupts(OS_INTERRUPTMASK_DSP_DSP);
    
    tmp = __DSPRegs[DSP_CONTROL_STATUS];
    tmp = (tmp & ~0xA8)| 0x800;
    __DSPRegs[DSP_CONTROL_STATUS] = tmp;
    
    tmp = __DSPRegs[DSP_CONTROL_STATUS];
    tmp = (tmp & ~0xAC) ;
    __DSPRegs[DSP_CONTROL_STATUS] = tmp;
    
    OSRestoreInterrupts(enable);

    if(__DSPCheckMXICBoot2(task) != 1){ 
        OSPanic("mxic.c", 357,"DSPInit(): MXIC Boot failed.");
    }
}


