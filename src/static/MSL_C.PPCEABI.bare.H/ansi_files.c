#include "MSL_C/ansi_files.h"

char stdin_buff[0x100];
char stdout_buff[0x100];
char stderr_buff[0x100];

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

void __close_all(void) {
    FILE* p = &__files._stdin;
    FILE* plast;

	while(p != NULL)
	{
		if (p->file_mode.file_kind != __closed_file)
		{
			fclose(p);
		}

		plast = p;
		p     = (FILE*)p->next;
		if (plast->char_buffer)
			free(plast);
		else
		{
			plast->file_mode.file_kind = __unavailable_file;
			if ((p != NULL) && p->char_buffer)
				plast->next = NULL;
		}
	}
}

unsigned int __flush_all(void)
{
    unsigned int retval = 0;
    FILE* __stream;
    __stream = &__files._stdin;
    while (__stream) {
        if ((__stream->file_mode.file_kind) && (fflush(__stream))) {
        retval = -1;
        }
        __stream = (FILE*)__stream->next;
    };
    return retval;
}
