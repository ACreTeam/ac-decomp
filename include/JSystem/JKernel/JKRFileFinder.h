#ifndef _JKRFILEFINDER_H
#define _JKRFILEFINDER_H

#include <dolphin/dvd.h>
#include <dolphin/os.h>
#include "types.h"

#ifdef __cplusplus
class JKRArchive;

struct JKRFileFinderBase {
    char* mFileName;    // _00
    int mFileIndex;     // _04
    u16 mFileID;        // _08
    u16 mFileTypeFlags; // _0A
};

class JKRFileFinder {
  public:
    JKRFileFinder() : mIsAvailable(false), mIsDir(false) {
    }

    JKRFileFinderBase mBase;

    virtual ~JKRFileFinder() {
    }                                // _08 (weak)
    virtual bool findNextFile() = 0; // _0C

    bool isAvailable() const {
        return mIsAvailable;
    }

    // _00     = VTBL

    bool mIsAvailable; // _10
    bool mIsDir;       // _11
};

class JKRArcFinder : public JKRFileFinder {
  public:
    JKRArcFinder(JKRArchive*, long, long);

    virtual ~JKRArcFinder() {
    }                            // _08 (weak)
    virtual bool findNextFile(); // _0C

    // _00     = VTBL
    // _00-_14 = JKRFileFinder
    JKRArchive* mArchive; // _14
    long mStartIndex;     // _18
    long mEndIndex;       // _1C
    long mNextIndex;      // _20
};

class JKRDvdFinder : public JKRFileFinder {
  public:
    JKRDvdFinder(const char*);

    virtual ~JKRDvdFinder() // _08 (weak)
    {
        if (mIsDvdOpen) {
            DVDCloseDir(&mDir);
        }
    }
    virtual bool findNextFile(); // _0C

    // _00     = VTBL
    // _00-_14 = JKRFileFinder
    DVDDir mDir;     // _14
    bool mIsDvdOpen; // _20
};

#endif
#endif
