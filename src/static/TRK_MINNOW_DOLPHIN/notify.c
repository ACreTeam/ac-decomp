
#include "PowerPC_EABI_Support/MetroTRK/trk.h"

inline DSError TRKDoNotifyStopped_Inline(TRKBuffer* msg, MessageCommandID cmd) {
    DSError err;

	if (msg->position >= 0x880) {
		err = DS_MessageBufferOverflow;
	} else {
		msg->data[msg->position++] = cmd;
		msg->length+=1;
	    err = 0;
	}
    return err;
}

DSError TRKDoNotifyStopped(MessageCommandID cmd)
{
	DSError err;
	int reqIdx;
	int bufIdx;
	TRKBuffer* msg;

	err = TRKGetFreeBuffer(&bufIdx, &msg);
	if (err == DS_NoError) {
		err = TRKDoNotifyStopped_Inline(msg, cmd);

		if (err == DS_NoError) {
			if ((u8)cmd == DSMSG_NotifyStopped) {
				TRKTargetAddStopInfo(msg);
			} else {
				TRKTargetAddExceptionInfo(msg);
			}
		}

		err = TRKRequestSend(msg, &reqIdx, 2, 3, 1);
		if (err == DS_NoError) {
			TRKReleaseBuffer(reqIdx);
		}
		TRKReleaseBuffer(bufIdx);
	}

	return err;
}
