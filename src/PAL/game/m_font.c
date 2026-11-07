#include "m_font.h"

#include "audio.h"
#include "m_lib.h"
#include "libforest/gbi_extensions.h"
#include "dataobject.h"
#include "game.h"
#include "graph.h"
#include "types.h"
#include "libultra/gu.h"
#include "sys_matrix.h"
#include "MSL_C/w_math.h"
#include "m_rcp.h"
#include "libc64/math64.h"
#include "libultra/libultra.h"
#include "m_common_data.h"
#include "m_msg.h"
#include "padmgr.h"

#define mFont_CC_FONT 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0
#define mFont_CC_NOFONT 0, 0, 0, PRIMITIVE, 0, PRIMITIVE, TEXEL0, PRIMITIVE

#include "../src/PAL/game/m_font_offset.c_inc"
#include "../src/PAL/game/m_font_main.c_inc"
#include "../src/PAL/game/m_font_mark.c_inc"
#include "../src/PAL/game/m_font_rect.c_inc"

/* @unused static u8* mFont_Get_end_load_texture() */

extern void mFont_ct() {
    mFont_CurrentScale_init();
    mFont_CurrentColor_init();
}

static int mMsg_CutLeftSpace(u8* str, int str_len) {
    u8* dst;
    u8* src;
    int i, j;

    for (i = 0; i < str_len; i++) {
        if (str[i] != CHAR_SPACE) {
            break;
        }
    }

    if (i == str_len) {
        return 0;
    } else if (i == 0) {
        return str_len;
    }

    dst = str;
    src = str + i;
    for (j = i; j < str_len; j++) {
        *dst++ = *src++;
    }

    for (j = 0; j < i; j++) {
        *dst++ = CHAR_SPACE;
    }

    return str_len - i;
}

static u8 mFont_suji_data[10] = "0123456789";

static int mFont_suji_check(u8 c) {
    int i;

    for (i = 0; i < 10; i++) {
        if (c == mFont_suji_data[i]) {
            return TRUE;
        }
    }

    return FALSE;
}

extern int mFont_UnintToString(u8* str, int figure, u32 num, int figure_start, int left_cut, int fill_zero,
                               int separator) {
    int i;
    int j;
    u32 cur_num;
    int next;

    int temp2;
    int last_figure;

    int l = figure - figure_start;
    u8 fill_char = fill_zero ? CHAR_ZERO : CHAR_SPACE;
    u8 left_fill_char = fill_zero && !left_cut ? CHAR_ZERO : CHAR_SPACE;

    cur_num = num;
    for (last_figure = figure - 1; last_figure >= l; last_figure--) {
        next = cur_num / 10;
        temp2 = cur_num - next * 10;
        if (cur_num == 0) {
            if (num == 0 && last_figure == figure - 1) {
                str[last_figure] = CHAR_ZERO;
            } else {
                str[last_figure] = fill_char;
            }
        } else {
            str[last_figure] = mFont_suji_data[temp2];
        }
        cur_num = next;
    }

    for (i = last_figure; i >= 0; i--) {
        str[i] = left_fill_char;
    }

    if (separator) {
        int count = 0;
        for (i = figure - 1; i >= 0; i--) {
            if (mFont_suji_check(str[i])) {
                count++;
                if (count > 3) {
                    for (j = 0; j < i; j++) {
                        str[j] = str[j + 1];
                    }

                    str[i] = CHAR_PERIOD;
                    count = 0;
                }
            }
        }
    }

    if (left_cut) {
        return mMsg_CutLeftSpace(str, figure);
    }

    return figure;
}

extern int mFont_char_save_data_check(u8 c) {
    return c == CHAR_CONTROL_CODE || c == CHAR_MESSAGE_TAG;
}

typedef struct font_small_capital_s {
    u8 small;
    u8 capital;
} mFont_SmallCapital_c;

