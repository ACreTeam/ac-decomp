/*
 * --INFO--
 * Address:	80012CC0
 * Size:	000130
 */
u32 Cmd_Process(seqp_* track, u8 cmd, u16 param_3)
{
	Arghead_ argpair;
	u16 argTypes;
	size_t i;
	u32 arg;
	CmdFunction function;
	seqp_** REF_track;
	u8* REF_cmd;

	REF_track = &track;
	REF_cmd   = &cmd;

	argpair  = Arglist[cmd - 0xC0];
	argTypes = argpair.argTypes | param_3;
	for (i = 0; i < argpair.argCount; ++i) {
		switch (argTypes & 0x03) {
		case 0: // 8-bit immediate value
			arg = __ByteRead(track);
			break;
		case 1: // 16-bit immediate value
			arg = __WordRead(track);
			break;
		case 2: // 24-bit immediate value
			arg = __24Read(track);
			break;
		case 3: // Register value
			arg = __ExchangeRegisterValue(track, __ByteRead(track));
			break;
		}

		argTypes   = argTypes >> 2;
		SEQ_ARG[i] = arg;
	}

	// Me when I have to introduce global state because I'm bored.
	SEQ_CMD = cmd;
	SEQ_P   = track;

	function = CMDP_LIST[cmd - 0xC0];
	if (!function) {
        OSReport("Error: NULL Command Pointer (cmd. %x ) \n", cmd);
        OSReport("SEQP %x  Access Offset %d\n", track, track->programCounter);
		return 0;
	}
	return function();
}

/*
 * --INFO--
 * Address:	80012E00
 * Size:	0000A8
 */
u32 RegCmd_Process(seqp_* track, BOOL param_2, u32 param_3)
{
	size_t i;
	u8 uVar4;
	u8 uVar3;
	u16 uVar5;
	u16 uVar6; // Uninitialized!  Naughty!

	uVar4 = __ByteRead(track);
	if (param_2 == TRUE) {
		uVar4 = __ExchangeRegisterValue(track, uVar4);
	}
	if (param_2 != TRUE || param_3 != 0) {
		uVar3 = __ByteRead(track);
		uVar5 = 0b11;
		for (i = 0; i < param_3 + 1; ++i) {
			if (uVar3 & 0b10000000) {
				uVar6 |= uVar5;
			}
			uVar3 = uVar3 << 1;
			uVar5 = uVar5 << 2;
		}
	}
	return Cmd_Process(track, uVar4, uVar6);
}

