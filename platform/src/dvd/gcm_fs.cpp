/* GCM / ISO virtual filesystem.
 * Stage 1: structure and stubs.  Stage 5: full FST parser + pread. */
#include "platform/platform.h"
#include "gcm_fs.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "platform/endian.h"

/* GCM disc image layout:
 *   0x000: disc header (0x440 bytes)
 *     0x420: boot info (DVDBB2) — FSTPosition, FSTLength, etc.
 *   FST: array of entries, each 12 bytes
 *     entry[0] is root dir: nameOffset[1]=0, parent[4]=0, siblingOrFileCount[4]=total
 *     file entry:  [0]=0x00, [1..3]=nameOfs(24-bit), [4..7]=fileOffset, [8..11]=fileLength
 *     dir  entry:  [0]=0x01, [1..3]=nameOfs(24-bit), [4..7]=parentIdx,  [8..11]=nextIdx
 *   String table: immediately after FST entries
 */

#define GCM_BOOT_HDR_OFFSET  0x420
#define GCM_DISKID_OFFSET    0x000
#define FST_ENTRY_SIZE       12

struct FSTEntry {
    uint8_t  flags;          /* 0=file, 1=dir */
    uint32_t nameOffset;     /* 24-bit, relative to string table start */
    uint32_t fileOffOrParent;
    uint32_t lengthOrNext;
};

struct GcmFS {
    int      fd;
    uint32_t fstOffset;
    uint32_t fstLength;
    uint32_t entryCount;
    uint8_t* fstData;        /* entire FST in memory */
    const char* stringTable; /* pointer into fstData */
    std::vector<FSTEntry> entries;
    std::vector<std::string> paths;
};

static GcmFS s_fs = { -1, 0, 0, 0, nullptr, nullptr };

static void gcm_fs_clear_state(void) {
    if (s_fs.fd >= 0) {
        close(s_fs.fd);
    }
    if (s_fs.fstData) {
        free(s_fs.fstData);
    }
    s_fs.fd = -1;
    s_fs.fstOffset = 0;
    s_fs.fstLength = 0;
    s_fs.entryCount = 0;
    s_fs.fstData = nullptr;
    s_fs.stringTable = nullptr;
    s_fs.entries.clear();
    s_fs.paths.clear();
}

static std::string normalize_lookup_path(const char* path) {
    if (!path || !path[0]) return std::string("/");
    std::string p(path);
    if (p[0] != '/') p.insert(0, "/");
    while (p.size() > 1 && p.back() == '/') p.pop_back();
    return p;
}

static const char* safe_entry_name(const FSTEntry& e) {
    if (!s_fs.stringTable || e.nameOffset >= s_fs.fstLength) return "";
    return s_fs.stringTable + e.nameOffset;
}

static void build_paths_for_dir(uint32_t dir_index, const std::string& parent_path) {
    if (dir_index >= s_fs.entries.size()) return;
    const FSTEntry& dir = s_fs.entries[dir_index];
    if (dir.flags == 0) return;

    uint32_t i = dir_index + 1;
    while (i < dir.lengthOrNext && i < s_fs.entryCount) {
        const FSTEntry& e = s_fs.entries[i];
        const char* name = safe_entry_name(e);
        std::string base = parent_path.empty() ? std::string("/") : parent_path;
        std::string full = base;
        if (full.size() > 1) full += "/";
        full += name;
        s_fs.paths[i] = full;

        if (e.flags != 0) {
            build_paths_for_dir(i, full);
            i = e.lengthOrNext;
        } else {
            i++;
        }
    }
}

static void parse_fst_entry(const uint8_t* raw, FSTEntry* e) {
    e->flags          = raw[0];
    e->nameOffset     = ((uint32_t)raw[1] << 16) | ((uint32_t)raw[2] << 8) | raw[3];
    e->fileOffOrParent = read_be32(raw + 4);
    e->lengthOrNext    = read_be32(raw + 8);
}

