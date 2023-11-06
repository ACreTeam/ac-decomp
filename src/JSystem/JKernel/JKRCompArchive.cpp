#include <dolphin/string.h>
#include <dolphin/os/OSCache.h>

#include "JSystem/JSystem.h"
#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/JKernel/JKRDecomp.h"
#include "JSystem/JKernel/JKRDvdAramRipper.h"
#include "JSystem/JKernel/JKRDvdRipper.h"
#include "JSystem/JUtility/JUTAssertion.h"

JKRCompArchive::JKRCompArchive(long entryNum, EMountDirection mountDirection) : JKRArchive(entryNum, MOUNT_COMP)
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

#ifdef DEBUG
void stringGen()
{
    JUT_PANIC("isMounted()");
    JUT_PANIC("mMountCount == 1");
}
#endif

JKRCompArchive::~JKRCompArchive()
{
    if (mArcInfoBlock)
    {
        SDIFileEntry *fileEntries = mFileEntries;
        for (int i = 0; i < mArcInfoBlock->num_file_entries; i++)
        {
            u32 flag = (fileEntries->mFlag >> 24);
            if ((flag & 16) == 0 && fileEntries->mData != nullptr)
            {
                JKRFreeToHeap(mHeap, fileEntries->mData);
            }
            fileEntries++;
        }
        JKRFreeToHeap(mHeap, mArcInfoBlock);
        mArcInfoBlock = nullptr;
    }
    if (mAramPart)
    {
        delete mAramPart;
    }
    if (mDvdFile)
    {
        delete mDvdFile;
    }

    sVolumeList.remove(&mFileLoaderLink);
    mIsMounted = false;
}

