#ifndef JSUFILEINPUTSTREAM_H
#define JSUFILEINPUTSTREAM_H

#include "types.h"
#include "JSystem/JKernel/JKRFile.h"
#include "JSystem/JSupport/JSURandomInputStream.h"

#ifdef __cplusplus
class JSUFileInputStream : public JSURandomInputStream {
  public:
    JSUFileInputStream(JKRFile* file);

    virtual int readData(void* buf, s32 len);
    virtual int getLength() const {
        return ((JKRFile*)this->mObject)->getFileSize();
    }
    virtual int getPosition() const {
        return this->mPosition;
    }
    virtual int seekPos(s32 offset, JSUStreamSeekFrom from);

    /* These two functions are shown in the symbol map, but are unused. */
    // bool open(const char* path);
    // bool close();

  protected:
    const void* mObject;
    s32 mPosition;
};

class JSUFileOutputStream : public JSURandomOutputStream {
  public:
    JSUFileOutputStream(JKRFile*);
};

#endif

#endif
