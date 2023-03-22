#ifndef IRQMGR_H
#define IRQMGR_H

#include "types.h"
#include "dolphin/os/OSTime.h"
#include "dolphin/os/OSTimer.h"

#ifdef __cplusplus
extern "C" {
#endif

#define IRQ_RESET_NORMAL 0
#define IRQ_RESET_PRENMI 1
#define IRQ_RESET_DELAY  2

#define IRQMGR_MESSAGES_MAX 8

typedef struct {
  s16 type;
  s8 data[30];
} irqmgr_mesg_t;

typedef struct irqmgr_client_s {
  struct irqmgr_client_s* next;
  OSMessageQueue* msgQueue;
} irqmgr_client_t;

typedef struct {
  irqmgr_mesg_t msgRetrace;
  irqmgr_mesg_t msgPreNMI;
  irqmgr_mesg_t msgDelayPreNMI;
  OSMessageQueue _msgQueue;
  OSMessage _msgBuf[IRQMGR_MESSAGES_MAX];
  OSThread thread;
  irqmgr_client_t* clients;
  u8 prenmi;
  OSTime prenmi_time;
  OSTimer timer;
  OSTime retraceTime;
} irqmgr_t;

extern volatile int ResetStatus;
extern volatile OSTime ResetTime;

#ifdef __cplusplus
};
#endif

#endif
