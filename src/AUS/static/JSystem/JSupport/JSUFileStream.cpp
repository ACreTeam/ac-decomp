#include <JSystem/JKernel/JKRFile.h>
#include <JSystem/JSupport/JSUStream.h>
#include "types.h"

JSUFileInputStream::JSUFileInputStream(JKRFile* file)
{
	mObject = file;
	mLength = 0;
}

int JSUFileInputStream::readData(void* buffer, long byteCount)
{
	int readBytes = 0;
	if (((JKRFile*)mObject)->isAvailable()) {
		if ((u32)(mLength + byteCount) > ((JKRFile*)mObject)->getFileSize()) {
			byteCount = ((JKRFile*)mObject)->getFileSize() - mLength;
		}
		if (byteCount > 0) {
			readBytes = ((JKRFile*)mObject)->readData(buffer, byteCount, mLength);
			if (readBytes < 0) {
				return 0;
			} else {
				mLength += readBytes;
			}
		}
	}
	return readBytes;
}

int JSUFileInputStream::seekPos(long offset, JSUStreamSeekFrom mode)
{
	u32 originalLength = mLength;
	switch (mode) {
	case SEEK_SET:
		mLength = offset;
		break;
	case SEEK_END:
		mLength = ((JKRFile*)mObject)->getFileSize() - offset;
		break;
	case SEEK_CUR:
		mLength += offset;
		break;
	default:
		break;
	}
	if (0 > mLength) {
		mLength = 0;
	}
	if (mLength > ((JKRFile*)mObject)->getFileSize()) {
		mLength = ((JKRFile*)mObject)->getFileSize();
	}
	return mLength - originalLength;
}
// Stripped file-output implementation retained for the original RTTI emission order.
JSUFileOutputStream::JSUFileOutputStream(JKRFile* file) {
    mObject = file;
    mLength = 0;
}

long JSUFileOutputStream::writeData(const void* buffer, long byteCount) {
    long written = 0;
    if (((JKRFile*)mObject)->isAvailable() && byteCount > 0) {
        written = ((JKRFile*)mObject)->writeData(buffer, byteCount, mLength);
        if (written < 0) return 0;
        mLength += written;
    }
    return written;
}

long JSUFileOutputStream::seekPos(long offset, JSUStreamSeekFrom mode) {
    u32 originalLength = mLength;
    switch (mode) {
    case SEEK_SET: mLength = offset; break;
    case SEEK_END: mLength = ((JKRFile*)mObject)->getFileSize() - offset; break;
    case SEEK_CUR: mLength += offset; break;
    }
    if (mLength < 0) mLength = 0;
    if (mLength > ((JKRFile*)mObject)->getFileSize()) mLength = ((JKRFile*)mObject)->getFileSize();
    return mLength - originalLength;
}
