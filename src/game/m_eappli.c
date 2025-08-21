#include "m_eappli.h"

#include "m_common_data.h"
#include "m_private.h"
#include "lb_rtc.h"
#include "m_scene_table.h"
#include "m_malloc.h"
#include "jsyswrap.h"

#define CRC32_POLYNOMIAL 0xEDB88320
#define CRC32_START_VALUE 0xAA478422

static u32 crcTable[256];

static u32 getcrc(u8* data, size_t len) {
    u32 crc = CRC32_START_VALUE;
    size_t i = 0;

    do {
        crc = (crc >> 8) ^ crcTable[(crc ^ data[i]) & 0xFF];
        i++;
    } while (i != len);

    return crc;
}

static void crcgen() {
    u32 c;
    int i;
    int j;

    for (i = 0; i < 256; i++) {
        c = i;

        for (j = 0; j < 8; j++) {
            c = (c & 1) ? ((c >> 1) ^ CRC32_POLYNOMIAL) : (c >> 1);
        }

        crcTable[i] = c;
    }
}

static u32 mEA_GetCRC(u8* data, size_t len) {
    crcgen();
    return getcrc(data, len);
}

static void putLEWord(u8* dst, u32 word) {
    dst[0] = word >> 0;
    dst[1] = word >> 8;
    dst[2] = word >> 16;
    dst[3] = word >> 24;
}

extern void mEA_InitLetterCardE() {
    mPr_carde_data_c* carde_data = &Common_Get(now_private)->ecard_letter_data;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    /* only reset if current date isn't same as last scan date */
    u16 year = carde_data->letter_send_date.year;
    u8 month = carde_data->letter_send_date.month;
    u8 day = carde_data->letter_send_date.day;
    if (rtc_time->year != year || rtc_time->month != month || rtc_time->day != day) {
        int i;
        for (i = 0; i < mPr_ECARD_LETTER_NUM; i++) {
            carde_data->card_letters_sent[i] = 0;
        }
    }
}

extern int mEA_CheckLetterCardE(int card_no) {
    mPr_carde_data_c* card_data = &Common_Get(now_private)->ecard_letter_data;
    int index = card_no < mPr_ECARD_NUM ? card_no : mPr_ECARD_NUM - 1;

    if (index == mPr_ECARD_NUM - 1) {
        return ((card_data->card_letters_sent[index >> 3] >> (index & 7)) & 1) ? 2 : 0;
    }

    return (card_data->card_letters_sent[index >> 3] >> (index & 7)) & 1;
}

extern void mEA_SetLetterCardE(int card_no) {
    mPr_carde_data_c* card_data = &Common_Get(now_private)->ecard_letter_data;
    int index = card_no < mPr_ECARD_NUM ? card_no : mPr_ECARD_NUM - 1;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    card_data->card_letters_sent[index >> 3] |= 1 << (index & 7);
    card_data->letter_send_date.year = rtc_time->year;
    card_data->letter_send_date.month = rtc_time->month;
    card_data->letter_send_date.day = rtc_time->day;
}

#define MY_ORIGINAL_DESIGN_DATA_SIZE (4 * (32 / 2) * 32)
extern void mEA_GetCardDLProgram() {
    if (Save_Get(scene_no) != SCENE_TITLE_DEMO && Common_Get(carde_program_p) == NULL) {
        u32 crc;

        Common_Set(carde_program_size, JW_GetResSizeFileNo(RESOURCE_MY_ORIGINAL) -
                                           MY_ORIGINAL_DESIGN_DATA_SIZE); // my_original.bin also contains texture data
        Common_Set(carde_program_p, (u8*)zelda_malloc_align(Common_Get(carde_program_size), 32));
        _JW_GetResourceAram(JW_GetAramAddress(RESOURCE_MY_ORIGINAL) + MY_ORIGINAL_DESIGN_DATA_SIZE,
                            Common_Get(carde_program_p), Common_Get(carde_program_size));

        /* write compressed program size to vpk payload */
        putLEWord(Common_Get(carde_program_p) + 0x2C, Common_Get(carde_program_size) - 0x34);

        /* write vpk CRC32 */
        crc = mEA_GetCRC(Common_Get(carde_program_p) + sizeof(u32), Common_Get(carde_program_size) - sizeof(u32));
        putLEWord(Common_Get(carde_program_p), crc);
    }
}

extern void mEA_CleanCardDLProgram() {
    if (Common_Get(carde_program_p) != NULL) {
        zelda_free(Common_Get(carde_program_p));
        Common_Set(carde_program_p, NULL);
        Common_Set(carde_program_size, 0);
    }
}

extern u8* mEA_dl_carde_program_p() {
    return Common_Get(carde_program_p);
}

extern size_t mEA_dl_carde_program_size() {
    return Common_Get(carde_program_size);
}
