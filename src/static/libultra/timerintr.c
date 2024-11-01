#include "libultra/libultra.h"

OSTimer __osBaseTimer;
OSTimer* __osTimerList = &__osBaseTimer;

void __osTimerServicesInit(void){
	__osTimerList->next = __osTimerList->prev  = __osTimerList;
	__osTimerList->value = 0;
	__osTimerList->interval = 0;
	__osTimerList->mq = NULL;
	__osTimerList->msg = 0;
}