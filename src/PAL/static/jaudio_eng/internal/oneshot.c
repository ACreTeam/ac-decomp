#include "jaudio_NES/oneshot.h"
#include "jaudio_NES/bankdrv.h"
#include "jaudio_NES/audiostruct.h"
#include "jaudio_NES/driverinterface.h"
#include "jaudio_NES/tables.h"
#include "jaudio_NES/bankread.h"
#include "jaudio_NES/waveread.h"
#include "jaudio_NES/connect.h"
#include "jaudio_NES/dspdriver.h"
#include "jaudio_NES/rate.h"
#include "jaudio_NES/bx.h"

static int Jesus1Shot_Update(jc_*, JCSTATUS);

static s16 OSC_REL[] = { 1, 10, 0, 15 };

Osc_ PERC_ENV    = { 0, 1.0f, 0, 0, 1.0f, 0 };
Osc_ OSC_ENV     = { 0, 1.0f, 0, OSC_REL, 1.0f, 0 };
u8 polys_table[] = { 0, 1, 2, 3, 4, 5, 6, 8, 10, 12, 14, 16, 20, 24, 28, 32 };

/* Keep helper code in separate contributions for the Australian function order. */
#include "oneshot_helpers.inc"
/*
 * --INFO--
 * Address:	80015BC0
 * Size:	000070
 */
void Init_1shot(jcs_* jcs, u32 id)
{
	if (jcs->chanCount != 0) {
		FixReleaseChannelAll(jcs);
	}
	InitJcs(jcs);
	FixAllocChannel(jcs, id);
	if (id == 0) {
		jcs->voiceStealingMode = 0;
	} else {
		jcs->voiceStealingMode = 1;
	}
}

/*
 * --INFO--
 * Address:	80015C40
 * Size:	00003C
 */
void Stop_1Shot(jc_* jc)
{
	if (jc->dspChannel == 0) {
		Jesus1Shot_Update(jc, JCSTAT_Unk6);
	} else {
		Jesus1Shot_Update(jc, JCSTAT_Unk0);
	}
}

/*
 * --INFO--
 * Address:	80015C80
 * Size:	000040
 */
void Stop_1Shot_R(jc_* jc, u16 id)
{
	if (jc->dspChannel == 0) {
		Jesus1Shot_Update(jc, JCSTAT_Unk6);
	} else {
		jc->mOscBuffers[0].releaseParam = id;
		Jesus1Shot_Update(jc, JCSTAT_Unk0);
	}
}

/*
 * --INFO--
 * Address:	80015CC0
 * Size:	00006C
 */
void AllStop_1Shot(jcs_* jcs)
{
	List_CountChannel(&jcs->freeChannels);
	List_CountChannel(&jcs->activeChannels);
	List_CountChannel(&jcs->releasingChannels);
	List_CountChannel(&jcs->waitingChannels);

	jc_* jc = jcs->activeChannels;
	jc_* next;
	jc_** REF_jc = &jc;
	while (jc) {
		next = (jc_*)jc->mNext;
		Stop_1Shot(jc);
		jc = next;
	}
}

/*
 * --INFO--
 * Address:	80015D40
 * Size:	00006C
 * Note: Equivalent to `JASChannel::sweepProc` in later JAudio.
 */
static BOOL Extra_Update(jc_* jc, JCSTATUS status)
{
	if (jc->pitchSweepSteps != 0) {
		f32 pitch = jc->targetPitch;
		pitch -= jc->currentPitch;
		pitch /= jc->pitchSweepSteps;
		jc->currentPitch += pitch;
		jc->pitchSweepSteps--;

		if (jc->pitchSweepSteps == 0) {
			jc->pitchSweepUpdater = NULL;
		}
	}
	return FALSE;
}

/*
 * --INFO--
 * Address:	80015DC0
 * Size:	000030
 */
void SetPitchTarget_1Shot(jc_* jc, f32 pitch, u32 steps)
{
	if (steps == 0) {
		jc->currentPitch      = pitch;
		jc->pitchSweepUpdater = NULL;
		return;
	}

	jc->targetPitch       = pitch;
	jc->pitchSweepSteps   = steps;
	jc->pitchSweepUpdater = Extra_Update;
}

/*
 * --INFO--
 * Address:	80015E00
 * Size:	000090
 * Note: (Roughly) Equivalent to `JASChannel::setKeySweepTarget` in later JAudio.
 */
