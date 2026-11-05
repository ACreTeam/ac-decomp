#include "_mem.h"
#include "types.h"
#include <string.h>
#include <JSystem/JKernel/JKRArchive.h>
#include <JSystem/JKernel/JKRDecomp.h>
#include <JSystem/JKernel/JKRDvdRipper.h>
#include <JSystem/JUtility/JUTDbg.h>

JKRMemArchive::JKRMemArchive() : JKRArchive() {}

JKRMemArchive::JKRMemArchive(s32 entryNum, EMountDirection mountDirection) : JKRArchive(entryNum, MOUNT_MEM)
{
    mIsMounted = false;
    mMountDirection = mountDirection;
    if (!open(entryNum, mMountDirection)) {
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

JKRMemArchive::JKRMemArchive(void *mem, u32 size, JKRMemBreakFlag breakFlag) : JKRArchive((s32)mem, MOUNT_MEM)
{
    mIsMounted = false;
    if (!open(mem, size, breakFlag)) {
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

JKRMemArchive::~JKRMemArchive()
{
    if (mIsMounted == true)
    {
        if (mIsOpen && mArcHeader)
            JKRFreeToHeap(mHeap, mArcHeader);

        sVolumeList.remove(&mFileLoaderLink);
        mIsMounted = false;
    }
}

#if DEBUG // function is needed to generate certain strings first, however this is not what the original function looks like
void JKRMemArchive::fixedInit(s32)
{
#line 200
    JUT_ASSERT(isMounted());
    JUT_PANIC("mMountCount == 1"); // some member is called mMountCount, if there's a game with this assert, fix
    JUT_ASSERT(mArcHeader->signature == 'RARC');
}
#endif

bool JKRMemArchive::open(s32 entryNum, JKRArchive::EMountDirection mountDirection)
{
    mArcHeader = nullptr;
    mArcInfoBlock = nullptr;
    mArchiveData = nullptr;
    mDirectories = nullptr;
    mFileEntries = nullptr;
    mStrTable = nullptr;
    mIsOpen = false;
    mMountDirection = mountDirection;

    if (mMountDirection == JKRArchive::MOUNT_DIRECTION_HEAD)
    {
        u32 loadedSize;
        mArcHeader = (SArcHeader *)JKRDvdRipper::loadToMainRAM(
            entryNum, nullptr, EXPAND_SWITCH_DECOMPRESS, 0, mHeap, JKRDvdRipper::ALLOC_DIR_TOP,
            0, (int *)&mCompression, &loadedSize);
        if (mArcHeader)
        {
            DCInvalidateRange(mArcHeader, loadedSize);
        }
    }
    else
    {
        u32 loadedSize;
        mArcHeader = (SArcHeader *)JKRDvdRipper::loadToMainRAM(
            entryNum, nullptr, EXPAND_SWITCH_DECOMPRESS, 0, mHeap,
            JKRDvdRipper::ALLOC_DIR_BOTTOM, 0, (int *)&mCompression, &loadedSize);
        if (mArcHeader)
        {
            DCInvalidateRange(mArcHeader, loadedSize);
        }
    }

    if (!mArcHeader)
    {
        mMountMode = UNKNOWN_MOUNT_MODE;
    }
    else
    {
#line 438
        JUT_ASSERT(mArcHeader->signature == 'RARC');
        mArcInfoBlock = (SArcDataInfo *)((u8 *)mArcHeader + mArcHeader->header_length);
        mDirectories = (SDIDirEntry *)((u8 *)&mArcInfoBlock->num_nodes + mArcInfoBlock->node_offset);
        mFileEntries = (SDIFileEntry *)((u8 *)&mArcInfoBlock->num_nodes + mArcInfoBlock->file_entry_offset);
        mStrTable = (char *)((u8 *)&mArcInfoBlock->num_nodes + mArcInfoBlock->string_table_offset);

        mArchiveData =
            (u8 *)((u32)mArcHeader + mArcHeader->header_length + mArcHeader->file_data_offset);
        mIsOpen = true;
    }
#if DEBUG
    // OS Assert?
    if (mMountMode == UNKNOWN_MOUNT_MODE)
    {
        OSReport(":::Cannot alloc memory [%s][%d]\n", __FILE__, 460);
    }
#endif
    return (mMountMode == UNKNOWN_MOUNT_MODE) ? false : true;
}

bool JKRMemArchive::open(void *buffer, u32 bufferSize, JKRMemBreakFlag flag)
{
#line 490
    mArcHeader = (SArcHeader *)buffer;
    JUT_ASSERT(mArcHeader->signature == 'RARC');
    mArcInfoBlock = (SArcDataInfo *)((u8 *)mArcHeader + mArcHeader->header_length);
    mDirectories = (SDIDirEntry *)((u8 *)&mArcInfoBlock->num_nodes + mArcInfoBlock->node_offset);
    mFileEntries = (SDIFileEntry *)((u8 *)&mArcInfoBlock->num_nodes + mArcInfoBlock->file_entry_offset);
    mStrTable = (char *)((u8 *)&mArcInfoBlock->num_nodes + mArcInfoBlock->string_table_offset);
    mArchiveData = (u8 *)(((u32)mArcHeader + mArcHeader->header_length) + mArcHeader->file_data_offset);
    mIsOpen = (flag == MBF_1) ? true : false; // mIsOpen might be u8
    mHeap = JKRHeap::findFromRoot(buffer);
    mCompression = JKRCOMPRESSION_NONE;
    return true;
}

void *JKRMemArchive::fetchResource(SDIFileEntry *fileEntry, u32 *resourceSize)
{
#line 555
    JUT_ASSERT(isMounted())

    if (!fileEntry->mData)
        fileEntry->mData = mArchiveData + fileEntry->mDataOffset;

    if (resourceSize)
        *resourceSize = fileEntry->mSize;

    return fileEntry->mData;
}

void *JKRMemArchive::fetchResource(void *buffer, u32 bufferSize, SDIFileEntry *fileEntry,
                                   u32 *resourceSize, JKRExpandSwitch expandSwitch)
{
#line 595
    JUT_ASSERT(isMounted())

    u32 srcLength = fileEntry->mSize;
    if (srcLength > bufferSize)
    {
        srcLength = bufferSize;
    }

    if (fileEntry->mData != nullptr)
    {
        memcpy(buffer, fileEntry->mData, srcLength);
    }
    else
    {
        int compression = JKRConvertAttrToCompressionType(fileEntry->getAttr());
        if (expandSwitch != EXPAND_SWITCH_DECOMPRESS)
            compression = JKRCOMPRESSION_NONE;
        void *data = mArchiveData + fileEntry->mDataOffset;
        srcLength =
            fetchResource_subroutine((u8 *)data, srcLength, (u8 *)buffer, bufferSize, compression);
    }

    if (resourceSize)
    {
        *resourceSize = srcLength;
    }

    return buffer;
}

void JKRMemArchive::removeResourceAll(void)
{
#line 642
    JUT_ASSERT(isMounted());

    if (mArcInfoBlock == nullptr)
        return;
    if (mMountMode == MOUNT_MEM)
        return;

    // !@bug: looping over file entries without incrementing the fileEntry pointer. Thus, only the
    // first fileEntry will clear/remove the resource data.
    SDIFileEntry *fileEntry = mFileEntries;
    for (int i = 0; i < mArcInfoBlock->num_file_entries; i++)
    {
        if (fileEntry->mData)
        {
            fileEntry->mData = nullptr;
        }
    }
}

bool JKRMemArchive::removeResource(void *resource)
{
#line 673
    JUT_ASSERT(isMounted());

    SDIFileEntry *fileEntry = findPtrResource(resource);
    if (!fileEntry)
        return false;

    fileEntry->mData = nullptr;
    return true;
}

u32 JKRMemArchive::fetchResource_subroutine(u8 *src, u32 srcLength, u8 *dst, u32 dstLength, int compression)
{
    switch (compression) // Maybe change CompressionMethod to defines?
    {
    case JKRCOMPRESSION_NONE:
        if (srcLength > dstLength)
            srcLength = dstLength;

        memcpy(dst, src, srcLength);
        return srcLength;

    case JKRCOMPRESSION_YAY0:
    case JKRCOMPRESSION_YAZ0:
        u32 expendedSize = JKRDecompExpandSize(src);
        srcLength = expendedSize;
        if (expendedSize > dstLength)
            srcLength = dstLength;

        JKRDecompress(src, dst, srcLength, 0);
        return srcLength;

    default:
    {
#line 723
        JUT_PANIC("??? bad sequence\n");
        return 0;
    }
    }

    return srcLength;
}

u32 JKRMemArchive::getExpandedResSize(const void *resource) const
{
    SDIFileEntry *fileEntry = findPtrResource(resource);
    if (fileEntry == nullptr)
        return -1;

    if (((u8)(fileEntry->mFlag >> 24) & 4) == 0)
        return getResSize(resource);
    else
        return JKRDecompExpandSize((u8 *)resource);
}