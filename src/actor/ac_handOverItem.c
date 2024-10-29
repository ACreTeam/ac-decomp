#include "ac_handOverItem.h"

#include "libultra/libultra.h"
#include "m_common_data.h"
#include "m_demo.h"
#include "m_msg.h"
#include "m_name_table.h"
#include "m_player_lib.h"
#include "m_rcp.h"
#include "sys_matrix.h"

enum {
  aHOI_ITEM_TYPE_ITEM,
  aHOI_ITEM_TYPE_FISH,
  aHOI_ITEM_TYPE_MAIL,

  aHOI_ITEM_TYPE_NUM
};

static void aHOI_actor_ct(ACTOR*, GAME*);
static void aHOI_actor_dt(ACTOR*, GAME*);
static void aHOI_actor_move(ACTOR*, GAME*);
static void aHOI_actor_draw(ACTOR*, GAME*);

ACTOR_PROFILE HandOverItem_Profile = {
  mAc_PROFILE_HANDOVERITEM,
  ACTOR_PART_BG,
  ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
  EMPTY_NO,
  ACTOR_OBJ_BANK_KEEP,
  sizeof(HANDOVERITEM_ACTOR),
  &aHOI_actor_ct,
  &aHOI_actor_dt,
  &aHOI_actor_move,
  &aHOI_actor_draw,
  NULL
};

static aHOI_Clip_c aHOI_clip;

typedef struct gyo_model_s {
  Gfx* dl_a;
  Gfx* dl_b;
  Gfx* dl_c;
} aHOI_GYO_DL_c;

