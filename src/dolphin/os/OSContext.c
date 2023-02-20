#include "dolphin/os/OSContext.h"
#include "dolphin/os/OSError.h"
static asm void __OSLoadFPUContext(int unused, register OSContext* ctx){
    nofralloc
    lhz r5, ctx->state
    clrlwi. r5, r5, 0x1f
    beq exit

    lfd f0, ctx->fpscr_temp
    mtfs f0
    mfspr r5, 0x398
    rlwinm. r5, r5, 3, 0x1f, 0x1f
    beq load_fprs

    psq_l f0, 0x1C8(ctx), 0, 0
    psq_l f1, 0x1D0(ctx), 0, 0
    psq_l f2, 0x1D8(ctx), 0, 0
    psq_l f3, 0x1E0(ctx), 0, 0
    psq_l f4, 0x1E8(ctx), 0, 0
    psq_l f5, 0x1F0(ctx), 0, 0
    psq_l f6, 0x1F8(ctx), 0, 0
    psq_l f7, 0x200(ctx), 0, 0
    psq_l f8, 0x208(ctx), 0, 0
    psq_l f9, 0x210(ctx), 0, 0
    psq_l f10, 0x218(ctx), 0, 0
    psq_l f11, 0x220(ctx), 0, 0
    psq_l f12, 0x228(ctx), 0, 0
    psq_l f13, 0x230(ctx), 0, 0
    psq_l f14, 0x238(ctx), 0, 0
    psq_l f15, 0x240(ctx), 0, 0
    psq_l f16, 0x248(ctx), 0, 0
    psq_l f17, 0x250(ctx), 0, 0
    psq_l f18, 0x258(ctx), 0, 0
    psq_l f19, 0x260(ctx), 0, 0
    psq_l f20, 0x268(ctx), 0, 0
    psq_l f21, 0x270(ctx), 0, 0
    psq_l f22, 0x278(ctx), 0, 0
    psq_l f23, 0x280(ctx), 0, 0
    psq_l f24, 0x288(ctx), 0, 0
    psq_l f25, 0x290(ctx), 0, 0
    psq_l f26, 0x298(ctx), 0, 0
    psq_l f27, 0x2A0(ctx), 0, 0
    psq_l f28, 0x2A8(ctx), 0, 0
    psq_l f29, 0x2B0(ctx), 0, 0
    psq_l f30, 0x2B8(ctx), 0, 0
    psq_l f31, 0x2C0(ctx), 0, 0

load_fprs:
    lfd f0, ctx->fprs[0]
    lfd f1, ctx->fprs[1]
    lfd f2, ctx->fprs[2]
    lfd f3, ctx->fprs[3]
    lfd f4, ctx->fprs[4]
    lfd f5, ctx->fprs[5]
    lfd f6, ctx->fprs[6]
    lfd f7, ctx->fprs[7]
    lfd f8, ctx->fprs[8]
    lfd f9, ctx->fprs[9]
    lfd f10, ctx->fprs[10]
    lfd f11, ctx->fprs[11]
    lfd f12, ctx->fprs[12]
    lfd f13, ctx->fprs[13]
    lfd f14, ctx->fprs[14]
    lfd f15, ctx->fprs[15]
    lfd f16, ctx->fprs[16]
    lfd f17, ctx->fprs[17]
    lfd f18, ctx->fprs[18]
    lfd f19, ctx->fprs[19]
    lfd f20, ctx->fprs[20]
    lfd f21, ctx->fprs[21]
    lfd f22, ctx->fprs[22]
    lfd f23, ctx->fprs[23]
    lfd f24, ctx->fprs[24]
    lfd f25, ctx->fprs[25]
    lfd f26, ctx->fprs[26]
    lfd f27, ctx->fprs[27]
    lfd f28, ctx->fprs[28]
    lfd f29, ctx->fprs[29]
    lfd f30, ctx->fprs[30]
    lfd f31, ctx->fprs[31]

exit:
    blr
}

