#include "TRK/trk.h"

DSError TRKMessageSend(MessageBuffer* msg)
{
	DSError writeErr = TRKWriteUARTN(&msg->data, msg->length);
	return DS_NoError;
}
