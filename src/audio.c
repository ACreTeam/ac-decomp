#include "audio.h"

#include "jaudio_NES/game64.h"
#include "jaudio_NES/melody.h"
#include "jaudio_NES/rhythm.h"
#include "jaudio_NES/radio.h"
#include "dolphin/os/OSRtc.h"
#include "m_common_data.h"
#include "m_camera2.h"
#include "sys_math.h"
#include "jaudio_NES/kappa.h"
#include "jaudio_NES/staff.h"

int S_ongenpos_refuse_fg;

static void sAdo_Calc_MicPosition_common(f32* fcalc, u16* scalc, xyz_t* pos) {

    f32 diff;
    xyz_t posd;
    xyz_t* camera_pos;
    s16 val;
    camera_pos = Camera2_getMicPos_p((GAME_PLAY*)gamePT);

    posd.x = pos->x - camera_pos->x;
    posd.z = pos->y - camera_pos->y;
    posd.y = pos->z - camera_pos->z;

    val = atans_table(posd.y, posd.x);

    if (fcalc != NULL) {
        *fcalc = sqrtf((posd.x * posd.x) + (posd.z * posd.z) + (posd.y * posd.y));
    }
    if (scalc != NULL) {
        *scalc = val;
    }
}

extern void sAdo_Calc_MicPosition_forTrig(f32* fcalc, u16* scalc, xyz_t* pos) {

    sAdo_Calc_MicPosition_common(fcalc, scalc, pos);
}

extern void sAdo_Calc_MicPosition_forLevel(f32* fcalc, u16* scalc, xyz_t* pos) {

    sAdo_Calc_MicPosition_common(fcalc, scalc, pos);
}

extern void sAdo_GameFrame() {
    Na_GameFrame();
}

extern void sAdo_BgmStart(u8 id) {
    Na_BgmStart(id);
}

extern void sAdo_BgmStop(u16 id) {
    Na_BgmStop(id);
}
extern void sAdo_SysTrgStart(u16 id) {
    Na_SysTrgStart(id);
}

extern void sAdo_PlyWalkSe(int walk, xyz_t* pos) {

    f32 fcalc;
    u16 scalc;
    sAdo_Calc_MicPosition_forTrig(&fcalc, &scalc, pos);

    Na_PlyWalkSe(walk, scalc, fcalc);
}

extern void sAdo_PlyWalkSeRoom(int walk, xyz_t* pos) {

    f32 fcalc;
    u16 scalc;
    sAdo_Calc_MicPosition_forTrig(&fcalc, &scalc, pos);

    Na_PlyWalkSeRoom(walk, scalc, fcalc);
}

extern void sAdo_NpcWalkSe(int walk, xyz_t* pos) {

    f32 fcalc;
    u16 scalc;
    sAdo_Calc_MicPosition_forTrig(&fcalc, &scalc, pos);

    Na_NpcWalkSe(walk, scalc, fcalc);
}

extern void sAdo_NpcWalkSeRoom(int walk, xyz_t* pos) {

    f32 fcalc;
    u16 scalc;
    sAdo_Calc_MicPosition_forTrig(&fcalc, &scalc, pos);

    Na_NpcWalkSeRoom(walk, scalc, fcalc);
}

extern void sAdo_PlayerStatusLevel(f32 speed, int p) {

    Na_PlayerStatusLevel(speed, p);
}

extern void sAdo_VoiceSe(u8 num, u8 num2, u8 num3, s16 character_idx, u8 scale, u8 mode) {

    Na_VoiceSe(num, num2, num3, character_idx, scale, mode);
}

extern void sAdo_Inst(u16 num, u8* p) {
    Na_Inst(num, p);
}

extern void sAdo_MessageStatus(u8 status) {

    Na_MessageStatus(status);
}

extern void sAdo_MessageSpeed(u8 speed) {

    Na_MessageSpeed(speed);
}

extern u8 sAdo_MessageSpeedGet() {

    return Na_MessageSpeedGet();
}

extern void sAdo_SysLevStart(u8 id) {

    Na_SysLevStart(id);
}

extern void sAdo_SysLevStop(u8 id) {

    Na_SysLevStop(id);
}

extern void sAdo_OngenPos(u32 p1, u8 p2, xyz_t* pos) {

    u16 scalc;
    f32 fcalc;

    if (S_ongenpos_refuse_fg == 0) {
        sAdo_Calc_MicPosition_forLevel(&fcalc, &scalc, pos);
        Na_OngenPos(p1, p2, scalc, fcalc);
    }
}

