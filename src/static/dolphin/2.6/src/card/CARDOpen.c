#include <dolphin/card.h>
#include <dolphin/dsp.h>
#include <dolphin/dvd.h>
#include <dolphin/os.h>

#include <dolphin/CARDPriv.h>

BOOL __CARDCompareFileName(CARDDir *ent, const char *fileName)
{
    char *entName;
    char c1;
    char c2;
    int n;

    entName = (char *)ent->fileName;
    n = CARD_FILENAME_MAX;
    while (0 <= --n)
    {
        if ((c1 = *entName++) != (c2 = *fileName++))
        {
            return FALSE;
        }
        else if (c2 == '\0')
        {
            return TRUE;
        }
    }

    if (*fileName == '\0')
    {
        return TRUE;
    }

    return FALSE;
}

s32 __CARDAccess(CARDControl *card, CARDDir *ent)
{
    const DVDDiskID *diskID = card->diskID;
    if (ent->gameName[0] == 0xFF)
    {
        return CARD_RESULT_NOFILE;
    }

    if (diskID == &__CARDDiskNone || (memcmp(ent->gameName, diskID->gameName, 4) == 0 &&
                                      memcmp(ent->company, diskID->company, 2) == 0))
    {
        return CARD_RESULT_READY;
    }

    return CARD_RESULT_NOPERM;
}

s32 __CARDIsWritable(CARDControl *card, CARDDir *entry)
{
    const DVDDiskID *diskID = card->diskID;
    s32 result;
    u8 perm;

    result = __CARDAccess(card, entry);
    if (result == CARD_RESULT_NOPERM)
    {
        perm = (u8)(entry->permission & __CARDPermMask);

        if ((perm & 0x20) && (memcmp(entry->gameName, __CARDDiskNone.gameName, 4) == 0 && memcmp(entry->company, __CARDDiskNone.company, 2) == 0))
        {
            return CARD_RESULT_READY;
        }

        if ((perm & 0x40) && (memcmp(entry->gameName, __CARDDiskNone.gameName, 4) == 0 && memcmp(entry->company, diskID->company, 2) == 0))
        {
            return CARD_RESULT_READY;
        }
    }
    return result;
}

s32 __CARDIsReadable(CARDControl* card, CARDDir* entry)
{
	s32 result = __CARDIsWritable(card, entry);

	if (result == CARD_RESULT_NOPERM && (entry->permission & 0x4)) {
		return CARD_RESULT_READY;
	}

	return result;
}

s32 __CARDGetFileNo(CARDControl *card, const char *fileName, s32 *pfileNo)
{
    CARDDir *dir;
    CARDDir *ent;
    s32 fileNo;
    s32 result;

    if (!card->attached)
    {
        return CARD_RESULT_NOCARD;
    }

    dir = __CARDGetDirBlock(card);
    for (fileNo = 0; fileNo < CARD_MAX_FILE; fileNo++)
    {
        ent = &dir[fileNo];
        result = __CARDAccess(card, ent);
        if (result < 0)
        {
            continue;
        }
        if (__CARDCompareFileName(ent, fileName))
        {
            *pfileNo = fileNo;
            return CARD_RESULT_READY;
        }
    }

    return CARD_RESULT_NOFILE;
}

s32 CARDFastOpen(s32 chan, s32 fileno, CARDFileInfo *fileinfo)
{
    CARDControl *card;
    CARDDir *dir;
    CARDDir *ent;
    s32 result;

    if (fileno < 0 || fileno >= 127)
    {
        return CARD_RESULT_FATAL_ERROR;
    }
    fileinfo->chan = -1;
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0)
    {
        return result;
    }

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileno];
    result = __CARDIsReadable(card, ent);

    if (0 <= result)
    {
        if (!CARDIsValidBlockNo(card, ent->startBlock))
        {
            result = CARD_RESULT_BROKEN;
        }
        else
        {
            fileinfo->chan = chan;
            fileinfo->fileNo = fileno;
            fileinfo->offset = 0;
            fileinfo->iBlock = ent->startBlock;
        }

    }
    return __CARDPutControlBlock(card, result);
}

s32 CARDOpen(s32 chan, const char *fileName, CARDFileInfo *fileInfo)
{
    CARDControl *card;
    CARDDir *dir;
    CARDDir *ent;
    s32 result;
    s32 fileNo;

    fileInfo->chan = -1;
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0)
    {
        return result;
    }
    result = __CARDGetFileNo(card, fileName, &fileNo);
    if (0 <= result)
    {
        dir = __CARDGetDirBlock(card);
        ent = &dir[fileNo];
        if (!CARDIsValidBlockNo(card, ent->startBlock))
        {
            result = CARD_RESULT_BROKEN;
        }
        else
        {
            fileInfo->chan = chan;
            fileInfo->fileNo = fileNo;
            fileInfo->offset = 0;
            fileInfo->iBlock = ent->startBlock;
        }
    }
    return __CARDPutControlBlock(card, result);
}

s32 CARDClose(CARDFileInfo *fileInfo)
{
    CARDControl *card;
    s32 result;

    result = __CARDGetControlBlock(fileInfo->chan, &card);
    if (result < 0)
    {
        return result;
    }

    fileInfo->chan = -1;
    return __CARDPutControlBlock(card, CARD_RESULT_READY);
}

BOOL __CARDIsOpened(CARDControl *card, s32 fileNo) { return FALSE; }
