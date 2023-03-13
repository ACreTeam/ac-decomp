#ifndef JKRDVDFILE_H
#define JKRDVDFILE_H

#include "JSystem/JKernel/JKRFile.h"
#include "JSystem/JSupport/JSUStream.h"

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
  virtual u32 getFileSize() const { return this->mDvdFileInfo.length; }
  virtual bool open(s32 entrynum);

  inline DVDFileInfo* getFileInfo() {
    return &this->mDvdFileInfo;
  }

  inline int readDataAsync(void* addr, s32 length, s32 offset) {
    OSLockMutex(&this->mMutex1);
    s32 retAddr;

    if (this->mThread2 != nullptr) {
      OSUnlockMutex(&this->mMutex1);
      retAddr = -1;
    }
    else {
      this->mThread2 = OSGetCurrentThread();
      retAddr = -1;
      if (DVDReadAsync(&this->mDvdFileInfo, addr, length, offset, JKRDvdFile::doneProcess)) {
        retAddr = this->sync();
      }

      this->mThread2 = nullptr;
      OSUnlockMutex(&this->mMutex1);
    }

    return retAddr;
  }

  inline int writeDataAsync(const void* data, s32 length, s32 offset) { return -1; }

  void initiate();
  s32 sync();

  static void doneProcess(s32 result, DVDFileInfo* info);

  static JSUList<JKRDvdFile> sDvdList;

protected:
  OSMutex mMutex1;
  OSMutex mMutex2;
  JKRAramBlock* mAramBlock;
  OSThread* mThread1;
  JSUFileInputStream* mInputStream;
  u32 _58;
  JKRDvdFileInfo mDvdFileInfo;
  OSMessageQueue mMessageQueue1;
  OSMessage mMsg1;
  OSMessageQueue mMessageQueue2;
  OSMessage mMsg2;
  JSULink<JKRDvdFile> mLink;
  OSThread* mThread2;
};

#endif
