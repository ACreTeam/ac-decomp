#include "m_lib.h"



void mem_copy(u8* arg0, u8* arg1, u32 arg2) {
    while (arg2 != 0) {
        *arg0 = *arg1;
        arg1++;
        arg0++;
        arg2--;
    }
}

void mem_clear(u8* arg0, u32 arg1, u8 arg2) {
    u32 i;

    for (i = 0; i < arg1; i++) {*arg0++ = arg2;}
}

s32 mem_cmp(u8* arg0, u8* arg1, u32 arg2) {
    while (arg2 != 0) {
        if (*arg0 != *arg1) {
            return 0;
        }
        arg0++;
        arg1++;
        arg2--;
    }
    return 1;
}


f32 sin_s(s16 arg0) {
    f32 ret = 3.051850945e-05f * sins(arg0); //something something get this from data
    return ret;
}

f32 cos_s(s16 arg0) {
    f32 ret = 3.051850945e-05f * coss(arg0); //something something get this from data
    return ret;
}

s32 chase_angle(s16* pValue, s16 target, s16 step) {
    if (step) {
        f32 updateScale = game_GameFrame_2F;

        if ((s16)(*pValue - target) > 0) {
            step = -step;
        }

        *pValue += (s16)(step * updateScale);

        if (((s16)(*pValue - target) * step) >= 0) {
            *pValue = target;
            return 1;
        }
    } else if (*pValue == target) {
        return 1;
    }

    return 0;
}


s32 chase_s(s16* pValue, s16 target, s16 step) {
    if (step) {
        if (*pValue > target) {
            step = -step;
        }

        *pValue += step;

        if ((step * (*pValue - target)) >= 0) {
            *pValue = target;
            return 1;
        }
    } else {
        if (*pValue == target) {
            return 1;
        }
    }
    return 0;
}

s32 chase_f(f32* pValue, f32 target, f32 step) {
    if (step) {
        if (*pValue > target) {
            step = -step;
        }

        *pValue += step;

        if ((step * (*pValue - target)) >= 0.0f) {
            *pValue = target;
            return 1;
        }
    } else {
        if (*pValue == target) {
            return 1;
        }
    }
    return 0;
}

f32 chase_xyz_t(xyz_t* pValue, xyz_t* target, f32 fraction) {
    xyz_t diff;
    f32 dist;
    f32 stepSize;

    xyz_t_sub(target, pValue, &diff);

    dist = Math3DVecLength(&diff);
    if (dist > fraction) {
        stepSize = fraction / dist;
        pValue->x += stepSize * diff.x;
        pValue->y += stepSize * diff.y;
        pValue->z += stepSize * diff.z;

        return dist - fraction;
    } else {
        xyz_t_move(pValue, target);

        return 0.0f;
    }
}


s32 chase_angle2(s16* pValue, s16 limit, s16 step) {
    s16 prev = *pValue;

    *pValue += step;
    if (((s16)(*pValue - limit) * (s16)(prev - limit)) <= 0) {
        s32 absDiff = ABS((s16)(*pValue - limit));

        if (absDiff < 0x4000) {
            *pValue = limit;
            return 1;
        }
    }

    return 0;
}

void inter_float(f32* pValue, f32 arg1, s32 arg2) {
    if (arg2 <= 0) {
        *pValue = arg1;
    } else {
        f32 diff = arg1 - *pValue;

        *pValue += diff / arg2;
    }
}

s16 get_random_timer(s16 base, s16 range) {
    return base + (s16)(range * fqrand());
}

void xyz_t_move(xyz_t* dest, xyz_t* src) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
}

void xyz_t_move_s_xyz(xyz_t* dest, s_xyz* src) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
}

void xyz_t_add(xyz_t* augend, xyz_t* addend, xyz_t* total) {
    total->x = augend->x + addend->x;
    total->y = augend->y + addend->y;
    total->z = augend->z + addend->z;
}

void xyz_t_sub(xyz_t* minuend, xyz_t* subtrahend, xyz_t* diff) {
    diff->x = minuend->x - subtrahend->x;
    diff->y = minuend->y - subtrahend->y;
    diff->z = minuend->z - subtrahend->z;
}

void xyz_t_mult_v(xyz_t* multiplicand, f32 multiplier) {
    multiplicand->x *= multiplier;
    multiplicand->y *= multiplier;
    multiplicand->z *= multiplier;
}

f32 search_position_distance(xyz_t* subtrahend, xyz_t* minuend) {
    f32 diffX = minuend->x - subtrahend->x;
    f32 diffY = minuend->y - subtrahend->y;
    f32 diffZ = minuend->z - subtrahend->z;

    return sqrtf(SQ(diffX) + SQ(diffY) + SQ(diffZ));
}