extern void sAdo_OngenTrgStart(u16 id, xyz_t* pos) {

    u16 scalc;
    f32 fcalc;

    sAdo_Calc_MicPosition_forTrig(&fcalc, &scalc, pos);
    Na_OngenTrgStart(id, scalc, fcalc);
}

extern void sAdo_SetOutMode(u8 mode) {

    if (OSGetSoundMode() == 0) {
        Na_SetOutMode(1);
    } else if (mode == 1) {
        Na_SetOutMode(0);
    } else {
        Na_SetOutMode(mode);
    }
}

extern void sAdo_SetVoiceMode(u8 mode) {

    Na_SetVoiceMode(mode);
}

extern void sAdo_FloorTrgStart(u16 id, xyz_t* pos) {

    u16 scalc;
    f32 fcalc;

    sAdo_Calc_MicPosition_forTrig(&fcalc, &scalc, pos);
    Na_FloorTrgStart(id, scalc, fcalc);
}

extern void sAdo_RhythmStart(u32 p, s8 type, s8 wait) {

    Na_RhythmStart(p, type, wait);
}

extern void sAdo_RhythmStop(u32 p) {

    Na_RhythmStop(p);
}

extern void sAdo_RhythmAllStop() {

    Na_RhythmAllStop();
}

extern void sAdo_FurnitureInst(int track_id, s8 cb, s32 cl, xyz_t* pos) {

    u16 scalc;
    f32 fcalc;

    sAdo_Calc_MicPosition_common(&fcalc, &scalc, pos);
    Na_FurnitureInst(track_id, cb, cl, scalc, fcalc);
}

extern void sAdo_Pause(u8 mode) {

    Na_Pause(mode);
}

extern f32 sAdo_GetRhythmAnimCounter(u32 p) {

    return Na_GetRhythmAnimCounter(p);
}

extern s8 sAdo_GetRhythmDelay(u32 p) {

    return Na_GetRhythmDelay(p);
}

extern f32 sAdo_GetRhythmInfo(u32 p) {

    return Na_GetRhythmInfo(p);
}

extern void sAdo_SetRhythmInfo(f32 p) {

    Na_SetRhythmInfo(p);
}

extern int sAdo_InstCountGet() {

    return Na_InstCountGet();
}

extern void sAdo_RhythmPos(u32 p, u8 haniwa_id, xyz_t* pos) {

    u16 scalc;
    f32 fcalc;

    sAdo_Calc_MicPosition_forLevel(&fcalc, &scalc, pos);
    Na_RhythmPos(p, haniwa_id, scalc, fcalc);
}

extern void sAdo_SpecChange(int spec) {

    Na_SpecChange(spec);
}

extern void sAdo_MDPlayerPos(xyz_t* pos, u16 s1, u16 s2, int p) {

    u16 scalc;
    f32 fcalc;

    sAdo_Calc_MicPosition_common(&fcalc, &scalc, pos);
    Na_MDPlayerPos(scalc, s1, s2, p, fcalc);
}

extern void sAdo_BGMVolume(f32 volume, u16 vol_move_ctr) {

    Na_BGMVolume(volume, vol_move_ctr);
}

extern void sAdo_BgmCrossfadeStart(u8 b) {

    Na_BgmCrossfadeStart(b);
}

extern void sAdo_SubGameStart() {

    Na_SubGameStart();
}

extern void sAdo_SubGameEnd() {

    Na_SubGameEnd();
}

extern int sAdo_SubGameOK() {

    return Na_SubGameOK();
}

extern void sAdo_Tenki(u8 mode) {

    Na_Tenki(mode);
}

extern void sAdos_KishaStatusTrg(u8 state) {

    Na_KishaStatusTrg(state);
}

extern void sAdos_KishaStatusLevel(f32 speed, u32 ongenNum1, u16 angle1, f32 distance1, u32 ongenNum2, u16 angle2,
                                   f32 distance2) {

    Na_KishaStatusLevel(speed, ongenNum1, angle1, distance1, ongenNum2, angle2, distance2);
}

extern void sAdos_GetRadioCounter(void* p) {
    Na_GetRadioCounter(p);
}

extern void sAdos_GetKappaCounter(void* p) {

    Na_GetKappaCounter(p);
}

extern void sAdos_GetStaffRollInfo(void* p) {

    Na_GetStaffRollInfo(p);
}

