// Include library ServoEasing by Armin Joachimsmeyer
#include "ServoEasing.hpp"

// Create new easing servo
ServoEasing motor1;
const int motor1_pin = 10;

void setup() {

	// Set the easing type we want
	motor1.setEasingType(EASE_CIRCULAR_OUT);

	// Attach the servo motor to the pin
	// Second paramter is the starting angle we want (90 degrees)
	motor1.attach(motor1_pin, 90);
	delay(300);
	
}

void loop() {
	// Move the servo to 30 degrees, speed of 60 degrees per second
	motor1.easeTo(30, 60);

	// Move the servo to 140 degrees, speed of 60 degrees per second
	motor1.easeTo(140, 60);
}

