#include "types.h"
#ifndef _JSYSTEM_JUTILITY_JUTDBG_H
#define _JSYSTEM_JUTILITY_JUTDBG_H

// Get rid of this file?

#include <JSystem/JUtility/JUTAssert.h>
#include <JSystem/JUtility/JUTException.h>

// Panic functions
#define JUT_PANIC(MSG) \
  JUTException::panic(__FILE__, __LINE__, MSG);
#define JUT_PANIC_F(...) \
  JUTException::panic_f(__FILE__, __LINE__, __VA_ARGS__);

#endif