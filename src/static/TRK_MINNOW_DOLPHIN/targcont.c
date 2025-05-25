#include "dolphin/trk.h"

/*
 * --INFO--
 * Address:	802207B8
 * Size:	000034
 */

unsigned int TRKTargetContinue(void)
{
	TRKTargetSetStopped(0);
	UnreserveEXI2Port();
	TRKSwapAndGo();
	ReserveEXI2Port();
	return 0;
}
