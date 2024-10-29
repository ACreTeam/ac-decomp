extern aFTR_rig_c aNogPiraluku_key_anime_data;

extern cKF_Skeleton_R_c cKF_bs_r_int_nog_piraluku;
extern cKF_Animation_R_c cKF_ba_r_int_nog_piraluku;

aFTR_rig_c aNogPiraluku_key_anime_data= {
    &cKF_bs_r_int_nog_piraluku,
    &cKF_ba_r_int_nog_piraluku,
    1.0f,
};

aFTR_PROFILE iam_nog_piraluku = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aNogPiraluku_key_anime_data,
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
