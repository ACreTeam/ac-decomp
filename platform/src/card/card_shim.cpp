/* CARD shim: redirects CARDxxx API to GCI file I/O.
 * Stage 1: stubs returning CARD_RESULT_NOCARD.
 * Stage 11: full GCI read/write. */
#include "platform/platform.h"
#include <dolphin/card.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <mutex>
#include <sys/stat.h>
#include <unistd.h>

/* Side table: maps fileNo → file path (since CARDFileInfo has no extra storage) */
static std::map<s32, std::string> s_file_paths;
static std::mutex s_file_map_lock;
static s32 s_next_fileno = 1;

static const char* save_dir(void) {
    static char dir[1024] = {};
    if (dir[0]) return dir;
    const char* home = getenv("HOME");
    if (home)
        snprintf(dir, sizeof(dir),
                 "%s/Library/Application Support/AnimalCrossing/save", home);
    else
        snprintf(dir, sizeof(dir), "./save");
    return dir;
}

static void ensure_save_dir(void) {
    const char* path = save_dir();
    char tmp[1024];
    size_t n = strlen(path);
    if (n >= sizeof(tmp)) return;
    memcpy(tmp, path, n + 1);

    for (size_t i = 1; i < n; i++) {
        if (tmp[i] == '/') {
            tmp[i] = '\0';
            mkdir(tmp, 0755);
            tmp[i] = '/';
        }
    }
    mkdir(tmp, 0755);
}

extern "C" {

void CARDInit(void) {}

s32 CARDMount(s32 chan, void* workArea, CARDCallback detachCb) {
    (void)workArea; (void)detachCb;
    return (chan == 0) ? CARD_RESULT_READY : CARD_RESULT_NOCARD;
}

s32 CARDMountAsync(s32 chan, void* workArea, CARDCallback detach,
                   CARDCallback attach) {
    (void)workArea; (void)detach;
    s32 r = (chan == 0) ? CARD_RESULT_READY : CARD_RESULT_NOCARD;
    if (attach) attach(chan, r);
    return r;
}

s32 CARDUnmount(s32 chan) { (void)chan; return CARD_RESULT_READY; }

BOOL CARDProbe(s32 chan) { return (chan == 0) ? TRUE : FALSE; }

s32 CARDProbeEx(s32 chan, s32* memSize, s32* sectorSize) {
    if (chan != 0) return CARD_RESULT_NOCARD;
    if (memSize)    *memSize    = 0x80000; /* 512 KB */
    if (sectorSize) *sectorSize = 0x2000;
    return CARD_RESULT_READY;
}

s32 CARDOpen(s32 chan, const char* fileName, CARDFileInfo* fileInfo) {
    if (chan != 0 || !fileInfo) return CARD_RESULT_NOCARD;
    ensure_save_dir();
    char path[2048];
    snprintf(path, sizeof(path), "%s/%s.gci", save_dir(), fileName);
    FILE* f = fopen(path, "rb");
    if (!f) return CARD_RESULT_NOFILE;
    fclose(f);

    memset(fileInfo, 0, sizeof(*fileInfo));
    fileInfo->chan = chan;
    { std::lock_guard<std::mutex> lk(s_file_map_lock);
      fileInfo->fileNo = s_next_fileno++;
      s_file_paths[fileInfo->fileNo] = path; }
    return CARD_RESULT_READY;
}

s32 CARDFastOpen(s32 chan, s32 fileNo, CARDFileInfo* fileInfo) {
    if (chan != 0 || !fileInfo) return CARD_RESULT_NOCARD;
    { std::lock_guard<std::mutex> lk(s_file_map_lock);
      if (s_file_paths.find(fileNo) == s_file_paths.end()) return CARD_RESULT_NOFILE; }
    memset(fileInfo, 0, sizeof(*fileInfo));
    fileInfo->chan   = chan;
    fileInfo->fileNo = fileNo;
    return CARD_RESULT_READY;
}

s32 CARDClose(CARDFileInfo* fileInfo) {
    if (!fileInfo) return CARD_RESULT_READY;
    std::lock_guard<std::mutex> lk(s_file_map_lock);
    s_file_paths.erase(fileInfo->fileNo);
    return CARD_RESULT_READY;
}

static std::string get_path(s32 fileNo) {
    std::lock_guard<std::mutex> lk(s_file_map_lock);
    auto it = s_file_paths.find(fileNo);
    return it != s_file_paths.end() ? it->second : std::string{};
}

s32 CARDRead(CARDFileInfo* fileInfo, void* addr, s32 length, s32 offset) {
    if (!fileInfo || !addr) return CARD_RESULT_BROKEN;
    std::string path = get_path(fileInfo->fileNo);
    if (path.empty()) return CARD_RESULT_NOFILE;
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) return CARD_RESULT_NOFILE;
    fseek(f, offset, SEEK_SET);
    s32 r = (s32)fread(addr, 1, (size_t)length, f);
    fclose(f);
    return r == length ? CARD_RESULT_READY : CARD_RESULT_BROKEN;
}

