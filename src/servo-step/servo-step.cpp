#include "Arduino.h"
#include "servo-step.h"
#include "../globals.h"

#include "../car/car.h"

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

// // Forward declare fmap
float fmap(float x, float in_min, float in_max, float out_min, float out_max);

// // Turn wheels left or right.
void ServoStep::servoTurn(int angle)
{
    float duty = fmap(angle, -512.0, 512.0, 60, 100.0);
    ledcWrite(_channel, duty);
    Dev::log(String(angle) + " -|- " + String(duty));
}

void ServoStep::servoSpin(int speed)
{
    // This works great on an sg90 servo with the potentiometer replaced with two resistors.
    float duty;

    static int prevSpeed = 0;
    static bool brakesOn = false;
    static unsigned long brakeStartTime = 0;

    // Detect forward → stop transition
    bool wasMovingForward = prevSpeed > 100; // threshold for "moving"
    bool nowStopped = (speed > -50 && speed < 50);

    if (wasMovingForward && nowStopped)
    {
        Car::toggleBrakeLights();
        brakesOn = true;
        brakeStartTime = millis();
    }

    // Turn off brakes after 1 second
    if (brakesOn && (millis() - brakeStartTime > 1000))
    {
        Car::toggleBrakeLights();
        brakesOn = false;
    }

    // Servo control
    if (speed > -50 && speed < 50)
    {
        duty = 78.2;
    }
    else
    {
        // Normal speed
        if (Car::driveMode == 0)
        {
            duty = fmap(speed, -512.0, 512.0, 75.0, 80.0);
        }
        // Sport speed
        else if (Car::driveMode == 1)
        {
            duty = fmap(speed, -512.0, 512.0, 73.0, 83.0);
        }
        // Donuts power!!!!
        else if (Car::driveMode == 2)
        {
            duty = fmap(speed, -512.0, 512.0, 70.0, 95.0);
        }
    }

    ledcWrite(_channel, duty);

    prevSpeed = speed;

    Dev::log(String(speed) + " | " + String(duty));
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
