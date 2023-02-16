// Include library ServoEasing by Armin Joachimsmeyer
#include "ServoEasing.hpp"

ServoEasing Servo1;
const int motor1_pin = 10;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Servo1.attach(motor1_pin, 30);

    // Wait for servo to reach start position.
    delay(500);
}

void loop() {

	// Starting moving to 160 degrees over a period of 2 seconds
	Servo1.startEaseToD(160, 2000);

	while (Servo1.isMoving()) {
		// While the Servo is moving, blink the LED
		blinkLED();
	}

	// Wait 1 second after we get there then turn off LED
	delay(1000);
	digitalWrite(LED_BUILTIN, LOW);

	// Starting moving back to 30 degree at speed = 25 degrees / second
	Servo1.startEaseTo(30, 25);
  
	while (Servo1.getCurrentAngle() > 100) {
		// Wait whilst angle is more than 100 degrees
	}

	// Turn on LED
	digitalWrite(LED_BUILTIN, HIGH);

	while (Servo1.isMoving()) {
		// Wait until Servo finishes moving
	}

	// Wait 1 second after we get there
	delay(1000);
}

// Helper function to blink LED
void blinkLED() {
	digitalWrite(LED_BUILTIN, HIGH);
	delay(100);
	digitalWrite(LED_BUILTIN, LOW);
	delay(100);
}