extern Gfx act_f01_funa_aT_model[];
extern Gfx act_f01_funa_bT_model[];
extern Gfx act_f01_funa_cT_model[];
extern Gfx act_f02_hera_aT_model[];
extern Gfx act_f02_hera_bT_model[];
extern Gfx act_f02_hera_cT_model[];
extern Gfx act_f03_koi_aT_model[];
extern Gfx act_f03_koi_bT_model[];
extern Gfx act_f03_koi_cT_model[];
extern Gfx act_f04_nisiki_aT_model[];
extern Gfx act_f04_nisiki_bT_model[];
extern Gfx act_f04_nisiki_cT_model[];
extern Gfx act_f05_namazu_aT_model[];
extern Gfx act_f05_namazu_bT_model[];
extern Gfx act_f05_namazu_cT_model[];
extern Gfx act_f06_bass_aT_model[];
extern Gfx act_f06_bass_bT_model[];
extern Gfx act_f06_bass_cT_model[];
extern Gfx act_f07_bassm_aT_model[];
extern Gfx act_f07_bassm_bT_model[];
extern Gfx act_f07_bassm_cT_model[];
extern Gfx act_f08_bassl_aT_model[];
extern Gfx act_f08_bassl_bT_model[];
extern Gfx act_f08_bassl_cT_model[];
extern Gfx act_f09_gill_aT_model[];
extern Gfx act_f09_gill_bT_model[];
extern Gfx act_f09_gill_cT_model[];
extern Gfx act_f10_oonamazu_aT_model[];
extern Gfx act_f10_oonamazu_bT_model[];
extern Gfx act_f10_oonamazu_cT_model[];
extern Gfx act_f11_raigyo_aT_model[];
extern Gfx act_f11_raigyo_bT_model[];
extern Gfx act_f11_raigyo_cT_model[];
extern Gfx act_f12_nigoi_aT_model[];
extern Gfx act_f12_nigoi_bT_model[];
extern Gfx act_f12_nigoi_cT_model[];
extern Gfx act_f13_ugui_aT_model[];
extern Gfx act_f13_ugui_bT_model[];
extern Gfx act_f13_ugui_cT_model[];
extern Gfx act_f14_oikawa_aT_model[];
extern Gfx act_f14_oikawa_bT_model[];
extern Gfx act_f14_oikawa_cT_model[];
extern Gfx act_f15_tanago_aT_model[];
extern Gfx act_f15_tanago_bT_model[];
extern Gfx act_f15_tanago_cT_model[];
extern Gfx act_f16_dojyo_aT_model[];
extern Gfx act_f16_dojyo_bT_model[];
extern Gfx act_f16_dojyo_cT_model[];
extern Gfx act_f17_wakasagi_aT_model[];
extern Gfx act_f17_wakasagi_bT_model[];
extern Gfx act_f17_wakasagi_cT_model[];
extern Gfx act_f18_ayu_aT_model[];
extern Gfx act_f18_ayu_bT_model[];
extern Gfx act_f18_ayu_cT_model[];
extern Gfx act_f19_yamame_aT_model[];
extern Gfx act_f19_yamame_bT_model[];
extern Gfx act_f19_yamame_cT_model[];
extern Gfx act_f20_iwana_aT_model[];
extern Gfx act_f20_iwana_bT_model[];
extern Gfx act_f20_iwana_cT_model[];
extern Gfx act_f21_niji_aT_model[];
extern Gfx act_f21_niji_bT_model[];
extern Gfx act_f21_niji_cT_model[];
extern Gfx act_f22_ito_aT_model[];
extern Gfx act_f22_ito_bT_model[];
extern Gfx act_f22_ito_cT_model[];
extern Gfx act_f23_sake_aT_model[];
extern Gfx act_f23_sake_bT_model[];
extern Gfx act_f23_sake_cT_model[];
extern Gfx act_f24_kingyo_aT_model[];
extern Gfx act_f24_kingyo_bT_model[];
extern Gfx act_f24_kingyo_cT_model[];
extern Gfx act_f25_pirania_aT_model[];
extern Gfx act_f25_pirania_bT_model[];
extern Gfx act_f25_pirania_cT_model[];
extern Gfx act_f26_aroana_aT_model[];
extern Gfx act_f26_aroana_bT_model[];
extern Gfx act_f26_aroana_cT_model[];
extern Gfx act_f27_unagi_aT_model[];
extern Gfx act_f27_unagi_bT_model[];
extern Gfx act_f27_unagi_cT_model[];
extern Gfx act_f28_donko_aT_model[];
extern Gfx act_f28_donko_bT_model[];
extern Gfx act_f28_donko_cT_model[];
extern Gfx act_f29_angel_aT_model[];
extern Gfx act_f29_angel_bT_model[];
extern Gfx act_f29_angel_cT_model[];
extern Gfx act_f30_gupi_aT_model[];
extern Gfx act_f30_gupi_bT_model[];
extern Gfx act_f30_gupi_cT_model[];
extern Gfx act_f31_demekin_aT_model[];
extern Gfx act_f31_demekin_bT_model[];
extern Gfx act_f31_demekin_cT_model[];
extern Gfx act_f32_kaseki_aT_model[];
extern Gfx act_f32_kasekiT_model[];
extern Gfx act_f32_kaseki_cT_model[];
extern Gfx act_f35_zarigani_aT_model[];
extern Gfx act_f35_zarigani_bT_model[];
extern Gfx act_f35_zarigani_cT_model[];
extern Gfx act_f36_kaeru_aT_model[];
extern Gfx act_f36_kaeru_bT_model[];
extern Gfx act_f36_kaeru_cT_model[];
extern Gfx act_f33_medaka_aT_model[];
extern Gfx act_f33_medaka_bT_model[];
extern Gfx act_f33_medaka_cT_model[];
extern Gfx act_f37_kurage_aT_model[];
extern Gfx act_f37_kurage_bT_model[];
extern Gfx act_f37_kurage_cT_model[];
extern Gfx act_f38_suzuki_aT_model[];
extern Gfx act_f38_suzuki_bT_model[];
extern Gfx act_f38_suzuki_cT_model[];
extern Gfx act_f39_tai_aT_model[];
extern Gfx act_f39_tai_bT_model[];
extern Gfx act_f39_tai_cT_model[];
extern Gfx act_f40_isidai_aT_model[];
extern Gfx act_f40_isidai_bT_model[];
extern Gfx act_f40_isidai_cT_model[];
extern Gfx act_f34_piraluku_aT_model[];
extern Gfx act_f34_piraluku_bT_model[];
extern Gfx act_f34_piraluku_cT_model[];
extern Gfx act_f28_akikanT_model[];
extern Gfx act_f28_akikanT_model[];
extern Gfx act_f28_akikanT_model[];
extern Gfx act_f30_nagagutuT_model[];
extern Gfx act_f30_nagagutuT_model[];
extern Gfx act_f30_nagagutuT_model[];
extern Gfx act_f29_petT_model[];
extern Gfx act_f29_petT_model[];
extern Gfx act_f29_petT_model[];

