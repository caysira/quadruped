/***************************************************
  Arduino sketch for servo calibration (min/max positions)
  for usage with Adafruit ServoShield-Library (12 bit pwm)
   
  the user should enter servo number (0-15) and 
  position (pwm-high duration 0..4096)
****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// our servo # counter
uint8_t servonum = 0;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Servo position calibration");
  Serial.println("==========================");
  pwm.begin();
  pwm.setPWMFreq(50); // Analog servos run at ~50 Hz updates (20ms PWM period)
}

void loop() 
{
  // todo:
  // read servo number from serial
  // read position value from serial
  // pwm.setPWM(servonum, 0, pulselen);
  // wait for keypress
}

