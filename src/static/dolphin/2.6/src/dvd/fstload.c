#include <dolphin/DVDPriv.h>
#include <dolphin/dvd.h>
#include <dolphin/hw_regs.h>
#include <dolphin/os.h>
#include <dolphin/os/OSBootInfo.h>
#include <cstring>

static s32 status = 0;

static u8 bb2Buf[OSRoundUp32B(sizeof(DVDBB2)) + 31];
static DVDBB2 *bb2 = 0;
static DVDDiskID *idTmp = NULL;

static void cb(s32 result, DVDCommandBlock *block)
{
    if (result > 0)
    {
        switch (status)
        {
        case 0:
            status = 1;
            DVDReadAbsAsyncForBS(block, bb2, OSRoundUp32B(sizeof(bb2)), 0x420, cb);
            break;
        case 1:
            status = 2;
            DVDReadAbsAsyncForBS(block, bb2->FSTAddress, OSRoundUp32B(bb2->FSTLength), bb2->FSTPosition,
                                 cb);
        }
    }
    else if (result == -1)
    {
    }
    else if (result == -4)
    {
        status = 0;
        DVDReset();
        DVDReadDiskID(block, idTmp, cb);
    }
}

void __fstLoad()
{
    OSBootInfo *bootInfo;
    DVDDiskID *id;
    u8 idTmpBuf[sizeof(DVDDiskID) + 31];
    static DVDCommandBlock block;
    void *arenaHi;

    arenaHi = OSGetArenaHi();
    bootInfo = (OSBootInfo *)OSPhysicalToCached(0);

    idTmp = (DVDDiskID *)(OSRoundUp32B(idTmpBuf));
    bb2 = (DVDBB2 *)(OSRoundUp32B(bb2Buf));

    DVDReset();
    DVDReadDiskID(&block, idTmp, cb);
    while (DVDGetDriveStatus() != 0)
        ;

    bootInfo->FSTLocation = bb2->FSTAddress;
    bootInfo->FSTMaxLength = bb2->FSTMaxLength;

    id = &bootInfo->DVDDiskID;

    memcpy(id, idTmp, sizeof(DVDDiskID));
    OSReport("\n");
    OSReport("  Game Name ... %c%c%c%c\n", id->gameName[0], id->gameName[1], id->gameName[2],
             id->gameName[3]);
    OSReport("  Company ..... %c%c\n", id->company[0], id->company[1]);
    OSReport("  Disk # ...... %d\n", id->diskNumber);
    OSReport("  Game ver .... %d\n", id->gameVersion);
    OSReport("  Streaming ... %s\n", (id->streaming == 0) ? "OFF" : "ON");
    OSReport("\n");
    OSSetArenaHi(bb2->FSTAddress);
}