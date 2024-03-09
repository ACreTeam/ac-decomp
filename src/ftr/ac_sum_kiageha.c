extern aFTR_rig_c aSumKiageha_key_anime_data;

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_kkiageha;
extern cKF_Animation_R_c cKF_ba_r_int_sum_kkiageha;

aFTR_rig_c aSumKiageha_key_anime_data {
    cKF_bs_r_int_sum_kkiageha,
    cKF_ba_r_int_sum_kkiageha,
    0.5f,
};

aFTR_PROFILE iam_sum_kiageha = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aSumKiageha_key_anime_data,
	NULL,
	30.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	2,
	0,
	aFTR_INTERACTION_INSECT,
	NULL,
};
