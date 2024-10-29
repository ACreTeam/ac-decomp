extern aFTR_rig_c aNogAmenbo_key_anime_data;

extern cKF_Skeleton_R_c cKF_bs_r_int_nog_amenbo;
extern cKF_Animation_R_c cKF_ba_r_int_nog_amenbo;

aFTR_rig_c aNogAmenbo_key_anime_data= {
    &cKF_bs_r_int_nog_amenbo,
    &cKF_ba_r_int_nog_amenbo,
    1.0f,
};

aFTR_PROFILE iam_nog_amenbo = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aNogAmenbo_key_anime_data,
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
