#include "ef_effect_control.h"

#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "m_player_lib.h"
#include "m_debug.h"

static eEC_PROFILE_c* profile_tbl[] = {
    &iam_ef_shock,
    &iam_ef_dust,
    &iam_ef_muka,
    &iam_ef_warau,
    &iam_ef_ha,
    &iam_ef_sibuki,
    &iam_ef_gimonhu,
    &iam_ef_kantanhu,
    &iam_ef_ase,
    &iam_ef_ase_ch,
    &iam_ef_kangaeru,
    &iam_ef_otikomi,
    &iam_ef_buruburu,
    &iam_ef_siawase_hikari,
    &iam_ef_siawase_hana,
    &iam_ef_siawase_hana_ch,
    &iam_ef_takurami,
    &iam_ef_takurami_kira,
    &iam_ef_kaze,
    &iam_ef_kaze_happa,
    &iam_ef_lovelove,
    &iam_ef_lovelove_heart,
    &iam_ef_pun,
    &iam_ef_pun_yuge,
    &iam_ef_pun_sekimen,
    &iam_ef_naku,
    &iam_ef_namida,
    &iam_ef_hirameki_den,
    &iam_ef_hirameki_hikari,
    &iam_ef_situren,
    &iam_ef_ase2,
    &iam_ef_dash_asimoto,
    &iam_ef_konpu,
    &iam_ef_lovelove2,
    &iam_ef_kpun,
    &iam_ef_kisha_kemuri,
    &iam_ef_neboke,
    &iam_ef_neboke_awa,
    &iam_ef_hanabi_yanagi,
    &iam_ef_hanabi_botan1,
    &iam_ef_hanabi_botan2,
    &iam_ef_hanabi_hoshi,
    &iam_ef_hanabi_set,
    &iam_ef_hanabi_switch,
    &iam_ef_footprint,
    &iam_ef_turn_footprint,
    &iam_ef_bubu,
    &iam_ef_turn_asimoto,
    &iam_ef_string,
    &iam_ef_yukihane,
    &iam_ef_anahikari,
    &iam_ef_bush_happa,
    &iam_ef_bush_yuki,
    &iam_ef_tumble,
    &iam_ef_tumble_bodyprint,
    &iam_ef_slip,
    &iam_ef_tumble_dust,
    &iam_ef_swing_net,
    &iam_ef_ami_mizu,
    &iam_ef_mizutama,
    &iam_ef_yukidama,
    &iam_ef_kikuzu,
    &iam_ef_swing_axe,
    &iam_ef_steam,
    &iam_ef_night15_moon,
    &iam_ef_night13_moon,
    &iam_ef_neboke_akubi,
    &iam_ef_slip_footprint,
    &iam_ef_walk_asimoto,
    &iam_ef_turi_hamon,
    &iam_ef_turi_mizu,
    &iam_ef_turi_hane0,
    &iam_ef_turi_hane1,
    &iam_ef_turi_suiteki,
    &iam_ef_ongen,
    &iam_ef_impact_star,
    &iam_ef_sandsplash,
    &iam_ef_young_tree,
    &iam_ef_swing_rod,
    &iam_ef_doyon,
    &iam_ef_kagu_happa,
    &iam_ef_hanabi_dummy,
    &iam_ef_dig_hole,
    &iam_ef_dig_scoop,
    &iam_ef_dig_mud,
    &iam_ef_kigae,
    &iam_ef_kigae_light,
    &iam_ef_tape,
    &iam_ef_clacker,
    &iam_ef_kamifubuki,
    &iam_ef_car_blight,
    &iam_ef_tamaire,
    &iam_ef_car_light,
    &iam_ef_reset_hole,
    &iam_ef_goki,
    &iam_ef_hanabira,
    &iam_ef_wait_asimoto,
    &iam_ef_otosiana,
    &iam_ef_ikigire,
    &iam_ef_yukidaruma,
    &iam_ef_kyousou_onpu,
    &iam_ef_douzou_light,
    &iam_ef_halloween_smoke,
    &iam_ef_halloween,
    &iam_ef_motiyuge,
    &iam_ef_taberu,
    &iam_ef_kasamizu,
    &iam_ef_kasamizutama,
    &iam_ef_hanatiri,
    &iam_ef_uranai,
    &iam_ef_suisou_awa,
    &iam_ef_break_axe,
    &iam_ef_yajirushi,
    &iam_ef_soba_yuge,
    &iam_ef_furo_yuge,
    &iam_ef_shooting,
    &iam_ef_shooting_set,
    &iam_ef_shooting_kira,
    &iam_ef_coin,
    &iam_ef_tent_lamp,
    &iam_ef_flash,
    &iam_ef_flashC,
    &iam_ef_killer,
    &iam_ef_make_hem,
    &iam_ef_make_hem_kira,
    &iam_ef_make_hem_light,
};

