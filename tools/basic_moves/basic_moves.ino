//  do some basic positioning of the q-bot using the definitions and basic functions

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "ServoDefinitions.h"
#include "ControlLegs.h"

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(9600);
  Serial.println("Q-Bot basic positioning");
  Serial.println("=======================");
  pwm.begin();
  pwm.setPWMFreq(50); // Analog servos run at ~50 Hz updates (20ms PWM period)
}

void loop() {
  
  delay(2000); // always a good idea to wait a moment ;-)
  // then go to start position
  hips_raw(POS_BASE_HIP_FRONT_LEFT, POS_BASE_HIP_FRONT_RIGHT, POS_BASE_HIP_REAR_LEFT, POS_BASE_HIP_REAR_RIGHT); 
  knees_raw(POS_BASE_KNEE_FRONT_LEFT, POS_BASE_KNEE_FRONT_RIGHT, POS_BASE_KNEE_REAR_LEFT, POS_BASE_KNEE_REAR_RIGHT);
  delay(2000);
  
  // now let's try the relative positioning
  // robot should lie down flat slowly, starting from base position
  int pos_inc = 0;
  while ((POS_REL_BASE_KNEE_FRONT_LEFT + pos_inc) <= REL_MAX) {
    knees_pos(POS_REL_BASE_KNEE_FRONT_LEFT + pos_inc, 
              POS_REL_BASE_KNEE_FRONT_RIGHT + pos_inc, 
              POS_REL_BASE_KNEE_REAR_LEFT + pos_inc, 
              POS_REL_BASE_KNEE_REAR_RIGHT + pos_inc);
    delay(100); // give the servo some time to act
    pos_inc++;
  }
  
  // so now get up again do basis position
  int pos_dec = 0;
  while ((REL_MAX - pos_dec) >= POS_REL_BASE_KNEE_FRONT_LEFT) {
    knees_pos(REL_MAX - pos_dec,
              REL_MAX - pos_dec,
              REL_MAX - pos_dec,
              REL_MAX - pos_dec);
    delay(100); // give the servo some time to act
    pos_dec++;
  }
    
//  delay(3000);
//  // base position
//  shoulders_raw(B_S_FL, B_S_FR, B_S_RL, B_S_RR);
//  delay(200);
//  hips_raw(B_K_FL, B_K_FR, B_K_RL, B_K_RR);
//  delay(3000);  
//  // lie down
//  knees(F_K_FL, F_K_FR, F_K_RL, F_K_RR);
//  delay(3000);
//  
//  // feet in the air
//  knees(U_K_FL, U_K_FR, U_K_RL, U_K_RR);
//  delay(3000);
//
//  // lie down
//  knees(F_K_FL, F_K_FR, F_K_RL, F_K_RR);
//  delay(3000);
//
//  // base position
//  knees(B_K_FL, B_K_FR, B_K_RL, B_K_RR);
//  delay(3000);
//
//  // I am frightened
//  knees(D_K_FL, D_K_FR, D_K_RL, D_K_RR);
//  delay(3000);
  
}

