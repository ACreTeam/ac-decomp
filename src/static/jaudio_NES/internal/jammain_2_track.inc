/*
 * --INFO--
 * Address:	80010A80
 * Size:	00004C
 */
static f32 __PanCalc(f32 param_1, f32 param_2, f32 param_3, u8 param_4)
{
	f32 result;

	switch (param_4) {
	case 0:
		return param_1;
	case 1:
		return param_2;
	case 2:
		result = param_1 * (1.0f - param_3) + (param_2 * param_3);
	}
	return result;
}

/*
 * --INFO--
 * Address:	80010AE0
 * Size:	000320
 */
void Jam_UpdateTrackAll(seqp_* track)
{
	f32 volumeValue;
	f32 pitchCents;
	f32 panValue;
	f32 fxMixValue;
	f32 dolbyValue;
	f32 distance;
	f32 parentDistance;

	f32 panScaled;
	s8 pan8bit;
	s8 panDelayLeft;

	size_t i;

	distance = track->regParam.param.arguments[3] / 32767.0f;
	if (track->flags != 4) {
		track->parentController.channelPriority = track->regParam.param.basePriority | 0x10000;
		track->parentController.releaseTime     = 0;

		panDelayLeft = 0;
		panScaled    = track->timedParam.inner._110.currentValue * 128.0f;

		OSf32tos8(&panScaled, &pan8bit);
		if (pan8bit < 0) {
			panDelayLeft = -pan8bit;
			pan8bit      = 0;
		}

		track->parentController.maxDelay        = 0x10;
		track->parentController.masterLevels[0] = panDelayLeft;
		track->parentController.masterLevels[1] = pan8bit;

		// Read base volume; if muted, force to zero
		volumeValue = track->timedParam.inner.volume.currentValue;
		if (track->isMuted > 0) {
			volumeValue = 0.0f;
		}

		// Convert pitch to cents, read pan/fxmix/dolby from timed parameters
		pitchCents = Jam_PitchToCent(track->timedParam.inner.pitch.currentValue, track->regParam.param.pitchScale);
		panValue   = track->timedParam.inner.pan.currentValue;
		fxMixValue = track->timedParam.inner.fxmix.currentValue;
		dolbyValue = track->timedParam.inner.dolby.currentValue;

		if (track->outerParams) {
			if (track->outerParams->flags & OuterParamFlag_Volume) {
				volumeValue = volumeValue * track->outerParams->volume;
			}

			if (track->outerParams->flags & OuterParamFlag_Pitch) {
				pitchCents = pitchCents * track->outerParams->pitch;
			}

			if (track->outerParams->flags & OuterParamFlag_Fxmix) {
				fxMixValue = __PanCalc(fxMixValue, track->outerParams->fxMix, distance, track->panCalcTypes[1]);
			}

			if (track->outerParams->flags & OuterParamFlag_Dolby) {
				dolbyValue = __PanCalc(dolbyValue, track->outerParams->dolby, distance, track->panCalcTypes[2]);
			}

			if (track->outerParams->flags & OuterParamFlag_Pan) {
				panValue = __PanCalc(panValue, track->outerParams->pan, distance, track->panCalcTypes[0]);
			}
		}

		// If there is no parent or this track overrides its parent (trackFlags & 1),
		// write the final values directly into the channel state
		if (!track->parent || (track->flags & 1)) {
			track->parentController.volume = volumeValue;
			track->parentController.pitch  = pitchCents;
			track->parentController.pan    = panValue;
			track->parentController.fxmix  = fxMixValue;
			track->parentController.dolby  = dolbyValue;
		} else {
			// Otherwise, combine with parent’s values using a second attenuation factor
			parentDistance = track->regParam.param.arguments[4] / 32767.0f;

			track->parentController.volume = track->parent->parentController.volume * volumeValue;
			track->parentController.pitch  = track->parent->parentController.pitch * pitchCents;
			track->parentController.pan
			    = __PanCalc(panValue, track->parent->parentController.pan, parentDistance, track->parentPanCalcTypes[0]);
			track->parentController.fxmix
			    = __PanCalc(fxMixValue, track->parent->parentController.fxmix, parentDistance, track->parentPanCalcTypes[1]);
			track->parentController.dolby
			    = __PanCalc(dolbyValue, track->parent->parentController.dolby, parentDistance, track->parentPanCalcTypes[2]);

			// If outerParams specify a custom FIR filter, copy those coefficients
			if (track->outerParams && (track->outerParams->flags & OuterParamFlag_FIR8Filter)) {
				for (i = 0; i < 8; ++i) {
					track->parentController.firCoefficients[i] = track->outerParams->firCoefficients[i];
				}

				track->parentController.filterMode = 8;
			}

			// Read inner IIR coefficients (normalized floats) and convert to 16-bit
			for (i = 0; i < 4; ++i) {
				track->parentController.iirCoefficients[i] = track->timedParam.inner.IIRs[i].currentValue * 32767.0f;
			}

			track->parentController.filterMode |= 0x20;
			track->parentController.distFilter = track->timedParam.inner.distFilter.currentValue * 32767.0f;
		}
	}
}

