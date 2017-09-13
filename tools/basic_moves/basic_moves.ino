//  with the values from servo calibration
//  do some basic positioning of the q-bot then
// the "knee" servos are numbers 2, 4, 6, 8
// the "hip" servos are numbers 1, 3, 5, 7

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include ServoDefinitions.h

// define servo names for "knees"
#define KNEE_FRONT_LEFT 6
#define KNEE_FRONT_RIGHT 8
#define KNEE_REAR_LEFT 4
#define KNEE_REAR_RIGHT 2

// knees up positions
#define POS_UP_KNEE_FRONT_LEFT 110    
#define POS_UP_KNEE_FRONT_RIGHT 450    
#define POS_UP_KNEE_REAR_LEFT 110    
#define POS_UP_KNEE_REAR_RIGHT 450    

// knees flat positions
#define POS_FLAT_KNEE_FRONT_LEFT 180   
#define POS_FLAT_KNEE_FRONT_REAR 370     
#define POS_FLAT_KNEE_REAR_LEFT 180     
#define POS_FLAT_KNEE_REAR_RIGHT 370

// knees down positions
#define POS_DOWN_KNEE_FRONT_LEFT 430    
#define POS_DOWN_KNEE_FRONT_RIGHT 140     
#define POS_DOWN_KNEE_REAR_LEFT 430     
#define POS_DOWN_KNEE_REAR_RIGHT 140     

// knees base positions (also initial starting position)
#define POS_BASE_KNEE_FRONT_LEFT 330    
#define POS_BASE_KNEE_FRONT_RIGHT 230     
#define POS_BASE_KNEE_REAR_LEFT 330     
#define POS_BASE_KNEE_REAR_RIGHT 230     

// define servo names for "hips"
#define HIP_FRONT_LEFT 5
#define HIP_FRONT_RIGHT 7
#define HIP_REAR_LEFT 3
#define HIP_REAR_RIGHT 1

// hips base position
#define POS_BASE_HIP_FRONT_LEFT 270    
#define POS_BASE_HIP_FRON_REAR 290     
#define POS_BASE_HIP_REAR_LEFT 270     
#define POS_BASE_HIP_REAR_RIGHT 210 

// define min/max value (resolution) for relative positioning
#define REL_MIN 0
#define REL_MAX 100

// relative position values of base position for knees
#define POS_REL_BASE_KNEE_FRONT_LEFT 31
#define POS_REL_BASE_KNEE_FRONT_REAR 29
#define POS_REL_BASE_KNEE_REAR_LEFT 31
#define POS_REL_BASE_KNEE_REAR_RIGHT 29

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(9600);
  Serial.println("Q-Bot basic positioning");
  Serial.println("=======================");
  pwm.begin();
  pwm.setPWMFreq(50); // Analog servos run at ~50 Hz updates (20ms PWM period)
}

// sets the positions of the hip-servos to the respective positions
// the values are raw-values as excpeted ba pws.setPWM
void knees_raw(int raw_front_left,
               int raw_front_right,
               int raw_rear_left,
               int raw_rear_right) {
  pwm.setPWM(KNEE_FRONT_LEFT, 0, raw_front_left);
  pwm.setPWM(KNEE_FRONT_RIGHT, 0, raw_front_right);
  pwm.setPWM(KNEE_REAR_LEFT, 0, raw_rear_left);
  pwm.setPWM(KNEE_REAR_RIGHT, 0, raw_rear_right);
}

// sets the positions of the shoulder-servos to the respective positions
// the values are raw-values as excpeted ba pws.setPWM
void hips_raw(int raw_front_left,
              int raw_front_right,
              int raw_rear_left,
              int raw_rear_right) {
  pwm.setPWM(HIP_FRONT_LEFT, 0, raw_front_left);
  pwm.setPWM(HIP_FRONT_RIGHT, 0, raw_front_right);
  pwm.setPWM(HIP_REAR_LEFT, 0, raw_rear_left);
  pwm.setPWM(HIP_REAR_RIGHT, 0, raw_rear_right);
}

// sets the positions for the hip-servos to the desired positions
// this are relative positions mapped to the raw ones accordingly
// the position range goes from REL_MIN..REL_MAX: 
// REL_MIN=leg fully down, REL_MAX=leg fully up
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

