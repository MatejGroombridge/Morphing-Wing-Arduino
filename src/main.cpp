#include <Arduino.h>
#include <Servo.h>

Servo myServo; // create servo object to control a servo

const int led1 = 7; // LED connected to digital pin 7
const int led2 = 8; // LED connected to digital pin 8

void setup()
{
  // put your setup code here, to run once:
  myServo.attach(9);     // attaches the servo on pin 9 to the servo object
  pinMode(led1, OUTPUT); // Set led1 as an output
  pinMode(led2, OUTPUT); // Set led2 as an output
}

void loop()
{
  // Rotate clockwise at full speed
  myServo.write(180);       // Set servo to 180 degrees
  digitalWrite(led1, HIGH); // Turn on led1
  digitalWrite(led2, HIGH); // Turn off led2
  delay(2000);              // Wait for 2 seconds

  // Stop the servo
  myServo.write(93);       // Set servo to 90 degrees (stop)
  digitalWrite(led1, LOW); // Turn off led1
  digitalWrite(led2, LOW); // Turn off led2
  delay(1000);             // Wait for 2 seconds
}