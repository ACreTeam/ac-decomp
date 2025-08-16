#ifndef M_KANKYO_H
#define M_KANKYO_H

#include "types.h"
#include "m_lights.h"
#include "m_play_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mEnv_POINT_LIGHT_NUM 4
#define mEnv_RAINBOW_TIME_START (9 * mTM_SECONDS_IN_HOUR)
#define mEnv_RAINBOW_TIME_END (15 * mTM_SECONDS_IN_HOUR)
#define mEnv_RAINBOW_TIME_BYE (15 * mTM_SECONDS_IN_HOUR + 30 * mTM_SECONDS_IN_MINUTE)
#define mEnv_TERM_NUM 8
#define mEnv_FOG_NEAR_MAX 996
#define mEnv_FOG_FAR_MAX 1600
#define mEnv_LIGHT_ANIME_FRAMES 20
#define mEnv_NPC_LIGHTS_OFF_TIME (5 * mTM_SECONDS_IN_HOUR)
#define mEnv_NPC_LIGHTS_ON_TIME (18 * mTM_SECONDS_IN_HOUR)

#define mEnv_WEATHER_TERM_NUM 20
#define mEnv_WIND_TERM_NUM 4u
#define mEnv_WIND_CHANGE_RATE (f32)(10 * mTM_SECONDS_IN_MINUTE * 60) // 60fps, 10 minutes

#if VERSION == VER_GAFU01_00
#define mEnv_CHANGE_WEATHER_ENV_RATE (1.0f/250.0f);
#else
#define mEnv_CHANGE_WEATHER_ENV_RATE (1.0f/600.0f);
#endif

enum weather {
    mEnv_WEATHER_CLEAR,
    mEnv_WEATHER_RAIN,
    mEnv_WEATHER_SNOW,
    mEnv_WEATHER_SAKURA,
    mEnv_WEATHER_LEAVES,

    mEnv_WEATHER_NUM
};

enum weather_intensity {
    mEnv_WEATHER_INTENSITY_NONE,
    mEnv_WEATHER_INTENSITY_LIGHT,
    mEnv_WEATHER_INTENSITY_NORMAL,
    mEnv_WEATHER_INTENSITY_HEAVY,

    mEnv_WEATHER_INTENSITY_NUM,
};

enum {
    mEnv_LIGHT_TYPE_PLAYER,
    mEnv_LIGHT_TYPE_TENT,
    mEnv_LIGHT_TYPE_LIGHTHOUSE,

    mEnv_LIGHT_TYPE_NUM
};

enum {
    mEnv_SWITCH_STATUS_ON,
    mEnv_SWITCH_STATUS_OFF,
    mEnv_SWITCH_STATUS_TURNING_OFF,
    mEnv_SWITCH_STATUS_TURNING_ON,

    mEnv_SWITCH_STATUS_NUM
};

enum {
    mEnv_WIND_STATE_STEADY,
    mEnv_WIND_STATE_FAST,
    mEnv_WIND_STATE_SLOW,
    mEnv_WIND_STATE_REDUCING,

    mEnv_WIND_STATE_NUM
};

#define mEnv_SAVE_GET_WEATHER_TYPE(w) (((w) & 0xF0) >> 4)
#define mEnv_SAVE_GET_WEATHER_INTENSITY(w) ((w) & 0xF)

typedef struct base_light_s {
    u8 ambient_color[3];
    s8 sun_dir[3];
    u8 sun_color[3];
    s8 moon_dir[3];
    u8 moon_color[3];
    u8 fog_color[3];
    s16 fog_near;
    s16 fog_far;
    u8 shadow_color[3];
    u8 room_color[3];
    u8 sun_color_window[3];
    u8 moon_color_window[3];
    u8 background_color[3];
} BaseLight;

typedef struct add_light_info_s {
    s16 ambient_color[3];
    s16 diffuse_color[3];
    s16 fog_color[3];
    s16 fog_near;
    s16 fog_far;
} AddLightInfo;

