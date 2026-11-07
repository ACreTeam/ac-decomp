/*
 * --INFO--
 * Address:	8000F8C0
 * Size:	000020
 */
u16 Extend8to16(u8 value)
{
	if (value & 0x80) {
		return value + 0xFF00;
	}
	return value;
}

/*
 * --INFO--
 * Address:	8000F8E0
 * Size:	0001A8
 */
void Jam_WriteTimeParam(seqp_* track, u8 controlByte)
{

	s32 duration;
	u8 paramIndex;
	s16 targetValue;
	MoveParam_* param;

	duration   = 0;
	paramIndex = __ByteRead(track);

	// Extract target value based on controlByte[3:2]
	switch (controlByte & 0x0C) {
	case 0x00: // Use register value
		targetValue = track->regParam.reg[__ByteRead(track)];
		break;
	case 0x04: // 8-bit immediate value
		targetValue = __ByteRead(track);
		break;
	case 0x08: // 8-bit value shifted to high byte
		targetValue = __ByteRead(track) << 8;
		break;
	case 0x0C: // 16-bit immediate value
		targetValue = __WordRead(track);
		break;
	}

	// Determine time over which to interpolate the parameter
	switch (controlByte & 0x03) {
	case 0: // Immediate (no interpolation)
		duration = -1;
		break;
	case 1: // Time from register
		duration = track->regParam.reg[__ByteRead(track)];
		break;
	case 2: // 8-bit immediate duration
		duration = __ByteRead(track);
		break;
	case 3: // 16-bit immediate duration
		duration = __WordRead(track);
		break;
	}

	param              = &track->timedParam.move[paramIndex];
	param->targetValue = targetValue / 32768.0f;

	if (duration >= 0) {
		param->duration = duration;
	}

	if (param->duration <= 0.0f) {
		param->currentValue = param->targetValue;
		param->stepSize     = 0.0f;
		param->duration     = 1.0f;
	} else {
		param->stepSize = (param->targetValue - param->currentValue) / param->duration;
	}
}

/*
 * --INFO--
 * Address:	8000FAA0
 * Size:	0000AC
 */
void Jam_WriteRegDirect(seqp_* track, u8 index, u16 value)
{

	u16 uVar1;

	switch (index) {
	case 0:
	case 1:
	case 2:
		value = value & 0xff;
		uVar1 = Extend8to16(value);
		break;
	case 32:
	case 33:
		return;
	case 34:
		Jam_WriteRegDirect(track, 0, value >> 8);
		uVar1 = value;
		value = value & 0xff;
		index = 1;
		break;
	default:
		uVar1 = value;
		break;
	}

	track->regParam.reg[index]  = value;
	track->regParam.param.value = uVar1;
}

/*
 * --INFO--
 * Address:	8000FB60
 * Size:	000098
 */
static u32 LoadTbl(seqp_* track, u32 ofs, u32 idx, u32 param_4)
{
	u32 result;

	switch (param_4) {
	case 4:
		result = __ByteReadOfs(track, ofs + idx);
		break;
	case 5:
		idx    = idx * 2;
		result = __WordReadOfs(track, ofs + idx);
		break;
	case 6:
		idx    = idx * 2 + idx; // Roundabout way to multiply by 3.
		result = __24ReadOfs(track, ofs + idx);
		break;
	case 7:
		idx = idx * 4;
	case 8:
		result = __LongReadOfs(track, ofs + idx);
		break;
	}
	return result;
}

/*
 * --INFO--
 * Address:	8000FC00
 * Size:	000484
 */
