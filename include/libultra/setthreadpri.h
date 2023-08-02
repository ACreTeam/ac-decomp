#ifndef SETTHREADPRI_H
#define SETTHREADPRI_H

#include "types.h"
#include "libultra/osThread.h"

#ifdef __cplusplus
 extern "C" {
#endif

void osSetThreadPri(OSThread* thread, OSPri priority);


#ifdef __cplusplus
 }
#endif


#endif