typedef void (*NATURE_PROC)(ACTOR*);

typedef struct nature_s {
    NATURE_PROC proc;
    void* arg;
} Nature;

typedef struct kankyo_s {
    /* 0x00 */ Lights sun_light;
    /* 0x0E */ Lights moon_light;
    /* 0x1C */ Lights* lamp_light;
    /* 0x20 */ Lights point_light;
    /* 0x30 */ int _30;
    /* 0x34 */ u8 _34[0x78 - 0x34];
    /* 0x78 */ AddLightInfo add_light_info; /* extra values added to specific light parameters */
    /* 0x90 */ int _90;
    /* 0x94 */ BaseLight base_light;
    /* 0xBA */ u8 _BA[0xC0 - 0xBA];
    /* 0xC0 */ f32 shadow_pos;
    /* 0xC4 */ u8 shadow_alpha;
    /* 0xC5 */ u8 countdown_timer;
    /* 0xC8 */ Nature nature;
} Kankyo;

extern void mEnv_regist_nature(Kankyo* kankyo, NATURE_PROC nature_proc, void* arg);
extern int mEnv_unregist_nature(Kankyo* kankyo, NATURE_PROC nature_proc);
extern void Global_kankyo_ct(GAME* game, Kankyo* kankyo);
extern void mEnv_GetRoomPrimColor(u8* r, u8* g, u8* b, GAME_PLAY* play);
extern void Global_kankyo_set_room_prim(GAME* game);
extern int mEnv_RequestChangeLightON(GAME_PLAY* play, int light_on_type, int play_sfx);
extern int mEnv_RequestChangeLightOFF(GAME_PLAY* play, int light_off_type, f32 step);
extern void mEnv_ManagePointLight(GAME_PLAY* play, Kankyo* kankyo, Global_light* global_light);
extern void Global_kankyo_set(GAME_PLAY* play, Kankyo* kankyo, Global_light* global_light);
extern void staffroll_light_init(GAME_PLAY* play);
extern void staffroll_light_proc_start(GAME_PLAY* play);
extern int staffroll_light_proc_end(GAME_PLAY* play);
extern void staffroll_light_dt(GAME_PLAY* play);
extern void mEnv_GetShadowPrimColor_Light(u8* r, u8* g, u8* b, GAME* game);
extern int mEnv_PointLightMin();
extern int mEnv_HereIsPlayerSelect();
extern f32 mKK_windowlight_alpha_get();
extern int mEnv_ReqeustChangeWeatherEnviroment(s16 now_weather, s16 next_weather);
extern int mEnv_ReservePointLight(GAME_PLAY* play, xyz_t* pos, u8 r, u8 g, u8 b, s16 power);
extern void mEnv_OperateReservedPointLight_Position(int point_light_idx, xyz_t* pos);
extern void mEnv_OperateReservedPointLight_Color(int point_light_idx, u8 r, u8 g, u8 b);
extern void mEnv_OperateReservedPointLight_Power(int point_light_idx, s16 power);
extern void mEnv_OperateReservedPointLight(int point_light_idx, xyz_t* pos, u8 r, u8 g, u8 b, s16 power);
extern int mEnv_CancelReservedPointLight(int point_light_idx, GAME_PLAY* play);
extern void mEnv_DecideWindDirect(s_xyz* dir, s16 x, s16 z);
extern void mEnv_RandomWeather(s16* next_weather, s16* next_intensity);
extern s16 mEnv_GetWindAngleS();
extern f32 mEnv_GetWindPowerF();
extern f32 mEnv_GetWindPowerF_Windmill();
extern void mEnv_DecideTodayWindPowerRange();
extern void mEnv_ChangeWind();
extern void mEnv_WindMove();
extern void mEnv_DecideWeather_GameStart();
extern void mEnv_DecideWeather_FirstGameStart();
extern void mEnv_PreRainNowFine_Init();
extern void mEnv_DecideWeather_NormalGameStart();
extern int mEnv_NowWeather();

#ifdef __cplusplus
}
#endif

#endif
