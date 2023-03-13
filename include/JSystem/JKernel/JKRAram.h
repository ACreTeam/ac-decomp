#ifndef JKRARAM_H
#define JKRARAM_H

#include "types.h"
#include "dolphin/ar.h"
#include "dolphin/os/OSMessage.h"
#include "JSystem/JKernel/JKRDisposer.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JKernel/JKRThread.h"
#include "JSystem/JSupport/JSUList.h"

#define ALIGN_PREV(u, align) (u & (~(align-1)))
#define ALIGN_NEXT(u, align) ((u + (align-1)) & (~(align-1)))

#define ARAM_GROUP_ID_ALL 0
#define ARAM_GROUP_ID_DEFAULT 0xFF

#define ARAM_MESGBUF_COUNT 4

#define ARAMPIECE_DONE_CALLBACK 0
#define ARAMPIECE_DONE_NONE 1
#define ARAMPIECE_DONE_DECOMPRESS 2

class JKRAramHeap;
class JKRDecompCommand;
class JKRAMCommand;

class JKRAramBlock {
  JKRAramBlock(u32 address, u32 size, u32 freeSize, u8 groupID, bool tempMemory);

  virtual ~JKRAramBlock();

  JKRAramBlock* allocHead(u32 size, u8 groupID, JKRAramHeap* heap);
  JKRAramBlock* allocTail(u32 size, u8 groupID, JKRAramHeap* heap);

  u32 getAddress() const { return this->mAddress; }
  u32 getSize() const { return this->mSize; }
  u32 getFreeSize() const { return this->mFreeSize; }
  bool isTempMemory() const { return this->mIsTempMemory; }
  void newGroupID(u8 groupID) { this->mGroupID = groupID; }

  JSULink<JKRAramBlock> mLink;
  u32 mAddress;
  u32 mSize;
  u32 mFreeSize;
  u8 mGroupID;
  bool mIsTempMemory;

  friend class JKRAramHeap;
};

class JKRAram : public JKRThread {
public:
  JKRAram(u32, u32, s32);

  virtual ~JKRAram();
  virtual void* run();

  static JKRAram* sAramObject;
  static const OSMessageQueue sMessageQueue;
  static JSUList<JKRAMCommand> sAramCommandList;
  static u32 sSZSBufferSize;
  static OSMessage sMessageBuffer[ARAM_MESGBUF_COUNT];

private:
  u32 mAudioMemoryPtr;
  u32 mAudioMemorySize;
  u32 mGraphMemoryPtr;
  u32 mGraphMemorySize;
  u32 mAramMemoryPtr;
  u32 mAramMemorySize;
  JKRAramHeap* mAramHeap;
  u32 mBlockLength;
  u8 _9C[4];
};

class JKRAramHeap : public JKRDisposer {
  enum EAllocMode {
    Head = 0,
    Tail = 1
  };

  JKRAramHeap(u32 baseAddress, u32 size);

  virtual ~JKRAramHeap();

  JKRAramBlock* alloc(u32 size, EAllocMode mode);
  void free(JKRAramBlock* block);
  JKRAramBlock* allocFromHead(u32 size);
  JKRAramBlock* allocFromTail(u32 size);
  u32 getFreeSize();
  u32 getTotalFreeSize();
  u32 getUsedSize(u8 groupID);
  void dump();

  u8 getCurrentGroupID() const { return this->mGroupID; }
  JKRHeap* getMgrHeap() const { return this->mHeap; }

  void lock() { OSLockMutex(&this->mMutex); }
  void unlock() { OSUnlockMutex(&this->mMutex); }

  static JSUList<JKRAramBlock> sAramList;

  OSMutex mMutex;
  JKRHeap* mHeap;
  u32 mHeadAddress;
  u32 mTailAddress;
  u32 mSize;
  u8 mGroupID;

  friend class JKRAramBlock;
};

class JKRAMCommand : public ARQRequest {
public:
  typedef void (*AMCommandCallback)(u32);

  JKRAMCommand();
  ~JKRAMCommand();

  JSULink<JKRAMCommand> mAramPieceCommandLink;
  JSULink<JKRAMCommand> mLink30;
  s32 mDirection;
  u32 mLength;
  u32 mSource;
  u32 mDestination;
  JKRAramBlock* mAramBlock;
  u8 _54[4];
  AMCommandCallback mCallback;
  OSMessageQueue* mCompletedMesgQueue;
  s32 mCallbackType;
  JKRDecompCommand* mDecompCommand;
  OSMessageQueue mMesgQueue;
  OSMessage mMesgBuffer[1];
  void* _8C;
  void* _90;
  void* _94;
};

class JKRAramCommand {
public:
  inline void setting(BOOL active, void* arg) {
    this->mActive = active;
    this->mArg = arg;
  }

  BOOL mActive;
  void* mArg;
};

class JKRAramPiece {
public:
  static JKRAMCommand* prepareCommand(int direction, u32 source, u32 destination, u32 length, JKRAramBlock* aramBlock, JKRAMCommand::AMCommandCallback callback);
  static void sendCommand(JKRAMCommand* cmd);
  static JKRAMCommand* orderAsync(int direction, u32 source, u32 destination, u32 length, JKRAramBlock* aramBlock, JKRAMCommand::AMCommandCallback callback);
  static bool sync(JKRAMCommand* cmd, BOOL noBlock);
  static bool orderSync(int direction, u32 source, u32 destination, u32 length, JKRAramBlock* aramBlock);
  static void startDMA(JKRAMCommand* cmd);
  static void doneDMA(u32 arg);

  static OSMutex mMutex;
  static JSUList<JKRAMCommand> sAramPieceCommandList;

private:
  static void lock() { OSLockMutex(&mMutex); }
  static void unlock() { OSUnlockMutex(&mMutex); }
};

inline bool JKRAramPcs(int direction, u32 source, u32 destination, u32 length, JKRAramBlock* block) {
  return JKRAramPiece::orderSync(direction, source, destination, length, block);
}

inline void JKRAramPcs_SendCommand(JKRAMCommand* cmd) {
  JKRAramPiece::sendCommand(cmd);
}

#endif