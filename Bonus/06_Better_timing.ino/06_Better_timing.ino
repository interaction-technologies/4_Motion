#include <Servo.h>
#include <FastLED.h>

// Create Servp object
Servo motor1;
const int motor1_pin = 10;

void setup(){
	motor1.attach(motor1_pin);
}

// Variables to save current positions and step sizes
int motor1_step = 1;
int motor1_pos = 50;

void loop(){
	EVERY_N_MILLIS(25){
		motor1.write(motor1_pos);

		// If we reach the end, invert the direction of travel
		if((motor1_pos >= 170)||(motor1_pos <= 10)){
			motor1_step = -motor1_step;
		}

		// Every 25ms we increase the motor pos by the size of the step defined above
		motor1_pos = motor1_pos + motor1_step;
	}
}