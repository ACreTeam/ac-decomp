#include <dolphin/os.h>
#include <JSystem/JSupport/JSUStream.h>
#include "types.h"

JSUInputStream::~JSUInputStream() { 
#if DEBUG // TODO: OS Assert/Panic?
    if(isGood())
    	OSReport("JSUInputStream: occur error.\n");
#endif
}

s32 JSUInputStream::read(void* data, s32 length)
{
	s32 len = readData(data, length);
	if (len != length) {
		setState(State_1);
	}
	return len;
}

char* JSUInputStream::read(char* str)
{
	u16 val;
	if (readData(&val, sizeof(val)) != sizeof(val)) {
		str[0] = '\0';
		setState(State_1);
		return nullptr;
	}

	int len  = readData(str, val);
	str[len] = '\0';
	if (len != val) {
		setState(State_1);
	}

	return str;
}

s32 JSUInputStream::skip(s32 val)
{
	char unk;
	int i;
	for (i = 0; val > i; i++) {
		if (readData(&unk, sizeof(unk)) != sizeof(unk)) {
			setState(State_1);
			break;
		}
	}
	return i;
}

u32 JSURandomInputStream::align(s32 arg0)
{
	int th_var;
	s32 one_var;
	s32 newtemp;
	s32 seekPosTmp;

	one_var = getPosition();
	th_var  = (arg0 - 1 + one_var) & ~(arg0 - 1) /*- one_var*/;
	newtemp = th_var - one_var;
	if (newtemp != 0) {
		seekPosTmp = seekPos(th_var, SEEK_SET);
		if (seekPosTmp != newtemp) {
			setState(State_1);
		}
	}
	return newtemp;
}

s32 JSURandomInputStream::skip(s32 offset)
{
	s32 tmp = seekPos(offset, SEEK_CUR);
	if (tmp != offset) {
		setState(State_1);
	}
	return tmp;
}

size_t JSURandomInputStream::peek(void* buffer, s32 byteCount)
{
	s32 position   = getPosition();
	s32 dataLength = read(buffer, byteCount);
	if (dataLength != 0) {
		seekPos(position, SEEK_SET);
	}
	return dataLength;
}

void JSURandomInputStream::seek(s32 offset, JSUStreamSeekFrom mode)
{
	seekPos(offset, mode);
	clrState(State_1);
}
