/*
 * --INFO--
 * Address:	80010380
 * Size:	000078
 */
BOOL Jam_WritePortAppDirect(seqp_* track, u32 param_2, u16 param_3)
{
	if (!track) {
		return FALSE;
	}
	track->trackPort[param_2].value      = param_3;
	track->trackPort[param_2].importFlag = 1;
	if (param_2 == 0) {
		Jam_SetInterrupt(track, 3);
	}
	if (param_2 == 1) {
		Jam_SetInterrupt(track, 4);
	}
	return TRUE;
}

/*
 * --INFO--
 * Address:	80010400
 * Size:	000030
 */
BOOL Jam_ReadPortAppDirect(seqp_* track, u32 param_2, u16* param_3)
{
	if (!track) {
		return FALSE;
	}
	*param_3                             = track->trackPort[param_2].value;
	track->trackPort[param_2].exportFlag = 0;
	return TRUE;
}

/*
 * --INFO--
 * Address:	80010440
 * Size:	00006C
 */
BOOL Jam_CheckPortAppDirect(seqp_* track, u32 param_2, u16 param_3)
{
	// Again with the cast to u8... what is it?
	switch ((u8)param_3) {
	case FALSE:
		if (track->trackPort[param_2].exportFlag == FALSE) {
			return FALSE;
		}
		return TRUE;
	case TRUE:
		if (track->trackPort[param_2].importFlag == TRUE) {
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000018
 */
void Jam_WritePort(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000018
 */
void Jam_ReadPort(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000034
 */
void Jam_WritePortChild(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000038
 */
void Jam_WritePortBros(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	800104C0
 * Size:	000030
 */
void Jam_InitRegistTrack(void)
{
	int i;

	T_LISTS = 0;
	for (i = 0; i < TRACK_LIST_SIZE; ++i) {
		TRACK_LIST[i].track = NULL;
	}
}

/*
 * --INFO--
 * Address:	80010500
 * Size:	0000A8
 */
void Jam_RegistTrack(seqp_* track, u32 param_2)
{
	u32* REF_param_2;
	size_t i;

	for (i = 0; i < T_LISTS; ++i) {
		if (param_2 == TRACK_LIST[i].id) {
			return;
		}
	}
	if (T_LISTS == TRACK_LIST_SIZE) {
		for (i = 0; i < TRACK_LIST_SIZE; ++i) {
			if (!TRACK_LIST[i].track) {
				break;
			}
		}
		if (i == TRACK_LIST_SIZE) {
			return;
		}
	} else {
		i = T_LISTS;
		++T_LISTS;
	}
	REF_param_2         = &param_2;
	TRACK_LIST[i].id    = param_2;
	TRACK_LIST[i].track = track;
	track->isRegistered = 1;
}

/*
 * --INFO--
 * Address:	800105C0
 * Size:	00008C
 */
void Jam_UnRegistTrack(seqp_* track)
{
	size_t i;

	if (!track->isRegistered) {
		return;
	}
	for (i = 0; i < T_LISTS; ++i) {
		if (track == TRACK_LIST[i].track) {
			TRACK_LIST[i].track = NULL;
		}
	}
	track->isRegistered = FALSE;
	for (; T_LISTS != 0; --T_LISTS) {
		if (TRACK_LIST[T_LISTS - 1].track) {
			break;
		}
	}
}

/*
 * --INFO--
 * Address:	80010660
 * Size:	000050
 */
seqp_* Jam_GetTrackHandle(u32 param_1)
{
	size_t i;

	for (i = 0; i < T_LISTS; ++i) {
		if (param_1 == TRACK_LIST[i].id && TRACK_LIST[i].track) {
			return TRACK_LIST[i].track;
		}
	}
	return NULL;
}

/*
 * --INFO--
 * Address:	800106C0
 * Size:	000018
 */
void Jam_InitExtBuffer(OuterParam_* ext)
{
	ext->flags       = 0;
	ext->updateFlags = 0;
	ext->isAssigned  = FALSE;
	ext->refCount    = 0;
}

/*
 * --INFO--
 * Address:	800106E0
 * Size:	000038
 */
BOOL Jam_AssignExtBuffer(seqp_* track, OuterParam_* ext)
{
	if (!track) {
		return FALSE;
	}
	if (!ext) {
		return FALSE;
	}
	track->outerParams = ext;
	++ext->refCount;
	return TRUE;
}

/*
 * --INFO--
 * Address:	80010720
 * Size:	000060
 */
BOOL Jam_AssignExtBufferP(seqp_* track, u8 index, OuterParam_* ext)
{
	if (!track) {
		return FALSE;
	}
	if (!ext) {
		return FALSE;
	}
	track->childOuterParams[index] = ext;
	ext->isAssigned                = TRUE;
	Jam_AssignExtBuffer(track->children[index], ext);
	return TRUE;
}

/*
 * --INFO--
 * Address:	80010780
 * Size:	000044
 */
void Jam_SetExtFirFilterD(OuterParam_* ext, s16* param_2)
{
	int i;

	if (!ext) {
		return;
	}
	ext->updateFlags |= OuterParamFlag_FIR8Filter;
	ext->flags |= OuterParamFlag_FIR8Filter;
	for (i = 0; i < 8; ++i) {
		ext->firCoefficients[i] = param_2[i];
	}
}

/*
 * --INFO--
 * Address:	800107E0
 * Size:	0000A4
 */
void Jam_SetExtParamD(f32 value, OuterParam_* ext, u8 updateFlags)
{
	f32* member;

	if (!ext) {
		return;
	}

	switch (updateFlags) {
	case OuterParamFlag_Volume:
		member = &ext->volume;
		break;
	case OuterParamFlag_Pitch:
		member = &ext->pitch;
		break;
	case OuterParamFlag_Fxmix:
		member = &ext->fxMix;
		break;
	case OuterParamFlag_Dolby:
		member = &ext->dolby;
		break;
	case OuterParamFlag_Pan:
		member = &ext->pan;
		break;
	case OuterParamFlag_Tempo:
		member = &ext->tempo;
		break;
	default:
		return;
	}

	*member = value;
	ext->updateFlags |= updateFlags;
}

/*
 * --INFO--
 * Address:	800108A0
 * Size:	000024
 */
void Jam_OnExtSwitchD(OuterParam_* ext, u16 param_2)
{
	if (!ext) {
		return;
	}
	ext->flags |= param_2;
	ext->updateFlags |= param_2;
}

/*
 * --INFO--
 * Address:	800108E0
 * Size:	000028
 */
void Jam_OffExtSwitchD(OuterParam_* ext, u16 param_2)
{
	if (!ext) {
		return;
	}
	ext->flags ^= ext->flags & param_2;
	ext->updateFlags |= param_2;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00001C
 */
void Jam_SetExtSwitchDirectD(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00002C
 */
void Jam_SetExtFirFilter(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80010920
 * Size:	00002C
 */
void Jam_SetExtParam(f32 param_1, seqp_* track, u8 param_3)
{
	if (!track) {
		return;
	}
	Jam_SetExtParamD(param_1, track->outerParams, param_3);
}

/*
 * --INFO--
 * Address:	80010960
 * Size:	00002C
 */
void Jam_OnExtSwitch(seqp_* track, u16 param_2)
{
	if (!track) {
		return;
	}
	Jam_OnExtSwitchD(track->outerParams, param_2);
}

/*
 * --INFO--
 * Address:	800109A0
 * Size:	00002C
 */
void Jam_OffExtSwitch(seqp_* track, u16 param_2)
{
	if (!track) {
		return;
	}
	Jam_OffExtSwitchD(track->outerParams, param_2);
}

/*
 * --INFO--
 * Address:	........
 * Size:	00002C
 */
void Jam_SetExtSwitchDirect(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00003C
 */
void Jam_SetExtFirFilterP(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	800109E0
 * Size:	000038
 */
void Jam_SetExtParamP(f32 param_1, seqp_* track, u8 index, u8 param_4)
{
	if (!track) {
		return;
	}
	Jam_SetExtParamD(param_1, track->childOuterParams[index], param_4);
}

/*
 * --INFO--
 * Address:	80010A20
 * Size:	00003C
 */
void Jam_OnExtSwitchP(seqp_* track, u8 index, u16 param_3)
{
	if (!track) {
		return;
	}
	Jam_OnExtSwitchD(track->childOuterParams[index], param_3);
}

/*
 * --INFO--
 * Address:	........
 * Size:	00003C
 */
void Jam_OffExtSwitchP(seqp_* track, u8 index, u16 param_3)
{
	if (!track) {
		return;
	}
	Jam_OffExtSwitchD(track->childOuterParams[index], param_3);
}

/*
 * --INFO--
 * Address:	........
 * Size:	00003C
 */
void Jam_SetExtSwitchDirectP(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00002C
 */
void Jam_CheckRunningCounter(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80010A60
 * Size:	00000C
 */
BOOL Jam_RegisterTrackCallback(TrackCallback callback)
{
	JAM_CALLBACK_FUNC = callback;
	return TRUE;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000038
 */
void Jam_SetTrackExtPanPower(void)
{
	// UNUSED FUNCTION
}

