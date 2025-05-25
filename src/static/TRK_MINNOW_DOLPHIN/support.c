#include "PowerPC_EABI_Support/MetroTRK/trk.h"

DSError TRKSuppAccessFile(u32 file_handle, u8* data, size_t* count,
                          u8* io_result, BOOL need_reply, BOOL read)
{
	DSError error;
	int replyBufferId;
	TRKBuffer* replyBuffer;
	int bufferId;
	TRKBuffer* buffer;
	u32 length;
	u32 done;
	u8 replyIOResult;
	u16 replyLength;
	BOOL exit;

	if (data == NULL || *count == 0) {
		return DS_ParameterError;
	}

	exit       = FALSE;
	*io_result = DS_IONoError;
	done       = 0;
	error      = DS_NoError;
	while (!exit && done < *count && error == DS_NoError && *io_result == DS_IONoError) {
		if (*count - done > 0x800) {
			length = 0x800;
		} else {
			length = *count - done;
		}

		error = TRKGetFreeBuffer(&bufferId, &buffer);

		if (error == DS_NoError)
			error = TRKAppendBuffer1_ui8(buffer, read ? DSMSG_ReadFile
			                                          : DSMSG_WriteFile);

		if (error == DS_NoError)
			error = TRKAppendBuffer1_ui32(buffer, file_handle);

		if (error == DS_NoError)
			error = TRKAppendBuffer1_ui16(buffer, length);

		if (!read && error == DS_NoError)
			error = TRKAppendBuffer_ui8(buffer, data + done, length);

		if (error == DS_NoError) {
			if (need_reply) {
				replyLength   = 0;
				replyIOResult = 0;

				error = TRKRequestSend(buffer, &replyBufferId, read ? 5 : 5, 3,
				                       !(read && file_handle == 0));
				if (error == DS_NoError) {
					replyBuffer = (TRKBuffer*)TRKGetBuffer(replyBufferId);
					TRKSetBufferPosition(replyBuffer, 2);
				}

				if (error == DS_NoError)
					error = TRKReadBuffer1_ui8(replyBuffer, &replyIOResult);

				if (error == DS_NoError)
					error = TRKReadBuffer1_ui16(replyBuffer, &replyLength);

				if (read && error == DS_NoError) {
					if (replyBuffer->length != replyLength + 5) {
						replyLength = replyBuffer->length - 5;
						if (replyIOResult == 0)
							replyIOResult = 1;
					}

					if (replyLength <= length)
						error = TRKReadBuffer_ui8(replyBuffer, data + done,
						                          replyLength);
				}

				if (replyLength != length) {
					if ((!read || replyLength >= length) && replyIOResult == 0)
						replyIOResult = 1;
					length = replyLength;
					exit   = TRUE;
				}

				*io_result = (DSIOResult)replyIOResult;
				TRKReleaseBuffer(replyBufferId);
			} else {
				error = TRKMessageSend(buffer);
			}
		}

		TRKReleaseBuffer(bufferId);
		done += length;
	}

	*count = done;
	return error;
}

DSError TRKRequestSend(TRKBuffer* msgBuf, int* bufferId, u32 p1, u32 p2, int p3)
{
	int error = DS_NoError;
	TRKBuffer* buffer;
	u32 timer;
	int tries;
	u8 msg_command;
	u8 msg_error;
	BOOL badReply = TRUE;

	*bufferId = -1;

	for (tries = p2 + 1; tries != 0 && *bufferId == -1 && error == DS_NoError;
	     tries--) {
		error = TRKMessageSend(msgBuf);
		if (error == DS_NoError) {
			if (p3) {
				timer = 0;
			}

			while (TRUE) {
				do {
					*bufferId = TRKTestForPacket();
					if (*bufferId != -1)
						break;
				} while (!p3 || ++timer < 79999980);

				if (*bufferId == -1)
					break;

				badReply = FALSE;

				buffer = TRKGetBuffer(*bufferId);
				TRKSetBufferPosition(buffer, 0);

				if ((error = TRKReadBuffer1_ui8(buffer, &msg_command))
				    != DS_NoError)
					break;

				if (msg_command >= DSMSG_ReplyACK)
					break;

				TRKProcessInput(*bufferId);
				*bufferId = -1;
			}

			if (*bufferId != -1) {
				if (buffer->length < p1) {
					badReply = TRUE;
				}
				if (error == DS_NoError && !badReply) {
					error = TRKReadBuffer1_ui8(buffer, &msg_error);
				}
				if (error == DS_NoError && !badReply) {
					if (msg_command != DSMSG_ReplyACK
					    || msg_error != DSREPLY_NoError) {
						badReply = TRUE;
					}
				}
				if (error != DS_NoError || badReply) {
					TRKReleaseBuffer(*bufferId);
					*bufferId = -1;
				}
			}
		}
	}

	if (*bufferId == -1) {
		error = DS_Error800;
	}

	return error;
}

