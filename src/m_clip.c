#include "m_common_data.h"

extern void clip_clear(void) {
    int i;
    void** clip = (void**)&common_data.clip;

    for (i = 0; i < sizeof(Clip_c) / sizeof(void*) - 1; i++) {
        *clip++ = NULL;
    }
}
