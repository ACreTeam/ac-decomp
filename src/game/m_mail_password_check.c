#include "m_mail_password_check.h"

#include "m_font.h"
#include "m_room_type.h"
#include "m_name_table.h"
#include "m_private.h"
#include "m_npc.h"
#include "m_shop.h"
#include "_mem.h"
#include "m_common_data.h"
#include "libultra/libultra.h"

static u8 usable_to_fontnum[64] = {
    CHAR_b,   CHAR_K,       CHAR_z, CHAR_FIVE, CHAR_c,       CHAR_q, CHAR_Y,     CHAR_Z,     CHAR_O,     CHAR_d,
    CHAR_t,   CHAR_SIX,     CHAR_n, CHAR_l,    CHAR_B,       CHAR_y, CHAR_o,     CHAR_EIGHT, CHAR_FOUR,  CHAR_L,
    CHAR_k,   CHAR_PERCENT, CHAR_A, CHAR_Q,    CHAR_m,       CHAR_D, CHAR_P,     CHAR_I,     CHAR_SEVEN, CHAR_AMPERSAND,
    CHAR_R,   CHAR_s,       CHAR_w, CHAR_U,    CHAR_HASHTAG, CHAR_r, CHAR_THREE, CHAR_E,     CHAR_x,     CHAR_M,
    CHAR_C,   CHAR_AT_SIGN, CHAR_e, CHAR_NINE, CHAR_g,       CHAR_v, CHAR_V,     CHAR_G,     CHAR_u,     CHAR_N,
    CHAR_i,   CHAR_X,       CHAR_W, CHAR_f,    CHAR_T,       CHAR_J, CHAR_F,     CHAR_S,     CHAR_H,     CHAR_p,
    CHAR_TWO, CHAR_a,       CHAR_j, CHAR_h,
};

static int mMpswd_prime_number[256] = {
    17,   19,   23,   29,   31,   37,   41,   43,   47,   53,   59,   61,   67,   71,   73,   79,   83,   89,   97,
    101,  103,  107,  109,  113,  127,  131,  137,  139,  149,  151,  157,  163,  167,  173,  179,  181,  191,  193,
    197,  199,  211,  223,  227,  229,  233,  239,  241,  251,  257,  263,  269,  271,  277,  281,  283,  293,  307,
    311,  313,  317,  331,  337,  347,  349,  353,  359,  367,  373,  379,  383,  389,  397,  401,  409,  419,  421,
    431,  433,  439,  443,  449,  457,  461,  463,  467,  479,  487,  491,  499,  503,  509,  521,  523,  541,  547,
    557,  563,  569,  571,  577,  587,  593,  599,  601,  607,  613,  617,  619,  631,  641,  643,  647,  653,  659,
    661,  673,  677,  683,  691,  701,  709,  719,  727,  733,  739,  743,  751,  757,  761,  769,  773,  787,  797,
    809,  811,  821,  823,  827,  829,  839,  853,  857,  859,  863,  877,  881,  883,  887,  907,  911,  919,  929,
    937,  941,  947,  953,  967,  971,  977,  983,  991,  997,  1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051,
    1061, 1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193,
    1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297, 1301, 1303, 1307, 1319,
    1321, 1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481,
    1483, 1487, 1489, 1493, 1499, 1511, 1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 1601, 1607,
    1609, 1613, 1619, 1621, 1627, 1637, 1657, 1663, 1667,
};

static u8 mMpswd_transposition_cipher_char0_0[9] = "NiiMasaru";
static u8 mMpswd_transposition_cipher_char0_1[15] = "KomatsuKunihiro";
static u8 mMpswd_transposition_cipher_char0_2[14] = "TakakiGentarou";
static u8 mMpswd_transposition_cipher_char0_3[15] = "MiyakeHiromichi";
static u8 mMpswd_transposition_cipher_char0_4[13] = "HayakawaKenzo";
static u8 mMpswd_transposition_cipher_char0_5[18] = "KasamatsuShigehiro";
static u8 mMpswd_transposition_cipher_char0_6[17] = "SumiyoshiNobuhiro";
static u8 mMpswd_transposition_cipher_char0_7[12] = "NomaTakafumi";
static u8 mMpswd_transposition_cipher_char0_8[13] = "EguchiKatsuya";
static u8 mMpswd_transposition_cipher_char0_9[13] = "NogamiHisashi";
static u8 mMpswd_transposition_cipher_char0_10[8] = "IidaToki";
static u8 mMpswd_transposition_cipher_char0_11[13] = "IkegawaNoriko";
static u8 mMpswd_transposition_cipher_char0_12[14] = "KawaseTomohiro";
static u8 mMpswd_transposition_cipher_char0_13[9] = "BandoTaro";
static u8 mMpswd_transposition_cipher_char0_14[11] = "TotakaKazuo";
static u8 mMpswd_transposition_cipher_char0_15[13] = "WatanabeKunio";

static u8 mMpswd_transposition_cipher_char1_0[11] = "RichAmtower";
static u8 mMpswd_transposition_cipher_char1_1[10] = "KyleHudson";
static u8 mMpswd_transposition_cipher_char1_2[15] = "MichaelKelbaugh";
static u8 mMpswd_transposition_cipher_char1_3[14] = "RaycholeLAneff";
static u8 mMpswd_transposition_cipher_char1_4[10] = "LeslieSwan";
static u8 mMpswd_transposition_cipher_char1_5[16] = "YoshinobuMantani";
static u8 mMpswd_transposition_cipher_char1_6[12] = "KirkBuchanan";
static u8 mMpswd_transposition_cipher_char1_7[9] = "TimOLeary";
static u8 mMpswd_transposition_cipher_char1_8[10] = "BillTrinen";
static u8 mMpswd_transposition_cipher_char1_9[20] = "nAkAyOsInoNyuuSankin";
static u8 mMpswd_transposition_cipher_char1_10[20] = "zendamaKINAKUDAMAkin";
static u8 mMpswd_transposition_cipher_char1_11[19] = "OishikutetUYOKUNARU";
static u8 mMpswd_transposition_cipher_char1_12[13] = "AsetoAminofen";
static u8 mMpswd_transposition_cipher_char1_13[20] = "fcSFCn64GCgbCGBagbVB";
static u8 mMpswd_transposition_cipher_char1_14[11] = "YossyIsland";
static u8 mMpswd_transposition_cipher_char1_15[14] = "KedamonoNoMori";

typedef struct {
    u8* str;
    int len;
} mMpswd_transposition_cipher_str_c;