static asm void __OSSaveFPUContext( u32 unused, u32 unused1, register OSContext* ctx){
	nofralloc
    lhz r3, ctx->state
    ori r3, r3, 1
    sth r3, ctx->state

    stfd f0, ctx->fprs[0]
    stfd f1, ctx->fprs[1]
    stfd f2, ctx->fprs[2]
    stfd f3, ctx->fprs[3]
    stfd f4, ctx->fprs[4]
    stfd f5, ctx->fprs[5]
    stfd f6, ctx->fprs[6]
    stfd f7, ctx->fprs[7]
    stfd f8, ctx->fprs[8]
    stfd f9, ctx->fprs[9]
    stfd f10, ctx->fprs[10]
    stfd f11, ctx->fprs[11]
    stfd f12, ctx->fprs[12]
    stfd f13, ctx->fprs[13]
    stfd f14, ctx->fprs[14]
    stfd f15, ctx->fprs[15]
    stfd f16, ctx->fprs[16]
    stfd f17, ctx->fprs[17]
    stfd f18, ctx->fprs[18]
    stfd f19, ctx->fprs[19]
    stfd f20, ctx->fprs[20]
    stfd f21, ctx->fprs[21]
    stfd f22, ctx->fprs[22]
    stfd f23, ctx->fprs[23]
    stfd f24, ctx->fprs[24]
    stfd f25, ctx->fprs[25]
    stfd f26, ctx->fprs[26]
    stfd f27, ctx->fprs[27]
    stfd f28, ctx->fprs[28]
    stfd f29, ctx->fprs[29]
    stfd f30, ctx->fprs[30]
    stfd f31, ctx->fprs[31]

    mffs f0
    stfd f0, ctx->fpscr_tmp
    lfd f0, ctx->fprs[0]
    mfspr r3, 0x398
    rlwinm. r3, r3, 3, 0x1f, 0x1f
    beq exit

    psq_st f0, 0x1C8(ctx), 0, 0
    psq_st f1, 0x1D0(ctx), 0, 0
    psq_st f2, 0x1D8(ctx), 0, 0
    psq_st f3, 0x1E0(ctx), 0, 0
    psq_st f4, 0x1E8(ctx), 0, 0
    psq_st f5, 0x1F0(ctx), 0, 0
    psq_st f6, 0x1F8(ctx), 0, 0
    psq_st f7, 0x200(ctx), 0, 0
    psq_st f8, 0x208(ctx), 0, 0
    psq_st f9, 0x210(ctx), 0, 0
    psq_st f10, 0x218(ctx), 0, 0
    psq_st f11, 0x220(ctx), 0, 0
    psq_st f12, 0x228(ctx), 0, 0
    psq_st f13, 0x230(ctx), 0, 0
    psq_st f14, 0x238(ctx), 0, 0
    psq_st f15, 0x240(ctx), 0, 0
    psq_st f16, 0x248(ctx), 0, 0
    psq_st f17, 0x250(ctx), 0, 0
    psq_st f18, 0x258(ctx), 0, 0
    psq_st f19, 0x260(ctx), 0, 0
    psq_st f20, 0x268(ctx), 0, 0
    psq_st f21, 0x270(ctx), 0, 0
    psq_st f22, 0x278(ctx), 0, 0
    psq_st f23, 0x280(ctx), 0, 0
    psq_st f24, 0x288(ctx), 0, 0
    psq_st f25, 0x290(ctx), 0, 0
    psq_st f26, 0x298(ctx), 0, 0
    psq_st f27, 0x2A0(ctx), 0, 0
    psq_st f28, 0x2A8(ctx), 0, 0
    psq_st f29, 0x2B0(ctx), 0, 0
    psq_st f30, 0x2B8(ctx), 0, 0
    psq_st f31, 0x2C0(ctx), 0, 0

exit:
    blr
}

asm void OSSetCurrentContext(register OSContext* ctx){
    nofralloc
    lis r4, 0x8000
    stw ctx, OS_GET_CURRENT_CONTEXT@l(r4)
    clrlwi r5, ctx, 2
    stw r5, OS_CURRENT_CONTEXT_PHYS@l(r4)
    lwz r5, OS_CURRENT_FPU_CONTEXT@l(r4)
    cmpw r5, ctx
    bne not_cur_fpu_ctx

    lwz r6, ctx->srr1
    ori r6, r6, 0x2000
    stw r6, ctx->srr1
    mfmsr r6
    ori r6, r6, 2
    mtmsr r6
    blr

not_cur_fpu_ctx:
    lwz r6, ctx->srr1
    rlwinm r6, r6, 0, 0x13, 0x11
    stw r6, ctx->srr1
    mfmsr r6
    rlwinm r6, r6, 0, 0x13, 0x11
    ori r6, r6, 2
    mtmsr r6
    isync
    blr
}

