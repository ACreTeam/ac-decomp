#include "jaudio_NES/kappa.h"
#include "jaudio_NES/audiostruct.h"
#include "jaudio_NES/audiowork.h"

int kappa_seq_handle = 0;

int Na_GetKappaCounter(kappa* kappa) {
    int counter;
    group* group = nullptr;
    int temp = 0;

    if (AG.groups[kappa_seq_handle].flags.enabled != 0) {
        group = &(AG.groups)[kappa_seq_handle];

    } else {
        return -1;
    }

    (void)temp;

    counter = group->counter;

    kappa->unk0 = counter / 192;
    counter -= (kappa->unk0 * 0xC0);
    kappa->unk4 = counter / 192.0f;

    return 0;
}

void Na_SetKappaSeqHandle(int flag) {
    kappa_seq_handle = flag;
}
