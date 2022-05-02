#include <Servo.h>

// Create Servo object
Servo motor1;
const int motor1_pin = 10;

void setup() {
   // Attach the servo motor to the pin
   motor1.attach(motor1_pin);
}

void loop() {
   // Sweep the motor from 10->170degs, 10ms step delay
   for(int i=10; i<170; i++){
      motor1.write(i);
      delay(10);
   }
   // Sweep the motor from 10->170degs, 50ms step delay
   for(int i=170; i>10; i--){
      motor1.write(i);
      delay(50);
   }
}
