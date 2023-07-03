#ifndef EVW_ANIME_H
#define EVW_ANIME_H

#include "types.h"

#ifdef __cplusplus
extern "C"{
#endif


typedef struct evw_anime_s{
    s16 unk0;
    s16 unk4;
    void* data_p;
}EVW_ANIME_DATA;

void Evw_Anime_Set(GAME*, EVW_ANIME_DATA*);

#ifdef __cplusplus
}
#endif

#endif