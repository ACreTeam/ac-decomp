#include "fault.h"
#include "terminal.h"
__declspec(section ".sdata") static fault* this;
static fault fault_class;

extern void fault_AddClientEx(fault_client* client, FaultCallback callback, const char* msg, u32 param, u8 priority, u8 flags) {
    BOOL enable;
    BOOL client_exists;
    fault_client* f0;
    fault_client* f1;
    
    client_exists = FALSE;
    if (client == NULL || callback == NULL) {
        return;
    }
    
    enable = OSDisableInterrupts();
    f0 = NULL;
    for (f1 = this->first_client; f1 != NULL; f1 = f1->next) {
        if (f1 == client) {
            client_exists = TRUE;
            goto exit;
        }

        if (f1->priority >= priority ) {
            f0 = f1;
        }
    }

    client->callback = callback;
    client->msg = msg;
    client->param = param;
    client->priority = priority;
    client->flags = flags;
    if (f0 != NULL) {
        client->next = f0->next;
        f0->next = client;
    }
    else {
        client->next = this->first_client;
        this->first_client = client;
    }

    this->num_clients++;

exit:
    OSRestoreInterrupts(enable);
    if (client_exists != FALSE) {
        OSReport(VTCOL(RED,WHITE)"fault_AddClient: %08x は既にリスト中にある\n%x",VT_RST, client);
    }
}

extern void fault_AddClient(fault_client* client, FaultCallback callback, const char* msg, u32 param) {
    fault_AddClientEx(client, callback, msg, param, FAULT_MIN_PRIORITY, FAULT_FLAG_POSTEXCEPTION);
}

static void fault_Printf(const char* fmt, ...) {
    void* console;

    console = JC_JUTException_getConsole();
    if (console != NULL) {
        va_list arg;
        va_start(arg, fmt);
        JC_JUTConsole_print_f_va(console, fmt, arg);
        va_end(arg);
    }
}

static void fault_DrawUpdate() {
    void* manager = JC_JUTConsoleManager_getManager();
    if (manager != NULL) {
        JC_JUTConsoleManager_drawDirect(manager, TRUE);
    }
}

extern void fault_WaitTime(u32 waitTime) {
    fault_DrawUpdate();
    JC_JUTException_waitTime(waitTime);
}

extern int fault_ReadPad(u32* outTrigger, u32* outButton) {
    void* manager;
    
    fault_DrawUpdate();
    manager = JC_JUTException_getManager();
    if (manager == NULL) {
        return FAULT_PAD_READ_FAILED;
    }
    else {
        JC_JUTException_readPad(manager, outTrigger, outButton);
        return FAULT_PAD_READ_SUCCESS;
    }
}

static void fault_CallBackFunc(int stage) {
    fault_client* client;
    int index;

    index = 0;
    for (client = this->first_client; client != NULL; client = client->next) {
        if (client->callback != NULL) {
            if ((client->flags & (1 << stage)) != 0) {
                if ((client->flags & FAULT_FLAG_SKIP_DRAW_SEPARATOR) == 0) {
                    fault_Printf("---------------------------------------------\n");
                    fault_DrawUpdate();
                }

                if ((client->flags & FAULT_FLAG_SKIP_DRAW_CALLBACK_INFO) == 0) {
                    fault_Printf("CallBack (%d/%d) %08x %08x %08x\n", index++, this->num_clients, client, client->msg, client->param);
                    fault_DrawUpdate();
                }

                (*client->callback)(client->msg, client->param);
                fault_DrawUpdate();
            }
        }
    }
    
    fault_DrawUpdate();
}

static void my_PreExceptionCallback() {
    if (JC_JUTException_getConsole() != NULL && JC_JUTConsoleManager_getManager() != NULL && JC_JUTException_getManager() != NULL) {
        fault_CallBackFunc(FAULT_STAGE_PRE);
    }
}

static void my_PostExceptionCallback() {
    if (JC_JUTException_getConsole() != NULL && JC_JUTConsoleManager_getManager() != NULL && JC_JUTException_getManager() != NULL) {
        fault_CallBackFunc(FAULT_STAGE_POST);
    }
}

extern void fault_Init() {
    this = &fault_class;
    bzero(&fault_class, sizeof(fault_class));
    this->_0 = 0;
    this->_1 = 0;
    this->_2 = 0;
    this->first_client = NULL;
    this->_3 = 0;
    fault_class._2 = 1;
    JC_JUTException_setPreUserCallback(&my_PreExceptionCallback);
    JC_JUTException_setPostUserCallback(&my_PostExceptionCallback);
}