static u8 eEC_effect_feature[] = {
    FALSE, FALSE, FALSE, TRUE,  FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE,
    TRUE,  FALSE, TRUE,  TRUE,  FALSE, FALSE, TRUE,  FALSE, FALSE, TRUE,  FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE,
    FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE, FALSE, TRUE,  FALSE,
    FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
    TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
    FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
    FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE, FALSE, FALSE, TRUE,  FALSE, FALSE,
    FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE, FALSE, TRUE,  FALSE, TRUE,  TRUE,  TRUE,  FALSE, TRUE,
};

static void eEC_actor_ct(ACTOR* actorx, GAME* game);
static void eEC_actor_dt(ACTOR* actorx, GAME* game);
static void eEC_actor_move(ACTOR* actorx, GAME* game);
static void eEC_actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Effect_Control_Profile = {
    mAc_PROFILE_EFFECT_CONTROL,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EFFECT_CONTROL_ACTOR),
    &eEC_actor_ct,
    &eEC_actor_dt,
    &eEC_actor_move,
    &eEC_actor_draw,
    NULL,
};

static eEC_work_c eEC_ctrl_work;

#include "../src/effect/ef_effect_lib.c"

static void eEC_Name2EffectMake(int effect_id, xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0,
                                s16 arg1) {
    if (effect_id >= 0 && effect_id < eEC_EFFECT_NUM) {
        if (eEC_effect_feature[effect_id] == FALSE) {
            profile_tbl[effect_id]->init_proc(pos, prio, angle, game, item_name, arg0, arg1);
        } else if (eEC_effect_feature[effect_id] == TRUE) {
            int i;
            u8* active_flags = eEC_ctrl_work.effect_active_flags;
            eEC_Effect_c* effect = eEC_ctrl_work.effects;

            /* Check if any of the spawned effects are an exact match to this one */
            for (i = 0; i < eEC_EFFECT_ACTIVE_MAX; active_flags++, effect++, i++) {
                if (*active_flags && effect->name == effect_id && effect->item_name == item_name) {
                    return;
                }
            }

            /* No exact matches, so create effect */
            profile_tbl[effect_id]->init_proc(pos, prio, angle, game, item_name, arg0, arg1);
        }
    }
}

static void eEC_Name2EffectKill(int effect_id, u16 item_name) {
    int i;
    u8* active_flags = eEC_ctrl_work.effect_active_flags;
    eEC_Effect_c* effect = eEC_ctrl_work.effects;

    for (i = 0; i < eEC_EFFECT_ACTIVE_MAX; i++, active_flags++, effect++) {
        if (*active_flags && effect->name == effect_id && effect->item_name == item_name && effect->prog_idx != -1) {
            if (profile_tbl[effect_id]->n_frames == eEC_IMMEDIATE_DEATH) {
                *active_flags = 0;

                if (profile_tbl[effect_id]->child_effect_id != eEC_NO_CHILD_ID) {
                    eEC_Name2EffectKill(profile_tbl[effect_id]->child_effect_id, item_name);
                }
            } else if (profile_tbl[effect_id]->n_frames != eEC_IGNORE_DEATH) {
                effect->timer = profile_tbl[effect_id]->n_frames;
                effect->state = eEC_STATE_FINISHED;

                if (profile_tbl[effect_id]->child_effect_id != eEC_NO_CHILD_ID) {
                    eEC_Name2EffectKill(profile_tbl[effect_id]->child_effect_id, item_name);
                }
            }
        }
    }
}

