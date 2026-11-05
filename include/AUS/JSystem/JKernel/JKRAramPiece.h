#include "types.h"
#ifndef JKRARAMPIECE_H
#define JKRARAMPIECE_H

#include "JSystem/JSupport/JSUList.h"
#include <dolphin/ar.h>
#include <dolphin/os.h>
#include <dolphin/types.h>

class JKRAramBlock;
class JKRDecompCommand;
class JKRAMCommand
{
public:
    typedef void (*AsyncCallback)(u32);

    JKRAMCommand();
    ~JKRAMCommand();

public:
    ARQRequest mRequest;              // _00
    JSULink<JKRAMCommand> mPieceLink; // _20
    JSULink<JKRAMCommand> _30;        // _30
    s32 mTransferDirection;           // _40
    u32 mDataLength;                  // _44
    u32 mSrc;                         // _48
    u32 mDst;                         // _4C
    JKRAramBlock *mAramBlock;         // _50
    u32 _54;                          // _54
    AsyncCallback mCallback;          // _58
    OSMessageQueue *_5C;              // _5C
    s32 _60;                          // _60
    JKRDecompCommand *mDecompCommand; // _64
    OSMessageQueue mMessageQueue;     // _68
    OSMessage mMessage;               // _88
    void *_8C;                        // _8C
    void *_90;                        // _90
    void *_94;                        // _94
};

struct JKRAramCommand
{
    void setting(int p1, void *p2)
    {
        _00 = p1;
        command = p2;
    }
    int _00;
    void *command;
};

class JKRAramPiece
{
public:
    static OSMutex mMutex;
    // TODO: fix type
    static JSUList<JKRAMCommand> sAramPieceCommandList;

public:
    static JKRAMCommand *prepareCommand(int, u32, u32, u32, JKRAramBlock *,
                                        JKRAMCommand::AsyncCallback);
    static void sendCommand(JKRAMCommand *);

    static JKRAMCommand *orderAsync(int, u32, u32, u32, JKRAramBlock *, JKRAMCommand::AsyncCallback);
    static BOOL sync(JKRAMCommand *, int);
    static BOOL orderSync(int, u32, u32, u32, JKRAramBlock *);
    static void startDMA(JKRAMCommand *);
    static void doneDMA(u32);

private:
    static void lock() { OSLockMutex(&mMutex); }
    static void unlock() { OSUnlockMutex(&mMutex); }
};

inline BOOL JKRAramPcs(int direction, u32 source, u32 destination, u32 length,
                       JKRAramBlock *block)
{
    return JKRAramPiece::orderSync(direction, source, destination, length, block);
}

#endif /* JKRARAMPIECE_H */