f32 search_position_distanceXZ(xyz_t* subtrahend, xyz_t* minuend) {
    f32 diffX = minuend->x - subtrahend->x;
    f32 diffZ = minuend->z - subtrahend->z;

    return sqrtf(SQ(diffX) + SQ(diffZ));
}

s16 search_position_angleY(xyz_t* subtrahend, xyz_t* minuend) {
    f32 diffX = minuend->x - subtrahend->x;
    f32 diffZ = minuend->z - subtrahend->z;

    return atans_table(diffZ, diffX);
}

s16 search_position_angleX(xyz_t* subtrahend, xyz_t* minuend) {
    f32 diffXZ = search_position_distanceXZ(subtrahend, minuend);
    f32 diffY = subtrahend->y - minuend->y;

    return atans_table(diffXZ, diffY);
}

void add_calc2(f32* pValue, f32 target, f32 fraction, f32 step) {
    f32 stepSize;

    if (*pValue != target) {
        stepSize = fraction * (target - *pValue);

        if (stepSize > step) {
            stepSize = step;
        } else if (stepSize < -step) {
            stepSize = -step;
        }

        *pValue += stepSize;
    }
}

void add_calc0(f32* pValue, f32 fraction, f32 step) {
    f32 stepSize = *pValue * fraction;

    if (stepSize > step) {
        stepSize = step;
    } else if (stepSize < -step) {
        stepSize = -step;
    }

    *pValue -= stepSize;
}


s16 add_calc_short_angle2(s16* pValue, s16 target, f32 fraction, s16 step, s16 minStep) {
    s16 stepSize = 0;
    s16 diff = target - *pValue;

    if (*pValue != target) {
        stepSize = (s16)(diff * fraction);

        if ((stepSize > minStep) || (stepSize < -minStep)) {
            if (stepSize > step) {
                stepSize = step;
            } else if (stepSize < -step) {
                stepSize = -step;
            }

            *pValue += stepSize;

            if (stepSize > 0) {
                if ((s16)(target - *pValue) < 0) {
                    *pValue = target;
                }
            } else {
                if ((s16)(target - *pValue) > 0) {
                    *pValue = target;
                }
            }
        } else {
            if (diff >= 0) {
                *pValue += minStep;
                if ((s16)(target - *pValue) < 0) {
                    *pValue = target;
                }
            } else {
                *pValue -= minStep;
                if ((s16)(target - *pValue) > 0) {
                    *pValue = target;
                }
            }
        } 
            
    }
    return target - *pValue;
}

s16 add_calc_short_angle3(s16* pValue, s16 target, f32 fraction, s16 maxStep, s16 minStep) {
    f32 stepSize;
    s32 uTarget;
    s32 newValue;
    s32 uValue;

    if (target != *pValue) {
        uValue = (u16)*pValue;
        uTarget = (u16)target;

        if (uValue > uTarget) {
            uTarget += 0x10000;
        }

        stepSize =  (uTarget - uValue) * fraction;

        if (stepSize > maxStep) {
            stepSize = maxStep;
        } else if (stepSize < minStep) {
            stepSize = minStep;
        }

        newValue = uValue + (s32) stepSize;
        if (newValue > uTarget) {
            newValue = uTarget;
        }
        *pValue = newValue;
    }

    return target - *pValue;
}

void rgba_t_move(rgba_t* dest, rgba_t* src) {
    dest->r = src->r;
    dest->g = src->g;
    dest->b = src->b;
    dest->a = src->a;
}

u32 none_proc1(void){
    return 0;
    //stub
} 

void none_proc2(void){
    //stub
}

// f32 check_percent_abs(s32 arg0, f32 arg8, f32 arg9, f32 argA, f32 argB)
// f32 get_percent_forAccelBrake(f32 arg8, f32 arg9, f32 argA, f32 argB, f32 argC)


void Game_play_Projection_Trans(game_play* play, Vec3f* src, Vec3f* dest) {
    f32 w;

    Matrix_mult(&play->unk_200C, 0);
    Matrix_Position(src, dest);
    w = play->unk_200C.ww + (
          (play->unk_200C.wx * src->x) 
        + (play->unk_200C.wy * src->y) 
        + (play->unk_200C.wz * src->z));
    dest->x = 160.0f + ((dest->x / w) * 160.0f);
    dest->y = 120.0f - ((dest->y / w) * 120.0f);
}

f32 get_percent(s32 arg0, s32 arg1, s32 arg2) {
    f32 temp_f0;
    f32 var_f2;

    var_f2 = 1.0f;
    if (arg2 < arg1) {
        var_f2 = 0.0f;
    } else if (arg2 < arg0) {
        temp_f0 = (f32) (arg0 - arg1);
        if (temp_f0 != 0.0f) {
            var_f2 = (f32) (arg2 - arg1) / temp_f0;
            if (var_f2 > 1.0f) {
                var_f2 = 1.0f;
            }
        }
    }
    return var_f2;
}