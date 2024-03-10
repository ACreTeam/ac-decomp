extern aFTR_rig_c aNogIsidai_key_anime_data;

extern cKF_Skeleton_R_c cKF_bs_r_int_nog_isidai;
extern cKF_Animation_R_c cKF_ba_r_int_nog_isidai;

aFTR_rig_c aNogIsidai_key_anime_data= {
    &cKF_bs_r_int_nog_isidai,
    &cKF_ba_r_int_nog_isidai,
    1.0f,
};

aFTR_PROFILE iam_nog_isidai = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aNogIsidai_key_anime_data,
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
