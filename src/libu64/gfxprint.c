#include "libu64/gfxprint.h"

#include "libultra/libultra.h"
#include "libc64/aprintf.h"

static u8 __gfxprint_default_flags;

static void gfxprint_setup(gfxprint_t* this) {
  int i;
  int tile;

  /* Initialize RDP & RSP settings */
  gDPPipeSync(this->glistp++);
  gDPSetOtherMode(this->glistp++,
                  G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT |
                      G_TF_BILERP | G_TT_IA16 | G_TL_TILE | G_TD_CLAMP |
                      G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                  G_RM_XLU_SURF | G_RM_XLU_SURF2 | G_ZS_PRIM);
  gDPSetCombineMode(this->glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);

  /* Initialize font texture */
  gDPLoadTextureBlock_4b(this->glistp++, gfxprint_font, G_IM_FMT_CI, 16, 256, 0,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                         0, 0, 0, 0);

  /* Load font palette */
  gDPLoadTLUT_palX(this->glistp++, 0, gfxprint_moji_tlut, 64);

  /* Initialize tile settings */
  for (i = 0, tile = 1; i < 3; i++, tile++) {
    gDPSetTile(this->glistp++, G_IM_FMT_CI, G_IM_SIZ_4b,
               ((((16) >> 1) + 7) >> 3), 0, tile * 2, tile,
               G_TX_NOMIRROR | G_TX_CLAMP, 0, 0, G_TX_NOMIRROR | G_TX_CLAMP, 0,
               0);
    gDPSetTileSize(this->glistp++, tile * 2, 0, 0,
                   (16 - 1) << G_TEXTURE_IMAGE_FRAC,
                   (256 - 1) << G_TEXTURE_IMAGE_FRAC);
  }

  /* Initialize font color */
  gDPSetColor(this->glistp++, G_SETPRIMCOLOR, this->color.rgba8888);
}

extern void gfxprint_color(gfxprint_t* this, u32 r, u32 g, u32 b, u32 a) {
  this->color.c.r = r;
  this->color.c.g = g;
  this->color.c.b = b;
  this->color.c.a = a;

  gDPPipeSync(this->glistp++);
  gDPSetColor(this->glistp++, G_SETPRIMCOLOR, this->color.rgba8888);
}

extern void gfxprint_locate(gfxprint_t* this, int x, int y) {
  this->position_x = this->offset_x + x * 4;
  this->position_y = this->offset_y + y * 4;
}

extern void gfxprint_locate8x8(struct gfxprint_obj* this, int x, int y) {
  gfxprint_locate(this, x * 8, y * 8);
}