s32 CARDWrite(CARDFileInfo* fileInfo, const void* addr, s32 length, s32 offset) {
    if (!fileInfo || !addr) return CARD_RESULT_BROKEN;
    std::string path = get_path(fileInfo->fileNo);
    if (path.empty()) return CARD_RESULT_NOFILE;
    FILE* f = fopen(path.c_str(), "r+b");
    if (!f) f = fopen(path.c_str(), "wb");
    if (!f) return CARD_RESULT_BROKEN;
    fseek(f, offset, SEEK_SET);
    s32 r = (s32)fwrite(addr, 1, (size_t)length, f);
    fclose(f);
    return r == length ? CARD_RESULT_READY : CARD_RESULT_BROKEN;
}

s32 CARDReadAsync(CARDFileInfo* fi, void* addr, s32 len, s32 off, CARDCallback cb) {
    s32 r = CARDRead(fi, addr, len, off);
    if (cb) cb(fi->chan, r);
    return r;
}

s32 CARDWriteAsync(CARDFileInfo* fi, const void* addr, s32 len, s32 off, CARDCallback cb) {
    s32 r = CARDWrite(fi, addr, len, off);
    if (cb) cb(fi->chan, r);
    return r;
}

s32 CARDCreate(s32 chan, const char* fileName, u32 size, CARDFileInfo* fileInfo) {
    if (chan != 0 || !fileInfo) return CARD_RESULT_NOCARD;
    ensure_save_dir();
    char path[2048];
    snprintf(path, sizeof(path), "%s/%s.gci", save_dir(), fileName);
    FILE* f = fopen(path, "wb");
    if (!f) return CARD_RESULT_BROKEN;
    if (size > 0) {
        if (fseek(f, (long)size - 1, SEEK_SET) != 0) {
            fclose(f);
            return CARD_RESULT_BROKEN;
        }
        fputc(0, f);
    }
    fclose(f);
    return CARDOpen(chan, fileName, fileInfo);
}

s32 CARDCreateAsync(s32 chan, const char* fn, u32 size, CARDFileInfo* fi, CARDCallback cb) {
    s32 r = CARDCreate(chan, fn, size, fi);
    if (cb) cb(chan, r);
    return r;
}

s32 CARDDelete(s32 chan, const char* fileName) {
    if (chan != 0) return CARD_RESULT_NOCARD;
    char path[2048];
    snprintf(path, sizeof(path), "%s/%s.gci", save_dir(), fileName);
    return (remove(path) == 0) ? CARD_RESULT_READY : CARD_RESULT_NOFILE;
}

s32 CARDDeleteAsync(s32 c, const char* fn, CARDCallback cb) {
    s32 r = CARDDelete(c, fn);
    if (cb) cb(c, r);
    return r;
}

s32 CARDFastDelete(s32 c, s32 fileNo) {
    std::string path;
    { std::lock_guard<std::mutex> lk(s_file_map_lock);
      auto it = s_file_paths.find(fileNo);
      if (it == s_file_paths.end()) return CARD_RESULT_NOFILE;
      path = it->second; }
    return (remove(path.c_str()) == 0) ? CARD_RESULT_READY : CARD_RESULT_NOFILE;
}

s32 CARDFastDeleteAsync(s32 c, s32 fn, CARDCallback cb) {
    s32 r = CARDFastDelete(c, fn);
    if (cb) cb(c, r);
    return r;
}

