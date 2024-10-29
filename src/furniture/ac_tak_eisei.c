extern aFTR_rig_c aTakEisei_sklkey;

extern cKF_Skeleton_R_c cKF_bs_r_int_tak_eisei;
extern cKF_Animation_R_c cKF_ba_r_int_tak_eisei;

aFTR_rig_c aTakEisei_sklkey= {
    &cKF_bs_r_int_tak_eisei,
    &cKF_ba_r_int_tak_eisei,
    1.0f,
};

aFTR_PROFILE iam_tak_eisei = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aTakEisei_sklkey,
	NULL,
	40.0f,
	0.01f,
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
	0,
	1,
	0,
	0,
	NULL,
};
