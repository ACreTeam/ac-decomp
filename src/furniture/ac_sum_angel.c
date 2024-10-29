extern aFTR_rig_c aSumAngel_key_anime_data;

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_angel;
extern cKF_Animation_R_c cKF_ba_r_int_sum_angel;

aFTR_rig_c aSumAngel_key_anime_data= {
    &cKF_bs_r_int_sum_angel,
    &cKF_ba_r_int_sum_angel,
    1.0f,
};

aFTR_PROFILE iam_sum_angel = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aSumAngel_key_anime_data,
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