static void eEC_Name2EffectKillAll(u16 item_name) {
    int i;
    u8* active_flags = eEC_ctrl_work.effect_active_flags;
    eEC_Effect_c* effect = eEC_ctrl_work.effects;

    for (i = 0; i < eEC_EFFECT_ACTIVE_MAX; i++, active_flags++, effect++) {
        if (*active_flags && effect->item_name == item_name && effect->prog_idx != -1) {
            if (profile_tbl[effect->name]->n_frames == eEC_IMMEDIATE_DEATH) {
                *active_flags = FALSE;
            } else if (eEC_ctrl_work.program_info[effect->prog_idx].end_frame != eEC_IGNORE_DEATH) {
                effect->timer = eEC_ctrl_work.program_info[effect->prog_idx].end_frame;
                effect->state = eEC_STATE_FINISHED;
            }
        }
    }
}

static void eEC_InitEffectControlWork(void) {
    eEL_InitUnchar(eEC_ctrl_work.effect_active_flags, eEC_EFFECT_ACTIVE_MAX, 0);
    eEC_ctrl_work.active_effect_num = 0;
}

static eEC_Effect_c* eEC_MakeEffect(s16 effect_id, xyz_t pos, xyz_t* ofs, GAME* game, void* ct_arg, u16 item_name,
                                    int prio, s16 arg0, s16 arg1);

static void eEC_EffectLib2Clip(ACTOR* actorx) {
    EFFECT_CONTROL_ACTOR* effect_ctrl = (EFFECT_CONTROL_ACTOR*)actorx;

    effect_ctrl->clip.effect_make_proc = &eEC_Name2EffectMake;
    effect_ctrl->clip.effect_kill_proc = &eEC_Name2EffectKill;
    effect_ctrl->clip.effect_kill_all_proc = &eEC_Name2EffectKillAll;
    effect_ctrl->clip.vector_rotate_y_proc = &eEL_VectorRoteteY;
    effect_ctrl->clip.random_first_speed_proc = &eEL_RandomFirstSpeed;
    effect_ctrl->clip.set_continious_env_proc = &eEL_SetContiniousEnv;
    effect_ctrl->clip.calc_adjust_proc = &eEL_CalcAdjust;
    effect_ctrl->clip.auto_matrix_xlu_proc = &eEL_AutoMatrixXlu;
    effect_ctrl->clip.auto_matrix_xlu_offset_proc = &eEL_AutoMatrixXlu_Offset;
    effect_ctrl->clip._20 = NULL;
    effect_ctrl->clip._24 = NULL;
    effect_ctrl->clip.make_effect_proc = &eEC_MakeEffect;
    effect_ctrl->clip.morph_combine_proc = &eEC_MorphCombine;
    effect_ctrl->clip.regist_effect_light = &eEL_RegistEffectLight;
    effect_ctrl->clip.decide_light_power_proc = &eEL_DecideLightPower;
    effect_ctrl->clip.check_lookat_block_proc = &mEL_CheckLookAtBlock;
    effect_ctrl->clip.effect_light_status = &eEL_EffectLightStatus;
    effect_ctrl->clip.special_block_center_pos_proc = &eEL_SpecialBlockCenterPos;

    eEC_CLIP = &effect_ctrl->clip;
}

static void eEC_MakeEffectLight(GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    Light_diffuse_ct(&eEC_ctrl_work.light_info, 0, 127, 0, 0, 0, 0);
    eEC_ctrl_work.light_list = Global_light_list_new(game, &play->global_light, &eEC_ctrl_work.light_info);
}

static void eEC_DeleteEffectLight(GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    Global_light_list_delete(&play->global_light, eEC_ctrl_work.light_list);
}

int eMH_special_point_light_num = 0;

static void eEC_actor_ct(ACTOR* actorx, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    eEC_EffectLib2Clip(actorx);
    eEC_InitEffectControlWork();
    eEC_MakeEffectLight(game);
    eEL_InitEffectLight();

    if (Save_Get(scene_no) == SCENE_TENT) {
        eEC_CLIP->effect_make_proc(eEC_EFFECT_TENT_LAMP, actorx->world.position, 3, 0, game, RSV_NO, 0, 0);
    }

    eMH_special_point_light_num = -1;
}

static void eEC_actor_dt(ACTOR* actorx, GAME* game) {
    eEC_CLIP = NULL;
    eEC_DeleteEffectLight(game);
}

static void eEC_actor_draw(ACTOR* actorx, GAME* game) {
    int i;
    u8* active_flags = eEC_ctrl_work.effect_active_flags;
    eEC_Effect_c* effect = eEC_ctrl_work.effects;

    _texture_z_light_fog_prim(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);

    for (i = 0; i < eEC_EFFECT_ACTIVE_MAX; i++, active_flags++, effect++) {
        if (*active_flags) {
            profile_tbl[effect->name]->draw_proc(effect, game);
        }
    }
}

