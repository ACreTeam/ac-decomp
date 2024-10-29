extern aFTR_rig_c aSumFuna_key_anime_data;

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_funa;
extern cKF_Animation_R_c cKF_ba_r_int_sum_funa;

aFTR_rig_c aSumFuna_key_anime_data= {
    &cKF_bs_r_int_sum_funa,
    &cKF_ba_r_int_sum_funa,
    1.0f,
};

aFTR_PROFILE iam_sum_funa = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aSumFuna_key_anime_data,
	NULL,
	30.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	2,
	0,
	aFTR_INTERACTION_FISH,
	NULL,
};
