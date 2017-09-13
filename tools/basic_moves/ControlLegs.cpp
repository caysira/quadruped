#include <Arduino.h>
#include "ServoDefinitions.h"
#include "ControlLegs.h"

//------------------------------------------------------------------------------------------
void knees_raw(int raw_front_left,
               int raw_front_right,
               int raw_rear_left,
               int raw_rear_right) {  
  
  pwm.setPWM(KNEE_FRONT_LEFT, 0, raw_front_left);  
  pwm.setPWM(KNEE_FRONT_RIGHT, 0, raw_front_right);  
  pwm.setPWM(KNEE_REAR_LEFT, 0, raw_rear_left);  
  pwm.setPWM(KNEE_REAR_RIGHT, 0, raw_rear_right);
}

//------------------------------------------------------------------------------------------
void hips_raw(int raw_front_left,
              int raw_front_right,
              int raw_rear_left,
              int raw_rear_right) {  
  
  pwm.setPWM(HIP_FRONT_LEFT, 0, raw_front_left);  
  pwm.setPWM(HIP_FRONT_RIGHT, 0, raw_front_right);  
  pwm.setPWM(HIP_REAR_LEFT, 0, raw_rear_left);  
  pwm.setPWM(HIP_REAR_RIGHT, 0, raw_rear_right);
}

//------------------------------------------------------------------------------------------
void knees_pos(int pos_front_left,
               int pos_front_right,
               int pos_rear_left,
               int pos_rear_right) {

  int raw_front_left, raw_front_right, raw_rear_left, raw_rear_right;
  
  // map positions values to raw values for pwm.setPWM  
  raw_front_left = map(pos_front_left, REL_MIN, REL_MAX, POS_DOWN_KNEE_FRONT_LEFT, POS_UP_KNEE_FRONT_LEFT);  
  raw_front_right = map(pos_front_right, REL_MIN, REL_MAX, POS_DOWN_KNEE_FRONT_RIGHT, POS_UP_KNEE_FRONT_RIGHT);  
  raw_rear_left = map(pos_rear_left, REL_MIN, REL_MAX, POS_DOWN_KNEE_REAR_LEFT, POS_UP_KNEE_REAR_LEFT);  
  raw_rear_right = map(pos_rear_right, REL_MIN, REL_MAX, POS_DOWN_KNEE_REAR_RIGHT, POS_UP_KNEE_REAR_RIGHT);    
  
  // set servos to desired positions  
  knees_raw(raw_front_left, raw_front_right, raw_rear_left, raw_rear_right);  
}
