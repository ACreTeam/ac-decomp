#include "PowerPC_EABI_Support/MetroTRK/trk.h"

static void TRK_fill_mem(void* dest, int val, size_t count);

__declspec(section ".init") void* TRK_memcpy(void* dest, const void* src, size_t count)
{
	u8* s = (u8*)src - 1;
	u8* d = (u8*)dest - 1;

	count++;

	while (--count) {
		*++d = *++s;
	}
}

__declspec(section ".init") void* TRK_memset(void* dest, int val, size_t count)
{
	TRK_fill_mem(dest, val, count);
	return dest;
}

/*
 * --INFO--
 * Address:	8021E7C0
 * Size:	0000C4
 */
static void TRK_fill_mem(void* dest, int value, size_t length)
{
#define cDest ((u8*)dest)
#define lDest ((u32*)dest)
	u32 val = (u8)value;
	u32 i;
	lDest = (u32*)dest;
	cDest = (u8*)dest;

	cDest--;

	if (length >= 32) {
		i = ~(u32)dest & 3;

		if (i) {
			length -= i;
			do {
				*++cDest = val;
			} while (--i);
		}

		if (val) {
			val |= val << 24 | val << 16 | val << 8;
		}

		lDest = (u32*)(cDest + 1) - 1;

		i = length >> 5;
		if (i) {
			do {
				*++lDest = val;
				*++lDest = val;
				*++lDest = val;
				*++lDest = val;
				*++lDest = val;
				*++lDest = val;
				*++lDest = val;
				*++lDest = val;
			} while (--i);
		}

		i = (length & 31) >> 2;

		if (i) {
			do {
				*++lDest = val;
			} while (--i);
		}

		cDest = (u8*)(lDest + 1) - 1;

		length &= 3;
	}

	if (length) {
		do {
			*++cDest = val;
		} while (--length);
	}

#undef cDest
#undef lDest
}
