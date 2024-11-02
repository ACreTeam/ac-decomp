#include "ac_fieldm_draw.h"

#include "m_name_table.h"

static void Fieldm_Actor_ct(ACTOR* actorx, GAME* game);
static void Fieldm_Actor_dt(ACTOR* actorx, GAME* game);
static void Fieldm_Actor_move(ACTOR* actorx, GAME* game);
static void Fieldm_Actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Fieldm_Draw_Profile = {
    mAc_PROFILE_FIELDM_DRAW,
    ACTOR_PART_BG,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(FIELDM_ACTOR),
    &Fieldm_Actor_ct,
    &Fieldm_Actor_dt,
    &Fieldm_Actor_move,
    &Fieldm_Actor_draw,
    NULL,
};
// clang-format on

static void Fieldm_Actor_ct(ACTOR* actorx, GAME* game) {
    // empty
}

static void Fieldm_Actor_dt(ACTOR* actorx, GAME* game) {
    // empty
}

static void Fieldm_Actor_move(ACTOR* actorx, GAME* game) {
    // empty
}

static void Fieldm_Actor_draw(ACTOR* actorx, GAME* game) {
    // empty
}
