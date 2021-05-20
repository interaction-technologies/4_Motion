#include <Servo.h>

// Include FastLED and Bounce2 libraries
#include <FastLED.h>
#include <Bounce2.h>

// Include the Ease.h file
#include "Ease.h"

// Setup motor
Servo motor1;
const int motor1_pin = 10;

// Variables to log the intended motion
uint8_t   start_pos = 0;
uint8_t   target_pos = 0; 
uint32_t  start_time = 0;
uint32_t  move_time  = 1500;

// Our easing object
// The second parameter can be used to change the way the ease looks
// See graphs here for an example: https://www.desmos.com/calculator/ctcmqijlpi
Ease custom_ease(ELASTIC_OUT, 50);

Bounce debouncer = Bounce();
const int button_pin = 3;

void setup() {
   motor1.attach(motor1_pin);
   debouncer.attach(button_pin,INPUT_PULLUP);
}

void loop() {
   
   // This is our updater for the motor position
   EVERY_N_MILLIS(16){
      if(millis() > start_time+move_time){
         // If we are beyond the finish time, then write the end position   
         motor1.write(target_pos); 
      }else if(millis() < start_time){
         // If we are before the start time, then write the start position
         motor1.write(start_pos); 
      }else{
         // Otherwise we should be moving!

         // Calculate what % through the movement we are
         double progress = ((double)millis()-start_time)/(move_time);

         // Use this progress to calculate the current position, and write that to motor
         double new_value = custom_ease.y(progress)*(target_pos - start_pos) + start_pos;
         motor1.write(new_value);
      }
   }

   // This is our button checker
   EVERY_N_MILLIS(5){
      debouncer.update();
      if(debouncer.rose()){ 
         // Set the movement to move:
         //  - FROM current position
         //  - TO a random position
         start_pos = motor1.read();
         target_pos = random(140)+20; // Pick target between 20->160
         start_time = millis();
      }
   }
}
