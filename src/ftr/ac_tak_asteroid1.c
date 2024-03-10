extern aFTR_rig_c aTakAsteroid1_sklkey;

extern cKF_Skeleton_R_c cKF_bs_r_int_tak_asteroid1;
extern cKF_Animation_R_c cKF_ba_r_int_tak_asteroid1;

aFTR_rig_c aTakAsteroid1_sklkey= {
    &cKF_bs_r_int_tak_asteroid1,
    &cKF_ba_r_int_tak_asteroid1,
    1.0f,
};

aFTR_PROFILE iam_tak_asteroid1 = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aTakAsteroid1_sklkey,
	NULL,
	40.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	NULL,
};
