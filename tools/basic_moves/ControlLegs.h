#ifndef H_CONTROL
#define H_CONTROL

#include <Arduino.h>

// sets the positions of the hip-servos to the respective positions
// the values are raw-values as excpeted ba pws.setPWM
void knees_raw(int raw_front_left, int raw_front_right, int raw_rear_left, int raw_rear_right);

// sets the positions of the shoulder-servos to the respective positions
// the values are raw-values as excpeted ba pws.setPWM
void hips_raw(int raw_front_left, int raw_front_right, int raw_rear_left, int raw_rear_right);

// sets the positions for the knee-servos to the desired positions
// this are relative positions mapped to the raw ones accordingly
// the position range goes from REL_MIN..REL_MAX: 
// REL_MIN=leg fully down, REL_MAX=leg fully up
void knees_pos(int pos_front_left, int pos_front_right, int pos_rear_left, int pos_rear_right); 

// todo //--------------

// sets the positions for the hip-servos to the desired positions
// this are relative positions mapped to the raw ones accordingly
// the position range goes from REL_MIN..REL_MAX: 
// REL_MIN=leg fully down, REL_MAX=leg fully up
void hips_pos(int pos_front_left, int pos_front_right, int pos_rear_left, int pos_rear_right); 

// sets the legs to the base position (bot standing straight)
void base_pos();

// sets the leg positions so that bot lies flat down on ground
void flat_pos();

// sets the leg positions so that bot stands on it's toe tips
void toe_tips_pos();

// 


#endif // H_CONTROL
