#include "jaudio_NES/jammain_2.h"

#include "jaudio_NES/oneshot.h"
#include "jaudio_NES/jamosc.h"
#include "jaudio_NES/seqsetup.h"
#include "jaudio_NES/fat.h"
#include "jaudio_NES/noteon.h"
#include "jaudio_NES/rate.h"
#include "jaudio_NES/random.h"
#include "jaudio_NES/centcalc.h"
#include "jaudio_NES/bankdrv.h"
#include "jaudio_NES/driverinterface.h"

#include "dolphin/os/OSError.h"
#include <dolphin/os/OSFastCast.h>
#include <dolphin/os.h>

// TODO IN THIS FILE: What do the return values for the `Cmd_` functions signify?
// 0 is probably success / "no error".  Return values 1 and 2 have been observed.
// This just breaking: Cmd_LoopE returns 0x80.

#define TRACK_LIST_SIZE (32)

typedef struct TrackListPair TrackListPair;
typedef struct Arghead_ Arghead_;

/**
 * @brief This is an invented pair-like struct, needed for `TRACK_LIST`.
 *
 * @note Size: 8.
 */
struct TrackListPair {
	seqp_* track; // _00
	u32 id;       // _04
};

/**
 * @brief This is an invented pair-like struct, needed for `Arglist`.
 *
 * @note Size: 4.
 */
struct Arghead_ {
	u16 argCount;
	u16 argTypes; // This is a bitfield array of eight 2-bit values
};

static TrackCallback JAM_CALLBACK_FUNC = NULL;

static size_t T_LISTS;
static TrackListPair TRACK_LIST[TRACK_LIST_SIZE];

static seqp_* SEQ_P;
static u8 SEQ_CMD;
static u32 SEQ_ARG[8];

// predeclare this so Jam_UpdateTrackAll can use this stupid function.
extern "C" static void OSf32tos8(f32* in, s8* out);

/*
 * --INFO--
 * Address:	8000F400
 * Size:	000054
 */
void* Jam_OfsToAddr(seqp_* track, u32 ofs)
{
	// TODO: What do 0, 1, and 2 mean?
	switch (track->dataSourceMode) {
	case 0:
		return track->baseData + ofs;
	case 1:
	case 2:
		return FAT_GetPointer(track->fileHandle, ofs);
	}
	return 0;
}

/*
 * --INFO--
 * Address:	8000F460
 * Size:	000054
 */
static u8 __ByteReadOfs(seqp_* track, u32 ofs)
{
	// TODO: What do 0, 1, and 2 mean?
	switch (track->dataSourceMode) {
	case 0:
		return track->baseData[ofs];
	case 1:
	case 2:
		return FAT_ReadByte(track->fileHandle, ofs);
	}
	return 0;
}

/*
 * --INFO--
 * Address:	8000F4C0
 * Size:	000050
 */
static u16 __WordReadOfs(seqp_* track, u32 ofs)
{
	u16 result = __ByteReadOfs(track, ofs + 0) << 8;
	result |= __ByteReadOfs(track, ofs + 1);
	return result;
}

/*
 * --INFO--
 * Address:	8000F520
 * Size:	000068
 */
static u32 __24ReadOfs(seqp_* track, u32 ofs)
{
	u32 result;
	result = __ByteReadOfs(track, ofs + 0) << 16;
	result |= __ByteReadOfs(track, ofs + 1) << 8;
	result |= __ByteReadOfs(track, ofs + 2);
	return result;
}

/*
 * --INFO--
 * Address:	8000F5A0
 * Size:	000050
 */
static u32 __LongReadOfs(seqp_* track, u32 ofs)
{
	u32 result;
	result = __WordReadOfs(track, ofs + 0) << 16;
	result |= __WordReadOfs(track, ofs + 2);
	return result;
}

/*
 * --INFO--
 * Address:	8000F600
 * Size:	000070
 */
