#undef DEBUG
#define DEBUG 1

#include "jaudio_NES/dsp_cardunlock.h"

#include "MSL_C/rand.h"
#include "jaudio_NES/ipldec.h"
#include "_mem.h"
#include "dolphin/os.h"
#include "dolphin/card.h"
#include "card/__card.h"

#define DATA_SCRAMBLE_R(data) (~(data ^ (data >> 7) ^ (data >> 15) ^ (data >> 23)))
#define DATA_SCRAMBLE_L(data) (~(data ^ (data << 7) ^ (data << 15) ^ (data << 23)))

/*
 * --INFO--
 * Address:	80008BE0
 * Size:	000038
 */
static u32 exnor_1st(u32 data, u32 rshift)
{
	for (u32 i = 0; i < rshift; ++i) {
		data = (data >> 1) | (DATA_SCRAMBLE_R(data) << 30) & 0x40000000;
	}
	return data;
}

/*
 * --INFO--
 * Address:	80008C20
 * Size:	000038
 */
static u32 exnor(u32 data, u32 lshift)
{
	for (u32 i = 0; i < lshift; ++i) {
		data = (data << 1) | (DATA_SCRAMBLE_L(data) >> 30) & 0x00000002;
	}
	return data;
}

/*
 * --INFO--
 * Address:	80008C60
 * Size:	00007C
 */
static u32 bitrev(u32 data)
{
	u32 wk;
	u32 i;
	u32 k = 0;
	u32 j = 1;

	wk = 0;
	for (i = 0; i < 32; ++i) {
		if (i > 0x0f) {
			if (i == 31) {
				wk |= (data & 1 << 31) >> 31;
			} else {
				wk |= (data & 1 << i) >> j;
				j += 2;
			}
		} else {
			wk |= (data & 1 << i) << (31 - i - k);
			k += 1;
		}
	}
	return wk;
}

/*
 * --INFO--
 * Address:	80008CE0
 * Size:	00017C
 */
static s32 ReadArrayUnlock(s32 chan, u32 data, void* rbuf, s32 length, BOOL mode)
{
	ASSERTLINE(217, 0 <= chan && chan < 2);
	CARDControl* card = &__CARDBlock[chan];

	if (!EXISelect(chan, 0, 4))
		return CARD_RESULT_NOCARD;

	data &= 0xFFFFF000;
	u8 cmd[5];
	memset(cmd, 0, sizeof(cmd));
	cmd[0] = 0x52;
	if (mode == FALSE) {
		cmd[1] = data >> 29 & 0x03;
		cmd[2] = data >> 21 & 0xff;
		cmd[3] = data >> 19 & 0x03;
		cmd[4] = data >> 12 & 0x7f;
	} else {
		cmd[1] = data >> 24 & 0xff;
		cmd[2] = data >> 16 & 0xff;
	}

	BOOL err = FALSE;
	err |= !EXIImmEx(chan, cmd, sizeof(cmd), EXI_WRITE);
	err |= !EXIImmEx(chan, (void*)(((CARDID*)card->workArea)+1), card->latency, EXI_WRITE);
	err |= !EXIImmEx(chan, rbuf, length, EXI_READ);
	err |= !EXIDeselect(chan);
	return err ? CARD_RESULT_NOCARD : CARD_RESULT_READY;
}

/*
 * --INFO--
 * Address:	80008E60
 * Size:	000044
 */
static u32 GetInitVal()
{
	srand(OSGetTick());
	u32 val = 0x7fec8000;
	val |= rand();
	val &= 0xFFFFF000;
	return val;
}

/*
 * --INFO--
 * Address:	80008EC0
 * Size:	00008C
 */
static u32 DummyLen()
{
	u32 lshift = 1;
	u32 i      = 0;

	srand(OSGetTick());
	int result = (rand() & 0x1f) + 1;
	for (; result < 4 && i < 10; i++) {
		result = OSGetTick() << lshift;
		if (++lshift > 0x10)
			lshift = 1;
		srand(result);
		result = (rand() & 0x1f) + 1;
	}

    if (result < 4) {
        result = 4;
    }

	return result;
}

static void InitCallback(void* dspTask);
static void DoneCallback(void* dspTask);

struct CARDDecodeParameters {
	u8* inputAddr;   // _00
	u32 inputLength; // _04
	u32 aramAddr;    // _08
	u8* outputAddr;  // _0C
};

/*
 * --INFO--
 * Address:	80008F60
 * Size:	0002B0
 */
