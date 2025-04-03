#include <Arduino.h>
#include <Servo.h> // Include the Servo library

Servo myServo; // Create a Servo object

const int led1 = 7; // LED 1 connected to pin 7
const int led2 = 8; // LED 2 connected to pin 8

void setup()
{
  myServo.attach(9); // Attach the servo to pin 9
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop()
{
  // Rotate clockwise at full speed
  myServo.write(180);       // Maximum speed clockwise
  digitalWrite(led1, HIGH); // Turn on LED 1
  digitalWrite(led2, LOW);  // Turn off LED 2
  delay(2000);              // Wait for 2 seconds

  // Stop the servo
  myServo.write(90);       // Neutral position (stops the servo)
  digitalWrite(led1, LOW); // Turn off LED 1
  digitalWrite(led2, LOW); // Turn off both LEDs
  delay(1000);             // Wait for 1 second

  // Rotate counterclockwise at full speed
  myServo.write(0);         // Maximum speed counterclockwise
  digitalWrite(led1, LOW);  // Turn off LED 1
  digitalWrite(led2, HIGH); // Turn on LED 2
  delay(2000);              // Wait for 2 seconds

  // Stop the servo
  myServo.write(90); // Neutral position
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  delay(1000); // Wait for 1 second
}
