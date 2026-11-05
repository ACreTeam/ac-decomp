extern "C" int abs(int);
#include "_mem.h"
#include "types.h"
#include <string.h>
#include "MSL_C/w_math.h"
#include "MSL_C/math.h"

#include <JSystem/JKernel/JKRAram.h>
#include <JSystem/JKernel/JKRArchive.h>
#include <JSystem/JKernel/JKRDvdAramRipper.h>
#include <JSystem/JUtility/JUTDbg.h>

JKRAramArchive::JKRAramArchive() : JKRArchive() {}

JKRAramArchive::JKRAramArchive(s32 entryNum, EMountDirection mountDirection) : JKRArchive(entryNum, MOUNT_ARAM)
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

JKRAramArchive::~JKRAramArchive()
{
    if (mIsMounted == true)
    {
        if (mArcInfoBlock)
        {
            SDIFileEntry *fileEntries = mFileEntries;
            for (int i = 0; i < mArcInfoBlock->num_file_entries; i++)
            {
                if (fileEntries->mData != nullptr) {
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
        if (mDvdFile) {
            delete mDvdFile;
        }
        if (mBlock) {
            delete mBlock;
        }

        sVolumeList.remove(&mFileLoaderLink);
        mIsMounted = false;
    }
}

void JKRAramArchive::fixedInit(long entryNum, EMountDirection direction) {
    mIsMounted = false;
    mMountDirection = direction;
    mMountMode = 2;
    mMountCount = 1;
    _58 = 2;
    mHeap = JKRGetCurrentHeap();
    mEntryNum = entryNum;

    if (sCurrentVolume)
        return;
    sCurrentVolume = this;
    sCurrentDirID = 0;
}

bool JKRAramArchive::mountFixed(long entryNum, EMountDirection direction) {
    if (entryNum < 0)
        return false;

    if (check_mount_already(entryNum, JKRGetCurrentHeap()))
        return false;

    fixedInit(entryNum, direction);
    if (open(entryNum) == false) {
        return false;
    }

    mVolumeType = 'RARC';
    mVolumeName = &mStrTable[mDirectories->mOffset];
    sVolumeList.prepend(&mFileLoaderLink);
    mIsMounted = true;
    return true;
}

bool JKRAramArchive::mountFixed(const char* path, EMountDirection direction) {
    s32 entrynum = DVDConvertPathToEntrynum((char*)path);
    return mountFixed(entrynum, direction);
}

void JKRAramArchive::unmountFixed() {
    if (sCurrentVolume == this)
        sCurrentVolume = nullptr;

    if (mArcInfoBlock) {
        SDIFileEntry* fileEntries = mFileEntries;
        for (int i = 0; i < mArcInfoBlock->num_file_entries; i++) {
            if (fileEntries->mData != nullptr) {
                JKRFreeToHeap(mHeap, fileEntries->mData);
            }
            fileEntries++;
        }
        JKRFreeToHeap(mHeap, mArcInfoBlock);
        mArcInfoBlock = nullptr;
    }

    if (mDvdFile)
        delete mDvdFile;

    if (mBlock)
        delete mBlock;

    sVolumeList.remove(&mFileLoaderLink);
    mIsMounted = false;
}

#if DEBUG
CW_FORCE_STRINGS(JKRAramArchive_cpp, __FILE__, "isMounted()", "mMountCount == 1")
#endif

bool JKRAramArchive::open(long entryNum) {
    mArcInfoBlock = nullptr;
    mDirectories = nullptr;
    mFileEntries = nullptr;
    mStrTable = nullptr;
    mBlock = nullptr;

    mDvdFile = new (JKRGetSystemHeap(), mMountDirection == MOUNT_DIRECTION_HEAD ? 4 : -4) JKRDvdFile(entryNum);
    if (mDvdFile == nullptr)
    {
        mMountMode = 0;
        return 0;
    }

    // NOTE: a different struct is used here for sure, unfortunately i can't get any hits on this address, so gonna leave it like this for now
    SArcHeader *mem = (SArcHeader *)JKRAllocFromSysHeap(32, -32); 
    if (mem == nullptr)  {
        mMountMode = 0;
    }
    else {
        JKRDvdToMainRam(entryNum, (u8 *)mem, EXPAND_SWITCH_DECOMPRESS, 32, nullptr, JKRDvdRipper::ALLOC_DIR_TOP, 0, &mCompression, nullptr);
        DCInvalidateRange(mem, 32);
        int alignment = mMountDirection == MOUNT_DIRECTION_HEAD ? 32 : -32;
        u32 alignedSize = ALIGN_NEXT(mem->file_data_offset, 32);
        mArcInfoBlock = (SArcDataInfo *)JKRAllocFromHeap(mHeap, alignedSize, alignment);
        if (mArcInfoBlock == nullptr) {
            mMountMode = 0;
        }
        else {
            JKRDvdToMainRam(entryNum, (u8 *)mArcInfoBlock, EXPAND_SWITCH_DECOMPRESS, alignedSize, nullptr, JKRDvdRipper::ALLOC_DIR_TOP, 32, nullptr, nullptr);
            DCInvalidateRange(mArcInfoBlock, alignedSize);

            mDirectories = (SDIDirEntry *)((u8 *)mArcInfoBlock + mArcInfoBlock->node_offset);
            mFileEntries = (SDIFileEntry *)((u8 *)mArcInfoBlock + mArcInfoBlock->file_entry_offset);
            mStrTable = (const char *)((u8 *)mArcInfoBlock + mArcInfoBlock->string_table_offset);
            mExpandSizes = nullptr;

            u8 compressedFiles = 0; // maybe a check for if the last file is compressed?

            SDIFileEntry *fileEntry = mFileEntries;
            for (int i = 0; i < mArcInfoBlock->num_file_entries; i++)
            {
                u8 flag = fileEntry->mFlag >> 24;
                if ((flag & 1))
                {
                    compressedFiles |= (flag & JKRARCHIVE_ATTR_COMPRESSION);
                }
                fileEntry++;
            }

            if (compressedFiles != 0)
            {
                mExpandSizes = (u32 *)JKRAllocFromHeap(mHeap, mArcInfoBlock->num_file_entries << 2, abs(alignment));
                if (mExpandSizes == nullptr)
                {
                    JKRFree(mArcInfoBlock);
                    mMountMode = 0;
                    goto cleanup;
                }
                memset(mExpandSizes, 0, mArcInfoBlock->num_file_entries << 2);
            }

            u32 aramSize = ALIGN_NEXT(mem->file_data_length, 32);
            mBlock = JKRAllocFromAram(aramSize, mMountDirection == MOUNT_DIRECTION_HEAD ? JKRAramHeap::AM_Head : JKRAramHeap::AM_Tail);
            if(mBlock == nullptr) {
                if (mArcInfoBlock) {
                    JKRFree(mArcInfoBlock);
                }
                if(mExpandSizes) {
                    JKRFree(mExpandSizes);
                }
                mMountMode = 0;
            }
            else {
                JKRDvdToAram(entryNum, mBlock->getAddress(), EXPAND_SWITCH_DECOMPRESS, mem->header_length + mem->file_data_offset, 0, nullptr);
            }

        }
    }
cleanup:
    if (mem != nullptr)
    {
        JKRFreeToSysHeap(mem);
    }
    if (mMountMode == 0)
    {
        JUT_REPORT_MSG(":::[%s: %d] Cannot alloc memory\n", __FILE__, 415); // TODO: macro
        if (mDvdFile != nullptr)
        {
            delete mDvdFile;
        }
        return false;
    }
    return true;
}

void *JKRAramArchive::fetchResource(SDIFileEntry *fileEntry, u32 *pSize)
{
#line 442
    JUT_ASSERT(isMounted());

    u32 sizeRef;
    u8 *data;

    if (pSize == nullptr) {
        pSize = &sizeRef; // this makes barely any sense but ok
    }

    int compression = JKRConvertAttrToCompressionType(fileEntry->mFlag >> 0x18);
    if(fileEntry->mData == nullptr) {
        u32 size = fetchResource_subroutine(fileEntry->mDataOffset + mBlock->getAddress(), fileEntry->mSize, mHeap, compression, &data);
        *pSize = size;
        if (size == 0) {
            return nullptr;
        }
        fileEntry->mData = data;
        if (compression == JKRCOMPRESSION_YAZ0)
        {
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

void *JKRAramArchive::fetchResource(void *data, u32 compressedSize, SDIFileEntry *fileEntry, u32 *pSize, JKRExpandSwitch expandSwitch) {
#line 515
    JUT_ASSERT(isMounted());
    u32 fileSize = fileEntry->mSize;
    if (fileSize > compressedSize) {
        fileSize = compressedSize;
    }

    int compression = JKRConvertAttrToCompressionType(fileEntry->mFlag >> 0x18);
    if (fileEntry->mData == nullptr) {
        if (expandSwitch != EXPAND_SWITCH_DECOMPRESS)
            compression = JKRCOMPRESSION_NONE;
        compressedSize = (s32)ALIGN_PREV(compressedSize, 32);
        fileSize = fetchResource_subroutine(fileEntry->mDataOffset + mBlock->getAddress(), fileSize, (u8 *)data,
                                            compressedSize, compression);
    }
    else
    {
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

// UNUSED
u32 JKRAramArchive::getAramAddress_Entry(SDIFileEntry *fileEntry)
{
#line 572
    JUT_ASSERT(isMounted());

    if(fileEntry == nullptr) {
        return 0;
    }
    return fileEntry->mDataOffset + mBlock->getAddress();
}

// UNUSED
u32 JKRAramArchive::getAramAddress(u32 type, const char* file) {
    SDIFileEntry* entry = findTypeResource(type, file);
    return getAramAddress_Entry(entry);
}

u32 JKRAramArchive::fetchResource_subroutine(u32 srcAram, u32 size, u8 *data, u32 expandSize, int compression)
{
    // do macros show in asserts? if not, use a macro here because if i ever reformat this then it'll screw this up
#line 628
    JUT_ASSERT(( srcAram & 0x1f ) == 0);

    u32 sizeRef;

    u32 alignedSize = ALIGN_NEXT(size, 32);
    u32 prevAlignedSize = ALIGN_PREV(expandSize, 32);
    switch (compression)
    {
    case JKRCOMPRESSION_NONE:
        if (alignedSize > prevAlignedSize)
        {
            alignedSize = prevAlignedSize;
        }
        JKRAramToMainRam(srcAram, data, alignedSize, EXPAND_SWITCH_DEFAULT, prevAlignedSize, nullptr, -1, &sizeRef);
        return sizeRef;
    case JKRCOMPRESSION_YAY0:
    case JKRCOMPRESSION_YAZ0:
        JKRAramToMainRam(srcAram, data, alignedSize, EXPAND_SWITCH_DECOMPRESS, prevAlignedSize, nullptr, -1, &sizeRef);
        return sizeRef;
    default:
#line 655
        JUT_PANIC("??? bad sequence\n")
        return 0;
    }
}

u32 JKRAramArchive::fetchResource_subroutine(u32 srcAram, u32 size, JKRHeap *heap, int compression, u8 **pBuf)
{
    u32 resSize;
    u32 alignedSize = ALIGN_NEXT(size, 32);

    u8 *buffer;
    switch(compression) {
    case JKRCOMPRESSION_NONE:
        buffer = (u8 *)JKRAllocFromHeap(heap, alignedSize, 32);
#line 677
        JUT_ASSERT(buffer != 0);

        JKRAramToMainRam(srcAram, buffer, alignedSize, EXPAND_SWITCH_DEFAULT, alignedSize, nullptr, -1, nullptr);
        *pBuf = buffer;
        return size;
    case JKRCOMPRESSION_YAY0:
    case JKRCOMPRESSION_YAZ0:
        u8 decompBuf[64];
        u8 *bufptr = (u8 *)ALIGN_NEXT((u32)decompBuf, 32);
        JKRAramToMainRam(srcAram, bufptr, sizeof(decompBuf) / 2, EXPAND_SWITCH_DEFAULT, 0, nullptr, -1, nullptr);

        u32 expandSize = ALIGN_NEXT(JKRDecompExpandSize(bufptr), 32);
        buffer = (u8 *)JKRAllocFromHeap(heap, expandSize, 32);
#line 703
        JUT_ASSERT(buffer);

        JKRAramToMainRam(srcAram, buffer, alignedSize, EXPAND_SWITCH_DECOMPRESS, expandSize, heap, -1, &resSize);
        *pBuf = buffer;
        return resSize;
    default:
#line 713
        JUT_PANIC("??? bad sequence\n");
        return 0;
    }
}

u32 JKRAramArchive::getExpandedResSize(const void *resource) const
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

    JKRAramToMainRam(fileEntry->mDataOffset + mBlock->getAddress(), bufPtr, sizeof(buf) / 2, EXPAND_SWITCH_DEFAULT, 0, nullptr, -1, nullptr);

    u32 decompExpandSize = JKRDecompExpandSize(bufPtr);
    const_cast<JKRAramArchive *>(this)->setExpandSize(fileEntry, decompExpandSize);
    return decompExpandSize;
}