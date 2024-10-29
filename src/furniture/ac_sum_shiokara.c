extern aFTR_rig_c aSumShiokara_key_anime_data;

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_shiokara;
extern cKF_Animation_R_c cKF_ba_r_int_sum_shiokara;

aFTR_rig_c aSumShiokara_key_anime_data= {
    &cKF_bs_r_int_sum_shiokara,
    &cKF_ba_r_int_sum_shiokara,
    1.0f,
};

aFTR_PROFILE iam_sum_shiokara = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aSumShiokara_key_anime_data,
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
