#ifndef JKRHEAP_H
#define JKRHEAP_H

#include <dolphin/os.h>
#include "JSystem/JKernel/JKRDisposer.h"

#include "types.h"

// TODO: Add JKRExpHeap and JKRAssertHeap to here?
typedef void JKRHeapErrorHandler(void *, u32, int);
class JKRHeap : public JKRDisposer
{
public:
    enum EAllocMode
    {
        HEAPALLOC_Unk1 = 1,
    };

    struct TState
    { // NB: this struct doesn't agree with TP's struct
        struct TLocation
        {
            TLocation() : _00(nullptr), _04(-1)
            {
            }

            char *_00; // _00
            int _04;   // _04
        };

        struct TArgument
        {
            TArgument(const JKRHeap *heap, u32 p2, bool p3)
                : mHeap((heap) ? heap : JKRHeap::sCurrentHeap), mId(p2), mIsCompareOnDestructed(p3)
            {
            }

            const JKRHeap *mHeap;        // _00
            u32 mId;                     // _04
            bool mIsCompareOnDestructed; // _08
        };

        TState(const JKRHeap *heap, u32 id, bool isCompareOnDestructed)
            : mUsedSize(0), mCheckCode(0), mArgument(heap, id, isCompareOnDestructed)
        {
            mArgument.mHeap->state_register(this, mArgument.mId);
        }

        TState(JKRHeap *heap)
            : mUsedSize(0), mCheckCode(0), mArgument(heap, 0xFFFFFFFF, true)
        {
        }

        ~TState();
        void dump() const { mArgument.mHeap->state_dump(*this); }
        static bool isVerbose() { return bVerbose_; };
        bool isCompareOnDestructed() const { return mArgument.mIsCompareOnDestructed; };
        u32 getUsedSize() const { return mUsedSize; }
        u32 getCheckCode() const { return mCheckCode; }
        const JKRHeap *getHeap() const { return mArgument.mHeap; }
        u32 getId() const { return mArgument.mId; }

        // unused/inlined:
        TState(const JKRHeap::TState::TArgument &arg, const JKRHeap::TState::TLocation &location);
        TState(const JKRHeap::TState &other, bool p2);
        TState(const JKRHeap::TState &other, const JKRHeap::TState::TLocation &location, bool p3);

        static bool bVerbose_;

        u32 mUsedSize;       // _00
        u32 mCheckCode;      // _04, plausibly TLocation when combined with _00
        u32 mBuf;            // _08
        u8 _0C[0x4];         // _0C
        TArgument mArgument; // _10
        TLocation mLocation; // _1C
    };

public:
    JKRHeap(void *, u32, JKRHeap *, bool);

    bool setErrorFlag(bool errorFlag);
    bool isSubHeap(JKRHeap *heap) const;

    /////////////// VTABLE
    virtual ~JKRHeap();                                               // _08
    virtual void callAllDisposer();                                   // _0C
    virtual u32 getHeapType() = 0;                                    // _10
    virtual bool check() = 0;                                         // _14
    virtual bool dump_sort() { return true; }                         // _18 (weak)
    virtual bool dump() = 0;                                          // _1C
    virtual void do_destroy() = 0;                                    // _20
    virtual void *do_alloc(u32, int) = 0;                             // _24
    virtual void do_free(void *) = 0;                                 // _28
    virtual void do_freeAll() = 0;                                    // _2C
    virtual void do_freeTail() = 0;                                   // _30
    virtual void do_fillFreeArea() = 0;                               // _34
    virtual int do_resize(void *, u32) = 0;                           // _38
    virtual int do_getSize(void *) = 0;                               // _3C
    virtual u32 do_getFreeSize() = 0;                                 // _40
    virtual void *do_getMaxFreeBlock() = 0;                           // _44
    virtual u32 do_getTotalFreeSize() = 0;                            // _48
    virtual s32 do_changeGroupID(u8);                     // _4C (weak)
    virtual u8 do_getCurrentGroupId();                   // _50 (weak)
    virtual void state_register(TState *, u32) const;                 // _54
    virtual bool state_compare(const TState &, const TState &) const; // _58
    virtual void state_dump(const TState &) const;                    // _5C

    JKRHeap *becomeSystemHeap();
    JKRHeap *becomeCurrentHeap();
    void destroy();
    void *alloc(u32, int);
    void free(void *);
    void freeAll();
    void freeTail();
    void fillFreeArea();
    int resize(void *memoryBlock, u32 newSize);

