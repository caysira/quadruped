//  with the values from servo calibration
//  do some basic positioning of the q-bot then
// the "knee" servos are numbers 2, 4, 6, 8
// the "hip" servos are numbers 1, 3, 5, 7

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// define servo names for "knees"
#define K_FL 6    // knee front left
#define K_FR 8    // knee front right
#define K_RL 4    // knee rear left
#define K_RR 2    // knee rear right
// knees up positions
#define U_K_FL 110    
#define U_K_FR 450    
#define U_K_RL 110    
#define U_K_RR 450    
// knees flat positions
#define F_K_FL 180   
#define F_K_FR 370     
#define F_K_RL 180     
#define F_K_RR 370     
// knees down positions
#define D_K_FL 430    
#define D_K_FR 140     
#define D_K_RL 430     
#define D_K_RR 140     
// knees base positions
#define B_K_FL 330    
#define B_K_FR 230     
#define B_K_RL 330     
#define B_K_RR 230     

// define servo names for "hips"
#define H_FL 5    // hip front left
#define H_FR 7    // hip front right
#define H_RL 3    // hip rear left
#define H_RR 1    // hip rear right
// hips base position
#define B_H_FL 270    
#define B_H_FR 290     
#define B_H_RL 270     
#define B_H_RR 210 

// define min/max value (resolution) for relative positioning
#define REL_MIN 0
#define REL_MAX 100

// relative position values of base position for knees
#define B_K_FL_REL 31
#define B_K_FR_REL 29
#define B_K_RL_REL 31
#define B_K_RR_REL 29

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
void knees_raw(int raw_fl, int raw_fr, int raw_rl, int raw_rr) {
  pwm.setPWM(K_FL, 0, raw_fl);
  pwm.setPWM(K_FR, 0, raw_fr);
  pwm.setPWM(K_RL, 0, raw_rl);
  pwm.setPWM(K_RR, 0, raw_rr);
}

// sets the positions of the shoulder-servos to the respective positions
// the values are raw-values as excpeted ba pws.setPWM
void hips_raw(int raw_fl, int raw_fr, int raw_rl, int raw_rr) {
  pwm.setPWM(H_FL, 0, raw_fl);
  pwm.setPWM(H_FR, 0, raw_fr);
  pwm.setPWM(H_RL, 0, raw_rl);
  pwm.setPWM(H_RR, 0, raw_rr);
}

// sets the positions for the hip-servos to the desired positions
// this are relative positions mapped to the raw ones accordingly
// the position range goes from REL_MIN..REL_MAX: 
// REL_MIN=leg fully down, REL_MAX=leg fully up
void knees_pos(int pos_fl, int pos_fr, int pos_rl, int pos_rr) {

  int r_fl, r_fr, r_rl, r_rr;
  
  // map positions values to raw values for pwm.setPWM
  r_fl = map(pos_fl, REL_MIN, REL_MAX, D_K_FL, U_K_FL);
  r_fr = map(pos_fr, REL_MIN, REL_MAX, D_K_FR, U_K_FR);
  r_rl = map(pos_rl, REL_MIN, REL_MAX, D_K_RL, U_K_RL);
  r_rr = map(pos_rr, REL_MIN, REL_MAX, D_K_RR, U_K_RR);
  
  // set servos to desired positions
  knees_raw(r_fl, r_fr, r_rl, r_rr);
  
}

void loop() {
  
  delay(2000); // always a good idea to wait a moment ;-)
  // then go to start position
  hips_raw(B_H_FL, B_H_FR, B_H_RL, B_H_RR); 
  knees_raw(B_K_FL, B_K_FR, B_K_RL, B_K_RR);
  delay(2000);
  
  // now let's try the relative positioning
  // robot should lie down flat slowly, starting from base position
  int pos_inc = 0;
  while ((B_K_FL_REL + pos_inc) <= REL_MAX) {
    knees_pos(B_K_FL_REL + pos_inc, 
              B_K_FR_REL + pos_inc, 
              B_K_RL_REL + pos_inc, 
              B_K_RR_REL + pos_inc);
    delay(100);
    pos_inc++;
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

