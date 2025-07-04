#include "types.h"

#ifndef _MSL_WIDE_CHAR
#define _MSL_WIDE_CHAR
#endif

#include "MSL_C/ansi_files.h"
#include "errno.h"

// define standard C file pointer location names
#define SEEK_SET (0)
#define SEEK_CUR (1)
#define SEEK_END (2)

int _ftell(FILE* file) {
	int charsInUndoBuffer = 0;
	int position;

	u8 tmp_kind = file->file_mode.file_kind;
	if (!(tmp_kind == __disk_file || tmp_kind == __console_file) || file->file_state.error) {
		errno = 0x28;
		return -1;
	}

	if (file->file_state.io_state == __neutral)
		return (file->position);

	position = file->buffer_position + (file->buffer_ptr - file->buffer);

	if (file->file_state.io_state >= __rereading) {
		charsInUndoBuffer = file->file_state.io_state - __rereading + 1;
		position -= charsInUndoBuffer;
	}

	return (position);
}

int ftell(FILE* stream) {
	int retval;

	retval = (s32)_ftell(stream);
	return retval;
}

int _fseek(FILE* file, u32 offset, int whence) {
    int adjust;
    u32 state;
    int buffLen;
    
    if (file->file_mode.file_kind != 1 || file->file_state.error != 0) {
        errno = 0x28;
        return -1;
    }

    if (file->file_state.io_state == 1) {
        if (__flush_buffer(file, nullptr) != 0) {
            file->file_state.error = 1;
            file->buffer_length = 0;
            errno = 0x28;
            return -1;
        }
    }

    if (whence == SEEK_CUR) {
        whence = SEEK_SET;
        if ((file->file_mode.file_kind != 1 && file->file_mode.file_kind != 2) || file->file_state.error != 0) {
            errno = 0x28;
            adjust = -1;
        } else {
            state = file->file_state.io_state;
            if (state == 0) {
                adjust = file->position;
            } else {
                adjust = file->buffer_position + (u32)(file->buffer_ptr - file->buffer);
                if ((state >= 3)) {
                    adjust -= (state - 2);
                }
            }
        }
        offset += adjust;
    } 
    
    if ((whence != SEEK_END) &&
            (file->file_mode.io_mode != 3) &&
            (file->file_state.io_state == 2 || file->file_state.io_state == 3)) {
        if ((offset >= file->position) || !(offset >= file->buffer_position)) {
            file->file_state.io_state = 0;
        } else {
            file->buffer_ptr = file->buffer + (offset - file->buffer_position);
            file->buffer_length =  file->position - offset;
            file->file_state.io_state = 2;
        }
    } else {
        file->file_state.io_state = 0;
    }

    if (file->file_state.io_state == 0) {
        if (file->position_fn != nullptr && (int)file->position_fn(file->handle, &offset, whence, file->idle_fn)) {
            file->file_state.error = 1;
            file->buffer_length = 0;
            errno = 0x28;
            return -1;
        } else {
            file->file_state.eof = 0;
            file->position = offset;
            file->buffer_length = 0;
        }
    } 
    
    return 0;
}

int fseek(FILE* stream, u32 offset, int whence) {
	int code;

	code = _fseek(stream, offset, whence); // 0 if successful, -1 if error
	return code;
}
