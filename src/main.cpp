#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal.h>

Servo servo1;
Servo servo2;
LiquidCrystal display(2, 3, 4, 5, 6, 7);

int potPin = A5;
int potValue;
int angle;
int prevAngle = 90;
int ledPin = 2;

const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
int total = 0;
int smoothedValue = 0;

void setup()
{
    servo1.attach(9);
    servo2.attach(10);
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    potValue = analogRead(potPin);

    // Subtract the oldest reading. Read and add the new value. Advance to the next index.
    total -= readings[readIndex];
    readings[readIndex] = analogRead(potPin);
    total += readings[readIndex];
    readIndex = (readIndex + 1) % numReadings;

    smoothedValue = total / numReadings;
    angle = map(smoothedValue, 0, 1023, 0, 180);

    servo1.write(angle);
    servo2.write(180 - angle);

    if ((angle / 30 != prevAngle / 30) || (angle < 10 || angle > 165))
    {
        digitalWrite(ledPin, HIGH);
        delay(100);
        prevAngle = angle;
    }
    else
    {
        digitalWrite(ledPin, LOW); // Turn LED off
    }

    Serial.print("Potentiometer Value: ");
    Serial.print(potValue);
    Serial.print(" | Angle: ");
    Serial.println(angle);

    delay(20);
}