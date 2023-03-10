#include "main.h"
#include "boot.h"

//TODO: actually add all the stacks and headers

void mainproc (void* val){ 
    static OSMessageQueue l_serialMsgQ;
    static OSMessage serialMsgBuf;
    IrqMgrClient irqClient;
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
    osSetThreadPri(0, 5);

    JW_Init3();
    mMsg_aram_init2();
    mLd_StartFlagOn();
    famicom_mount_archive();
    
    JC_JKRAramHeap_dump(JC_JKRAram_getAramHeap());
    osSetThreadPri(0, 13);

    do {
        msg = NULL;
        while (irqMgrMsgQueue.usedCount != 0) {
            osRecvMesg(&irqMgrMsgQueue, NULL, 0);
        }

        osRecvMesg(&irqMgrMsgQueue, &msg, 1);
    } while (msg != NULL);
}



u32 entry(void) { // TODO: debug_mode struct thing
    padmgr_Init(0);
    new_Debug_mode();
    
    debug_mode.idk = 0;
    mainproc(0);

    return 0;
}



void main_foresta(void){
    OSReport("どうぶつの森 main2 開始");
    HotStartEntry = (u32)&entry;
}