static aHOI_GYO_DL_c aGYO_funa_dl = {
  act_f01_funa_aT_model,
  act_f01_funa_bT_model,
  act_f01_funa_cT_model,
};
static aHOI_GYO_DL_c aGYO_hera_dl = {
  act_f02_hera_aT_model,
  act_f02_hera_bT_model,
  act_f02_hera_cT_model,
};
static aHOI_GYO_DL_c aGYO_koi_dl = {
  act_f03_koi_aT_model,
  act_f03_koi_bT_model,
  act_f03_koi_cT_model,
};
static aHOI_GYO_DL_c aGYO_nisiki_dl = {
  act_f04_nisiki_aT_model,
  act_f04_nisiki_bT_model,
  act_f04_nisiki_cT_model,
};
static aHOI_GYO_DL_c aGYO_namazu_dl = {
  act_f05_namazu_aT_model,
  act_f05_namazu_bT_model,
  act_f05_namazu_cT_model,
};
static aHOI_GYO_DL_c aGYO_bass_s_dl = {
  act_f06_bass_aT_model,
  act_f06_bass_bT_model,
  act_f06_bass_cT_model,
};
static aHOI_GYO_DL_c aGYO_bass_m_dl = {
  act_f07_bassm_aT_model,
  act_f07_bassm_bT_model,
  act_f07_bassm_cT_model,
};
static aHOI_GYO_DL_c aGYO_bass_l_dl = {
  act_f08_bassl_aT_model,
  act_f08_bassl_bT_model,
  act_f08_bassl_cT_model,
};
static aHOI_GYO_DL_c aGYO_blue_gill_dl = {
  act_f09_gill_aT_model,
  act_f09_gill_bT_model,
  act_f09_gill_cT_model,
};
static aHOI_GYO_DL_c aGYO_oonamazu_dl = {
  act_f10_oonamazu_aT_model,
  act_f10_oonamazu_bT_model,
  act_f10_oonamazu_cT_model,
};
static aHOI_GYO_DL_c aGYO_raigyo_dl = {
  act_f11_raigyo_aT_model,
  act_f11_raigyo_bT_model,
  act_f11_raigyo_cT_model,
};
static aHOI_GYO_DL_c aGYO_nigoi_dl = {
  act_f12_nigoi_aT_model,
  act_f12_nigoi_bT_model,
  act_f12_nigoi_cT_model,
};
static aHOI_GYO_DL_c aGYO_ugui_dl = {
  act_f13_ugui_aT_model,
  act_f13_ugui_bT_model,
  act_f13_ugui_cT_model,
};
static aHOI_GYO_DL_c aGYO_oikawa_dl = {
  act_f14_oikawa_aT_model,
  act_f14_oikawa_bT_model,
  act_f14_oikawa_cT_model,
};
static aHOI_GYO_DL_c aGYO_tanago_dl = {
  act_f15_tanago_aT_model,
  act_f15_tanago_bT_model,
  act_f15_tanago_cT_model,
};
static aHOI_GYO_DL_c aGYO_dojyo_dl = {
  act_f16_dojyo_aT_model,
  act_f16_dojyo_bT_model,
  act_f16_dojyo_cT_model,
};
static aHOI_GYO_DL_c aGYO_wakasagi_dl = {
  act_f17_wakasagi_aT_model,
  act_f17_wakasagi_bT_model,
  act_f17_wakasagi_cT_model,
};
static aHOI_GYO_DL_c aGYO_ayu_dl = {
  act_f18_ayu_aT_model,
  act_f18_ayu_bT_model,
  act_f18_ayu_cT_model,
};
static aHOI_GYO_DL_c aGYO_yamame_dl = {
  act_f19_yamame_aT_model,
  act_f19_yamame_bT_model,
  act_f19_yamame_cT_model,
};
static aHOI_GYO_DL_c aGYO_iwana_dl = {
  act_f20_iwana_aT_model,
  act_f20_iwana_bT_model,
  act_f20_iwana_cT_model,
};
static aHOI_GYO_DL_c aGYO_niji_dl = {
  act_f21_niji_aT_model,
  act_f21_niji_bT_model,
  act_f21_niji_cT_model,
};
static aHOI_GYO_DL_c aGYO_ito_dl = {
  act_f22_ito_aT_model,
  act_f22_ito_bT_model,
  act_f22_ito_cT_model,
};
static aHOI_GYO_DL_c aGYO_sake_dl = {
  act_f23_sake_aT_model,
  act_f23_sake_bT_model,
  act_f23_sake_cT_model,
};
static aHOI_GYO_DL_c aGYO_kingyo_dl = {
  act_f24_kingyo_aT_model,
  act_f24_kingyo_bT_model,
  act_f24_kingyo_cT_model,
};
static aHOI_GYO_DL_c aGYO_pirania_dl = {
  act_f25_pirania_aT_model,
  act_f25_pirania_bT_model,
  act_f25_pirania_cT_model,
};
static aHOI_GYO_DL_c aGYO_aroana_dl = {
  act_f26_aroana_aT_model,
  act_f26_aroana_bT_model,
  act_f26_aroana_cT_model,
};
static aHOI_GYO_DL_c aGYO_unagi_dl = {
  act_f27_unagi_aT_model,
  act_f27_unagi_bT_model,
  act_f27_unagi_cT_model,
};
static aHOI_GYO_DL_c aGYO_donko_dl = {
  act_f28_donko_aT_model,
  act_f28_donko_bT_model,
  act_f28_donko_cT_model,
};
static aHOI_GYO_DL_c aGYO_angel_dl = {
  act_f29_angel_aT_model,
  act_f29_angel_bT_model,
  act_f29_angel_cT_model,
};
static aHOI_GYO_DL_c aGYO_gupi_dl = {
  act_f30_gupi_aT_model,
  act_f30_gupi_bT_model,
  act_f30_gupi_cT_model,
};
static aHOI_GYO_DL_c aGYO_demekin_dl = {
  act_f31_demekin_aT_model,
  act_f31_demekin_bT_model,
  act_f31_demekin_cT_model,
};
static aHOI_GYO_DL_c aGYO_kaseki_dl = {
  act_f32_kaseki_aT_model,
  act_f32_kasekiT_model,
  act_f32_kaseki_cT_model,
};
static aHOI_GYO_DL_c aGYO_zarigani_dl = {
  act_f35_zarigani_aT_model,
  act_f35_zarigani_bT_model,
  act_f35_zarigani_cT_model,
};
static aHOI_GYO_DL_c aGYO_kaeru_dl = {
  act_f36_kaeru_aT_model,
  act_f36_kaeru_bT_model,
  act_f36_kaeru_cT_model,
};
static aHOI_GYO_DL_c aGYO_medaka_dl = {
  act_f33_medaka_aT_model,
  act_f33_medaka_bT_model,
  act_f33_medaka_cT_model,
};
static aHOI_GYO_DL_c aGYO_kurage_dl = {
  act_f37_kurage_aT_model,
  act_f37_kurage_bT_model,
  act_f37_kurage_cT_model,
};
static aHOI_GYO_DL_c aGYO_suzuki_dl = {
  act_f38_suzuki_aT_model,
  act_f38_suzuki_bT_model,
  act_f38_suzuki_cT_model,
};
static aHOI_GYO_DL_c aGYO_tai_dl = {
  act_f39_tai_aT_model,
  act_f39_tai_bT_model,
  act_f39_tai_cT_model,
};
static aHOI_GYO_DL_c aGYO_ishidai_dl = {
  act_f40_isidai_aT_model,
  act_f40_isidai_bT_model,
  act_f40_isidai_cT_model,
};
static aHOI_GYO_DL_c aGYO_piraluku_dl = {
  act_f34_piraluku_aT_model,
  act_f34_piraluku_bT_model,
  act_f34_piraluku_cT_model,
};
static aHOI_GYO_DL_c aGYO_akikan_dl = {
  act_f28_akikanT_model,
  act_f28_akikanT_model,
  act_f28_akikanT_model,
};
static aHOI_GYO_DL_c aGYO_nagagutu_dl = {
  act_f30_nagagutuT_model,
  act_f30_nagagutuT_model,
  act_f30_nagagutuT_model,
};
static aHOI_GYO_DL_c aGYO_taiya_dl = {
  act_f29_petT_model,
  act_f29_petT_model,
  act_f29_petT_model,
};


