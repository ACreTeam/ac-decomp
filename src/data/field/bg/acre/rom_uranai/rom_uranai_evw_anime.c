#include "evw_anime.h"

static EVW_ANIME_SCROLL rom_uranai_evw_anime_2[] = { { 0, 0, 32, 32 }, { 0, 12, 32, 32 } };

static EVW_ANIME_SCROLL rom_uranai_evw_anime_3[] = { { 0, 0, 32, 32 }, { 1, 1, 32, 32 } };

extern EVW_ANIME_DATA rom_uranai_evw_anime[] = {
    { 2, EVW_ANIME_TYPE_SCROLL2, rom_uranai_evw_anime_2 },
    { -3, EVW_ANIME_TYPE_SCROLL2, rom_uranai_evw_anime_3 },
};
