extern aFTR_rig_c aSumIto_key_anime_data;

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_ito;
extern cKF_Animation_R_c cKF_ba_r_int_sum_ito;

aFTR_rig_c aSumIto_key_anime_data= {
    &cKF_bs_r_int_sum_ito,
    &cKF_ba_r_int_sum_ito,
    1.0f,
};

aFTR_PROFILE iam_sum_ito = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aSumIto_key_anime_data,
	NULL,
	30.0f,
	0.01f,
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
	0,
	2,
	0,
	aFTR_INTERACTION_FISH,
	NULL,
};
