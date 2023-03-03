#include "_mem.h"

__declspec(section ".init") void* memset(void* dst, int val, size_t size){
    __fill_mem(dst,val, size);

    return dst;
}

__declspec(section ".init") void __fill_mem(void* dst, int val, size_t n){
 	u32	v = (u8) val;
	u32	i;
	
	((u8 *) dst) = ((u8 *) dst) - 1;
	
	if (n >= 32)
	{
		i = (~ (u32) dst) & 3;

		if (i) {
			n -= i;
			
			do {
				*++(((u8 *) dst)) = v;
			} while (--i);
		}
	
		if (v)
			v |= v << 24 | v << 16 | v <<  8;
		
		((u32 *) dst) = ((u32 *) (((u8 *) dst) + 1)) - 1;
		
		i = n >> 5;
		
		if (i) {
			do {
				*++((u32 *) dst) = v;
				*++((u32 *) dst) = v;
				*++((u32 *) dst) = v;
				*++((u32 *) dst) = v;
				*++((u32 *) dst) = v;
				*++((u32 *) dst) = v;
				*++((u32 *) dst) = v;
				*++((u32 *) dst) = v;
			} while (--i);
		}
		
		i = (n & 31) >> 2;
		
		if (i) {
			do {
				*++((u32 *) dst) = v;
			} while (--i);
		}
		
		((u8 *) dst) = ((u8 *) (((u32 *) dst) + 1)) - 1;
		
		n &= 3;
	}
	
	if (n)
		do {
			*++((u8 *) dst) = v;
		} while (--n);
	
	return;
}

__declspec(section ".init") void* memcpy(void* dst, const void* src, size_t size){
    const u8* s;
    u8* d;

    if((u32)src >= (u32)dst){
        s = (const u8*)src -1;
        d = (u8*)dst -1;
        size++;
        while (--size !=0){
            *++d = *++s;
            } 
        }
        else{
            s = (const u8*)src + size;
            d = (u8*)dst + size;
            size++;
            while (--size != 0){
                *--d = *--s;
            }
        }
            return dst;
        }
