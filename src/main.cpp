#include <Arduino.h>
#include <Servo.h>
// #include <LiquidCrystal.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Servo servo1;
Servo servo2;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

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

unsigned long lastDisplayUpdate = 0;
const unsigned long displayInterval = 500;

void setup()
{
    servo1.attach(9);
    servo2.attach(10);
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);

    for (int i = 0; i < numReadings; i++)
    {
        readings[i] = analogRead(potPin);
        total += readings[i];
        delay(10);
    }

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("Hello!"));
    display.setCursor(0, 20);
    display.setTextSize(1);
    display.println(F("Instructions: Turn the knob to control morph angle."));
    display.setCursor(0, 48);
    display.println(F("By Matej, Gavinu, Aarnav, Elijah & Sam"));
    display.display();
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
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
    angle = constrain(map(smoothedValue, 0, 1023, 0, 180), 0, 180);

    servo1.write(angle);
    servo2.write(180 - angle);

    // if (millis() - lastDisplayUpdate >= displayInterval)
    // {
    //     lastDisplayUpdate = millis();
    //     prevAngle = angle;

    //     display.clearDisplay();
    //     display.setCursor(0, 0);
    //     display.setTextSize(2);
    //     display.setTextColor(SSD1306_WHITE);
    //     display.print(F("Angle: "));
    //     display.print(angle);
    //     display.display();
    // }

    if ((angle / 30 != prevAngle / 30) || (angle < 10 || angle > 165))
    {
        digitalWrite(ledPin, HIGH);
        delay(100);
        prevAngle = angle;
    }
    else
    {
        digitalWrite(ledPin, LOW);
    }

    Serial.print("Potentiometer Value: ");
    Serial.print(potValue);
    Serial.print(" | Angle: ");
    Serial.println(angle);

    delay(20);
}