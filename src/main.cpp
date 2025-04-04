#include <Arduino.h>
#include <Servo.h>

Servo servo1;
Servo servo2;

int potPin = A0; // Analog pin connected to the potentiometer
int potValue;    // Variable to store the potentiometer value (0 to 1023)
int angle;       // Variable to store the servo angle (0 to 90 degrees)

void setup()
{
  servo1.attach(9);   // Servo 1 connected to pin 9
  servo2.attach(10);  // Servo 2 connected to pin 10
  Serial.begin(9600); // Initialize serial communication for debugging
  Serial.println("Servo Control Initialized");
  Serial.println("Potentiometer Value: ");
  Serial.println(potValue);
}

void loop()
{
  potValue = analogRead(potPin);         // Read the potentiometer value
  angle = map(potValue, 0, 1023, 0, 90); // Map the value to a range of 0 to 90 degrees

  Serial.println("Potentiometer Value: ");
  Serial.print(potValue);

  delay(20); // Short delay to allow the servos to reach the desired angle
}
