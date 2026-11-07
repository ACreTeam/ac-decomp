#include "m_mail_check_ovl.h"

#include "m_mail.h"
#include "m_font.h"
#include "m_msg.h"

static int mMck_strlen(u8* str, int len) {
    u8* end_p = str + len;

    while (len != 0) {
        len--;

        if (*end_p != CHAR_SPACE) {
            goto end; /* Don't like this */
        }

        end_p--;
    }

    len--;

end:
    return len + 1;
}

static int mMck_cmp_sep(u8 c) {
    switch (c) {
        case CHAR_SPACE:
        case CHAR_COMMA:
        case CHAR_QUESTIONMARK:
        case CHAR_EXCLAMATION:
        case CHAR_PERIOD:
        case CHAR_INTERPUNCT:
        case CHAR_NEW_LINE:
            return TRUE;

        default:
            return FALSE;
    }
}

static u8* mMck_search_sep(u8* str, u8 len) {
    while (len-- != 0) {

        /* Only accept the separator if the next character is also not a separator */
        if (mMck_cmp_sep(str[0]) == TRUE && mMck_cmp_sep(str[1]) == FALSE) {
            break;
        }

        str++;
    }

    return str;
}

static u8* mMck_next_key(u8* str) {
    return str + 2;
}

typedef struct string_table_s {
    u8 trigger_lower;
    u8 trigger_upper;

    u8* str_table;
} mMck_cmp_str_table_c;

#if VERSION == VER_GAFP01_00 && GAME_LANGUAGE == GAME_LANG_ES
#include "../src/PAL/game/m_mail_check_ovl_es.c_inc"
#elif VERSION == VER_GAFP01_00 && GAME_LANGUAGE == GAME_LANG_FR
#include "../src/PAL/game/m_mail_check_ovl_fr.c_inc"
#elif VERSION == VER_GAFP01_00 && GAME_LANGUAGE == GAME_LANG_IT
#include "../src/PAL/game/m_mail_check_ovl_it.c_inc"
#elif VERSION == VER_GAFP01_00 && GAME_LANGUAGE == GAME_LANG_DE
#include "../src/PAL/game/m_mail_check_ovl_de.c_inc"
#else
#include "../src/game/m_mail_check_ovl_en.c_inc"
#endif

#if VERSION == VER_GAFP01_00 && GAME_LANGUAGE == GAME_LANG_ES
static int mMck_cmp_code(u8 code1, u8 code2) {
    u8* table = l_mmck_dash_table;
    int res = FALSE;

    if (code1 == code2) {
        res = TRUE;
    } else {
        for (; table[0] != CHAR_CONTROL_CODE; table += 2) {
            if (code2 == table[0]) {
                if (code1 == table[1]) {
                    res = TRUE;
                }
                break;
            } else if (code2 == table[1]) {
                if (code1 == table[0]) {
                    res = TRUE;
                }
                break;
            }
        }
    }

    return res;
}
#endif