void Jam_WriteRegParam(seqp_* track, u8 param_2)
{

	s16 r30_newRegValue; // r30
	u8 r29_regIdx;       // r29
	u16 r28;             // r28
	u32 unaff_r27;       // r27
	u32 r26;             // r26
	u32 r25;             // r25
	u32 unaff_r24;       // r24
	s16 r23_oldRegValue; // r23

	r26 = param_2 & 0xc;
	r25 = param_2 & 3;
	if ((param_2 & 0x0F) == 0x0B) {
		r26 = 0;
		r25 = 0xb;
	}
	if ((param_2 & 0x0F) == 0x0A) {
		param_2   = __ByteRead(track);
		r26       = param_2 & 0x0C;
		r25       = 0xa;
		unaff_r24 = (u8)(param_2 >> 4) + 4;
	}
	if ((param_2 & 0x0F) == 0x09) {
		param_2 = __ByteRead(track);
		r26     = param_2 & 0x0c;
		r25     = param_2 & 0xf0;
		if (r26 == 8) {
			r26 = 0x10;
		}
	}
	r29_regIdx = __ByteRead(track);
	if (r25 == 0x0A) {
		unaff_r27 = Jam_ReadReg32(track, __ByteRead(track));
	}
	switch (r26) {
	case 0:
		r30_newRegValue = Jam_ReadRegDirect(track, __ByteRead(track));
		break;
	case 4:
		r30_newRegValue = __ByteRead(track);
		break;
	case 8:
		r30_newRegValue = __ByteRead(track) << 8;
		break;
	case 12:
		r30_newRegValue = __WordRead(track);
		break;
	case 16:
		r30_newRegValue = -1;
	}

	r23_oldRegValue = Jam_ReadRegDirect(track, r29_regIdx);
	switch (r25) {
	case 0x00:
		break;
	case 0x01:
		if (r26 == 4) {
			r30_newRegValue = Extend8to16(r30_newRegValue);
		}
		r30_newRegValue = r23_oldRegValue + r30_newRegValue;
		break;
	case 0x02:
		unaff_r27 = r23_oldRegValue * r30_newRegValue;
		Jam_WriteRegXY(track, unaff_r27);
		return;
	case 0x03:
		track->regParam.param.value = r23_oldRegValue - r30_newRegValue;
		return;
	case 0x0B:
		r30_newRegValue = r23_oldRegValue - r30_newRegValue;
		break;
	case 0x10:
		if (r26 == 4) {
			r30_newRegValue = Extend8to16(r30_newRegValue);
		}
		if (r30_newRegValue < 0) {
			r30_newRegValue = (u16)r23_oldRegValue >> -r30_newRegValue;
		} else {
			r30_newRegValue = (u16)r23_oldRegValue << r30_newRegValue;
		}
		break;
	case 0x20:
		if (r26 == 4) {
			r30_newRegValue = Extend8to16(r30_newRegValue);
		}
		if (r30_newRegValue < 0) {
			r30_newRegValue = r23_oldRegValue >> -r30_newRegValue;
		} else {
			r30_newRegValue = r23_oldRegValue << r30_newRegValue;
		}
		break;
	case 0x30:
		r30_newRegValue = r23_oldRegValue & r30_newRegValue;
		break;
	case 0x40:
		r30_newRegValue = r23_oldRegValue | r30_newRegValue;
		break;
	case 0x50:
		r30_newRegValue = r23_oldRegValue ^ r30_newRegValue;
		break;
	case 0x60:
		r30_newRegValue = -r23_oldRegValue;
		break;
	case 0x90:
		unaff_r27       = GetRandom_s32();
		r30_newRegValue = unaff_r27 % (u16)r30_newRegValue;
		break;
	case 0xA:
		unaff_r27       = LoadTbl(track, unaff_r27, r30_newRegValue, unaff_r24);
		r30_newRegValue = (u16)unaff_r27;
		break;
	}

	switch (r29_regIdx) {
	case 0:
	case 1:
	case 2:
		r30_newRegValue = r30_newRegValue & 0xff;
		r28             = Extend8to16(r30_newRegValue);
		break;
	case 0x21:
		r29_regIdx      = 6;
		r30_newRegValue = track->regParam.param.bankNumber & 0xff00 | r30_newRegValue & 0x00ff;
		break;
	case 0x20:
		r29_regIdx      = 6;
		r30_newRegValue = track->regParam.param.bankNumber & 0x00ff | r30_newRegValue << 8;
		break;
	case 0x2E:
		r29_regIdx      = 0xd;
		r30_newRegValue = track->regParam.param.basePriority & 0xff00 | r30_newRegValue & 0x00ff;
		break;
	case 0x2F:
		r29_regIdx      = 0xd;
		r30_newRegValue = track->regParam.param.basePriority & 0x00ff | r30_newRegValue << 8;
		break;
	case 0x22:
		Jam_WriteRegDirect(track, 0, r30_newRegValue >> 8);
		r30_newRegValue = r30_newRegValue & 0xff;
		r28             = r30_newRegValue;
		r29_regIdx      = 1;
		break;
	case 0x28:
	case 0x29:
	case 0x2A:
	case 0x2B:
		track->regParam.param._20[r29_regIdx - 0x28] = unaff_r27;
		return;
	default:
		r28 = r30_newRegValue;
		break;
	}

	track->regParam.reg[r29_regIdx] = r30_newRegValue;
	track->regParam.param.value     = r28;

	if (r29_regIdx == 6) {
		Osc_Clear_Overwrite(track);
	}
	if (r29_regIdx == 7) {
		track->updateFlags |= OuterParamFlag_Pitch;
	}
	if (r29_regIdx == 0xd) {
		track->parentController.channelPriority = track->regParam.param.basePriority | 0x10000;
		track->parentController.releaseTime     = 0;
	}
}

