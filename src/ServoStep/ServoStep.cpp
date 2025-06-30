#include "Arduino.h"
#include "ServoStep.h"
#include "../globals.h"

ServoStep::ServoStep(int pin)
{
    _pin = pin;
    ledcSetup(0, 200, 8);
    ledcAttachPin(_pin, 0);
}

void ServoStep::servoSet(int angle)
{
    duty = (map(angle, 0, 180, 5, 25)) * 5.1;
    // 5.1 is the ratio of pulse width (in decimilliseconds)to duty cycle at a fequency of 200Hz (the minimum for ledc on esp32c3)
    ledcWrite(0, duty); // write to servo
    delay(300);
}

void ServoStep::servoUp()
{
    ledcWrite(0, 77);  // 90degress
    ledcWrite(0, 128); // 180 degrees
    delay(300);
    ledcWrite(0, 77); // 90 degrees
}

void ServoStep::servoDown()
{
    ledcWrite(0, 77); // 90degress
    ledcWrite(0, 26); // 0 degrees
    delay(300);
    ledcWrite(0, 77); // 90 degrees
}

// Forward declare fmap
float fmap(float x, float in_min, float in_max, float out_min, float out_max);

void ServoStep::servoSpin(int speed)
{
    // float duty = fmap(speed, -512.0, 512.0, 122.0, 130.0);
    float duty = fmap(speed, -512.0, 512.0, 120.0, 130.0);
    ledcWrite(0, duty);
    Dev::log(String(speed) + " | " + String(duty));
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
