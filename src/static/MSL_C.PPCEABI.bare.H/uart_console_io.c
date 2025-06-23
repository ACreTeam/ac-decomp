#include "stddef.h"

unsigned long WriteUARTN(void* buf, unsigned long len);
unsigned long ReadUARTN(void* bytes, unsigned long length);
unsigned long InitializeUART(unsigned long baudRate);

static inline int __init_uart_console(void);

int __write_console(int param_0, unsigned char* data, size_t* size, int param_3) {
    if (__init_uart_console() != 0) {
        return 1;
    }

    if ((long)WriteUARTN(data, *size) != 0) {
        *size = 0;
        return 1;
    }

    __TRK_write_console(param_0, data, size, (void*)param_3);

    return 0;
}

int __close_console() {
    return 0;
}

static inline int __init_uart_console(void) {
    static int initialized = 0;
    int ret = 0;

    if (initialized == 0) {
        ret = InitializeUART(0xE100);

        if (ret == 0) {
            initialized = 1;
        }
    }

    return ret;
}
