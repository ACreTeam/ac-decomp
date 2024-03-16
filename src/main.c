#include "main.h"

#include "boot.h"
#include "irqmgr.h"
#include "sys_stacks.h"
#include "graph.h"
#include "libultra/osMesg.h"
#include "libultra/os_thread.h"
#include "jsyswrap.h"
#include "m_card.h"
#include "_mem.h"
#include "padmgr.h"
#include "libultra/setthreadpri.h"
#include "m_msg.h"
#include "Famicom/famicom.h"
#include "m_debug.h"
#include "dolphin/os.h"
#include "libforest/osreport.h"
#include "m_land.h"

// TODO: actually add all the stacks and headers

OSThread graphThread;
static OSMessage serialMsgBuf;
static OSMessageQueue l_serialMsgQ;
u8 SegmentBaseAddress[0x40];

int ScreenWidth = SCREEN_WIDTH;
int ScreenHeight = SCREEN_HEIGHT;

extern void mainproc(void* val) {

    irqmgr_client_t irqClient;
    OSMessageQueue irqMgrMsgQueue;
    OSMessage irqMsgBuf[10];
    OSMessage msg;

    ScreenWidth = SCREEN_WIDTH;
    ScreenHeight = SCREEN_HEIGHT;

    JW_BeginFrame();
    JW_EndFrame();
    mCD_init_card();

    osCreateMesgQueue(&l_serialMsgQ, &serialMsgBuf, 1);
    osCreateMesgQueue(&irqMgrMsgQueue, irqMsgBuf, 10);
    CreateIRQManager(irqmgrStack + IRQMGR_STACK_SIZE, IRQMGR_STACK_SIZE, 18, 1);
    irqmgr_AddClient(&irqClient, &irqMgrMsgQueue);
    memset(padmgrStack, 0xEB, PADMGR_STACK_SIZE);

    padmgr_Create(&l_serialMsgQ, 7, 15, padmgrStack + PADMGR_STACK_SIZE, PADMGR_STACK_SIZE);

    osCreateThread2(&graphThread, 4, graph_proc, val, graphStack + GRAPH_STACK_SIZE, GRAPH_STACK_SIZE, 8);

    JW_BeginFrame();
    JW_EndFrame();

    osStartThread(&graphThread);
    osSetThreadPri(NULL, 5);

    JW_Init3();
    mMsg_aram_init2();
    mLd_StartFlagOn();
    famicom_mount_archive();

    JC_JKRAramHeap_dump(JC_JKRAram_getAramHeap());
    osSetThreadPri(NULL, 13);

    do {
        msg = NULL;
        while (irqMgrMsgQueue.usedCount != 0) {
            osRecvMesg(&irqMgrMsgQueue, NULL, 0);
        }

        osRecvMesg(&irqMgrMsgQueue, &msg, 1);
    } while (msg != NULL);
}

u32 entry(void) {
    padmgr_Init(NULL);
    new_Debug_mode();

    SETREG(SREG, 0, 0);
    mainproc(NULL);

    return 0;
}

void foresta_main(void) {
    OSReport("どうぶつの森 main2 開始\n");
    HotStartEntry = &entry;
}
