#include "libultra/osThread.h"
#include "dolphin/os/OSThread.h"

BOOL osIsTerminatedThread(OSThread* t){
    return OSIsThreadTerminated(t);
}