static aHOI_GYO_DL_c* aGYO_displayList[45] = {
  &aGYO_funa_dl,
  &aGYO_hera_dl,
  &aGYO_koi_dl,
  &aGYO_nisiki_dl,
  &aGYO_namazu_dl,
  &aGYO_bass_s_dl,
  &aGYO_bass_m_dl,
  &aGYO_bass_l_dl,
  &aGYO_blue_gill_dl,
  &aGYO_oonamazu_dl,
  &aGYO_raigyo_dl,
  &aGYO_nigoi_dl,
  &aGYO_ugui_dl,
  &aGYO_oikawa_dl,
  &aGYO_tanago_dl,
  &aGYO_dojyo_dl,
  &aGYO_wakasagi_dl,
  &aGYO_ayu_dl,
  &aGYO_yamame_dl,
  &aGYO_iwana_dl,
  &aGYO_niji_dl,
  &aGYO_ito_dl,
  &aGYO_sake_dl,
  &aGYO_kingyo_dl,
  &aGYO_pirania_dl,
  &aGYO_aroana_dl,
  &aGYO_unagi_dl,
  &aGYO_donko_dl,
  &aGYO_angel_dl,
  &aGYO_gupi_dl,
  &aGYO_demekin_dl,
  &aGYO_kaseki_dl,
  &aGYO_zarigani_dl,
  &aGYO_kaeru_dl,
  &aGYO_medaka_dl,
  &aGYO_kurage_dl,
  &aGYO_suzuki_dl,
  &aGYO_tai_dl,
  &aGYO_ishidai_dl,
  &aGYO_piraluku_dl,
  &aGYO_piraluku_dl,
  &aGYO_akikan_dl,
  &aGYO_nagagutu_dl,
  &aGYO_taiya_dl,
  NULL
};

