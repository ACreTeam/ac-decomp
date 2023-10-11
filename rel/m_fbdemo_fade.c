#include "m_fbdemo_fade.h"

#include "libultra/gu.h"
#include "libultra/libultra.h"
#include "m_common_data.h"

Gfx fbdemo_fade_gfx_init[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG |
                          G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                          G_LOD | G_SHADING_SMOOTH),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT |
                         G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP |
                         G_TP_NONE | G_CYC_1CYCLE | G_PM_1PRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsSPEndDisplayList(),
};

fbdemo_fade* fbdemo_fade_init(fbdemo_fade* this) {
  bzero(this, sizeof(fbdemo_fade));
  return this;
}

void fbdemo_fade_move(fbdemo_fade* this, int rate) {
  f32 ftimer;
  int alpha;

  if (this->timer != 0) {
    this->timer -= 1;
    return;
  }

  if (this->type != 7) {
    this->frame += rate;
    if (this->frame >= Common_Get(transition).fade_rate) {
      this->frame = Common_Get(transition).fade_rate;
      this->isDone = 1;
    }
    ftimer = (f32)this->frame;
    if (ftimer < 0.0f) {
      ftimer = 0.0f;
    }

    alpha = (255.0f * ftimer) / Common_Get(transition).fade_rate;
    if (this->type == 1) {
      this->color.a = 255 - alpha;
    } else {
      this->color.a = alpha;
    }
  }
}

void fbdemo_fade_draw(fbdemo_fade* this, Gfx** gfxP) {
  Gfx* gfx;
  if (this->color.a != 0) {
    gfx = *gfxP;
    gSPDisplayList(gfx++, fbdemo_fade_gfx_init);
    gDPSetPrimColor(gfx++, 0, 0, this->color.r, this->color.g, this->color.b,
                    this->color.a);
    gDPFillRectangle(gfx++, 0, 0, N64_SCREEN_WIDTH * 2, N64_SCREEN_HEIGHT * 2);
    gDPPipeSync(gfx++);
    *gfxP = gfx;
  }
}

void fbdemo_fade_startup(fbdemo_fade* this) {
  static s8 start_frame[] = {0x00, 0xFA, 0x00, 0x00, 0x00, 0x00, 0xAB, 0x00,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  static u8 start_color[] = {0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  this->color.a = start_color[this->type];
  this->frame = start_frame[this->type];
  this->isDone = 0;
  if (this->type == 1) {
    this->timer = 10;
  }
}

void fbdemo_fade_settype(fbdemo_fade* this, int type) { this->type = type; }

void fbdemo_fade_setcolor_rgba8888(fbdemo_fade* this, u32 color) {
  this->color.rgba = color;
}

u8 fbdemo_fade_is_finish(fbdemo_fade* this) { return this->isDone; }