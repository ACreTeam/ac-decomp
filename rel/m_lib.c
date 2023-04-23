/**
 * @file m_lib.c
 * @brief Utility functions for various mathematical and memory operations.
 *
 * This file contains a collection of utility functions used for various mathematical
 * and memory operations. These functions include:
 *
 * - mem_copy(): Copy memory from one location to another.
 * - mem_clear(): Clear a memory area.
 * - mem_cmp(): Compare two memory areas.
 * - cos_s(): Calculate the cosine of a short angle.
 * - sin_s(): Calculate the sine of a short angle.
 * - chase_angle(): Chase an angle with a given step value.
 * - chase_s(): Chase a short integer value with a given step value.
 * - chase_f(): Chase a float value with a given step value.
 * - chase_xyz_t(): Chase an xyz_t structure value with a given fraction value.
 * - chase_angle2(): Chase an angle with a given step value and limit.
 * - inter_float(): Interpolate between two float values with a given step value.
 * - get_random_timer(): Get a random timer value with a base and range.
 * - xyz_t_move(): Move an xyz_t value from a source to a destination.
 * - xyz_t_move_s_xyz(): Move an xyz_t value from an s_xyz source to a destination.
 * - xyz_t_add(): Add two xyz_t values.
 * - xyz_t_sub(): Subtract two xyz_t values.
 * - xyz_t_mult_v(): Multiply an xyz_t value by a scalar.
 * - search_position_distance(): Calculate the distance between two 3D positions.
 * - search_position_distanceXZ(): Calculate the horizontal distance between two 3D positions.
 * - search_position_angleY(): Calculate the Y angle between two 3D positions.
 * - search_position_angleX(): Calculate the X angle between two 3D positions.
 * - add_calc(): Update a float value towards a target with a given fraction, max step, and min step.
 * - add_calc2(): Update a float value towards a target with a given fraction and max step.
 * - add_calc0(): Update a float value with a given fraction and max step.
 * - add_calc_short_angle2(): Update a short angle value towards a target with given fraction, max step, and min step.
 * - add_calc_short_angle3(): Update a short angle value towards a target with given fraction, max step, and min step.
 * - rgba_t_move(): Move an rgba_t value from a source to a destination.
 * - none_proc1(): A general no-op function that returns 0.
 * - none_proc2(): A no-op function meant for ACTORs which does nothing.
 * - _Game_play_isPause(): Check if the game is paused.
 * - check_percent_abs(): Calculate a percentage value with scaling and optional shifting.
 * - get_percent_forAccelBrake(): Calculate a percentage value for acceleration and braking.
 * - Game_play_Projection_Trans(): Transform a world position into screen space.
 * - get_percent(): Calculate a percentage value given a min and max range.
 */

#include "m_lib.h"

#include "game.h"
#include "m_actor.h"
#include "m_play.h"
#include "main.h"

/**
 * @brief Copy memory from the source buffer to the destination buffer.
 *
 * This function copies the specified number of bytes from the source buffer
 * to the destination buffer.
 *
 * @param dst Pointer to the destination buffer.
 * @param src Pointer to the source buffer.
 * @param size Number of bytes to copy.
 */
extern void mem_copy(u8* dst, u8* src, size_t size) {
  for (size; size != 0; size--) {
    *dst = *src;
    src++;
    dst++;
  }
}

/**
 * @brief Clear memory in the destination buffer by setting it to the specified value.
 *
 * This function sets the specified number of bytes in the destination buffer
 * to the provided value.
 *
 * @param dst Pointer to the destination buffer.
 * @param size Number of bytes to clear.
 * @param val Value to set each byte in the destination buffer.
 */
extern void mem_clear(u8* dst, size_t size, u8 val) {
  u32 i;

  for (i = 0; i < size; i++) {
    *dst++ = val;
  }
}

