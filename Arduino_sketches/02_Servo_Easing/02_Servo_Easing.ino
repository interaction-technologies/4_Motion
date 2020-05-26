#include <Servo.h>
#include <FastLED.h>

// Include the Ease.h file
#include "Ease.h"

// Setup motor object
Servo motor1;
const int motor1_pin = 10;

// Create a new ease with CUBIC_IN as the profile
Ease custom_ease(CUBIC_OUT);

void setup() {
   motor1.attach(motor1_pin);
}

const int sweep_duration = 2; // How many seconds for the sweep
int sweep_direction = 1;      // Are we heading CW or CCW
float progress = 0;           // Holder for progress counter, goes from 0->1

void loop() {

   EVERY_N_MILLIS(20){ // 20ms = updates 50 times per second

      // Use ease.y() to convert linear value to eased value
      // (x*160)+10 scales the value from 0->1 to 10->170
      motor1.write((custom_ease.y(progress)*160)+10);

      // Increment the position, based on 20ms steps and the sweep_duration
      progress = progress + (0.02/sweep_duration)*sweep_direction;

      // If we get to the start or end of progress, swap the direction
      if((progress >= 1) ||(progress <= 0)){
         sweep_direction *= -1;
      }
   }
}
