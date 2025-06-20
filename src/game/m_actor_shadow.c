#include "m_actor_shadow.h"

#include "m_collision_bg.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_lights.h"
#include "libultra/libultra.h"

extern Gfx ef_shadow_out_modelT[];
extern Gfx ef_shadow_in_modelT[];

int mActorShadow_OperateScrollLimit(int value, int step, int limit) {
    if (step != 0) {
        if (step > 0) {
            value += step;
            if (value > limit) {
                value = limit;
            }
        } else if (step < 0) {
            value += step;
            if (value < limit) {
                value = limit;
            }
        }
    }
    return value;
}

Gfx* mActorShadow_TileScroll2(u32* x1, u32* y1, int step1, int step2, int limit1, int limit2, int width1, int height1,
                              u32* x2, u32* y2, int step3, int step4, int limit3, int limit4, int width2, int height2,
                              GAME* game) {

    *x1 = mActorShadow_OperateScrollLimit(*x1, step1, limit1);
    *y1 = mActorShadow_OperateScrollLimit(*y1, step2, limit2);
    *x2 = mActorShadow_OperateScrollLimit(*x2, step3, limit3);
    *y2 = mActorShadow_OperateScrollLimit(*y2, step4, limit4);

    return two_tex_scroll(game->graph, 0, *x1, *y1, width1, height1, 1, *x2, *y2, width2, height2);
}

void mActorShadow_AdjustRate(f32* rate) {
    if (*rate < 0.0f) {
        *rate = 0.0f;
    } else if (*rate > 1.0f) {
        *rate = 1.0f;
    }
}

void mActorShadow_GetTimeAngleY_TimeAlpha(Shadow_Info* shadow, GAME_PLAY* play) {
    f32 timef;
    int timesec = Common_Get(time.now_sec);
    shadow->unk1C = play->kankyo.shadow_alpha;

    // Between 4 a.m and 8 p.m
    if ((timesec >= 14400) && (timesec < 72000)) {
        timef = (timesec - 14400) / 57600.0f;
    } // Between 12 a.m and 4 a.m
    else if (timesec < 14400) {
        timef = 0.5f + timesec / 28800.0f;
    } // Between 8 p.m and 12 a.m
    else {
        timef = (timesec - 72000) / 28800.0f;
    }

    shadow->unk26 = 0x8000 - ((s16)(16384.0f * timef) + 0x6000);
}

void mActorShadow_GetGroundAverageAngle(Shadow_Info* shadow) {
    static xyz_t angle_range_table[4] = {
        { 10.0f, 0.0f, 10.0f },
        { 10.0f, 0.0f, -10.0f },
        { -10.0f, 0.0f, 10.0f },
        { -10.0f, 0.0f, -10.0f },
    };

    int x = 0;
    int y = 0;
    int z = 0;
    int i;

    for (i = 0; i < 4; i++) {
        xyz_t pos = shadow->position;
        s_xyz sangle = { 0, 0, 0 };

        pos.x += angle_range_table[i].x;
        pos.y += angle_range_table[i].y;
        pos.z += angle_range_table[i].z;

        mCoBG_GetBgY_AngleS_FromWpos(&sangle, pos, 0.0f);

        x += sangle.x;
        y += sangle.y;
        z += sangle.z;
    }

    shadow->unk20 = x >> 2;
    shadow->unk22 = y >> 2;
    shadow->unk24 = z >> 2;
}

void mActorShadow_GetDistanceRate(Shadow_Info* shadow, f32 rate) {
    f32 xcalc;
    f32 disty = shadow->position.y - shadow->groundY;

    disty = disty >= 0.0f ? disty : -disty;
    xcalc = rate + 100.0f;

    if (disty > xcalc) {
        shadow->unk14 = 0.600000023842f;
        shadow->unk18 = 0;
        return;
    }

    xcalc = (xcalc - disty) / xcalc;
    shadow->unk14 = xcalc * 0.399999976158f + 0.6f;
    shadow->unk18 = xcalc;
}
f32 mActorShadow_GetAbsBigger(f32 a, f32 b) {
    a = a >= 0.0f ? a : -a;
    b = b >= 0.0f ? b : -b;

    if (a > b) {
        return a;
    }
    return b;
}

