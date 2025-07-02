#include "Arduino.h"
#include "ServoStep.h"
#include "../globals.h"

// Updating the servo with PWN signals, as there is no servo lib for esp32-c3
// * Works great with the servo plugged into 3v and not 5v.

ServoStep::ServoStep(int pin, int channel)
{
    _pin = pin;
    _channel = channel;
    ledcSetup(_channel, 200, 8);
    ledcAttachPin(_pin, _channel);
}

void ServoStep::servoSet(int angle)
{
    duty = (map(angle, 0, 180, 5, 25)) * 5.1;
    ledcWrite(_channel, duty);
    delay(300);
}

// Forward declare fmap
float fmap(float x, float in_min, float in_max, float out_min, float out_max);

// Drive wheels forward or backwards.
void ServoStep::servoSpin(int speed)
{
    float duty = fmap(speed, -512.0, 512.0, 120.0, 130.0);
    ledcWrite(_channel, duty);
    Dev::log(String(speed) + " | " + String(duty));
}

// Turn wheels left or right.
void ServoStep::servoTurn(int angle)
{
    float duty = fmap(angle, -512.0, 512.0, 50.0, 95.0);
    ledcWrite(_channel, duty);
    Dev::log(String(angle) + " -|- " + String(duty));
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
