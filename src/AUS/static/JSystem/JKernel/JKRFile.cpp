#include "types.h"
#include <dolphin/vi.h>
#include "JSystem/JKernel/JKRFile.h"
#include "JSystem/JUtility/JUTDbg.h"

// not sure if this matches, doesn't exist in mkdd
void JKRFile::read(void* address, s32 length, s32 offset) {
#line 34
    JUT_ASSERT(34, (length & 0x1f));
    while (writeData(address, length, offset) != length) {
        VIWaitForRetrace();
    }
}
