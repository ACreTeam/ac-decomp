#include "dolphin/ar/arq.h"
#include "dolphin/os.h"

const char *__ARQVersion = "<< Dolphin SDK - ARQ\trelease build: Apr 17 2003 12:33:56 (0x2301) >>";
static ARQRequest *__ARQRequestQueueHi;
static ARQRequest *__ARQRequestTailHi;
static ARQRequest *__ARQRequestQueueLo;
static ARQRequest *__ARQRequestTailLo;
static ARQRequest *__ARQRequestPendingHi;
static ARQRequest *__ARQRequestPendingLo;
static ARQCallback __ARQCallbackHi;
static ARQCallback __ARQCallbackLo;
static u32 __ARQChunkSize;

static volatile BOOL __ARQ_init_flag = FALSE;

void __ARQPopTaskQueueHi(void);
void __ARQServiceQueueLo(void);
void __ARQCallbackHack(void);
void __ARQInterruptServiceRoutine(void);
void __ARQInitTempQueue(void);
void __ARQPushTempQueue(ARQRequest *task);

void __ARQPopTaskQueueHi(void)
{

    if (__ARQRequestQueueHi)
    {
        if (__ARQRequestQueueHi->type == ARQ_TYPE_MRAM_TO_ARAM)
        {
            ARStartDMA(__ARQRequestQueueHi->type, __ARQRequestQueueHi->source, __ARQRequestQueueHi->dest,
                       __ARQRequestQueueHi->length);
        }
        else
        {
            ARStartDMA(__ARQRequestQueueHi->type, __ARQRequestQueueHi->dest, __ARQRequestQueueHi->source,
                       __ARQRequestQueueHi->length);
        }

        __ARQCallbackHi = __ARQRequestQueueHi->callback;

        __ARQRequestPendingHi = __ARQRequestQueueHi;

        __ARQRequestQueueHi = __ARQRequestQueueHi->next;
    }
}

void __ARQServiceQueueLo(void)
{

    if ((__ARQRequestPendingLo == NULL) && (__ARQRequestQueueLo))
    {
        __ARQRequestPendingLo = __ARQRequestQueueLo;

        __ARQRequestQueueLo = __ARQRequestQueueLo->next;
    }

    if (__ARQRequestPendingLo)
    {
        if (__ARQRequestPendingLo->length <= __ARQChunkSize)
        {
            if (__ARQRequestPendingLo->type == ARQ_TYPE_MRAM_TO_ARAM)
                ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->source,
                           __ARQRequestPendingLo->dest, __ARQRequestPendingLo->length);
            else
                ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->dest,
                           __ARQRequestPendingLo->source, __ARQRequestPendingLo->length);

            __ARQCallbackLo = __ARQRequestPendingLo->callback;
        }
        else
        {
            if (__ARQRequestPendingLo->type == ARQ_TYPE_MRAM_TO_ARAM)
                ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->source,
                           __ARQRequestPendingLo->dest, __ARQChunkSize);
            else
                ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->dest,
                           __ARQRequestPendingLo->source, __ARQChunkSize);
        }

        __ARQRequestPendingLo->length -= __ARQChunkSize;
        __ARQRequestPendingLo->source += __ARQChunkSize;
        __ARQRequestPendingLo->dest += __ARQChunkSize;
    }
}
void __ARQCallbackHack(void) { return; }

void __ARQInterruptServiceRoutine(void)
{

    if (__ARQCallbackHi)
    {
        (*__ARQCallbackHi)((u32)__ARQRequestPendingHi);
        __ARQRequestPendingHi = NULL;
        __ARQCallbackHi = NULL;
    }

    else if (__ARQCallbackLo)
    {
        (*__ARQCallbackLo)((u32)__ARQRequestPendingLo);
        __ARQRequestPendingLo = NULL;
        __ARQCallbackLo = NULL;
    }

    __ARQPopTaskQueueHi();

    if (__ARQRequestPendingHi == NULL)
        __ARQServiceQueueLo();
}

void ARQInit(void)
{

    if (TRUE == __ARQ_init_flag)
    {
        return;
    }

    OSRegisterVersion(__ARQVersion);
    __ARQRequestQueueHi = __ARQRequestQueueLo = NULL;
    __ARQChunkSize = ARQ_CHUNK_SIZE_DEFAULT;
    ARRegisterDMACallback(&__ARQInterruptServiceRoutine);
    __ARQRequestPendingHi = NULL;
    __ARQRequestPendingLo = NULL;
    __ARQCallbackHi = NULL;
    __ARQCallbackLo = NULL;
    __ARQ_init_flag = TRUE;
}

void ARQPostRequest(ARQRequest *request, u32 owner, u32 type, u32 priority, u32 source, u32 dest,
                    u32 length, ARQCallback callback)
{

    BOOL enabled;

    request->next = NULL;
    request->owner = owner;
    request->type = type;
    request->source = source;
    request->dest = dest;
    request->length = length;

    if (callback)
    {
        request->callback = callback;
    }
    else
    {
        request->callback = (ARQCallback)&__ARQCallbackHack;
    }

    enabled = OSDisableInterrupts();

    switch (priority)
    {
    case ARQ_PRIORITY_LOW:

        if (__ARQRequestQueueLo)
        {
            __ARQRequestTailLo->next = request;
        }
        else
        {
            __ARQRequestQueueLo = request;
        }
        __ARQRequestTailLo = request;

        break;

    case ARQ_PRIORITY_HIGH:

        if (__ARQRequestQueueHi)
        {
            __ARQRequestTailHi->next = request;
        }
        else
        {
            __ARQRequestQueueHi = request;
        }

        __ARQRequestTailHi = request;

        break;
    }

    if ((__ARQRequestPendingHi == NULL) && (__ARQRequestPendingLo == NULL))
    {
        __ARQPopTaskQueueHi();

        if (__ARQRequestPendingHi == NULL)
        {
            __ARQServiceQueueLo();
        }
    }

    OSRestoreInterrupts(enabled);
}

u32 ARQGetChunkSize(void) { return __ARQChunkSize; }