void mActorShadow_RadiusScaleRate(ACTOR* actor, Shadow_Info* shadow) {
    f32 abs_bigger = mActorShadow_GetAbsBigger(actor->shape_info.shadow_size_x, actor->shape_info.shadow_size_z);
    shadow->unk10 = (abs_bigger / 19.0f) * 0.018f;
}

void mActorShadow_GetShadowTopPos_GetSlideS(Shadow_Info* shadow) {

    xyz_t wpos;
    xyz_t base;
    f32 bg_y;
    int res;

    if (shadow->kind == 0) {
        base.x = 0.0f;
        base.y = 0.0f;
        base.z = -40.0f;
        sMath_RotateY(&base, shadow->unk26 * (9.58738019108e-05f));
        wpos.x = shadow->position.x + base.x;
        wpos.y = shadow->position.y + base.y;
        wpos.z = shadow->position.z + base.z;
        res = 0;
        bg_y = mCoBG_GetShadowBgY_AngleS_FromWpos(NULL, wpos, 0.0f);
        if ((shadow->position.y - bg_y) > 20.0f) {
            shadow->unk34 = 28;
            return;
        }
    }
    shadow->unk34 = 0;
}

Gfx* mActorShadow_SetTexScroll(ACTOR* actor, Shadow_Info* shadow, GAME* game) {

    u32 y1 = 0;
    u32 x1 = 0;
    u32 y2 = 0;
    int step;

    if (actor->shape_info.unk_20 < shadow->unk34) {
        step = 0xD;
    } else if (actor->shape_info.unk_20 > shadow->unk34) {
        step = -0xD;
    } else {
        step = 0;
    }

    mActorShadow_TileScroll2(&x1, &y1, 0, 0, 0, 0, 0x20, 0x10, (u32*)&actor->shape_info.unk_20, &y2, step, 0,
                             shadow->unk34, 0, 0x20, 0x10, game);
}

void mActorShadow_GetLastAlphaScale(f32* scale, u8* alpha, ACTOR* actor, Shadow_Info* shadow) {

    f32 alph = shadow->unk1C * shadow->unk18 * actor->shape_info.shadow_alpha_change_rate * 0.75f;

    *scale = shadow->unk10 * shadow->unk14 * actor->shape_info.shadow_size_change_rate;

    if (shadow->kind == 1) {
        alph *= 0.7f;
    }
    *alpha = alph;
}

