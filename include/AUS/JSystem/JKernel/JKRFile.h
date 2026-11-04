#ifndef JKRFILE_H
#define JKRFILE_H

#include "types.h"
#include "dolphin/dvd.h"
#include "dolphin/os.h"
#include "JSystem/JSupport/JSUList.h"
#include "JSystem/JKernel/JKRDisposer.h"
#include "JSystem/JKernel/JKRMacro.h"

#ifdef __cplusplus
class JKRFile : public JKRDisposer {
  public:
    inline JKRFile() : JKRDisposer(), mFileOpen(false) {
    }

    virtual ~JKRFile() {
    }
    virtual bool open(const char* path) = 0;
    virtual bool close() = 0;
    virtual int readData(void* data, s32 length, s32 ofs) = 0;
    virtual int writeData(const void* data, s32 length, s32 ofs) = 0;
    virtual u32 getFileSize() const = 0;

    void read(void* data, s32 length, s32 ofs);
    bool isAvailable() {
        return this->mFileOpen;
    }

  protected:
    bool mFileOpen;
};
#endif

#endif
