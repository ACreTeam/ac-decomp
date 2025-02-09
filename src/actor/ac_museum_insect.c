#include "ac_museum_insect_priv.h"
// clang-format off
extern Gfx
    act_m_mu_monshiro1T_model,
    act_m_mu_monshiro2T_model,
    act_m_mu_monki1T_model,
    act_m_mu_monki2T_model,
    act_m_mu_kiageha1T_model,
    act_m_mu_kiageha2T_model,
    act_m_mu_ohmurasaki1T_model,
    act_m_mu_ohmurasaki2T_model,
    act_m_mu_minmin1_1T_model,
    act_m_mu_minmin1_2T_model,
    act_m_mu_tukutuku1_1T_model,
    act_m_mu_tukutuku1_2T_model,
    act_m_mu_higurashi1_1T_model,
    act_m_mu_higurashi1_2T_model,
    act_m_mu_abura1_1T_model,
    act_m_mu_abura1_2T_model,
    act_m_mu_shiokara1_1T_model,
    act_m_mu_shiokara1_2T_model,
    act_m_mu_shiokara2_2T_model,
    act_m_mu_akiakane1_1T_model,
    act_m_mu_akiakane1_2T_model,
    act_m_mu_akiakane2_2T_model,
    act_m_mu_ginyanma1_1T_model,
    act_m_mu_ginyanma1_2T_model,
    act_m_mu_ginyanma2_2T_model,
    act_m_mu_oniyanma1_1T_model,
    act_m_mu_oniyanma1_2T_model,
    act_m_mu_oniyanma2_2T_model,
    act_m_mu_syouryou1T_model,
    act_m_mu_syouryou2_2T_model,
    act_m_mu_tonosama1T_model,
    act_m_mu_tonosama2_2T_model,
    act_m_mu_koorogi1T_model,
    act_m_mu_koorogi2_2T_model,
    act_m_mu_kirigirisu1T_model,
    act_m_mu_kirigirisu2_2T_model,
    act_m_mu_suzumushi1T_model,
    act_m_mu_suzumushi2_2T_model,
    act_m_mu_matumushi1T_model,
    act_m_mu_matumushi2_2T_model,
    act_m_mu_tentou1T_model,
    act_m_mu_tentou2T_model,
    act_m_mu_nanahoshi1T_model,
    act_m_mu_nanahoshi2T_model,
    act_m_mu_kamakiri1T_model,
    act_m_mu_kamakiri2_2T_model,
    act_m_mu_maimaiT_model,
    act_m_mu_hachi1_1T_model,
    act_m_mu_hachi1_2T_model,
    act_m_mu_hachi2_2T_model,
    act_m_mu_kanabun1T_model,
    act_m_mu_kabuto1T_model,
    act_m_mu_hirata1T_model,
    act_m_mu_tamamushi1T_model,
    act_m_mu_gomadara1T_model,
    act_m_mu_nokogiri1T_model,
    act_m_mu_miyama1T_model,
    act_m_mu_okuwa1T_model,
    act_m_mu_amenbo1T_model,
    act_m_mu_amenbo2T_model,
    act_m_mu_mino1_1T_model,
    act_m_mu_mino1_2T_model,
    act_m_mu_mino2T_model,
    act_m_mu_kumo1_1T_mode,
    act_m_mu_kumo1_2T_mode,
    act_m_mu_kumo2T_model,
    act_m_mu_kumo1_1T_model,
    act_m_mu_kumo1_2T_model,
    act_m_mu_danna1T_model,
    act_m_mu_danna2T_model,
    act_m_mu_genji2_a_model,
    act_m_mu_genji2_b_model,
    act_m_mu_genji2_c_model,
    act_m_mu_genji2_d_model,
    act_m_mu_dango1T_model,
    act_m_mu_dango2T_model,
    act_m_mu_ariT_model,
    act_m_mu_keraT_model,
    act_m_mu_ka1T_model,
    act_m_mu_ka2_1T_model,
    act_m_mu_ka2_2T_model;

