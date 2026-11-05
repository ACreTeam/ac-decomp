#include "types.h"
#include <dolphin/os.h>
#include <dolphin/types.h>
#include "JSystem/JUtility/JUTDbg.h"
#include "JSystem/JKernel/JKRAramPiece.h"
#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JKernel/JKRDecomp.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTException.h"

// yoinked from TP

JKRAMCommand* JKRAramPiece::prepareCommand(int direction, u32 src, u32 dst, u32 length,
                                           JKRAramBlock* block,
                                           JKRAMCommand::AsyncCallback callback) {
    JKRAMCommand* command = new (JKRHeap::getSystemHeap(), -4) JKRAMCommand();
    command->mTransferDirection = direction;
    command->mSrc = src;
    command->mDst = dst;
    command->mAramBlock = block;
    command->mDataLength = length;
    command->mCallback = callback;
    return command;
}

void JKRAramPiece::sendCommand(JKRAMCommand* command) {
    startDMA(command);
}

JSUList<JKRAMCommand> JKRAramPiece::sAramPieceCommandList;
OSMutex JKRAramPiece::mMutex;

JKRAMCommand* JKRAramPiece::orderAsync(int direction, u32 source, u32 destination, u32 length,
                                       JKRAramBlock* block, JKRAMCommand::AsyncCallback callback) {
    lock();
    if (((source & 0x1f) != 0) || ((destination & 0x1f) != 0)) {
        OSReport("direction = %x\n", direction);
        OSReport("source = %x\n", source);
        OSReport("destination = %x\n", destination);
        OSReport("length = %x\n", length);
#line 108
        JUT_PANIC("illegal address. abort.");
    }

    JKRAramCommand *message = new (JKRHeap::getSystemHeap(), -4) JKRAramCommand();
    JKRAMCommand* command =
        JKRAramPiece::prepareCommand(direction, source, destination, length, block, callback);
    message->setting(1, command);

    OSSendMessage(&JKRAram::sMessageQueue, message, OS_MESSAGE_BLOCK);
    if (command->mCallback != nullptr) {
        sAramPieceCommandList.append(&command->mPieceLink);
    }

    unlock();
    return command;
}

BOOL JKRAramPiece::sync(JKRAMCommand* command, int is_non_blocking) {
    OSMessage message;

    lock();
    if (is_non_blocking == 0) {
        OSReceiveMessage(&command->mMessageQueue, &message, OS_MESSAGE_BLOCK);
        sAramPieceCommandList.remove(&command->mPieceLink);
        unlock();
        return TRUE;
    }

    BOOL result = OSReceiveMessage(&command->mMessageQueue, &message, OS_MESSAGE_NOBLOCK);
    if (!result) {
        unlock();
        return FALSE;
    }

    sAramPieceCommandList.remove(&command->mPieceLink);
    unlock();
    return TRUE;
}

BOOL JKRAramPiece::orderSync(int direction, u32 source, u32 destination, u32 length,
                             JKRAramBlock* block) {
    lock();

    JKRAMCommand* command =
        JKRAramPiece::orderAsync(direction, source, destination, length, block, nullptr);
    BOOL result = JKRAramPiece::sync(command, 0);
    delete command;

    unlock();
    return result;
}

void JKRAramPiece::startDMA(JKRAMCommand* command) {
    if (command->mTransferDirection == 1) {
        DCInvalidateRange((void*)command->mDst, command->mDataLength);
    } else {
        DCStoreRange((void*)command->mSrc, command->mDataLength);
    }

    ARQPostRequest(&command->mRequest, 0, command->mTransferDirection, 0, command->mSrc,
                   command->mDst, command->mDataLength, JKRAramPiece::doneDMA);
}

void JKRAramPiece::doneDMA(u32 requestAddress) {
    JKRAMCommand* command = (JKRAMCommand*)requestAddress;

    if (command->mTransferDirection == 1) {
        DCInvalidateRange((void*)command->mDst, command->mDataLength);
    }

    if (command->_60 != 0)
    {
        if (command->_60 == 2)
        {
            JKRDecomp::sendCommand(command->mDecompCommand);
        }
        return;
    }

    if (command->mCallback) {
        (*command->mCallback)(requestAddress);
    }
    else if (command->_5C)
    {
        OSSendMessage(command->_5C, command, OS_MESSAGE_NOBLOCK);
    }
    else
    {
        OSSendMessage(&command->mMessageQueue, command, OS_MESSAGE_NOBLOCK);
    }
}

JKRAMCommand::JKRAMCommand() : mPieceLink(this), _30(this)
{
    OSInitMessageQueue(&mMessageQueue, &mMessage, 1);
    mCallback = nullptr;
    _5C = nullptr;
    _60 = 0;
    _8C = nullptr;
    _90 = nullptr;
    _94 = nullptr;
}

JKRAMCommand::~JKRAMCommand() {
    if (_8C)
        delete _8C;
    if (_90)
        delete _90;

    if (_94)
        JKRFree(_94);
}