bool gcm_fs_open(const char* iso_path) {
    gcm_fs_clear_state();

    s_fs.fd = open(iso_path, O_RDONLY);
    if (s_fs.fd < 0) {
        fprintf(stderr, "[DVD] Cannot open disc image: %s\n", iso_path);
        return false;
    }
    /* Read boot info block */
    uint8_t boot[32];
    if (pread(s_fs.fd, boot, 32, GCM_BOOT_HDR_OFFSET) < 32) {
        fprintf(stderr, "[DVD] Cannot read boot header\n");
        gcm_fs_clear_state();
        return false;
    }
    s_fs.fstOffset  = read_be32(boot + 4);
    s_fs.fstLength  = read_be32(boot + 8);
    if (!s_fs.fstOffset || !s_fs.fstLength) {
        fprintf(stderr, "[DVD] Bad FST offset/length\n");
        gcm_fs_clear_state();
        return false;
    }
    s_fs.fstData = (uint8_t*)malloc(s_fs.fstLength);
    if (!s_fs.fstData) {
        gcm_fs_clear_state();
        return false;
    }
    if ((size_t)pread(s_fs.fd, s_fs.fstData, s_fs.fstLength, s_fs.fstOffset)
            < s_fs.fstLength) {
        fprintf(stderr, "[DVD] Cannot read FST\n");
        gcm_fs_clear_state();
        return false;
    }
    /* Root entry count is in the 'lengthOrNext' of entry 0 */
    FSTEntry root;
    parse_fst_entry(s_fs.fstData, &root);
    s_fs.entryCount  = root.lengthOrNext;
    s_fs.stringTable = (const char*)(s_fs.fstData + s_fs.entryCount * FST_ENTRY_SIZE);
    if (s_fs.entryCount == 0 || (s_fs.entryCount * FST_ENTRY_SIZE) > s_fs.fstLength) {
        fprintf(stderr, "[DVD] Invalid FST entry count: %u\n", s_fs.entryCount);
        gcm_fs_clear_state();
        return false;
    }

    s_fs.entries.resize(s_fs.entryCount);
    s_fs.paths.assign(s_fs.entryCount, std::string());
    s_fs.paths[0] = "/";
    for (uint32_t i = 0; i < s_fs.entryCount; i++) {
        parse_fst_entry(s_fs.fstData + i * FST_ENTRY_SIZE, &s_fs.entries[i]);
    }
    build_paths_for_dir(0, "");

    fprintf(stderr, "[DVD] FST loaded: %u entries\n", s_fs.entryCount);
    return true;
}

void gcm_fs_close(void) {
    gcm_fs_clear_state();
}

/* Resolve a path like "/root/subdir/file.arc" → file offset + length */
bool gcm_fs_lookup(const char* path, uint32_t* out_offset, uint32_t* out_length) {
    if (!s_fs.fstData || s_fs.paths.empty()) return false;
    std::string want = normalize_lookup_path(path);

    for (uint32_t i = 1; i < s_fs.entryCount; i++) {
        const FSTEntry& e = s_fs.entries[i];
        if (e.flags == 0 && s_fs.paths[i] == want) {
            if (out_offset) *out_offset = e.fileOffOrParent;
            if (out_length) *out_length = e.lengthOrNext;
            return true;
        }
    }
    return false;
}

int gcm_fs_path_to_entry(const char* path) {
    if (!s_fs.fstData || s_fs.paths.empty()) return -1;
    std::string want = normalize_lookup_path(path);
    for (uint32_t i = 0; i < s_fs.entryCount; i++) {
        if (s_fs.paths[i] == want) {
            return (int)i;
        }
    }
    return -1;
}

bool gcm_fs_lookup_entry(int entry_num, bool* out_is_dir, uint32_t* out_offset, uint32_t* out_length) {
    if (entry_num < 0 || (uint32_t)entry_num >= s_fs.entryCount) return false;
    const FSTEntry& e = s_fs.entries[(uint32_t)entry_num];
    if (out_is_dir) *out_is_dir = (e.flags != 0);
    if (e.flags == 0) {
        if (out_offset) *out_offset = e.fileOffOrParent;
        if (out_length) *out_length = e.lengthOrNext;
    } else {
        if (out_offset) *out_offset = 0;
        if (out_length) *out_length = 0;
    }
    return true;
}

void* gcm_fs_get_fst_location(void) {
    return s_fs.fstData;
}

bool gcm_fs_read(uint32_t disc_offset, void* buf, uint32_t length) {
    if (s_fs.fd < 0) return false;
    ssize_t r = pread(s_fs.fd, buf, length, (off_t)disc_offset);
    return r == (ssize_t)length;
}

int gcm_fs_get_fd(void)  { return s_fs.fd; }
bool gcm_fs_is_open(void) { return s_fs.fd >= 0; }