static int eEC_DistDeath(eEC_Effect_c* effect, GAME* game, s16 prog_idx) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    int res = FALSE; // in range

    if (prog_idx != -1) {
        f32 max_dist = profile_tbl[effect->name]->max_dist;

        if (max_dist != eEC_IGNORE_DEATH_DIST) {
            PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);

            if (ABS(player->actor_class.world.position.x - effect->position.x) > max_dist ||
                ABS(player->actor_class.world.position.z - effect->position.z) > max_dist ||
                ABS(player->actor_class.world.position.y - effect->position.y) > max_dist) {
                res = TRUE; // out of range
            }
        }
    }

    return res;
}

static void eEC_AllEffectMove(GAME* game) {
    int i;
    u8* active_flags = eEC_ctrl_work.effect_active_flags;
    eEC_Effect_c* effect = eEC_ctrl_work.effects;

    for (i = 0; i < eEC_EFFECT_ACTIVE_MAX; i++, active_flags++, effect++) {
        if (*active_flags) {
            s16 prog_idx = effect->prog_idx;

            profile_tbl[effect->name]->move_proc(effect, game);
            effect->timer--;

            if (effect->timer <= 0 || eEC_DistDeath(effect, game, prog_idx) == TRUE) {
                *active_flags = 0;
                effect->timer = 0;
                effect->_0A = 0;
            }
        }
    }
}

static void eEC_actor_move(ACTOR* actorx, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);

    eEL_CalcEffectLight_Set(game);
    eEC_AllEffectMove(game);
    actorx->world.position = player->actor_class.world.position;
}

static int eEC_GetEffectBuff(int prio) {
    int now_idx = eEC_ctrl_work.active_effect_num;
    u8* active_flags = eEC_ctrl_work.effect_active_flags;
    int i;

    for (i = now_idx; i < eEC_EFFECT_ACTIVE_MAX; i++) {
        if (active_flags[i] == 0) {
            return i;
        }
    }

    for (i = 0; i < now_idx - 1; i++) {
        if (active_flags[i] == 0) {
            return i;
        }
    }

    for (i = now_idx; i < eEC_EFFECT_ACTIVE_MAX; i++) {
        if (active_flags[i] < prio) {
            return i;
        }
    }

    for (i = 0; i < now_idx - 1; i++) {
        if (active_flags[i] != 2) {
            return i;
        }
    }

    return -1;
}

static void eEC_SetFirstOffset(eEC_Effect_c* effect, xyz_t* ofs) {
    static xyz_t default_offset = { 0.0f, 0.0f, 0.0f };

    effect->offset = default_offset;
    if (ofs != NULL) {
        effect->offset = *ofs;
    }
}

static eEC_Effect_c* eEC_MakeEffect(s16 effect_id, xyz_t pos, xyz_t* ofs, GAME* game, void* ct_arg, u16 item_name,
                                    int prio, s16 arg0, s16 arg1) {
    static xyz_t defaultX = { 0.0f, 0.0f, 0.0f };
    static xyz_t scale_default = { 0.01f, 0.01f, 0.01f };
    int* active_effect_num = &eEC_ctrl_work.active_effect_num;
    eEC_Effect_c* effect = NULL;
    eEC_Effect_c* effects = eEC_ctrl_work.effects;
    u8* active_flags = eEC_ctrl_work.effect_active_flags;
    int use_idx;

    use_idx = eEC_GetEffectBuff(prio);
    if (use_idx != -1) {
        active_flags[use_idx] = prio;
        effects[use_idx].name = effect_id;
        effects[use_idx].position = pos;
        effects[use_idx].item_name = item_name;
        effects[use_idx].prio = prio;
        effects[use_idx].state = eEC_STATE_NORMAL;
        eEC_SetFirstOffset(&effects[use_idx], ofs);
        effects[use_idx].timer = 10;
        effects[use_idx].velocity = defaultX;
        effects[use_idx].acceleration = defaultX;
        effects[use_idx].scale = scale_default;
        effects[use_idx].arg0 = arg0;
        effects[use_idx].arg1 = arg1;

        profile_tbl[effect_id]->ct_proc(&effects[use_idx], game, ct_arg);
        *active_effect_num = use_idx + 1;
        effect = &effects[use_idx];
    }

    return effect;
}
