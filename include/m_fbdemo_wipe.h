#ifndef M_FBDEMO_WIPE_H
#define M_FBDEMO_WIPE_H

#include "types.h"
#include "m_fbdemo.h"
#include "m_fbdemo_wipe1.h"
#include "m_fbdemo_fade.h"
#include "m_fbdemo_triforce.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef union fbdemo_wipe_union {
  fbdemo_wipe1 fbdemo_wipe1;
  fbdemo_triforce fbdemo_triforce;
  fbdemo_fade fbdemo_fade;
} fbdemo_wipe_u;

typedef fbdemo_wipe_u* (*FBDEMO_INIT_PROC)(fbdemo_wipe_u*);
typedef void (*FBDEMO_CLEANUP_PROC)(fbdemo_wipe_u*);
typedef void (*FBDEMO_MOVE_PROC)(fbdemo_wipe_u*, int);
typedef void (*FBDEMO_DRAW_PROC)(fbdemo_wipe_u*, Gfx**);
typedef void (*FBDEMO_STARTUP_PROC)(fbdemo_wipe_u*);
typedef void (*FBDEMO_SETTYPE_PROC)(fbdemo_wipe_u*, int);
typedef void (*FBDEMO_SETCOLOR_PROC)(fbdemo_wipe_u*, u32);
typedef int (*FBDEMO_ISFINISHED_PROC)(fbdemo_wipe_u*);

typedef struct {
  FBDEMO_INIT_PROC init_proc;
  FBDEMO_CLEANUP_PROC cleanup_proc;
  FBDEMO_MOVE_PROC move_proc;
  FBDEMO_DRAW_PROC draw_proc;
  FBDEMO_STARTUP_PROC startup_proc;
  FBDEMO_SETTYPE_PROC settype_proc;
  FBDEMO_SETCOLOR_PROC setcolor_proc;
  void* unused_proc; // unknown
  FBDEMO_ISFINISHED_PROC isfinished_proc;
} fbdemo_wipe_proc_c;

typedef struct {
  fbdemo_wipe_u wipe_data;
  int wipe_type;
  fbdemo_wipe_proc_c wipe_procs;
} fbdemo_wipe;

#ifdef __cplusplus
}
#endif

#endif