static int mMck_cmp_key(u8* str) {
    u8 char0 = str[0];
    u8 char1 = str[1];
    u8 char2 = str[2];
#if VERSION == VER_GAFP01_00 && GAME_LANGUAGE == GAME_LANG_ES
    u8* str_table;
#endif
    int i;

    for (i = 0; i < 26; i++) {
#if VERSION == VER_GAFP01_00 && GAME_LANGUAGE == GAME_LANG_ES
        str_table = cmp_str_table_c[i].str_table;
#else
        u8* str_table = cmp_str_table_c[i].str_table;
#endif

#if VERSION == VER_GAFP01_00 && GAME_LANGUAGE == GAME_LANG_ES
        if (mMck_cmp_code(char0, cmp_str_table_c[i].trigger_lower) == TRUE ||
            mMck_cmp_code(char0, cmp_str_table_c[i].trigger_upper) == TRUE) {
#else
        if (char0 == cmp_str_table_c[i].trigger_lower || char0 == cmp_str_table_c[i].trigger_upper) {
#endif

            /*
            BUG: in the NTSC-U (US version) of AC, the string tables are missing the control code character (0x7F).
            The game will continue processing data as syllable values until it either reaches an unrelated 0x7F byte,
            or it finds two consecutive bytes which satisfies the current syllable pair.
            */

            for (str_table; str_table[0] != CHAR_CONTROL_CODE; str_table = mMck_next_key(str_table)) {
#if VERSION == VER_GAFP01_00 && GAME_LANGUAGE == GAME_LANG_ES
                if (mMck_cmp_code(char1, str_table[0]) == TRUE && mMck_cmp_code(char2, str_table[1]) == TRUE) {
#else
                if (char1 == str_table[0] && char2 == str_table[1]) {
#endif
                    return TRUE; /* Valid 3-letter (syllable?) match found */
                }
            }
        }
    }

    return FALSE; /* No match found */
}

extern int mMck_check_key_hit(int* len, u8* str) {
    u8* sep = str;
    int i;
    int str_len;
    int matches;
    int chars;

    *len = 0;
    i = 0;
    matches = 0;
    chars = 0;
    str_len = mMck_strlen(str, MAIL_BODY_LEN - 3);

    if (str_len == 0) {
        return 0;
    } else {
        /* There might be a goto here? */

        while (i <= str_len) {
            sep = str;
            chars++;
            if (mMck_cmp_key(sep)) {
                matches++;
            }

            str = mMck_search_sep(sep, str_len - i) + 1;
            i += (int)(str - sep); /* track current position */
        }

        *len = chars;
        return (matches * 10000) / (chars * 100);
    }
}

static int mMck_cmp_sep_nes(u8 c) {
    switch (c) {
        case CHAR_PERIOD:
        case CHAR_QUESTIONMARK:
        case CHAR_EXCLAMATION:
            return TRUE;

        default:
            return FALSE;
    }
}

static int mMck_strlen_new(u8* str, int len) {
    if (len > 0) {
        u8* end_p = (u8*)(len + (int)str);
        end_p--;

        for (len; len != 0; len--) {
            if (*end_p != CHAR_SPACE) {
                break;
            }
            end_p--;
        }
    }

    return len;
}

static int mMck_check_alpha(u8 c, int alpha_case) {
    static u8 offset[mMck_CASE_NUM] = { CHAR_a, CHAR_A };

    int res = FALSE;

    if (alpha_case < mMck_CASE_NUM) {
        u8 ofs = offset[alpha_case];
        if (c >= ofs && c <= ofs + 25) {
            res = TRUE;
        }
    }

    return res;
}

static int mMck_check_eof(u8* str, int pos) {
    int points = 0;

    if (pos < MAIL_BODY_LEN && mMck_cmp_sep_nes(str[pos - 1]) == TRUE) {
        points = 20;
    }

    return points;
}

static int mMck_check_key_get_hit_count(u8* str) {
    u8* sep;
    int i;
    int hit_count;
    int str_len;

    i = 0;
    hit_count = 0;
    str_len = mMck_strlen_new(str, MAIL_BODY_LEN - 3);

    if (str_len <= 0) {
        return 0;
    } else {
        /* There might be a goto here? */

        while (i <= str_len) {
            sep = str;
            if (mMck_cmp_key(sep)) {
                hit_count++;
            }

            str = mMck_search_sep(sep, str_len - i) + 1;
            i += (int)(str - sep); /* track current position */
        }

        return hit_count;
    }
}

/* Scores each "sentence" for correct capitalization.
   An uppercase character must appear within 3 characters after separators.
*/
static int mMck_check_key_type_A(u8* str, int pos) {
    int sz;
    int points = mMck_check_eof(str, pos);

    while (str != NULL && pos > 3) {
        /* Find the next separator (.?!) */
        while (mMck_cmp_sep_nes(*str) == FALSE && pos > 3) {
            str++;
            pos--;
        }

        /* Must be three characters or more remaining */
        if (pos > 3) {
            sz = 3;
            str++;
            pos--;

            /* Check that at least one of the characters after the separator is uppercase */
            while (TRUE) {
                if (mMck_check_alpha(*str, mMck_CASE_UPPER) == TRUE) {
                    break;
                }

                sz--;
                str++;
                pos--;

                if (sz <= 0) {
                    break;
                }
            }

            /* Add or subtract 10 points depending on whether uppercase letters were found */
            if (sz == 0) {
                points -= 10;
            } else {
                points += 10;
            }
        }
    }

    return points;
}

/* Add three (six in PAL) points for each "valid" three-character groupings */
static int mMck_check_key_type_B(u8* str, int len) {
#if VERSION == VER_GAFP01_00
    return mMck_check_key_get_hit_count(str) * 6;
#else
    return mMck_check_key_get_hit_count(str) * 3;
#endif
}

/*
  Add 20 points if the non-space character following a separator is correctly
  capitalized. If it is not, subtract 10 points. 0 points if no non-space
  characters are left following the separator.
*/
static int mMck_check_key_type_C(u8* str, int len) {
    int points = 0;

    for (len; len != 0; len--) {
        if (*str != CHAR_SPACE) {
            if (mMck_check_alpha(*str, mMck_CASE_UPPER) == TRUE) {
                points = 20;
            } else {
                points = -10;
            }

            break;
        }

        str++;
    }

    return points;
}

/*
  If three characters in a row are the same alpha (a-z/A-Z) character,
  subtract 50 points.
*/
static int mMck_check_key_type_D(u8* str, int len) {
    int points = 0;

    while (len > 2) {
        /* Check if the next character is alpha range (A-Za-z) */
        if (mMck_check_alpha(*str, mMck_CASE_LOWER) == TRUE || mMck_check_alpha(*str, mMck_CASE_UPPER) == TRUE) {
            if (str[0] == str[1] && str[0] == str[2]) {
                points = -50;
                break;
            }
        }

        len--;
        str++;
    }

    return points;
}

/*
  If the string is 20% or more spaces, add 20 points.
  Otherwise, subtract 20 points.
*/
static int mMck_check_key_type_E(u8* str, int len) {
    int spaces = 0;
    int non_spaces;
    int i;
    int points;

    for (i = len; i != 0; i--) {
        if (*str == CHAR_SPACE) {
            spaces++;
        }

        str++;
    }

    len = len - spaces;
    if (len > 0) {
        if ((spaces * 100) / len >= 20) {
            points = 20;
        } else {
            points = -20;
        }
    } else {
        points = -20;
    }

    return points;
}

/*
  Search for any run-on sentences. Run-on sentences are
  75 or more characters in a row without a separator (.?!).
  If a run-on sentence is found, subtract 150 points.
*/
static int mMck_check_key_type_F(u8* str, int len) {
    int sentence_len;
    int points = 0;

    while (len > 76) {
        if (mMck_cmp_sep_nes(*str) == TRUE) {
            sentence_len = 0;

            len--;
            str++;

            while (mMck_cmp_sep_nes(*str) == FALSE) {
                sentence_len++;

                if (sentence_len >= 75) {
                    break;
                }

                str++;
                len--;
            }

            if (sentence_len >= 75) {
                points = -150;
                break;
            }
        }

        len--;
        str++;
    }

    return points;
}

/*
  Subtract 20 points for every 32 characters in a row
  for which a space is not present.
*/
static int mMck_check_key_type_G(u8* str, int len) {
    int r_len = 32;
    u8 no_space = TRUE;
    int points = 0;

    for (len; len > 0; len--) {
        r_len--;

        if (no_space == TRUE) {
            if (*str == CHAR_SPACE) {
                no_space = FALSE;
            } else if (r_len == 0) {
                points += -20;
            }
        }

        if (r_len == 0) {
            r_len = 32;
            no_space = TRUE;
        }

        str++;
    }

    return points;
}

typedef int (*mMck_CHECK_PROC)(u8*, int);

extern int mMck_check_key_hit_nes(u8* str) {
    static mMck_CHECK_PROC check_proc[mMck_CHECK_KEY_TYPE_NUM] = { &mMck_check_key_type_A, &mMck_check_key_type_B,
                                                                   &mMck_check_key_type_C, &mMck_check_key_type_D,
                                                                   &mMck_check_key_type_E, &mMck_check_key_type_F,
                                                                   &mMck_check_key_type_G };

    int len;
    int points = 0;
    int i;

    if (str != NULL) {
        len = mMck_strlen_new(str, MAIL_BODY_LEN);

        for (i = 0; i < mMck_CHECK_KEY_TYPE_NUM; i++) {
            points += (*check_proc[i])(str, len);
        }
    }

    return points;
}
