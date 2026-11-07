#include "jaudio_NES/noteon.h"

#include "jaudio_NES/audiostruct.h"
#include "jaudio_NES/jammain_2.h"
#include "jaudio_NES/oneshot.h"
#include "jaudio_NES/connect.h"
#include "jaudio_NES/driverinterface.h"

/*
 * --INFO--
 * Address:	80013840
 * Size:	000394
 */
s32 NoteON(seqp_* track, s32 channel, s32 flag1, s32 flag2, s32 playFlag)
{
	if (track->isMuted && (track->pauseStatus & 0x40)) {
		return -1;
	}
    
	if (track->channels[channel]) {
		NoteOFF(track, channel);
	}

    jc_* sound;
	u32 reg;
	seqp_* temp;
    seqp_* parent = track->parent;
	jcs_* jcs     = &track->parentController;
	
    temp = parent;
	while (jcs->chanCount == 0 || jcs->freeChannels == 0) {
		if (temp == NULL) {
			jcs = &track->parentController;
			break;
		}
		jcs  = &temp->parentController;
		temp = temp->parent;
	}

	if (track->flags == 4) {
		if (track->parent == NULL) {
			return -1;
		}

		if (jcs != &parent->parentController) {
			jc_* chan = List_GetChannel(&jcs->freeChannels);
			if (chan) {
				jcs->chanCount--;
				List_AddChannel(&track->parentController.freeChannels, chan);
				parent->parentController.chanCount++;
				chan->mMgr = &parent->parentController;
			}
			jcs = &parent->parentController;
		}
	} else if (jcs != &track->parentController) {
		jc_* chan = List_GetChannel(&jcs->freeChannels);
		if (chan) {
			jcs->chanCount--;
			List_AddChannel(&track->parentController.freeChannels, chan);
			track->parentController.chanCount++;
			chan->mMgr = &track->parentController;
		}
		jcs = &track->parentController;
	}

	reg      = Jam_ReadRegDirect(track, 6);
	u16 phys = Jac_BnkVirtualToPhysical(reg >> 8);
    u32 r    = reg & 0xFF;
	u32 b    = (phys & 0xff) << 8 | reg & 0xff;
	u32 a    = b << 16 | flag1 << 8 | flag2;

	SOUNDID_ id;
    u32 flag;
    u32 i;

	id.value = a;
	if (r >= 0xf0) {
		sound = Play_1shot_Osc(jcs, id, playFlag);
	} else if (r >= 0xe4) {
		sound = Play_1shot_Perc(jcs, id, playFlag);
	} else {
		sound = Play_1shot(jcs, id, playFlag);
	}
	track->channels[channel] = sound;
	if (sound == NULL) {
		return -1;
	}
	track->activeSoundIds[channel] = sound->channelId;
	UpdatePanPower_1Shot(sound, track->regParam.param.arguments[0], track->regParam.param.arguments[1], track->regParam.param.arguments[2],
	                     track->regParam.param.arguments[3]);

	for (i = 0; i < 2; i++) {
		flag = track->oscillatorRouting[i];
        
		if (flag != 15 && flag != 14) {
            if (flag >= 8) {
                flag -= 8;
                if (sound->mOscillators[flag]) {
                    track->oscillators[i] = *sound->mOscillators[flag];
                }
            } else if (flag >= 4) {
                flag -= 4;
                s16* prev = track->oscillators[i].releaseVecOffset;
                if (sound->mOscillators[flag]) {
                    track->oscillators[i]                  = *sound->mOscillators[flag];
                    track->oscillators[i].releaseVecOffset = prev;
                }
            }

            Effecter_Overwrite_1ShotD(sound, &track->oscillators[i], flag);
        }
	}

	Jam_UpdateTrack(track, 3);
	ResetInitialVolume(sound);
	return 0;

	s32* REF_channel = &channel;
}

/*
 * --INFO--
 * Address:	80013BE0
 * Size:	000090
 */
s32 NoteOFF_R(seqp_* track, u8 param_2, u16 param_3)
{
	u8* REF_param_2;
	jc_* jc;

	REF_param_2 = &param_2;
	if (jc = track->channels[param_2]) {
		if (jc->channelId == track->activeSoundIds[param_2]) {
			if (param_3 == 0) {
				Stop_1Shot(jc);
			} else {
				Stop_1Shot_R(jc, param_3);
			}
		}
		track->channels[param_2]       = NULL;
		track->activeSoundIds[param_2] = 0;
		return 1;
	}
	return 0;
}

/*
 * --INFO--
 * Address:	80013C80
 * Size:	000024
 */
s32 NoteOFF(seqp_* track, u8 param_2)
{
	return NoteOFF_R(track, param_2, 0);
}

/*
 * --INFO--
 * Address:	80013CC0
 * Size:	000058
 */
s32 GateON(seqp_* track, s32 param_2, s32 param_3, s32 param_4, s32 param_5)
{
	s32* REF_param_3 = &param_3;

	if (track->channels[param_2]) {
		Gate_1Shot(track->channels[param_2], param_3, param_4, param_5);
	} else {
		return -1;
	}
	return 0;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
void ProgramChange(s32 chan)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80013D20
 * Size:	000064
 */
BOOL CheckNoteStop(seqp_* track, s32 param_2)
{
	jc_* jc;

	if (jc = track->channels[param_2]) {
		if (jc->channelId != track->activeSoundIds[param_2]) {
			track->channels[param_2]       = NULL;
			track->activeSoundIds[param_2] = 0;
			return TRUE;
		}
		return jc->note == 0xff;
	}
	return TRUE;
}
