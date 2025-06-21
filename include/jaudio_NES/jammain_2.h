#ifndef _JAUDIO_JAMMAIN_2_H
#define _JAUDIO_JAMMAIN_2_H

#include "types.h"

#include "jaudio_NES/audiostruct.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

//! NOTE from intns:
//! There's something iffy going on with the value 0xC0.
//! It appears in seqsetup with flags regarding opening tracks,
//! It appears to do with command id(s) for some reason
//! It's everywhere, but why? Why, J(esus)System?

typedef struct seqp_ seqp_;
typedef struct TrackPort_ TrackPort_;
typedef struct MoveParam_ MoveParam_;
typedef struct AInnerParam_ AInnerParam_;
typedef union TimedParam_ TimedParam_;
typedef struct OuterParam_ OuterParam_;
typedef struct RegisterParam_ RegisterParam_;
typedef union URegisterParam_ URegisterParam_;

typedef u32 (*CmdFunction)();              // TODO: Confirm return type
typedef u16 (*TrackCallback)(seqp_*, u16); // TODO: Confirm return type

typedef enum {
	OuterParamFlag_None       = 0,
	OuterParamFlag_Volume     = 1 << 0,
	OuterParamFlag_Pitch      = 1 << 1,
	OuterParamFlag_Fxmix      = 1 << 2,
	OuterParamFlag_Pan        = 1 << 3,
	OuterParamFlag_Dolby      = 1 << 4,
	OuterParamFlag_DistFilt   = 1 << 5,
	OuterParamFlag_Tempo      = 1 << 6,
	OuterParamFlag_FIR8Filter = 1 << 7, // Probably related to FIR filter

	OuterParamFlag_IIR0      = 1 << 12, // IIR0 filter
	OuterParamFlag_IIR1      = 1 << 13, // IIR1 filter
	OuterParamFlag_IIR2      = 1 << 14, // IIR2 filter
	OuterParamFlag_IIR3      = 1 << 15, // IIR3 filter
	OuterParamFlag_IIRFilter = (OuterParamFlag_IIR0 | OuterParamFlag_IIR1 | OuterParamFlag_IIR2 | OuterParamFlag_IIR3),

	SEQTRACK_FLAG_MASTER_LEVEL = 1 << 17 // TODO: suspicious, unknown use
} OuterParamFlag;

typedef enum {
	CMD_NONE_0 = 0,        // 0
	CMD_OPEN_TRACK,        // 1
	CMD_OPEN_TRACK_BROS,   // 2
	CMD_CALL,              // 3
	CMD_CALL_F,            // 4
	CMD_RETURN,            // 5
	CMD_RETURN_F,          // 6
	CMD_JUMP,              // 7
	CMD_JUMP_F,            // 8
	CMD_LOOP_START,        // 9
	CMD_LOOP_END,          // 10
	CMD_READ_PORT,         // 11
	CMD_WRITE_PORT,        // 12
	CMD_CHECK_PORT_IMPORT, // 13
	CMD_CHECK_PORT_EXPORT, // 14
	CMD_WAIT_REGISTER,     // 15
	CMD_CONNECT_NAME,      // 16
	CMD_PARENT_WRITE_PORT, // 17
	CMD_CHILD_WRITE_PORT,  // 18
	CMD_NONE_1,            // 19
	CMD_SET_LAST_NOTE,     // 20
	CMD_TIME_RELATE,       // 21
	CMD_SIMPLE_OSC,        // 22
	CMD_SIMPLE_ENV,        // 23
	CMD_SIMPLE_ADSR,       // 24
	CMD_TRANSPOSE,         // 25
	CMD_CLOSE_TRACK,       // 26
	CMD_OUTPUT_SWITCH,     // 27
	CMD_UPDATE_SYNC,       // 28
	CMD_BUS_CONNECT,       // 29
	CMD_PAUSE_STATUS,      // 30
	CMD_SET_INTERRUPT,     // 31
	CMD_DISABLE_INTERRUPT, // 32
	CMD_CLEAR_I,           // 33
	CMD_SET_I,             // 34
	CMD_RETURN_I,          // 35
	CMD_INTERRUPT_TIMER,   // 36
	CMD_CONNECT_OPEN,      // 37
	CMD_CONNECT_CLOSE,     // 38
	CMD_SYNC_CPU,          // 39
	CMD_FLUSH_ALL,         // 40
	CMD_FLUSH_RELEASE,     // 41
	CMD_WAIT_3,            // 42
	CMD_PAN_POWER_SET,     // 43
	CMD_IIR_SET,           // 44
	CMD_FIR_SET,           // 45
	CMD_EXT_SET,           // 46
	CMD_PAN_SWITCH_SET,    // 47
	CMD_OSC_ROUTE,         // 48
	CMD_IIR_CUTOFF,        // 49
	CMD_OSC_FULL,          // 50
	CMD_NONE_2,            // 51
	CMD_NONE_3,            // 52
	CMD_NONE_4,            // 53
	CMD_NONE_5,            // 54
	CMD_NONE_6,            // 55
	CMD_NONE_7,            // 56
	CMD_NONE_8,            // 57
	CMD_CHECK_WAVE,        // 58
	CMD_PRINTF,            // 59
	CMD_NOP,               // 60
	CMD_TEMPO,             // 61
	CMD_TIME_BASE,         // 62
	CMD_FINISH,            // 63
	CMD_COUNT              // 64
} CommandID;