extern u8 mFont_small_to_capital(u8 small) {
    static const mFont_SmallCapital_c tbl[] = {
        { CHAR_a, CHAR_A },
        { CHAR_b, CHAR_B },
        { CHAR_c, CHAR_C },
        { CHAR_d, CHAR_D },
        { CHAR_e, CHAR_E },
        { CHAR_f, CHAR_F },
        { CHAR_g, CHAR_G },
        { CHAR_h, CHAR_H },
        { CHAR_i, CHAR_I },
        { CHAR_j, CHAR_J },
        { CHAR_k, CHAR_K },
        { CHAR_l, CHAR_L },
        { CHAR_m, CHAR_M },
        { CHAR_n, CHAR_N },
        { CHAR_o, CHAR_O },
        { CHAR_p, CHAR_P },
        { CHAR_q, CHAR_Q },
        { CHAR_r, CHAR_R },
        { CHAR_s, CHAR_S },
        { CHAR_t, CHAR_T },
        { CHAR_u, CHAR_U },
        { CHAR_v, CHAR_V },
        { CHAR_w, CHAR_W },
        { CHAR_x, CHAR_X },
        { CHAR_y, CHAR_Y },
        { CHAR_z, CHAR_Z },
        { CHAR_DIARESIS_a, CHAR_DIAERESIS_A },
        { CHAR_GRAVE_a, CHAR_GRAVE_A },
        { CHAR_ACUTE_a, CHAR_ACUTE_A },
        { CHAR_CIRCUMFLEX_a, CHAR_CIRCUMFLEX_A },
        { CHAR_TILDE_a, CHAR_TILDE_A },
        { CHAR_ANGSTROM_a, CHAR_ANGSTROM_A },
        { CHAR_LOWER_CEDILLA, CHAR_CEDILLA },
        { CHAR_GRAVE_e, CHAR_GRAVE_E },
        { CHAR_ACUTE_e, CHAR_ACUTE_E },
        { CHAR_CIRCUMFLEX_e, CHAR_CIRCUMFLEX_E },
        { CHAR_DIARESIS_e, CHAR_DIARESIS_E },
        { CHAR_GRAVE_i, CHAR_GRAVE_I },
        { CHAR_ACUTE_i, CHAR_ACUTE_I },
        { CHAR_CIRCUMFLEX_i, CHAR_CIRCUMFLEX_I },
        { CHAR_DIARESIS_i, CHAR_DIARESIS_I },
        { CHAR_LOWER_ETH, CHAR_ETH },
        { CHAR_TILDE_n, CHAR_TILDE_N },
        { CHAR_GRAVE_o, CHAR_GRAVE_O },
        { CHAR_ACUTE_o, CHAR_ACUTE_O },
        { CHAR_CIRCUMFLEX_o, CHAR_CIRCUMFLEX_O },
        { CHAR_TILDE_o, CHAR_TILDE_O },
        { CHAR_DIARESIS_o, CHAR_DIARESIS_O },
        { CHAR_oe, CHAR_OE },
        { CHAR_GRAVE_u, CHAR_GRAVE_U },
        { CHAR_ACUTE_u, CHAR_ACUTE_U },
        { CHAR_CIRCUMFLEX_u, CHAR_CIRCUMFLEX_U },
        { CHAR_DIARESIS_u, CHAR_DIARESIS_U },
        { CHAR_ACUTE_y, CHAR_ACUTE_Y },
        { CHAR_LOWER_THORN, CHAR_THORN },
        { CHAR_LOWER_ASH, CHAR_ASH },
        { CHAR_LOWER_ETHEL, CHAR_ETHEL },
    };

    u8 res = small;
    const mFont_SmallCapital_c* t = tbl;
    int i;

    for (i = 0; i < ARRAY_COUNT(tbl); i++, t++) {
        if (t->small == small) {
            res = t->capital;
            break;
        }
    }

    return res;
}

extern int mFont_Check_Cont(u8 c) {
    return c == CHAR_CONTROL_CODE;
}

extern int mFont_Check_ContId(const u8* str, int cont_id) {
    int ret = FALSE;

    if (mFont_Check_Cont(str[0]) && str[1] == cont_id) {
        ret = TRUE;
    }

    return ret;
}

extern u8 mFont_Get_ContPrmU8(const u8* str) {
    return str[2];
}

extern int mFont_Check_Tag(u8 c) {
    return c == CHAR_MESSAGE_TAG;
}

extern u8 mFont_Get_TagSize(const u8* str) {
    return str[1];
}

extern int mFont_Get_TagGroup(const u8* str) {
    return str[2];
}

extern int mFont_Get_TagId(const u8* str) {
    return (str[3] << 8) | str[4];
}

extern int mFont_Check_TagId(const u8* str, int args, int group, int id) {
    int ret = FALSE;

    if (mFont_Check_Tag(str[0])) {
        int chk_grp = str[2];
        int chk_id = mFont_Get_TagId(str);

        if (chk_grp == group && chk_id == id) {
            ret = TRUE;
        }
    }

    return ret;
}
extern u8 mFont_Get_TagPrmU8(const u8* str) {
    return str[5];
}

extern u16 mFont_Get_TagPrmU16(const u8* str) {
    return (str[5] << 8) | str[6];
}

extern void mFont_Get_TagPrmU16U16(const u8* str, u16* prm0, u16* prm1) {
    *prm0 = (str[5] << 8) | str[6];
    *prm1 = (str[7] << 8) | str[8];
}

extern void mFont_Get_TagPrmU16U16U16(const u8* str, u16* prm0, u16* prm1, u16* prm2) {
    *prm0 = (str[5] << 8) | str[6];
    *prm1 = (str[7] << 8) | str[8];
    *prm2 = (str[9] << 8) | str[10];
}

extern void mFont_Get_TagPrmU16U16U16U16(const u8* str, u16* prm0, u16* prm1, u16* prm2, u16* prm3) {
    *prm0 = (str[5] << 8) | str[6];
    *prm1 = (str[7] << 8) | str[8];
    *prm2 = (str[9] << 8) | str[10];
    *prm3 = (str[11] << 8) | str[12];
}

extern void mFont_Get_TagPrmU8U16(const u8* str, u8* prm0, u16* prm1) {
    *prm0 = str[5];
    *prm1 = (str[6] << 8) | str[7];
}

extern void mFont_Get_TagPrmU8U16U16(const u8* str, u8* prm0, u16* prm1, u16* prm2) {
    *prm0 = str[5];
    *prm1 = (str[6] << 8) | str[7];
    *prm2 = (str[8] << 8) | str[9];
}
