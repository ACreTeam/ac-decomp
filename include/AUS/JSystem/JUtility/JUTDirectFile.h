#ifndef _JSYSTEM_JUT_JUTDIRECTFILE_H
#define _JSYSTEM_JUT_JUTDIRECTFILE_H

#include <dolphin/dvd.h>
#include "types.h"

#define JUTDF_BUFSIZE (0x800)

struct JUTDirectFile {
    JUTDirectFile();

    ~JUTDirectFile();

    bool fopen(const char*);
    void fclose();
    int fgets(void*, int);

    // unused/inlined
    int fetch32byte();
    void fread(void*, u32);
    void setPos(u32);
    void fgetc();

    u8 mBuffer[0x820];     // _000, 0x20 header, 0x800 sector
    u8* mSectorStart;      // _820, ptr to 0x800 buffer
    u32 mToRead;           // _824, length (max 32 bytes) to read
    u32 mLength;           // _828, length of file
    u32 mPos;              // _82C, position in file
    bool mIsOpen;          // _830, is file open
    DVDFileInfo mFileInfo; // _834
};

#endif
