#ifndef JKRDVDRIPPER_H
#define JKRDVDRIPPER_H

#include "types.h"
#include "JSystem/JKernel/JKREnum.h"
#include "JSystem/JKernel/JKRDvdFile.h"

#define SZP_BUFFERSIZE 1024
#define REF_BUFFERSIZE 0x1120

struct SZPHeader {
  u32 magic;
  u32 decompSize;
};

class JKRDMCommand {
  JKRDMCommand();
  ~JKRDMCommand();
};

class JKRDvdRipper {
public:
  enum EAllocDirection {
    ALLOC_DIR_DEFAULT = 0,
    ALLOC_DIR_TOP = 1,
    ALLOC_DIR_BOTTOM = 2
  };

  static void* loadToMainRAM(const char* file, u8* buf, JKRExpandSwitch expandSwitch, u32 maxDest, JKRHeap* heap, EAllocDirection allocDir, u32 offset, int* compressMode);
  static void* loadToMainRAM(s32 entrynum, u8* buf, JKRExpandSwitch expandSwitch, u32 maxDest, JKRHeap* heap, EAllocDirection allocDir, u32 offset, int* compressMode);
  static void* loadToMainRAM(JKRDvdFile* file, u8* buf, JKRExpandSwitch expandSwitch, u32 maxDest, JKRHeap* heap, EAllocDirection allocDir, u32 offset, int* compressMode);

  static inline bool isErrorRetry() { return JKRDvdRipper::errorRetry; }

  static JSUList<JKRDMCommand> sDvdAsyncList;

  static bool errorRetry;
};

static int JKRDecompressFromDVD(JKRDvdFile* srcFile, void* buf, u32 size, u32 maxDest, u32 fileOffset, u32 srcOffset);

#endif