extern void sAdos_TTKK_ARM(u8 mode) {

    Na_TTKK_ARM(mode);
}

extern void sAdo_OngenTrgStartSpeed(f32 speed, u16 s1, xyz_t* pos) {

    f32 fcalc;
    u16 scalc;

    sAdo_Calc_MicPosition_forTrig(&fcalc, &scalc, pos);

    Na_OngenTrgStartSpeed(s1, scalc, fcalc, speed);
}

extern void sAdo_TrgSeEcho(u8 b) {

    Na_TrgSeEcho(b);
}

extern void sAdo_LevSeEcho(u8 b) {

    Na_LevSeEcho(b);
}

extern u8 sAdo_BgmFadeoutCheck() {

    Na_BgmFadeoutCheck();
}

extern u8 sAdo_SeFadeoutCheck() {

    Na_SeFadeoutCheck();
}

extern void sAdo_RoomType(u8 type) {

    Na_RoomType(type);
}

extern void sAdo_Museum(u8 type) {

    Na_Museum(type);
}

extern void sAdo_SoftReset() {

    Na_SoftReset();
}

u16 sAdo_Get_WalkLabel(int type) {

    u16 ret;
    switch (type) {
        case 0:
        case 1:
        case 2:
            if (Common_Get(time.season) != 3) {
                ret = 0x4201;
            } else {
                ret = 0x4206;
            }
            break;
        case 4:
        case 5:
        case 6:
            ret = 0x4202;
            break;
        case 7:
            ret = 0x4203;
            break;
        case 23:
            ret = 0x4204;
            break;
        case 9:
            ret = 0x4205;
            break;
        case 22:
            ret = 0x4208;
            break;
        case 11:
            ret = 0x4209;
            break;
        default:
            ret = 0x4202;
            break;
    }
    return ret;
}

int sAdo_Get_KokeruLabel(int type) {

    u16 label = sAdo_Get_WalkLabel(type);
    int ret;

    switch (label) {
        case 0x4201:
            ret = 0xe;
            break;
        case 0x4206:
            ret = 0x13;
            break;
        case 0x4202:
            ret = 0xf;
            break;
        case 0x4203:
            ret = 0x10;
            break;
        case 0x4204:
            ret = 0x11;
            break;
        case 0x4205:
            ret = 0x12;
            break;
        case 0x4208:
            ret = 0x156;
            break;
        case 0x4209:
            ret = 0x157;
            break;
        default:
            ret = 15;
            break;
    }
    return ret;
}

extern void sAdo_SceneMode(u8 mode) {

    Na_SceneMode(mode);
}

extern u8 sAdo_RoomIncectPos(u32 f, u16 u, xyz_t* pos) {

    u16 scalc;
    f32 fcalc;

    sAdo_Calc_MicPosition_forLevel(&fcalc, &scalc, pos);
    return Na_RoomIncectPos(f, u, scalc, fcalc);
}

extern void sAdo_FurnitureInstPos(u32 f, xyz_t* pos) {

    u16 scalc;
    f32 fcalc;

    sAdo_Calc_MicPosition_forLevel(&fcalc, &scalc, pos);
    Na_FurnitureInstPos(f, scalc, fcalc);
}

extern void sAdo_Set_ongenpos_refuse_fg(int state) {

    S_ongenpos_refuse_fg = state;
}

extern int sAdo_GameframeEnd_Check() {

    return S_ongenpos_refuse_fg;
}

extern int sAdo_GetSoundFrameCounter() {

    return Na_GetSoundFrameCounter();
}

extern int sAdo_CheckOnPlussBridge(xyz_t* pos, u32 atr) {

    f32 x;
    f32 z;
    if ((Common_Get(pluss_bridge_pos) != NULL) && (atr == 0x17)) {
        x = pos->x - Common_Get(pluss_bridge_pos->x);
        z = pos->z - Common_Get(pluss_bridge_pos->z);
        if ((x * x) + (z * z) < 3969.0f) {
            return 1;
        }
    }
    return 0;
}

extern void sAdo_RegistPlussBridge(xyz_t* pos) {

    Common_Set(pluss_bridge_pos, pos);
}

extern void sAdo_DeletePlussBridge() {

    Common_Set(pluss_bridge_pos, NULL);
}

extern void sAdo_kazagurumaLevel(f32 level) {

    Na_kazagurumaLevel(level);
}
