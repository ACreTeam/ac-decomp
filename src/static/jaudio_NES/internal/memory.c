#include "jaudio_NES/memory.h"

/*
 * --INFO--
 * Address:	........
 * Size:	00001C
 */
void __CalcRelf(f32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000170
 */
void MakeReleaseTable()
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000A0
 */
void Nas_ResetIDtable()
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000E0
 */
void Nas_ForceStopChannel(s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00006C
 */
void Nas_ForceReleaseChannel(s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000084
 */
void Nas_ForceStopSeq(s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000030
 */
void* Nas_CacheOff(u8*, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00006C
 */
void Nas_2ndHeapAlloc_CL(ALHeap*, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00006C
 */
void* Nas_2ndHeapAlloc(ALHeap*, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00003C
 */
void Nas_NcHeapAlloc(ALHeap*, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00003C
 */
void Nas_NcHeapAlloc_CL(ALHeap*, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000054
 */
void* Nas_HeapAlloc_CL(ALHeap*, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000048
 */
void Nas_TmpAlloc(ALHeap*, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000034
 */
void Nas_HeapFree(ALHeap*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80005640
 * Size:	00006C
 */
void* Nas_HeapAlloc(ALHeap* heap, s32 size)
{
	s32* REF_size;

	REF_size        = &size;
	u32 roundedSize = ALIGN_NEXT(size, 32);
	if (!heap->base) {
		return NULL;
	}

	u8* prev = heap->current;
	if (prev + roundedSize <= heap->base + heap->length) {
		heap->current = prev + roundedSize;
	} else {
		return NULL;
	}

	heap->count++;
	heap->last = prev;
	return prev;
}

/*
 * --INFO--
 * Address:	800056C0
 * Size:	000058
 */
void Nas_HeapInit(ALHeap* heap, u8* p2, s32 p3)
{
	ALHeap** REF_heap;

	int length;

	REF_heap    = &heap;
	heap->count = 0;
	if (!p2) {
		heap->length  = 0;
		heap->current = NULL;
		heap->last    = NULL;
	} else {
		length        = p3 - ((u32)p2 & 0x1F);
		heap->base    = (u8*)ALIGN_NEXT((u32)p2, 32);
		heap->current = heap->base;
		heap->length  = length;
		heap->last    = NULL;
	}
}

/*
 * --INFO--
 * Address:	........
 * Size:	000018
 */
void Nas_SzStayClear(SZStay*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00003C
 */
void Nas_SzAutoClear(SZAuto*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000014
 */
// void Nas_SzCustomClear(SZCustom*)
// {
// 	// UNUSED FUNCTION
// }

/*
 * --INFO--
 * Address:	........
 * Size:	00010C
 */
void Nas_SzStayDelete(s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000068
 */
void Nas_SzHeapReset(u32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000058
 */
void Nas_SzHeapDivide(AudioHeapstrc*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000014
 */
void Nas_SzDataDivide(DataHeapstrc*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000B4
 */
void Nas_SzStayDivide(StayHeapstrc*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000B4
 */
void Nas_SzAutoDivide(AutoHeapstrc*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0006CC
 */
void* Nas_SzHeapAlloc(s32, s32, s32, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000064
 */
u32 Nas_SzCacheCheck(s32, s32, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000114
 */
void __Nas_SzCacheCheck_Inner(s32, s32, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000D4
 */
void Nas_InitFilterCoef(f32, f32, u16*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000020
 */
void Nas_ClearFilter(s16*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000040
 */
void Nas_SetLPFilter(s16*, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000044
 */
void Nas_SetHPFilter(s16*, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000134
 */
void Nas_SetBPFilter(s16*, s32, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000004
 */
void __DownDelay(delay*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000A0
 */
void __Nas_DelayDown()
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000048
 */
void __Nas_DacClear()
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000258
 */
s32 Nas_SpecChange()
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0006B4
 */
void __Nas_MemoryReconfig()
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00005C
 */
void* EmemOnCheck(s32, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00007C
 */
void* EmemAlloc(s32, s32, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000064
 */
void Nas_Alloc_Single(s32, s32, u8*, char, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000C4
 */
void Nas_Init_Single(s32, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000200
 */
void __Nas_Alloc_Single_Auto_Inner(s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00012C
 */
void __SearchBank(SwMember*, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000EC
 */
void __KillSwMember(SwMember*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000034
 */
void __RomAddrSet(SwMember*, smzwavetable*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000094
 */
void __Nas_Alloc_Single_Stay_Inner(s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000040
 */
void __Do_EmemKill(SwMember*, s32, s32, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000128
 */
void Emem_KillSwMember()
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000A0
 */
void __RestoreAddr(Wavelookuptable*, smzwavetable*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000030
 */
void DirtyWave(s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000030
 */
void EntryWave(s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000238
 */
void __ExchangeWave(s32, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000088
 */
void Dirty_AllWave()
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000AC
 */
void __Nas_GetCompressBuffer(delay*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00028C
 */
void Nas_SetDelayLineParam(s32, s32, s32, s32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0001E0
 */
void Nas_SetDelayLine(s32, fxconfig_*, s32)
{
	// UNUSED FUNCTION
}
