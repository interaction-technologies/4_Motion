#include <Servo.h>
#include <Bounce2.h>

// Create Servo objects
Servo motor1;
Servo motor2;
const int motor1_pin = 10;
const int motor2_pin = 11;

// Create button to control movement
Bounce debouncer = Bounce();
const int button_pin = 3;

void setup() {
   // Attach motors and button debouncer
   motor1.attach(motor1_pin);
   motor2.attach(motor2_pin);
   debouncer.attach(button_pin,INPUT_PULLUP);
}

void loop() {
   // Update button value
   debouncer.update();

   // If button changed
   if(debouncer.rose()){
      // Move motors to a random position from 10->170 
      uint8_t pos = random(160)+10;
      motor1.write(pos);
      motor2.write(pos);
   }
}
