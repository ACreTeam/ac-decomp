#include "m_controller.h"
#include "game.h"
#include "m_lib.h"
#include "m_event.h"
#include "MSL_C/w_math.h"
#include "sys_math.h"

/**
 * @brief Constructor for MCON.
 **/
extern void mCon_ct() { }

/**
 * @brief Destructor for MCON.
 **/
extern void mCon_dt() { }

/**
 * @brief Controller input processing function.
 * Only processes port 1 controller.
 * 
 * @param mcon Pointer to MCON struct which will be updated
 * @param stick_x Joystick X position
 * @param stick_y Joystick Y position
 **/
extern void mCon_calc(MCON* mcon, f32 stick_x, f32 stick_y) {
  f32 t;

  mcon->last_move_pX = mcon->move_pX;
  mcon->last_move_pY = mcon->move_pY;
  mcon->last_move_pR = mcon->move_pR;
  mcon->last_move_angle = mcon->move_angle;

  mcon->last_adjusted_pX = mcon->adjusted_pX;
  mcon->last_adjusted_pY = mcon->adjusted_pY;
  mcon->last_adjusted_pR = mcon->adjusted_pR;

  t = sqrtf(stick_x * stick_x + stick_y * stick_y);

  if (t <= STICK_MIN) {
    mcon->move_pX = 0.0f;
    mcon->move_pY = 0.0f;
    mcon->move_pR = 0.0f;

    mcon->adjusted_pX = 0.0f;
    mcon->adjusted_pY = 0.0f;
    mcon->adjusted_pR = 0.0f;
  }
  else {
    s16 stick_angle = atans_table(stick_x, stick_y);
    if (t > STICK_MAX) {
      stick_x = cos_s(stick_angle) * STICK_MAX;
      stick_y = sin_s(stick_angle) * STICK_MAX;
      t = STICK_MAX;
    }

    mcon->move_angle = stick_angle;
    mcon->move_pX = check_percent_abs(stick_x, STICK_MIN, STICK_MAX, STICK_UNCORRECTED_SCALE, 0);
    mcon->move_pY = check_percent_abs(stick_y, STICK_MIN, STICK_MAX, STICK_UNCORRECTED_SCALE, 0);
    mcon->move_pR = check_percent_abs(      t, STICK_MIN, STICK_MAX, STICK_UNCORRECTED_SCALE, 0);

    mcon->adjusted_pX = check_percent_abs(stick_x, STICK_MIN, STICK_MAX, STICK_CORRECTED_SCALE, 1);
    mcon->adjusted_pY = check_percent_abs(stick_y, STICK_MIN, STICK_MAX, STICK_CORRECTED_SCALE, 1);
    mcon->adjusted_pR = check_percent_abs(      t, STICK_MIN, STICK_MAX, STICK_CORRECTED_SCALE, 1);
  }
}

/**
 * @brief Controller main process.
 * 
 * @param game Pointer to current GAME structure
 **/
extern void mCon_main(GAME* game) {
  f32 stick_x = getJoystick_X();
  f32 stick_y = getJoystick_Y();

  mCon_calc(&game->mcon, stick_x, stick_y);
}

/**
 * @brief Checks if a specific button combination currently pressed.
 * 
 * @param mask Button combination to check
 * @return TRUE when the button combination is pressed, FALSE otherwise
 **/
extern int chkButton(u16 mask) {
  if (mEv_IsTitleDemo()) {
    return FALSE;
  }

  return (mask & (gamePT->pads[0].now.button)) == mask;
}

/**
 * @brief Gets the currently pressed buttons.
 * 
 * @return Pressed buttons
 **/
extern u16 getButton() {
  if (mEv_IsTitleDemo()) {
    return BUTTON_NONE;
  }

  return gamePT->pads[0].now.button;
}

/**
 * @brief Checks if a specific button combination was pressed this frame.
 * 
 * @param mask Button combination to check
 * @return TRUE when the button combination was pressed this frame, FALSE otherwise
 **/
extern int chkTrigger(u16 mask) {
  if (mEv_IsTitleDemo()) {
    return FALSE;
  }

  return (mask & (gamePT->pads[0].on.button)) == mask;
}

/**
 * @brief Gets the buttons pressed on the current frame.
 * 
 * @return Buttons pressed on the current frame
 **/
extern u16 getTrigger() {
  if (mEv_IsTitleDemo()) {
    return BUTTON_NONE;
  }

  return gamePT->pads[0].on.button;
}

/**
 * @brief Gets the current joystick X position.
 * 
 * @return Joystick X position
 **/
extern int getJoystick_X() {
  if (mEv_IsTitleDemo()) {
    return 0;
  }

  return gamePT->pads[0].now.stick_x;
}

/**
 * @brief Gets the current joystick Y position.
 * 
 * @return Joystick Y position
 **/
extern int getJoystick_Y() {
  if (mEv_IsTitleDemo()) {
    return 0;
  }

  return gamePT->pads[0].now.stick_y;
}
