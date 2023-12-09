#include "executor.h"

#include "dolphin/os/__ppc_eabi_init.h"
#include "dolphin/os.h"
#include "dolphin/os/OSContext.h"
#include "terminal.h"
#include "main.h"

BOOL construct_skip;

void _prolog() {
    voidfunctionptr *constructor;

    /* call static initializers */
    if (!construct_skip) {
        for (constructor = _ctors; *constructor; constructor++) {
            (*constructor)();
        }
    }
    foresta_main();
}

void _epilog() {
  voidfunctionptr *destructor;

  /* call static destructors */
  for (destructor = _dtors; *destructor; destructor++) {
    (*destructor)();
  }
}

void _unresolved() {
  u32 i;
  u32* p;

  OSReport(VT_COL(RED, WHITE) "\nError: A called an unlinked function.\n");
  OSReport("Address:      Back Chain    LR Save\n");

  for (i = 0, p = (u32*)OSGetStackPointer(); p && (u32)p != 0xffffffff && i++ < 16; p = (u32*)*p) {
    OSReport("0x%08x:   0x%08x    0x%08x\n", p, p[0], p[1]);
  }

  OSReport("\n" VT_RST "\n");
}