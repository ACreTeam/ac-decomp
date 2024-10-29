#include "m_olib.h"

extern void radianxy_by_2pos(xyz_t* dest, xyz_t* sub, xyz_t* min) {

    xyz_t ret;

    ret.x = fatan2(min->z - sub->z, min->y - sub->y);
    ret.y = fatan2(min->x - sub->x, min->z - sub->z);
    ret.z = 0.0f;

    *dest = ret;
}

extern s_xyz sanglexy_by_2pos(xyz_t* sub, xyz_t* min) {
    
    s_xyz sangle;
    xyz_t conv;
    xyz_t angle;
    
    radianxy_by_2pos(&angle, sub, min);
    conv = angle;
    sangle.x = CAM_DEG_TO_BINANG(RAD_TO_DEG(conv.x));
    sangle.y = CAM_DEG_TO_BINANG(RAD_TO_DEG(conv.y));
    sangle.z = 0;
    

   return sangle;
}