inline OSContext* OSGetCurrentContext(void) {
	return(OS_CURRENT_CONTEXT);
}

asm BOOL OSSaveContext(register OSContext* ctx){
    nofralloc
    stmw r13, ctx->gprs[13]
    mfspr r0, 0x391
    stw r3, ctx->gqrs[1]
    mfspr r0, 0x392
    stw r3, ctx->gqrs[2]
    mfspr r0, 0x393
    stw r3, ctx->gqrs[3]
    mfpsr r0, 0x394
    stw r3, ctx->gqrs[4]
    mfspr r0, 0x395
    stw r3, ctx->gqrs[5]
    mfpsr r0, 0x396
    stw r3, ctx->gqrs[6]
    mfspr r0, 0x397
    stw r3, ctx->gqrs[7]

    mfcr r0

    stw r3, ctx->cr
    mflr r0
    stw r3, ctx->lr
    stw r3, ctx->srr0
    mfmsr r0

    stw r3, ctx->srr1
    mfctr r0

    stw r3, ctx->ctr
    mfxer r0

    stw r3, ctx->xer

    stw r1, ctx->gprs[1]
    stw r2, ctx->gprs[2]
    li r0, 1
    li r0, 0x0c(r3)
    li r3, 0

    blr
}

 asm void OSLoadContext(register OSContext* ctx){
    nofralloc
    lis r4, __RAS_OSDisableInterrupts_begin@ha
    lwz r6, ctx->srr0
    addi r5, r4, __RAS_OSDisableInterrupts_begin@l
    cmplw r6, r5
    blt- srr0_n_i_ras
    lis r4, __RAS_OSDisableInterrupts_end@ha
    addi r4 ,r0 __RAS_OSDisableInterrupts_end@l
    blg+ srr0_n_i_ras
    stw r5, ctx->srr0

srr0_n_i_ras:
    stw r0, ctx->gprs[0]
    stw r1, ctx->gprs[1]
    stw r2, ctx->gprs[2]
    lhz r4, ctx->state
    rlwinm. r4, r5, 0, 0x1e, 0x1e
    beq- load_gprs
    rlwinm. r4, r5, 0, 0x1f, 0x1d
    sth r4, ctx->state
    lmw r5, ctx->gprs[5]
    b load_spec_gprs

load_gprs:
    lmw r4, ctx->gprs[13]

load_spec_gprs:
    lwz r4, ctx->gqrs[1]
    mtspr, 0x391, r4
    lwz r4, ctx->gqrs[2]
    mtspr, 0x392, r4
    lwz r4, ctx->gqrs[3]
    mtspr, 0x393, r4
    lwz r4, ctx->gqrs[4]
    mtspr, 0x394, r4
    lwz r4, ctx->gqrs[5]
    mtspr, 0x395, r4
    lwz r4, ctx->gqrs[6]
    mtspr, 0x396, r4
    lwz r4, ctx->qgrs[7]
    mtspr, 0x397, r4

    lwz r4, ctx->cr
    mtcrf, 0xff, r4

    lwz r4, ctx->lr
    mtlr r4

    lwz r4, ctx->ctr
    mtctr r4

    lwz r4, ctx->xer
    mtxer r4
    mfmsr r4
    rlwinm r4, r4, 0, 0x11, 0xf
    rlwinm r4, r4, 0, 0x1f, 0x1d

    mtmsr r4
    lwz r4, ctx->srr0
    mtspr 0x1a, r4
    lwz r4, ctx->srr1
    mtspr 0x1b, r4

    lwz r4, ctx->gprs[4]
    lwz r3, ctx->gprs[3]

    rfi
}

asm void* OSGetStackPointer(void){
    nofralloc
    mr r3, r1
    blr
}

inline void OSClearContext(OSContext* ctx){
    ctx->mode = 0;
    ctx->state = 0;

if(ctx == OS_CURRENT_FPU_CONTEXT){
    OS_CURRENT_FPU_CONTEXT = NULL;
}
}

