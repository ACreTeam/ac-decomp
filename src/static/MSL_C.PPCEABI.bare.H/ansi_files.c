#include "MSL_C/ansi_files.h"

char stderr_buff[0x100];
char stdout_buff[0x100];
char stdin_buff[0x100];

extern int __close_console(__file_handle file);
extern int __write_console(__file_handle file, unsigned char* buf, size_t* count, __idle_proc idle_fn);
extern int __read_console(__file_handle file, unsigned char* buf, size_t* count, __idle_proc idle_fn);

extern files __files = {
    {
        0,
        0,
        1,
        1,
        2,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        { 0, 0 },
        { 0, 0 },
        0,
        (unsigned char*)&stdin_buff,
        0x100,
        (unsigned char*)&stdin_buff,
        0,
        0,
        0,
        0,
        NULL,
        __read_console,
        __write_console,
        __close_console,
        NULL,
        &__files._stdout,
    },
    {
        1,
        0,
        2,
        1,
        2,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        { 0, 0 },
        { 0, 0 },
        0,
        (unsigned char*)&stdout_buff,
        0x100,
        (unsigned char*)&stdout_buff,
        0,
        0,
        0,
        0,
        NULL,
        __read_console,
        __write_console,
        __close_console,
        NULL,
        &__files._stderr,
    },
    {
        2,
        0,
        2,
        0,
        2,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        { 0, 0 },
        { 0, 0 },
        0,
        (unsigned char*)&stderr_buff,
        0x100,
        (unsigned char*)&stderr_buff,
        0,
        0,
        0,
        0,
        NULL,
        __read_console,
        __write_console,
        __close_console,
        NULL,
        &__files._sentinel,
    },
};

unsigned int __flush_all(void) {
}

void __close_all(void) {
    FILE* file = &__files._stdin;

    while (file) {
        FILE* curr;

        if (file->file_mode.file_kind & 0x3)
            fclose(file);

        curr = file->next;
        file = file->next;
        if (curr->char_buffer) {
            free(curr);
            continue;
        }

        file->file_mode.file_kind = 3;

        if (file && file->char_buffer)
            curr->next = NULL;
    }
}