ACTOR_PROFILE Museum_Insect_Profile = {
    mAc_PROFILE_MUSEUM_INSECT,
    ACTOR_PART_BG,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_408,
    sizeof(MUSEUM_INSECT_ACTOR),
    Museum_Insect_Actor_ct,
    Museum_Insect_Actor_dt,
    Museum_Insect_Actor_move,
    Museum_Insect_Actor_draw,
    NULL,
};

rgba_t window_color = { 
    0xff, 0xff, 0xcd, 0xff 
};

Gfx *m_monshiro_disp_tbl[] = {
    &act_m_mu_monshiro1T_model,
    &act_m_mu_monshiro2T_model,
    NULL
};

Gfx *m_monki_disp_tbl[] = {
    &act_m_mu_monki1T_model,
    &act_m_mu_monki2T_model,
    NULL
};

Gfx *m_ageha_disp_tbl[] = {
    &act_m_mu_kiageha1T_model,
    &act_m_mu_kiageha2T_model,
    NULL
};

Gfx *m_ohmurasaki_disp_tbl[] = {
    &act_m_mu_ohmurasaki1T_model,
    &act_m_mu_ohmurasaki2T_model,
    NULL
};

Gfx *m_minmin_disp_tbl[] = {
    &act_m_mu_minmin1_1T_model,
    &act_m_mu_minmin1_2T_model,
    NULL
};

Gfx *m_tukutuku_disp_tbl[] = {
    &act_m_mu_tukutuku1_1T_model,
    &act_m_mu_tukutuku1_2T_model,
    NULL
};

Gfx *m_higurashi_disp_tbl[] = {
    &act_m_mu_higurashi1_1T_model,
    &act_m_mu_higurashi1_2T_model,
    NULL
};

Gfx *m_abura_disp_tbl[] = {
    &act_m_mu_abura1_1T_model,
    &act_m_mu_abura1_2T_model,
    NULL
};

Gfx *m_shiokara_disp_tbl[] = {
    &act_m_mu_shiokara1_1T_model,
    &act_m_mu_shiokara1_2T_model,
    &act_m_mu_shiokara2_2T_model,
    NULL
};

Gfx *m_akiakane_disp_tbl[] = {
    &act_m_mu_akiakane1_1T_model,
    &act_m_mu_akiakane1_2T_model,
    &act_m_mu_akiakane2_2T_model,
    NULL
};

Gfx *m_ginyanma_disp_tbl[] = {
    &act_m_mu_ginyanma1_1T_model,
    &act_m_mu_ginyanma1_2T_model,
    &act_m_mu_ginyanma2_2T_model,
    NULL
};

Gfx *m_oniyanma_disp_tbl[] = {
    &act_m_mu_oniyanma1_1T_model,
    &act_m_mu_oniyanma1_2T_model,
    &act_m_mu_oniyanma2_2T_model,
    NULL
};

Gfx *m_syouryou_disp_tbl[] = {
    &act_m_mu_syouryou1T_model,
    &act_m_mu_syouryou2_2T_model,
    NULL
};

Gfx *m_tonosama_disp_tbl[] = {
    &act_m_mu_tonosama1T_model,
    &act_m_mu_tonosama2_2T_model,
    NULL
};

Gfx *m_koorogi_disp_tbl[] = {
    &act_m_mu_koorogi1T_model,
    &act_m_mu_koorogi2_2T_model,
    NULL
};

Gfx *m_kirigirisu_disp_tbl[] = {
    &act_m_mu_kirigirisu1T_model,
    &act_m_mu_kirigirisu2_2T_model,
    NULL
};

Gfx *m_suzumushi_disp_tbl[] = {
    &act_m_mu_suzumushi1T_model,
    &act_m_mu_suzumushi2_2T_model,
    NULL
};

Gfx *m_matumushi_disp_tbl[] = {
    &act_m_mu_matumushi1T_model,
    &act_m_mu_matumushi2_2T_model,
    NULL
};

Gfx *m_tentou_disp_tbl[] = {
    &act_m_mu_tentou1T_model,
    &act_m_mu_tentou2T_model,
    NULL
};

Gfx *m_nanahoshi_disp_tbl[] = {
    &act_m_mu_nanahoshi1T_model,
    &act_m_mu_nanahoshi2T_model,
    NULL
};

