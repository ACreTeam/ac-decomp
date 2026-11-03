#include "dolphin/OSRtcPriv.h"
#include "dolphin/os.h"
#include "dolphin/vi.h"
#include "dolphin/hw_regs.h"

volatile u8 DAT_800030e2 : 0x800030e2;
typedef struct Unk {
  u8 pad[0x24];
  u32 resetCode;
} Unk;
volatile Unk DAT_cc003000 : 0xcc003000;

typedef struct Unk2 {
  u16 _0;
  u16 _2;
} Unk2;

volatile Unk2 DAT_cc002000 : 0xcc002000;

typedef struct OSResetQueue {
  OSResetFunctionInfo* first;
  OSResetFunctionInfo* last;
} OSResetQueue;

static OSResetQueue ResetFunctionQueue;
static u32 bootThisDol;

void OSRegisterResetFunction(OSResetFunctionInfo* func) {
  OSResetFunctionInfo* tmp;
  OSResetFunctionInfo* iter;

  for (iter = ResetFunctionQueue.first; iter && iter->priority <= func->priority; iter = iter->next)
    ;

  if (iter == NULL) {
    tmp = ResetFunctionQueue.last;
    if (tmp == NULL) {
      ResetFunctionQueue.first = func;
    } else {
      tmp->next = func;
    }
    func->prev = tmp;
    func->next = NULL;
    ResetFunctionQueue.last = func;
    return;
  }

  func->next = iter;
  tmp = iter->prev;
  iter->prev = func;
  func->prev = tmp;
  if (tmp == NULL) {
    ResetFunctionQueue.first = func;
    return;
  }
  tmp->next = func;
}

BOOL __OSCallResetFunctions(BOOL arg0) {
  OSResetFunctionInfo *info;
  s32 err = 0;

  for (info = ResetFunctionQueue.first; info != NULL && err == 0; info = info->next)
  {
    err |= !info->func(arg0);
  }
  err |= !__OSSyncSram() ;
  if (err)
  {
    return 0;
  }
  return 1;
}

asm void Reset(register s32 resetCode) {
  // clang-format off
    nofralloc
    b lbl_8038315C
lbl_80383140:
    mfspr r8, HID0
    ori r8, r8, 8
    mtspr HID0, r8
    isync
    sync
    nop
    b lbl_80383160
lbl_8038315C:
    b lbl_8038317C
lbl_80383160:
    mftb r5, 268
lbl_80383164:
    mftb r6, 268
    subf r7, r5, r6
    cmplwi r7, 0x1124
    blt lbl_80383164
    nop
    b lbl_80383180
lbl_8038317C:
    b lbl_8038319C
lbl_80383180:
    lis r8, 0xCC003000@h
    ori r8, r8, 0xCC003000@l
    li r4, 3
    stw r4, 0x24(r8)
    stw r3, 0x24(r8)
    nop
    b lbl_803831A0
lbl_8038319C:
    b lbl_803831A8
lbl_803831A0:
    nop
    b lbl_803831A0
lbl_803831A8:
    b lbl_80383140
  // clang-format on
}

OSThreadQueue __OSActiveThreadQueue : (OS_BASE_CACHED | 0x00DC);

static void KillThreads(void) {
  OSThread* thread;
  OSThread* next;

  for (thread = __OSActiveThreadQueue.head; thread; thread = next) {
    next = thread->linkActive.next;
    switch (thread->state) {
    case 1:
    case 4:
      OSCancelThread(thread);
      break;
    default:
      break;
    }
  }
}

void __OSDoHotReset(u32 arg0) {
  OSDisableInterrupts();
  __VIRegs[1] = 0;
  ICFlashInvalidate();
  Reset(arg0 * 8);
}

void OSResetSystem(int reset, u32 resetCode, BOOL forceMenu)
{
  BOOL rc;
  BOOL disableRecalibration;
  u32 unk[3]; // dumb compiler

  OSDisableScheduler();
  __OSStopAudioSystem();

  if (reset == OS_RESET_SHUTDOWN || (reset == OS_RESET_RESTART && bootThisDol != 0))
  {
    disableRecalibration = __PADDisableRecalibration(TRUE);
  }

  while (!__OSCallResetFunctions(FALSE))
  {
    ;
  }

  if (reset == OS_RESET_HOTRESET && forceMenu)
  {
    OSSram *sram;

    sram = __OSLockSram();
    sram->flags |= 0x40;
    __OSUnlockSram(TRUE);

    while (!__OSSyncSram())
    {
      ;
    }
  }

  OSDisableInterrupts();
  __OSCallResetFunctions(TRUE);
  LCDisable();
  if (reset == OS_RESET_HOTRESET)
  {
    __OSDoHotReset(resetCode);
  }
  else if (reset == OS_RESET_RESTART)
  {
    if ((*(u32 *)OSPhysicalToCached(0x30EC) = bootThisDol) != 0)
    {
      __PADDisableRecalibration(disableRecalibration);
    }
    KillThreads();
    OSEnableScheduler();
    __OSReboot(resetCode, forceMenu);
  }

  KillThreads();
  memset(OSPhysicalToCached(0x40), 0, 0xCC - 0x40);
  memset(OSPhysicalToCached(0xD4), 0, 0xE8 - 0xD4);
  memset(OSPhysicalToCached(0xF4), 0, 0xF8 - 0xF4);
  memset(OSPhysicalToCached(0x3000), 0, 0xC0);
  memset(OSPhysicalToCached(0x30C8), 0, 0xD4 - 0xC8);
  memset(OSPhysicalToCached(0x30E2), 0, 1);

  __PADDisableRecalibration(disableRecalibration);
}

u32 OSGetResetCode(void) {
  if (DAT_800030e2 != 0) {
    return 0x80000000;
  }
  return ((DAT_cc003000.resetCode & ~7) >> 3);
}
