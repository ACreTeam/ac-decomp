extern aFTR_rig_c aNogDango_key_anime_data;

extern cKF_Skeleton_R_c cKF_bs_r_int_nog_dango;
extern cKF_Animation_R_c cKF_ba_r_int_nog_dango;

aFTR_rig_c aNogDango_key_anime_data= {
    &cKF_bs_r_int_nog_dango,
    &cKF_ba_r_int_nog_dango,
    1.0f,
};


aFTR_PROFILE iam_nog_dango = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aNogDango_key_anime_data,
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
