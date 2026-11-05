#include "JSystem/JUtility/JUTDbg.h"
#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JKernel/JKRAramPiece.h"
#include "JSystem/JSupport/JSUStream.h"
#include <dolphin/os.h>
#include "types.h"

// From Pikmin Repo

OSMessage JKRAramStream::sMessageBuffer[4] = {0};
OSMessageQueue JKRAramStream::sMessageQueue = {0};

JKRAramStream *JKRAramStream::sAramStreamObject = nullptr;
u8 *JKRAramStream::transBuffer = nullptr;
u32 JKRAramStream::transSize = nullptr;
JKRHeap *JKRAramStream::transHeap = nullptr;


JKRAramStream *JKRAramStream::create(s32 param)
{
    if (JKRAramStream::sAramStreamObject == nullptr)
    {
        JKRAramStream::sAramStreamObject = new (JKRGetSystemHeap(), 0) JKRAramStream(param);
        setTransBuffer(nullptr, 0, nullptr);
    }
    return JKRAramStream::sAramStreamObject;
}

JKRAramStream::JKRAramStream(s32 priority)
    : JKRThread(0x4000, 0x10, priority)
{
    OSResumeThread(mThreadRecord);
}

JKRAramStream::~JKRAramStream(){};

void *JKRAramStream::run()
{
    OSMessage result;
    OSInitMessageQueue(&JKRAramStream::sMessageQueue, JKRAramStream::sMessageBuffer,
                       ARRAY_COUNT(sMessageBuffer)); // jank cast to void** to satisfy prototype
    while (true)
    {
        OSReceiveMessage(&JKRAramStream::sMessageQueue, &result, OS_MESSAGE_BLOCK);
        JKRAramStreamCommand *command = static_cast<JKRAramStreamCommand *>(result);
        switch (command->type)
        {
        case JKRAramStreamCommand::ECT_READ:
            readFromAram();
            break;
        case JKRAramStreamCommand::ECT_WRITE:
            writeToAram(command);
            break;
        }
    }
}

u32 JKRAramStream::readFromAram() { return 1; } // probably a define evaluating to 1

s32 JKRAramStream::writeToAram(JKRAramStreamCommand *command)
{
    u32 dstSize = command->mSize;
    u32 offset = command->mOffset;
    u32 writtenLength = 0;
    u32 destination = command->mAddress;
    u8 *buffer = command->mTransferBuffer;
    u32 bufferSize = command->mTransferBufferSize;
    JKRHeap *heap = command->mHeap;
    if (buffer)
    {
        bufferSize = (bufferSize == nullptr) ? 0x8000 : bufferSize;

        command->mTransferBufferSize = bufferSize;
        command->mAllocatedTransferBuffer = false;
    }
    else
    {
        bufferSize = (bufferSize == nullptr) ? 0x8000 : bufferSize;

        if (heap)
        {
            buffer = (u8 *)JKRAllocFromHeap(heap, bufferSize, -0x20);
            command->mTransferBuffer = buffer;
        }
        else
        {
            buffer = (u8 *)JKRAllocFromSysHeap(bufferSize, -0x20);
            command->mTransferBuffer = buffer;
        }

        command->mTransferBufferSize = bufferSize;
        command->mAllocatedTransferBuffer = true;
    }

    if (!buffer)
    {
        if (!heap)
        {
            JKRGetCurrentHeap()->dump();
        }
        else
        {
            heap->dump();
        }
#line 172
        JUT_PANIC(":::Cannot alloc memory\n");
    }

    if (buffer)
    {
        command->mStream->seek(offset, SEEK_SET);
        while (dstSize != 0)
        {
            u32 length = (dstSize > bufferSize) ? bufferSize : dstSize;

            s32 readLength = command->mStream->read(buffer, length);
            if (readLength == 0)
            {
                writtenLength = 0;
                break;
            }

            JKRAramPcs(0, (u32)buffer, destination, length, nullptr);
            dstSize -= length;
            writtenLength += length;
            destination += length;

            if (command->mReturnSize)
            {
                *command->mReturnSize += length;
            }
        }

        if (command->mAllocatedTransferBuffer)
        {
            JKRFree(buffer);
            command->mAllocatedTransferBuffer = false;
        }
    }

    OSSendMessage(&command->mMessageQueue, (OSMessage)writtenLength, OS_MESSAGE_NOBLOCK);
    return writtenLength;
};

