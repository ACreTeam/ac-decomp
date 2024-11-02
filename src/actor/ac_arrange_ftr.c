#include "ac_arrange_ftr.h"

#include "m_name_table.h"

static void Arrange_Furniture_Actor_ct(ACTOR* actorx, GAME* game);
static void Arrange_Furniture_Actor_dt(ACTOR* actorx, GAME* game);
static void Arrange_Furniture_Actor_move(ACTOR* actorx, GAME* game);
static void Arrange_Furniture_Actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Arrange_Furniture_Profile = {
    mAc_PROFILE_ARRANGE_FURNITURE,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    ETC_ARRANGE_FURNITURE,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(ARRANGE_FURNITURE_ACTOR),
    &Arrange_Furniture_Actor_ct,
    &Arrange_Furniture_Actor_dt,
    &Arrange_Furniture_Actor_move,
    &Arrange_Furniture_Actor_draw,
    NULL,
};
// clang-format on

static void Arrange_Furniture_Actor_ct(ACTOR* actorx, GAME* game) {
    // empty
}

static void Arrange_Furniture_Actor_dt(ACTOR* actorx, GAME* game) {
    // empty
}

static void Arrange_Furniture_Actor_draw(ACTOR* actorx, GAME* game) {
    // empty
}

static void Arrange_Furniture_Actor_move(ACTOR* actorx, GAME* game) {
    // empty
}
