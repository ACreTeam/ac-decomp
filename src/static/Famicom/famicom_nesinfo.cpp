#include "Famicom/famicom.h"

#include "_mem.h"
#include "dolphin/os.h"

static u8 highscore_num = 0;
static u8 highscore_updated = 0;
static u8* highscore_flags = nullptr;
static u8 nesinfo_mcrd_cont_no = 0;
static u8* nesinfo_mcrd_game_name = nullptr;
static u8* nesinfo_ptr = nullptr;
static u32 nesinfo_tags_size = 0;
static u8* nesinfo_tags_start = nullptr;
static u8* nesinfo_tags_end = nullptr;
static char* nesinfo_tags_gameName = nullptr;
static char* nesinfo_tags_kanjiName = nullptr;
static u8* nesinfo_tags_moriName = nullptr;
static u32 nesinfo_data_size = 0;
static u8* nesinfo_data_start = nullptr;
static u8* nesinfo_data_end = nullptr;
static u32 nesinfo_rom_size = 0;
static u8* nesinfo_rom_start = nullptr;
static u8* nesinfo_rom_end = nullptr;
static u32 nesinfo_expand_rom_size = 0;
static bool tcs_bad = false;
static bool ics_bad = false;

enum highscore_state { HIGHSCORE_STATE_UNSET, HIGHSCORE_STATE_SET, HIGHSCORE_STATE_2, HIGHSCORE_STATE_UNINITIALIZED };

enum famicom_games {
    FAMICOM_GAME_CLU_CLU_LAND,
    FAMICOM_GAME_BALLOON_FIGHT,
    FAMICOM_GAME_DONKEY_KONG,
    FAMICOM_GAME_DONKEY_KONG_JR_MATH,
    FAMICOM_GAME_PINBALL,

};

#define END_TAG()  'E', 'N', 'D', 0
#define GID_TAG(l) 'G', 'I', 'D', (l)
#define GNM_TAG(l) 'G', 'N', 'M', (l)
#define GNO_TAG()  'G', 'N', 'O', sizeof(u8)
#define OFS_TAG()  'O', 'F', 'S', sizeof(u16)
#define HSC_TAG(l) 'H', 'S', 'C', (sizeof(u16) + l)

#define OFS_U16(ofs) ((u8)((u32)(ofs) >> 8), (u8)(ofs))

static u8 tags_table_default[] = { END_TAG() };

// clang-format off
static u8 tags_table_cluclu_land[] = {
    GID_TAG(2), 'C', 'L',
    GNM_TAG(12), 'C', 'L', 'U', ' ', 'C', 'L', 'U', ' ', 'L', 'A', 'N', 'D',
    GNO_TAG(), FAMICOM_GAME_CLU_CLU_LAND,
    OFS_TAG(), OFS_U16(0x0000),
    HSC_TAG(4), OFS_U16(0x8020), 0, 0, 0, 0,
    END_TAG(),
};

static u8 tags_table_balloon_fight[] = {
    GID_TAG(2), 'B', 'F',
    GNM_TAG(13), 'B', 'A', 'L', 'L', 'O', 'O', 'N', ' ', 'F', 'I', 'G', 'H', 'T',
    GNO_TAG(), FAMICOM_GAME_BALLOON_FIGHT,
    OFS_TAG(), OFS_U16(0x0004),
    HSC_TAG(5), OFS_U16(0x0629), 0, 0, 0, 1, 0,
    HSC_TAG(5), OFS_U16(0x062E), 0, 0, 0, 1, 0,
    HSC_TAG(5), OFS_U16(0x0633), 0, 0, 5, 2, 0,
    END_TAG(),
};

static u8 tags_table_donkey_kong[] = {
    GID_TAG(2), 'D', 'K',
    GNM_TAG(11), 'D', 'O', 'N', 'K', 'E', 'Y', ' ', 'K', 'O', 'N', 'G',
    GNO_TAG(), FAMICOM_GAME_DONKEY_KONG,
    OFS_TAG(), OFS_U16(0x0013),
    HSC_TAG(2), OFS_U16(0x0507), 0, 0,
    HSC_TAG(2), OFS_U16(0x0509), 0, 0,
    END_TAG(),
};

static u8 tags_table_sansu_asobi[] = {
    GID_TAG(2), 'C', 'A',
    GNM_TAG(13), 'D', 'O', 'N', 'K', 'Y', ' ', 'J', 'R', ' ', 'M', 'A', 'T', 'H',
    GNO_TAG(), FAMICOM_GAME_DONKEY_KONG_JR_MATH,
    OFS_TAG(), OFS_U16(0x0017),
    HSC_TAG(2), OFS_U16(0x04D7), 0, 0,
    HSC_TAG(2), OFS_U16(0x04D9), 0, 0,
    HSC_TAG(2), OFS_U16(0x04DB), 0, 0,
    HSC_TAG(2), OFS_U16(0x04DD), 0, 0,
    HSC_TAG(2), OFS_U16(0x04DF), 0, 0,
    HSC_TAG(2), OFS_U16(0x04E1), 0, 0,
    HSC_TAG(2), OFS_U16(0x04E3), 0, 0,
    HSC_TAG(2), OFS_U16(0x04E5), 0, 0,
    HSC_TAG(2), OFS_U16(0x04E7), 0, 0,
    END_TAG(),
};

static u8 tags_table_pinball[] = {
    GID_TAG(2), 'P', 'N',
    GNM_TAG(7), 'P', 'I', 'N', 'B', 'A', 'L', 'L',
    GNO_TAG(), FAMICOM_GAME_PINBALL,
    OFS_TAG(), OFS_U16(0x0029),
    HSC_TAG(2), OFS_U16(0x0507), 0, 0,
    HSC_TAG(2), OFS_U16(0x0509), 0, 0,
    END_TAG(),
};