static mMpswd_transposition_cipher_str_c mMpswd_transposition_cipher_char0_table[16] = {
    { mMpswd_transposition_cipher_char0_0, sizeof(mMpswd_transposition_cipher_char0_0) },
    { mMpswd_transposition_cipher_char0_1, sizeof(mMpswd_transposition_cipher_char0_1) },
    { mMpswd_transposition_cipher_char0_2, sizeof(mMpswd_transposition_cipher_char0_2) },
    { mMpswd_transposition_cipher_char0_3, sizeof(mMpswd_transposition_cipher_char0_3) },
    { mMpswd_transposition_cipher_char0_4, sizeof(mMpswd_transposition_cipher_char0_4) },
    { mMpswd_transposition_cipher_char0_5, sizeof(mMpswd_transposition_cipher_char0_5) },
    { mMpswd_transposition_cipher_char0_6, sizeof(mMpswd_transposition_cipher_char0_6) },
    { mMpswd_transposition_cipher_char0_7, sizeof(mMpswd_transposition_cipher_char0_7) },
    { mMpswd_transposition_cipher_char0_8, sizeof(mMpswd_transposition_cipher_char0_8) },
    { mMpswd_transposition_cipher_char0_9, sizeof(mMpswd_transposition_cipher_char0_9) },
    { mMpswd_transposition_cipher_char0_10, sizeof(mMpswd_transposition_cipher_char0_10) },
    { mMpswd_transposition_cipher_char0_11, sizeof(mMpswd_transposition_cipher_char0_11) },
    { mMpswd_transposition_cipher_char0_12, sizeof(mMpswd_transposition_cipher_char0_12) },
    { mMpswd_transposition_cipher_char0_13, sizeof(mMpswd_transposition_cipher_char0_13) },
    { mMpswd_transposition_cipher_char0_14, sizeof(mMpswd_transposition_cipher_char0_14) },
    { mMpswd_transposition_cipher_char0_15, sizeof(mMpswd_transposition_cipher_char0_15) }
};

static mMpswd_transposition_cipher_str_c mMpswd_transposition_cipher_char1_table[16] = {
    { mMpswd_transposition_cipher_char1_0, sizeof(mMpswd_transposition_cipher_char1_0) },
    { mMpswd_transposition_cipher_char1_1, sizeof(mMpswd_transposition_cipher_char1_1) },
    { mMpswd_transposition_cipher_char1_2, sizeof(mMpswd_transposition_cipher_char1_2) },
    { mMpswd_transposition_cipher_char1_3, sizeof(mMpswd_transposition_cipher_char1_3) },
    { mMpswd_transposition_cipher_char1_4, sizeof(mMpswd_transposition_cipher_char1_4) },
    { mMpswd_transposition_cipher_char1_5, sizeof(mMpswd_transposition_cipher_char1_5) },
    { mMpswd_transposition_cipher_char1_6, sizeof(mMpswd_transposition_cipher_char1_6) },
    { mMpswd_transposition_cipher_char1_7, sizeof(mMpswd_transposition_cipher_char1_7) },
    { mMpswd_transposition_cipher_char1_8, sizeof(mMpswd_transposition_cipher_char1_8) },
    { mMpswd_transposition_cipher_char1_9, sizeof(mMpswd_transposition_cipher_char1_9) },
    { mMpswd_transposition_cipher_char1_10, sizeof(mMpswd_transposition_cipher_char1_10) },
    { mMpswd_transposition_cipher_char1_11, sizeof(mMpswd_transposition_cipher_char1_11) },
    { mMpswd_transposition_cipher_char1_12, sizeof(mMpswd_transposition_cipher_char1_12) },
    { mMpswd_transposition_cipher_char1_13, sizeof(mMpswd_transposition_cipher_char1_13) },
    { mMpswd_transposition_cipher_char1_14, sizeof(mMpswd_transposition_cipher_char1_14) },
    { mMpswd_transposition_cipher_char1_15, sizeof(mMpswd_transposition_cipher_char1_15) }
};

static mMpswd_transposition_cipher_str_c* mMpswd_transposition_cipher_char_table[2] = {
    mMpswd_transposition_cipher_char0_table, mMpswd_transposition_cipher_char1_table
};

static u8 mMpswd_chg_code_table[256] = {
    0xf0, 0x83, 0xfd, 0x62, 0x93, 0x49, 0x0d, 0x3e, 0xe1, 0xa4, 0x2b, 0xaf, 0x3a, 0x25, 0xd0, 0x82, 0x7f, 0x97, 0xd2,
    0x03, 0xb2, 0x32, 0xb4, 0xe6, 0x09, 0x42, 0x57, 0x27, 0x60, 0xea, 0x76, 0xab, 0x2d, 0x65, 0xa8, 0x4d, 0x8b, 0x95,
    0x01, 0x37, 0x59, 0x79, 0x33, 0xac, 0x2f, 0xae, 0x9f, 0xfe, 0x56, 0xd9, 0x04, 0xc6, 0xb9, 0x28, 0x06, 0x5c, 0x54,
    0x8d, 0xe5, 0x00, 0xb3, 0x7b, 0x5e, 0xa7, 0x3c, 0x78, 0xcb, 0x2e, 0x6d, 0xe4, 0xe8, 0xdc, 0x40, 0xa0, 0xde, 0x2c,
    0xf5, 0x1f, 0xcc, 0x85, 0x71, 0x3d, 0x26, 0x74, 0x9c, 0x13, 0x7d, 0x7e, 0x66, 0xf2, 0x9e, 0x02, 0xa1, 0x53, 0x15,
    0x4f, 0x51, 0x20, 0xd5, 0x39, 0x1a, 0x67, 0x99, 0x41, 0xc7, 0xc3, 0xa6, 0xc4, 0xbc, 0x38, 0x8c, 0xaa, 0x81, 0x12,
    0xdd, 0x17, 0xb7, 0xef, 0x2a, 0x80, 0x9d, 0x50, 0xdf, 0xcf, 0x89, 0xc8, 0x91, 0x1b, 0xbb, 0x73, 0xf8, 0x14, 0x61,
    0xc2, 0x45, 0xc5, 0x55, 0xfc, 0x8e, 0xe9, 0x8a, 0x46, 0xdb, 0x4e, 0x05, 0xc1, 0x64, 0xd1, 0xe0, 0x70, 0x16, 0xf9,
    0xb6, 0x36, 0x44, 0x8f, 0x0c, 0x29, 0xd3, 0x0e, 0x6f, 0x7c, 0xd7, 0x4a, 0xff, 0x75, 0x6c, 0x11, 0x10, 0x77, 0x3b,
    0x98, 0xba, 0x69, 0x5b, 0xa3, 0x6a, 0x72, 0x94, 0xd6, 0xd4, 0x22, 0x08, 0x86, 0x31, 0x47, 0xbe, 0x87, 0x63, 0x34,
    0x52, 0x3f, 0x68, 0xf6, 0x0f, 0xbf, 0xeb, 0xc0, 0xce, 0x24, 0xa5, 0x9a, 0x90, 0xed, 0x19, 0xb8, 0xb5, 0x96, 0xfa,
    0x88, 0x6e, 0xfb, 0x84, 0x23, 0x5d, 0xcd, 0xee, 0x92, 0x58, 0x4c, 0x0b, 0xf7, 0x0a, 0xb1, 0xda, 0x35, 0x5f, 0x9b,
    0xc9, 0xa9, 0xe7, 0x07, 0x1d, 0x18, 0xf3, 0xe3, 0xf1, 0xf4, 0xca, 0xb0, 0x6b, 0x30, 0xec, 0x4b, 0x48, 0x1c, 0xad,
    0xe2, 0x21, 0x1e, 0xa2, 0xbd, 0x5a, 0xd8, 0x43, 0x7a,
};

