/*
 * --INFO--
 * Address:	80015140
 * Size:	000034
 */
static u8 __GetTrigger(jc_* jc, u8 n)
{
	switch (n) {
	case 1:
		return jc->velocity;
	case 2:
		return jc->note;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	80015180
 * Size:	000028
 */
static f32 __Clamp01(f32 val)
{
	if (val < 0.0f) {
		return 0.0f;
	}
	if (val > 1.0f) {
		return 1.0f;
	}
	return val;
}

/*
 * --INFO--
 * Address:	800151C0
 * Size:	000054
 */
static void __Clamp01InitPan(jc_* jc)
{
	for (u32 i = 1; i < 3; i++) {
		jc->panMatrices[i].values[0] = __Clamp01(jc->panMatrices[i].values[0]);
	}
}

/*
 * --INFO--
 * Address:	80015220
 * Size:	000068
 */
static void __DoEffect(jc_* jc, u8 id, f32 val)
{
	switch (id) {
	case 1:
		jc->currentPitch *= val;
		break;
	case 0:
		jc->currentVolume *= val;
		break;
	case 2:
		jc->panMatrices[1].values[1] = val;
		break;
	case 3:
		jc->panMatrices[2].values[1] = val;
		break;
	case 4:
		jc->panMatrices[3].values[1] = val;
		break;
	}
}

/*
 * --INFO--
 * Address:	800152A0
 * Size:	000138
 */
static void EffecterInit(jc_* jc, Inst_* inst)
{
	jc->pitchModifier            = 1.0f;
	jc->volumeModifier           = 1.0f;
	jc->panMatrices[1].values[1] = 0.5f;
	jc->panMatrices[2].values[1] = 0.0f;
	jc->panMatrices[3].values[1] = 0.0f;
	for (u32 i = 0; i < 2; i++) {
		if (inst->mSensors[i]) {
			u8 trigger     = __GetTrigger(jc, inst->mSensors[i]->type);
			f32 sense      = Bank_SenseToOfs(inst->mSensors[i], trigger);
			f32* REF_sense = &sense;
			__DoEffect(jc, inst->mSensors[i]->id, sense);
		}

		if (inst->mEffects[i]) {
			f32 r = Bank_RandToOfs(inst->mEffects[i]);
			__DoEffect(jc, inst->mEffects[i]->id, r);
		}

		if (inst->mOscillators[i]) {
			jc->mOscBuffers[i].state = 1;
			jc->mOscillators[i]      = inst->mOscillators[i];
			f32 ofs                  = Bank_OscToOfs(jc->mOscillators[i], &jc->mOscBuffers[i]);
			DoEffectOsc(jc, jc->mOscillators[i]->mode, ofs);
		} else {
			jc->mOscillators[i] = NULL;
		}
	}
	__Clamp01InitPan(jc);
}

/*
 * --INFO--
 * Address:	800153E0
 * Size:	0000D0
 */
static void EffecterInit_Perc(jc_* jc, Pmap_* pmap, u16 id)
{
	jc->pitchModifier            = 1.0f;
	jc->volumeModifier           = 1.0f;
	jc->panMatrices[1].values[1] = 0.5f;
	jc->panMatrices[2].values[1] = 0.0f;
	jc->panMatrices[3].values[1] = 0.0f;

	// PERC instruments only have rand and not osc
    Pmap_* map;
	for (u32 i = 0; i < 2; i++) {
		 map = (Pmap_*)((int*)pmap + i + 2);
		if (map->_00) {
			f32 r      = Bank_RandToOfs(map->_00);
			f32* REF_r = &r;
			__DoEffect(jc, map->_00->id, r);
		}

		jc->mOscillators[i] = NULL;
	}
	jc->mOscillators[0]      = &PERC_ENV;
	jc->mOscBuffers[0].state = TRUE;
	Bank_OscToOfs(jc->mOscillators[0], &jc->mOscBuffers[0]);
	jc->mOscBuffers[0].releaseParam = id;
	__Clamp01InitPan(jc);
}

/*
 * --INFO--
 * Address:	800154C0
 * Size:	00007C
 */
static void EffecterInit_Osc(jc_* jc)
{
	jc->pitchModifier            = 1.0f;
	jc->volumeModifier           = 1.0f;
	jc->panMatrices[1].values[1] = 0.5f;
	jc->panMatrices[2].values[1] = 0.0f;
	jc->panMatrices[3].values[1] = 0.0f;

	for (u32 i = 0; i < 2; i++) {
		jc->mOscillators[i] = NULL;
	}

	jc->mOscillators[0]      = &OSC_ENV;
	jc->mOscBuffers[0].state = TRUE;
	Bank_OscToOfs(jc->mOscillators[0], &jc->mOscBuffers[0]);
}

/*
 * --INFO--
 * Address:	80015540
 * Size:	00006C
 */
void Effecter_Overwrite_1ShotD(jc_* jc, Osc_* osc, u32 id)
{
	if (id < 4) {
		jc->mOscBuffers[id].state = TRUE;
		jc->mOscillators[id]      = osc;
		DoEffectOsc(jc, jc->mOscillators[id]->mode, Bank_OscToOfs(jc->mOscillators[id], &jc->mOscBuffers[id]));
	}
}

/*
 * --INFO--
 * Address:	........
 * Size:	000060
 */
void Effecter_Overwrite_1Shot(jc_* jc, Osc_* osc1, Osc_* osc2)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	800155C0
 * Size:	00010C
 */
static jc_* __Oneshot_Play_Start(jcs_* jcs, jc_* jc, u32 id)
{
	BOOL play;

	if (id == 0) {
		id = -1;
	}
	jc->playId         = id;
	jc->savedPlayId    = jc->playId;
	jc->updateCallback = Jesus1Shot_Update;
	jc->dspChannel     = AllocDSPchannel(0, (u32)jc);

	if (jc->dspChannel == NULL) {
		play = CheckLogicalChannel(jc);
	} else {
		play = PlayLogicalChannel(jc);
	}

	if (jc->dspChannel == NULL && play == TRUE) {
		if (Add_WaitDSPChannel(jc) == TRUE) {
			List_AddChannelTail(&jcs->waitingChannels, jc);
			return jc;
		} else {
			List_AddChannelTail(&jcs->freeChannels, jc);
			return NULL;
		}
	} else if (play == FALSE) {
		DeAllocDSPchannel(jc->dspChannel, (u32)jc);
		jc->dspChannel = NULL;
		List_AddChannelTail(&jcs->freeChannels, jc);
		return NULL;
	} else {
		List_AddChannelTail(&jcs->activeChannels, jc);
	}
	return jc;
}

/*
 * --INFO--
 * Address:	800156E0
 * Size:	000154
 */
static jc_* __Oneshot_GetLogicalChannel(jcs_* jcs, CtrlWave_* wave)
{
	if (wave && wave->_0C == NULL) {
		return FALSE;
	}

	jc_* chan = List_GetChannel(&jcs->freeChannels);
	jc_* chan2;
	jc_** REF_chan2 = &chan2;
	if (chan == NULL) {

		if (FixAllocChannel(jcs, 1) == FALSE) {
			return 0;
		}
		jcs->chanAllocCount++;
		chan = List_GetChannel(&jcs->freeChannels);
		if (chan == NULL) {
			return 0;
		}

		if (jcs->voiceStealingMode == 1) {
			chan2 = List_GetChannel(&jcs->releasingChannels);
			if (chan2 == NULL) {
				chan2 = List_GetChannel(&jcs->activeChannels);
				if (chan2) {
					List_CountChannel(&jcs->waitingChannels);
				}
			}

			if (chan2) {
				chan2->mOscBuffers[0].state = 6;
				List_AddChannel(&jcs->waitingChannels, chan2);
				if (chan2->dspChannel) {
					ForceStopDSPchannel(chan2->dspChannel);
				}
			}
		}
	}
	Channel_Init(chan);
	if (wave) {
		chan->waveData        = (Wave_*)wave->_34;
		chan->_14             = wave->_0C;
		chan->logicalChanType = 0;
	}
	chan->_18 = 0;
	UpdatePanPower_1Shot(chan, 1.0f, 1.0f, 1.0f, 1.0f);
	return chan;
}

/*
 * --INFO--
 * Address:	80015840
 * Size:	000044
 */
Perc_* PercRead(u32 a1, u32 a2)
{
	Bank_* bank = Bank_Get(a1);
	if (bank == NULL) {
		return NULL;
	}

	return Bank_PercChange(bank, a2);
}

/*
 * --INFO--
 * Address:	800158A0
 * Size:	000044
 */
Inst_* InstRead(u32 a1, u32 a2)
{

	Bank_* bank = Bank_Get(a1);
	if (bank == NULL) {
		return NULL;
	}

	return Bank_InstChange(bank, a2);
}

/*
 * --INFO--
 * Address:	80015900
 * Size:	00002C
 */
Vmap_* VmapRead(Inst_* inst, u8 a1, u8 a2)
{
	Vmap_* map = (Vmap_*)Bank_GetInstVmap(inst, a1, a2);
	return !map ? NULL : map;
}

/*
 * --INFO--
 * Address:	80015940
 * Size:	000010
 */
static void __Oneshot_WavePause(jc_* jc, u8 a)
{
	jc->pauseFlag = a;
	jc->toFlush   = 1;
}

/*
 * --INFO--
 * Address:	80015960
 * Size:	00014C
 */
static BOOL __Oneshot_StartMonoPolyCheck(jc_* jc, u32 id)
{
	jcs_* mgr = jc->mMgr;
	jc_* chan = mgr->activeChannels;
	u32 index = 0;
	u8 flag   = id >> 0x18;
	u8 poly   = polys_table[flag & 0xf];


	if (poly == 0) {
		return TRUE;
	}

	while (TRUE) {
		if (chan == NULL) {
			break;
		}

		if (chan->soundId == id) {
			if (flag & 0x20) {
				index++;
			} else {
				chan->polyphonyCounter++;
				if (chan->polyphonyCounter == poly) {
					if (flag & 0x10) {
						ForceStopLogicalChannel(chan);
					} else {
						__Oneshot_WavePause(chan, 1);
					}
				}
			}
		}
		chan = (jc_*)chan->mNext;
	}

	chan = mgr->releasingChannels;
	while (TRUE) {
		if (chan == NULL) {
			break;
		}

		if (chan->soundId == id) {
			if (flag & 0x20) {
				index++;
			} else {
				chan->polyphonyCounter++;
				if (chan->polyphonyCounter == poly) {
					ForceStopLogicalChannel(chan);
				}
			}
		}

		chan = (jc_*)chan->mNext;
	}

	if (flag & 0x20) {
		jc->polyphonyCounter = index;
		if (index < poly) {
			return TRUE;
		}
		return FALSE;
	}

	jc->polyphonyCounter = 0;
	return TRUE;
}

/*
 * --INFO--
 * Address:	80015AC0
 * Size:	0000E8
 */
static void __Oneshot_StopMonoPolyCheck(jc_* jc, u32 id)
{
	jc_* chan;
	u8 poly;

	chan = jc->mMgr->activeChannels;
	poly = polys_table[id >> 0x18 & 0xf];

	if (id && poly) {

		while (TRUE) {
			if (chan == NULL) {
				break;
			}

			int flag = id >> 0x18 & 0x20;
			if (chan->soundId == id) {
				if (flag) {
					if (chan->polyphonyCounter > jc->polyphonyCounter) {
						chan->polyphonyCounter--;
						if (chan->polyphonyCounter == poly - 1) {
							__Oneshot_WavePause(chan, 0);
						}
					}
				} else {
					if (chan->polyphonyCounter > jc->polyphonyCounter) {
						chan->polyphonyCounter--;
						if (chan->polyphonyCounter < poly) {
							__Oneshot_WavePause(chan, 0);
						}
					}
				}
			}

			chan = (jc_*)chan->mNext;
		}
	}
}

