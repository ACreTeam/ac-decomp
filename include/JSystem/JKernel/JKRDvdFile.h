#ifndef JKRDVDFILE_H
#define JKRDVDFILE_H

#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JKernel/JKRFile.h"
#include "JSystem/JSupport/JSUStream.h"

#ifdef __cplusplus
class JKRDvdFile;

struct JKRDvdFileInfo : public DVDFileInfo {
    JKRDvdFile* mFile;
};

class JKRDvdFile : public JKRFile {
  public:
    JKRDvdFile();
    JKRDvdFile(const char* filename);
    JKRDvdFile(s32 entrynum);

    virtual ~JKRDvdFile();

    virtual bool open(const char* filename);
    virtual bool close();
    virtual int readData(void* data, s32 length, s32 ofs);
    virtual int writeData(const void* data, s32 length, s32 ofs);
    virtual u32 getFileSize() const {
        return this->mDvdFileInfo.length;
    }
    virtual bool open(s32 entrynum);

    inline DVDFileInfo* getFileInfo() {
        return &this->mDvdFileInfo;
    }

    inline int readDataAsync(void* addr, s32 length, s32 offset) {
        OSLockMutex(&this->mDvdMutex);
        s32 retAddr;

        if (this->mDvdThread != nullptr) {
            OSUnlockMutex(&this->mDvdMutex);
            retAddr = -1;
        } else {
            this->mDvdThread = OSGetCurrentThread();
            retAddr = -1;
            if (DVDReadAsync(&this->mDvdFileInfo, addr, length, offset, JKRDvdFile::doneProcess)) {
                retAddr = this->sync();
            }

            this->mDvdThread = nullptr;
            OSUnlockMutex(&this->mDvdMutex);
        }

        return retAddr;
    }

    inline int writeDataAsync(const void* data, s32 length, s32 offset) {
        return -1;
    }

    void initiate();
    s32 sync();

    static void doneProcess(s32 result, DVDFileInfo* info);

    static JSUList<JKRDvdFile> sDvdList;

  public:
    OSMutex mDvdMutex;
    OSMutex mAramMutex;
    JKRAramBlock* mAramBlock;
    OSThread* mAramThread;
    JSUFileInputStream* mInputStream;
    u32 _58;
    JKRDvdFileInfo mDvdFileInfo;
    OSMessageQueue mAramMessageQueue;
    OSMessage mAramMessage;
    OSMessageQueue mDvdMessageQueue;
    OSMessage mDvdMessage;
    JSULink<JKRDvdFile> mLink;
    OSThread* mDvdThread;
};
#endif

#endif
