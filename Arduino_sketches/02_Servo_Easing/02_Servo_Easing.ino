#include <Servo.h>

// Include the Ease.h file
#include "Ease.h"

// Setup motor object
Servo motor1;
const int motor1_pin = 10;

// Create a new ease with CUBIC_IN as the easing type
Ease my_ease(CUBIC_IN);

void setup() {
  motor1.attach(motor1_pin);
}

void loop() {

  // Count from 0->1 in 0.01 steps = 100 steps
  for(float i=0; i<=1; i+=0.01){
    // Use ease.y() to convert linear value to eased value
    float eased_value = my_ease.y(i);

    // (x*120)+30 scales the value from 0->1 to 30->150
    int motor_pos = (eased_value*120)+30;
    motor1.write(motor_pos);

    // 20ms delay x 100 steps = 2 seconds per movement
    delay(20);
  }

  // Count from 0->1 in 0.01 steps = 100 steps
  for(float i=0; i<=1; i+=0.01){
    // Use ease.y() to convert linear value to eased value
    float eased_value = my_ease.y(i);
    
    // (x*120)+30 scales the value from 0->1 to 30->150
    int motor_pos = (eased_value*120)+30;
    motor1.write(180 - motor_pos); // Subtract from 180 to go back the other way
    
    // 20ms delay x 100 steps = 2 seconds per movement
    delay(20);
  }
}
