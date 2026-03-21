/* DVD shim: routes DVD* API calls to the GCM virtual filesystem.
 * Stage 1: DVDInit always returns FALSE (no disc image found).
 * Stage 5: reads settings.ini for disc path, opens ISO, returns real data. */
#include "platform/platform.h"
#include "gcm_fs.h"
#include <dolphin/dvd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/* DiskID global (replaces the AT_ADDRESS(0x80000000) declaration) */
DVDDiskID DiskID = {};

static bool s_disc_open = false;

/* Read the disc path from settings.ini */
static const char* read_disc_path(void) {
    static char path[1024] = {};
    /* Try to read from settings.ini next to the executable */
    FILE* f = fopen("settings.ini", "r");
    if (!f) {
        const char* home = getenv("HOME");
        if (home) {
            snprintf(path, sizeof(path),
                     "%s/Library/Application Support/AnimalCrossing/settings.ini", home);
            f = fopen(path, "r");
        }
    }
    if (!f) return nullptr;
    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "disc=", 5) == 0) {
            size_t len = strlen(line + 5);
            if (len > 0 && line[5 + len - 1] == '\n')
                line[5 + len - 1] = '\0';
            strncpy(path, line + 5, sizeof(path) - 1);
            fclose(f);
            return path;
        }
    }
    fclose(f);
    return nullptr;
}

extern "C" {

void DVDInit(void) {
    const char* disc = read_disc_path();
    if (disc && gcm_fs_open(disc)) {
        s_disc_open = true;
        /* Populate DiskID from the first 32 bytes of the image */
        gcm_fs_read(0, &DiskID, sizeof(DiskID));
        fprintf(stderr, "[DVD] Disc opened: %.4s%.2s\n",
                DiskID.gameName, DiskID.company);
    } else {
        fprintf(stderr, "[DVD] No disc image — set disc= in settings.ini\n");
    }
}

BOOL DVDOpen(char* filename, DVDFileInfo* fileInfo) {
    if (!s_disc_open || !fileInfo) return FALSE;
    uint32_t off = 0, len = 0;
    if (!gcm_fs_lookup(filename, &off, &len)) {
        fprintf(stderr, "[DVD] File not found: %s\n", filename);
        return FALSE;
    }
    memset(fileInfo, 0, sizeof(*fileInfo));
    fileInfo->startAddr = off;
    fileInfo->length    = len;
    fileInfo->cb.state  = DVD_FILEINFO_READY;
    return TRUE;
}

BOOL DVDFastOpen(s32 entryNum, DVDFileInfo* fileInfo) {
    /* TODO Stage 5: look up by FST entry number */
    (void)entryNum; (void)fileInfo;
    return FALSE;
}

s32 DVDReadPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, s32 prio) {
    (void)prio;
    if (!s_disc_open || !fileInfo || !addr) return DVD_RESULT_FATAL_ERROR;
    uint32_t disc_off = fileInfo->startAddr + (uint32_t)offset;
    if (!gcm_fs_read(disc_off, addr, (uint32_t)length)) return DVD_RESULT_FATAL_ERROR;
    return length;
}

/* Async read: spawn a detached thread */
struct AsyncCtx {
    DVDFileInfo* fi;
    void* addr;
    s32 length;
    s32 offset;
    DVDCallback cb;
};

static void* async_read_thread(void* arg) {
    AsyncCtx* ctx = (AsyncCtx*)arg;
    s32 r = DVDReadPrio(ctx->fi, ctx->addr, ctx->length, ctx->offset, 2);
    if (ctx->cb) ctx->cb(r >= 0 ? DVD_RESULT_GOOD : DVD_RESULT_FATAL_ERROR, ctx->fi);
    free(ctx);
    return nullptr;
}

BOOL DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset,
                      DVDCallback callback, s32 prio) {
    (void)prio;
    AsyncCtx* ctx = (AsyncCtx*)malloc(sizeof(*ctx));
    if (!ctx) return FALSE;
    ctx->fi     = fileInfo;
    ctx->addr   = addr;
    ctx->length = length;
    ctx->offset = offset;
    ctx->cb     = callback;
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    bool ok = pthread_create(&tid, &attr, async_read_thread, ctx) == 0;
    pthread_attr_destroy(&attr);
    if (!ok) { free(ctx); return FALSE; }
    return TRUE;
}

BOOL DVDClose(DVDFileInfo* fileInfo) { (void)fileInfo; return TRUE; }
void DVDResume(void)  {}
void DVDReset(void)   {}

BOOL DVDCancelAsync(DVDCommandBlock* block, DVDCBCallback callback) {
    (void)block; (void)callback; return FALSE;
}
s32 DVDCancel(volatile DVDCommandBlock* block) { (void)block; return -1; }
s32 DVDChangeDisk(DVDCommandBlock* b, DVDDiskID* id) { (void)b; (void)id; return -1; }
BOOL DVDChangeDiskAsync(DVDCommandBlock* b, DVDDiskID* id, DVDCBCallback cb) {
    (void)b; (void)id; (void)cb; return FALSE;
}

s32  DVDGetCommandBlockStatus(const DVDCommandBlock* b) { (void)b; return 0; }
s32  DVDGetDriveStatus(void) {
    return s_disc_open ? DVD_STATE_END : DVD_STATE_NO_DISK;
}
BOOL DVDSetAutoInvalidation(BOOL v) { return v; }
void* DVDGetFSTLocation(void) { return nullptr; /* TODO Stage 5 */ }

BOOL DVDOpenDir(char* dirName, DVDDir* dir) { (void)dirName; (void)dir; return FALSE; }
BOOL DVDReadDir(DVDDir* dir, DVDDirEntry* e) { (void)dir; (void)e; return FALSE; }
BOOL DVDCloseDir(DVDDir* dir) { (void)dir; return TRUE; }
BOOL DVDGetCurrentDir(char* p, u32 max) { (void)max; if (p) p[0]='\0'; return TRUE; }
BOOL DVDChangeDir(char* d) { (void)d; return FALSE; }
s32  DVDConvertPathToEntrynum(char* p) { (void)p; return -1; }
s32  DVDGetTransferredSize(DVDFileInfo* fi) { (void)fi; return 0; }
DVDDiskID* DVDGetCurrentDiskID(void) { return &DiskID; }
BOOL DVDCompareDiskID(DVDDiskID* a, DVDDiskID* b) {
    if (!a || !b) return FALSE;
    return memcmp(a, b, sizeof(*a)) == 0 ? TRUE : FALSE;
}
DVDLowCallback DVDLowClearCallback(void)  { return nullptr; }
BOOL DVDPrepareStreamAsync(DVDFileInfo*, u32, u32, DVDCallback) { return FALSE; }
s32  DVDCancelStream(DVDCommandBlock* b)  { (void)b; return -1; }
BOOL DVDCheckDisk(void)                   { return s_disc_open ? TRUE : FALSE; }
void DVDPause(void)                       {}
s32  DVDSeekPrio(DVDFileInfo*, s32, s32)  { return -1; }
BOOL DVDSeekAsyncPrio(DVDFileInfo*, s32, DVDCallback, s32) { return FALSE; }
BOOL DVDFastOpenDir(s32, DVDDir*)         { return FALSE; }
BOOL DVDCancelAllAsync(DVDCBCallback cb)  { (void)cb; return FALSE; }
s32  DVDCancelAll(void)                   { return -1; }
void DVDDumpWaitingQueue(void)            {}

} /* extern "C" */