static int mMpswd_select_idx0[8] = { 17, 11, 0, 10, 12, 6, 8, 4 };
static int mMpswd_select_idx1[8] = { 3, 8, 11, 16, 4, 6, 9, 19 };
static int mMpswd_select_idx2[8] = { 9, 14, 17, 18, 11, 10, 12, 2 };
static int mMpswd_select_idx3[8] = { 0, 2, 1, 4, 18, 10, 12, 8 };
static int mMpswd_select_idx4[8] = { 17, 19, 16, 7, 12, 8, 2, 9 };
static int mMpswd_select_idx5[8] = { 16, 3, 1, 8, 18, 4, 7, 6 };
static int mMpswd_select_idx6[8] = { 19, 6, 10, 17, 3, 16, 8, 9 };
static int mMpswd_select_idx7[8] = { 17, 7, 18, 16, 12, 2, 11, 0 };
static int mMpswd_select_idx8[8] = { 6, 2, 12, 1, 8, 14, 0, 16 };
static int mMpswd_select_idx9[8] = { 19, 16, 11, 8, 17, 3, 6, 14 };
static int mMpswd_select_idx10[8] = { 18, 12, 2, 7, 10, 11, 1, 14 };
static int mMpswd_select_idx11[8] = { 8, 0, 14, 2, 7, 11, 12, 17 };
static int mMpswd_select_idx12[8] = { 9, 3, 2, 0, 11, 8, 14, 10 };
static int mMpswd_select_idx13[8] = { 10, 11, 12, 16, 19, 7, 17, 8 };
static int mMpswd_select_idx14[8] = { 19, 8, 6, 1, 17, 9, 14, 10 };
static int mMpswd_select_idx15[8] = { 9, 7, 17, 12, 19, 10, 1, 11 };

static int* mMpswd_select_idx_table[16] = {
    mMpswd_select_idx0,  mMpswd_select_idx1,  mMpswd_select_idx2,  mMpswd_select_idx3,
    mMpswd_select_idx4,  mMpswd_select_idx5,  mMpswd_select_idx6,  mMpswd_select_idx7,
    mMpswd_select_idx8,  mMpswd_select_idx9,  mMpswd_select_idx10, mMpswd_select_idx11,
    mMpswd_select_idx12, mMpswd_select_idx13, mMpswd_select_idx14, mMpswd_select_idx15,
};

static void mMpswd_bit_shift(u8* pswd, int shift) {
    u8 buf[mMpswd_PASSWORD_DATA_LEN - 1];
    u8 shifted_buf[mMpswd_PASSWORD_DATA_LEN - 1];
    int bytes_shifted;
    int bits_shifted;

    /* copy password data into work buffer while skipping key index byte */
    memcpy(buf, pswd, 1);
    memcpy(buf + 1, pswd + 2, (mMpswd_PASSWORD_DATA_LEN - 2));

    // this has to be a fakematch
    bytes_shifted = __abs(shift);
    bytes_shifted /= 8; // degenerate code
    bits_shifted = ABS(shift) % 8;

    while (bytes_shifted > mMpswd_PASSWORD_DATA_LEN - 1) {
        bytes_shifted -= (mMpswd_PASSWORD_DATA_LEN - 1);
    }

    if (shift > 0) {
        /* positive shift */
        int dst;
        int byte;
        int shift_mask = 0;
        int i;
        for (i = 0; i < bits_shifted; i++) {
            shift_mask = shift_mask * 2 + 1;
        }

        byte = (buf[bits_shifted == 0 ? 0 : mMpswd_PASSWORD_DATA_LEN - 2] >> (8 - bits_shifted)) & shift_mask;
        dst = bytes_shifted;
        for (i = 0; i < mMpswd_PASSWORD_DATA_LEN - 1; i++) {
            u8 now_byte = buf[i];

            shifted_buf[dst] = byte | (now_byte << bits_shifted);
            byte = (now_byte >> (8 - bits_shifted)) & shift_mask;
            dst = (dst + 1) % (mMpswd_PASSWORD_DATA_LEN - 1);
        }
    } else if (shift < 0) {
        /* negative shift */
        int shift_idx;
        int shift;
        int shift_mask = 0;
        int byte;
        int i;

        for (i = 0; i < bits_shifted; i++) {
            shift_mask = shift_mask * 2 + 1;
        }

        // fakematch?
        byte = 0;
        byte += (buf[bits_shifted == 0 ? mMpswd_PASSWORD_DATA_LEN - 2 : 0]); // start byte

        shift = 8 - bits_shifted;                                                                    // invert shift
        shift_idx = (mMpswd_PASSWORD_DATA_LEN - 2 - bytes_shifted) % (mMpswd_PASSWORD_DATA_LEN - 1); // dst index
        byte &= shift_mask;
        byte <<= shift; // move bits into position

        for (i = mMpswd_PASSWORD_DATA_LEN - 2; i >= 0; i--) {
            int now_byte = buf[i];

            shifted_buf[shift_idx] = byte | (now_byte >> bits_shifted); // save shifted byte
            byte = (now_byte & shift_mask) << shift;                    // update initial bits

            shift_idx--;
            if (shift_idx < 0) {
                shift_idx = mMpswd_PASSWORD_DATA_LEN - 2;
            }
        }
    } else {
        /* no shift (shift == 0) */
        memcpy(shifted_buf, buf, mMpswd_PASSWORD_DATA_LEN - 1);
    }

    /* copy shifted buffer back into main password buffer */
    memcpy(pswd, shifted_buf, 1);
    memcpy(pswd + 2, shifted_buf + 1, mMpswd_PASSWORD_DATA_LEN - 2);
}

static void mMpswd_bit_reverse(u8* pswd) {
    int i;

    for (i = 0; i < mMpswd_PASSWORD_DATA_LEN; i++) {
        if (i != mMpswd_PASSWORD_KEY_IDX) {
            pswd[i] ^= 0xFF;
        }
    }
}

