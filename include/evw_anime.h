#ifndef EVW_ANIME_H
#define EVW_ANIME_H

#include "types.h"
#include "m_play_h.h"

#ifdef __cplusplus
extern "C"{
#endif

#define EVW_COLOR_BUF_MAX 50

enum {
  EVW_ANIME_TYPE_SCROLL1,
  EVW_ANIME_TYPE_SCROLL2,
  EVW_ANIME_TYPE_COLREG_MANUAL,
  EVW_ANIME_TYPE_COLREG_LINEAR,
  EVW_ANIME_TYPE_COLREG_NONLINEAR,
  EVW_ANIME_TYPE_TEXANIME,

  EVW_ANIME_TYPE_NUM
};

typedef struct evw_anime_col_prim_s {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
  u8 l;
} EVW_ANIME_COL_PRIM;

typedef struct evw_anime_col_env_s {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} EVW_ANIME_COL_ENV;

typedef struct evw_anime_col_reg_s {
  u16 frame_count; /* total frames in the animation */
  u16 key_count; /* number of animation keyframes */

  EVW_ANIME_COL_PRIM* prim_colors; /* list of primitive colors per-keyframe */
  EVW_ANIME_COL_ENV* env_colors; /* list of environment colors per-keyframe */

  u16* keyframes; /* list of keyframe frame indices */
} EVW_ANIME_COLREG;

typedef struct evw_anime_scroll_s {
  s8 x; /* x (s) texture position */
  s8 y; /* y (t) texture position */
  u8 width; /* texture width */
  u8 height; /* texture height */
} EVW_ANIME_SCROLL;

typedef struct evw_anime_texanime_s {
  u16 frame_count; /* total frames in the animation */
  u16 key_count; /* number of animation keyframes */

  void** texture_tbl; /* list of each texture */
  u8* animation_pattern; /* list of which texture to use per keyframe (runs at 30 FPS) */

  u16* keyframes; /* list of keyframe frame indices */
} EVW_ANIME_TEXANIME;

typedef struct evw_anime_s {
  s8 segment; /* Negative segments signal the end of the animation data array */
  s16 type;
  void* data_p;
} EVW_ANIME_DATA;

extern void Evw_Anime_Set(GAME_PLAY* play, EVW_ANIME_DATA* evw_anime_data);

#ifdef __cplusplus
}
#endif

#endif