#include "jaudio_NES/radio.h"
#include "jaudio_NES/game64.h"
#include "jaudio_NES/audiowork.h"


s16 Na_GetRadioCounter(radio* radio) {
    int unk16;
    u16 tempo = 0;
    
    group* group = nullptr;
    int unused = 0;
    

    if (AG.groups[sou_now_bgm_handle].flags.enabled != 0 && AG.groups[sou_now_bgm_handle].seq_id == 0xDA) {
        group = &(AG.groups)[sou_now_bgm_handle];

    } else {
        return -1;
    }

    unk16 = group->unk016;

    (void)unused;

    if (unk16 < 0x2E8) {
        radio->unk0 = 0;
    } else {
        unk16 -= 0x2E8;
        radio->unk0 = (s8)(unk16 / 0x300);
        unk16 = unk16 - (radio->unk0 * 0x300);
        radio->unk0++;
    }
    if (radio->unk0 == 9) {
        radio->unk4 = unk16 / 216.0f;

    } else {
        radio->unk4 = unk16 / 768.0f;
    }

    radio->tempo = AG.groups[sou_now_bgm_handle].tempo / 48;
    tempo = radio->tempo;
    return 0;
}