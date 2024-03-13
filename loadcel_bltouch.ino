#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;

// INPUT_PIN: specific pin number that you're using to receive the control signal
// from the 3D printer controller. This pin will be used to detect when the 3D printer
// sends a signal to deploy or stow the BL-Touch probe, triggering the load cell to
// reset its baseline (tare) or start measuring for touch detection.
const int INPUT_PIN = 4; // Example pin for receiving control signals

// OUTPUT_PIN: digital pin configured as an output to send a signal to the printer's
// controller when the load cell detects a touch (i.e., when the nozzle comes into contact
// with the bed). This mimics the BLTouch's behavior of signaling bed contact
const int OUTPUT_PIN = 5; // Example pin for signaling touch detection to the printer

HX711 scale;

void setup() {
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.tare(); // Resets to 0 with no weight on it at startup
  
  pinMode(INPUT_PIN, INPUT); // Set the control signal pin as input
  pinMode(OUTPUT_PIN, OUTPUT); // Set the touch detection signal pin as output
}

void loop() {
  // Check for control signal to deploy/stow probe
  if(digitalRead(INPUT_PIN) == HIGH) { // Assuming HIGH signal for deploy
    scale.tare(); // Reset scale to 0 to recalibrate for current position
  }

  // Read and filter the scale value to detect touch sensitivity and 
  // manage potential bed crashes. 
  float reading = getFilteredReading();

  // Assuming a threshold for touch detection; adjust based on the setup's sensitivity
  float touchThreshold = -0.05; // This is an example threshold. To determine the correct value through testing.


  // Detect touch - if reading goes below threshold, it indicates a touch
  if (touchThreshold < 0) {
    // Touch detected, send signal
    // This part depends on how you wish to signal the main controller,
    // For example, by setting a pin HIGH briefly
    digitalWrite(OUTPUT_PIN, HIGH);
    delay(10); // Short pulse to mimic BLTouch signal
    digitalWrite(OUTPUT_PIN, LOW); // Reset signal
  }
  
  // For debugging: output the reading to the serial monitor
  Serial.print("Filtered Reading: ");
  Serial.println(reading);

  delay(100); // Adjust based on tests for responsiveness vs. performance
}

float getFilteredReading() {
  // Setup for a simple moving average filter
  const int numReadings = 10; // Adjust the number of readings to balance smoothness and responsiveness
  static float readings[numReadings]; // Array to store readings
  static int readIndex = 0; // Current position in array
  static float total = 0; // Sum of readings
  static float average = 0; // Average of readings

  total = total - readings[readIndex]; // Subtract the oldest reading and add the newest
  readings[readIndex] = scale.get_units(); // Read from the sensor
  total = total + readings[readIndex]; // Add the reading to the total
  readIndex = (readIndex + 1) % numReadings; // Circular buffer

  average = total / numReadings; // Calculate the average
  return average; // Return the filtered reading
  }