void SetKeyTarget_1Shot(jc_* jc, u8 key, u32 steps)
{
	int pitchKey;
	if (jc == 0) {
		return;
	}

	if (jc->logicalChanType == 2 || jc->waveData == NULL) {
		pitchKey = key;
	} else {
		pitchKey = key + 60 - jc->waveData->key;
	}

	if (pitchKey < 0) {
		pitchKey = 0;
	}
	if (pitchKey > 0x7f) {
		pitchKey = 0x7f;
	}

	f32 pitch = C5BASE_PITCHTABLE[pitchKey];
    pitch = jc->basePitch * pitch;
	SetPitchTarget_1Shot(jc, pitch, steps);
}

/*
 * --INFO--
 * Address:	80015EA0
 * Size:	0000C8
 */
void Gate_1Shot(jc_* jc, u8 key, u8 a2, s32 a3)
{
	if (jc->playId == -1) {
		jc->playId      = a3;
		jc->savedPlayId = jc->playId;
		int pitchKey;
		if (jc->logicalChanType == 2) {
			pitchKey = key;
		} else {
			pitchKey = key + 60 - jc->waveData->key;
		}
		if (pitchKey < 0) {
			pitchKey = 0;
		}
		if (pitchKey > 0x7f) {
			pitchKey = 0x7f;
		}

		f32 pitch         = C5BASE_PITCHTABLE[pitchKey];
		jc->velocity      = a2;
		jc->note          = key;
		jc->currentPitch  = jc->basePitch * pitch;
		jc->currentVolume = jc->velocity / 127.0f;
		jc->currentVolume = jc->currentVolume * jc->currentVolume * jc->baseVolume;
	}
}

/*
 * --INFO--
 * Address:	80015F80
 * Size:	000008
 */
void UpdatePause_1Shot(jc_* jc, u8 a1)
{
	jc->pauseFlag = a1;
}

/*
 * --INFO--
 * Address:	80015FA0
 * Size:	000030
 */
