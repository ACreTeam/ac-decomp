#ifndef TRK_CIRCLE_BUFFER_H
#define TRK_CIRCLE_BUFFER_H

#include "types.h"

typedef struct CircleBuffer {
	u8* mReadPtr;      // _00
	u8* mWritePtr;     // _04
	u8* mStartPtr;     // _08
	u32 mSize;         // _0C
	u32 mBytesToRead;  // _10
	u32 mBytesToWrite; // _14
	uint mSection;     // _18
	u32 _1C;           // _1C
} CircleBuffer;

u32 CBGetBytesAvailableForRead(CircleBuffer* cb);
u32 CBGetBytesAvailableForWrite(CircleBuffer* cb);
void CircleBufferInitialize(CircleBuffer* cb, u8* buf, u32 size);
void CircleBufferTerminate(CircleBuffer* cb);
int CircleBufferWriteBytes(CircleBuffer* cb, u8* buf, u32 size);
int CircleBufferReadBytes(CircleBuffer* cb, u8* buf, u32 size);

#endif
