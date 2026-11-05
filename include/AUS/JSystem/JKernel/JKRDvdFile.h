#ifndef _JSYSTEM_JKR_JKRDVDFILE_H
#define _JSYSTEM_JKR_JKRDVDFILE_H

#include <dolphin/os.h>
#include <dolphin/dvd.h>
#include <JSystem/JKernel/JKRFile.h>
#include <JSystem/JSupport/JSUStream.h>
#include "types.h"

class JKRAramBlock;

class JKRDvdFile;

// fabricated
struct JKRDvdFileInfo : public DVDFileInfo
{
    JKRDvdFile *mFile;
};

class JKRDvdFile : public JKRFile
{
public:
    JKRDvdFile();
    JKRDvdFile(s32);
    void initiate();
    OSMessage sync();

    // Inline/Unused
    void readDataAsync(void *, s32, s32);
    void writeDataAsync(void *, s32, s32);
    void check();
    void load(const char *, JKRHeap *);

    // Vtable layout
    virtual ~JKRDvdFile();                                           // 08
    virtual bool open(const char *fileName);                         // 0C
    virtual void close();                                            // 10
    virtual s32 readData(void *addr, s32 length, s32 offset);        // 14
    virtual s32 writeData(const void *addr, s32 length, s32 offset); // 18
    virtual s32 getFileSize() const { return mDvdFileInfo.length; }  // 1C
    virtual bool open(s32);                                          // 20

    // Inline getters/setters
    DVDFileInfo *getFileInfo() { return &mDvdFileInfo; }

    // Callback functions
    static void doneProcess(s32 msg, DVDFileInfo * fInfo);

    // global variables
    static JSUList<JKRDvdFile> sDvdList;

public:
    OSMutex mDvdMutex;                // 1C
    OSMutex mAramMutex;               // 34
    JKRAramBlock *mBlock;             // 4C
    OSThread *mCommandThread;         // 50, alternative name: mAramThread
    JSUFileInputStream *mFileStream;  // 54
    int _58;                          // 58
    JKRDvdFileInfo mDvdFileInfo;      // 5C
    OSMessageQueue mAramMessageQueue; // 9C
    OSMessage mAramMessage;           // BC
    OSMessageQueue mDvdMessageQueue;
    OSMessage mDvdMessage;

private:
    JSULink<JKRDvdFile> mLink; // E4
    OSThread *mThread;         // F4, alternative name: mDvdThread
};

#endif
