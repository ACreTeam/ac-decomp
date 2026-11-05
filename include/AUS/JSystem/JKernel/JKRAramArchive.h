#ifndef JKRARAMARCHIVE_H
#define JKRARAMARCHIVE_H

#include "JSystem/JKernel/JKRArchive.h"

inline bool JKRMountFixedAramArchive(JKRAramArchive* archive, const char* path) {
    return archive->mountFixed(path, JKRArchive::MOUNT_DIRECTION_HEAD);
}
inline void JKRUnmountFixedAramArchive(JKRAramArchive* archive) { archive->unmountFixed(); }

#endif
