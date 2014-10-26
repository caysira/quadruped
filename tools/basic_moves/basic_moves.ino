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
#define S_FL 5    // hip front left
#define S_FR 7    // hip front right
#define S_RL 3    // hip rear left
#define S_RR 1    // hip rear right
// hips base position
#define B_S_FL 270    
#define B_S_FR 290     
#define B_S_RL 270     
#define B_S_RR 210 

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(9600);
  Serial.println("Q-Bot basic positioning");
  Serial.println("=======================");
  pwm.begin();
  pwm.setPWMFreq(50); // Analog servos run at ~50 Hz updates (20ms PWM period)
}

void knees(int fl, int fr, int rl, int rr) {
  pwm.setPWM(K_FL, 0, fl);
  pwm.setPWM(K_FR, 0, fr);
  pwm.setPWM(K_RL, 0, rl);
  pwm.setPWM(K_RR, 0, rr);
}

void shoulders(int fl, int fr, int rl, int rr) {
  pwm.setPWM(S_FL, 0, fl);
  pwm.setPWM(S_FR, 0, fr);
  pwm.setPWM(S_RL, 0, rl);
  pwm.setPWM(S_RR, 0, rr);
}

void loop() {
  
  delay(3000);
  
  // base position
  shoulders(B_S_FL, B_S_FR, B_S_RL, B_S_RR);
  delay(200);
  knees(B_K_FL, B_K_FR, B_K_RL, B_K_RR);
  delay(3000);
  
  // lie down
  knees(F_K_FL, F_K_FR, F_K_RL, F_K_RR);
  delay(3000);
  
  // feet in the air
  knees(U_K_FL, U_K_FR, U_K_RL, U_K_RR);
  delay(3000);

  // lie down
  knees(F_K_FL, F_K_FR, F_K_RL, F_K_RR);
  delay(3000);

  // base position
  knees(B_K_FL, B_K_FR, B_K_RL, B_K_RR);
  delay(3000);

  // I am frightened
  knees(D_K_FL, D_K_FR, D_K_RL, D_K_RR);
  delay(3000);
  
}