extern Gfx apple_DL_mode[];
extern Gfx orange_DL_mode[];
extern Gfx peach_DL_mode[];
extern Gfx pear_DL_mode[];
extern Gfx nuts_DL_mode[];
extern Gfx matutake_DL_mode[];
extern Gfx kabu_DL_mode[];
extern Gfx fish_DL_mode[];
extern Gfx bag_DL_mode[];
extern Gfx leaf_DL_mode[];
extern Gfx obj_rollT_mat_model[];
extern Gfx box_DL_mode[];
extern Gfx pack_DL_mode[];
extern Gfx present_DL_mode[];
extern Gfx seed_DL_mode[];
extern Gfx obj_haniwaT_mat_model[];
extern Gfx obj_boxT_mat_model[];
extern Gfx obj_cageT_mat_model[];
extern Gfx obj_toolT_mat_model[];
extern Gfx obj_fossilT_mat_model[];
extern Gfx obj_trashT_mat_model[];
extern Gfx obj_letterT_mat_model[];
extern Gfx obj_otosiT_mat_model[];
extern Gfx obj_item_shellAT_mat_model[];
extern Gfx obj_item_shellBT_mat_model[];
extern Gfx obj_item_shellCT_mat_model[];
extern Gfx obj_shop_candy_mat_modelT[];
extern Gfx obj_item_cocoT_mat_model[];
extern Gfx obj_item_omikuji_mat_model[];
extern Gfx obj_item_clothT_mat_model[];
extern Gfx obj_item_carpetT_mat_model[];
extern Gfx obj_item_wallT_mat_model[];
extern Gfx obj_item_axeT_mat_model[];
extern Gfx obj_item_netT_mat_model[];
extern Gfx obj_item_rodT_mat_model[];
extern Gfx obj_item_shovelT_mat_model[];
extern Gfx obj_item_axe2T_mat_model[];
extern Gfx obj_item_net2T_mat_model[];
extern Gfx obj_item_rod2T_mat_model[];
extern Gfx obj_item_shovel2T_mat_model[];
extern Gfx obj_item_umbrellaT_mat_model[];
extern Gfx obj_item_kazaT_mat_model[];
extern Gfx obj_item_utiwaT_mat_model[];
extern Gfx obj_item_paperT_mat_model[];
extern Gfx obj_item_seedT_mat_model[];
extern Gfx obj_item_fukuT_mat_model[];
extern Gfx obj_item_taisouT_mat_model[];
extern Gfx obj_mdT_mat_model[];
extern Gfx obj_item_ticketT_mat_model[];
extern Gfx obj_item_boneT_mat_model[];
extern Gfx obj_item_diaryT_mat_model[];
extern Gfx obj_item_fork_onT_mat_model[];