void mActorShadow_DrawActorShadow(ACTOR* actor, Shadow_Info* shadow, GAME_PLAY* play, int id, xyz_t ofs, f32 rad) {
    f32 x, y, z;
    f32 y_adjust;
    f32 scale;
    u8 alpha;
    u8 r, g, b;
    int scene;
    Gfx* texscroll;
    GRAPH* graph;
    GAME* game = (GAME*)play;

    scene = Save_Get(scene_no);

    mActorShadow_GetLastAlphaScale(&scale, &alpha, actor, shadow);
    graph = game->graph;
    _texture_z_light_fog_prim_shadow(graph);

    OPEN_DISP(graph);

    y_adjust = (scene == 19 || scene == 27 || scene == 28 || scene == 34)
                   ? 0.5f
                   : ((scene == 15 || scene == 16 || scene == 49) ? 0.6f : 2.0f);

    switch (actor->shape_info.force_shadow_position) {
        case 1:
            x = actor->shape_info.shadow_position->x + ofs.x;
            y = actor->shape_info.shadow_position->y + y_adjust + ofs.y;
            z = actor->shape_info.shadow_position->z + ofs.z;
            Matrix_translate(x, y, z, MTX_LOAD);
            break;
        default:
            x = shadow->position.x + ofs.x;
            y = shadow->groundY + y_adjust + ofs.y;
            z = shadow->position.z + ofs.z;
            Matrix_translate(x, y, z, MTX_LOAD);
            break;
    }

    switch (actor->shape_info.force_shadow_position) {
        case 1:
            Matrix_RotateZ(0, MTX_MULT);
            Matrix_RotateX(0, MTX_MULT);
            break;
        default:
            Matrix_RotateZ(shadow->unk24, MTX_MULT);
            Matrix_RotateX(shadow->unk20, MTX_MULT);
            break;
    }

    if ((shadow->kind == 0) && (id == 0)) {
        Matrix_RotateY(shadow->unk26, MTX_MULT);
    }

    switch (id) {
        case 1:
            Matrix_scale(shadow->unk10, shadow->unk10, rad, MTX_MULT);
            break;
        default:
            switch (actor->shape_info.force_shadow_position) {
                case 1:
                    Matrix_scale(shadow->unk10, shadow->unk10, shadow->unk10, MTX_MULT);
                    break;
                default:
                    Matrix_scale(scale, scale, scale, MTX_MULT);
                    break;
            }
            break;
    }

    gSPMatrix(NEXT_SHADOW_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    mEnv_GetShadowPrimColor_Light(&r, &g, &b, game);
    gDPSetPrimColor(NEXT_SHADOW_DISP, 0, 0xFF, r, g, b, (u8)alpha);

    if ((shadow->kind == 0) && (id == 0)) {
        texscroll = mActorShadow_SetTexScroll(actor, shadow, game);
        if (texscroll != NULL) {
            gSPSegment(NEXT_SHADOW_DISP, 0x08, texscroll);
            gSPDisplayList(NEXT_SHADOW_DISP, ef_shadow_out_modelT);
        }
    } else {
        gSPDisplayList(NEXT_SHADOW_DISP, ef_shadow_in_modelT);
    }

    CLOSE_DISP(graph);
}

void mActorShadow_GetShadowPosition(ACTOR* actor, xyz_t* position) {

    if (actor->shape_info.shadow_position != NULL) {
        *position = *actor->shape_info.shadow_position;
    } else {
        *position = actor->world.position;
    }
}

int mActorShadow_GetShadowKind(void) {
    if (!(mFI_GetFieldId() & 0xF000)) {
        return 0;
    } else {
        return 1;
    }
}

f32 mAc_GetShadowGroundY_NoneForce(const Shadow_Info* shadow) {
    f32 res = mCoBG_GetShadowBgY_AngleS_FromWpos(NULL, shadow->position, 0.0f);
    return res;
}

f32 mAc_GetShadowGroundY_Force(const Shadow_Info* shadow) {
    return mCoBG_GetBgY_OnlyCenter_FromWpos2(shadow->position, 0.0f);
}

void mAc_DecideShadowRadius_IamNotFish(Shadow_Info* shadow, ACTOR* actor, f32* radius) {
    mActorShadow_RadiusScaleRate(actor, shadow);
    *radius = 0.01f;
}

void mAc_DecideShadowRadius_IamFish(Shadow_Info* shadow, ACTOR* actor, f32* radius) {
    shadow->unk10 = (actor->shape_info.shadow_size_x / 19.0f) * 0.018f;
    *radius = (actor->shape_info.shadow_size_z / 19.0f) * 0.018f;
}

void mAc_ActorShadowDraw_ShadowDrawFlagOff(ACTOR* actor, GAME_PLAY* play, int arg2, xyz_t arg3, f32 arg6) {
}

void mAc_ActorShadowDraw_ShadowDrawFlagOn(ACTOR* actor, GAME_PLAY* play, int proc, xyz_t pos, f32 rate) {
    static void (*set_raius_proc[])(Shadow_Info*, ACTOR*, f32*) = {
        mAc_DecideShadowRadius_IamNotFish,
        mAc_DecideShadowRadius_IamFish,
    };
    static f32 (*get_ground_y_proc[])(const Shadow_Info*) = {
        mAc_GetShadowGroundY_NoneForce,
        mAc_GetShadowGroundY_Force,
    };

    Shadow_Info shadow;
    f32 rad = 0.01f;
    u8 ground_y_proc;
    bzero(&shadow, sizeof(Shadow_Info));

    shadow.kind = mActorShadow_GetShadowKind();
    mActorShadow_GetShadowPosition(actor, &shadow.position);
    mActorShadow_AdjustRate(&actor->shape_info.shadow_size_change_rate);
    mActorShadow_AdjustRate(&actor->shape_info.shadow_alpha_change_rate);

    ground_y_proc = actor->shape_info.force_shadow_position & 1;
    shadow.groundY = get_ground_y_proc[ground_y_proc](&shadow);

    mActorShadow_GetTimeAngleY_TimeAlpha(&shadow, play);
    mActorShadow_GetGroundAverageAngle(&shadow);
    mActorShadow_GetDistanceRate(&shadow, rate);
    set_raius_proc[proc & 1](&shadow, actor, &rad);
    mActorShadow_GetShadowTopPos_GetSlideS(&shadow);
    mActorShadow_DrawActorShadow(actor, &shadow, play, proc, pos, rad);
    actor->shape_info.force_shadow_position = 0;
}

void mAc_ActorShadowDraw(ACTOR* actor, GAME_PLAY* play, int arg2, xyz_t arg3, f32 arg6) {

    static void (*shadwo_draw_proc[])(ACTOR* actor, GAME_PLAY* play, int arg2, xyz_t arg3, f32 arg6) = {
        mAc_ActorShadowDraw_ShadowDrawFlagOff,
        mAc_ActorShadowDraw_ShadowDrawFlagOn,
    };

    if (actor->id == 0x4A) {
        mActorShadow_UnSetForceShadowPos(actor);
        actor->shape_info.shadow_position = &actor->world.position;
    }

    shadwo_draw_proc[actor->shape_info.draw_shadow & 1](actor, play, arg2, arg3, arg6);
    actor->shape_info.shadow_position = &actor->world.position;
}

xyz_t mActorShadow_offset0 = { 0.0f, 0.0f, 0.0f };

void mActorShadow_SetForceShadowPos(ACTOR* actor, xyz_t* pos) {
    actor->shape_info.force_shadow_position = 1;
    actor->shape_info.shadow_position = pos;
}

void mActorShadow_UnSetForceShadowPos(ACTOR* actor) {
    actor->shape_info.force_shadow_position = 0;
    actor->shape_info.shadow_position = &actor->world.position;
}

void mAc_NormalActorShadow(ACTOR* actor, GAME_PLAY* play, f32 rad) {
    mAc_ActorShadowDraw(actor, play, 0, mActorShadow_offset0, rad);
}

void mAc_UnagiActorShadow(ACTOR* actor, GAME* game, xyz_t pos) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    
    mAc_ActorShadowDraw(actor, play, 1, pos, 1.0f);
}

void mAc_ActorShadowCircle(ACTOR* actor, LightsN* lights, GAME_PLAY* play) {
    mAc_ActorShadowDraw(actor, play, 0, mActorShadow_offset0, 1.0f);
}

void mAc_ActorShadowEllipse(ACTOR* actor, LightsN* lights, GAME_PLAY* play) {

    static xyz_t tunekiti_offset = { 0.0f, 1.0f, 0.0f };

    if (actor->id == 0x79) {
        mAc_ActorShadowDraw(actor, play, 0, tunekiti_offset, 1.0f);

    } else {
        mAc_ActorShadowDraw(actor, play, 0, mActorShadow_offset0, 1.0f);
    }
}
