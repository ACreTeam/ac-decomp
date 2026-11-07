/*
 * --INFO--
 * Address:	80011800
 * Size:	000038
 */
static u32 Cmd_OpenTrack()
{
	Jaq_OpenTrack(SEQ_P, SEQ_ARG[0], SEQ_ARG[1]);
	return 0;
}

/*
 * --INFO--
 * Address:	80011840
 * Size:	000050
 */
static u32 Cmd_OpenTrackBros()
{
	if (SEQ_P->parent) {
		Jaq_OpenTrack(SEQ_P->parent, SEQ_ARG[0], SEQ_ARG[1]);
	} else {
		return 0x40;
	}
	return 0;
}

/*
 * --INFO--
 * Address:	800118A0
 * Size:	00003C
 */
static u32 Cmd_Call()
{
	SEQ_P->callStack[SEQ_P->callStackDepth++] = SEQ_P->programCounter;
	SEQ_P->programCounter                     = SEQ_ARG[0];
	return 0;
}

/*
 * --INFO--
 * Address:	800118E0
 * Size:	000100
 */
static u32 Cmd_CallF()
{
	u8 bVar1;
	u32 uVar2;
	u32 uVar3;
	u8 uVar4;

	bVar1 = __ByteRead(SEQ_P);
	if (bVar1 & 0x80) {
		uVar4 = __ByteRead(SEQ_P);
		uVar2 = Jam_ReadRegDirect(SEQ_P, uVar4);
		if (bVar1 & 0x40) {
			if (bVar1 & 0x20) {
				uVar4 = __ByteRead(SEQ_P);
				uVar3 = Jam_ReadRegDirect(SEQ_P, uVar4);
			} else {
				uVar3 = __24Read(SEQ_P);
			}
			uVar2 = __24ReadOfs(SEQ_P, uVar3 + uVar2 * 3);
		}
	} else {
		uVar2 = __24Read(SEQ_P);
	}
	if ((u8)__ConditionCheck(SEQ_P, bVar1 & 0x0f) == TRUE) {
		if (SEQ_CMD == (0xC0 + CMD_CALL_F)) {
			SEQ_P->callStack[SEQ_P->callStackDepth++] = SEQ_P->programCounter;
		}
		SEQ_P->programCounter = uVar2;
	}
	return 0;
}

/*
 * --INFO--
 * Address:	800119E0
 * Size:	000028
 */
static u32 Cmd_Ret()
{
	SEQ_P->programCounter = SEQ_P->callStack[--SEQ_P->callStackDepth];
	return 0;
}

/*
 * --INFO--
 * Address:	80011A20
 * Size:	000060
 */
static u32 Cmd_RetF()
{
	// But why cast it...?  And why check if it explicitly equals TRUE...?
	if ((u8)__ConditionCheck(SEQ_P, SEQ_ARG[0] & 0x0f) == TRUE) {
		SEQ_P->programCounter = SEQ_P->callStack[--SEQ_P->callStackDepth];
	}
	return 0;
}

/*
 * --INFO--
 * Address:	80011A80
 * Size:	00001C
 */
static u32 Cmd_Jmp()
{
	SEQ_P->programCounter = SEQ_ARG[1];
	return 0;
}

/*
 * --INFO--
 * Address:	80011AA0
 * Size:	000020
 */
static u32 Cmd_JmpF()
{
	Cmd_CallF();
}

/*
 * --INFO--
 * Address:	80011AC0
 * Size:	000048
 */
static u32 Cmd_LoopS()
{
	SEQ_P->callStack[SEQ_P->callStackDepth]      = SEQ_P->programCounter;
	SEQ_P->loopCounters[SEQ_P->callStackDepth++] = SEQ_ARG[0];
	return 0;
}

/*
 * --INFO--
 * Address:	80011B20
 * Size:	000078
 */
