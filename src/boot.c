#include "boot.h"

static u8 nintendo_hi_0[0x9900]; // This should be nintendo_hi_0.aw
extern u32 *StringTable;

u32 soundArenaAlloc(void){
    return 0;
}

u32 search_partial_address(u32 add){
    //TODO
}

u32 convert_partial_address(u32 add){
    //TODO
}

int LoadStringTable(char table){ //https://decomp.me/scratch/7syDa
    
    OSReport("ストリングテーブル読み込み開始\n");
    osGetTime();
    StringTable = JC__JKRDvdToMainRam_byName(table, 0, 1);
    
    if (StringTable == 0){
        OSDVDFatalError();
    }
    OSSetStringTable(StringTable);
    osGetTime();
    OSReport("ストリングテーブル読み込み 完了\n");
    return 0;
}

void UnLink(u32 linkre){
    //TODO
}

void LoadLink(u32 link){
//TODO
}

void audioFatalCallback(void) {

OSReport("audioFatalCallback\x1B\x5B\x6D\n");
OSDVDFatalError();

}

void sound_initial(void){ 

Na_InitAudio(audioFatalCallback, 0, 0, nintendo_hi_0, 0x66a0, 0);
OSReport("sizeof(nintendo_hi_0)=%08x\n", 0x9900);
OSReport("実際のnintendo_hi_0.awのサイズ=%08x \n", 0x66a0);
OSReport("ニンテンド\x81\x5B発生タイムラグまで寝てます(%dms)\x1B\x5B\x6D\n", 0x9c4);
msleep(0x9c4);

}

}

void sound_initial2(void) {

while(!(Na_CheckNeosBoot() & 0xFF)){
    VIWaitForRetrace();
    Na_GameFrame();
}
bzero(&nintendo_hi_0, sizeof(nintendo_hi_0));
    
}

void HotResetIplMenu(void) {
    if((osAppNMIBuffer[15] & 0x10) != 0){
        OSChangeBootMode(1);
    }
    OSResetSystem(1,osAppNMIBuffer[15], 1);
}

void fault_callback_keyCheck(u32 key){ //https://decomp.me/scratch/MMa4E
    //To Finish 
}

void fault_callback_OK(void) {
fault_Printf("\nOK! YOU ARE GREAT!\n");
fault_WaitTime(0x7d0);
}

void fault_callback_Setumei(void) {
fault_Printf("\n+ KEY to SCROLL UP/DOWN\nB BUTTON: TOP OF CONSOLE\nA BUTTON: BOTTOM OF CONSOLE\n");
}

void fault_callback_vimode(void){
//TODO
}

void fault_callback_scroll(void){
//TODO
}

void adjustOSArena(){ //https://decomp.me/scratch/LdpbQ
// To Finish
}

int main(int argc, const char **argv){ //https://decomp.me/scratch/frpgE
// To Finish
}