Gfx *m_kamakiri_disp_tbl[] = {
    &act_m_mu_kamakiri1T_model,
    &act_m_mu_kamakiri2_2T_model,
    NULL
};

Gfx *m_maimai_disp_tbl[] = {
    &act_m_mu_maimaiT_model,
    NULL
};

Gfx *m_hachi_disp_tbl[] = {
    &act_m_mu_hachi1_1T_model,
    &act_m_mu_hachi1_2T_model,
    &act_m_mu_hachi2_2T_model,
    NULL
};

Gfx *m_kanabun_disp_tbl[] = {
    &act_m_mu_kanabun1T_model,
    NULL
};

Gfx *m_kabuto_disp_tbl[] = {
    &act_m_mu_kabuto1T_model,
    NULL
};

Gfx *m_hirata_disp_tbl[] = {
    &act_m_mu_hirata1T_model,
    NULL
};

Gfx *m_tamamushi_disp_tbl[] = {
    &act_m_mu_tamamushi1T_model,
    NULL
};

Gfx *m_gomadara_disp_tbl[] = {
    &act_m_mu_gomadara1T_model,
    NULL
};

Gfx *m_nokogiri_disp_tbl[] = {
    &act_m_mu_nokogiri1T_model,
    NULL
};

Gfx *m_miyama_disp_tbl[] = {
    &act_m_mu_miyama1T_model,
    NULL
};

Gfx *m_okuwa_disp_tbl[] = {
    &act_m_mu_okuwa1T_model,
    NULL
};

Gfx *m_amenbo_disp_tbl[] = {
    &act_m_mu_amenbo1T_model,
    &act_m_mu_amenbo2T_model,
    NULL
};

Gfx *m_mino_disp_tbl[] = {
    &act_m_mu_mino1_1T_model,
    &act_m_mu_mino1_2T_model,
    &act_m_mu_mino2T_model,
    NULL
};

Gfx *m_kumo_disp_tbl[] = {
    &act_m_mu_kumo1_1T_model,
    &act_m_mu_kumo1_2T_model,
    &act_m_mu_kumo2T_model,
    NULL
};

Gfx *m_goki_disp_tbl[] = {
    &act_m_mu_danna1T_model,
    &act_m_mu_danna2T_model,
    NULL
};

Gfx *m_genji_disp_tbl[] = {
    &act_m_mu_genji2_a_model,
    &act_m_mu_genji2_b_model,
    &act_m_mu_genji2_c_model,
    &act_m_mu_genji2_d_model,
    NULL
};

Gfx *m_dango_disp_tbl[] = {
    &act_m_mu_dango1T_model,
    &act_m_mu_dango2T_model,
    NULL
};

Gfx *m_ari_disp_tbl[] = {
    &act_m_mu_ariT_model,
    NULL
};

Gfx *m_okera_disp_tbl[] = {
    &act_m_mu_keraT_model,
    NULL
};

Gfx *m_ka_disp_tbl[] = {
    &act_m_mu_ka1T_model,
    &act_m_mu_ka2_1T_model,
    &act_m_mu_ka2_2T_model,
    NULL
};

Gfx **minsect_mdl[] = {
    m_monshiro_disp_tbl,
    m_monki_disp_tbl,
    m_ageha_disp_tbl,
    m_ohmurasaki_disp_tbl,
    m_minmin_disp_tbl,
    m_tukutuku_disp_tbl,
    m_higurashi_disp_tbl,
    m_abura_disp_tbl,
    m_hachi_disp_tbl,
    m_shiokara_disp_tbl,
    m_akiakane_disp_tbl,
    m_ginyanma_disp_tbl,
    m_oniyanma_disp_tbl,
    m_syouryou_disp_tbl,
    m_tonosama_disp_tbl,
    m_koorogi_disp_tbl,
    m_kirigirisu_disp_tbl,
    m_suzumushi_disp_tbl,
    m_matumushi_disp_tbl,
    m_kanabun_disp_tbl,
    m_kabuto_disp_tbl,
    m_hirata_disp_tbl,
    m_tamamushi_disp_tbl,
    m_gomadara_disp_tbl,
    m_tentou_disp_tbl,
    m_nanahoshi_disp_tbl,
    m_kamakiri_disp_tbl,
    m_genji_disp_tbl,
    m_goki_disp_tbl,
    m_nokogiri_disp_tbl,
    m_miyama_disp_tbl,
    m_okuwa_disp_tbl,
    m_maimai_disp_tbl,
    m_okera_disp_tbl,
    m_amenbo_disp_tbl,
    m_mino_disp_tbl,
    m_dango_disp_tbl,
    m_kumo_disp_tbl,
    m_ari_disp_tbl,
    m_ka_disp_tbl
};