s32 CARDGetStatus(s32 chan, s32 fileNo, CARDStat* cardStat) {
    if (chan != 0 || !cardStat) return CARD_RESULT_NOCARD;
    std::string path = get_path(fileNo);
    if (path.empty()) return CARD_RESULT_NOFILE;

    struct stat st;
    if (stat(path.c_str(), &st) != 0) return CARD_RESULT_NOFILE;

    memset(cardStat, 0, sizeof(*cardStat));
    cardStat->length = (u32)st.st_size;
    const char* base = strrchr(path.c_str(), '/');
    base = base ? base + 1 : path.c_str();
    size_t len = strlen(base);
    if (len > 4 && strcmp(base + len - 4, ".gci") == 0) len -= 4;
    if (len >= CARD_FILENAME_MAX) len = CARD_FILENAME_MAX - 1;
    memcpy(cardStat->fileName, base, len);
    cardStat->fileName[len] = '\0';
    return CARD_RESULT_READY;
}
s32 CARDSetStatus(s32 chan, s32 fileNo, CARDStat* stat) {
    (void)chan; (void)fileNo; (void)stat; return CARD_RESULT_READY;
}
s32 CARDSetStatusAsync(s32 c, s32 fn, CARDStat* s, CARDCallback cb) {
    s32 r = CARDSetStatus(c, fn, s); if (cb) cb(c, r); return r;
}
s32 CARDFreeBlocks(s32 chan, s32* byteNotUsed, s32* filesNotUsed) {
    (void)chan;
    if (byteNotUsed)  *byteNotUsed  = 0x40000;
    if (filesNotUsed) *filesNotUsed = 127;
    return CARD_RESULT_READY;
}

s32 CARDFormat(s32 chan)             { (void)chan; return CARD_RESULT_READY; }
s32 CARDFormatAsync(s32 c, CARDCallback cb) {
    if (cb) cb(c, CARD_RESULT_READY); return CARD_RESULT_READY;
}
s32 CARDCheck(s32 chan)              { return (chan == 0) ? CARD_RESULT_READY : CARD_RESULT_NOCARD; }
s32 CARDCheckAsync(s32 c, CARDCallback cb) {
    s32 r = CARDCheck(c); if (cb) cb(c, r); return r;
}
s32 CARDCheckEx(s32 c, s32* x)      { (void)x; return CARDCheck(c); }
s32 CARDCheckExAsync(s32 c, s32* x, CARDCallback cb) {
    s32 r = CARDCheckEx(c, x); if (cb) cb(c, r); return r;
}
s32 CARDGetResultCode(s32 chan)      { (void)chan; return CARD_RESULT_READY; }
s32 CARDGetXferredBytes(s32 chan)    { (void)chan; return 0; }
s32 CARDGetMemSize(s32 c, u16* sz)  { if (sz) *sz = 0x800; (void)c; return CARD_RESULT_READY; }
s32 CARDGetSectorSize(s32 c, u32* s){ if (s) *s = 0x2000; (void)c; return CARD_RESULT_READY; }
s32 CARDGetSerialNo(s32 c, u64* sn) { if (sn) *sn = 0; (void)c; return CARD_RESULT_READY; }
s32 CARDGetEncoding(s32 c, u16* e)  { if (e) *e = CARD_ENCODE_ANSI; (void)c; return CARD_RESULT_READY; }
s32 CARDGetAttributes(s32 c, s32 fn, u8* attr) { (void)c; (void)fn; if (attr) *attr=0; return CARD_RESULT_READY; }
s32 CARDSetAttributes(s32 c, s32 fn, u8 a)  { (void)c; (void)fn; (void)a; return CARD_RESULT_READY; }
s32 CARDSetAttributesAsync(s32 c, s32 fn, u8 a, CARDCallback cb) {
    s32 r = CARDSetAttributes(c, fn, a); if (cb) cb(c, r); return r;
}
s32 CARDRename(s32 c, const char* o, const char* n) {
    if (c != 0 || !o || !n) return CARD_RESULT_NOCARD;
    ensure_save_dir();
    char old_path[2048];
    char new_path[2048];
    snprintf(old_path, sizeof(old_path), "%s/%s.gci", save_dir(), o);
    snprintf(new_path, sizeof(new_path), "%s/%s.gci", save_dir(), n);
    if (rename(old_path, new_path) != 0) return CARD_RESULT_NOFILE;

    std::lock_guard<std::mutex> lk(s_file_map_lock);
    for (auto& it : s_file_paths) {
        if (it.second == old_path) {
            it.second = new_path;
        }
    }
    return CARD_RESULT_READY;
}
s32 CARDRenameAsync(s32 c, const char* o, const char* n, CARDCallback cb) {
    s32 r = CARDRename(c, o, n); if (cb) cb(c, r); return r;
}
s32 CARDCancel(CARDFileInfo* fi)    { (void)fi; return CARD_RESULT_READY; }
s32 CARDGetCurrentMode(s32 c, u32* m){ (void)c; if (m) *m = 0; return CARD_RESULT_READY; }

BOOL CARDGetFastMode(void)          { return FALSE; }
BOOL CARDSetFastMode(BOOL enable)   { (void)enable; return FALSE; }

} /* extern "C" */
