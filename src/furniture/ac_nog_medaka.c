extern aFTR_rig_c aNogMedaka_key_anime_data;

extern cKF_Skeleton_R_c cKF_bs_r_int_nog_medaka;
extern cKF_Animation_R_c cKF_ba_r_int_nog_medaka;

aFTR_rig_c aNogMedaka_key_anime_data= {
    &cKF_bs_r_int_nog_medaka,
    &cKF_ba_r_int_nog_medaka,
    1.0f,
};

aFTR_PROFILE iam_nog_medaka = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aNogMedaka_key_anime_data,
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
