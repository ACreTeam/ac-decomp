#include "PowerPC_EABI_Support/MetroTRK/trk.h"

extern TRKEventQueue gTRKEventQueue;
extern TRKState gTRKState;

/*
 * --INFO--
 * Address:	8021BF4C
 * Size:	000028
 */
void TRKHandleRequestEvent(TRKEvent* event)
{
	TRKBuffer* buffer = TRKGetBuffer(event->msgBufID);
	TRKDispatchMessage(buffer);
}

/*
 * --INFO--
 * Address:	8021BF74
 * Size:	000020
 */
void TRKHandleSupportEvent(TRKEvent* event)
{
	TRKTargetSupportRequest();
}

/*
 * --INFO--
 * Address:	8021BF94
 * Size:	00002C
 */
void TRKIdle()
{
	if (TRKTargetStopped() == FALSE) {
		TRKTargetContinue();
	}
}

/*
 * --INFO--
 * Address:	8021BFC0
 * Size:	0000F4
 */
void TRKNubMainLoop(void)
{
	TRKEvent event;
	BOOL isShutdownRequested;
	BOOL isNewInput;

	isShutdownRequested = FALSE;
	isNewInput          = FALSE;
	while (isShutdownRequested == FALSE) {
		if (TRKGetNextEvent(&event) != FALSE) {
			isNewInput = FALSE;

			switch (event.eventType) {
			case NUBEVENT_Null:
				break;

			case NUBEVENT_Request:
				TRKHandleRequestEvent(&event);
				break;

			case NUBEVENT_Shutdown:
				isShutdownRequested = TRUE;
				break;

			case NUBEVENT_Breakpoint:
			case NUBEVENT_Exception:
				TRKTargetInterrupt(&event);
				break;

			case NUBEVENT_Support:
				TRKHandleSupportEvent(&event);
				break;
			}

			TRKDestructEvent(&event);
			continue;
		}

		if ((isNewInput == FALSE) || (*(u8*)gTRKInputPendingPtr != '\0')) {
			isNewInput = TRUE;
			TRKGetInput();
			continue;
		}

		TRKIdle();
		isNewInput = FALSE;
	}
}
