#ifndef JSURANDOMINPUTSTREAM_H
#define JSURANDOMINPUTSTREAM_H

#include "types.h"
#include "JSystem/JKernel/JKRFile.h"
#include "JSystem/JSupport/JSUInputStream.h"

#ifdef __cplusplus
class JSURandomInputStream : public JSUInputStream {
  public:
    virtual ~JSURandomInputStream() {
    }

    virtual int getAvailable() const {
        return this->getLength() - this->getPosition();
    }
    virtual int skip(s32 amount);
    virtual int readData(void* buf, s32 count) = 0;
    virtual int getLength() const = 0;
    virtual int getPosition() const = 0;
    virtual int seekPos(s32 offset, JSUStreamSeekFrom from) = 0;

    int align(s32 alignment);
    int peek(void* buf, s32 len);
    int seek(s32 offset, JSUStreamSeekFrom from);
};

class JSURandomOutputStream : public JSUOutputStream {
  public:
    virtual ~JSURandomOutputStream() {
    }

    virtual int getAvailable() const;
    virtual int skip(s32 amount);
    virtual int readData(void* buf, s32 count) = 0;
    virtual int getLength() const = 0;
    virtual int getPosition() const = 0;
    virtual int seekPos(s32 offset, JSUStreamSeekFrom from) = 0;

    int align(s32 alignment);
    int peek(void* buf, s32 len);
    int seek(s32 offset, JSUStreamSeekFrom from);
};

#endif

#endif