/*
 * --INFO--
 * Address:	800100A0
 * Size:	00016C
 */
u16 Jam_ReadRegDirect(seqp_* track, u8 regIdx)
{
	s16 result;
	u16 regDirectLo;
	u16 regDirectHi;
	int i;

	switch (regIdx) {
	case 0x20:
	case 0x21:
		result = track->regParam.param.bankNumber;
		break;
	case 0x22:
		regDirectLo = Jam_ReadRegDirect(track, 1);
		regDirectHi = Jam_ReadRegDirect(track, 0);
		result      = regDirectHi << 8 | regDirectLo;
		break;
	case 0x2C:
		result = 0;
		for (i = 15; i >= 0; --i) {
			result = result << 1; // For some reason, `<<=` prevents `srawi`.
			if (track->children[i] && track->children[i]->trackState) {
				result |= 1;
			}
		}
		break;
	case 0x2D:
		result = 0;
		for (i = 7; i >= 0; --i) {
			result = result << 1; // For some reason, `<<=` prevents `srawi`.
			result |= (u8)CheckNoteStop(track, i);
		}
		break;
	case 0x30:
		if (track->callStackDepth == 0) {
			result = 0;
		} else {
			result = track->loopCounters[track->callStackDepth - 1];
		}
		break;
	default:
		result = track->regParam.reg[regIdx];
		break;
	}
	switch (regIdx) {
	case 0x00:
	case 0x01:
	case 0x02:
	case 0x21:
		result = result & 0xff;
		break;
	case 0x20:
		result = result >> 8;
		break;
	}
	return result;
}

/*
 * --INFO--
 * Address:	80010220
 * Size:	000048
 */
u32 Jam_ReadRegXY(seqp_* track)
{
	return (Jam_ReadRegDirect(track, 4) << 16) | Jam_ReadRegDirect(track, 5);
}

/*
 * --INFO--
 * Address:	80010280
 * Size:	00005C
 */
u32 Jam_ReadReg32(seqp_* track, u8 index)
{
	switch (index) {
	case 40:
	case 41:
	case 42:
	case 43:
		return track->regParam.param._20[index - 40];
	case 35:
		return Jam_ReadRegXY(track);
	}
	return Jam_ReadRegDirect(track, index);
}

/*
 * --INFO--
 * Address:	800102E0
 * Size:	000048
 */
void Jam_WriteRegXY(seqp_* track, u32 param_2)
{
    u16 v = param_2 >> 16;
	Jam_WriteRegDirect(track, 4, (u16)v);
    u16 v2 = param_2;
	Jam_WriteRegDirect(track, 5, (u16)v2);
}

/*
 * --INFO--
 * Address:	80010340
 * Size:	00003C
 * Note: Equivalent to `JASTrack::exchangeRegisterValue` in later JAudio.
 */
u32 __ExchangeRegisterValue(seqp_* track, u8 param_2)
{
	if (param_2 < 64) {
		return Jam_ReadReg32(track, param_2);
	}
	return track->trackPort[param_2 - 64].value;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00004C
 */
void Jam_WritePortApp(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00004C
 */
void Jam_ReadPortApp(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000048
 */
void Jam_CheckExportApp(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000048
 */
void Jam_CheckImportApp(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000A0
 */
void Jam_WritePortIndirect(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000058
 */
void Jam_ReadPortIndirect(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000A4
 */
void Jam_CheckPortIndirect(void)
{
	// UNUSED FUNCTION
}

