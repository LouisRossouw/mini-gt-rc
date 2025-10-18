#include "car.h"
#include "../globals.h"
#include <Arduino.h>
#include "../dev/dev.h"

// Left indicators
bool Car::isLeftFlickerLedOn = false;
bool Car::isLeftFlickerEnabled = false;
unsigned long Car::lastLeftFlickerToggleTime = 0;

// Left indicators
bool Car::isRightFlickerLedOn = false;
bool Car::isRightFlickerEnabled = false;
unsigned long Car::lastRightFlickerToggleTime = 0;

// Headlights
bool Car::isHeadLightsEnabled = false;
bool Car::isHeadLightsBrightsEnabled = false;

// Rearlights
bool Car::isRearLightsEnabled = false;
bool Car::isBreakLightsEnabled = false;

bool Car::activeLights = false;

bool Car::activeDrive = false;

int maxBrightness = Car::RearLights.maxBrightness;
int defaultBrightness = Car::RearLights.defaultBrightness;

int Car::driveMode = 0;

// TODO; Rename flicker to indicator
// TODO; Fix file names / investigate as to why they are capitalized? is that a c++ must?

void Car::toggleDriveMode()
{
    driveMode += 1;

    if (driveMode > 2)
    {
        driveMode = 0;
    }
}

void Car::toggleLeftFlicker()
{
    isLeftFlickerEnabled = !isLeftFlickerEnabled;

    if (!isLeftFlickerEnabled)
    {
        digitalWrite(Car::LeftFlicker.pin, LOW);
        isLeftFlickerLedOn = false;
    };

    digitalWrite(RightFlicker.pin, LOW);

    isRightFlickerEnabled = false;
    isRightFlickerLedOn = false;
}

void Car::updateLeftFlicker()
{
    if (!isLeftFlickerEnabled)
        return;

    unsigned long now = millis();
    if (now - lastLeftFlickerToggleTime >= 500)
    {
        lastLeftFlickerToggleTime = now;
        isLeftFlickerLedOn = !isLeftFlickerLedOn;
        digitalWrite(Car::LeftFlicker.pin, isLeftFlickerLedOn ? HIGH : LOW);
    };
}

void Car::toggleRightFlicker()
{
    isRightFlickerEnabled = !isRightFlickerEnabled;

    if (!isRightFlickerEnabled)
    {
        digitalWrite(Car::RightFlicker.pin, LOW);
        isRightFlickerLedOn = false;
    };

    digitalWrite(Car::LeftFlicker.pin, LOW);

    isLeftFlickerEnabled = false;
    isLeftFlickerLedOn = false;
}

void Car::toggleHazardLights()
{

    isLeftFlickerEnabled = !isLeftFlickerEnabled;

    if (!isLeftFlickerEnabled)
    {
        digitalWrite(Car::LeftFlicker.pin, LOW);
        isLeftFlickerLedOn = false;
    };

    isRightFlickerEnabled = !isRightFlickerEnabled;

    if (!isRightFlickerEnabled)
    {
        digitalWrite(Car::RightFlicker.pin, LOW);
        isRightFlickerLedOn = false;
    };
}

void Car::updateRightFlicker()
{
    if (!isRightFlickerEnabled)
        return;

    unsigned long now = millis();
    if (now - lastRightFlickerToggleTime >= 500)
    {
        lastRightFlickerToggleTime = now;
        isRightFlickerLedOn = !isRightFlickerLedOn;
        digitalWrite(Car::RightFlicker.pin, isRightFlickerLedOn ? HIGH : LOW);
    };
}

void Car::toggleLights()
{
    activeLights = !activeLights;

    isHeadLightsEnabled = activeLights;
    isRearLightsEnabled = activeLights;

    ledcWrite(1, activeLights ? defaultBrightness : 0);
    ledcWrite(0, activeLights ? defaultBrightness : 0);
}

void Car::toggleHeadLights()
{
    isHeadLightsEnabled = !isHeadLightsEnabled;
    ledcWrite(1, isHeadLightsEnabled ? defaultBrightness : 0);
}

void Car::toggleRearLights()
{
    isRearLightsEnabled = !isRearLightsEnabled;
    ledcWrite(0, isRearLightsEnabled ? defaultBrightness : 0);
}

void Car::toggleBrightHeadLights()
{

    isHeadLightsBrightsEnabled = !isHeadLightsBrightsEnabled;
    if (isHeadLightsBrightsEnabled)
    {
        ledcWrite(1, maxBrightness);
    }
    else if (isHeadLightsEnabled)
    {
        ledcWrite(1, defaultBrightness);
    }
    else
    {
        ledcWrite(1, 0);
    }
}

void Car::toggleBrakeLights()
{

    isBreakLightsEnabled = !isBreakLightsEnabled;
    if (isBreakLightsEnabled)
    {
        ledcWrite(0, maxBrightness);
    }
    else if (isRearLightsEnabled)
    {
        ledcWrite(0, defaultBrightness);
    }
    else
    {
        ledcWrite(0, 0);
    }
}

bool Car::areHazardsOn()
{
    return isLeftFlickerEnabled && isRightFlickerEnabled;
}

// Loop that is used in the .ino loop.
void Car::loop()
{
    Car::updateLeftFlicker();
    Car::updateRightFlicker();
}