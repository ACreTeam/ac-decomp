#include "sys_romcheck.h"

#include "dolphin/dvd.h"
#include "m_nmibuf.h"

extern void sys_romcheck() {
  if (DVDGetCurrentDiskID()->gameVersion >= SYS_ROMCHECK_DEBUG_ROM_VERSION) {
    APPNMI_ZURUMODE2_SET();
  }
}