static Gfx* mode_DL_table[mNT_ITEM_TYPE_NUM] = {
  NULL,  
  apple_DL_mode,
  orange_DL_mode,
  peach_DL_mode,
  pear_DL_mode,
  nuts_DL_mode,
  matutake_DL_mode,
  kabu_DL_mode,
  fish_DL_mode,
  bag_DL_mode,
  leaf_DL_mode,
  obj_rollT_mat_model,
  box_DL_mode,
  pack_DL_mode,
  present_DL_mode,
  seed_DL_mode,
  obj_haniwaT_mat_model,
  obj_boxT_mat_model,
  obj_cageT_mat_model,
  obj_toolT_mat_model,
  obj_fossilT_mat_model,
  obj_trashT_mat_model,
  obj_letterT_mat_model,
  obj_otosiT_mat_model,
  obj_item_shellAT_mat_model,
  obj_item_shellBT_mat_model,
  obj_item_shellCT_mat_model,
  obj_shop_candy_mat_modelT,
  obj_item_cocoT_mat_model,
  obj_item_omikuji_mat_model,
  obj_item_clothT_mat_model,
  obj_item_carpetT_mat_model,
  obj_item_wallT_mat_model,
  obj_item_axeT_mat_model,
  obj_item_netT_mat_model,
  obj_item_rodT_mat_model,
  obj_item_shovelT_mat_model,
  obj_item_axe2T_mat_model,
  obj_item_net2T_mat_model,
  obj_item_rod2T_mat_model,
  obj_item_shovel2T_mat_model,
  obj_item_umbrellaT_mat_model,
  obj_item_kazaT_mat_model,
  obj_item_utiwaT_mat_model,
  obj_item_paperT_mat_model,
  obj_item_seedT_mat_model,
  obj_item_fukuT_mat_model,
  obj_item_taisouT_mat_model,
  obj_mdT_mat_model,
  obj_item_ticketT_mat_model,
  obj_item_boneT_mat_model,
  obj_item_diaryT_mat_model,
  obj_item_fork_onT_mat_model
};