static void mMpswd_bit_arrange_reverse(u8* pswd) {
    u8 buf[mMpswd_PASSWORD_DATA_LEN - 1];
    u8 reversed_buf[mMpswd_PASSWORD_DATA_LEN - 1];
    u8 reversed;
    int i;
    int j;
    int b;

    /* copy password data into work buffer while skipping key index byte */
    memcpy(buf, pswd, 1);
    memcpy(buf + 1, pswd + 2, (mMpswd_PASSWORD_DATA_LEN - 2));

    for (i = mMpswd_PASSWORD_DATA_LEN - 2, j = 0; i >= 0; i--) {

        reversed = 0;

        for (b = 7; b >= 0; b--) {
            reversed |= ((buf[i] >> b) & 1) << (7 - b);
        }

        reversed_buf[j] = reversed;
        j++;
    }

    memcpy(pswd, reversed_buf, 1);
    memcpy(pswd + 2, reversed_buf + 1, mMpswd_PASSWORD_DATA_LEN - 2);
}

static int mMpswd_check_opening_sentence(const u8* sentence) {
    int res = TRUE;
    if (sentence[0] != CHAR_SYMBOL_KEY) {
        res = FALSE;
    }

    return res;
}

static u8* mMpswd_get_password_pointer(u8* sentence) {
    int i;
    u8* ptr = NULL;

    for (i = 0; i < 32; i++) {
        if (sentence[0] == CHAR_NEW_LINE) {
            if (sentence[15] == CHAR_NEW_LINE) {
                ptr = sentence + 1;
            }

            break;
        }

        sentence++;
    }

    return ptr;
}

static void mMpswd_except_return_code(u8* dst, u8* src) {
    int i;

    for (i = 0; i < 29; i++, src++) {
        // src[14] is always going to be the newline character
        if (i != 14) {
            dst[0] = src[0];
            dst++;
        }
    }
}

static void mMpswd_adjust_letter(u8* pswd_str) {
    int i;

    for (i = 0; i < mMpswd_PASSWORD_STR_LEN; i++) {
        switch (pswd_str[i]) {
            case CHAR_ZERO: {
                pswd_str[i] = CHAR_O; // 0 -> O
                break;
            }

            case CHAR_ONE: {
                pswd_str[i] = CHAR_l; // 1 -> l
                break;
            }
        }
    }
}

static void mMpswd_make_passcode(u8* passcode, int type, int hit_rate, u8* str0, u8* str1, mActor_name_t item,
                                 int npc_type, int npc_code) {
    int checksum;

    switch (type) {
        case mMpswd_CODETYPE_FAMICOM:
        case mMpswd_CODETYPE_USER:
        case mMpswd_CODETYPE_CARD_E_MINI: {
            hit_rate = 1;
            npc_code = 0xFF;
            break;
        }

        case mMpswd_CODETYPE_POPULAR: {
            hit_rate =
                4; // potential bug? when code is set to popularity contest, hitrate interferes with checksum bits
            break;
        }

        case mMpswd_CODETYPE_CARD_E: {
            break;
        }

        case mMpswd_CODETYPE_MAGAZINE: {
            npc_type = (hit_rate >> 2) & 1;
            hit_rate &= 3;
            npc_code = 0xFF;
            break;
        }

        default: {
            type = mMpswd_CODETYPE_USER;
            break;
        }
    }

    passcode[0] = type << 5;
    passcode[0] |= hit_rate << 1;
    passcode[0] |= npc_type & 1;
    passcode[1] = npc_code;

    memcpy(passcode + 2, str0, PLAYER_NAME_LEN);
    memcpy(passcode + 10, str1, PLAYER_NAME_LEN);

    checksum = 0;
    passcode[18] = (item >> 8);
    passcode[19] = item;

    {
        int i;

        for (i = 0; i < PLAYER_NAME_LEN; i++) {
            checksum += str0[i];
        }

        for (i = 0; i < PLAYER_NAME_LEN; i++) {
            checksum += str1[i];
        }
    }

    checksum += item;
    checksum += npc_code;
    passcode[0] |= (checksum & 3) << 3;
}

static void mMpswd_chg_6bits_code(u8* sixbits, u8* eightbits) {
    u8 six_byte;
    int six_idx;
    int eight_bit;
    int six_bit;

    six_idx = 0;
    eight_bit = 0;
    six_bit = 0;
    six_byte = 0;

    do {
        u8 bit = ((eightbits[0] >> eight_bit) & 1) << six_bit;
        eight_bit++;
        six_bit++;
        six_byte |= bit;

        if (six_bit >= 6) {
            six_idx++;
            sixbits[0] = six_byte;
            six_bit = 0;
            sixbits++;

            if (six_idx >= mMpswd_PASSWORD_STR_LEN) {
                return;
            }

            six_byte = 0;
        }

        if (eight_bit >= 8) {
            eight_bit = 0;
            eightbits++;
        }
    } while (TRUE);
}

static void mMpswd_chg_8bits_code(u8* eightbits, u8* sixbits) {
    u8 eight_byte;
    int eight_idx;
    int six_bit;
    int eight_bit;

    eight_idx = 0;
    six_bit = 0;
    eight_bit = 0;
    eight_byte = 0;

    do {
        u8 bit = ((sixbits[0] >> six_bit) & 1) << eight_bit;
        six_bit++;
        eight_bit++;
        eight_byte |= bit;

        if (eight_bit >= 8) {
            eight_idx++;
            eightbits[0] = eight_byte;
            eight_bit = 0;
            eightbits++;

            if (eight_idx >= mMpswd_PASSWORD_DATA_LEN) {
                return;
            }

            eight_byte = 0;
        }

        if (six_bit >= 6) {
            six_bit = 0;
            sixbits++;
        }
    } while (TRUE);
}

static void mMpswd_get_RSA_key_code(int* p, int* q, int* r, int** select_table, const u8* pswd) {
    u32 rsa_info = pswd[mMpswd_RSA_INFO_IDX];
    int p_idx = rsa_info & 3;
    int q_idx = (rsa_info >> 2) & 3;

    if (p_idx == 3) {
        p_idx = (p_idx ^ q_idx) & 3;
        if (p_idx == 3) {
            p_idx = 0;
        }
    }

    if (q_idx == 3) {
        q_idx = (p_idx + 1) & 3;
        if (q_idx == 3) {
            q_idx = 1;
        }
    }

    if (p_idx == q_idx) {
        q_idx = (p_idx + 1) & 3;
        if (q_idx == 3) {
            q_idx = 1;
        }
    }

    *p = mMpswd_prime_number[p_idx];
    *q = mMpswd_prime_number[q_idx];
    *select_table = mMpswd_select_idx_table[(rsa_info >> 4) & 0xF];
    *r = mMpswd_prime_number[pswd[mMpswd_RSA_R_PRIME_IDX]];
}