/*
 * Unused function, made-up contents. Do not take this seriously!
 * While the function exists in the map, this is almost certainly incorrect.
 * Should exist to generate JSURandomInputStream::getAvailable() const afterwards.
 */
JKRAramStreamCommand *JKRAramStream::write_StreamToAram_Async(JSUFileInputStream *stream, JKRAramBlock *addr, u32 size, u32 offset,
                                                              u32 *returnSize)
{
    JKRAramStreamCommand *command = new (JKRGetSystemHeap(), -4) JKRAramStreamCommand();
    command->type = JKRAramStreamCommand::ECT_WRITE;
    command->mAddress = (u32)addr;
    command->mSize = size;
    command->mStream = stream;
    command->_2C = stream->getAvailable();
    command->mOffset = offset;
    command->mTransferBuffer = transBuffer;
    command->mHeap = transHeap;
    command->mTransferBufferSize = transSize;
    command->mReturnSize = returnSize;
    if (returnSize)
    {
        *returnSize = 0;
    }

    OSInitMessageQueue(&command->mMessageQueue, &command->mMessage, 1);
    OSSendMessage(&sMessageQueue, command, OS_MESSAGE_BLOCK);
    return command;
}

JKRAramStreamCommand *JKRAramStream::write_StreamToAram_Async(JSUFileInputStream *stream, u32 addr, u32 size, u32 offset, u32 *returnSize)
{
    JKRAramStreamCommand *command = new (JKRGetSystemHeap(), -4) JKRAramStreamCommand();
    command->type = JKRAramStreamCommand::ECT_WRITE;
    command->mAddress = addr;
    command->mSize = size;
    command->mStream = stream;
    command->_2C = 0;
    command->mOffset = offset;
    command->mTransferBuffer = transBuffer;
    command->mHeap = transHeap;
    command->mTransferBufferSize = transSize;
    command->mReturnSize = returnSize;
    if (returnSize)
    {
        *returnSize = 0;
    }

    OSInitMessageQueue(&command->mMessageQueue, &command->mMessage, 1);
    OSSendMessage(&sMessageQueue, command, OS_MESSAGE_BLOCK);
    return command;
}

JKRAramStreamCommand *JKRAramStream::sync(JKRAramStreamCommand *command, BOOL isNonBlocking)
{
    OSMessage msg;
    if (isNonBlocking == FALSE)
    {
        OSReceiveMessage(&command->mMessageQueue, &msg, OS_MESSAGE_BLOCK);
        if (msg == nullptr)
        {
            command = nullptr;
            return command;
        }
        else
        {
            return command;
        }
    }
    else
    {
        BOOL receiveResult = OSReceiveMessage(&command->mMessageQueue, &msg, OS_MESSAGE_NOBLOCK);
        if (receiveResult == FALSE)
        {
            command = nullptr;
            return command;
        }
        else if (msg == nullptr)
        {
            command = nullptr;
            return command;
        }
        else
        {
            return command;
        }
    }
}

void JKRAramStream::setTransBuffer(u8 *buffer, u32 bufferSize, JKRHeap *heap)
{
    transBuffer = nullptr;
    transSize = 0x8000;
    transHeap = nullptr;

    if (buffer)
    {
        transBuffer = (u8 *)ALIGN_NEXT((u32)buffer, 0x20);
    }

    if (bufferSize)
    {
        transSize = ALIGN_PREV(bufferSize, 0x20);
    }

    if (heap && !buffer)
    {
        transHeap = heap;
    }
}

JKRAramStreamCommand::JKRAramStreamCommand()
{
    mAllocatedTransferBuffer = false;
}
