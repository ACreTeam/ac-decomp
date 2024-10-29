#include "ef_lamp_light.h"
#include "m_field_info.h"
#include "m_lights.h"
#include "m_common_data.h"
#include "m_name_table.h"

static void Ef_Lamp_Light_actor_ct(ACTOR* actor, GAME* game);
static void Ef_Lamp_Light_actor_dt(ACTOR* actor, GAME* game);
static void Ef_Lamp_Light_actor_move(ACTOR* actor, GAME* game);

ACTOR_PROFILE Lamp_Light_Profile = {
    mAc_PROFILE_LAMP_LIGHT,
    ACTOR_PART_EFFECT,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(LAMPLIGHT_ACTOR),
    Ef_Lamp_Light_actor_ct,
    Ef_Lamp_Light_actor_dt,
    (mActor_proc)Ef_Lamp_Light_actor_move,
    NONE_ACTOR_PROC,
    NULL,
};

static void Ef_Lamp_Light_actor_ct(ACTOR* actor, GAME* game) {
    LAMPLIGHT_ACTOR* lamp = (LAMPLIGHT_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;

    play->kankyo.lamp_light = &lamp->lights;
    Light_diffuse_ct(&lamp->lights, 0, 0x50, 0, 0, 0, 0);
    lamp->node_p = Global_light_list_new(game, &play->global_light, &lamp->lights);
}

static void Ef_Lamp_Light_actor_dt(ACTOR* actor, GAME* game) {
    LAMPLIGHT_ACTOR* lamp = (LAMPLIGHT_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;

    play->kankyo.lamp_light = NULL;
    Global_light_list_delete(&play->global_light, lamp->node_p);
}

static int eLL_get_light_sw_other_room() {
    int ret = 0;
    // Not before 6 p.m or past 6 a.m
    if ((Common_Get(time.now_sec) < 21600) || (Common_Get(time.now_sec) >= 64800)) {
        ret = 1;
    }

    return ret;
}

static int eLL_get_light_sw_player_room() {
    // 6 p.m to 11 p.m
    if ((Common_Get(time.now_sec) >= 64800) && (Common_Get(time.now_sec) < 82800)) {
        return 1;
    }

    return 0;
}

static int eLL_get_light_sw_start_demo() {
    int ret = 1;

    if (Common_Get(sunlight_flag) == 1) {
        ret = 0;
    }

    return ret;
}

static void eLL_ctrl_light_sw(LAMPLIGHT_ACTOR* lamp) {
    int ret = 0;

    switch (Common_Get(field_type)) {
        case 2:
        case 3:
            switch (mFI_GetFieldId()) {
                case mFI_FIELD_PLAYER0_ROOM:
                case mFI_FIELD_PLAYER1_ROOM:
                case mFI_FIELD_PLAYER2_ROOM:
                case mFI_FIELD_PLAYER3_ROOM:
                    ret = eLL_get_light_sw_player_room(lamp);
                    break;

                case mFI_FIELD_DEMO_STARTDEMO:
                case mFI_FIELD_DEMO_STARTDEMO2:
                    ret = eLL_get_light_sw_start_demo();
                    break;

                default:
                    ret = eLL_get_light_sw_other_room();
                    break;
            }
            break;

        case 1:
            ret = eLL_get_light_sw_player_room(lamp);
            break;
    }

    lamp->switch_type = ret;
}

static void Ef_Lamp_Light_actor_move(ACTOR* actor, GAME* game) {
    static s16 add_data_off[] = { 2, 2, 1, 0 };
    static s16 add_data_on[] = { 16, 16, 8, 0 };
    static s16* add_data[] = { add_data_off, add_data_on };
    static s16 cmp_data_off[] = { 0, 0, 0, 0 };
    static s16 cmp_data_on[] = { 0xC8, 0xC8, 0x96, 0 };
    static s16* cmp_data[] = { cmp_data_off, cmp_data_on };

    LAMPLIGHT_ACTOR* lamp = (LAMPLIGHT_ACTOR*)actor;

    s16 val;
    u8* color;
    s16* add;
    int type;
    s16* cmp;
    int i;

    eLL_ctrl_light_sw(lamp);
    color = lamp->lights.lights.diffuse.color;
    type = lamp->switch_type;
    add = add_data[type];
    cmp = cmp_data[type];

    for (i = 0; i < 3; i++, add++, cmp++, color++) {
        val = *color;
        chase_s(&val, *cmp, (0.5f * *add));
        *color = val;
    }
}
