extern aFTR_rig_c aTakUfo_sklkey;

extern cKF_Skeleton_R_c cKF_bs_r_int_tak_ufo;
extern cKF_Animation_R_c cKF_ba_r_int_tak_ufo;

aFTR_rig_c aTakUfo_sklkey= {
    &cKF_bs_r_int_tak_ufo,
    &cKF_ba_r_int_tak_ufo,
    1.0f,
};

aFTR_PROFILE iam_tak_ufo = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aTakUfo_sklkey,
	NULL,
	40.0f,
	0.01f,
	aFTR_SHAPE_TYPEC,
	mCoBG_FTR_TYPEC,
	0,
	0,
	0,
	0,
	NULL,
};
