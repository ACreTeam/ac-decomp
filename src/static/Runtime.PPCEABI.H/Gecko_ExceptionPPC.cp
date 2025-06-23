#include "Runtime.PPCEABI.H/NMWException.h"

// NOTE: there is a bug in mwcc where any pure-asm function
// disables this optimization but doesn't reset it to be on
// original probably had an asm function in one of the headers
// above, but no idea which for now
#pragma peephole off

typedef struct ProcessInfo {
	__eti_init_info* exception_info;
	char* TOC;
	int active;
} ProcessInfo;

#define MAXFRAGMENTS 1
static ProcessInfo fragmentinfo[MAXFRAGMENTS];

int __register_fragment(struct __eti_init_info* info, char* TOC)
{
	ProcessInfo* f = fragmentinfo;
	int i;

	for (i = 0; i < MAXFRAGMENTS; i++, f++) {
		if (f->active == 0) {
			f->exception_info = info;
			f->TOC            = TOC;
			f->active         = 1;
			return i;
		}
	}

	return -1;
}

void __unregister_fragment(int fragmentID)
{
	ProcessInfo* f;

	if (fragmentID >= 0 && fragmentID < MAXFRAGMENTS) {
		f                 = &fragmentinfo[fragmentID];
		f->exception_info = 0;
		f->TOC            = 0;
		f->active         = 0;
	}
}
