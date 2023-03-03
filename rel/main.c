#include "main.h"
#include "boot.h"

void mainproc(){
    //TODO
}

u32 entry_foresta(void) { // Something something, needs pad manager? and idk what's debug_mode actually
    OSMesgQueue* osmsg;
    padmgr_Init(NULL,osmsg);
    new_Debug_mode();
    debug_mode[106] = 0;
    mainproc(0);
    return 0; 
}


void main(void){
    OSReport("どうぶつの森 main2 開始");
    HotStartEntry = (u32)&entry;
}
