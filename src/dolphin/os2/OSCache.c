#include "dolphin/os/OSCache.h"
//Needs OSError stuff
asm void DCEnable(void){
	nofralloc
	sync
	mfspr r3, 0x3f0
	ori r3, r3, 0x4000
	mtspr 0x3f0, r3
	blr
}
asm void DCInvalidateRange(register void* buf, register u32 len){
	nofralloc
	cmplwi len, 0
	blelr-
	
	clrlwi. r5, buf, 0x1b
	beq- pi_r
	addi len, len, 0x20
	
pi_r:
	addi len, len, 0x1f
	srwi len, len, 5
	mtctr len
	
inv_ran:
	dcbi 0, buf
	addi buf, buf, 0x20
	bdnz inv_ran
	
	blr
}
asm void DCFlushRange(register void* buf, register u32 len){
	nofralloc
	cmplwi len, 0
	blelr-
	
	clrlwi. r5, buf, 0x1b
	beq- pf_r
	addi len, len, 0x20
	
pf_r:
	addi len, len, 0x1f
	srwi len, len, 5
	mtctr len
	
fls_ran:
	dcbf 0, buf
	addi buf, buf, 0x20
	bdnz fls_ran
	sc
	blr
}

asm void DCStoreRange(register void* buf, register u32 len){
	nofralloc
	cmplwi len, 0
	blelr-
	
	clrlwi. r5, buf, 0x1b
	beq- ps_r
	addi len, len, 0x20
	
ps_r:
	addi len, len, 0x1f
	srwi len, len, 5
	mtctr len
	
st_ran:
	dcbst 0, buf
	addi buf, buf, 0x20
	bdnz st_ran
	sc
	blr
}

asm void DCFlushRangeNoSync(register void* buf, register u32 len){
	nofralloc
	cmplwi len, 0
	blelr-
	
	clrlwi. r5, buf, 0x1b
	beq- pfns_r
	addi len, len, 0x20
	
pfns_r:
	addi len, len, 0x1f
	srwi len, len, 5
	mtctr len
	
fls_ranns:
	dcbf 0, buf
	addi buf, buf, 0x20
	bdnz fls_ranns
	blr
}

asm void DCStoreRangeNoSync(register void* buf, register u32 len){
	nofralloc
	cmplwi len, 0
	blelr-
	
	clrlwi. r5, buf, 0x1b
	beq- psns_r
	addi len, len, 0x20
	
psns_r:
	addi len, len, 0x1f
	srwi len, len, 5
	mtctr len
	
st_ranns:
	dcbst 0, buf
	addi buf, buf, 0x20
	bdnz st_ranns
	sc
	blr
}

asm void DCZeroRange(register void* buf, register u32 len){
	nofralloc
	cmplwi len, 0
	blelr-
	
	clrlwi. r5, buf, 0x1b
	beq- pzr_r
	addi len, len, 0x20
	
pzr_r:
	addi len, len, 0x1f
	srwi len, len, 5
	mtctr len
	
z_ran:
	dcbz 0, buf
	addi buf, buf, 0x20
	bdnz z_ran
	blr
}

asm void DCTouchRange(register void* buf, register u32 len){
	nofralloc
	cmplwi len, 0
	blelr-
	
	clrlwi. r5, buf, 0x1b
	beq- ptor_r
	addi len, len, 0x20
	
ptor_r:
	addi len, len, 0x1f
	srwi len, len, 5
	mtctr len
	
t_ran:
	dcbt 0, buf
	addi buf, buf, 0x20
	bdnz t_ran
	blr
}

asm void ICInvalidateRange(register void* buf, register u32 len){
	nofralloc
	cmplwi len, 0
	blelr-
	
	clrlwi. r5, buf, 0x1b
	beq- pir_r
	addi len, len, 0x20
	
pir_r:
	addi len, len, 0x1f
	srwi len, len, 5
	mtctr len
	
i_ran:
	icbi 0, buf
	addi buf, buf, 0x20
	bdnz i_ran
	sync
	isync
	blr
}
asm void ICFlashInvalidate(void){
	nofralloc
	mfspr r3, 0x3f0
	ori r3, r3, 0x800
	mtspr 0x3f0, r3
	blr
}

asm void ICEnable(void){
	nofralloc
	isync
	mfspr r3, 0x3f0
	ori r3, r3, 0x8000
	mtspr 0x3f0, r3
	blr
}

asm void LCDisable(void){
	nofralloc
	lis r3, 0xE000
	li r4, 0x200
	mtctr r4
dis:
	dcbi 0, r3
	addi r3, r3, 0x20
	bdnz dis
	mfspr r4, 0x398
	rlwinm r4, r4, 0, 4, 2
	mtspr 0x398, r4
	blr
}


