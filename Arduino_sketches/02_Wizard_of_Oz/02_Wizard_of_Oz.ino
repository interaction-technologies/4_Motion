#include <Servo.h>

// Create Servo object
Servo motor;

// Create variables for pins
const int motor_pin = 10;
const int pot_pin = A3;

void setup() {

	Serial.begin(9600);

	// Attach the servo motor to the pin
	motor.attach(motor_pin);
}

void loop() {

	// Convert the analog position of potentiometer to a motor position
	int pot_position = analogRead(pot_pin);
	int motor_position = map(pot_position,0, 1023, 10, 170);

	// Uncomment these lines if you want to see how the mapping works
	// Serial.print(pot_position);
	// Serial.print(" -> ");
	// Serial.println(motor_position);

	// Move the motor!
	motor.write(motor_position);
	delay(50);

}