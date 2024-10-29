extern aFTR_rig_c aTakStation_sklkey;

extern cKF_Skeleton_R_c cKF_bs_r_int_tak_station;
extern cKF_Animation_R_c cKF_ba_r_int_tak_station;

aFTR_rig_c aTakStation_sklkey= {
    &cKF_bs_r_int_tak_station,
    &cKF_ba_r_int_tak_station,
    1.0f,
};

aFTR_PROFILE iam_tak_station = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aTakStation_sklkey,
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