#define OS_FASTCAST_S8 (4)

#include "jammain_2_fastcast.inc"
/*
 * --INFO--
 * Address:	80010E20
 * Size:	0004A8
 */
void Jam_UpdateTrack(seqp_* track, u32 updateFlags)
{
	// A bizarre way the devs attempted to re-use some repeated AND operations in this function,
	// which the compiler can already see and optimize in its own way, causes regalloc inflation.
	u32 updateVolumeFlag;
	u32 updatePitchFlag;
	u32 updatePanFlag;
	u32 updateFxMixFlag;
	u32 updateDolbyFlag;

	f32 computedVolume; // f31
	f32 unaff_f30;      // f30
	f32 unaff_f29;      // f29
	f32 unaff_f28;      // f28
	f32 unaff_f27;      // f27
	f32 regionAttenuation;
	f32 offset;
	f32 dVar15_3;

	size_t i;

	// Used for `OSf32tos8`
	f32 masterLevelF32;
	s8 masterRight;
	s8 masterLeft;

	regionAttenuation = track->regParam.param.arguments[3] / 32767.0f;

	if (track->flags != 0x04) {

		// Update master pan delay levels if requested
		if (updateFlags & SEQTRACK_FLAG_MASTER_LEVEL) {
			masterLeft     = 0;
			masterLevelF32 = track->timedParam.inner._110.currentValue * 128.0f;
			OSf32tos8(&masterLevelF32, &masterRight);
			if (masterRight < 0) {
				masterLeft  = -masterRight;
				masterRight = 0;
			}
			track->parentController.masterLevels[0] = masterLeft;
			track->parentController.masterLevels[1] = masterRight;
		}

		// Tempo update (only if top-level track)
		if (updateFlags & OuterParamFlag_Tempo && !track->parent) {
			Jam_UpdateTempo(track);
		}

		updateVolumeFlag = updateFlags & OuterParamFlag_Volume;
		if (updateVolumeFlag) {
			computedVolume = track->timedParam.inner.volume.currentValue;
			if (track->isMuted != 0) {
				computedVolume = 0.0f;
			}

			if (track->outerParams && (track->outerParams->flags & OuterParamFlag_Volume)) {
				computedVolume *= track->outerParams->volume;
			}

			if (track->isPaused && (track->pauseStatus & 1)) {
				computedVolume *= track->timedParam.inner._100.currentValue;
			}
		}

		updatePitchFlag = updateFlags & OuterParamFlag_Pitch;
		if (updatePitchFlag) {
			unaff_f30 = Jam_PitchToCent((track->timedParam).inner.pitch.currentValue, track->regParam.param.pitchScale);
			if (track->outerParams && ((track->outerParams->flags & OuterParamFlag_Pitch) != 0)) {
				unaff_f30 = (unaff_f30 * track->outerParams->pitch);
			}
		}

		updatePanFlag = updateFlags & OuterParamFlag_Pan;
		if (updatePanFlag) {
			unaff_f29 = (track->timedParam).inner.pan.currentValue;
			if (track->outerParams && ((track->outerParams->flags & OuterParamFlag_Pan) != 0)) {
				unaff_f29 = __PanCalc(unaff_f29, track->outerParams->pan, regionAttenuation, track->panCalcTypes[0]);
			}
		}

		updateFxMixFlag = updateFlags & OuterParamFlag_Fxmix;
		if (updateFxMixFlag) {
			unaff_f28 = (track->timedParam).inner.fxmix.currentValue;
			if (track->outerParams && ((track->outerParams->flags & OuterParamFlag_Fxmix) != 0)) {
				unaff_f28 = __PanCalc(unaff_f28, track->outerParams->fxMix, regionAttenuation, track->panCalcTypes[1]);
			}
		}

		updateDolbyFlag = updateFlags & OuterParamFlag_Dolby;
		if (updateDolbyFlag) {
			unaff_f27 = (track->timedParam).inner.dolby.currentValue;
			if (track->outerParams && ((track->outerParams->flags & OuterParamFlag_Dolby) != 0)) {
				unaff_f27 = __PanCalc(unaff_f27, track->outerParams->dolby, regionAttenuation, track->panCalcTypes[2]);
			}
		}

		// IIR flag is set
		if (updateFlags & OuterParamFlag_IIRFilter) {
			for (i = 0; i < 4; ++i) {
				track->parentController.iirCoefficients[i] = track->timedParam.inner.IIRs[i].currentValue * 32767.0f;
			}

			track->parentController.filterMode |= 0x20;
		}

		if (track->outerParams) {
			if (updateFlags & OuterParamFlag_FIR8Filter && (track->outerParams->flags & OuterParamFlag_FIR8Filter)) {
				for (i = 0; i < 8; ++i) {
					track->parentController.firCoefficients[i] = track->outerParams->firCoefficients[i];
				}

				track->parentController.filterMode = (track->parentController.filterMode & 0x20) + 8;
			}
		}

		if (updateFlags & OuterParamFlag_DistFilt) {
			track->parentController.distFilter = track->timedParam.inner.distFilter.currentValue * 32767.0f;
		}

		for (i = 0; i < 2; ++i) {
			if (track->oscillatorRouting[i] == 0x0E) {
				offset = Bank_OscToOfs(&track->oscillators[i], &track->oscillatorParams[i]);
				switch (track->oscillators[i].mode) {
				case 1:
					unaff_f30 = unaff_f30 * offset;
					break;
				case 0:
					computedVolume = computedVolume * offset;
					break;
				case 2:
					unaff_f29 = unaff_f29 * offset;
					break;
				case 3:
					unaff_f28 = unaff_f28 * offset;
					break;
				case 4:
					unaff_f27 = unaff_f27 * offset;
					break;
				}
			}
		}
		if (!track->parent || ((track->flags & 1) != 0)) {
			if (updateVolumeFlag) {
				track->parentController.volume = computedVolume;
			}
			if (updatePitchFlag) {
				track->parentController.pitch = unaff_f30;
			}
			if (updatePanFlag) {
				track->parentController.pan = unaff_f29;
			}
			if (updateFxMixFlag) {
				track->parentController.fxmix = unaff_f28;
			}
			if (updateDolbyFlag != 0) {
				track->parentController.dolby = unaff_f27;
			}
		} else {
			dVar15_3 = track->regParam.param.arguments[4] / 32767.0f;
			if (updateVolumeFlag) {
				track->parentController.volume = track->parent->parentController.volume * computedVolume;
			}
			if (updatePitchFlag) {
				track->parentController.pitch = track->parent->parentController.pitch * unaff_f30;
			}
			if (updatePanFlag) {
				track->parentController.pan
				    = __PanCalc(unaff_f29, track->parent->parentController.pan, dVar15_3, track->parentPanCalcTypes[0]);
			}
			if (updateFxMixFlag) {
				track->parentController.fxmix
				    = __PanCalc(unaff_f28, track->parent->parentController.fxmix, dVar15_3, track->parentPanCalcTypes[1]);
			}
			if (updateDolbyFlag) {
				track->parentController.dolby
				    = __PanCalc(unaff_f27, track->parent->parentController.dolby, dVar15_3, track->parentPanCalcTypes[2]);
			}
		}
	}
}