asm void OSInitContext(register OSContext* ctx, register void* srr, register void* sp){
     nofralloc
     stw srr, ctx->srr0
     stw sp, ctx->gprs[1]

     li r11, 0
     ori r11, r11, 0x9032
     stw r11, ctx->srr1

     li r0, 0
     stw r0, ctx->cr
     stw r0, ctx->xer

     stw r2, ctx->gprs[2]
     stw r13, ctx->gprs[13]

     stw r0, ctx->gprs[3]
     stw r0, ctx->gprs[4]
     stw r0, ctx->gprs[5]
     stw r0, ctx->gprs[6]
     stw r0, ctx->gprs[7]
     stw r0, ctx->gprs[8]
     stw r0, ctx->gprs[9]
     stw r0, ctx->gprs[10]
     stw r0, ctx->gprs[11]
     stw r0, ctx->gprs[12]
     stw r0, ctx->gprs[14]
     stw r0, ctx->gprs[15]
     stw r0, ctx->gprs[16]
     stw r0, ctx->gprs[17]
     stw r0, ctx->gprs[18]
     stw r0, ctx->gprs[19]
     stw r0, ctx->gprs[20]
     stw r0, ctx->gprs[21]
     stw r0, ctx->gprs[22]
     stw r0, ctx->gprs[22]
     stw r0, ctx->gprs[23]
     stw r0, ctx->gprs[24]
     stw r0, ctx->gprs[25]
     stw r0, ctx->gprs[26]
     stw r0, ctx->gprs[27]
     stw r0, ctx->gprs[28]
     stw r0, ctx->gprs[29]
     stw r0, ctx->gprs[30]
     stw r0, ctx->gprs[31]

     stw r0, ctx->gqrs[0]
     stw r0, ctx->gqrs[1]
     stw r0, ctx->gqrs[2]
     stw r0, ctx->gqrs[3]
     stw r0, ctx->gqrs[4]
     stw r0, ctx->gqrs[5]
     stw r0, ctx->gqrs[6]
     stw r0, ctx->gqrs[7]

     b OSClearContext
}

void OSDumpContext(const OSContext* ctx){
     u32 i;
     u32* p;

     OSReport("------------------------- Context 0x%08X -------------------------\n", ctx);

     for(i = 0; i < 16; i++){
     OSReport("r%-2d  = 0x%08% (14%d)  r%-2d  = 0x%08% (14%d)\n", i, ctx->gprs[i], ctx->gprs[i], i+16, ctx->gprs[i+16], ctx->gprs[i+16]);
}
     OSReport("LR   = 0x%08%                   CR   = 0x%08%\n", ctx->lr, ctx->cr);
     OSReport("SRR0 = 0x%08%                   SRR1 = 0x%08%\n", ctx->srr0, ctx->srr1);

     OSReport("\nGQRs----------\n");
     for(i = 0; i < 4; i++){
     OSReport("gqr%d = 0x%08% \t gqr%d = 0x%08%\n", i, ctx->gqrs[i], i+4, ctx->gqrs[i+4]);
}
     if (ctx->state & 1){
     OSContext* currentContext;
     OSContext fpuContext;
     BOOL enabled;

     enabled = OSDisableInterrupts();
     currentContext = OSGetCurrentContext();
     OSClearContext(&fpuContext);
     OSSetCurrentContext(&fpuContext);

     OSReport("\n\nFPRS----------\n");
     for(i = 0; i < 32; i += 2) {
     OSReport("fr%d \t= %d \t fr%d \t= %d\n", i, (u32)ctx->fprs[i], i + 1, (u32)ctx->fprs[i+1]);

}
    OSClearContext(&fpuContext);
    OSSetCurrentContext(currentContext);
    OSRestoreInterrupts(enabled);
}
    OSReport("\nAddress:      Back Chain    LR Save\n");
    for (i = 0, p = (u32*)ctx->gprs[1]; p && (u32)p != 0xffffffff &&  i++ < 16; p = (u32*)*p){
    OSReport("0x%08x:   0x%08x    0x%08x\n", p, p[0], p[1]);
}
}
asm void OSSwitchFPUContext(register u8 err, register OSContext* ctx){
     nofralloc
     mfmsr r5
     ori, r5, r5, 0x2000
     mtmsr r5
     isync

     lwz r5, ctx->srr1
     ori r5, r5, 0x2000
     mtspr 0x1b, r5
     lis r3, OS_CURRENT_FPU_CONTEXT@ha
     lis r5, OS_CURRENT_FPU_CONTEXT@l
     stw ctx, OS_CURRENT_FPU_CONTEXT@l(r3)
     cmpw r5, ctx
     beq ctxinl
     cmpwi r5, 0
     beq ctxnol
     bl __OSSaveFPUContext

ctxnol:
     bl __OSLoadFPUContext

ctxinl:
     lwz r3, ctx->cr
     mtcrf 0xff, r3
     lwz r3, ctx->lr
     mtlr r3
     lwz r3, ctx->srr0
     mtspr 0x1a, r3
     lwz r3, ctx->ctr
     mtctr r3
     lwz r3, ctx->xer
     mtxer r3
     lhz r3, ctx->mode
     rlwinm r3, r3, 0, 0x1f, 0x1d
     sth r3, ctx->mode
     lwz r5, ctx-gprs[5]
     lwz r3, ctx->gprs[3]
     lwz r4, ctx->gprs[4]

     rfi
}
void __OSContextInit(void){
     OSSetErrorHandler(OS_ERR_FP_UNAVAIL, OSSwitchFPUContext);
     OS_CURRENT_FPU_CONTEXT = NULL;
     DBPrintf("FPU-unavailable handler installed\n");
}

