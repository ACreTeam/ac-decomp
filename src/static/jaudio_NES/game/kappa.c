#include "jaudio_NES/kappa.h"
#include "jaudio_NES/audiostruct.h"
#include "jaudio_NES/audiowork.h"

int kappa_seq_handle = 0;

int Na_GetKappaCounter(kappa* kappa) {
    int unk16;
    group* group = nullptr;
    int temp = 0;
    
    if (AG.groups[kappa_seq_handle].flags.enabled != 0) {
        group = &(AG.groups)[kappa_seq_handle];

    } else {
        return -1;
    }

    (void)temp;

    unk16 = group->unk016;

    kappa->unk0 = unk16 / 192;
    unk16 -= (kappa->unk0 * 0xC0);
    kappa->unk4 = unk16 / 192.0f;
    
    return 0;
}
 
void Na_SetKappaSeqHandle(int flag) {
    kappa_seq_handle = flag;
}
