// Create variables for pins
const int stretch_pin = A5;

// Set max and min levels for stretch detection
const int min_level = 400;
const int max_level = 600;

void setup() {
	Serial.begin(9600);
}

void loop() {

	// Read in stretch sensor value
	int stretch_reading = analogRead(pot_pin);

	// Constrain reading so that it doesn't exceed bounds
	stretch_reading = constrain(stretch_reading, min_level, max_level);

	// Map the stretch sensor to the servo motor range (10 -> 170)
	int motor_pos = map(stretch_reading, min_level, max_level, 10, 170);

	// Review this data in serial monitor/plotter
	Serial.print("Stretch:");
	Serial.print(stretch_reading);
	Serial.print(", Motor:");
	Serial.println(motor_pos);

	delay(50);
}