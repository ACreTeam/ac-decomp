#include "libc64/qrand.h"

static u32 __qrand_idum = 1;
static u32 __qrand_itemp;

u32 qrand(void){
    __qrand_idum = __qrand_idum * 0x19660D + 0x3C6EF35F;
    return __qrand_idum;
}

void sqrand(u32 seed){
    __qrand_idum = seed;
}

float fqrand(void){
    __qrand_idum = __qrand_idum * 0x19660D + 0x3C6EF35F;
    __qrand_itemp = __qrand_idum >> 9 | 0x3F800000;
    __qrand_itemp = __qrand_itemp;
    return *(float*)&__qrand_itemp - 1.0f;
}

float fqrand2(void){
    __qrand_idum = __qrand_idum * 0x19660D + 0x3C6EF35F;
    __qrand_itemp = __qrand_idum >> 9 | 0x3F800000;
    return *(float*)&__qrand_itemp - 1.5f;
}