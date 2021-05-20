#include <WiFi.h>
#include <HTTPClient.h>

// Install the "Arduino_JSON" library by Arduino  
#include <Arduino_JSON.h>

// Install the "ESP32Servo" library by Kevin Harrington, John K. Bennett
#include <ESP32Servo.h>

// Your Wifi name and password
const char* ssid = "your_wifi_network_name";
const char* password = "your_wifi_password!";

Servo motor1;      // Create Servo reference
int servoPin = 18; // Pin for Servo connection (G18)

// Array of servo positions for each value on the scale
// Hopefully no more than 7 people in space at once!
int positions[8] = {140,120,100,80,60,40,20,0};

void setup() {
   Serial.begin(115200);
   
   // Begin servo motor
   motor1.attach(servoPin);
   motor1.write(180);

   // Begin Wifi connection and wait until connected
   WiFi.begin(ssid, password);
   Serial.println("Connecting");
   while(WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
   }
   Serial.println("");
   Serial.print("Connected to WiFi network with IP Address: ");
   Serial.println(WiFi.localIP());
}

void loop() {
   // If we are connected
   if(WiFi.status()== WL_CONNECTED){

      // Create a new GET request to the API address
      HTTPClient http;
      http.begin("http://api.open-notify.org/astros.json"); 
      int httpResponseCode = http.GET();

      if(httpResponseCode<=0){
         Serial.print("Error finding page: ");
         Serial.println(httpResponseCode);
      }else{
         // If we get a response, save the string of data
         Serial.print("HTTP Response code: ");
         Serial.println(httpResponseCode);
         String payload = http.getString();

         // Print the returned text
         Serial.print("Response data: ");
         Serial.println(payload);
  
         // Try to convert the response text to JSON
         JSONVar space_data = JSON.parse(payload.c_str());
         if (JSON.typeof(space_data) == "undefined") {
            Serial.println("Failed to parse JSON!");
         }else{
            // If it was possible, try to get the number of people in space
            Serial.print("Number of people in space: ");
            int num_in_space = space_data["number"];
            Serial.println(num_in_space);

            // Convert this number to a position in the positions[] array
            // Constrain keeps the number between 0 and 7 (that was all my scale had)
            motor1.write(positions[constrain(num_in_space,0,7)]);
         }
      }
      http.end(); // End the HTTP connection
   }

  // Wait 1 minute between requests
  delay(60*1000);
}