static void mMpswd_chg_RSA_cipher(u8* pswd) {
    int r;
    int p;
    int q;
    int* select_idx_table;
    int b;
    int pq;
    int rsa_keysave;
    int i;
    int idx;
    int pow;
    int chg;

    mMpswd_get_RSA_key_code(&p, &q, &r, &select_idx_table, pswd);

    rsa_keysave = 0;
    pq = p * q;

    for (i = 0; i < 8; i++) {
        idx = select_idx_table[0];
        b = pswd[idx];
        chg = b;

        for (pow = r - 1; pow > 0; pow--) {
            chg = (chg * b) % pq;
        }

        pswd[idx] = chg;
        // save the 9th bit state
        rsa_keysave |= ((chg >> 8) & 1) << i;
        select_idx_table++;
    }

    pswd[mMpswd_RSA_KEYSAVE_IDX] = rsa_keysave;
}

static void mMpswd_decode_RSA_cipher(u8* pswd) {
    int n;
    int r;
    int p;
    int q;
    int pq_1;
    int* select_idx_table;
    int decrypted;
    int i;
    int b;
    int pq;
    int pow;
    int rsa_keysave;
    int d;

    mMpswd_get_RSA_key_code(&p, &q, &r, &select_idx_table, pswd);
    pq = p * q;
    pq_1 = (p - 1) * (q - 1);
    pow = 1;

    /* Calculate exponent d for decryption */
    do {
        n = pow * pq_1 + 1;
        if (n % r == 0) {
            r = n / r;
            break;
        }

        pow++;
    } while (TRUE);

    rsa_keysave = pswd[mMpswd_RSA_KEYSAVE_IDX];
    for (i = 0; i < 8; i++) {
        b = pswd[select_idx_table[0]] | (((rsa_keysave >> i) & 1) << 8);
        decrypted = b;

        /* Do decryption c^d = (m^e)^d = m (% n) */
        for (d = r - 1; d > 0; d--) {
            decrypted = (decrypted * b) % pq;
        }

        pswd[select_idx_table[0]] = decrypted;
        select_idx_table++;
    }
}

static void mMpswd_bit_mix_code(u8* pswd) {
    int bit_mix_code = pswd[mMpswd_BITMIX_CODE_IDX] & 0xF;

    if (bit_mix_code > 12) { // [13, 15] (3 or 18.75%)
        mMpswd_bit_arrange_reverse(pswd);
        mMpswd_bit_reverse(pswd);
        mMpswd_bit_shift(pswd, bit_mix_code * 3);
    } else if (bit_mix_code > 8) { // [9, 12] (4 or 25%)
        mMpswd_bit_arrange_reverse(pswd);
        mMpswd_bit_shift(pswd, -bit_mix_code * 5);
    } else if (bit_mix_code > 4) { // [5, 8] (4 or 25%)
        mMpswd_bit_shift(pswd, -bit_mix_code * 5);
        mMpswd_bit_reverse(pswd);
    } else { // [0, 4] (5 or 31.25%)
        mMpswd_bit_shift(pswd, bit_mix_code * 3);
        mMpswd_bit_arrange_reverse(pswd);
    }
}

static void mMpswd_decode_bit_code(u8* pswd) {
    int bit_mix_code = pswd[mMpswd_BITMIX_CODE_IDX] & 0xF;

    if (bit_mix_code > 12) { // [13, 15] (3 or 18.75%)
        mMpswd_bit_shift(pswd, -bit_mix_code * 3);
        mMpswd_bit_reverse(pswd);
        mMpswd_bit_arrange_reverse(pswd);
    } else if (bit_mix_code > 8) { // [9, 12] (4 or 25%)
        mMpswd_bit_shift(pswd, bit_mix_code * 5);
        mMpswd_bit_arrange_reverse(pswd);
    } else if (bit_mix_code > 4) { // [5, 8] (4 or 25%)
        mMpswd_bit_reverse(pswd);
        mMpswd_bit_shift(pswd, bit_mix_code * 5);
    } else { // [0, 4] (5 or 31.25%)
        mMpswd_bit_arrange_reverse(pswd);
        mMpswd_bit_shift(pswd, -bit_mix_code * 3);
    }
}

static void mMpswd_substitution_cipher(u8* pswd) {
    int i;

    for (i = 0; i < mMpswd_PASSWORD_DATA_LEN; i++) {
        pswd[i] = mMpswd_chg_code_table[pswd[i]];
    }
}

static void mMpswd_decode_substitution_cipher(u8* pswd) {
    int i;
    int idx;

    for (i = 0, idx = 0; i < mMpswd_PASSWORD_DATA_LEN; i++) {
        int j;

        for (j = 0; j < 256; j++) {
            if (mMpswd_chg_code_table[j] == pswd[idx]) {
                pswd[idx] = j;
                idx++;
                break;
            }
        }
    }
}

static void mMpswd_transposition_cipher(u8* pswd, int dir, int char_idx) {
    static int key_idx[2] = { 18, 9 };
    mMpswd_transposition_cipher_str_c* cipher;
    u8* trans_str;
    int len;

    int m;
    int i;
    int str_idx;

    cipher = &mMpswd_transposition_cipher_char_table[char_idx][pswd[key_idx[char_idx]] & 0xF];
    trans_str = cipher->str;
    len = cipher->len;

    m = 1;
    if (dir == 1) {
        m = -1;
    }
    str_idx = 0;
    for (i = 0; i < mMpswd_PASSWORD_DATA_LEN; i++) {
        if (i != key_idx[char_idx]) {
            *pswd += trans_str[str_idx++] * m;

            if (str_idx >= len) {
                str_idx = 0;
            }
        }

        pswd++;
    }
}

// @fakematch
static void mMpswd_bit_shuffle(u8* pswd, int stage) {
    u8 buf[mMpswd_PASSWORD_DATA_LEN - 1];
    u8 work_buf[mMpswd_PASSWORD_DATA_LEN - 1];

    int key_idx;
    int test2;
    u8* test;
    int count;

    count = mMpswd_PASSWORD_DATA_LEN - 1;
    key_idx = 2;

    if (stage == 0) {
        key_idx = 13;
        count = mMpswd_PASSWORD_DATA_LEN - 2;
    }

    memcpy(buf, pswd, key_idx);
    test = pswd + key_idx + 1;
    memcpy(buf + key_idx, test, test2 = (mMpswd_PASSWORD_DATA_LEN - 1) - key_idx); // TODO: fakematch here
    bzero(work_buf, count);

    {
        int* select_idx_table = mMpswd_select_idx_table[pswd[key_idx] & 3];
        int dst_idx;
        int i;

        for (i = 0; i < count; i++) {
            u8 b = buf[i];
            int bit;

            for (bit = 0; bit < 8; bit++) {
                dst_idx = i + select_idx_table[bit];

                if (dst_idx >= count) {
                    dst_idx -= count;
                }

                work_buf[dst_idx] |= (u8)(((b >> bit) & 1) << bit);
            }
        }
    }

    memcpy(pswd, work_buf, key_idx);
    memcpy(test, work_buf + key_idx, test2); // (mMpswd_PASSWORD_DATA_LEN - 1) - key_idx adding this screws it up
}