DSError HandleOpenFileSupportRequest(const char* path, u8 replyError, u32* param_3, u8* ioResult) {
    int sp10;
    int spC;
    TRKBuffer* sp8;
    TRKBuffer* var_r31;
    DSError var_r26;

    *param_3 = 0;
    var_r26 = TRKGetFreeBuffer(&spC, &sp8);
    if (var_r26 == DS_NoError) {
        var_r26 = TRKAppendBuffer1_ui8(sp8, 0xD2);
    }
    if (var_r26 == DS_NoError) {
        var_r26 = TRKAppendBuffer1_ui8(sp8, replyError);
    }
    if (var_r26 == DS_NoError) {
        var_r26 = TRKAppendBuffer1_ui16(sp8, strlen(path) + 1);
    }
    if (var_r26 == DS_NoError) {
        var_r26 = TRKAppendBuffer_ui8(sp8, (u8*) path, strlen(path) + 1);
    }
    if (var_r26 == DS_NoError) {
        *ioResult = 0;
        var_r26 = TRKRequestSend(sp8, &sp10, 7, 3, 0);
        if (var_r26 == DS_NoError) {
            var_r31 = TRKGetBuffer(sp10);
            TRKSetBufferPosition(var_r31, 2);
        }
        if (var_r26 == DS_NoError) {
            var_r26 = TRKReadBuffer1_ui8(var_r31, ioResult);
        }
        if (var_r26 == DS_NoError) {
            var_r26 = TRKReadBuffer1_ui32(var_r31, param_3);
        }
        TRKReleaseBuffer(sp10);
    }
    TRKReleaseBuffer(spC);
    return var_r26;
}

DSError HandleCloseFileSupportRequest(int replyError, u8* ioResult) {
    int sp10;
    int spC;
    DSError var_r31;
    TRKBuffer* sp8;
    TRKBuffer* var_r30;

    var_r31 = TRKGetFreeBuffer(&spC, &sp8);
    if (var_r31 == DS_NoError) {
        var_r31 = TRKAppendBuffer1_ui8(sp8, 0xD3);
    }
    if (var_r31 == DS_NoError) {
        var_r31 = TRKAppendBuffer1_ui32(sp8, replyError);
    }
    if (var_r31 == DS_NoError) {
        *ioResult = DS_IONoError;
        var_r31 = TRKRequestSend(sp8, &sp10, 3, 3, 0);
        if (var_r31 == DS_NoError) {
            var_r30 = TRKGetBuffer(sp10);
            TRKSetBufferPosition(var_r30, 2);
        }
        if (var_r31 == DS_NoError) {
            var_r31 = TRKReadBuffer1_ui8(var_r30, ioResult);
        }
        TRKReleaseBuffer(sp10);
    }
    TRKReleaseBuffer(spC);
    return var_r31;
}

DSError HandlePositionFileSupportRequest(u32 replyErr, u32* param_2, u8 param_3, u8* ioResult) {
    int sp10;
    int spC;
    TRKBuffer* sp8;
    TRKBuffer* var_r31;
    DSError var_r27;

    var_r27 = TRKGetFreeBuffer(&spC, &sp8);
    if (var_r27 == DS_NoError) {
        var_r27 = TRKAppendBuffer1_ui8(sp8, 0xD4);
    }
    if (var_r27 == DS_NoError) {
        var_r27 = TRKAppendBuffer1_ui32(sp8, replyErr);
    }
    if (var_r27 == DS_NoError) {
        var_r27 = TRKAppendBuffer1_ui32(sp8, *param_2);
    }
    if (var_r27 == DS_NoError) {
        var_r27 = TRKAppendBuffer1_ui8(sp8, param_3);
    }
    if (var_r27 == DS_NoError) {
        *ioResult = DS_IONoError;
        var_r27 = TRKRequestSend(sp8, &sp10, 3, 3, 0);
        if (var_r27 == DS_NoError) {
            var_r31 = TRKGetBuffer(sp10);
            TRKSetBufferPosition(var_r31, 2);
        }
        if (var_r27 == DS_NoError) {
            var_r27 = TRKReadBuffer1_ui8(var_r31, ioResult);
        }
        if (var_r27 == DS_NoError) {
            var_r27 = TRKReadBuffer1_ui32(var_r31, param_2);
        } else {
            *param_2 = -1;
        }
        TRKReleaseBuffer(sp10);
    }
    TRKReleaseBuffer(spC);
    return var_r27;
}
