#include "m_scene.h"

extern Actor_data PLAYER_SELECT2_player_data[];
extern s16 PLAYER_SELECT2_ctrl_actor_data[];

extern Scene_Word_u PLAYER_SELECT2_info[] = {
    mSc_DATA_SOUND(0, 0),                                    // Sound data
    mSc_DATA_PLAYER(PLAYER_SELECT2_player_data),             // Player Data
    mSc_DATA_ARRANGE_ROOM_CT(),                              // Arrange_room construct
    mSc_DATA_CTRL_ACTORS(3, PLAYER_SELECT2_ctrl_actor_data), // Control actors
    mSc_DATA_FIELDCT(mSc_ITEM_TYPE_BGITEM, 1, 0xA000, mSc_ROOM_TYPE_MISC_ROOM,
                     FIELD_DRAW_TYPE_PLAYER_SELECT), // Field construct params
    mSc_DATA_END(),                                  // End of scene data
};

extern Actor_data PLAYER_SELECT2_player_data[] = {
    {
        mAc_PROFILE_PLAYER, // profile
        { 100, 0, 120 },    // position
        { 0, 0, 0 },        // rotation
        0                   // ct arg
    },
};

extern s16 PLAYER_SELECT2_ctrl_actor_data[] = {
    mAc_PROFILE_BIRTH_CONTROL,  // 0
    mAc_PROFILE_NPC2,           // 1
    mAc_PROFILE_EFFECT_CONTROL, // 2
};
