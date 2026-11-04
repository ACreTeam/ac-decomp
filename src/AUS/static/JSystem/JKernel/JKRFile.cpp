#include "JSystem/JKernel/JKRFile.h"
#include "dolphin/vi.h"

#ifdef JSYSTEM_DEBUG
#include "JSystem/JUtility/JUTAssertion.h"
#endif

/* Empty space for aligning line numbers */

















/**
 * Nonmatched function. Unused in Animal Crossing.
 */
void JKRFile::read(void* data, s32 length, s32 ofs) {
#ifdef JSYSTEM_DEBUG
    if (!JKR_ISALIGNED(length, 32)) {
        JUTAssertion::showAssert(JUTAssertion::getSDevice(), __FILE__, __LINE__, "( length & 0x1f ) == 0");
    }
#endif

    while (true) {
        if (this->readData(data, length, ofs) == length) {
            return;
        }

        VIWaitForRetrace();
    }
}