/*
 * --INFO--
 * Address:	800112E0
 * Size:	000104
 */
void Jam_UpdateTempo(seqp_* track)
{
	size_t i;

	size_t* REF_i;

	if (!track->parent) {
		track->tempoFactor = (float)track->timeBase * (float)track->tempo / (JAC_DAC_RATE * 60.0f / 80.0f);
		if ((track->outerParams->flags & OuterParamFlag_Tempo) != 0) {
			track->tempoFactor = track->tempoFactor * track->outerParams->tempo;
		}
	} else {
		track->tempoFactor = track->parent->tempoFactor;
		track->timeBase    = track->parent->timeBase;
	}
	for (i = 0; i < 16; ++i) {
		REF_i = &i;
		if (track->children[i] && track->children[i]->trackState) {
			Jam_UpdateTempo(track->children[i]);
		}
	}
}

/*
 * --INFO--
 * Address:	80011400
 * Size:	0000CC
 */
void Jam_MuteTrack(seqp_* track, u8 param_2)
{
	u32 i;
	u16 mask;

	if (track->parent) {
		track->isMuted = track->parent->isMuted | param_2;
		mask           = 1 << (track->trackId & 0xf);
		if (!param_2) {
			track->parent->childMuteMask &= ~mask;
		} else {
			track->parent->childMuteMask |= mask;
		}
	} else {
		track->isMuted = param_2;
	}
	track->updateFlags |= OuterParamFlag_Volume;
	if (track->isMuted && (track->pauseStatus & 0x20)) {
		for (i = 0; i < 8; ++i) {
			NoteOFF_R(track, (u8)i, 10);
		};
	}
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000B4
 */
void Jam_MuteChildTracks(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	800114E0
 * Size:	00013C
 */
void Jam_PauseTrack(seqp_* track, u8 param_2)
{
	size_t i;
	jc_* pjVar1;

	size_t* REF_i;

	track->isPaused = TRUE;
	if (track->pauseStatus & 0x01) {
		track->updateFlags |= OuterParamFlag_Volume;
	}
	if (track->pauseStatus & 0x04) {
		for (i = 0; i < 8; ++i) {
			REF_i = &i;
			NoteOFF_R(track, i, 10);
		}
	}
	if (track->pauseStatus & 0x08) {
		for (i = 0; i < 8; ++i) {
			pjVar1 = track->channels[i];
			if (pjVar1 && track->activeSoundIds[i] == pjVar1->channelId) {
				UpdatePause_1Shot(pjVar1, 1);
			}
		}
	}
	Jam_SetInterrupt(track, 0);
	if (param_2 == TRUE) {
		for (i = 0; i < 16; ++i) {
			if (track->children[i] && track->children[i]->trackState) {
				Jam_PauseTrack(track->children[i], 1);
			}
		}
	}
}

/*
 * --INFO--
 * Address:	80011620
 * Size:	0000EC
 */
void Jam_UnPauseTrack(seqp_* track, u8 param_2)
{
	size_t i;
	jc_* pjVar1;

	size_t* REF_i;

	track->isPaused = FALSE;
	track->updateFlags |= OuterParamFlag_Volume;
	for (i = 0; i < 8; ++i) {
		REF_i  = &i;
		pjVar1 = track->channels[i];
		if (pjVar1 && track->activeSoundIds[i] == pjVar1->channelId) {
			UpdatePause_1Shot(pjVar1, 0);
		}
	}
	Jam_SetInterrupt(track, 1);
	if (param_2 == TRUE) {
		for (i = 0; i < 16; ++i) {
			if (track->children[i] && track->children[i]->trackState) {
				Jam_UnPauseTrack(track->children[i], 1);
			}
		}
	}
}

/*
 * --INFO--
 * Address:	80011720
 * Size:	000028
 * Note: Equivalent to `JASIntrMgr::request` in later JAudio.
 */
void Jam_SetInterrupt(seqp_* track, u16 interrupt)
{
	if (track->interruptEnable & (1 << interrupt)) {
		track->interruptPending |= (1 << interrupt);
	}
}

/*
 * --INFO--
 * Address:	80011760
 * Size:	000090
 */
BOOL Jam_TryInterrupt(seqp_* track)
{
	u32 mask;
	int i;

	if (track->interruptActive) {
		return FALSE;
	}
	for (i = 0; i < 8; ++i) {
		mask = 1 << i;
		if ((track->interruptEnable & mask) && (track->interruptPending & mask)) {
			track->savedProgramCounter = track->programCounter;
			track->programCounter      = track->interruptAddresses[i];
			track->interruptActive     = mask;
			track->_3CC                = track->waitTimer;
			track->waitTimer           = 0;
			track->interruptPending ^= mask;
			return TRUE;
		}
	}
	return FALSE;
}

