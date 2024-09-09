#include "jaudio_NES/radio.h"
#include "jaudio_NES/game64.h"
#include "jaudio_NES/audiowork.h"

int Na_GetRadioCounter(Radio_c* radio) {
    int counter;
    u16 tempo = 0;

    group* group = nullptr;
    int unused = 0;

    if (AG.groups[sou_now_bgm_handle].flags.enabled != 0 && AG.groups[sou_now_bgm_handle].seq_id == 0xDA) {
        group = &(AG.groups)[sou_now_bgm_handle];

    } else {
        return -1;
    }

    counter = group->counter;

    (void)unused;

    if (counter < 744) {
        radio->unk0 = 0;
    } else {
        counter -= 744;
        radio->unk0 = (s8)(counter / 768);
        counter = counter - (radio->unk0 * 768);
        radio->unk0++;
    }
    if (radio->unk0 == 9) {
        radio->unk4 = counter / 216.0f;

    } else {
        radio->unk4 = counter / 768.0f;
    }

    radio->tempo = AG.groups[sou_now_bgm_handle].tempo / 48;
    tempo = radio->tempo;
    return 0;
}
