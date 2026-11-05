#ifndef JUTFSFONT_H
#define JUTFSFONT_H

#include "JSystem/JUtility/JUTFont.h"
#include "JSystem/JKernel/JKRFileLoader.h"

class JUTFsFont : public JUTResFont {
public:
    JUTFsFont(const char* path, JKRHeap* heap)
        : JUTResFont(reinterpret_cast<const ResFONT*>(JKRFileLoader::getGlbResource(path)), heap) {}
    virtual ~JUTFsFont();
};

#endif
