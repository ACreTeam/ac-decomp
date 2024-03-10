extern aFTR_rig_c aSumKanabun_key_anime_data;

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_kanabun;
extern cKF_Animation_R_c cKF_ba_r_int_sum_kanabun;

aFTR_rig_c aSumKanabun_key_anime_data = {
    &cKF_bs_r_int_sum_kanabun,
    &cKF_ba_r_int_sum_kanabun,
    1.0f,
};

aFTR_PROFILE iam_sum_kanabun = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aSumKanabun_key_anime_data,
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