int __CARDUnlock(int chan, u8 flashID[12])
{
	u32 Ans1, Ans2;
	u8 rbuf[64];
    u32 para1A;
    u32 para1B;
    u32 para2A;
    u32 para2B;
    
    // The nonsense
	CARDControl* card           = &__CARDBlock[chan];
	DSPTaskInfo* task           = &card->task;
	CARDDecodeParameters* param = (CARDDecodeParameters*)card->workArea;
	u8* input                   = (u8*)param + sizeof(CARDDecodeParameters);
	input                       = (u8*)OSRoundUp32B(input);
	u8* output                  = input + 32;
    
	u32 data;
	s32 dummy;
	s32 rlen;

    u32 shift;
	u32 wk;

	data  = GetInitVal();
	dummy = DummyLen();
	rlen  = dummy;
	if (ReadArrayUnlock(chan, data, rbuf, rlen, FALSE) < CARD_RESULT_READY)
		return CARD_RESULT_NOCARD;

	// TODO: Pikmin uses `card->formatStep`, but every other
	// decomp uses `card->scramble`. What's up with that?

	shift            = dummy * 8 + 1;
	wk               = exnor_1st(data, shift);
	card->formatStep = wk | (DATA_SCRAMBLE_R(wk) << 31 & 0x80000000);
	card->formatStep = bitrev(card->formatStep);

	data  = 0;
	dummy = DummyLen();
	rlen  = dummy + 20;
	if (ReadArrayUnlock(chan, data, rbuf, rlen, TRUE) < CARD_RESULT_READY)
		return CARD_RESULT_NOCARD;

	para1A = *(u32*)(rbuf + 0);
	para1B = *(u32*)(rbuf + 4);
	Ans1       = *(u32*)(rbuf + 8);
	para2A = *(u32*)(rbuf + 12);
	para2B = *(u32*)(rbuf + 16);
	para1A ^= card->formatStep;

	shift            = 32;
	wk               = exnor(card->formatStep, shift);
	card->formatStep = wk | (DATA_SCRAMBLE_L(wk) >> 31 & 0x00000001);
	para1B ^= card->formatStep;

	shift            = 32;
	wk               = exnor(card->formatStep, shift);
	card->formatStep = wk | (DATA_SCRAMBLE_L(wk) >> 31 & 0x00000001);
	Ans1 ^= card->formatStep;

	shift            = 32;
	wk               = exnor(card->formatStep, shift);
	card->formatStep = wk | (DATA_SCRAMBLE_L(wk) >> 31 & 0x00000001);
	para2A ^= card->formatStep;

	shift            = 32;
	wk               = exnor(card->formatStep, shift);
	card->formatStep = wk | (DATA_SCRAMBLE_L(wk) >> 31 & 0x00000001);
	para2B ^= card->formatStep;

	shift            = dummy * 8;
	wk               = exnor(card->formatStep, shift);
	card->formatStep = wk | (DATA_SCRAMBLE_L(wk) >> 31 & 0x00000001);

	shift            = 32 + 1;
	wk               = exnor(card->formatStep, shift);
	card->formatStep = wk | (DATA_SCRAMBLE_L(wk) >> 31 & 0x00000001);

	*(u32*)(input + 0) = para2A;
	*(u32*)(input + 4) = para2B;

	param->inputAddr   = input;
	param->inputLength = 8;
	param->outputAddr  = output;
	param->aramAddr    = 0;

	DCFlushRange(input, 8);
	DCInvalidateRange(output, 4);
	DCFlushRange(param, sizeof(CARDDecodeParameters));

	Jac_DSPcardDecodeAsync(task, param, DoneCallback);

	*(u32*)(flashID + 0) = para1A;
	*(u32*)(flashID + 4) = para1B;
	*(u32*)(flashID + 8) = Ans1;

	return CARD_RESULT_READY;
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000C4
 */
static void InitCallback(void* dspTask)
{
}

/*
 * --INFO--
 * Address:	80009220
 * Size:	0001E0
 */
static void DoneCallback(void* dspTask)
{
	DSPTaskInfo* task = (DSPTaskInfo*)dspTask;

	u8 rbuf[64];
	u32 Ans2;
	u8 status;

	s32 chan;
	CARDControl* card;
	for (chan = 0; chan < 2; ++chan) {
		card = &__CARDBlock[chan];
		if (&card->task == task) {
			break;
		}
	}
	ASSERTLINE(549, 0 <= chan && chan < 2);

	// The nonsense
	CARDDecodeParameters* param = (CARDDecodeParameters*)card->workArea;
	u8* input                   = (u8*)param + sizeof(CARDDecodeParameters);
	input                       = (u8*)OSRoundUp32B(input);
	u8* output                  = input + 32;
	Ans2                        = *(u32*)output;

	// TODO: Pikmin uses `card->formatStep`, but every other
	// decomp uses `card->scramble`. What's up with that?

	s32 dummy;
	s32 rlen;
	u32 data;

	dummy = DummyLen();
	rlen  = dummy;
	data  = (Ans2 ^ card->formatStep) & 0xffff0000;
	if (ReadArrayUnlock(chan, data, rbuf, rlen, TRUE) < CARD_RESULT_READY) {
		EXIUnlock(chan);
		__CARDMountCallback(chan, CARD_RESULT_NOCARD);
		return;
	}

	u32 shift;
	u32 wk, wk1;

	shift            = (rlen + 4 + card->latency) * 8 + 1;
	wk               = exnor(card->formatStep, shift);
	card->formatStep = wk | ((DATA_SCRAMBLE_L(wk) >> 31) & 0x00000001);

	dummy = DummyLen();
	rlen  = dummy;
	data  = ((Ans2 << 16) ^ card->formatStep) & 0xffff0000;
	if (ReadArrayUnlock(chan, data, rbuf, rlen, TRUE) < CARD_RESULT_READY) {
		EXIUnlock(chan);
		__CARDMountCallback(chan, CARD_RESULT_NOCARD);
		return;
	}
	s32 result = __CARDReadStatus(chan, &status);
	if (!EXIProbe(chan)) {
		EXIUnlock(chan);
		__CARDMountCallback(chan, CARD_RESULT_NOCARD);
		return;
	}
	if (result == CARD_RESULT_READY && !(status & 0x40)) {
		EXIUnlock(chan);
		result = CARD_RESULT_IOERROR;
	}
	__CARDMountCallback(chan, result);
}
