#ifndef _STDDEF_H_
#define _STDDEF_H_

#define offsetof(type, member)	((size_t) &(((type *) 0)->member))
#define membersize(type, member) (sizeof(((type*)0)->member))

#ifndef _SIZE_T_DEF
#define _SIZE_T_DEF
typedef unsigned long size_t;
#endif

#ifndef NULL
#define NULL 0L
#endif

#endif
