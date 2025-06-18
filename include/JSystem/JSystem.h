#ifndef JSYSTEM_H
#define JSYSTEM_H

#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JKernel/JKRFileLoader.h"
#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/JMacro.h"
#include "JSystem/JUtility/JUTException.h"

// probably a better place to put these
static inline void* JKRGetResource(const char* resourceName) {
    return JKRFileLoader::getGlbResource(resourceName);
}

static inline void JKRRemoveResource(void* resource) {
    JKRFileLoader::removeResource(resource, nullptr);
}

static inline BOOL JKRDetachResource(void* resource) {
    return JKRFileLoader::detachResource(resource, nullptr);
}

static inline void* JKRGetResourceEntry_byName(u32 root_name, const char* res_name, JKRArchive* archive) {
    return archive->findTypeResource(root_name, res_name);
}

#endif