PRIV_INSECT_PROCESS minsect_ct[] = {
    minsect_chou_ct,
    minsect_chou_ct,
    minsect_chou_ct,
    minsect_chou_ct,
    minsect_semi_ct,
    minsect_semi_ct,
    minsect_semi_ct,
    minsect_semi_ct,
    minsect_hachi_ct,
    minsect_tonbo_ct,
    minsect_tonbo_ct,
    minsect_tonbo_ct,
    minsect_tonbo_ct,
    minsect_batta_ct,
    minsect_batta_ct,
    minsect_batta_ct,
    minsect_batta_ct,
    minsect_batta_ct,
    minsect_batta_ct,
    minsect_kabuto_ct,
    minsect_kabuto_ct,
    minsect_kuwagata_ct,
    minsect_kabuto_ct,
    minsect_kabuto_ct,
    minsect_tentou_ct,
    minsect_tentou_ct,
    minsect_tentou_ct,
    minsect_genji_ct,
    minsect_goki_ct,
    minsect_kuwagata_ct,
    minsect_kuwagata_ct,
    minsect_kuwagata_ct,
    minsect_tentou_ct,
    minsect_okera_ct,
    minsect_amenbo_ct,
    minsect_mino_ct,
    minsect_dango_ct,
    minsect_kumo_ct,
    minsect_ari_ct,
    minsect_ka_ct
};

PRIV_INSECT_PROCESS minsect_mv[] = {
    minsect_chou_mv,
    minsect_chou_mv,
    minsect_chou_mv,
    minsect_chou_mv,
    minsect_semi_mv,
    minsect_semi_mv,
    minsect_semi_mv,
    minsect_semi_mv,
    minsect_hachi_mv,
    minsect_tonbo_mv,
    minsect_tonbo_mv,
    minsect_tonbo_mv,
    minsect_tonbo_mv,
    minsect_batta_mv,
    minsect_batta_mv,
    minsect_batta_mv,
    minsect_batta_mv,
    minsect_batta_mv,
    minsect_batta_mv,
    minsect_kabuto_mv,
    minsect_kabuto_mv,
    minsect_kuwagata_mv,
    minsect_kabuto_mv,
    minsect_kabuto_mv,
    minsect_tentou_mv,
    minsect_tentou_mv,
    minsect_tentou_mv,
    minsect_genji_mv,
    minsect_goki_mv,
    minsect_kuwagata_mv,
    minsect_kuwagata_mv,
    minsect_kuwagata_mv,
    minsect_tentou_mv,
    minsect_okera_mv,
    minsect_amenbo_mv,
    minsect_mino_mv,
    minsect_dango_mv,
    minsect_kumo_mv,
    minsect_ari_mv,
    minsect_ka_mv
};

PRIV_INSECT_PROCESS minsect_dw[] = {
    minsect_chou_dw,
    minsect_chou_dw,
    minsect_chou_dw,
    minsect_chou_dw,
    minsect_semi_dw,
    minsect_semi_dw,
    minsect_semi_dw,
    minsect_semi_dw,
    minsect_hachi_dw,
    minsect_tonbo_dw,
    minsect_tonbo_dw,
    minsect_tonbo_dw,
    minsect_tonbo_dw,
    minsect_batta_dw,
    minsect_batta_dw,
    minsect_batta_dw,
    minsect_batta_dw,
    minsect_batta_dw,
    minsect_batta_dw,
    minsect_kabuto_dw,
    minsect_kabuto_dw,
    minsect_kuwagata_dw,
    minsect_kabuto_dw,
    minsect_kabuto_dw,
    minsect_tentou_dw,
    minsect_tentou_dw,
    minsect_tentou_dw,
    minsect_genji_dw,
    minsect_goki_dw,
    minsect_kuwagata_dw,
    minsect_kuwagata_dw,
    minsect_kuwagata_dw,
    minsect_tentou_dw,
    minsect_okera_dw,
    minsect_amenbo_dw,
    minsect_mino_dw,
    minsect_dango_dw,
    minsect_kumo_dw,
    minsect_ari_dw,
    minsect_ka_dw
};

