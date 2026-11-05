#ifndef _JSYSTEM_JKR_JKRFILE_H
#define _JSYSTEM_JKR_JKRFILE_H

#include <JSystem/JKernel/JKRDisposer.h>
#include "types.h"

class JKRFile : public JKRDisposer {
public:
    JKRFile() : JKRDisposer(), mFileOpen(false) {}
    virtual ~JKRFile() {}                                                // 8
    virtual bool open(const char *fileName) = 0;                         // C
    virtual void close() = 0;                                            // 10
    virtual s32 readData(void *addr, s32 length, s32 offset) = 0;        // 14
    virtual s32 writeData(const void *addr, s32 length, s32 offset) = 0; // 18
    virtual s32 getFileSize() const = 0;                                 // 1C

    void read(void *, s32, s32);

    bool isAvailable() const {
        return mFileOpen;
    }

protected:
    bool mFileOpen;
};
#endif