extern aFTR_rig_c aSumKaseki_key_anime_data;

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_kaseki;
extern cKF_Animation_R_c cKF_ba_r_int_sum_kaseki;

aFTR_rig_c aSumKaseki_key_anime_data= {
    &cKF_bs_r_int_sum_kaseki,
    &cKF_ba_r_int_sum_kaseki,
    1.0f,
};

aFTR_PROFILE iam_sum_kaseki = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aSumKaseki_key_anime_data,
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