f32 minsect_shadow_scale_tbl[] = {
    1.0f,
    1.0f,
    1.5f,
    1.5f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    1.0f,
    1.0f,
    1.0f,
    1.5f,
    1.5f,
    1.8f,
    1.0f,
    1.5f,
    1.0f,
    1.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    1.0f,
    0.6f,
    0.7f,
    0.0f,
    0.0f
};

int active_time_tbl[] = {
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 4, 0, 0),
    mTM_TIME2SEC( 4, 0, 0),
    mTM_TIME2SEC( 4, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC(16, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC(16, 0, 0),
    mTM_TIME2SEC(16, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC(19, 0, 0),
    mTM_TIME2SEC(19, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC(19, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC(19, 0, 0),
    mTM_TIME2SEC(19, 0, 0),
    mTM_TIME2SEC(19, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0)
};

int relax_time_tbl[] = {
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC(16, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC(16, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(4, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC(19, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0)
};

xyz_t flower_pos[8] = {
    { 147.0f, 66.f, 169.f },
    { 238.0f, 66.f, 201.f },
    { 264.0f, 66.f, 164.f },
    { 165.0f, 66.f, 219.f },
    { 181.0f, 66.f, 235.f },
    { 199.0f, 66.f, 188.f },
    { 327.5f, 66.f, 154.f },
    { 410.0f, 66.f, 190.f }
};

xyz_t ohmurasaki_tree_pos = {
    360.f, 85.f, 265.f
};

xyz_t tree_pos[8] = {
    {  92.f, 0.f, -15.f },
    { 168.f, 0.f,   5.f },
    { 244.f, 0.f, -15.f },
    { 316.f, 0.f,   5.f },
    { 392.f, 0.f, -15.f },
    { 468.f, 0.f,   5.f },
    { 360.f, 0.f, 245.f },
    { 165.f, 0.f, 485.f }
};

xyz_t rock_pos[] = {
    { 225.f, 0.f, 388.5f },
    { 385.f, 0.f, 485.0f }
};

xyz_t tonbo_rock_pos[6] = {
    { 215.f, 68.f, 403.f },
    { 232.f, 60.f, 381.f },
    { 372.f, 65.f, 482.f },
    { 390.f, 68.f, 469.f },
    { 328.f, 72.f, 501.f },
    { 351.f, 72.f, 501.f }
};

xyz_t tentou_flower_pos[4] = {
    { 410.0f, 65.f, 240.0f },
    { 213.5f, 65.f, 155.0f },
    { 233.0f, 65.f, 233.5f },
    { 294.0f, 65.f, 170.5f },
};

xyz_t hachi_base_pos = {
    165.5f, 78.5f, 482.5f
};

xyz_t kabuto_base_pos[9] = {
    { 165.5f, 78.5f, 482.5f },
    { 389.5f, 66.5f, -14.5f },
    { 241.5f, 67.0f, -15.5f },
    { 165.0f, 81.5f,   0.5f },
    {  89.0f, 64.0f, -15.5f },
    { 466.0f, 84.0f,   1.5f },
    { 171.0f, 64.5f,   5.5f },
    { 319.0f, 81.0f,   1.0f },
    { 313.0f, 63.0f,   5.5f }
};

extern cKF_Skeleton_R_c
    cKF_bs_r_act_m_hirata_b,
    cKF_bs_r_act_m_nokogiri_b,
    cKF_bs_r_act_m_miyama_b,
    cKF_bs_r_act_m_okuwa_b;

cKF_Skeleton_R_c *kuwagata_model_tbl[] = {
    &cKF_bs_r_act_m_hirata_b,
    &cKF_bs_r_act_m_nokogiri_b,
    &cKF_bs_r_act_m_miyama_b,
    &cKF_bs_r_act_m_okuwa_b
};

extern cKF_Animation_R_c
    cKF_ba_r_act_m_hirata_b,
    cKF_ba_r_act_m_nokogiri_b,
    cKF_ba_r_act_m_miyama_b,
    cKF_ba_r_act_m_okuwa_b;

cKF_Animation_R_c *kuwagata_anim_tbl[] = {
    &cKF_ba_r_act_m_hirata_b,
    &cKF_ba_r_act_m_nokogiri_b,
    &cKF_ba_r_act_m_miyama_b,
    &cKF_ba_r_act_m_okuwa_b
};

xyz_t kuwagata_base_pos[4] = {
    { 166.f, 80.5f, 0.5f },
    { 169.f, 66.5f, 5.0f },
    { 318.f, 80.0f, 1.0f },
    { 315.f, 65.0f, 5.5f }
};

xyz_t amenbo_center_pos = {
    289.f, 25.f, 218.f
};

xyz_t rail_pos[6] = {
    { 368.f, 45.f, 467.f },
    { 363.f, 45.f, 482.f },
    { 374.f, 45.f, 499.f },
    { 393.f, 45.f, 502.f },
    { 407.f, 45.f, 488.f },
    { 407.f, 45.f, 469.f }
};

xyz_t ari_rail_pos[3] = {
    { 177.f, 45.f, -14.f },
    { 242.f, 45.f,  10.f },
    { 307.f, 45.f, -14.f }
};

f32 minsect_scale_tbl[40] = {
    0.01f,
    0.01f,
    0.01f,
    0.01f,
    0.008f,
    0.008f,
    0.008f,
    0.008f,
    0.01f,
    0.01f,
    0.01f,
    0.01f,
    0.01f,
    0.01f,
    0.01f,
    0.01f,
    0.01f,
    0.01f,
    0.01f,
    0.01f,
    0.01f,
    0.01f,
    0.009f,
    0.009f,
    0.009f,
    0.009f,
    0.01f,
    0.01f,
    0.01f,
    0.01f,
    0.01f,
    0.01f,
    0.01f,
    0.01f,
    0.007f,
    0.01f,
    0.01f,
    0.01f,
    0.01f,
    0.01f
};

// rodata
const s16 aim_angle_tbl[6] = {
    DEG2SHORT_ANGLE(45 + 0),
    DEG2SHORT_ANGLE(45 + 90),
    DEG2SHORT_ANGLE(45 + 180),
    DEG2SHORT_ANGLE(45 + 270),
    DEG2SHORT_ANGLE(45 + 180),
    DEG2SHORT_ANGLE(45 + 90)
};

const f32 base_high_tbl[4] = {
    85.f, 95.f, 90.f, 90.f
};

const xyz_t mino_base_pos = {
    135.f, 64.f, 474.f
};

const xyz_t mino_top_pos = {
    135.f, 90.f, 474.f
};

const xyz_t mino_bottom_pos = {
    135.f, 54.f, 474.f
};

const xyz_t kumo_base_pos = {
    330.f, 64.5f, 229.f 
};

const xyz_t kumo_top_pos = {
    330.f, 90.f, 229.f
};

const xyz_t kumo_bottom_pos = {
    330.f, 54.f, 229.f
};

const xyz_t base_genji_pos = {
    258.f, 62.f, 258.5f
};

const xyz_t genji_mizu_pos = {
    289.f, 25.f, 218.f
};

const xyz_t okera_base_pos = {
    235.f, 45.f, 445.f
};

// clang-format on

int Museum_Insect_GetMsgNo(ACTOR* actorx) {
    static u8 item_name[mIN_ITEM_NAME_LEN];
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    int insect_caught_by = actor->_2F80[actor->_2F7C].insectInfo;
    s16 insect_no = ITM_INSECT_START + actor->_2F80[actor->_2F7C].insectName;
    int msgNo;
    mIN_copy_name_str(item_name, insect_no);
    mMsg_Set_item_str_art(mMsg_Get_base_window_p(), mMsg_ITEM_STR0, item_name, ARRAY_COUNT(item_name),
                          mIN_get_item_article(insect_no));

    if (insect_caught_by >= 1 && insect_caught_by <= 4) {
        mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR0,
                          common_data.save.save.private_data[insect_caught_by - 1].player_ID.player_name, 8);
    }

    if (actor->_2F7C < actor->_2F78 - 1) {
        if (insect_caught_by >= 1 && insect_caught_by <= 4) {
            msgNo = 0x2fa2;
        } else {
            msgNo = 0x2fa3;
        }
    } else {
        if (insect_caught_by >= 1 && insect_caught_by <= 4) {
            msgNo = 0x2f9f;
        } else {
            msgNo = 0x2fa0;
        }
    }

    return msgNo;
}

MUSEUM_INSECT_ACTOR* MI_Control_Actor = NULL;

int Museum_Insect_Check_Talk_Distance(GAME* game, int i) {
    static xyz_t kanban_pos[6] = { { 140.f, 40.f, 60.f },  { 420.f, 40.f, 60.f },  { 220.f, 40.f, 300.f },
                                   { 380.f, 40.f, 300.f }, { 180.f, 40.f, 540.f }, { 340.f, 40.f, 540.f } };
    GAME_PLAY* play = (GAME_PLAY*)game;
    xyz_t p;
    PLAYER_ACTOR* player_actor = get_player_actor_withoutCheck(play);
    s16 newAngle = player_actor->actor_class.world.angle.y + DEG2SHORT_ANGLE(-180);
    xyz_t_sub(&player_actor->actor_class.world.position, &kanban_pos[i], &p);

    if (ABS(p.x) < 20.f && ABS(p.z) < 20.f && ABS(newAngle) < DEG2SHORT_ANGLE(67.5f)) {
        return TRUE;
    }
    return FALSE;
}

void Museum_Insect_Set_MsgInsectInfo(ACTOR* actorx, int groupNum) {
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    int i;
    static int group_max_num[6] = { 7, 6, 6, 6, 7, 7 };
    static int group_1_insect_name[7] = { 22, 4, 21, 29, 38, 20, 7 };
    static int group_2_insect_name[6] = { 31, 30, 19, 5, 23, 6 };
    static int group_3_insect_name[6] = { 0, 25, 26, 1, 27, 2 };
    static int group_4_insect_name[6] = { 32, 34, 37, 3, 24, 39 };
    static int group_5_insect_name[7] = { 35, 8, 33, 9, 10, 11, 12 };
    static int group_6_insect_name[7] = { 15, 16, 18, 17, 13, 14, 36 };
    static int* group_insect_name[6] = { group_1_insect_name, group_2_insect_name, group_3_insect_name,
                                         group_4_insect_name, group_5_insect_name, group_6_insect_name };
    actor->_2F78 = 0;
    actor->_2F7C = 0;
    for (i = 0; i < group_max_num[groupNum]; i++) {
        s16 insectName = group_insect_name[groupNum][i];
        s16 s = mMmd_InsectInfo(insectName);
        if (s) {
            actor->_2F80[actor->_2F78].insectName = insectName;
            actor->_2F80[actor->_2F78].insectInfo = s;
            actor->_2F78++;
        }
    }
}

void Museum_Insect_set_talk_info(ACTOR* actorx) {
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    int x;
    if (actor->_2F78 > 0) {
        x = Museum_Insect_GetMsgNo(actorx);
        actor->_2F7C++;
    } else {
        x = 0x2fa1;
    }
    mDemo_Set_talk_window_color(&window_color);
    mDemo_Set_msg_num(x);
    mDemo_Set_talk_display_name(FALSE);
    mDemo_Set_ListenAble();
    mDemo_Set_camera(CAMERA2_PROCESS_NORMAL);
    mDemo_Set_use_zoom_sound(TRUE);
}

void Museum_Insect_Talk_process(ACTOR* actorx, GAME* game) {
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    if (mDemo_Check(mDemo_TYPE_SPEAK, actorx)) {
        s_xyz rot = get_player_actor_withoutCheck((GAME_PLAY*)game)->actor_class.shape_info.rotation;
        add_calc_short_angle2(&rot.y, DEG2SHORT_ANGLE(-180), 0.3f, DEG2SHORT_ANGLE(22.5), DEG2SHORT_ANGLE(0));
        get_player_actor_withoutCheck((GAME_PLAY*)gamePT)
            ->Set_force_position_angle_proc(gamePT, NULL, &rot, mPlayer_FORCE_POSITION_ANGLE_ROTY);
        if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p())) {
            int choice = mChoice_Get_ChoseNum(mChoice_Get_base_window_p());
            if (choice != -1) {
                if (choice == 0) {
                    int msgNum = Museum_Insect_GetMsgNo(actorx);
                    actor->_2F7C++;
                    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), msgNum);
                    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
                } else {
                    mMsg_Set_CancelNormalContinue(mMsg_Get_base_window_p());
                    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
                }
            }
        }
    } else if (chkTrigger(BUTTON_A) && !mDemo_Get_talk_actor()) {
        int i;
        for (i = 0; i < 6; i++) {
            if (Museum_Insect_Check_Talk_Distance(game, i)) {
                Museum_Insect_Set_MsgInsectInfo(actorx, i);
                mDemo_Request(mDemo_TYPE_SPEAK, actorx, Museum_Insect_set_talk_info);
            }
        }
    }
}

void Museum_Insect_Actor_ct(ACTOR* actorx, GAME* game) {
    int i;
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    MI_Control_Actor = actor;
    for (i = 0; i < 5; i++) {
        actor->_2F9C[i] = 0;
    }
    for (i = 0; i < aINS_INSECT_TYPE_NUM; i++) {
        if (mMmd_InsectInfo(i)) {
            actor->privInsects[i]._8C |= 1;
            actor->privInsects[i]._00 = i;
            actor->privInsects[i]._14 = minsect_scale_tbl[i];
            set_relax_active_time(&actor->privInsects[i], game);
            minsect_ct[i](&actor->privInsects[i], game);
        }
    }
}

void Museum_Insect_Actor_dt(ACTOR* actor, GAME* game) {
    return;
}

void Museum_Insect_Actor_move(ACTOR* actorx, GAME* game) {
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    int i;
    actor->actor.world.position.y = 4000.f;
    Museum_Insect_Talk_process(actorx, game);
    for (i = 0; i < aINS_INSECT_TYPE_NUM; i++) {
        if (actor->privInsects[i]._8C & 1) {
            minsect_mv[i](&actor->privInsects[i], game);
        }
    }
}

extern EVW_ANIME_DATA obj_museum4_water_evw_anime;
extern Gfx obj_museum4_water_modelT[];

void Museum_Insect_Actor_draw(ACTOR* actorx, GAME* game) {
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    GRAPH* graph;
    int i;
    _texture_z_light_fog_prim_xlu(game->graph);
    Evw_Anime_Set((GAME_PLAY*)game, &obj_museum4_water_evw_anime);
    graph = game->graph;
    Matrix_translate(100.0f, 0.0f, 0.0f, FALSE);
    Matrix_scale(0.01f, 0.01f, 0.01f, TRUE);
    OPEN_DISP(graph);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_XLU_DISP, obj_museum4_water_modelT);
    CLOSE_DISP(graph);
    for (i = 0; i < aINS_INSECT_TYPE_NUM; i++) {
        if (actor->privInsects[i]._8C & 1) {
            if (GETREG(TAKREG, 0) == i + 1) {
                actor->privInsects[i]._14 = (GETREG(TAKREG, 1) * 0.0001f) + minsect_scale_tbl[i];
            }
            minsect_dw[i](&actor->privInsects[i], game);
            if (GETREG(TAKREG, 0) == i + 1) {
                actor->privInsects[i]._14 = minsect_scale_tbl[i];
            }
        }
    }
}

#include "../src/actor/ac_museum_insect_base.c_inc"
