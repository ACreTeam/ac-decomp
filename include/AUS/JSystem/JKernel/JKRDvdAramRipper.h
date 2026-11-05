#ifndef JKRDVDARAMRIPPER_H
#define JKRDVDARAMRIPPER_H

#include <JSystem/JKernel/JKRAram.h>
#include <JSystem/JSupport/JSUList.h>
#include "types.h"

class JKRADCommand
{
public:
    typedef void (*LoadCallback)(u32);
    JKRADCommand();
    ~JKRADCommand();

    JSULink<JKRADCommand> mLink;
    u8 _10[0x18];                         // _10 - unknown/padding
    JKRDvdFile *mDvdFile;                 // _28
    u32 _2C;                              // _2C
    JKRAramBlock *mBlock;                 // _30
    JKRExpandSwitch mExpandSwitch;        // _34
    LoadCallback mCallBack;               // _38
    u32 _3C;                              // _3C
    u32 _40;                              // _40, probably size
    u32 *_44;                             // _44
    s32 _48;                              // _48
    u8 _4C;                               // _4C
    JKRAramStreamCommand *mStreamCommand; // _50
};

class JKRDvdAramRipper
{
public:
    static JKRAramBlock *loadToAram(char const *, u32, JKRExpandSwitch, u32, u32, u32 *);
    static JKRAramBlock *loadToAram(s32, u32, JKRExpandSwitch, u32, u32, u32 *);
    static JKRAramBlock *loadToAram(JKRDvdFile *, u32, JKRExpandSwitch, u32, u32, u32 *);
    static JKRADCommand *loadToAram_Async(JKRDvdFile *, u32, JKRExpandSwitch, JKRADCommand::LoadCallback, u32, u32, u32 *);
    static JKRADCommand *callCommand_Async(JKRADCommand *);
    static bool syncAram(JKRADCommand *, int);

    // unused/inlined:
    static JKRADCommand *loadToAram_Async(const char *, u32, JKRExpandSwitch, JKRADCommand::LoadCallback, u32, u32, u32 *);
    static JKRADCommand *loadToAram_Async(s32, u32, JKRExpandSwitch, JKRADCommand::LoadCallback, u32, u32, u32 *);
    static void syncAramAll(int);
    static void countLeftSync();
    static void afterAramAsync(JKRADCommand *);

    static int getSZSBufferSize() { return sSZSBufferSize; }
    static bool isErrorRetry() { return errorRetry; }

    static bool errorRetry;
    static int sSZSBufferSize;
    static JSUList<JKRADCommand> sDvdAramAsyncList;    
};

inline JKRAramBlock *JKRDvdToAram(s32 entrynum, u32 p2, JKRExpandSwitch expSwitch, u32 p4, u32 p5, u32 *p6) {
    return JKRDvdAramRipper::loadToAram(entrynum, p2, expSwitch, p4, p5, p6);
}

#endif