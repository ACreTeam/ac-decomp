#include "MSL_C/ansi_files.h"

void __prep_buffer(FILE* file) {
    file->buffer_ptr = file->buffer;
    file->buffer_length = file->buffer_size;
    file->buffer_length -= file->position & file->buffer_alignment;
    file->buffer_position = file->position;
}

void __convert_from_newlines(unsigned char* p, size_t* n) {
}

int __flush_buffer(FILE* file, size_t* bytes_flushed) {
    size_t buffer_len;
    int ioresult;

    buffer_len = file->buffer_ptr - file->buffer;

    if (buffer_len) {
        file->buffer_length = buffer_len;

        if (!file->file_mode.binary_io)
            __convert_from_newlines(file->buffer, &file->buffer_length);

        ioresult = (*file->write_fn)(file->handle, file->buffer, &file->buffer_length, file->idle_fn);

        if (bytes_flushed)
            *bytes_flushed = file->buffer_length;

        if (ioresult)
            return ioresult;

        file->position += file->buffer_length;
    }

    __prep_buffer(file);

    return __no_io_error;
}