void UpdatePanPower_1Shot(jc_* channel, f32 leftPower, f32 rightPower, f32 centerPower, f32 v4)
{
	f32 val = leftPower + rightPower + centerPower;
	if (val == 0.0f) {
		return;
	}

	channel->panMatrices[0].values[0] = leftPower / val;
	channel->panMatrices[0].values[1] = rightPower / val;
	channel->panMatrices[0].values[2] = centerPower / val;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000068
 */
void CountChan(jc_* jc)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000068
 */
void CountChanD(jc_* jc)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000080
 */
void CheckChan(jc_* jc)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000AC
 */
void PrintChan(char* str, jc_* jc, u32 id)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80015FE0
 * Size:	0000B0
 */
void FlushRelease_1Shot(jcs_* jcs)
{
	int count = List_CountChannel(&jcs->releasingChannels);

	for (u32 i = 0; i < count; i++) {
		jc_* chan = List_GetChannel(&jcs->releasingChannels);
		if (chan == NULL) {
			break;
		}

		for (int j = 0; j < 2; j++) {
			if (chan->mOscillators[j]) {
				if (chan->mOscBuffers[j].state != 6 && chan->mOscBuffers[j].state != 7) {
					chan->mOscBuffers[j].state = 6;
				}
			}
		}

		List_AddChannelTail(&jcs->releasingChannels, chan);
	}
}

/*
 * --INFO--
 * Address:	800160A0
 * Size:	0001C4
 */
static BOOL Jesus1Shot_Update(jc_* jc, JCSTATUS jstatus)
{
    Oscbuf_* buf;
	u32 test    = FALSE;
	jc_** jcptr = &jc;
	s32 status  = jstatus;

	if (status == 0) {
		for (u32 i = 0; i < 2; i++) {
			if (jc->mOscillators[i]) {
				buf = &jc->mOscBuffers[i];
				if (buf->state != 6 && buf->state != 7) {
					buf->state = 4;
					test       = TRUE;
				}
			}
		}

		if (test && List_CutChannel(jc) != -1) {
			List_AddChannelTail(&jc->mMgr->releasingChannels, jc);
			if (jc->dspChannel) {
				u8 flag   = jc->channelPriority >> 8;
				u32 test2 = flag;
				if ((flag & 0xff) == 0) {
					test2 = 1;
				}
				jc->dspChannel->_03 = test2;
			}
		}
		jc->playId = -1;
		return FALSE;
	} else if (status == 1 || status == 2 || status == 6) {
		if (jc->mMgr->chanAllocCount) {
			if (List_CutChannel(jc) != -1) {
				jc->mMgr->chanAllocCount--;
				int id      = jc->soundId;
				jc->soundId = 0;
				__Oneshot_StopMonoPolyCheck(jc, id);
				FixReleaseChannel(jc);
			}
		} else {
			if (List_CutChannel(jc) != -1) {
				int id      = jc->soundId;
				jc->soundId = 0;
				__Oneshot_StopMonoPolyCheck(jc, id);
				List_AddChannel(&jc->mMgr->freeChannels, jc);
			}
		}
		if (status != 6) {
			StopLogicalChannel(jc);
		} else {
			Del_WaitDSPChannel(jc);
		}
		jc->note           = -1;
		jc->playId         = -1;
		jc->updateCallback = NULL;
	}
	return FALSE;
}

/*
 * --INFO--
 * Address:	80016280
 * Size:	000098
 */
u32 One_CheckInstWave(SOUNDID_ sound)
{
	Inst_* inst = InstRead(sound.bytes[0], sound.bytes[1]);
	if (inst == NULL) {
		return 1;
	}

	// TODO: fix this conversion to something wave-related once we've sorted that out
	int* map = (int*)VmapRead(inst, sound.bytes[2], sound.bytes[3]);
	if (map == NULL) {
		return 2;
	}

	// clearly need something better than map[1]
	CtrlGroup_* group = WaveidToWavegroup(map[1], sound.bytes[0]);
	if (group == NULL) {
		return 3;
	}

	WaveID_* handle = GetSoundHandle(group, map[1]);
	if (handle == 0) {
		return 4;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000090
 */
void Get_CtrlWave(SOUNDID_ sound)
{
	// UNUSED FUNCTION
}

typedef struct testPercMap {
	int _00; // this clearly should one of the existing structs, but Vmap doesnt work so I have no idea
	int _04;
	f32 _08;
	f32 _0C;
} testPercMap;

/*
 * --INFO--
 * Address:	80016320
 * Size:	00027C
 */
jc_* Play_1shot(jcs_* jcs, SOUNDID_ sound, u32 id)
{
	jc_* chan;
	Inst_* inst;
	WaveID_* wave;
	BOOL test = FALSE;

	inst = InstRead(sound.bytes[0], sound.bytes[1]);
	if (inst == NULL) {
		return NULL;
	}

	testPercMap* map = (testPercMap*)VmapRead(inst, sound.bytes[2], sound.bytes[3]);
	if (map == NULL) {
		return NULL;
	}

	CtrlGroup_* group = WaveidToWavegroup(map->_04, sound.bytes[0]);
	if (group == NULL) {
		return NULL;
	}

	wave = GetSoundHandle(group, map->_04);
	if (wave == NULL) {
		return NULL;
	}

	chan = __Oneshot_GetLogicalChannel(jcs, (CtrlWave_*)wave);
	if (chan == NULL) {
		return NULL;
	}

	int val = sound.bytes[2] + 60 - wave->data->key;
	if (val < 0) {
		val = 0;
	}
	if (val > 127) {
		val = 127;
	}
	f32 pitch                      = C5BASE_PITCHTABLE[val];
	chan->velocity                 = sound.bytes[3];
	chan->note                     = sound.bytes[2];
	chan->basePitch                = map->_0C * (wave->data->_04 / JAC_DAC_RATE) * inst->mGainMultiplier;
	chan->currentPitch             = chan->basePitch * pitch;
	chan->baseVolume               = map->_08 * inst->mFreqMultiplier;
	chan->currentVolume            = chan->velocity / 127.0f;
	chan->currentVolume            = chan->currentVolume * chan->currentVolume * chan->baseVolume;
	chan->panMatrices[1].values[0] = 0.5f;
	chan->panMatrices[2].values[0] = 0.0f;
	chan->panMatrices[3].values[0] = 0.0f;
	EffecterInit(chan, inst);

	int flag = inst->mFlag << 0x18 | sound.value >> 0x10;
	switch (inst->mFlag & 0xc0) {
	case 0xc0:
		flag |= 0xffffff;
		break;
	case 0x80:
		flag |= 0xff;
		break;
	case 0x40:
		flag |= Bank_GetInstKeymap(inst, sound.bytes[2]) << 0x10;
		break;
	}

	chan->soundId = 0;
	if (__Oneshot_StartMonoPolyCheck(chan, flag) == FALSE) {
		if (inst->mFlag & 0x10) {
			List_AddChannelTail(&jcs->freeChannels, chan);
			return FALSE;
		}
		test = TRUE;
	}
	chan->soundId = flag;

	jc_* newjc = __Oneshot_Play_Start(jcs, chan, id);
	if (test) {
		__Oneshot_WavePause(newjc, 1);
	}
	return newjc;
}

/*
 * --INFO--
 * Address:	800165A0
 * Size:	00020C
 */
jc_* Play_1shot_Perc(jcs_* jcs, SOUNDID_ sound, u32 id)
{
	jc_* chan;
	Perc_* perc;
	u32* idp = &id;

	perc = PercRead(sound.bytes[0], sound.bytes[1]);
	if (perc == NULL) {
		return NULL;
	}

	testPercMap* map   = (testPercMap*)Bank_GetPercVmap(perc, sound.bytes[2], sound.bytes[3]);
	testPercMap** mapp = &map;
	if (map == NULL) {
		return NULL;
	}

	u32 x;

	CtrlGroup_* group = WaveidToWavegroup(map->_04, sound.bytes[0]);
	if (group == NULL) {
		return NULL;
	}

	WaveID_* wave = GetSoundHandle(group, map->_04);
	if (wave == NULL) {
		return NULL;
	}

	chan = __Oneshot_GetLogicalChannel(jcs, (CtrlWave_*)wave);
	if (chan == NULL) {
		return NULL;
	}

	chan->velocity = sound.bytes[3];
	chan->note     = sound.bytes[2];

	chan->basePitch    = (wave->data->_04 / JAC_DAC_RATE) * map->_0C * perc->mKeyRegions[sound.bytes[2]]->mVolume;
	chan->currentPitch = chan->basePitch;

	chan->baseVolume    = map->_08 * perc->mKeyRegions[sound.bytes[2]]->mPitch;
	chan->currentVolume = chan->velocity / 127.0f;
	chan->currentVolume = chan->currentVolume * chan->currentVolume * chan->baseVolume;

	u16 flag;
	if (perc->mMagic == 'PER2') {
		chan->panMatrices[1].values[0] = perc->_288[sound.bytes[2]] / 127.0f;
		flag                           = perc->_308[sound.bytes[2]];
	} else {
		flag                           = 1000;
		chan->panMatrices[1].values[0] = 0.5f;
	}
	chan->panMatrices[2].values[0] = 0.0f;
	chan->panMatrices[3].values[0] = 0.0f;
	EffecterInit_Perc(chan, (Pmap_*)perc->mKeyRegions[sound.bytes[2]], flag);
	chan->soundId = 0;

	return __Oneshot_Play_Start(jcs, chan, id);
}

/*
 * --INFO--
 * Address:	800167C0
 * Size:	000128
 */
jc_* Play_1shot_Osc(jcs_* jcs, SOUNDID_ sound, u32 id)
{
	jc_* chan;
	u32 ids = id;
	int pit;
	jcs_* mgr = jcs;

	chan = __Oneshot_GetLogicalChannel(mgr, NULL);
	if (chan == NULL) {
		return NULL;
	}

	chan->_14             = sound.bytes[1] - 0xf0;
	chan->logicalChanType = 2;

	pit = sound.bytes[2];
	if (pit < 0) {
		pit = 0;
	}
	if (pit > 127) {
		pit = 127;
	}
	f32 pitch                      = C5BASE_PITCHTABLE[pit];
	chan->velocity                 = sound.bytes[3];
	chan->note                     = sound.bytes[2];
	chan->basePitch                = 16736.016f / JAC_DAC_RATE;
	chan->currentPitch             = chan->basePitch * pitch;
	chan->baseVolume               = 1.0f;
	chan->currentVolume            = chan->velocity / 127.0f;
	chan->currentVolume            = chan->currentVolume * chan->currentVolume;
	chan->panMatrices[1].values[0] = 0.5f;
	chan->panMatrices[2].values[0] = 0.0f;
	chan->panMatrices[3].values[0] = 0.0f;
	EffecterInit_Osc(chan);
	chan->soundId = 0;
	return __Oneshot_Play_Start(mgr, chan, ids);
}
