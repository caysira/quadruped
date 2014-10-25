//  Arduino sketch for servo calibration (min/max positions)
//  for usage with Adafruit ServoShield-Library (12 bit pwm)
//
//  the user should enter servo number (0-15) and 
//  position (pwm-high duration 0..4096)

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(9600);
  Serial.println("Servo position calibration");
  Serial.println("==========================");
  pwm.begin();
  pwm.setPWMFreq(60); // Analog servos run at ~50 Hz updates (20ms PWM period)
}

void loop() {

  // servo number
  uint8_t servonum = 0;
  
  // length of pulse (0..4096)
  uint16_t pulselen = 0;
  
  // read servo number from serial
  Serial.println();
  Serial.print("Enter servo number (0-15): ");
  while (!Serial.available()) {}  // wait until data entered
  servonum = Serial.parseInt();
  Serial.println(servonum);
    
  // read position value from serial
  Serial.print("Enter pulse length (0..4096): ");
  while (!Serial.available()) {}    
  pulselen = Serial.parseInt();
  Serial.println(pulselen);
    
  // set desired pulse length
  pwm.setPWM(servonum, 0, pulselen);
  
}

