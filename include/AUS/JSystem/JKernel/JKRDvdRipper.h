#ifndef _JSYSTEM_JKR_JKRDVDRIPPER_H
#define _JSYSTEM_JKR_JKRDVDRIPPER_H

#include <dolphin/os.h>
#include <dolphin/dvd.h>
#include "JSystem/JKernel/JKRDvdFile.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JKernel/JKRCompression.h"
#include "types.h"

struct SYaz0Header
{
    u32 signature;
    u32 length;
};

class JKRDMCommand {
    JKRDMCommand();
    ~JKRDMCommand();
};

namespace JKRDvdRipper { // not sure if this is a class/struct or a namespace(if it is a class, it could be inherited from JKRRipper perhaps?)
    enum EAllocDirection {
        ALLOC_DIR_PAD,    // Unseen/unhandled so far
        ALLOC_DIR_TOP,    //!< [1] Negative alignment; allocate block from top of
                          //!< free block.
        ALLOC_DIR_BOTTOM, //!< [2] Positive alignment; allocate block from
                          //!< bottom of free block.
    };
    // could also be u8 * return, however most functions seem to use void *
    void *loadToMainRAM(const char *, u8 *, JKRExpandSwitch, u32, JKRHeap *, EAllocDirection, u32, int *, u32 *); 
    void *loadToMainRAM(s32, u8 *, JKRExpandSwitch, u32, JKRHeap *, EAllocDirection, u32, int *, u32 *);
    void *loadToMainRAM(JKRDvdFile *, u8 *, JKRExpandSwitch, u32, JKRHeap *, EAllocDirection, u32, int *, u32 *);
    // Inline/Unused
    void loadToMainRAMAsync(const char *, u8 *, JKRExpandSwitch, u32, JKRHeap *, u32 *);
    void loadToMainRAMAsync(s32, u8 *, JKRExpandSwitch, u32, JKRHeap *, u32 *);
    void loadToMainRAMAsync(JKRDvdFile *, u8 *, JKRExpandSwitch, u32, JKRHeap *, u32* );

    void sync(JKRDMCommand *, int);
    void syncAll(int);
    void countLeftSync();

    extern JSUList<JKRDMCommand> sDvdAsyncList;

    extern bool errorRetry; 
    extern int sSZSBufferSize; // 0x400
    // Weak
    inline int getSZSBufferSize() { return sSZSBufferSize; }    
    inline bool isErrorRetry() { return errorRetry; }
}

inline void *JKRDvdToMainRam(long entryNum, u8 *dst, JKRExpandSwitch expandSwitch, u32 fileSize, JKRHeap *heap, JKRDvdRipper::EAllocDirection allocDirection, u32 startOffset, int *pCompression, u32 *pSize)
{
    return JKRDvdRipper::loadToMainRAM(entryNum, dst, expandSwitch, fileSize, heap, allocDirection, startOffset, pCompression, pSize);
}

inline void *JKRDvdToMainRam(const char *path, u8 *dst, JKRExpandSwitch expandSwitch, u32 fileSize, JKRHeap *heap, JKRDvdRipper::EAllocDirection allocDirection, u32 startOffset, int *pCompression, u32 *pSize)
{
    return JKRDvdRipper::loadToMainRAM(path, dst, expandSwitch, fileSize, heap, allocDirection, startOffset, pCompression, pSize);
}

#endif
