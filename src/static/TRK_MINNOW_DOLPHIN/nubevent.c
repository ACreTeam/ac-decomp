#include "PowerPC_EABI_Support/MetroTRK/trk.h"

TRKEventQueue gTRKEventQueue;

/*
 * --INFO--
 * Address:	8021C0B4
 * Size:	00005C
 */
DSError TRKInitializeEventQueue()
{
	TRKInitializeMutex(&gTRKEventQueue);
	TRKAcquireMutex(&gTRKEventQueue);
	gTRKEventQueue.count   = 0;
	gTRKEventQueue.next    = 0;
	gTRKEventQueue.eventID = 0x100;
	TRKReleaseMutex(&gTRKEventQueue);
	return DS_NoError;
}

/*
 * --INFO--
 * Address:	8021C110
 * Size:	000024
 */
void TRKCopyEvent(TRKEvent* dstEvent, const TRKEvent* srcEvent)
{
	TRK_memcpy(dstEvent, srcEvent, sizeof(TRKEvent));
}

/*
 * --INFO--
 * Address:	8021C134
 * Size:	0000C0
 */
BOOL TRKGetNextEvent(TRKEvent* event)
{
	BOOL status = 0;
	TRKAcquireMutex(&gTRKEventQueue);
	if (0 < gTRKEventQueue.count) {
		TRKCopyEvent(event, &gTRKEventQueue.events[gTRKEventQueue.next]);
		gTRKEventQueue.count--;
		gTRKEventQueue.next++;
		if (gTRKEventQueue.next == 2)
			gTRKEventQueue.next = 0;

		status = 1;
	}
	TRKReleaseMutex(&gTRKEventQueue);
	return status;
}

/*
 * --INFO--
 * Address:	8021C1F4
 * Size:	0000E0
 */
DSError TRKPostEvent(TRKEvent* event)
{
	DSError ret = DS_NoError;
	int nextEventID;

	TRKAcquireMutex(&gTRKEventQueue);

	if (gTRKEventQueue.count == 2) {
		ret = DS_EventQueueFull;
	} else {
		nextEventID = (gTRKEventQueue.next + gTRKEventQueue.count) % 2;
		TRKCopyEvent(&gTRKEventQueue.events[nextEventID], event);
		gTRKEventQueue.events[nextEventID].eventID = gTRKEventQueue.eventID;
		gTRKEventQueue.eventID++;
		if (gTRKEventQueue.eventID < 0x100)
			gTRKEventQueue.eventID = 0x100;

		gTRKEventQueue.count++;
	}

	TRKReleaseMutex(&gTRKEventQueue);
	return ret;
}

/*
 * --INFO--
 * Address:	8021C2D4
 * Size:	000018
 */
void TRKConstructEvent(TRKEvent* event, int eventType)
{
	event->eventType = eventType;
	event->eventID   = 0;
	event->msgBufID  = -1;
}

/*
 * --INFO--
 * Address:	8021C2EC
 * Size:	000024
 */
void TRKDestructEvent(TRKEvent* event)
{
	TRKReleaseBuffer(event->msgBufID);
}
