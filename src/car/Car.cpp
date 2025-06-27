#include <Arduino.h>
#include "car.h"
// #include "../globals.h"

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

// Rearlights
bool Car::isRearLightsEnabled = false;
bool Car::isBreakLightsEnabled = false;

bool Car::activeLights = false;

int maxBrightness = Car::RearLights.maxBrightness;
int defaultBrightness = Car::RearLights.defaultBrightness;

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

    digitalWrite(Car::HeadLights.pin, activeLights ? HIGH : LOW);
    ledcWrite(Car::RearLights.pin, activeLights ? defaultBrightness : 0);
}

void Car::toggleHeadLights()
{
    isHeadLightsEnabled = !isHeadLightsEnabled;
    digitalWrite(Car::HeadLights.pin, isHeadLightsEnabled ? LOW : HIGH);
}

void Car::toggleRearLights()
{
    isRearLightsEnabled = !isRearLightsEnabled;
    ledcWrite(Car::RearLights.pin, isRearLightsEnabled ? defaultBrightness : 0);
}

void Car::toggleBrakeLights()
{

    isBreakLightsEnabled = !isBreakLightsEnabled;
    if (isBreakLightsEnabled)
    {
        ledcWrite(Car::RearLights.pin, maxBrightness);
    }
    else if (isRearLightsEnabled)
    {
        ledcWrite(Car::RearLights.pin, defaultBrightness);
    }
    else
    {
        ledcWrite(Car::RearLights.pin, 0);
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