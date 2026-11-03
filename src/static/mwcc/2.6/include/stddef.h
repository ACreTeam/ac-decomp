#ifndef _STDDEF_H_
#define _STDDEF_H_

#include <cstddef>

#define membersize(type, member) (sizeof(((type*)0)->member))

#endif