bool JKRCompArchive::open(long entryNum)
{
    mArcInfoBlock = nullptr;
    _60 = 0;
    mAramPart = nullptr;
    _68 = 0;
    mSizeOfMemPart = 0;
    mSizeOfAramPart = 0;
    _78 = 0;
    mDirectories = nullptr;
    mFileEntries = nullptr;
    mStrTable = nullptr;

    mDvdFile = new (JKRGetSystemHeap(), 0) JKRDvdFile(entryNum);
    if (mDvdFile == nullptr)
    {
        mMountMode = 0;
        return 0;
    }
    SArcHeader *arcHeader = (SArcHeader *)JKRAllocFromSysHeap(sizeof(SArcHeader), -32); // NOTE: unconfirmed if this struct is used
    if (arcHeader == nullptr)
    {
        mMountMode = 0;
    }
    else
    {
        int alignment;

        JKRDvdToMainRam(entryNum, (u8 *)arcHeader, EXPAND_SWITCH_DECOMPRESS, 32, nullptr, JKRDvdRipper::ALLOC_DIR_TOP, 0, &mCompression);
        DCInvalidateRange(arcHeader, 32);

        mSizeOfMemPart = arcHeader->_14;
        mSizeOfAramPart = arcHeader->_18;
        JUT_ASSERT((mSizeOfMemPart & 0x1f) == 0);
        JUT_ASSERT((mSizeOfAramPart & 0x1f) == 0);

        switch (mCompression)
        {
        case JKRCOMPRESSION_NONE:
        case JKRCOMPRESSION_YAZ0:
            alignment = mMountDirection == 1 ? 32 : -32;
            mArcInfoBlock = (SArcDataInfo *)JKRAllocFromHeap(mHeap, arcHeader->file_data_offset + mSizeOfMemPart, alignment);
            if (mArcInfoBlock == nullptr)
            {
                mMountMode = 0;
            }
            else
            {
                JKRDvdToMainRam(entryNum, (u8 *)mArcInfoBlock, EXPAND_SWITCH_DECOMPRESS, (u32)arcHeader->file_data_offset + mSizeOfMemPart,
                                nullptr, JKRDvdRipper::ALLOC_DIR_TOP, 0x20, nullptr);
                DCInvalidateRange(mArcInfoBlock, (u32)arcHeader->file_data_offset + mSizeOfMemPart);
                _60 = (u32)mArcInfoBlock + arcHeader->file_data_offset;

                if (mSizeOfAramPart != 0)
                {
                    mAramPart = JKRAllocFromAram(mSizeOfAramPart, JKRAramHeap::Head);
                    if (mAramPart == nullptr)
                    {
                        mMountMode = 0;
                        break;
                    }

                    JKRDvdToAram(entryNum, mAramPart->getAddress(), EXPAND_SWITCH_DECOMPRESS, arcHeader->header_length + arcHeader->file_data_offset + mSizeOfMemPart, 0);
                }

                mDirectories = (SDIDirEntry *)((u32)mArcInfoBlock + mArcInfoBlock->node_offset);
                mFileEntries = (SDIFileEntry *)((u32)mArcInfoBlock + mArcInfoBlock->file_entry_offset);
                mStrTable = (const char *)((u32)mArcInfoBlock + mArcInfoBlock->string_table_offset);
                _68 = arcHeader->header_length + arcHeader->file_data_offset;
            }
            break;

        case JKRCOMPRESSION_YAY0:
            u32 alignedSize = ALIGN_NEXT(mDvdFile->getFileSize(), 32);
            alignment = ((mMountDirection == 1) ? 32 : -32);
            u8 *buf = (u8 *)JKRAllocFromSysHeap(alignedSize, -alignment);

            if (buf == nullptr)
            {
                mMountMode = 0;
            }
            else
            {
                JKRDvdToMainRam(entryNum, buf, EXPAND_SWITCH_NONE, alignedSize, nullptr, JKRDvdRipper::ALLOC_DIR_TOP, 0, nullptr);
                DCInvalidateRange(buf, alignedSize);
                u32 expandSize = ALIGN_NEXT(JKRDecompExpandSize(buf), 32);
                u8 *mem = (u8 *)JKRAllocFromHeap(mHeap, expandSize, -alignment);

                if (mem == nullptr)
                {
                    mMountMode = 0;
                }
                else
                {
                    arcHeader = (SArcHeader *)mem;
                    JKRDecompress((u8 *)buf, (u8 *)mem, expandSize, 0);
                    JKRFreeToSysHeap(buf);

                    mArcInfoBlock = (SArcDataInfo *)JKRAllocFromHeap(mHeap, arcHeader->file_data_offset + mSizeOfMemPart, alignment);
                    if (mArcInfoBlock == nullptr)
                    {
                        mMountMode = 0;
                    }
                    else
                    {
                        // arcHeader + 1 should lead to 0x20, which is the data after the header
                        JKRHeap::copyMemory((u8 *)mArcInfoBlock, arcHeader + 1, (arcHeader->file_data_offset + mSizeOfMemPart));
                        _60 = (u32)mArcInfoBlock + arcHeader->file_data_offset;
                        if (mSizeOfAramPart != 0)
                        {
                            mAramPart = JKRAllocFromAram(mSizeOfAramPart, JKRAramHeap::Head);
                            if (mAramPart == nullptr)
                            {
                                mMountMode = 0;
                            }
                            else
                            {
                                JKRMainRamToAram((u8 *)mem + arcHeader->header_length + arcHeader->file_data_offset + mSizeOfMemPart,
                                                 mAramPart->getAddress(), mSizeOfAramPart, EXPAND_SWITCH_DEFAULT, 0, nullptr, -1, nullptr);
                            }
                        }
                    }
                }
            }
            mDirectories = (SDIDirEntry *)((u32)mArcInfoBlock + mArcInfoBlock->node_offset);
            mFileEntries = (SDIFileEntry *)((u32)mArcInfoBlock + mArcInfoBlock->file_entry_offset);
            mStrTable = (const char *)((u32)mArcInfoBlock + mArcInfoBlock->string_table_offset);
            _68 = arcHeader->header_length + arcHeader->file_data_offset;
            break;
        }

        u8 compressedFiles = 0;
        SDIFileEntry *fileEntry = mFileEntries;
        for (int i = 0; i < mArcInfoBlock->num_file_entries; i++)
        {
            u8 flag = fileEntry->mFlag >> 0x18;
            if (((flag & 0x1) != 0) && (((flag)&0x10) == 0))
            {
                compressedFiles = compressedFiles | (flag & 4);
            }
            fileEntry++;
        }

        if (compressedFiles != 0)
        {
            /*mExpandSizes = (u32 *)JKRAllocFromHeap(mHeap, mArcInfoBlock->num_file_entries * 4, abs(alignment));
            if (mExpandSizes == nullptr)
            {
                JKRFreeToSysHeap(mArcInfoBlock);
                mMountMode = 0;
            }
            else
            {
                memset(mExpandSizes, 0, mArcInfoBlock->num_file_entries * 4);
            }*/
        }
    }

    if (arcHeader != nullptr)
    {
        JKRFreeToSysHeap(arcHeader);
    }
    if (mMountMode == 0)
    {
        JREPORT(":::[%s: %d] Cannot alloc memory in mounting CompArchive\n", __FILE__, 567); // Macro?
        if (mDvdFile != nullptr)
        {
            delete mDvdFile;
        }
        return false;
    }
    return true;
}

