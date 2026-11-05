extern "C" int abs(int);
#include "_mem.h"
#include "types.h"
#include <string.h>

#include "MSL_C/w_math.h"
#include "MSL_C/math.h"
#include <JSystem/JKernel/JKRArchive.h>
#include <JSystem/JKernel/JKRDvdAramRipper.h>
#include <JSystem/JKernel/JKRDvdRipper.h>
#include <JSystem/JUtility/JUTDbg.h>

JKRDvdArchive::JKRDvdArchive() : JKRArchive() {}

JKRDvdArchive::JKRDvdArchive(s32 entryNum, EMountDirection mountDirection) : JKRArchive(entryNum, MOUNT_DVD)
{
    mMountDirection = mountDirection;
    if (!open(entryNum))
    {
        return;
    }
    else
    {
        mVolumeType = 'RARC';
        mVolumeName = &mStrTable[mDirectories->mOffset];
        sVolumeList.prepend(&mFileLoaderLink);
        mIsMounted = true;
    }
}

JKRDvdArchive::~JKRDvdArchive() {
    if(mIsMounted == true) {
        if (mArcInfoBlock)
        {
            SDIFileEntry *fileEntries = mFileEntries;
            for (int i = 0; i < mArcInfoBlock->num_file_entries; i++)
            {
                if (fileEntries->mData != nullptr)
                {
                    JKRFreeToHeap(mHeap, fileEntries->mData);
                }
                fileEntries++;
            }
            JKRFreeToHeap(mHeap, mArcInfoBlock);
            mArcInfoBlock = nullptr;
        }

        if (mExpandSizes)
        {
            JKRFree(mExpandSizes);
            mExpandSizes = nullptr;
        }
        if (mDvdFile)
        {
            delete mDvdFile;
        }

        sVolumeList.remove(&mFileLoaderLink);
        mIsMounted = false;
    }
}

#if DEBUG
CW_FORCE_STRINGS(JKRDvdArchive_cpp, __FILE__, "isMounted()", "mMountCount == 1")
#endif

bool JKRDvdArchive::open(long entryNum)
{
    mArcInfoBlock = nullptr;
    _64 = 0;
    mDirectories = nullptr;
    mFileEntries = nullptr;
    mStrTable = nullptr;

    mDvdFile = new (JKRGetSystemHeap(), 0) JKRDvdFile(entryNum);
    if (mDvdFile == nullptr)
    {
        mMountMode = 0;
        return 0;
    }
    SDIFileEntry *mem = (SDIFileEntry *)JKRAllocFromSysHeap(32, 32); // NOTE: unconfirmed if this struct was used here
    if (mem == nullptr)
    {
        mMountMode = 0;
    }
    else
    {
        JKRDvdToMainRam(entryNum, (u8 *)mem, EXPAND_SWITCH_DECOMPRESS, 32, nullptr, JKRDvdRipper::ALLOC_DIR_TOP, 0, &mCompression, nullptr);
        DCInvalidateRange(mem, 32);
        int alignment = mMountDirection == MOUNT_DIRECTION_HEAD ? 32 : -32;

        mArcInfoBlock = (SArcDataInfo *)JKRAllocFromHeap(mHeap, mem->mSize, alignment);
        if (mArcInfoBlock == nullptr) {
            mMountMode = 0;
        }
        else {
            JKRDvdToMainRam(entryNum, (u8 *)mArcInfoBlock, EXPAND_SWITCH_DECOMPRESS, mem->mSize, nullptr, JKRDvdRipper::ALLOC_DIR_TOP, 32, nullptr, nullptr);
            DCInvalidateRange(mArcInfoBlock, mem->mSize);

            mDirectories = (SDIDirEntry *)((u8 *)mArcInfoBlock + mArcInfoBlock->node_offset);
            mFileEntries = (SDIFileEntry *)((u8 *)mArcInfoBlock + mArcInfoBlock->file_entry_offset);
            mStrTable = (const char *)((u8 *)mArcInfoBlock + mArcInfoBlock->string_table_offset);
            mExpandSizes = nullptr;

            u8 compressedFiles = 0; // maybe a check for if the last file is compressed?

            SDIFileEntry *fileEntry = mFileEntries;
            for (int i = 0; i < mArcInfoBlock->num_file_entries; i++)
            {
                u8 flag = fileEntry->mFlag >> 24;
                if ((flag & 1)) {
                    compressedFiles |= (flag & JKRARCHIVE_ATTR_COMPRESSION);
                }
                fileEntry++;
            }

            if(compressedFiles != 0) {
                mExpandSizes = (u32 *)JKRAllocFromHeap(mHeap, mArcInfoBlock->num_file_entries << 2, abs(alignment));
                if (mExpandSizes == nullptr)
                {
                    JKRFreeToSysHeap(mArcInfoBlock);
                    mMountMode = 0;
                    goto cleanup;
                }
                memset(mExpandSizes, 0, mArcInfoBlock->num_file_entries << 2);
            }
            _64 = mem->mDataOffset + mem->mSize; // End of data offset?
        }
    }
    cleanup:
    if (mem != nullptr)
    {
        JKRFreeToSysHeap(mem);
    }
    if (mMountMode == 0)
    {
#line 397
        JUT_REPORT_MSG(":::Cannot alloc memory [%s][%d]\n", __FILE__, __LINE__); // TODO: macro
        if (mDvdFile != nullptr)
        {
            delete mDvdFile;
        }
        return false;
    }
    return true;
}