    // ... more functions

    s32 getSize(void *ptr);
    s32 getFreeSize();
    void *getMaxFreeBlock();
    u32 getTotalFreeSize();
    u8 getCurrentGroupId();
    s32 changeGroupID(u8 newGroupId);
    u32 getMaxAllocatableSize(int alignment);
    JKRHeap *find(void *memory) const;        // 0x80084640
    JKRHeap *findAllHeap(void *memory) const; // 0x8008492c
    bool dispose(void *memory, u32 size);     // 0x80084b9c
    void dispose(void *begin, void *end);     // 0x80084c2c
    void dispose();                           // 0x80084cb8
    void dispose_subroutine(u32 begin, u32 end);

    void appendDisposer(JKRDisposer *disposer)
    {
        mDisposerList.append(&disposer->mPointerLinks);
    }

    void removeDisposer(JKRDisposer *disposer)
    {
        mDisposerList.remove(&disposer->mPointerLinks);
    }

    void setDebugFill(bool debugFill) { mIsDebugFill = debugFill; }
    bool getDebugFill() const { return mIsDebugFill; }
    void *getStartAddr() { return (void *)mStartAddress; }
    void *getEndAddr() { return (void *)mEndAddress; }
    u32 getHeapSize() const { return mHeapSize; }
    bool getErrorFlag() const { return mErrorFlag; }
    void callErrorHandler(JKRHeap *heap, u32 size, int alignment)
    {
        if (mErrorHandler)
        {
            (*mErrorHandler)(heap, size, alignment);
        }
    }

    // TState related
    static u32 getState_buf_(TState *state) { return state->mBuf; } // might instead be a pointer to a next state?
    static void setState_u32ID_(TState *state, u32 id)
    {
        state->mArgument.mId = id;
    }
    static void setState_uUsedSize_(TState *state, u32 usedSize)
    {
        state->mUsedSize = usedSize;
    }
    static void setState_u32CheckCode_(TState *state, u32 checkCode) { state->mCheckCode = checkCode; }

    void lock() const { OSLockMutex(&mMutex); }
    void unlock() const { OSUnlockMutex(&mMutex); }

    JKRHeap *getParent()
    {
        return mHeapTree.getParent()->getObject();
    }

    const JSUTree<JKRHeap> &getHeapTree() { return mHeapTree; }

    // Unused
    void checkMemoryFilled(u8 *, u32 size, u8);

    static void destroy(JKRHeap *heap); // fabricated
    static bool initArena(char **outUserRamStart, u32 *outUserRamSize, int numHeaps);
    static void *alloc(u32 byteCount, int alignment, JKRHeap *heap);
    static void copyMemory(void *, void *, u32);
    static void free(void *memory, JKRHeap *heap);
    static void state_dumpDifference(const TState &r1, const TState &r2);
    static JKRHeap *findFromRoot(void *memory);
    static JKRHeapErrorHandler *setErrorHandler(JKRHeapErrorHandler *errorHandler);

    static void *getCodeStart() { return mCodeStart; }
    static void *getCodeEnd() { return mCodeEnd; }
    static void *getUserRamStart() { return mUserRamStart; }
    static void *getUserRamEnd() { return mUserRamEnd; }
    static u32 getMemorySize() { return mMemorySize; }
    static JKRHeap *getCurrentHeap() { return sCurrentHeap; }
    static JKRHeap *getRootHeap() { return sRootHeap; }
    static JKRHeap *getSystemHeap() { return sSystemHeap; }

    static void *mCodeStart;
    static void *mCodeEnd;
    static void *mUserRamStart;
    static void *mUserRamEnd;
    static u32 mMemorySize;

    static JKRHeap *sSystemHeap;
    static JKRHeap *sCurrentHeap;
    static JKRHeap *sRootHeap;

    static bool sDefaultFillFlag;
    static bool sDefaultFillCheckFlag;

    static JKRHeapErrorHandler *mErrorHandler;

protected:
    mutable OSMutex mMutex;             // _18
    void *mStartAddress;                // _30
    void *mEndAddress;                  // _34
    u32 mHeapSize;                      // _38
    bool mIsDebugFill;                  // _3C
    u8 mFillCheckFlag;                  // _3D
    u8 mAllocMode;                      // _3E, see EAllocMode enum
    u8 mGroupID;                        // _3F
    JSUTree<JKRHeap> mHeapTree;         // _40
    JSUList<JKRDisposer> mDisposerList; // _5C
    bool mErrorFlag;                    // _68
    bool mInitFlag;                     // _69
};