void *JKRCompArchive::fetchResource(SDIFileEntry *fileEntry, u32 *pSize)
{
    JUT_ASSERT(isMounted());

    u32 ptrSize;
    u32 size = fileEntry->mSize;
    int compression = JKRConvertAttrToCompressionType(fileEntry->mFlag >> 0x18);

    if (pSize == nullptr)
    {
        pSize = &ptrSize; // this makes barely any sense but ok
    }

    if (fileEntry->mData == nullptr)
    {
        u32 flag = fileEntry->mFlag >> 0x18;
        if (flag & 0x10)
        {
            fileEntry->mData = (void *)(_60 + fileEntry->mDataOffset);
            *pSize = size;
        }
        else if (flag & 0x20)
        {
            u8 *data;
            *pSize = JKRAramArchive::fetchResource_subroutine(fileEntry->mDataOffset + mAramPart->getAddress() - mSizeOfMemPart, size, mHeap, compression, &data);
            fileEntry->mData = data;
            /*if (compression == JKRCOMPRESSION_YAZ0)
            {
                setExpandSize(fileEntry, *pSize);
            }*/
        }
        else if (flag & 0x40)
        {
            u8 *data;
            u32 resSize = JKRDvdArchive::fetchResource_subroutine(mEntryNum, _68 + fileEntry->mDataOffset, fileEntry->mSize, mHeap, compression, mCompression, &data);
            if (pSize != nullptr)
            {
                *pSize = resSize;
            }
            fileEntry->mData = data;
            /*if (compression == JKRCOMPRESSION_YAZ0)
            {
                setExpandSize(fileEntry, *pSize);
            }*/
        }
    }
    else
    {
        if (pSize != nullptr)
        {
            *pSize = fileEntry->mSize;
        }
    }
    return fileEntry->mData;
}

void *JKRCompArchive::fetchResource(void *data, u32 compressedSize, SDIFileEntry *fileEntry, u32 *pSize, JKRExpandSwitch expandSwitch)
{
    u32 size = 0;
    JUT_ASSERT(isMounted());

    u32 fileSize = fileEntry->mSize;
    u32 alignedSize = ALIGN_NEXT(fileSize, 32);
    u32 fileFlag = fileEntry->mFlag >> 0x18;
    int compression = JKRConvertAttrToCompressionType(fileFlag);

    if (fileEntry->mData != nullptr)
    {
        /*if (compression == JKRCOMPRESSION_YAZ0)
        {
            u32 expandSize = getExpandSize(fileEntry);
            if (expandSize != 0)
            {
                fileSize = expandSize;
            }
        }*/

        if (fileSize > compressedSize)
        {
            fileSize = compressedSize;
        }

        JKRHeap::copyMemory(data, fileEntry->mData, fileSize);
        size = fileSize;
    }
    else
    {
        if (fileFlag & 0x10)
        {
            size = JKRMemArchive::fetchResource_subroutine((u8 *)(_60 + fileEntry->mDataOffset), alignedSize, (u8 *)data,
                                                           compressedSize & ~31, compression);
        }
        else if (fileFlag & 0x20)
        {
            size = JKRAramArchive::fetchResource_subroutine(fileEntry->mDataOffset + mAramPart->getAddress() - mSizeOfMemPart,
                                                            alignedSize, (u8 *)data, compressedSize & ~31, compression);
        }
        else if (fileFlag & 0x40)
        {
            size = JKRDvdArchive::fetchResource_subroutine(mEntryNum, _68 + fileEntry->mDataOffset, alignedSize, (u8 *)data,
                                                           compressedSize & ~31, compression, mCompression);
        }
        else
        {
            JUT_PANIC("illegal archive.");
        }
    }

    if (pSize != nullptr)
    {
        *pSize = size;
    }
    return data;
}

void JKRCompArchive::removeResourceAll()
{
    if (mArcInfoBlock != nullptr && mMountMode != MOUNT_MEM)
    {
        SDIFileEntry *fileEntry = mFileEntries;
        for (int i = 0; i < mArcInfoBlock->num_file_entries; i++)
        {
            u32 flag = fileEntry->mFlag >> 0x18;
            if (fileEntry->mData != nullptr)
            {
                if ((flag & 0x10) == 0)
                {
                    JKRFreeToHeap(mHeap, fileEntry->mData);
                }

                fileEntry->mData = nullptr;
            }
        }
    }
}

bool JKRCompArchive::removeResource(void *resource)
{
    SDIFileEntry *fileEntry = findPtrResource(resource);
    if (!fileEntry)
        return false;

    if (((fileEntry->mFlag >> 0x18) & 0x10) == 0)
    {
        JKRFreeToHeap(mHeap, resource);
    }

    fileEntry->mData = nullptr;
    return true;
}