/**
 * @brief This is an invented type of an unknown name.
 *
 * @note Size: 4
 */
struct TrackPort_ {
	u8 importFlag; // _00
	u8 exportFlag; // _01
	u16 value;     // _02
};

/**
 * @brief Name borrowed from `JASTrack.h` from Pikmin 2.
 *
 * @note Size: 16
 */
struct MoveParam_ {
	f32 currentValue; // _00
	f32 targetValue;  // _04
	f32 duration;     // _08
	f32 stepSize;     // _0C
};

/**
 * @brief Name borrowed from `JASTrack.h` from Pikmin 2.
 *
 * @note Size: 0x120
 */
struct AInnerParam_ {
	MoveParam_ volume;     // _00
	MoveParam_ pitch;      // _10
	MoveParam_ fxmix;      // _20
	MoveParam_ pan;        // _30
	MoveParam_ dolby;      // _40
	MoveParam_ distFilter; // _50
	MoveParam_ osc0Width;  // _60
	MoveParam_ osc0Rate;   // _70
	MoveParam_ osc0Vertex; // _80
	MoveParam_ osc1Width;  // _90
	MoveParam_ osc1Rate;   // _A0
	MoveParam_ osc1Vertex; // _B0
	MoveParam_ IIRs[4];    // _C0
	MoveParam_ _100;       // _100
	MoveParam_ _110;       // _110
};

union TimedParam_ {
	AInnerParam_ inner;  // Get individual params by member name
	MoveParam_ move[18]; // Get individual params by index
};

/**
 * @brief Name borrowed from `JASTrack.h` from Pikmin 2.
 *
 * @note Size: 0x40.
 */
struct OuterParam_ {
	BOOL isAssigned;        // _00
	u32 refCount;           // _04
	u16 flags;              // _08
	u16 updateFlags;        // _0A
	f32 volume;             // _0C
	f32 fxMix;              // _10
	f32 dolby;              // _14
	f32 pitch;              // _18
	f32 pan;                // _1C
	f32 tempo;              // _20
	s16 firCoefficients[8]; // _24
	u8 _34[0x40 - 0x34];    // _34
};

/**
 * @brief Name borrowed from `JASRegisterParam.h` from Pikmin 2.
 *
 * @note Size: 0x40.
 */