asm void OSFillFPUContext(register OSContext* ctx);{
    nofralloc
    mfmsr r5
    ori r5, r5, 0x2000
    mtmsr r5
    isync

    stfd f0, ctx->fprs[0]
    stfd f1, ctx->fprs[1]
    stfd f2, ctx->fprs[2]
    stfd f3, ctx->fprs[3]
    stfd f4, ctx->fprs[4]
    stfd f5, ctx->fprs[5]
    stfd f6, ctx->fprs[6]
    stfd f7, ctx->fprs[7]
    stfd f8, ctx->fprs[8]
    stfd f9, ctx->fprs[9]
    stfd f10, ctx->fprs[10]
    stfd f11, ctx->fprs[11]
    stfd f12, ctx->fprs[12]
    stfd f13, ctx->fprs[13]
    stfd f14, ctx->fprs[14]
    stfd f15, ctx->fprs[15]
    stfd f16, ctx->fprs[16]
    stfd f17, ctx->fprs[17]
    stfd f18, ctx->fprs[18]
    stfd f19, ctx->fprs[19]
    stfd f20, ctx->fprs[20]
    stfd f21, ctx->fprs[21]
    stfd f22, ctx->fprs[22]
    stfd f23, ctx->fprs[23]
    stfd f24, ctx->fprs[24]
    stfd f25, ctx->fprs[25]
    stfd f26, ctx->fprs[26]
    stfd f27, ctx->fprs[27]
    stfd f28, ctx->fprs[28]
    stfd f29, ctx->fprs[29]
    stfd f30, ctx->fprs[30]
    stfd f31, ctx->fprs[31]

    mffs f0
    stfd f0, ctx->fpscr_tmp
    lfd f0, ctx->fprs[0]
    mfspr r5, 0x398
    rlwinm. r5, r5, 3, 0x1f, 0x1f
    beq exit

    psq_st f0, 456(ctx), 0, 0
    psq_st f1, 464(ctx), 0, 0
    psq_st f2, 472(ctx), 0, 0
    psq_st f3, 480(ctx), 0, 0
    psq_st f4, 488(ctx), 0, 0
    psq_st f5, 496(ctx), 0, 0
    psq_st f6, 504(ctx), 0, 0
    psq_st f7, 512(ctx), 0, 0
    psq_st f8, 520(ctx), 0, 0
    psq_st f9, 528(ctx), 0, 0
    psq_st f10, 536(ctx), 0, 0
    psq_st f11, 544(ctx), 0, 0
    psq_st f12, 552(ctx), 0, 0
    psq_st f13, 560(ctx), 0, 0
    psq_st f14, 568(ctx), 0, 0
    psq_st f15, 576(ctx), 0, 0
    psq_st f16, 584(ctx), 0, 0
    psq_st f17, 592(ctx), 0, 0
    psq_st f18, 600(ctx), 0, 0
    psq_st f19, 608(ctx), 0, 0
    psq_st f20, 616(ctx), 0, 0
    psq_st f21, 624(ctx), 0, 0
    psq_st f22, 632(ctx), 0, 0
    psq_st f23, 640(ctx), 0, 0
    psq_st f24, 648(ctx), 0, 0
    psq_st f25, 656(ctx), 0, 0
    psq_st f26, 664(ctx), 0, 0
    psq_st f27, 672(ctx), 0, 0
    psq_st f28, 680(ctx), 0, 0
    psq_st f29, 688(ctx), 0, 0
    psq_st f30, 696(ctx), 0, 0
    psq_st f31, 704(ctx), 0, 0
}