static u8 __ByteRead(seqp_* track)
{
	// TODO: What do 0, 1, and 2 mean?
	switch (track->dataSourceMode) {
	case 0:
		return track->baseData[track->programCounter++];
	case 1:
	case 2:
		return FAT_ReadByte(track->fileHandle, track->programCounter++);
	}
	return 0;
}

/*
 * --INFO--
 * Address:	8000F680
 * Size:	000048
 */
static u16 __WordRead(seqp_* track)
{
	u16 result;
	result = __ByteRead(track) << 8;
	result |= __ByteRead(track);
	return result;
}

/*
 * --INFO--
 * Address:	8000F6E0
 * Size:	00005C
 */
static u32 __24Read(seqp_* track)
{
	u32 result;
	result = __ByteRead(track) << 16;
	result |= __ByteRead(track) << 8;
	result |= __ByteRead(track);
	return result;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000048
 */
static u32 __32Read(seqp_* track)
{
	// Despite being unused, it's obvious this function is similar to `__LongReadOfs`.
	u32 result;
	result = __WordRead(track) << 16;
	result |= __WordRead(track);
	return result;
}

/*
 * --INFO--
 * Address:	8000F740
 * Size:	0000D0
 */
static BOOL __ConditionCheck(seqp_* track, u8 param_2)
{
	BOOL result;
	u16 uVar1;

	uVar1  = Jam_ReadRegDirect(track, 3);
	result = FALSE;

	switch (param_2 & 0x0f) {
	case 0:
		result = TRUE;
		break;
	case 1:
		if (uVar1 == 0) {
			result = TRUE;
		}
		break;
	case 2:
		if (uVar1 != 0) {
			result = TRUE;
		}
		break;
	case 3:
		if (uVar1 == 1) {
			result = TRUE;
		}
		break;
	case 4:
		if (uVar1 >= 0x8000) {
			result = TRUE;
		}
		break;
	case 5:
		if (uVar1 < 0x8000) {
			result = TRUE;
		}
		break;
	}
	return result;
}

/*
 * --INFO--
 * Address:	8000F820
 * Size:	000090
 * Note: Equivalent to `JASTrack::seqTimeToDspTime` in later JAudio
 */
int Jam_SEQtimeToDSPtime(seqp_* track, s32 param_2, u8 param_3)
{
	f32 dspTime;

	dspTime = (f32)param_2 * (f32)param_3 / 100.0f;

	if (track->timeRelationMode == 1) {
		dspTime = dspTime / track->tempoFactor;
	} else {
		dspTime = dspTime * 120.0f / track->timeBase;
	}

	return dspTime;
}

/* Keep helper code in separate contributions for the Australian function order. */
#include "jammain_2_register.inc"
#include "jammain_2_port.inc"
#include "jammain_2_track.inc"
#include "jammain_2_commands.inc"
#include "jammain_2_dispatch.inc"
// TODO: These five values appear all over this file. They mean something.
static u8 osc_table[] = { 0x01, 0x02, 0x08, 0x04, 0x10 };

/*
 * --INFO--
 * Address:	80012EC0
 * Size:	0008C0
 * Note: (Roughly) Equivalent to `JASTrack::mainProc` in later JAudio.
 */
#pragma opt_dead_assignments off // @HACK - necessary to remove a mr where NULL + 0 are used in the same loop.
s32 Jam_SeqmainNote(seqp_* track, u8 isMuted) {
    u32 pitch;
    u32 uVar2;
    BOOL var_r26;
    u8 bVar9;
    u8 velocity;
    u32 noteMode;
    int iVar11;
    s32 uVar5;
    u8 bVar10_2;
    f32 tempoProportion;
    u8 opcode;
    u8 uVar6;
    u32 keyTarget;
    u8 bVar10;
    int local_64;
    int iVar11_2;
    int iVar12;
    u32 seqRes;
    int duration;
    jc_* pjVar3;
    int iVar11_3;
    u8 voice;

    seqRes = 0;
    if (track->parent && track->doChangeTempo == TRUE) {
        tempoProportion = (float)track->tempo / (float)track->parent->tempo;
        if (tempoProportion > 1.0f) {
            tempoProportion = 1.0f;
        }
        track->tempoAccumulator += tempoProportion;
        if (track->tempoAccumulator < 1.0f) {
            return 0;
        }
        track->tempoAccumulator -= 1.0f;
    }

    { // This whole part is not present(?) in later JAudio.
        if (track->parent) {
            track->isMuted = isMuted;
        }
        if (track->parent && track->parentController.chanCount != 0) {
            pjVar3 = List_GetChannel(&track->parentController.freeChannels);
            if (pjVar3) {
                List_AddChannel(&track->parent->parentController.freeChannels, pjVar3);
                pjVar3->mMgr = &track->parent->parentController;
                track->parentController.chanCount--;
                track->parent->parentController.chanCount++;
            }
        }
        // This resembles `JASTrack::getTranspose` of later JAudio.
        if (track->parent) {
            track->finalTranspose = track->transpose + track->parent->finalTranspose;
        } else {
            track->finalTranspose = track->transpose;
        }
    }

    Jam_SetInterrupt(track, 7);
    { // This resembles `JASIntrMgr::timerProcess` of later JAudio.
        if (track->timer != 0) {
            if (--track->timer == 0) {
                Jam_SetInterrupt(track, 6);
                if (track->timerCount != 0) {
                    if (--track->timerCount != 0) {
                        track->timer = track->maxTime;
                    }
                } else {
                    track->timer = track->maxTime;
                }
            }
        }
    }

try_interrupt:
    Jam_TryInterrupt(track);
    if (track->isPaused && (track->pauseStatus & 2)) {
        goto LAB_800136e0;
    }
    track->tickCounter++;
    if (track->waitTimer == -1) {
        if ((u8)CheckNoteStop(track, 0)) { // TODO: CheckNoteStop should return u8 or C++ bool
            track->waitTimer = 0;
        } else {
            goto timed;
        }
    }

    if (track->waitTimer > 0) {
        --track->waitTimer;
        if (track->waitTimer != 0) {
            goto timed;
        }
        if (track->_D0 != -1 && track->_D4 == 0) {
            for (int index = 0; index < (int)track->_90; index++) {
                track->_94[index] = 0xff;
                track->channels[index] = NULL;
            }
        }
    }

    while (TRUE) {
        opcode = __ByteRead(track);
        if (!(opcode & 0x80)) {
            // MIDI pitch (0-127)
            pitch = (u8)(opcode + track->finalTranspose);

            if ((bVar10 = __ByteRead(track)) & 0x80) {
                u8 exchangedPitch = __ExchangeRegisterValue(track, pitch);
                pitch = (u8)(exchangedPitch + track->finalTranspose);
            }

            if ((u8)pitch >= 128) {
                OSReport("♪Jam/Seq :: Error Note %d\n", (u8)pitch);
            }

            noteMode = bVar10;
            noteMode &= 0x60;
            noteMode >>= 5;
            if (noteMode & 2) {
                keyTarget = (u8)pitch;
                pitch = *(s8*)((u8*)track + 0xD5) & 0xff;
            }

            velocity = __ByteRead(track);
            if (velocity >= 0x80) {
                velocity = __ExchangeRegisterValue(track, velocity - 0x80);
            }

            u32 lowBits = bVar10;
            lowBits &= 7;
            if (lowBits == 0) {
                voice = 0;
                bVar9 = __ByteRead(track);
                if (bVar9 >= 0x80) {
                    bVar9 = __ExchangeRegisterValue(track, bVar9 - 0x80);
                }
                uVar2 = 0;
                for (iVar11 = 0; iVar11 < (bVar10 >> 3 & 3); iVar11++) {
                    uVar2 = uVar2 << 8 | __ByteRead(track);
                }
                if ((u32)(bVar10 >> 3 & 3) == 1 && uVar2 >= 0x80) {
                    uVar2 = __ExchangeRegisterValue(track, uVar2 - 0x80);
                }
            } else {
                voice = lowBits;
                // fake volatile for matching
                if (*(u8*)&bVar10 >> 3 & 3) {
                    voice = __ExchangeRegisterValue(track, voice - 1);
                    if (voice >= 8) {
                        break;
                    }
                }
                uVar2 = -1;
                bVar9 = 100;
            }

            track->_D4 = noteMode;

            BOOL cond = track->_D6 ? TRUE : FALSE;
            int voiceArg = voice;
            var_r26 = FALSE;

            for (int j = 0; j < 1; j++) {
                // u8* track_p = track->_94;
                int unused = j * 2;

                if (cond) {
                    duration = uVar2;
                    if (track->_D4 & 1) {
                        duration = -1;
                    }
                    if (duration != -1) {
                        duration = Jam_SEQtimeToDSPtime(track, duration, bVar9);
                    }
                    if (track->isPaused && (track->pauseStatus & 0x10)) {
                        iVar11_2 = -1;
                    } else {
                        u32 gatePitch = pitch;
                        gatePitch &= 0xff;
                        iVar11_2 = GateON(track, voiceArg, gatePitch, velocity, duration);
                    }
                } else {
                    if ((duration = uVar2) != -1) {
                        duration = Jam_SEQtimeToDSPtime(track, duration, bVar9);
                    }
                    if (track->_D4 & 1) {
                        duration = -1;
                    }
                    if (track->isPaused && (track->pauseStatus & 0x10)) {
                        iVar11_2 = -1;
                    } else {
                        u32 notePitch = pitch;
                        notePitch = (notePitch << 24) >> 24;
                        iVar11_2 = NoteON(track, voiceArg, notePitch, velocity, duration);
                    }
                }

                if (iVar11_2 != -1) {
                    track->_94[voice + j] = pitch;
                    var_r26 = TRUE;
                }
                !unused;
            }

            track->_90 = var_r26;
            track->_CC = bVar9;
            track->_CD = velocity;
            track->_D0 = uVar2;

            if (track->_D4 & 1) {
                track->_D6 = TRUE;
            } else {
                track->_D6 = FALSE;
            }

            if (track->_D4 & 2) {
                s32 steps = duration;
                if (duration == -1) {
                    steps = Jam_SEQtimeToDSPtime(track, uVar2, track->_CC);
                }
                SetKeyTarget_1Shot(track->channels[0], (u8)keyTarget + track->finalTranspose, steps);
                pitch = (u8)keyTarget;
            }

            track->_D5 = pitch;

            if (uVar2 != -1) {
                track->waitTimer = uVar2;
                if (uVar2 == 0) {
                    track->waitTimer = -1;
                }
                break;
            }
        } else if ((opcode & 0xf0) == 0x80 || opcode == 0xf9) {
            iVar11_3 = 1;
            uVar5 = 0;
            if (opcode == 0xf9) {
                bVar10_2 = __ByteRead(track);
                uVar6 = __ExchangeRegisterValue(track, bVar10_2 & 7);
                if (uVar6 > 7 || uVar6 == 0) {
                    OSReport("♪Jam/main :: r-noteoff error\n");
                    if ((bVar10_2 & 0x80) != 0) {
                        __ByteRead(track);
                    }
                    continue;
                }
                opcode = uVar6 + 0x80;
                if (bVar10_2 & 0x80) {
                    opcode += 8;
                }
            }
            uVar6 = opcode & 0x0f;
            if (uVar6 == 8) {
                iVar11_3 = 2;
                uVar6 -= 8;
            }
            if (uVar6 > 8) {
                uVar6 -= 8;
                uVar5 = __ByteRead(track);
                if (uVar5 > 100) {
                    uVar5 = (uVar5 - 98) * 20;
                }
            }
            if (uVar6 == 0) {
                // This for loop init feels fake... but idk.  Check this again later.
                for (track->waitTimer = iVar12 = 0; iVar12 < iVar11_3; iVar12++) {
                    track->waitTimer = track->waitTimer << 8 | __ByteRead(track);
                }
                if (track->waitTimer == 0) {
                    continue;
                }
                break;
            }
            if (uVar5 == 0) {
                NoteOFF(track, uVar6);
            } else {
                NoteOFF_R(track, uVar6, uVar5);
            }
        } else {
            // This portion is equivalent to `JASSeqParser::parseSeq` in later JAudio.
            u32 cmdResult = 0;
            if ((opcode & 0xf0) == 0x90) {
                Jam_WriteTimeParam(track, opcode & 0x0f);
            } else if ((opcode & 0xf0) == 0xa0) {
                Jam_WriteRegParam(track, opcode & 0x0f);
            } else if ((opcode & 0xf0) == 0xb0) {
                u32 param_3 = opcode & 7;
                cmdResult = RegCmd_Process(track, (opcode & 8) ? TRUE : FALSE, param_3);
            } else {
                cmdResult = Cmd_Process(track, opcode, 0);
            }

            if (cmdResult == 0) {
                continue;
            } else if (cmdResult == 1) {
                break;
            } else if (cmdResult == 2) {
                goto try_interrupt;
            } else if (cmdResult == 3) {
                return -1;
            } else if (cmdResult == 0x80) {
                OSReport("\x1b[4%dm", 1);
                OSReport("♪Jam/seq :: Sequence Error occerd... I try to continue\n");
                OSReport("\x1b[m");
            }
        }
    }

timed:
    // This portion is equivalent to `JASTrack::updateTimedParam` in later JAudio.
    for (int i = 0; i < 18; i++) {
        MoveParam_* move = &track->timedParam.move[i];
        if (move->duration > 0.0f) {
            move->currentValue += move->stepSize;
            move->duration -= 1.0f;
            if (i <= 5 || i >= 11) {
                seqRes |= (1 << i);
            } else {
                Osc_Update_Param(track, i, move->currentValue);
            }
        }
    }

    if (track->oscillatorRouting[0] == 0x0E) {
        seqRes |= osc_table[track->oscillators[0].mode];
    }
    if (track->oscillatorRouting[1] == 0x0E) {
        seqRes |= osc_table[track->oscillators[1].mode];
    }

LAB_800136e0:
    track->updateFlags |= seqRes;

    int childOffset;
    int i;
    i = 0;
    childOffset = 0;
    for (; i < 16; i++, childOffset += 4) {
        if ((*(seqp_**)((u8*)track + 0x44 + childOffset)) &&
            (*(seqp_**)((u8*)track + 0x44 + childOffset))->trackState != 0) {
            if (track != (*(seqp_**)((u8*)track + 0x44 + childOffset))->parent) {
                OSReport("##########Error:: Track %d の共有違反です\n", i);
            }
            BOOL childIsMuted = track->isMuted | ((track->childMuteMask & (1 << i)) >> i);
            if (Jam_SeqmainNote((*(seqp_**)((u8*)track + 0x44 + childOffset)), childIsMuted) == -1) {
                Jaq_CloseTrack((*(seqp_**)((u8*)track + 0x44 + childOffset)));
                (*(seqp_**)((u8*)track + 0x44 + childOffset)) = NULL;
            }
        }
    }

    return 0;
}
#pragma opt_dead_assignments reset

/*
 * --INFO--
 * Address:	80013780
 * Size:	0000A8
 */
void SeqUpdate(seqp_* track, u32 updateFlags)
{
	u32 finalFlags;
	size_t i;

	finalFlags = updateFlags | track->updateFlags;
	if (track->outerParams) {
		finalFlags |= track->outerParams->updateFlags;
		track->outerParams->updateFlags = 0;
	}

	track->updateFlags = OuterParamFlag_None;
	if (finalFlags) {
		Jam_UpdateTrack(track, finalFlags);
	}

	for (i = 0; i < 16; ++i) {
		if (track->children[i] && track->children[i]->trackState) {
			SeqUpdate(track->children[i], finalFlags);
		}
	}
}