class JKRSolidHeap : public JKRHeap
{
public:
    struct State
    {
        State(State *other, u32 cnt)
        {
            mCnt = cnt;
            mSize = other->mSize;
            _08 = other->_08;
            _0C = other->_0C;
            mNext = other;
            other = this;
        }
        State(u32 cnt, u32 size, u8 *p3, u8 *p4, State *next)
        {
            mCnt = cnt;
            mSize = size;
            _08 = p3;
            _0C = p4;
            mNext = next;
        }
        u32 mCnt;
        u32 mSize;
        u8 *_08;
        void *_0C;
        State *mNext;
    };

    JKRSolidHeap(void *, u32, JKRHeap *, bool);

    virtual ~JKRSolidHeap();                                          // _08
    virtual u32 getHeapType() { return 'SLID'; }                      // _10 (weak)
    virtual bool check();                                             // _14
    virtual bool dump();                                              // _1C
    virtual void do_destroy();                                        // _20
    virtual void *do_alloc(u32, int);                                 // _24
    virtual void do_free(void *);                                     // _28
    virtual void do_freeAll();                                        // _2C
    virtual void do_freeTail();                                       // _30
    virtual void do_fillFreeArea();                                   // _34
    virtual int do_resize(void *, u32);                               // _38
    virtual int do_getSize(void *);                                   // _3C
    virtual u32 do_getFreeSize() { return mFreeSize; }                // _40 (weak)
    virtual void *do_getMaxFreeBlock() { return (void *)mSolidHead; } // _44 (weak)
    virtual u32 do_getTotalFreeSize() { return getFreeSize(); }       // _48 (weak)
    virtual void state_register(TState *, u32) const;                 // _54
    virtual bool state_compare(const TState &, const TState &) const; // _58

    s32 adjustSize();
    void recordState(u32);
    void restoreState(u32);
    void *allocFromHead(u32, int);
    void *allocFromTail(u32, int);

    static JKRSolidHeap *create(u32, JKRHeap *, bool);

    // TState stupidness
    static u32 getUsedSize(JKRSolidHeap *sldHeap)
    {
        u32 totalFreeSize = sldHeap->getTotalFreeSize();
        return sldHeap->mHeapSize - totalFreeSize;
    }
    static u32 getState_(TState *state) { return getState_buf_(state); } // might instead be a pointer to a next state?

    // _00     = VTBL
    // _00-_6C = JKRHeap
private:
    u32 mFreeSize;  // _6C
    u8 *mSolidHead; // _70
    u8 *mSolidTail; // _74
    State *_78;     // _78, seems to be some linked list struct in TP
};

inline JKRSolidHeap *JKRCreateSolidHeap(size_t size, JKRHeap *heap, bool p3) { return JKRSolidHeap::create(size, heap, p3); }
inline JKRHeap *JKRGetCurrentHeap() { return JKRHeap::getCurrentHeap(); }
inline JKRHeap *JKRSetCurrentHeap(JKRHeap *heap) { return heap->becomeCurrentHeap(); }
inline JKRHeap *JKRGetSystemHeap() { return JKRHeap::getSystemHeap(); }
inline JKRHeap *JKRGetRootHeap() { return JKRHeap::getRootHeap(); }
inline void *JKRAllocFromSysHeap(u32 size, int alignment) { return JKRHeap::getSystemHeap()->alloc(size, alignment); }
inline void *JKRAllocFromHeap(JKRHeap *heap, u32 size, int alignment) { return JKRHeap::alloc(size, alignment, heap); }
inline void JKRFree(void *pBuf) { JKRHeap::free(pBuf, nullptr); }
inline void JKRFreeToHeap(JKRHeap *heap, void *ptr) { JKRHeap::free(ptr, heap); }
inline void JKRFreeToSysHeap(void *buf) { JKRHeap::getSystemHeap()->free(buf); }

void JKRDefaultMemoryErrorRoutine(void *, u32, int);

void *operator new(size_t);
void *operator new(size_t, int);
void *operator new(size_t, JKRHeap *, int);
inline void *operator new(size_t, void *buf) { return buf; }

void *operator new[](size_t);
void *operator new[](size_t, int);
void *operator new[](size_t, JKRHeap *, int);

void operator delete(void *);
void operator delete[](void *);

#endif // !JKRHEAP_H
