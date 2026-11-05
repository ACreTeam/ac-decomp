#ifndef _JSYSTEM_JSUINPUTSTREAM_H
#define _JSYSTEM_JSUINPUTSTREAM_H

#include <JSystem/JKernel/JKRFile.h>
#include "types.h"

// Named after standard C++ constants with the exact same meaning.
enum JSUStreamSeekFrom
{
    SEEK_SET = 0,
    SEEK_CUR,
    SEEK_END
};

class JSUIosBase
{
public:
    JSUIosBase()
        : mState(0)
    {
    }

    virtual ~JSUIosBase() {} //_08 (weak)
    enum EIoState
    {
        State_Bad,
        State_1,
        State_2
    };

    void setState(EIoState state)
    {
        mState |= state;
    }

    void clrState(EIoState state)
    {
        mState &= ~state;
    }

    bool isGood()
    {
        return mState != State_Bad;
    }

    // _00 VTBL
    u8 mState; // _04
};

class JSUInputStream : public JSUIosBase
{
public:
    JSUInputStream() {}

    virtual ~JSUInputStream();              // _08
    virtual int getAvailable() const = 0;   // _0C
    virtual s32 skip(long);                 // _10
    virtual int readData(void *, long) = 0; // _14

    s32 read(void *, long);
    char *read(char *);

    JSUInputStream &operator>>(char *pVal) {
        read(pVal);
        return *this;
    }

    JSUInputStream &operator>>(u8 &val) {
        read(&val, sizeof(u8));
        return *this;
    }

    JSUInputStream &operator>>(u16 &val) {
        read(&val, sizeof(u16));
        return *this;
    }

    /** @fabricated */
    template<typename T>
    T read(T *pType) {
        read(pType, sizeof(T));
        return *pType;
    }

    inline s32 read(bool &val) {
        return read(&val, (sizeof(val)));
    }

    inline s32 read(u8 &val) {
        return read(&val, (sizeof(val)));
    }

    inline s32 read(u16 &val) {
        return read(&val, (sizeof(val)));
    }

    inline s32 read(u32 &val) {
        return read(&val, (sizeof(val)));
    }

    /** @fabricated */
    inline bool readBool()
    {
        bool temp;
        read(&temp, 1);
        return temp;
    }

    inline u8 read8b()
    {
        u8 byte;
        read(&byte, 1);
        return byte;
    }

    inline u16 read16b()
    {
        u16 temp;
        read(&temp, 2);
        return temp;
    }

    inline u32 read32b()
    {
        u32 temp;
        read(&temp, 4);
        return temp;
    }

    inline u8 readU8()
    {
        u8 byte;
        read(&byte, 1);
        return byte;
    }

    inline s16 readS16()
    {
        s16 temp;
        read(&temp, 2);
        return temp;
    }

    /** @fabricated */
    inline f32 readS16ToFloat()
    {
        s16 temp;
        read(&temp, 2);
        return temp;
    }

    inline u16 readU16()
    {
        u16 temp;
        read(&temp, 2);
        return temp;
    }

    /** @fabricated */
    inline f32 readU16ToFloat()
    {
        u16 temp;
        read(&temp, 2);
        return temp;
    }

    inline u32 readU32()
    {
        u32 temp;
        read(&temp, 4);
        return temp;
    }

    
    inline s32 readS32()
    {
        s32 temp;
        read(&temp, 4);
        return temp;
    }

    // _00		= VTBL
    // _00-_08	= JSUIosBase
};

class JSURandomInputStream : public JSUInputStream
{
public:
    JSURandomInputStream() {}

    virtual ~JSURandomInputStream() {}                                       // _08 (weak)
    virtual int getAvailable() const { return getLength() - getPosition(); } // _0C (weak)
    virtual s32 skip(long);                                                  // _10
    virtual int readData(void *, long) = 0;                                  // _14
    virtual int getLength() const = 0;                                       // _18
    virtual int getPosition() const = 0;                                     // _1C
    virtual int seekPos(long, JSUStreamSeekFrom) = 0;                        // _20

    u32 align(s32);
    size_t peek(void *, long);
    void seek(long, JSUStreamSeekFrom);

    // _00		= VTBL
    // _00-_08	= JSUIosBase
};

class JSUMemoryInputStream : public JSURandomInputStream
{
public:
    JSUMemoryInputStream(const void *head, s32 len) {
        setBuffer(head,len);
    }

    virtual ~JSUMemoryInputStream() {}                    // _08 (weak)
    virtual int readData(void *, long);                   // _14
    virtual int getLength() const { return mLength; }     // _18 (weak)
    virtual int getPosition() const { return mPosition; } // _1C (weak)
    virtual int seekPos(long, JSUStreamSeekFrom);         // _20

    void setBuffer(const void *, long);

    // _00		= VTBL
    // _00-_08	= JSUIosBase
    const void *mObject; // _08
    long mLength;        // _0C
    int mPosition;       // _10
};

// Size: 0x10
class JSUFileInputStream : public JSURandomInputStream
{
public:
    JSUFileInputStream(JKRFile *);

    virtual int readData(void *, long);                                           // _14
    virtual int getLength() const { return ((JKRFile *)mObject)->getFileSize(); } // _18 (weak)
    virtual int getPosition() const { return mLength; }                           // _1C (weak)
    virtual int seekPos(long, JSUStreamSeekFrom);                                 // _20

    // _00		= VTBL
    // _00-_08	= JSUIosBase
    const void *mObject; // _08
    long mLength;        // _0C
};

/* Not much remains of this. */
class JSUOutputStream : public JSUIosBase
{
public:
    virtual ~JSUOutputStream(); // _08
    virtual long skip(long, s8); // _0C
    virtual long writeData(const void *, long) = 0; // _10

    int write(const void *, long);
    void write(const char *);

    // _00		= VTBL
    // _00-_08	= JSUIosBase
};

// The file-output half is stripped in Australia, but shares base-class RTTI.
class JSURandomOutputStream : public JSUOutputStream {
public:
    virtual ~JSURandomOutputStream() {}
    virtual long getLength() const = 0;
    virtual long getPosition() const = 0;
    virtual long seek(long, JSUStreamSeekFrom);
    virtual long getAvailable() const;
    virtual long seekPos(long, JSUStreamSeekFrom) = 0;
};

class JSUFileOutputStream : public JSURandomOutputStream {
public:
    JSUFileOutputStream(JKRFile* file);
    virtual long writeData(const void*, long);
    virtual long getLength() const { return ((JKRFile*)mObject)->getFileSize(); }
    virtual long getPosition() const { return mLength; }
    virtual long seekPos(long, JSUStreamSeekFrom);
    const void* mObject;
    long mLength;
};

// TODO: this.
struct JSUMemoryOutputStream;

#endif