struct RegisterParam_ {
	u8 _00[0x06 - 0x00]; // _00, 00 - 02
	u16 value;           // _06, 03
	u8 _08[0x0C - 0x08]; // _08, 04 - 05
	u16 bankNumber;      // _0C, 06
	u16 pitchScale;      // _0E, 07
	u16 arguments[5];    // _10, 08 - 12, Exact length confirmed: `Cmd_PanPowSet`.
	u16 basePriority;    // _1A, 13
	u8 _1C[0x20 - 0x1C]; // _1C, 14
	u32 _20[4];          // _20, 15 - 22, Exact length semi-confirmed; Pikmin 2 also says 4.
	u8 _30[0x40 - 0x30]; // _1C, 23 - 31
};

/**
 * @brief Invented struct necessitated by behavior in `seqsetup.c`.
 *
 * @note Size: 0x40.
 */
union URegisterParam_ {
	RegisterParam_ param;
	u16 reg[32];
};

/**
 * @brief This struct is analogous to `JASTrack` of later JAudio.
 *
 * @note Size: 0x434 (Confirmed by `Jaf_HandleToSeq`).
 */
struct seqp_ {
	u8* baseData;                      // _000
	u32 programCounter;                // _004
	u32 callStackDepth;                // _008
	u32 callStack[2];                  // _00C, Exact length unknown, but it is an array.
	u8 _10[0x02c - 0x014];             // _008
	u16 loopCounters[2];               // _02C, Exact length unknown, but it is an array.
	u8 _30[0x03c - 0x030];             // _030
	u8 trackState;                     // _03C, Confirmed unsigned by switch cases
	u8 dataSourceMode;                 // _03D
	u8 fileHandle;                     // _03E
	u8 flags;                          // _03F
	seqp_* parent;                     // _040
	seqp_* children[16];               // _044
	u32 connectionId;                  // _084
	u32 trackId;                       // _088
	s32 waitTimer;                     // _08C
	u32 _90;                           // _090
	u8 _94[8];                         // _094
	jc_* channels[8];                  // _09C
	u16 activeSoundIds[8];             // _0BC
	u8 _CC;                            // _0CC
	u8 _CD;                            // _0CD
	u8 _CE[0x0d0 - 0x0ce];             // _0CE
	u32 _D0;                           // _0D0
	u8 _D4;                            // _0D4
	u8 _D5;                            // _0D5
	u8 _D6;                            // _0D6, boolean-like
	u8 _D7[0x0d8 - 0x0d7];             // _0D7
	jcs_ parentController;             // _0D8
	TimedParam_ timedParam;            // _14C
	URegisterParam_ regParam;          // _26C
	OuterParam_* outerParams;          // _2AC
	OuterParam_* childOuterParams[16]; // _2B0
	TrackPort_ trackPort[16];          // _2F0
	f32 tempoAccumulator;              // _330
	f32 tempoFactor;                   // _334
	u16 timeBase;                      // _338
	u16 tempo;                         // _33A
	u8 timeRelationMode;               // _33C
	u8 _33D;                           // _33D
	Osc_ oscillators[2];               // _340
	u8 oscillatorRouting[2];           // _370
	s16 adsTable[12];                  // _372
	s16 relTable[6];                   // _38A
	s8 transpose;                      // _396
	u8 finalTranspose;                 // _397
	s32 tickCounter;                   // _398
	u8 isPaused;                       // _39C, boolean-like
	u8 pauseStatus;                    // _39D
	u8 isMuted;                        // _39E, boolean-like
	u8 _39F[0x3a0 - 0x39f];            // _39F
	u16 childMuteMask;                 // _3A0
	u8 _3A2[0x3a4 - 0x3a2];            // _3A2
	u8 interruptActive;                // _3A4
	u8 interruptPending;               // _3A5
	u8 interruptEnable;                // _3A6
	u8 timerCount;                     // _3A7
	u32 interruptAddresses[8];         // _3A8
	u32 savedProgramCounter;           // _3C8
	u32 _3CC;                          // _3CC, to do with timers (CMD_IntTimer)
	u32 timer;                         // _3D0, to do with timers (CMD_IntTimer)
	u32 maxTime;                       // _3D4, to do with timers (CMD_IntTimer)
	u32 updateFlags;                   // _3D8, see `SEQTRACK_FLAG_*` defines
	u8 panCalcTypes[3];                // _3DC
	u8 parentPanCalcTypes[3];          // _3DF
	u8 isRegistered;                   // _3E2
	u8 doChangeTempo;                  // _3E3, boolean-like
	u8 _3E4;                           // _3E4
	u8 _3E5[0x3e8 - 0x3e5];            // _3E5
	Oscbuf_ oscillatorParams[2];       // _3E8
	u8 _418[0x434 - 0x418];            // _400
};