static u32 Cmd_LoopE()
{
	u16 uVar1;

	if (SEQ_P->callStackDepth == 0) {
		return 0x80;
	}

	uVar1 = SEQ_P->loopCounters[SEQ_P->callStackDepth - 1];
	if (uVar1 != 0) {
		uVar1 = (u16)(uVar1 - 1);
	}
    
	if (uVar1 == 0) {
		SEQ_P->callStackDepth -= 1;
		return 0;
	}

	SEQ_P->loopCounters[SEQ_P->callStackDepth - 1] = uVar1;
	SEQ_P->programCounter                          = SEQ_P->callStack[SEQ_P->callStackDepth - 1];
	return 0;
}

/*
 * --INFO--
 * Address:	80011BA0
 * Size:	000054
 */
static u32 Cmd_ReadPort()
{
	u16 temp;

	temp                                    = SEQ_P->trackPort[SEQ_ARG[0]].value;
	SEQ_P->trackPort[SEQ_ARG[0]].importFlag = 0;
	Jam_WriteRegDirect(SEQ_P, SEQ_ARG[1], temp);
	return 0;
}

/*
 * --INFO--
 * Address:	80011C00
 * Size:	000040
 */
static u32 Cmd_WritePort()
{
	SEQ_P->trackPort[SEQ_ARG[0]].value      = SEQ_ARG[1];
	SEQ_P->trackPort[SEQ_ARG[0]].exportFlag = 1;
	return 0;
}

/*
 * --INFO--
 * Address:	80011C40
 * Size:	000044
 */
static u32 Cmd_CheckPortImport()
{
	Jam_WriteRegDirect(SEQ_P, 3, SEQ_P->trackPort[SEQ_ARG[0]].importFlag);
	return 0;
}

/*
 * --INFO--
 * Address:	80011CA0
 * Size:	000044
 */
static u32 Cmd_CheckPortExport()
{
	Jam_WriteRegDirect(SEQ_P, 3, SEQ_P->trackPort[SEQ_ARG[0]].exportFlag);
	return 0;
}

/*
 * --INFO--
 * Address:	80011D00
 * Size:	00002C
 */
static u32 Cmd_WaitReg()
{
	SEQ_P->waitTimer = SEQ_ARG[0];
	return SEQ_ARG[0] ? 1 : 0;
}

/*
 * --INFO--
 * Address:	80011D40
 * Size:	000028
 */
static u32 Cmd_ConnectName()
{
	SEQ_P->connectionId = SEQ_ARG[0] << 16 | SEQ_ARG[1];
	return 0;
}

/*
 * --INFO--
 * Address:	80011D80
 * Size:	000040
 */
static u32 Cmd_ParentWritePort()
{
	Jam_WritePortAppDirect(SEQ_P->parent, SEQ_ARG[0] & 0x0f, SEQ_ARG[1]);
	return 0;
}

/*
 * --INFO--
 * Address:	80011DC0
 * Size:	000048
 */
static u32 Cmd_ChildWritePort()
{
	Jam_WritePortAppDirect(SEQ_P->children[(SEQ_ARG[0] >> 4)], SEQ_ARG[0] & 0x0f, SEQ_ARG[1]);
	return 0;
}

/*
 * --INFO--
 * Address:	80011E20
 * Size:	000030
 */
static u32 Cmd_SetLastNote()
{
	SEQ_P->_D5 = SEQ_ARG[0];
	SEQ_P->_D5 += SEQ_P->finalTranspose;
	return 0;
}

/*
 * --INFO--
 * Address:	80011E60
 * Size:	00001C
 */
static u32 Cmd_TimeRelate()
{
	SEQ_P->timeRelationMode = SEQ_ARG[0];
	return 0;
}

/*
 * --INFO--
 * Address:	80011E80
 * Size:	000034
 */
static u32 Cmd_SimpleOsc()
{
	Osc_Setup_Simple(SEQ_P, SEQ_ARG[0]);
	return 0;
}

/*
 * --INFO--
 * Address:	80011EC0
 * Size:	000038
 */