void *JKRDvdArchive::fetchResource(SDIFileEntry *fileEntry, u32 *pSize) {
#line 428
    JUT_ASSERT(isMounted());
    u32 sizeptr;
    u32 size;
    u8 *data;

    if(pSize == nullptr) {
        pSize = &sizeptr;
    }

    int compression = JKRConvertAttrToCompressionType((u8)(fileEntry->mFlag >> 24));

    if(fileEntry->mData == nullptr) {
        size = fetchResource_subroutine(mEntryNum, _64 + fileEntry->mDataOffset, fileEntry->mSize, mHeap, (int)compression, mCompression, &data);
        *pSize = size;
        if(size == 0) {
            return nullptr;
        }
        fileEntry->mData = data;
        if (compression == JKRCOMPRESSION_YAZ0) {
            setExpandSize(fileEntry, *pSize);
        }
    }
    else if (compression == JKRCOMPRESSION_YAZ0) {
        *pSize = getExpandSize(fileEntry);
    }
    else {
        *pSize = fileEntry->mSize;
    }

    return fileEntry->mData;
}

void *JKRDvdArchive::fetchResource(void *data, u32 compressedSize, SDIFileEntry *fileEntry, u32 *pSize, JKRExpandSwitch expandSwitch)
{
#line 504
    JUT_ASSERT(isMounted());

    u32 fileSize = fileEntry->mSize;
    u32 alignedSize = ALIGN_NEXT(fileSize, 32);
    u32 fileFlag = fileEntry->mFlag >> 0x18;
    int compression = JKRConvertAttrToCompressionType(fileFlag);

    if (fileEntry->mData == nullptr)
    {
        if (expandSwitch != EXPAND_SWITCH_DECOMPRESS)
            compression = JKRCOMPRESSION_NONE;
        compressedSize = (s32)ALIGN_PREV(compressedSize, 32);
        fileSize = fetchResource_subroutine(mEntryNum, _64 + fileEntry->mDataOffset, fileEntry->mSize, (u8 *)data,
                                            compressedSize, compression, mCompression);
    }
    else {
        if (compression == JKRCOMPRESSION_YAZ0)
        {
            u32 expandSize = getExpandSize(fileEntry);
            if (expandSize != 0) {
                fileSize = expandSize;
            }
        }

        if (fileSize > compressedSize) {
            fileSize = compressedSize;
        }

        JKRHeap::copyMemory(data, fileEntry->mData, fileSize);
    }

    if (pSize != nullptr)
    {
        *pSize = fileSize;
    }
    return data;
}

u32 JKRDvdArchive::fetchResource_subroutine(long entryNum, u32 offset, u32 size, u8 *data, u32 expandSize, int fileCompression, int archiveCompression) {
    u32 prevAlignedSize, alignedSize;

    alignedSize = ALIGN_NEXT(size, 32);
    prevAlignedSize = ALIGN_PREV(expandSize, 32);
    switch (archiveCompression)
    {
    case JKRCOMPRESSION_NONE: {
        switch (fileCompression)
        {
        case JKRCOMPRESSION_NONE:

            if (alignedSize > prevAlignedSize)
            {
                alignedSize = prevAlignedSize;
            }
            JKRDvdToMainRam(entryNum, data, EXPAND_SWITCH_DEFAULT, alignedSize, nullptr, JKRDvdRipper::ALLOC_DIR_TOP, offset, nullptr, nullptr);
            DCInvalidateRange(data, alignedSize);
            return alignedSize;

        case JKRCOMPRESSION_YAY0:
        case JKRCOMPRESSION_YAZ0:
            u8 buf[64];
            u8 *bufPtr = (u8 *)ALIGN_NEXT((u32)buf, 32);
            JKRDvdToMainRam(entryNum, bufPtr, EXPAND_SWITCH_NONE, sizeof(buf) / 2, nullptr, JKRDvdRipper::ALLOC_DIR_TOP, offset, nullptr, nullptr);
            DCInvalidateRange(bufPtr, sizeof(buf) / 2);
            u32 expandFileSize = JKRDecompExpandSize(bufPtr);
            alignedSize = ALIGN_NEXT(expandFileSize, 32);
            if (alignedSize > prevAlignedSize) {
                alignedSize = prevAlignedSize;
            }
            JKRDvdToMainRam(entryNum, data, EXPAND_SWITCH_DECOMPRESS, alignedSize, nullptr, JKRDvdRipper::ALLOC_DIR_TOP, offset, nullptr, nullptr);
            DCInvalidateRange(data, alignedSize);
            return expandFileSize;
        }
    }
    case JKRCOMPRESSION_YAZ0: {
        if (size > prevAlignedSize)
        {
            size = prevAlignedSize;
        }
        JKRDvdRipper::loadToMainRAM(entryNum, data, EXPAND_SWITCH_DECOMPRESS, size, nullptr, JKRDvdRipper::ALLOC_DIR_TOP, offset, nullptr, nullptr);
        DCInvalidateRange(data, size);
        return size;
    }

    case JKRCOMPRESSION_YAY0: {
#line 649
        JUT_PANIC("Sorry, not applied for SZP archive.\n");
    }        
    
    default: {
        JUT_PANIC("??? bad sequence\n");
    }
        
    }
    return 0;
}