extern Gfx apple_DL_vtx[];
extern Gfx orange_DL_vtx[];
extern Gfx peach_DL_vtx[];
extern Gfx pear_DL_vtx[];
extern Gfx nuts_DL_vtx[];
extern Gfx matutake_DL_vtx[];
extern Gfx kabu_DL_vtx[];
extern Gfx fish_DL_vtx[];
extern Gfx bag_DL_vtx[];
extern Gfx leaf_DL_vtx[];
extern Gfx obj_rollT_gfx_model[];
extern Gfx box_DL_vtx[];
extern Gfx pack_DL_vtx[];
extern Gfx present_DL_vtx[];
extern Gfx seed_DL_vtx[];
extern Gfx obj_haniwaT_gfx_model[];
extern Gfx obj_boxT_gfx_model[];
extern Gfx obj_cageT_gfx_model[];
extern Gfx obj_toolT_gfx_model[];
extern Gfx obj_fossilT_gfx_model[];
extern Gfx obj_trashT_gfx_model[];
extern Gfx obj_letterT_gfx_model[];
extern Gfx obj_otosiT_gfx_model[];
extern Gfx obj_item_shellAT_gfx_model[];
extern Gfx obj_item_shellBT_gfx_model[];
extern Gfx obj_item_shellCT_gfx_model[];
extern Gfx obj_shop_candy_gfx_modelT[];
extern Gfx obj_item_cocoT_gfx_model[];
extern Gfx obj_item_omikuji_gfx_model[];
extern Gfx obj_item_clothT_gfx_model[];
extern Gfx obj_item_carpetT_gfx_model[];
extern Gfx obj_item_wallT_gfx_model[];
extern Gfx obj_item_axeT_gfx_model[];
extern Gfx obj_item_netT_gfx_model[];
extern Gfx obj_item_rodT_gfx_model[];
extern Gfx obj_item_shovelT_gfx_model[];
extern Gfx obj_item_axe2T_gfx_model[];
extern Gfx obj_item_net2T_gfx_model[];
extern Gfx obj_item_rod2T_gfx_model[];
extern Gfx obj_item_shovel2T_gfx_model[];
extern Gfx obj_item_umbrellaT_gfx_model[];
extern Gfx obj_item_kazaT_gfx_model[];
extern Gfx obj_item_utiwaT_gfx_model[];
extern Gfx obj_item_paperT_gfx_model[];
extern Gfx obj_item_seedT_gfx_model[];
extern Gfx obj_item_fukuT_gfx_model[];
extern Gfx obj_item_taisouT_gfx_model[];
extern Gfx obj_mdT_gfx_model[];
extern Gfx obj_item_ticketT_gfx_model[];
extern Gfx obj_item_boneT_gfx_model[];
extern Gfx obj_item_diaryT_gfx_model[];
extern Gfx obj_item_fork_onT_gfx_model[];

static Gfx* vtx_DL_table[mNT_ITEM_TYPE_NUM] = {
  NULL, 
  apple_DL_vtx,
  orange_DL_vtx,
  peach_DL_vtx,
  pear_DL_vtx,
  nuts_DL_vtx,
  matutake_DL_vtx,
  kabu_DL_vtx,
  fish_DL_vtx,
  bag_DL_vtx,
  leaf_DL_vtx,
  obj_rollT_gfx_model,
  box_DL_vtx,
  pack_DL_vtx,
  present_DL_vtx,
  seed_DL_vtx,
  obj_haniwaT_gfx_model,
  obj_boxT_gfx_model,
  obj_cageT_gfx_model,
  obj_toolT_gfx_model,
  obj_fossilT_gfx_model,
  obj_trashT_gfx_model,
  obj_letterT_gfx_model,
  obj_otosiT_gfx_model,
  obj_item_shellAT_gfx_model,
  obj_item_shellBT_gfx_model,
  obj_item_shellCT_gfx_model,
  obj_shop_candy_gfx_modelT,
  obj_item_cocoT_gfx_model,
  obj_item_omikuji_gfx_model,
  obj_item_clothT_gfx_model,
  obj_item_carpetT_gfx_model,
  obj_item_wallT_gfx_model,
  obj_item_axeT_gfx_model,
  obj_item_netT_gfx_model,
  obj_item_rodT_gfx_model,
  obj_item_shovelT_gfx_model,
  obj_item_axe2T_gfx_model,
  obj_item_net2T_gfx_model,
  obj_item_rod2T_gfx_model,
  obj_item_shovel2T_gfx_model,
  obj_item_umbrellaT_gfx_model,
  obj_item_kazaT_gfx_model,
  obj_item_utiwaT_gfx_model,
  obj_item_paperT_gfx_model,
  obj_item_seedT_gfx_model,
  obj_item_fukuT_gfx_model,
  obj_item_taisouT_gfx_model,
  obj_mdT_gfx_model,
  obj_item_ticketT_gfx_model,
  obj_item_boneT_gfx_model,
  obj_item_diaryT_gfx_model,
  obj_item_fork_onT_gfx_model
};

/* Clip */
#include "../src/actor/ac_handOverItem_clip.c_inc"

/* Move */
#include "../src/actor/ac_handOverItem_move.c_inc"

/* Draw */
#include "../src/actor/ac_handOverItem_draw.c_inc"

static void aHOI_actor_ct(ACTOR* actorx, GAME* game) {
  aHOI_init_clip_area(actorx, game);
}

static void aHOI_actor_dt(ACTOR* actorx, GAME* game) {
  aHOI_free_clip_area();
}
