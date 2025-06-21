#include "jaudio_NES/aramcall.h"

#include "jaudio_NES/heapctrl.h"
#include "jaudio_NES/dummyrom.h"
#include "jaudio_NES/dvdthread.h"

#include "string.h"

jaheap_ aram_mother;

ARAMCallback ARCALL    = &LoadAram_Default;
static char extdir[64] = "/Banks/";

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
void Jac_RegisterARAMCallback(ARAMCallback callback)
{
	ARCALL = callback;
}

/*
 * --INFO--
 * Address:	8000D8A0
 * Size:	000064
 */
u32 LoadAram(char* filepath, u32* status, u32 dst)
{
	// GUH MUH BRUH
	volatile char** filepathGuh = (volatile char**)&filepath;
	volatile u32* dstGuh        = &dst;
	char* filepathMruh          = (char*)*filepathGuh;
	u32 dstMruh                 = *dstGuh;

	if (DVDT_LoadtoARAM(0, filepathMruh, dstMruh, 0, 0, status, NULL) == -1) {
		return 0;
	}
	return dst;
}

/*
 * --INFO--
 * Address:	8000D920
 * Size:	000068
 */
u32 LoadAramSingle(char* filepath, u32 src, u32 length, u32* status, u32 dst)
{
	// GUH MUH BRUH (this function is very stupidly written, why does this match?)
	u32 pad[1];
	volatile char** filepathGuh = (volatile char**)&filepath;
	volatile u32* srcGuh        = &src;
	volatile u32* lengthGuh     = &length;
	char* filepathMruh          = (char*)*filepathGuh;
	u32 lengthMuh               = *lengthGuh;
	u32 srcMuh                  = *srcGuh;
	// u32 dstMuh = *dstGuh;

	// Why is normal dst passed into this function when everything else isn't???
	if (DVDT_LoadtoARAM(0, filepathMruh, dst, srcMuh, lengthMuh, status, NULL) == -1) {
		return 0;
	}
	return dst;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000030
 */
void Jac_WaveDirectorySet(char* directory)
{
	strcpy(extdir, directory);
}

/*
 * --INFO--
 * Address:	........
 * Size:	00000C
 */
jaheap_* Get_AramMotherHeap(void)
{
	return &aram_mother;
}

/*
 * --INFO--
 * Address:	8000D9A0
 * Size:	00002C
 */
void Show_AramMotherHeap(void)
{
	Jac_ShowHeap(&aram_mother, 0);
}

/*
 * --INFO--
 * Address:	8000D9E0
 * Size:	00002C
 */
void Collect_AramMotherHeap(void)
{
	Jac_GarbageCollection_St(&aram_mother);
	Show_AramMotherHeap();
}

/*
 * --INFO--
 * Address:	8000DA20
 * Size:	00006C
 */
void Init_AramMotherHeap(void)
{
	void* alloc;
	u32 outSize;

	static BOOL inited = FALSE;
	if (!inited) {
		inited = TRUE;

		void* alloc = ARAllocFull(&outSize);
		Jac_InitMotherHeap(&aram_mother, (u32)alloc, outSize, 0);
	}
}

// Used only by `LoadAram_Default`.
static BOOL first = TRUE;

/*
 * --INFO--
 * Address:	8000DAA0
 * Size:	0000F8
 */
u32 LoadAram_Default(char* filename, u32 src, u32 length, u32* status, jaheap_* heap)
{
	char filepath[140];

	if (first) {
		Init_AramMotherHeap();
		first = FALSE;
	}

	strcpy(filepath, extdir);
	strcat(filepath, filename);

	if (src == 0 && length == 0) {
		if (!Jac_AllocHeap(heap, &aram_mother, DVDT_CheckFile(filepath))) {
			return 0;
		}
		return LoadAram(filepath, status, heap->startAddress);
	} else {
		if (!Jac_AllocHeap(heap, &aram_mother, length)) {
			return 0;
		}
		return LoadAramSingle(filepath, src, length, status, heap->startAddress);
	}
}

/*
 * --INFO--
 * Address:	8000DBA0
 * Size:	000038
 */
u32 LoadAram_All(char* filename, u32* status, jaheap_* heap)
{
	return ARCALL(filename, 0, 0, status, heap);
}

/*
 * --INFO--
 * Address:	8000DBE0
 * Size:	000028
 */
u32 LoadAram_One(char* filename, u32 src, u32 length, u32* status, jaheap_* heap)
{
	return ARCALL(filename, src, length, status, heap);
}