u32 JKRDvdArchive::fetchResource_subroutine(long entryNum, u32 offset, u32 size, JKRHeap *heap, int fileCompression, int archiveCompression, u8 **pBuf) {
    u32 alignedSize = ALIGN_NEXT(size, 32);
    
    u8 *buffer;
    switch (archiveCompression)
    {
    case JKRCOMPRESSION_NONE:
    {
        switch (fileCompression)
        {
        case JKRCOMPRESSION_NONE:
            buffer = (u8 *)JKRAllocFromHeap(heap, alignedSize, 32);
#line 675
            JUT_ASSERT(buffer != 0);

            JKRDvdToMainRam(entryNum, buffer, EXPAND_SWITCH_DEFAULT, alignedSize, nullptr, JKRDvdRipper::ALLOC_DIR_TOP, offset, nullptr, nullptr);
            DCInvalidateRange(buffer, alignedSize);
            *pBuf = buffer;
            return alignedSize;

        case JKRCOMPRESSION_YAY0:
        case JKRCOMPRESSION_YAZ0:
            u8 decompBuf[64];
            u8 *bufptr = (u8*)ALIGN_NEXT((u32)decompBuf, 32);
            JKRDvdToMainRam(entryNum, bufptr, EXPAND_SWITCH_NONE, sizeof(decompBuf) / 2, nullptr, JKRDvdRipper::ALLOC_DIR_TOP, offset, nullptr, nullptr);
            DCInvalidateRange(bufptr, 0x20);

            alignedSize = JKRDecompExpandSize(bufptr);

            buffer = (u8 *)JKRAllocFromHeap(heap, alignedSize, 32);
#line 715
            JUT_ASSERT(buffer);

            JKRDvdToMainRam(entryNum, buffer, EXPAND_SWITCH_DECOMPRESS, alignedSize, nullptr, JKRDvdRipper::ALLOC_DIR_TOP, offset, nullptr, nullptr);
            DCInvalidateRange(buffer, alignedSize);
            *pBuf = buffer;
            return alignedSize;
        }
    }
    case JKRCOMPRESSION_YAZ0:
    {
        buffer = (u8 *)JKRAllocFromHeap(heap, alignedSize, 32);
#line 735
        JUT_ASSERT(buffer);
        JKRDvdToMainRam(entryNum, buffer, EXPAND_SWITCH_DECOMPRESS, size, nullptr, JKRDvdRipper::ALLOC_DIR_TOP, offset, nullptr, nullptr);
        DCInvalidateRange(buffer, size);
        *pBuf = buffer;
        return alignedSize;
    }

    case JKRCOMPRESSION_YAY0: {
#line 754
        JUT_PANIC("Sorry, not applied SZP archive.\n");
    }

    default: {
        JUT_PANIC("??? bad sequence\n");
    }
        
    }
    return 0;
}

// might be long/s32 return
u32 JKRDvdArchive::getExpandedResSize(const void *resource) const
{
    if (mExpandSizes == 0)
    {
        return getResSize(resource);
    }

    SDIFileEntry *fileEntry = findPtrResource(resource);
    if (fileEntry == nullptr)
    {
        return 0xffffffff;
    }

    u8 flags = (fileEntry->mFlag >> 0x18);
    if ((flags & 4) == 0)
    { // not compressed
        return getResSize(resource);
    }

    u32 expandSize = getExpandSize(fileEntry);
    if (expandSize != 0)
    {
        return expandSize;
    }

    u8 buf[64];
    u8 *bufPtr = (u8 *)ALIGN_NEXT((u32)buf, 32);

    JKRDvdToMainRam(mEntryNum, bufPtr, EXPAND_SWITCH_NONE, sizeof(buf) / 2, nullptr, JKRDvdRipper::ALLOC_DIR_TOP, _64 + fileEntry->mDataOffset, nullptr, nullptr);
    DCInvalidateRange(bufPtr, sizeof(buf) / 2);

    u32 decompExpandSize = JKRDecompExpandSize(bufPtr);
    const_cast<JKRDvdArchive *>(this)->setExpandSize(fileEntry, decompExpandSize);
    return decompExpandSize;
}