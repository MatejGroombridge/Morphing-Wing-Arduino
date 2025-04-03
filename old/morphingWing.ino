#include <Arduino.h>
#include <Servo.h> // Include the Servo library

Servo myServo; // Create a Servo object

const int led1 = 7;    // LED 1 connected to pin 7
const int led2 = 8;    // LED 2 connected to pin 8
const int potPin = A0; // Potentiometer connected to analog pin A0

int potValue;     // Variable to store the potentiometer value (0 to 1023)
int angle;        // Variable to store the servo angle (0 to 90 degrees)
int servoPin = 9; // Servo connected to pin 9
int servoValue;   // Variable to store the servo value (0 to 180 degrees)

void setup()
{
    myServo.attach(servoPin); // Attach the servo to pin 9
    pinMode(led1, OUTPUT);    // Set led1 as an output
    pinMode(led2, OUTPUT);    // Set led2 as an output
}

void loop()
{
    potValue = analogRead(potPin);          // Read the potentiometer value
    angle = map(potValue, 0, 1023, 0, 90);  // Map the value to a range of 0 to 90 degrees
    servoValue = map(angle, 0, 90, 0, 180); // Map the angle to a range of 0 to 180 degrees

    myServo.write(servoValue); // Rotate the servo to the calculated angle
    digitalWrite(led1, HIGH);  // Turn on led1
    digitalWrite(led2, LOW);   // Turn off led2
    delay(20);                 // Short delay to allow the servo to reach the desired angle

    // Stop the servo
    myServo.write(90);        // Set servo to neutral position (stop)
    digitalWrite(led1, LOW);  // Turn off led1
    digitalWrite(led2, HIGH); // Turn on led2
}