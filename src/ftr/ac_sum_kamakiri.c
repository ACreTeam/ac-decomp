extern aFTR_rig_c aSumKamakiri_key_anime_data;

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_kamakiri;
extern cKF_Animation_R_c cKF_ba_r_int_sum_kamakiri;

aFTR_rig_c aSumKamakiri_key_anime_data= {
    &cKF_bs_r_int_sum_kamakiri,
    &cKF_ba_r_int_sum_kamakiri,
    1.0f,
};

aFTR_PROFILE iam_sum_kamakiri = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aSumKamakiri_key_anime_data,
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
