#ifndef _DOLPHIN_ARQ
#define _DOLPHIN_ARQ

#include "dolphin/ar/ar.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define ARQ_DMA_ALIGNMENT 32
#define ARQ_CHUNK_SIZE_DEFAULT 4096

#define ARQ_TYPE_MRAM_TO_ARAM ARAM_DIR_MRAM_TO_ARAM
#define ARQ_TYPE_ARAM_TO_MRAM ARAM_DIR_ARAM_TO_MRAM

#define ARQ_PRIORITY_LOW 0
#define ARQ_PRIORITY_HIGH 1

    typedef void (*ARQCallback)(u32 pointerToARQRequest);

    typedef struct ARQRequest
    {

        struct ARQRequest *next;
        u32 owner;
        u32 type;
        u32 priority;
        u32 source;
        u32 dest;
        u32 length;
        ARQCallback callback;

    } ARQRequest;

    void ARQInit(void);
    void ARQReset(void);
    void ARQPostRequest(ARQRequest *task, u32 owner, u32 type, u32 priority, u32 source, u32 dest,
                        u32 length, ARQCallback callback);
    void ARQRemoveRequest(ARQRequest *task);
    void ARQRemoveOwnerRequest(u32 owner);
    void ARQFlushQueue(void);
    void ARQSetChunkSize(u32 size);
    u32 ARQGetChunkSize(void);
    BOOL ARQCheckInit(void);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_ARQ