extern s16 CUTOFF_TO_IIR_TABLE[128][4];

void* Jam_OfsToAddr(seqp_*, u32);
void Jam_WriteRegDirect(seqp_*, u8, u16);
void Jam_WriteRegParam(seqp_*, u8);
u16 Jam_ReadRegDirect(seqp_*, u8);
u32 Jam_ReadReg32(seqp_* track, u8 index);
void Jam_WriteRegXY(seqp_* track, u32 param_2);
void Jam_WritePortApp(void);
void Jam_ReadPortApp(void);
void Jam_CheckExportApp(void);
void Jam_CheckImportApp(void);
void Jam_WritePortIndirect(void);
void Jam_ReadPortIndirect(void);
void Jam_CheckPortIndirect(void);
BOOL Jam_WritePortAppDirect(seqp_*, u32, u16);
BOOL Jam_ReadPortAppDirect(seqp_*, u32, u16*);
BOOL Jam_CheckPortAppDirect(seqp_*, u32, u16);
void Jam_WritePort(void);
void Jam_ReadPort(void);
void Jam_WritePortChild(void);
void Jam_WritePortBros(void);
void Jam_InitRegistTrack(void);
void Jam_UnRegistTrack(seqp_*);
seqp_* Jam_GetTrackHandle(u32);
void Jam_InitExtBuffer(OuterParam_*);
BOOL Jam_AssignExtBuffer(seqp_*, OuterParam_*);
BOOL Jam_AssignExtBufferP(seqp_*, u8, OuterParam_*);
void Jam_SetExtFirFilterD(OuterParam_*, s16*);
void Jam_SetExtParamD(f32, OuterParam_*, u8);
void Jam_OnExtSwitchD(OuterParam_*, u16);
void Jam_OffExtSwitchD(OuterParam_*, u16);
void Jam_SetExtSwitchDirectD(void);
void Jam_SetExtFirFilter(void);
void Jam_SetExtParam(f32, seqp_*, u8);
void Jam_OnExtSwitch(seqp_*, u16);
void Jam_OffExtSwitch(seqp_*, u16);
void Jam_SetExtSwitchDirect(void);
void Jam_SetExtFirFilterP(void);
void Jam_SetExtParamP(f32, seqp_*, u8, u8);
void Jam_OnExtSwitchP(seqp_*, u8, u16);
void Jam_OffExtSwitchP(seqp_*, u8, u16);
void Jam_SetExtSwitchDirectP(void);
void Jam_CheckRunningCounter(void);
BOOL Jam_RegisterTrackCallback(TrackCallback);
void Jam_SetTrackExtPanPower(void);
void Jam_UpdateTrackAll(seqp_*);
void Jam_UpdateTrack(seqp_*, u32);
void Jam_UpdateTempo(seqp_*);
void Jam_MuteTrack(seqp_*, u8);
void Jam_MuteChildTracks(void);
void Jam_PauseTrack(seqp_*, u8);
void Jam_UnPauseTrack(seqp_*, u8);
void Jam_SetInterrupt(seqp_*, u16);
BOOL Jam_TryInterrupt(seqp_*);
s32 Jam_SeqmainNote(seqp_*, u8);
void SeqUpdate(seqp_*, u32);

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
