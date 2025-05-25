#include "PowerPC_EABI_Support/MetroTRK/trk.h"
#include <stddef.h>

// forward declares
DSIOResult __read_file(u32 handle, u8* buffer, size_t* count, void* ref_con);
DSIOResult __write_file(u32 handle, u8* buffer, size_t* count, void* ref_con);
DSIOResult __access_file(u32 handle, u8* buffer, size_t* count, void* ref_con, MessageCommandID cmd);

/**
 * @note Address: 0x800C0B4C
 * @note Size: 0xBC
 */
DSIOResult __read_console(u32 handle, u8* buffer, size_t* count, void* ref_con)
{
	if (GetUseSerialIO() == 0) {
		return DS_IOError;
	}
	return __read_file(DS_Stdin, buffer, count, ref_con);
}

/**
 * @note Address: 0x800C0A90
 * @note Size: 0xBC
 */
DSIOResult __TRK_write_console(u32 handle, u8* buffer, size_t* count, void* ref_con)
{
	if (GetUseSerialIO() == 0) {
		return DS_IOError;
	}
	return __write_file(DS_Stdout, buffer, count, ref_con);
}

/**
 * @note Address: N/A
 * @note Size: 0xB4
 */
DSIOResult __read_file(u32 handle, u8* buffer, size_t* count, void* ref_con)
{
	return __access_file(handle, buffer, count, ref_con, DSMSG_ReadFile);
}

/**
 * @note Address: N/A
 * @note Size: 0xB4
 */
DSIOResult __write_file(u32 handle, u8* buffer, size_t* count, void* ref_con)
{
	return __access_file(handle, buffer, count, ref_con, DSMSG_WriteFile);
}

/**
 * @note Address: N/A
 * @note Size: 0x17C
 */
void __open_file(void)
{
	// UNUSED FUNCTION
}

/**
 * @note Address: N/A
 * @note Size: 0xDC
 */
void __position_file(void)
{
	// UNUSED FUNCTION
}

/**
 * @note Address: N/A
 * @note Size: 0xE0
 */
void convertFileMode(void)
{
	// UNUSED FUNCTION
}

/**
 * @note Address: N/A
 * @note Size: 0xC0
 */
DSIOResult __access_file(u32 handle, u8* buffer, size_t* count, void* ref_con, MessageCommandID cmd)
{
	size_t countTemp;
	u32 r0;

	if (GetTRKConnected() == DS_NoError) {
		return DS_IOError;
	}

	countTemp = *count;
	r0        = TRKAccessFile(cmd, handle, &countTemp, buffer);
	*count    = countTemp;

	switch ((u8)r0) {
	case DS_IONoError:
		return DS_IONoError;
	case DS_IOEOF:
		return DS_IOEOF;
	}

	return DS_IOError;
}

/**
 * @note Address: N/A
 * @note Size: 0x1D0
 */
void __open_temp_file(void)
{
	// UNUSED FUNCTION
}