static void gfxprint_putc1(gfxprint_t* this, char c) {
  int tile;
  int x0;
  int x1;

  tile = (c & 3) * 2;
  x0 = (c & 4) * 2;
  x1 = c & 0xF8;

  if (gfxprint_isChanged(this)) {
    gfxprint_clrChanged(this);
    gDPPipeSync(this->glistp++);
    gDPSetTextureLUT(this->glistp++, G_TT_IA16);
    gDPSetCycleType(this->glistp++, G_CYC_1CYCLE);
    gDPSetRenderMode(this->glistp++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineMode(this->glistp++, G_CC_MODULATEIDECALA_PRIM,
                      G_CC_MODULATEIDECALA_PRIM);
  }

  if (gfxprint_isShadow(this)) {
    gDPSetColor(this->glistp++, G_SETPRIMCOLOR, 0);
    if (gfxprint_isHighres(this)) {
      gSPTextureRectangle(
          this->glistp++, (this->position_x + 4) << 1,
          (this->position_y + 4) << 1, (this->position_x + 32) << 1,
          (this->position_y + 32) << 1, tile, x0 << 5, x1 << 5, 512, 512);
    } else {
      gSPTextureRectangle(this->glistp++, this->position_x + 4,
                          this->position_y + 4, this->position_x + 32,
                          this->position_y + 32, tile, x0 << 5, x1 << 5, 1024,
                          1024);
    }
    gDPSetColor(this->glistp++, G_SETPRIMCOLOR, this->color.rgba8888);
  }

  if (gfxprint_isHighres(this)) {
    gSPTextureRectangle(this->glistp++, this->position_x << 1,
                        this->position_y << 1, (this->position_x + 28) << 1,
                        (this->position_y + 28) << 1, tile, x0 << 5, x1 << 5,
                        512, 512);
  } else {
    gSPTextureRectangle(this->glistp++, this->position_x, this->position_y,
                        this->position_x + 28, this->position_y + 28, tile,
                        x0 << 5, x1 << 5, 1024, 1024);
  }

  this->position_x += 32;
}

extern void gfxprint_putc(gfxprint_t* this, char c) {
  u8 param = c;

  if (param == ' ') {
    this->position_x += 32;
  } else if (param > ' ' && param <= 0x7E) {
    gfxprint_putc1(this, param);
  } else if (param >= 0xA0 && param <= 0xDF) {
    if (gfxprint_isHiragana(this)) {
      if (param <= 0xBF) {
        param -= 0x20;
      } else {
        param += 0x20;
      }
    }

    gfxprint_putc1(this, param);
  } else {
    switch (param) {
      case '\0':
        break;
      case '\n':
        this->position_y += 32;
#pragma fallthrough
      case '\r':
        this->position_x = this->offset_x;
        break;
      case '\t':
        do {
          gfxprint_putc1(this, ' ');
        } while ((this->position_x - this->offset_x) % 256);
        break;
      case '\x8D':
        gfxprint_setHiragana(this);
        break;
      case '\x8C':
        gfxprint_setKatakana(this);
        break;
      case '\x8B':
        gfxprint_setGradient(this);
        gfxprint_setChanged(this);
        break;
      case '\x8A':
        gfxprint_clrGradient(this);
        gfxprint_setChanged(this);
        break;
      case '\x8E':
        break;
      default:
        break;
    }
  }
}

extern void gfxprint_write(gfxprint_t* this, const void* buffer, size_t size,
                           size_t n) {
  char* buf = (char*)buffer;
  size_t i;

  for (i = size * n; i != 0; i--) {
    gfxprint_putc(this, *buf++);
  }
}

static void* gfxprint_prout(void* this, const char* buffer, int n) {
  gfxprint_write((gfxprint_t*)this, buffer, sizeof(char), (size_t)n);
  return this;
}

extern void gfxprint_init(gfxprint_t* this) {
  gfxprint_clrOpened(this);
  this->prout_func = &gfxprint_prout;
  this->glistp = NULL;
  this->position_x = 0;
  this->position_y = 0;
  this->offset_x = 0;
  this->offset_y = 0;
  this->color.rgba8888 = 0;
  gfxprint_setKatakana(this);
  gfxprint_clrGradient(this);
  gfxprint_setShadow(this);
  gfxprint_setChanged(this);

  if ((__gfxprint_default_flags & GFXPRINT_FLAG_HIGHRES) != 0) {
    gfxprint_setHighres(this);
  } else {
    gfxprint_clrHighres(this);
  }
}

extern void gfxprint_cleanup(gfxprint_t* this) {}

extern void gfxprint_open(gfxprint_t* this, Gfx* glistp) {
  if (!gfxprint_isOpened(this)) {
    gfxprint_setOpened(this);
    this->glistp = glistp;
    gfxprint_setup(this);
  } else {
    osSyncPrintf("gfxprint_open:２重オープンです\n");
  }
}

extern Gfx* gfxprint_close(gfxprint_t* this) {
  Gfx* list;

  gfxprint_clrOpened(this);
  gDPPipeSync(this->glistp++);
  list = this->glistp;
  this->glistp = NULL;
  return list;
}

extern int gfxprint_vprintf(gfxprint_t* this, const char* fmt, va_list ap) {
  return vaprintf((aprout_func_t*)&this->prout_func, fmt, ap);
}

extern int gfxprint_printf(gfxprint_t* this, const char* fmt, ...) {
  int res;

  va_list ap;
  va_start(ap, fmt);
  res = gfxprint_vprintf(this, fmt, ap);
  va_end(ap);

  return res;
}
