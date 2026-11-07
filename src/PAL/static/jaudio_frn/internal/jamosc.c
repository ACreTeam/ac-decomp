#include "jaudio_NES/jamosc.h"
#include "jaudio_NES/jammain_2.h"

s16 VIB_TABLE[] = { 0, 0, 0, 0, 20, 0x7fff, 0, 20, 0, 0, 0x14, 0xc000, 0, 20, 0, 13, 0, 1 };
s16 TRE_TABLE[] = { 0, 0, 0x7fff, 0, 20, 0, 0, 20, 0x8001, 0, 0x14, 0, 0, 0x14, 0x7fff, 13, 0, 1 };
s16 REL_TABLE[] = { 0, 10, 0, 15, 1, 0 };

Osc_ VIBRATO_DEF  = { 1, 0.8f, VIB_TABLE, VIB_TABLE, 0.0f, 1.0f };
Osc_ TREMOLO_DEF  = { 0, 1.0f, TRE_TABLE, TRE_TABLE, 0.0f, 1.0f };
Osc_ ENVELOPE_DEF = { 0, 1.0f, NULL, REL_TABLE, 1.0f, 0.0f };

s16 ADS_TABLE[] = { 0, 0, 0x7fff, 0, 0, 0x7fff, 0, 0, 0, 14, 0, 0 };
Osc_ ADSR_DEF   = { 0, 1.0f, NULL, NULL, 1.0f, 0.0f };
Osc_ OSC_DEF    = { 0, 1.0f, NULL, REL_TABLE, 1.0f, 0.0f };

/*
 * --INFO--
 * Address:	80014CA0
 * Size:	000090
 * Note: Equivalent to `JASTrack::updateOscParam` in later JAudio.
 */
void Osc_Update_Param(seqp_* track, u8 id, f32 val)
{
	switch (id) {
	case 6:
		track->oscillators[0].width = val;
		break;
	case 7:
		track->oscillators[0].rate = val;
		break;
	case 8:
		track->oscillators[0].vertex = val;
		break;
	case 9:
		track->oscillators[1].width = val;
		break;
	case 10:
		track->oscillators[1].rate = val;
		break;
	case 11:
		track->oscillators[1].vertex = val;
		break;
	}
}

/*
 * --INFO--
 * Address:	80014D40
 * Size:	00003C
 */
void Osc_Setup_Vibrato(seqp_* track, u8 id)
{
	track->oscillators[id] = VIBRATO_DEF;
}

/*
 * --INFO--
 * Address:	80014D80
 * Size:	00003C
 */
void Osc_Setup_Tremolo(seqp_* track, u8 id)
{
	track->oscillators[id] = TREMOLO_DEF;
}

/*
 * --INFO--
 * Address:	80014DC0
 * Size:	000064
 * Note: Equivalent to `JASTrack::oscSetupSimple` in later JAudio.
 */
void Osc_Setup_Simple(seqp_* track, u8 id)
{
	switch (id) {
	case 0:
		Osc_Setup_Vibrato(track, 1);
		break;
	case 1:
		Osc_Setup_Tremolo(track, 0);
		break;
	case 2:
		Osc_Setup_Tremolo(track, 1);
		break;
	}
}

/*
 * --INFO--
 * Address:	80014E40
 * Size:	000010
 */
void Osc_Clear_Overwrite(seqp_* track)
{
	track->oscillatorRouting[0] = 15;
	track->oscillatorRouting[1] = 15;
}

/*
 * --INFO--
 * Address:	80014E60
 * Size:	00004C
 */
void Osc_Init_Env(seqp_* track)
{
	track->oscillators[0] = ENVELOPE_DEF;

	Osc_Clear_Overwrite(track);
}

/*
 * --INFO--
 * Address:	80014EC0
 * Size:	000094
 */
void Osc_Setup_SimpleEnv(seqp_* track, u8 id, u32 val)
{
	switch (id) {
	case 0:
		track->oscillators[0]                 = ENVELOPE_DEF;
		track->oscillators[0].attackVecOffset = (s16*)Jam_OfsToAddr(track, val);
		break;

	case 1:
		track->oscillators[0].releaseVecOffset = (s16*)Jam_OfsToAddr(track, val);
		break;
	}
}

/*
 * --INFO--
 * Address:	80014F60
 * Size:	0000B0
 */
void Osc_Setup_ADSR(seqp_* track, s16* addr)
{
	track->oscillators[0] = ADSR_DEF;

	track->oscillators[0].attackVecOffset  = track->adsTable;
	track->oscillators[0].releaseVecOffset = track->relTable;

	for (int i = 0; i < 12; i++) {
		track->adsTable[i] = ADS_TABLE[i];
	}

	for (int i = 0; i < 6; i++) {
		track->relTable[i] = REL_TABLE[i];
	}

	track->adsTable[1] = addr[0];
	track->adsTable[4] = addr[1];
	track->adsTable[7] = addr[2];
	track->adsTable[8] = addr[3];
	track->relTable[1] = addr[4];
}

/*
 * --INFO--
 * Address:	80015020
 * Size:	00010C
 */
void Osc_Setup_Full(seqp_* track, u8 flag, u32 offs1, u32 offs2)
{
    u8 idx;
    u8 a;
    u8 b;
    u8 c;
    u8 d;

    idx = (flag >> 4) & 0x1;
    a   = flag & 0xF;
    b   = flag & 0x40;
    c   = flag & 0x20;
    d   = flag & 0x80;
	if (d) {
		track->oscillators[idx] = ENVELOPE_DEF;

		track->oscillators[idx].mode = a;
		switch (a) {
		case 1:
			track->oscillators[idx].vertex = 1.0f;
			break;
		}
	}

	if (b) {
		if (offs1 == 0) {
			track->oscillators[idx].attackVecOffset = NULL;
		}
		track->oscillators[idx].attackVecOffset = (s16*)Jam_OfsToAddr(track, offs1);
	}

	if (c) {
		if (offs2 == 0) {
			track->oscillators[idx].releaseVecOffset = REL_TABLE;
		}
		track->oscillators[idx].releaseVecOffset = (s16*)Jam_OfsToAddr(track, offs2);
	}
}