// @fakematch
static void mMpswd_decode_bit_shuffle(u8* pswd, int stage) {
    u8 work_buf[mMpswd_PASSWORD_DATA_LEN - 1];
    u8 buf[mMpswd_PASSWORD_DATA_LEN - 1];
    int key_idx;
    int test2;
    u8* test;
    int count;
    int* select_idx_table;
    int i;

    count = mMpswd_PASSWORD_DATA_LEN - 1;
    key_idx = 2;

    if (stage == 0) {
        key_idx = 13;
        count = mMpswd_PASSWORD_DATA_LEN - 2;
    }

    memcpy(work_buf, pswd, key_idx);
    test = pswd + key_idx + 1;
    memcpy(work_buf + key_idx, test, test2 = (mMpswd_PASSWORD_DATA_LEN - 1) - key_idx); // TODO: fakematch
    bzero(buf, count);

    select_idx_table = mMpswd_select_idx_table[pswd[key_idx] & 3];

    for (i = 0; i < count; i++) {
        int bit;

        for (bit = 0; bit < 8; bit++) {
            int dst_idx = i + select_idx_table[bit];

            if (dst_idx >= count) {
                dst_idx -= count;
            }

            buf[i] |= (u8)(((work_buf[dst_idx] >> bit) & 1) << bit);
        }
    }

    memcpy(pswd, buf, key_idx);
    memcpy(test, buf + key_idx, test2);
}

static void mMpswd_chg_common_font_code(u8* pswd) {
    u8 changed_pswd[mMpswd_PASSWORD_STR_LEN];
    int i;

    for (i = 0; i < mMpswd_PASSWORD_STR_LEN; i++) {
        changed_pswd[i] = usable_to_fontnum[pswd[i]];
    }

    memcpy(pswd, changed_pswd, mMpswd_PASSWORD_STR_LEN);
}

static u8 mMpswd_chg_password_font_code_sub(u8 c) {
    int i;
    int res = 0xFF;

    for (i = 0; i < 64; i++) {
        if (c == usable_to_fontnum[i]) {
            res = i; // probably should've used a break; here
        }
    }

    return res;
}

static int mMpswd_chg_password_font_code(u8* pswd) {
    u8 changed_pswd[mMpswd_PASSWORD_STR_LEN];
    int i;
    int res = TRUE;

    for (i = 0; i < mMpswd_PASSWORD_STR_LEN; i++) {
        u8 new_code = mMpswd_chg_password_font_code_sub(pswd[i]);

        if (new_code == 0xFF) {
            res = FALSE;
            break;
        }

        changed_pswd[i] = new_code;
    }

    if (res == TRUE) {
        memcpy(pswd, changed_pswd, mMpswd_PASSWORD_STR_LEN);
    }

    return res;
}

extern void mMpswd_make_password(u8* password_buf, int type, int hit_rate, u8* str0, u8* str1, mActor_name_t item,
                                 int npc_type, int npc_code) {
    u8 work_buf[mMpswd_PASSWORD_STR_LEN];

    bzero(work_buf, mMpswd_PASSWORD_STR_LEN);
    mMpswd_make_passcode(work_buf, type, hit_rate, str0, str1, item, npc_type, npc_code);
    mMpswd_substitution_cipher(work_buf);
    mMpswd_transposition_cipher(work_buf, 1, 0);
    mMpswd_bit_shuffle(work_buf, 0);
    mMpswd_chg_RSA_cipher(work_buf);
    mMpswd_bit_mix_code(work_buf);
    mMpswd_bit_shuffle(work_buf, 1);
    mMpswd_transposition_cipher(work_buf, 0, 1);
    mMpswd_chg_6bits_code(password_buf, work_buf);
    mMpswd_chg_common_font_code(password_buf);
}

extern int mMpswd_decode_code(u8* password_data, u8* password_str) {
    u8 work_buf[mMpswd_PASSWORD_STR_LEN];
    int res = FALSE;

    memcpy(work_buf, password_str, mMpswd_PASSWORD_STR_LEN);
    mMpswd_adjust_letter(work_buf);
    if (mMpswd_chg_password_font_code(work_buf) == TRUE) {
        mMpswd_chg_8bits_code(password_data, work_buf);
        mMpswd_transposition_cipher(password_data, 1, 1);
        mMpswd_decode_bit_shuffle(password_data, 1);
        mMpswd_decode_bit_code(password_data);
        mMpswd_decode_RSA_cipher(password_data);
        mMpswd_decode_bit_shuffle(password_data, 0);
        mMpswd_transposition_cipher(password_data, 0, 0);
        mMpswd_decode_substitution_cipher(password_data);

        res = TRUE;
    }

    return res;
}

extern int mMpswd_restore_code(u8* body, u8* password) {
    u8 password_str[mMpswd_PASSWORD_STR_LEN];
    int res = FALSE;

    if (mMpswd_check_opening_sentence(body) == TRUE) {
        u8* password_str_p = mMpswd_get_password_pointer(body);
        if (password_str_p != NULL) {
            mMpswd_except_return_code(password_str, password_str_p);
            res = mMpswd_decode_code(password, password_str);
        }
    }

    return res;
}

extern void mMpswd_password(u8* password_data, mMpswd_password_c* password) {
    u32 b0 = password_data[0];

    password->checksum = (b0 >> 3) & 3;
    memcpy(password->str0, password_data + 2, PLAYER_NAME_LEN);
    memcpy(password->str1, password_data + 10, PLAYER_NAME_LEN);
    password->item = (password_data[18] << 8) + password_data[19];
    password->type = (b0 >> 5) & 7;

    switch (password->type) {
        case mMpswd_CODETYPE_POPULAR: {
            password->hit_rate_index = (b0 >> 1) & 3;
            password->npc_type = b0 & 1;
            password->npc_code = password_data[1];
            break;
        }

        case mMpswd_CODETYPE_CARD_E: {
            password->hit_rate_index = (b0 >> 1) & 3;
            password->npc_type = b0 & 1;
            password->npc_code = password_data[1];
            break;
        }

        case mMpswd_CODETYPE_MAGAZINE: {
            password->hit_rate_index = ((b0 >> 1) & 3) | (b0 & 1) << 2;
            password->npc_type = -1;
            password->npc_code = -1;
            break;
        }

        default: {
            password->hit_rate_index = (b0 >> 1) & 3;
            password->npc_type = -1;
            password->npc_code = -1;
            break;
        }
    }
}

extern int mMpswd_password_zuru_check(mMpswd_password_c* password) {
    int cheated = TRUE;

    if (password->type < mMpswd_CODETYPE_NUM) {
        int checksum = 0;
        int i;

        for (i = 0; i < PLAYER_NAME_LEN; i++) {
            checksum += password->str0[i];
        }

        for (i = 0; i < PLAYER_NAME_LEN; i++) {
            checksum += password->str1[i];
        }

        checksum += password->item;
        checksum += password->npc_code;

        if ((checksum & 3) == password->checksum) {
            cheated = FALSE;
        }
    }

    return cheated;
}

