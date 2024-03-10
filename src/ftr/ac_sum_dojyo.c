extern aFTR_rig_c aSumDojyo_key_anime_data;

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_dojyo;
extern cKF_Animation_R_c cKF_ba_r_int_sum_dojyo;

aFTR_rig_c aSumDojyo_key_anime_data= {
    &cKF_bs_r_int_sum_dojyo,
    &cKF_ba_r_int_sum_dojyo,
    1.0f,
};
aFTR_PROFILE iam_sum_dojyo = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aSumDojyo_key_anime_data,
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
