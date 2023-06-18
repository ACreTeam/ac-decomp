#ifndef TRK_H
#define TRK_H
#include "types.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum {
	TRKSuccess = 0,
	TRKError100 = 0x100,
	TRKError301 = 0x301,
	TRKError302 = 0x302,
	TRKError500 = 0x500
}TRKResult;

typedef struct TRKEvent{
	u8 mEventType;
	int mMax;
	int mBufferIndex;
}TRKEvent;

#ifdef __cplusplus
}
#endif
#endif