/**
 * @brief Compare two memory buffers for equality.
 *
 * This function compares the specified number of bytes between two memory
 * buffers. If they are equal, the function returns TRUE, otherwise FALSE.
 *
 * @param p1 Pointer to the first memory buffer.
 * @param p2 Pointer to the second memory buffer.
 * @param size Number of bytes to compare.
 * @return TRUE if the memory buffers are equal, FALSE otherwise.
 */
extern int mem_cmp(u8* p1, u8* p2, size_t size) {
  for (size; size != 0; size--) {
    if (*p1 != *p2) {
      return FALSE;
    }
    p1++;
    p2++;
  }
  return TRUE;
}

/**
 * @brief Calculate the cosine of the given angle.
 *
 * This function calculates the cosine of the given angle (in s16 format)
 * and returns the result as a floating-point value.
 *
 * @param angle Angle in s16 format.
 * @return Cosine of the angle as a floating-point value.
 */
extern f32 cos_s(s16 angle) { return coss(angle) * SHT_MINV; }

/**
 * @brief Calculate the sine of the given angle.
 *
 * This function calculates the sine of the given angle (in s16 format)
 * and returns the result as a floating-point value.
 *
 * @param angle Angle in s16 format.
 * @return Sine of the angle as a floating-point value.
 */
extern f32 sin_s(s16 angle) { return sins(angle) * SHT_MINV; }

/**
 * @brief Chase an angle value towards a target angle, with a specified step.
 *
 * This function updates the angle value, moving it towards the target angle
 * by a specified step. The angle will not overshoot the target. The function
 * returns TRUE if the angle reaches the target, and FALSE otherwise.
 *
 * @param pValue Pointer to the angle value to be updated.
 * @param target Target angle to chase.
 * @param step Step value to be added or subtracted from the current angle.
 * @return TRUE if the angle reaches the target, FALSE otherwise.
 */
extern int chase_angle(s16* const pValue, const s16 target, s16 step) {
  if (step) {
    f32 updateScale = game_GameFrame_2F;

    if ((s16)(*pValue - target) > 0) {
      step = -step;
    }

    *pValue += (s16)(step * updateScale);

    if (((s16)(*pValue - target) * step) >= 0) {
      *pValue = target;
      return TRUE;
    }
  } else if (*pValue == target) {
    return TRUE;
  }

  return FALSE;
}

/**
 * @brief Chase a signed 16-bit value towards a target value, with a specified step.
 *
 * This function updates the value, moving it towards the target value
 * by a specified step. The value will not overshoot the target. The function
 * returns TRUE if the value reaches the target, and FALSE otherwise.
 *
 * @param pValue Pointer to the value to be updated.
 * @param target Target value to chase.
 * @param step Step value to be added or subtracted from the current value.
 * @return TRUE if the value reaches the target, FALSE otherwise.
 */