static u32 Cmd_SimpleEnv()
{
	Osc_Setup_SimpleEnv(SEQ_P, SEQ_ARG[0], SEQ_ARG[1]);
	return 0;
}

/*
 * --INFO--
 * Address:	80011F00
 * Size:	000064
 */
static u32 Cmd_SimpleADSR()
{
	int i;
	s16 local_10[5];

	for (i = 0; i < 5; ++i) {
		local_10[i] = SEQ_ARG[i];
	}
	Osc_Setup_ADSR(SEQ_P, local_10);
	return 0;
}

/*
 * --INFO--
 * Address:	80011F80
 * Size:	000048
 */
static u32 Cmd_Transpose()
{
	SEQ_P->transpose = SEQ_ARG[0];
	if (SEQ_P->parent) {
		SEQ_P->finalTranspose = SEQ_P->parent->transpose + SEQ_P->transpose;
	} else {
		SEQ_P->finalTranspose = SEQ_P->transpose;
	}
	return 0;
}

/*
 * --INFO--
 * Address:	80011FE0
 * Size:	000068
 */
static u32 Cmd_CloseTrack()
{
	u8 index = SEQ_ARG[0];
	if (index >= (u32)ARRAY_COUNT(SEQ_P->children)) {
		return 0x80;
	}
	Jaq_CloseTrack(SEQ_P->children[index]);
	SEQ_P->children[index] = NULL;
	return 0;
}

/*
 * --INFO--
 * Address:	80012060
 * Size:	000038
 */