static int mMpswd_check_present_famicom(mActor_name_t item) {
    int i;
    int res = FALSE;

    for (i = 0; i < pswd_famicom_list_max; i++) {
        if (item == mRmTp_FtrIdx2FtrItemNo(pswd_famicom_list[i], 0)) {
            res = TRUE;
            break;
        }
    }

    return res;
}

extern int mMpswd_check_present_user(mActor_name_t item) {
    mActor_name_t full_stack_item;
    u32 price = 0;
    int res = FALSE;

    switch (ITEM_NAME_GET_TYPE(item)) {
        case NAME_TYPE_FTR0:
        case NAME_TYPE_FTR1: {
            if (item >= FTR_CLOTH_START && item <= FTR_CLOTH_END) {
                item = mRmTp_FtrItemNo2Item1ItemNo(item, FALSE);
                if (mSP_SearchItemCategoryPriority(item, mSP_KIND_CLOTH, mSP_LISTTYPE_COMMON, NULL) ||
                    mSP_SearchItemCategoryPriority(item, mSP_KIND_CLOTH, mSP_LISTTYPE_UNCOMMON, NULL) ||
                    mSP_SearchItemCategoryPriority(item, mSP_KIND_CLOTH, mSP_LISTTYPE_RARE, NULL)) {
                    price = mSP_ItemNo2ItemPrice(item);
                }
            } else if (item >= FTR_UMBRELLA_START && item <= FTR_UMBRELLA_END) {
                price = mSP_ItemNo2ItemPrice(mRmTp_FtrItemNo2Item1ItemNo(item, FALSE));
            } else if ( // TODO: furniture index values need to be declared in some header file as defines
                (mRmTp_FtrItemNo2FtrIdx(item) >= FTR_NOG_BALLOON_COMMON0 && mRmTp_FtrItemNo2FtrIdx(item) <= FTR_NOG_BALLOON_COMMON7) || // balloons
                (item >= FTR_START(FTR_NOG_COLLEGENOTE) && item <= FTR_END(FTR_IKE_NIKKI_WAFU1)) ||                    // diaries
                (mRmTp_FtrItemNo2FtrIdx(item) >= FTR_UTIWA0 && mRmTp_FtrItemNo2FtrIdx(item) <= FTR_UTIWA7) || // fans
                (mRmTp_FtrItemNo2FtrIdx(item) >= FTR_KAZAGURUMA0 && mRmTp_FtrItemNo2FtrIdx(item) <= FTR_KAZAGURUMA7) || // pinwheels
                (mRmTp_FtrItemNo2FtrIdx(item) >= FTR_GOLD_ITEM0 && mRmTp_FtrItemNo2FtrIdx(item) <= FTR_GOLD_ITEM3) || // golden tools
                (mRmTp_FtrItemNo2FtrIdx(item) >= FTR_TOOL0 && mRmTp_FtrItemNo2FtrIdx(item) <= FTR_TOOL3)    // regular tools
            ) {
                /* Convert furniture to their item1 variants */
                price = mSP_ItemNo2ItemPrice(mRmTp_FtrItemNo2Item1ItemNo(item, FALSE));
            } else if (mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_COMMON, NULL) ||
                       mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_UNCOMMON, NULL) ||
                       mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_RARE, NULL) ||
                       mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_TRAIN, NULL) ||
                       mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_EVENT, NULL) ||
                       mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_LOTTERY, NULL) ||
                       mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_EVENTPRESENTCHUMON,
                                                      NULL)) {
                price = mSP_ItemNo2ItemPrice(item);
            }

            break;
        }

        case NAME_TYPE_ITEM1: {
            if (item >= ITM_CLOTH_START && item < ITM_CLOTH_END) {
                if (mSP_SearchItemCategoryPriority(item, mSP_KIND_CLOTH, mSP_LISTTYPE_COMMON, NULL) ||
                    mSP_SearchItemCategoryPriority(item, mSP_KIND_CLOTH, mSP_LISTTYPE_UNCOMMON, NULL) ||
                    mSP_SearchItemCategoryPriority(item, mSP_KIND_CLOTH, mSP_LISTTYPE_RARE, NULL)) {
                    price = mSP_ItemNo2ItemPrice(item);
                }
            } else if (item >= ITM_UMBRELLA00 && item <= ITM_MY_ORG_UMBRELLA7) {
                price = mSP_ItemNo2ItemPrice(item);
            } else if ((item >= ITM_RED_BALLOON && item <= ITM_BUNNY_O_BALLOON) ||
                       (item >= ITM_DIARY00 && item <= ITM_DIARY15) ||
                       (item >= ITM_BLUEBELL_FAN && item <= ITM_LEAF_FAN) ||
                       (item >= ITM_YELLOW_PINWHEEL && item <= ITM_FANCY_PINWHEEL) ||
                       (item >= ITM_GOLDEN_NET && item <= ITM_GOLDEN_ROD) || (item >= ITM_NET && item <= ITM_ROD)) {
                price = mSP_ItemNo2ItemPrice(item);
            } else {
                switch (ITEM_NAME_GET_CAT(item)) {
                    case ITEM1_CAT_FRUIT: {
                        price = mSP_ItemNo2ItemPrice(item);
                        break;
                    }

                    case ITEM1_CAT_PAPER: {
                        full_stack_item = ITM_PAPER_STACK_FOUR_START + (item & 0x3F);
                        if (mSP_SearchItemCategoryPriority(full_stack_item, mSP_KIND_PAPER, mSP_LISTTYPE_COMMON,
                                                           NULL) ||
                            mSP_SearchItemCategoryPriority(full_stack_item, mSP_KIND_PAPER, mSP_LISTTYPE_UNCOMMON,
                                                           NULL) ||
                            mSP_SearchItemCategoryPriority(full_stack_item, mSP_KIND_PAPER, mSP_LISTTYPE_RARE, NULL)) {
                            price = mSP_ItemNo2ItemPrice(full_stack_item);
                        }

                        break;
                    }

                    case ITEM1_CAT_WALL: {
                        if (mSP_SearchItemCategoryPriority(item, mSP_KIND_WALLPAPER, mSP_LISTTYPE_COMMON, NULL) ||
                            mSP_SearchItemCategoryPriority(item, mSP_KIND_WALLPAPER, mSP_LISTTYPE_UNCOMMON, NULL) ||
                            mSP_SearchItemCategoryPriority(item, mSP_KIND_WALLPAPER, mSP_LISTTYPE_RARE, NULL)) {
                            price = mSP_ItemNo2ItemPrice(item);
                        }

                        break;
                    }

                    case ITEM1_CAT_CARPET: {
                        if (mSP_SearchItemCategoryPriority(item, mSP_KIND_CARPET, mSP_LISTTYPE_COMMON, NULL) ||
                            mSP_SearchItemCategoryPriority(item, mSP_KIND_CARPET, mSP_LISTTYPE_UNCOMMON, NULL) ||
                            mSP_SearchItemCategoryPriority(item, mSP_KIND_CARPET, mSP_LISTTYPE_RARE, NULL)) {
                            price = mSP_ItemNo2ItemPrice(item);
                        }

                        break;
                    }
                }
            }

            break;
        }
    }

    if (price != 0) {
        res = TRUE;
    }

    return res;
}