extern int chase_s(s16* const pValue, const s16 target, s16 step) {
  if (step) {
    if (*pValue > target) {
      step = -step;
    }

    *pValue += step;

    if ((step * (*pValue - target)) >= 0) {
      *pValue = target;
      return TRUE;
    }
  } else {
    if (*pValue == target) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * @brief Chase a floating-point value towards a target value, with a specified step.
 *
 * This function updates the value, moving it towards the target value
 * by a specified step. The value will not overshoot the target. The function
 * returns TRUE if the value reaches the target, and FALSE otherwise.
 *
 * @param pValue Pointer to the value to be updated.
 * @param target Target value to chase.
 * @param step Step value to be added or subtracted from the current value.
 * @return TRUE if the value reaches the target, FALSE otherwise.
 */
extern int chase_f(f32* const pValue, const f32 target, f32 step) {
  if (step) {
    if (*pValue > target) {
      step = -step;
    }

    *pValue += step;

    if ((step * (*pValue - target)) >= 0.0f) {
      *pValue = target;
      return TRUE;
    }
  } else {
    if (*pValue == target) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * @brief Chase an xyz_t value towards a target xyz_t value, with a specified fraction.
 *
 * This function updates the xyz_t value, moving it towards the target xyz_t value
 * by a specified fraction of the distance between the current value and the target.
 * The function returns the remaining distance after the chase.
 *
 * @param pValue Pointer to the xyz_t value to be updated.
 * @param target Pointer to the target xyz_t value to chase.
 * @param fraction Fraction of the distance to move towards the target.
 * @return Remaining distance after the chase.
 */
extern f32 chase_xyz_t(xyz_t* const pValue, const xyz_t* const target,
                       const f32 fraction) {
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

/**
 * @brief Chase an angle value towards a limit angle with a specified step, considering wrap-around.
 *
 * This function updates the angle value, moving it towards the limit angle by a specified step,
 * taking into account the angle wrap-around (0 to 65535). The function returns TRUE if the value
 * reaches the limit, and FALSE otherwise.
 *
 * @param pValue Pointer to the angle value to be updated.
 * @param limit Limit angle to chase.
 * @param step Step value to be added to the current angle.
 * @return TRUE if the angle reaches the limit, FALSE otherwise.
 */
extern int chase_angle2(s16* const pValue, const s16 limit, const s16 step) {
  s16 prev = *pValue;

  *pValue += step;
  if (((s16)(*pValue - limit) * (s16)(prev - limit)) <= 0) {
    s32 absDiff = ABS((s16)(*pValue - limit));

    if (absDiff < 16384) {
      *pValue = limit;
      return TRUE;
    }
  }

  return FALSE;
}

/**
 * @brief Interpolate between a floating-point value and a target value using a specified step.
 *
 * This function updates the value, moving it towards the target value
 * by a specified fraction of the difference between the current value and the target.
 * If the step is less than or equal to zero, the value is set directly to the target value.
 *
 * @param pValue Pointer to the floating-point value to be updated.
 * @param arg1 Target value to interpolate.
 * @param step Step value used to control the interpolation speed.
 */
extern void inter_float(f32* const pValue, const f32 arg1, const int step) {
  if (step <= 0) {
    *pValue = arg1;
  } else {
    f32 diff = arg1 - *pValue;

    *pValue += diff / step;
  }
}

/**
 * @brief Generate a random timer value based on a base value and a range.
 *
 * This function generates a random timer value by adding a fraction of the specified range
 * to the base value. The random fraction is generated using fqrand().
 * Range will be [base, base + range).
 *
 * @param base Base value for the timer.
 * @param range Range value used to generate the random fraction.
 * @return Random timer value.
 */
extern s16 get_random_timer(const s16 base, const s16 range) {
  return base + (s16)(range * fqrand());
}

/**
 * @brief Move the content of an xyz_t structure to another xyz_t structure.
 *
 * This function copies the x, y, and z values from the source xyz_t structure
 * to the destination xyz_t structure.
 *
 * @param dest Pointer to the destination xyz_t structure.
 * @param src Pointer to the source xyz_t structure.
 */
extern void xyz_t_move(xyz_t* const dest, const xyz_t* const src) {
  dest->x = src->x;
  dest->y = src->y;
  dest->z = src->z;
}

/**
 * @brief Move the content of an s_xyz structure to an xyz_t structure.
 *
 * This function copies the x, y, and z values from the source s_xyz structure
 * to the destination xyz_t structure, converting the values to floating-point.
 *
 * @param dest Pointer to the destination xyz_t structure.
 * @param src Pointer to the source s_xyz structure.
 */
extern void xyz_t_move_s_xyz(xyz_t* const dest, const s_xyz* const src) {
  dest->x = src->x;
  dest->y = src->y;
  dest->z = src->z;
}

/**
 * @brief Add two xyz_t structures element-wise and store the result in another xyz_t structure.
 *
 * This function adds the corresponding x, y, and z values of the two input xyz_t structures
 * and stores the result in the output xyz_t structure.
 *
 * @param augend Pointer to the first xyz_t structure (augend).
 * @param addend Pointer to the second xyz_t structure (addend).
 * @param total Pointer to the output xyz_t structure where the result will be stored.
 */
extern void xyz_t_add(const xyz_t* const augend, const xyz_t* const addend,
                      xyz_t* const total) {
  total->x = augend->x + addend->x;
  total->y = augend->y + addend->y;
  total->z = augend->z + addend->z;
}

/**
 * @brief Subtract two xyz_t structures element-wise and store the result in another xyz_t structure.
 *
 * This function subtracts the corresponding x, y, and z values of the second input xyz_t structure
 * from the first input xyz_t structure and stores the result in the output xyz_t structure.
 *
 * @param minuend Pointer to the first xyz_t structure (minuend).
 * @param subtrahend Pointer to the second xyz_t structure (subtrahend).
 * @param diff Pointer to the output xyz_t structure where the result will be stored.
 */
extern void xyz_t_sub(const xyz_t* const minuend, const xyz_t* const subtrahend,
                      xyz_t* const diff) {
  diff->x = minuend->x - subtrahend->x;
  diff->y = minuend->y - subtrahend->y;
  diff->z = minuend->z - subtrahend->z;
}

/**
 * @brief Multiply an xyz_t structure by a scalar value.
 *
 * This function multiplies the x, y, and z values of the input xyz_t structure
 * by the specified scalar value, updating the input structure in-place.
 *
 * @param multiplicand Pointer to the xyz_t structure to be multiplied.
 * @param multiplier Scalar value to multiply the xyz_t structure by.
 */
extern void xyz_t_mult_v(xyz_t* const multiplicand, const f32 multiplier) {
  multiplicand->x *= multiplier;
  multiplicand->y *= multiplier;
  multiplicand->z *= multiplier;
}

/**
 * @brief Calculate the Euclidean distance between two xyz_t structures.
 *
 * This function computes the Euclidean distance between the input position and target
 * xyz_t structures, returning the result as a floating-point value.
 *
 * @param pos Pointer to the first xyz_t structure representing the position.
 * @param target Pointer to the second xyz_t structure representing the target position.
 * @return The Euclidean distance between the two xyz_t structures.
 */
extern f32 search_position_distance(const xyz_t* const pos,
                                    const xyz_t* const target) {
  f32 diffX = target->x - pos->x;
  f32 diffY = target->y - pos->y;
  f32 diffZ = target->z - pos->z;

  return sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));
}

/**
 * @brief Calculate the Euclidean distance between two xyz_t structures in the XZ plane.
 *
 * This function computes the Euclidean distance between the input position and target
 * xyz_t structures in the XZ plane, ignoring the Y component, returning the result as a floating-point value.
 *
 * @param pos Pointer to the first xyz_t structure representing the position.
 * @param target Pointer to the second xyz_t structure representing the target position.
 * @return The Euclidean distance between the two xyz_t structures in the XZ plane.
 */
extern f32 search_position_distanceXZ(const xyz_t* const pos,
                                      const xyz_t* const target) {
  f32 diffX = target->x - pos->x;
  f32 diffZ = target->z - pos->z;

  return sqrtf((diffX * diffX) + (diffZ * diffZ));
}

/**
 * @brief Calculate the angle in the Y axis between two xyz_t structures.
 *
 * This function computes the angle in the Y axis between the input position and target
 * xyz_t structures using the atans_table function.
 *
 * @param pos Pointer to the first xyz_t structure representing the position.
 * @param target Pointer to the second xyz_t structure representing the target position.
 * @return The angle in the Y axis between the two xyz_t structures.
 */
extern s16 search_position_angleY(const xyz_t* const pos,
                                  const xyz_t* const target) {
  f32 diffX = target->x - pos->x;
  f32 diffZ = target->z - pos->z;

  return atans_table(diffZ, diffX);
}

/**
 * @brief Calculate the angle in the X axis between two xyz_t structures.
 *
 * This function computes the angle in the X axis between the input position and target
 * xyz_t structures using the atans_table function.
 *
 * @param pos Pointer to the first xyz_t structure representing the position.
 * @param target Pointer to the second xyz_t structure representing the target position.
 * @return The angle in the X axis between the two xyz_t structures.
 */
extern s16 search_position_angleX(const xyz_t* const pos,
                                  const xyz_t* const target) {
  f32 diffXZ = search_position_distanceXZ(pos, target);
  f32 diffY = pos->y - target->y;

  return atans_table(diffXZ, diffY);
}

/**
 * @brief Add a calculated value to a variable to approach a target value with minimum and maximum step limits.
 *
 * This function adds a calculated step size to the input variable to approach the target value.
 * The step size is calculated based on the fraction and is limited by the minimum and maximum step values.
 *
 * @param pValue Pointer to the input variable.
 * @param target Target value to approach.
 * @param fraction Fraction to use in the step size calculation.
 * @param maxStep Maximum allowed step size.
 * @param minStep Minimum allowed step size.
 * @return The difference between the updated input variable value and the target value.
 */
extern f32 add_calc(f32* pValue, f32 target, f32 fraction, f32 maxStep,
                    f32 minStep) {
  f32 negMinStep;
  f32 stepSize;

  if (*pValue != target) {
    stepSize = fraction * (target - *pValue);
    negMinStep = -minStep;

    if ((stepSize <= negMinStep) || (minStep <= stepSize)) {
      if (stepSize > maxStep) {
        stepSize = maxStep;
      } else if (stepSize < -maxStep) {
        stepSize = -maxStep;
      }

      *pValue += stepSize;

      if (stepSize > 0.0f) {
        if (*pValue > target) {
          *pValue = target;
        }
      } else {
        if (*pValue < target) {
          *pValue = target;
        }
      }
    } else {
      if (stepSize > 0.0f) {
        *pValue += minStep;
        if (*pValue > target) {
          *pValue = target;
        }
      } else {
        *pValue += negMinStep;
        if (*pValue < target) {
          *pValue = target;
        }
      }
    }
  }

  return target - *pValue;
}

/**
 * @brief Add a calculated value to a variable to approach a target value with a maximum step limit.
 *
 * This function adds a calculated step size to the input variable to approach the target value.
 * The step size is calculated based on the fraction and is limited by the maximum step value.
 *
 * @param pValue Pointer to the input variable.
 * @param target Target value to approach.
 * @param fraction Fraction to use in the step size calculation.
 * @param maxStep Maximum allowed step size.
 */
extern void add_calc2(f32* pValue, f32 target, f32 fraction, f32 maxStep) {
  f32 stepSize;

  if (*pValue != target) {
    stepSize = fraction * (target - *pValue);

    if (stepSize > maxStep) {
      stepSize = maxStep;
    } else if (stepSize < -maxStep) {
      stepSize = -maxStep;
    }

    *pValue += stepSize;
  }
}

/**
 * @brief Subtract a calculated value from a variable based on a fraction with a maximum step limit.
 *
 * This function subtracts a calculated step size from the input variable based on the fraction.
 * The step size is limited by the maximum step value.
 *
 * @param pValue Pointer to the input variable.
 * @param fraction Fraction to use in the step size calculation.
 * @param maxStep Maximum allowed step size.
 */
extern void add_calc0(f32* pValue, f32 fraction, f32 maxStep) {
  f32 stepSize = *pValue * fraction;

  if (stepSize > maxStep) {
    stepSize = maxStep;
  } else if (stepSize < -maxStep) {
    stepSize = -maxStep;
  }

  *pValue -= stepSize;
}

/**
 * @brief Add a calculated value to a short integer variable to approach a target angle with minimum and maximum step limits.
 *
 * This function adds a calculated step size to the input short integer variable to approach the target angle.
 * The step size is calculated based on the fraction and is limited by the minimum and maximum step values.
 *
 * @param pValue Pointer to the input short integer variable.
 * @param target Target angle to approach.
 * @param fraction Fraction to use in the step size calculation.
 * @param maxStep Maximum allowed step size.
 * @param minStep Minimum allowed step size.
 * @return The difference between the updated input variable angle and the target angle.
 */
extern s16 add_calc_short_angle2(s16* pValue, s16 target, f32 fraction,
                                 s16 maxStep, s16 minStep) {
  s16 stepSize = 0;
  s16 diff = target - *pValue;

  if (*pValue != target) {
    stepSize = (s16)(diff * fraction);

    if ((stepSize > minStep) || (stepSize < -minStep)) {
      if (stepSize > maxStep) {
        stepSize = maxStep;
      } else if (stepSize < -maxStep) {
        stepSize = -maxStep;
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

/**
 * @brief Add a calculated value to a short integer angle variable to approach a target angle with minimum and maximum step limits.
 *
 * This function adds a calculated step size to the input short integer angle variable to approach the target angle.
 * The step size is calculated based on the fraction and is limited by the minimum and maximum step values.
 * Handles angle wrapping correctly.
 *
 * @param pValue Pointer to the input short integer angle variable.
 * @param target Target angle to approach.
 * @param fraction Fraction to use in the step size calculation.
 * @param maxStep Maximum allowed step size.
 * @param minStep Minimum allowed step size.
 * @return The difference between the updated input variable angle and the target angle.
 */
extern s16 add_calc_short_angle3(s16* pValue, s16 target, f32 fraction,
                                 s16 maxStep, s16 minStep) {
  f32 stepSize;
  s32 uTarget;
  s32 newValue;
  s32 uValue;

  if (target != *pValue) {
    uValue = (u16)*pValue;
    uTarget = (u16)target;

    if (uValue > uTarget) {
      uTarget += 65536; /* Add 360 short degrees */
    }

    stepSize = (uTarget - uValue) * fraction;

    if (stepSize > maxStep) {
      stepSize = maxStep;
    } else if (stepSize < minStep) {
      stepSize = minStep;
    }

    newValue = uValue + (s32)stepSize;
    if (newValue > uTarget) {
      newValue = uTarget;
    }
    *pValue = newValue;
  }

  return target - *pValue;
}

/**
 * @brief Move the RGBA color value from a source to a destination variable.
 *
 * This function copies the RGBA color value from the source variable to the destination variable.
 *
 * @param dest Pointer to the destination rgba_t variable.
 * @param src Pointer to the source rgba_t variable.
 */
extern void rgba_t_move(rgba_t* dest, const rgba_t* const src) {
  dest->r = src->r;
  dest->g = src->g;
  dest->b = src->b;
  dest->a = src->a;
}

/**
 * @brief A function that always returns 0.
 *
 * This function returns 0 without performing any operations.
 *
 * @return 0
 */
extern int none_proc1() { return 0; }

/**
 * @brief A function that performs no operation.
 *
 * This function performs no operation, serving as a placeholder
 * or no-op function.
 *
 * @param actor Pointer to an ACTOR structure.
 * @param game Pointer to a GAME structure.
 */
extern void none_proc2(ACTOR* actor, GAME* game) {}

/**
 * @brief Check if the game is in pause state.
 *
 * This function checks if the game is in the pause state and returns the result.
 *
 * @param play Pointer to a GAME_PLAY structure.
 * @return TRUE if the game is in pause state, FALSE otherwise.
 */
extern int _Game_play_isPause(GAME_PLAY* play) { return (play->isPause != 0); }

/**
 * @brief Calculate a percentage with respect to minimum and maximum values, and apply scaling.
 *
 * This function calculates a percentage with respect to given minimum and maximum values.
 * The percentage is then scaled by the provided scale factor. If shift_by_min is set,
 * the percentage is shifted by the minimum value.
 *
 * @param x Input value to check.
 * @param min Minimum value for the range.
 * @param max Maximum value for the range.
 * @param scale Scaling factor to apply to the percentage.
 * @param shift_by_min Flag to shift the percentage by the minimum value (1 to shift, 0 not to shift).
 * @return Scaled percentage of the input value within the specified range.
 */
extern f32 check_percent_abs(f32 x, f32 min, f32 max, f32 scale,
                             s32 shift_by_min) {
  if ((-min <= x) && (x <= min)) {
    return 0.0f;
  }
  if (x >= max) {
    return 1.0f;
  }
  if (x <= -max) {
    return -1.0f;
  }
  if (shift_by_min) {
    if (x > 0.0f) {
      return (x - min) * scale;
    } else {
      return (x + min) * scale;
    }
  } else {
    return x * scale;
  }
}

/**
 * @brief Calculate the percentage of completion based on acceleration and braking values.
 *
 * This function calculates the percentage of completion using the current position, start and end positions,
 * acceleration and braking distances.
 *
 * @param now Current position value.
 * @param start Start position value.
 * @param end End position value.
 * @param accelerate Acceleration distance.
 * @param brake Braking distance.
 * @return Percentage of completion.
 */
extern f32 get_percent_forAccelBrake(f32 now, f32 start, f32 end,
                                     f32 accelerate, f32 brake) {
  f32 percent;
  f32 total_delta;
  f32 now_delta;
  f32 step;

  if (now >= end) {
    return 1.0f;
  }
  if (now <= start) {
    return 0.0f;
  }
  total_delta = end - start;
  now_delta = now - start;
  if (total_delta < (accelerate + brake)) {
    return 0.0f;
  }

  step = 1.0f / (((2.0f * total_delta) - accelerate) - brake);
  if (accelerate != 0.0f) {
    if (now_delta <= accelerate) {
      percent = (now_delta * (step * now_delta));
      percent /= accelerate;
      return percent;
    }
    percent = step * accelerate;
  } else {
    percent = 0.0f;
  }
  if (now_delta <= (total_delta - brake)) {
    percent += (step * 2.0f) * (now_delta - accelerate);
    return percent;
  }
  percent += (2.0f * step * ((total_delta - accelerate) - brake));
  if (brake != 0.0f) {
    percent += step * brake;
    if (now_delta < total_delta) {
      f32 diff = total_delta - now_delta;
      percent -= step * diff * diff / brake;
    }
  }
  return percent;
}

/**
 * @brief Project a 3D world position onto a 2D screen position.
 *
 * This function projects a 3D world position onto a 2D screen position using the provided
 * game play matrix.
 *
 * @param play Pointer to a GAME_PLAY structure.
 * @param wpos Pointer to the 3D world position (xyz_t).
 * @param screen_pos Pointer to the resulting 2D screen position (xyz_t).
 */
extern void Game_play_Projection_Trans(GAME_PLAY* play, xyz_t* wpos,
                                       xyz_t* screen_pos) {
  f32 w;

  Matrix_mult(&play->matrix, 0);
  Matrix_Position(wpos, screen_pos);
  w = play->matrix.ww +
      ((play->matrix.wx * wpos->x) +
       (play->matrix.wy * wpos->y) +
       (play->matrix.wz * wpos->z));
  screen_pos->x = (SCREEN_WIDTH_F / 2.0f) + ((screen_pos->x / w) * (SCREEN_WIDTH_F / 2.0f));
  screen_pos->y = (SCREEN_HEIGHT_F / 2.0f) - ((screen_pos->y / w) * (SCREEN_HEIGHT_F / 2.0f));
}

/**
 * @brief Calculate the percentage of the input value within the specified range.
 *
 * This function calculates the percentage of the input value within the specified range.
 * The range is defined by the minimum and maximum integer values.
 *
 * @param max Maximum value for the range.
 * @param min Minimum value for the range.
 * @param x Input value to check.
 * @return Percentage of the input value within the specified range.
 */
extern f32 get_percent(int max, int min, int x) {
  f32 check;
  f32 percent;

  percent = 1.0f;
  if (x < min) {
    percent = 0.0f;
  } else if (x < max) {
    check = (f32)(max - min);
    if (check != 0.0f) {
      percent = (f32)(x - min) / check;
      if (percent > 1.0f) {
        percent = 1.0f;
      }
    }
  }
  return percent;
}
