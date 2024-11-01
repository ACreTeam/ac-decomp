#include "m_diary.h"

#include "libultra/libultra.h"
#include "m_lib.h"
#include "m_font.h"

extern int mDi_strlen(u8* str, int max_len, u8 end_char) {
    int i;

    str += max_len - 1;
    for (i = max_len; i != 0; i--) {
        if (*str != end_char) {
            return i;
        }
        str--;
    }

    return 0;
}

static void mDi_clear_diary(mDi_entry_c* entry_p) {
    bzero(entry_p->text, sizeof(entry_p->text));
    mem_clear(entry_p->text, sizeof(entry_p->text), CHAR_SPACE);
}

extern void mDi_init_diary(mDi_entry_c* entry_p) {
    mDi_clear_diary(entry_p);
}