static int mMpswd_check_present_other(mActor_name_t item) {
    int res = FALSE;

    switch (ITEM_NAME_GET_TYPE(item)) {
        case NAME_TYPE_FTR0:
        case NAME_TYPE_FTR1: {
            switch (mRmTp_FurnitureIdx2FurnitureKind(mRmTp_FtrItemNo2FtrIdx(item))) {
                case mRmTp_BIRTH_TYPE_FTR_CLOTH:
                case mRmTp_BIRTH_TYPE_FTR_UMBRELLA:
                case mRmTp_BIRTH_TYPE_FTR_INSECT:
                case mRmTp_BIRTH_TYPE_FTR_FISH:
                case mRmTp_BIRTH_TYPE_UNOBTAINABLE:
                case mRmTp_BIRTH_TYPE_FAMICOM_EREADER:
                case mRmTp_BIRTH_TYPE_MY_ORIGINAL:
                case mRmTp_BIRTH_TYPE_FAMICOM_CODE:
                case mRmTp_BIRTH_TYPE_FTR_DIARY: {
                    break;
                }

                default: {
                    res = TRUE;
                    break;
                }
            }

            break;
        }

        case NAME_TYPE_ITEM1: {
            switch (ITEM_NAME_GET_CAT(item)) {
                case ITEM1_CAT_TOOL: {
                    /* allow umbrellas */
                    if (item >= ITM_UMBRELLA00 && item <= ITM_UMBRELLA31) {
                        res = TRUE;
                        break;
                    }

                    /* allow balloons */
                    if ((item >= ITM_RED_BALLOON && item <= ITM_BUNNY_O_BALLOON) == TRUE) {
                        res = TRUE;
                        break;
                    }

                    /* allow fans */
                    if ((item >= ITM_BLUEBELL_FAN && item <= ITM_LEAF_FAN) == TRUE) {
                        res = TRUE;
                        break;
                    }

                    /* allow pinwheels */
                    if ((item >= ITM_YELLOW_PINWHEEL && item <= ITM_FANCY_PINWHEEL) == TRUE) {
                        res = TRUE;
                        break;
                    }

                    break;
                }

                case ITEM1_CAT_PAPER: {
                    int amount = item - ITM_PAPER_START;
                    if (amount / 64 + 1 >= 4) {
                        res = TRUE; // Paper in stacks of 4
                    }

                    break;
                }

                case ITEM1_CAT_FISH: {
                    /* fish are not allowed */
                    break;
                }

                case ITEM1_CAT_INSECT: {
                    /* insects are not allowed */
                    break;
                }

                default: {
                    /* allow everything else in the 2XXX range through */
                    res = TRUE;
                    break;
                }
            }
            break;
        }
    }

    return res;
}

extern int mMpswd_check_present(mMpswd_password_c* password) {
    mActor_name_t present = password->item;
    int valid;

    if (present == RSV_NO) {
        valid = TRUE;
    } else {
        switch (password->type) {
            case mMpswd_CODETYPE_FAMICOM: {
                valid = mMpswd_check_present_famicom(present);
                break;
            }

            case mMpswd_CODETYPE_USER: {
                valid = mMpswd_check_present_user(present);
                break;
            }

            default: {
                valid = mMpswd_check_present_other(present);
                break;
            }
        }
    }

    return valid;
}

extern mActor_name_t mMpswd_get_sp_npc_num(int sp_npc) {
    static mActor_name_t sp_npc_code_table[mMpswd_SPECIAL_NPC_NUM] = {
        SP_NPC_SHOP_MASTER,    // Tom Nook
        SP_NPC_ARTIST,         // Wendell
        SP_NPC_CARPETPEDDLER,  // Saharah
        SP_NPC_DESIGNER,       // Gracie
        SP_NPC_KABUPEDDLER,    // Joan
        SP_NPC_GYPSY,          // Katrina
        SP_NPC_POLICE,         // Copper
        SP_NPC_HALLOWEEN,      // Jack
        SP_NPC_SANTA,          // Jingle
        SP_NPC_POST_MAN,       // Pete
        SP_NPC_POST_GIRL,      // Pelly
        SP_NPC_POST_GIRL2,     // Phyllis
        SP_NPC_GUIDE,          // Rover
        SP_NPC_TOTAKEKE,       // K.K. Slider
        SP_NPC_ANGLER,         // Chip
        SP_NPC_POLICE2,        // Booker
        SP_NPC_MAMEDANUKI0,    // Timmy
        SP_NPC_MAMEDANUKI1,    // Tommy
        SP_NPC_BROKER,         // Redd
        SP_NPC_MAJIN,          // Resetti
        SP_NPC_EV_DOZAEMON,    // Gulliver
        SP_NPC_STATION_MASTER, // Porter
        SP_NPC_CURATOR,        // Blathers
        SP_NPC_SENDO,          // Kapp'n
        SP_NPC_NEEDLEWORK0,    // Mable
        SP_NPC_NEEDLEWORK1,    // Sable
        SP_NPC_EV_SONCHO,      // Tortimer
        SP_NPC_EV_GHOST,       // Wisp
        SP_NPC_MAJIN_BROTHER,  // Don
        SP_NPC_MASK_CAT,       // Blanca
        SP_NPC_TURKEY,         // Franklin
        SP_NPC_HEM,            // Farley
    };

    if (sp_npc < 0 || sp_npc >= mMpswd_SPECIAL_NPC_NUM) {
        sp_npc = 0;
    }

    return sp_npc_code_table[sp_npc];
}

extern int mMpswd_check_npc_code(mMpswd_password_c* password) {
    int res = FALSE;

    if ((password->npc_type == mMpswd_NPCTYPE_NORMAL && password->npc_code < NPC_NUM) ||
        (password->npc_type == mMpswd_NPCTYPE_SPECIAL && password->npc_code < mMpswd_SPECIAL_NPC_NUM)) {
        res = TRUE;
    }

    return res;
}

extern int mMpswd_check_name(mMpswd_password_c* password) {
    int res = FALSE;
    Private_c* priv_data = Common_Get(now_private);

    if (mPr_CheckCmpPlayerName(password->str0, Common_Get(now_private)->player_ID.player_name) == TRUE) {
        if (mLd_CheckCmpLandName(password->str1, Common_Get(now_private)->player_ID.land_name) == TRUE) {
            res = TRUE;
        }
    }

    return res;
}