static u32 Cmd_OutSwitch()
{
	if (SEQ_P->outerParams) {
		SEQ_P->outerParams->flags       = SEQ_ARG[0];
		SEQ_P->outerParams->updateFlags = -1;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	800120A0
 * Size:	000034
 */
static u32 Cmd_UpdateSync()
{
	Jam_UpdateTrack(SEQ_P, SEQ_ARG[0]);
	return 0;
}

/*
 * --INFO--
 * Address:	800120E0
 * Size:	00002C
 */
static u32 Cmd_BusConnect()
{
	if (SEQ_ARG[0] < 6) {
		SEQ_P->parentController.busConnect[SEQ_ARG[0]] = SEQ_ARG[1];
	}
	return 0;
}

/*
 * --INFO--
 * Address:	80012120
 * Size:	00001C
 */
static u32 Cmd_PauseStatus()
{
	SEQ_P->pauseStatus = SEQ_ARG[0];
	return 0;
}

/*
 * --INFO--
 * Address:	80012140
 * Size:	000044
 */
static u32 Cmd_SetInterrupt()
{
	SEQ_P->interruptEnable |= (1 << SEQ_ARG[0]);
	SEQ_P->interruptAddresses[SEQ_ARG[0]] = SEQ_ARG[1];
	return 0;
}

/*
 * --INFO--
 * Address:	800121A0
 * Size:	000030
 */
static u32 Cmd_DisInterrupt()
{
	u8 arg;
	arg = SEQ_ARG[0];
	arg = 1 << arg;
    arg = ~arg;
	SEQ_P->interruptEnable &= arg;
	return 0;
}

/*
 * --INFO--
 * Address:	800121E0
 * Size:	000014
 */
static u32 Cmd_ClrI()
{
	SEQ_P->interruptActive = 0;
	return 0;
}

/*
 * --INFO--
 * Address:	80012200
 * Size:	000014
 */
static u32 Cmd_SetI()
{
	SEQ_P->interruptActive = 1;
	return 0;
}

/*
 * --INFO--
 * Address:	80012220
 * Size:	00002C
 */
static u32 Cmd_RetI()
{
	SEQ_P->waitTimer       = SEQ_P->_3CC;
	SEQ_P->interruptActive = 0;
	SEQ_P->programCounter  = SEQ_P->savedProgramCounter;
	return 2;
}

/*
 * --INFO--
 * Address:	80012260
 * Size:	000034
 */
static u32 Cmd_IntTimer()
{
	SEQ_P->timerCount = SEQ_ARG[0];
	SEQ_P->timer      = SEQ_ARG[1];
	SEQ_P->maxTime    = SEQ_ARG[1];
	return 0;
}

/*
 * --INFO--
 * Address:	800122A0
 * Size:	00002C
 */
static u32 Cmd_ConnectOpen()
{
	Jam_RegistTrack(SEQ_P, SEQ_P->connectionId);
	return 0;
}

/*
 * --INFO--
 * Address:	800122E0
 * Size:	000028
 */
static u32 Cmd_ConnectClose()
{
	Jam_UnRegistTrack(SEQ_P);
	return 0;
}

/*
 * --INFO--
 * Address:	80012320
 * Size:	000060
 */
static u32 Cmd_SyncCPU()
{
	u16 seq_arg;
	u16 param_3;

	seq_arg = SEQ_ARG[0];
	if (JAM_CALLBACK_FUNC) {
		param_3 = JAM_CALLBACK_FUNC(SEQ_P, seq_arg);
	} else {
		param_3 = 0xffff;
	}
	Jam_WriteRegDirect(SEQ_P, 3, param_3);
	return 0;
}

/*
 * --INFO--
 * Address:	80012380
 * Size:	000038
 */
static u32 Cmd_FlushAll()
{
	AllStop_1Shot(&SEQ_P->parentController);
	FlushRelease_1Shot(&SEQ_P->parentController);
	return 0;
}

/*
 * --INFO--
 * Address:	800123C0
 * Size:	00002C
 */
static u32 Cmd_FlushRelease()
{
	FlushRelease_1Shot(&SEQ_P->parentController);
	return 0;
}

/*
 * --INFO--
 * Address:	80012400
 * Size:	00002C
 */
static u32 Cmd_Wait3()
{
	SEQ_P->waitTimer = SEQ_ARG[0];
	return SEQ_ARG[0] ? 1 : 0;
}

/*
 * --INFO--
 * Address:	80012440
 * Size:	000044
 */
static u32 Cmd_TimeBase()
{
	SEQ_P->timeBase = SEQ_ARG[0];
	if (!SEQ_P->parent) {
		Jam_UpdateTempo(SEQ_P);
	}
	return 0;
}

/*
 * --INFO--
 * Address:	800124A0
 * Size:	000050
 */
static u32 Cmd_Tempo()
{
	SEQ_P->tempo = SEQ_ARG[0];
	if (!SEQ_P->parent) {
		Jam_UpdateTempo(SEQ_P);
	} else {
		SEQ_P->doChangeTempo = TRUE;
	}
	return 0;
}

/*
 * --INFO--
 * Address:	80012500
 * Size:	0000CC
 */
static u32 Cmd_Finish()
{
	size_t i;
	u32 updateFlags;
	MoveParam_* temp;

	updateFlags = 0;
	for (i = 0; i < 18; ++i) {
		temp = &SEQ_P->timedParam.move[i];
		if (temp->duration > 0.0f) {
			temp->currentValue += temp->stepSize;
			temp->duration -= 1.0f;
			if (i <= 5 || i >= 11) {
				updateFlags |= 1 << i;
			} else {
				Osc_Update_Param(SEQ_P, i, temp->currentValue);
			}
		}
	}
	SeqUpdate(SEQ_P, updateFlags);

	return 3;
}

/*
 * --INFO--
 * Address:	800125E0
 * Size:	000008
 */
static u32 Cmd_Nop()
{
	return 0;
}

/*
 * --INFO--
 * Address:	80012600
 * Size:	0000AC
 */
static u32 Cmd_PanPowSet()
{
	size_t i;

	for (i = 0; i < 3; ++i) {
		SEQ_P->regParam.param.arguments[i] = SEQ_ARG[i];
	}
	for (i = 3; i < 5; ++i) {
		SEQ_P->regParam.param.arguments[i] = SEQ_ARG[i] * 327.67f;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	800126C0
 * Size:	000094
 */
static u32 Cmd_IIRSet()
{

	size_t i;
	MoveParam_* iir;

	for (i = 0; i < 4; ++i) {
		iir               = &SEQ_P->timedParam.move[i + 12]; // IIRs 0 - 4 are at 12-15
		iir->targetValue  = (s16)SEQ_ARG[i] / 32768.0f;
		iir->currentValue = iir->targetValue;
		iir->stepSize     = 0.0f;
		iir->duration     = 1.0f;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	80012760
 * Size:	000044
 */
static u32 Cmd_FIRSet()
{
	Jam_SetExtFirFilterD(SEQ_P->outerParams, (s16*)Jam_OfsToAddr(SEQ_P, SEQ_ARG[0]));
	return 0;
}

/*
 * --INFO--
 * Address:	800127C0
 * Size:	000050
 */
static u32 Cmd_EXTSet()
{
	OuterParam_* ext;

	ext = (OuterParam_*)Jam_OfsToAddr(SEQ_P, SEQ_ARG[0]);
	Jam_InitExtBuffer(ext);
	Jam_AssignExtBuffer(SEQ_P, ext);
	return 0;
}

/*
 * --INFO--
 * Address:	80012820
 * Size:	0000C4
 */
static u32 Cmd_PanSwSet()
{
	size_t i;

	// Ah yes, let's just construct this on the stack real quick.
	u8 calcTypes[]       = { 0, 0, 0, 1, 1, 2, 2 };
	u8 parentCalcTypes[] = { 0, 1, 2, 0, 2, 0, 2 };

	for (i = 0; i < 3; ++i) {
		SEQ_P->panCalcTypes[i]                  = calcTypes[SEQ_ARG[i] >> 5];
		SEQ_P->parentPanCalcTypes[i]            = parentCalcTypes[SEQ_ARG[i] >> 5];
		SEQ_P->parentController.panCalcTypes[i] = SEQ_ARG[i] & 0x1f;
		SEQ_P->updateFlags |= OuterParamFlag_Pan;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	80012900
 * Size:	000040
 */
static u32 Cmd_OscRoute()
{
	u8 uVar2;
	u8 oscRoute;

	uVar2    = SEQ_ARG[0] >> 4 & 0xf;
	oscRoute = SEQ_ARG[0] & 0xf;

	SEQ_P->oscillatorRouting[uVar2] = oscRoute;
	if (oscRoute == 14) {
		SEQ_P->oscillatorParams[uVar2].state = 1;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	80012940
 * Size:	0000A0
 */
static u32 Cmd_IIRCutOff()
{
	u8 index;
	size_t i;
	MoveParam_* iir;

	index = SEQ_ARG[0];
	for (i = 0; i < 4; ++i) {
		iir               = &SEQ_P->timedParam.move[i + 12]; // IIRs 0 - 4 are at 12-15
		iir->targetValue  = CUTOFF_TO_IIR_TABLE[index][i] / 32767.0f;
		iir->currentValue = iir->targetValue;
		iir->stepSize     = 0.0f;
		iir->duration     = 1.0f;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	800129E0
 * Size:	000040
 */
static u32 Cmd_OscFull()
{
	Osc_Setup_Full(SEQ_P, SEQ_ARG[0], SEQ_ARG[1], SEQ_ARG[2]);
	return 0;
}

/*
 * --INFO--
 * Address:	80012A20
 * Size:	000068
 */
static u32 Cmd_CheckWave()
{
	SOUNDID_ soundID;
	u32 uVar2;

	soundID.value = SEQ_ARG[0] | (Jam_ReadRegDirect(SEQ_P, 6) << 16);
	uVar2         = One_CheckInstWave(soundID);
	Jam_WriteRegDirect(SEQ_P, 3, (u8)uVar2);
	return 0;
}

/*
 * --INFO--
 * Address:	80012AA0
 * Size:	000204
 */
static u32 Cmd_Printf()
{
	char fmtStr[0x80];
	u8 fmtFlags[4];
	u32 fmtParms[4];
	size_t fmtCount;
	size_t i;

	fmtCount = 0;
	for (i = 0; i < (u32)ARRAY_COUNT(fmtStr); ++i) {
		fmtStr[i] = __ByteRead(SEQ_P);
		if (fmtStr[i] == '\0') {
			// Handle end of string
			break;
		}
		if (fmtStr[i] == '\\') {
			// Handle escape sequences (just the one)
			fmtStr[i] = __ByteRead(SEQ_P);

			if (fmtStr[i] == '\0') {
				// Unexpected end of string!
				break;
			}
			switch (fmtStr[i]) {
			case 'n':
				// Convert newlines to... carriage returns?
				fmtStr[i] = '\r';
				break;
			}
			continue;
		}
		if (fmtStr[i] == '%') {
			// Handle conversion specifiers (plus a few custom ones!)
			++i;
			fmtStr[i] = __ByteRead(SEQ_P);

			if (fmtStr[i] == '\0') {
				// Unexpected end of string!
				break;
			}
			switch (fmtStr[i]) {
			case 'd': // Decimal
				fmtFlags[fmtCount] = 0;
				break;
			case 'x': // Hexadecimal
				fmtFlags[fmtCount] = 1;
				break;
			case 's': // String
				fmtFlags[fmtCount] = 2;
				break;
			case 'r': // ?
				fmtFlags[fmtCount] = 3;
				fmtStr[i]          = 'd';
				break;
            case 'R':
				fmtFlags[fmtCount] = 4;
				fmtStr[i]          = 'x';
				break;
			}
			++fmtCount;
			continue;
		}
	}
	for (i = 0; i < fmtCount; ++i) {
		fmtParms[i] = __ByteRead(SEQ_P);
		if (fmtFlags[i] == 2) {
			fmtParms[i] = (u32)Jam_OfsToAddr(SEQ_P, fmtParms[i]);
		// } else if (fmtFlags[i] == 5) {
		// 	fmtParms[i] = SEQ_P->trackId;
		}
        
        if (fmtFlags[i] >= 3) {
			fmtParms[i] = __ExchangeRegisterValue(SEQ_P, fmtParms[i]);
		}
	}
	// A restoration of this command's functionality can be enabled below:
	OSReport(fmtStr, fmtParms[0], fmtParms[1], fmtParms[2], fmtParms[3]);
	return 0;
}

static Arghead_ Arglist[CMD_COUNT] = {
	{ 0, 0x0000 }, //
	{ 2, 0x0008 }, // OpenTrack
	{ 2, 0x0008 }, // OpenTrackBros
	{ 1, 0x0002 }, // Call
	{ 0, 0x0000 }, // CallF
	{ 0, 0x0000 }, // Ret
	{ 1, 0x0000 }, // RetF
	{ 1, 0x0002 }, // Jmp
	{ 0, 0x0000 }, // JmpF
	{ 1, 0x0001 }, // LoopS
	{ 0, 0x0000 }, // LoopE
	{ 2, 0x0000 }, // ReadPort
	{ 2, 0x000c }, // WritePort
	{ 1, 0x0000 }, // CheckPortImport
	{ 1, 0x0000 }, // CheckPortExport
	{ 1, 0x0003 }, // WaitReg
	{ 2, 0x0005 }, // ConnectName
	{ 2, 0x000c }, // ParentWritePort
	{ 2, 0x000c }, // ChildWritePort
	{ 2, 0x000f }, //
	{ 1, 0x0000 }, // SetLastNote
	{ 1, 0x0000 }, // TimeRelate
	{ 1, 0x0000 }, // SimpleOsc
	{ 2, 0x0008 }, // SimpleEnv
	{ 5, 0x0155 }, // SimpleADSR
	{ 1, 0x0000 }, // Transpose
	{ 1, 0x0000 }, // CloseTrack
	{ 1, 0x0000 }, // OutSwitch
	{ 1, 0x0001 }, // UpdateSync
	{ 2, 0x0004 }, // BusConnect
	{ 1, 0x0000 }, // PauseStatus
	{ 2, 0x0008 }, // SetInterrupt
	{ 1, 0x0000 }, // DisInterrupt
	{ 0, 0x0000 }, // ClrI
	{ 0, 0x0000 }, // SetI
	{ 0, 0x0000 }, // RetI
	{ 2, 0x0004 }, // IntTimer
	{ 0, 0x0000 }, // ConnectOpen
	{ 0, 0x0000 }, // ConnectClose
	{ 1, 0x0001 }, // SyncCPU
	{ 0, 0x0000 }, // FlushAll
	{ 0, 0x0000 }, // FlushRelease
	{ 1, 0x0002 }, // Wait3
	{ 5, 0x0000 }, // PanPowSet
	{ 4, 0x0055 }, // IIRSet
	{ 1, 0x0002 }, // FIRSet
	{ 1, 0x0002 }, // EXTSet
	{ 3, 0x0000 }, // PanSwSet
	{ 1, 0x0000 }, // OscRoute
	{ 1, 0x0000 }, // IIRCutOff
	{ 3, 0x0028 }, // OscFull
	{ 0, 0x0000 }, //
	{ 0, 0x0000 }, //
	{ 0, 0x0000 }, //
	{ 0, 0x0000 }, //
	{ 0, 0x0000 }, //
	{ 0, 0x0000 }, //
	{ 0, 0x0000 }, //
	{ 1, 0x0001 }, // CheckWave
	{ 0, 0x0000 }, // Printf
	{ 0, 0x0000 }, // Nop
	{ 1, 0x0001 }, // Tempo
	{ 1, 0x0001 }, // TimeBase
	{ 0, 0x0000 }, // Finish

};

static CmdFunction CMDP_LIST[CMD_COUNT] = {
	NULL,
	Cmd_OpenTrack,
	Cmd_OpenTrackBros,
	Cmd_Call,
	Cmd_CallF,
	Cmd_Ret,
	Cmd_RetF,
	Cmd_Jmp,
	Cmd_JmpF,
	Cmd_LoopS,
	Cmd_LoopE,
	Cmd_ReadPort,
	Cmd_WritePort,
	Cmd_CheckPortImport,
	Cmd_CheckPortExport,
	Cmd_WaitReg,
	Cmd_ConnectName,
	Cmd_ParentWritePort,
	Cmd_ChildWritePort,
	NULL,
	Cmd_SetLastNote,
	Cmd_TimeRelate,
	Cmd_SimpleOsc,
	Cmd_SimpleEnv,
	Cmd_SimpleADSR,
	Cmd_Transpose,
	Cmd_CloseTrack,
	Cmd_OutSwitch,
	Cmd_UpdateSync,
	Cmd_BusConnect,
	Cmd_PauseStatus,
	Cmd_SetInterrupt,
	Cmd_DisInterrupt,
	Cmd_ClrI,
	Cmd_SetI,
	Cmd_RetI,
	Cmd_IntTimer,
	Cmd_ConnectOpen,
	Cmd_ConnectClose,
	Cmd_SyncCPU,
	Cmd_FlushAll,
	Cmd_FlushRelease,
	Cmd_Wait3,
	Cmd_PanPowSet,
	Cmd_IIRSet,
	Cmd_FIRSet,
	Cmd_EXTSet,
	Cmd_PanSwSet,
	Cmd_OscRoute,
	Cmd_IIRCutOff,
	Cmd_OscFull,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	Cmd_CheckWave,
	Cmd_Printf,
	Cmd_Nop,
	Cmd_Tempo,
	Cmd_TimeBase,
	Cmd_Finish,
};