typedef struct nesinfo_tag_s {
    u8* tags_table;
    size_t tags_size;
    char* gameName;
    char* kanjiName;
} nesinfo_tag_info;

static nesinfo_tag_info tags_table_table[FAMICOM_INTERNAL_ROM_NUM];

// clang-format on

static u8 moriNameTable[FAMICOM_INTERNAL_ROM_NUM][16] = {
    // TODO
};

static void update_highscore_raw(u32 ofs, u32 size, u8* initial_value, u8* high_score, u8* state) {
    u8* current_score_p = &famicomCommon.sp->wram[ofs];

    if (*state == HIGHSCORE_STATE_UNINITIALIZED) {
        memcpy(high_score, initial_value, size);
        *state = HIGHSCORE_STATE_UNSET; // default highscore
        // High score data was not found, so it has been initialized.
        OSReport("ハイスコアデータがないので初期化しました\n");
    }

    if (*state == HIGHSCORE_STATE_UNSET) {
        if (memcmp(current_score_p, initial_value, size) == 0) {
            // The high score in WRAM has been reset to its default value.
            OSReport("WRAMのハイスコアが初期値になりました\n");
            memcpy(current_score_p, high_score, size);
            *state = HIGHSCORE_STATE_SET;
        } else {
            // The high score in WRAM has not been reset to its default value. Offset=%04x\n
            OSReport("WRAMのハイスコアが初期値になっていません オフセット=%04x\n", ofs);
        }
    } else {
        if (memcmp(current_score_p, high_score, size) != 0) {
            // The high score in WRAM has been updated.
            OSReport("WRAMのハイスコアが更新されました\n");
            memcpy(high_score, current_score_p, size);
            highscore_updated = true;
        }
    }
}

static u16 nesinfo_get_u16(u8* data) {
    return (u16)(((u32)data[0] << 8) + (u32)data[1]);
}

static u8 nesinfo_get_u8(u8* data) {
    return (u8)(u32)data[0];
}

static void nesinfo_set_u16(u8* data, u16* value) {
    data[0] = (u8)(((u32)value >> 8) & 0xFF);
    data[1] = (u8)((u32)value & 0xFF);
}

static u8* nesinfo_next_tag_raw(u8* data) {
    if (data == nullptr || (nesinfo_tags_end != nullptr && data >= nesinfo_tags_end) ||
        memcmp(data, NESTAG_END, NESTAG_CMD_SIZE) == 0) {
        return nullptr;
    } else {
        return &data[data[NESTAG_CMD_SIZE] + NESTAG_SIZE];
    }
}

static u8* nesinfo_next_tag(u8* data) {
    do {
        data = nesinfo_next_tag_raw(data);
        if (data == nullptr) {
            break;
        }

        if (memcmp(data, NESTAG_VEQ, NESTAG_CMD_SIZE) == 0) {
            if (data[NESTAG_SIZE + 1] != 1) {
                data = nesinfo_next_tag_raw(data);
            }
        } else if (memcmp(data, NESTAG_VNE, NESTAG_CMD_SIZE) == 0) {
            if (data[NESTAG_SIZE + 1] == 1) {
                data = nesinfo_next_tag_raw(data);
            }
        } else {
            break; // found a tag to return
        }
    } while (data != nullptr);

    return data;
}

static u16 calc_check_sum2(void* data, size_t size) {
    if (((u32)data & 1) == 0) {
        u16 sum;
        size_t i;
        u16* data2;

        data2 = (u16*)data;
        sum = 0;
        for (i = 0; i < size; i += 2) {
            sum += *data2++;
        }

        return sum;
    } else {
        u16 sum0;
        u16 sum1;
        size_t i;
        u8* data_u8;

        data_u8 = (u8*)data;
        sum0 = 0;
        sum1 = 0;
        for (i = 0; i < size - 1; i += sizeof(u16)) {
            sum0 += data_u8[0];
            sum1 += data_u8[1];
            data_u8 += sizeof(u16);
        }

        if (i < size) {
            sum0 += data_u8[0];
            data_u8 += sizeof(u8);
        }

        return (u16)((sum0 << 8) + sum1);
    }
}

static void print_stringn_lf(u8* data, size_t size) {
    while (size-- > 0) {
        OSReport("%c", *data++);
    }

    OSReport("\n");
}

static void print_hex_lf(u8* data, size_t size) {
    while (size-- > 0) {
        OSReport(" %02x", *data++);
    }

    OSReport("\n");
}

extern void nesinfo_tags_set(int rom_no) {
    nesinfo_tags_start = nullptr;
    nesinfo_tags_end = nullptr;
    nesinfo_tags_size = 0;
    nesinfo_tags_gameName = nullptr;
    nesinfo_tags_kanjiName = nullptr;
    nesinfo_tags_moriName = nullptr;

    if (rom_no < 0) {
        return;
    }

    if (rom_no < 0 || rom_no >= FAMICOM_INTERNAL_ROM_NUM) {
        return;
    }

    nesinfo_tags_start = tags_table_table[rom_no].tags_table;
    nesinfo_tags_end = nesinfo_tags_start + tags_table_table[rom_no].tags_size;
    nesinfo_tags_size = (u32)(nesinfo_tags_end - nesinfo_tags_start);
    nesinfo_tags_gameName = tags_table_table[rom_no].gameName;
    nesinfo_tags_kanjiName = tags_table_table[rom_no].kanjiName;

    if (rom_no < FAMICOM_INTERNAL_ROM_NUM) {
        nesinfo_tags_moriName = moriNameTable[rom_no];
    }
}
