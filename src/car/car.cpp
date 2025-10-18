#include "car.h"
#include "../globals.h"
#include <Arduino.h>
#include "../dev/dev.h"

// Left indicators
bool Car::isLeftIndicatorLedOn = false;
bool Car::isLeftIndicatorEnabled = false;
unsigned long Car::lastLeftIndicatorToggleTime = 0;

// Left indicators
bool Car::isRightIndicatorLedOn = false;
bool Car::isRightIndicatorEnabled = false;
unsigned long Car::lastRightIndicatorToggleTime = 0;

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

void Car::toggleDriveMode()
{
    driveMode += 1;

    if (driveMode > 2)
    {
        driveMode = 0;
    }
}

void Car::toggleLeftIndicator()
{
    isLeftIndicatorEnabled = !isLeftIndicatorEnabled;

    if (!isLeftIndicatorEnabled)
    {
        digitalWrite(Car::LeftIndicator.pin, LOW);
        isLeftIndicatorLedOn = false;
    };

    digitalWrite(RightIndicator.pin, LOW);

    isRightIndicatorEnabled = false;
    isRightIndicatorLedOn = false;
}

void Car::updateLeftIndicator()
{
    if (!isLeftIndicatorEnabled)
        return;

    unsigned long now = millis();
    if (now - lastLeftIndicatorToggleTime >= 500)
    {
        lastLeftIndicatorToggleTime = now;
        isLeftIndicatorLedOn = !isLeftIndicatorLedOn;
        digitalWrite(Car::LeftIndicator.pin, isLeftIndicatorLedOn ? HIGH : LOW);
    };
}

void Car::toggleRightIndicator()
{
    isRightIndicatorEnabled = !isRightIndicatorEnabled;

    if (!isRightIndicatorEnabled)
    {
        digitalWrite(Car::RightIndicator.pin, LOW);
        isRightIndicatorLedOn = false;
    };

    digitalWrite(Car::LeftIndicator.pin, LOW);

    isLeftIndicatorEnabled = false;
    isLeftIndicatorLedOn = false;
}

void Car::toggleHazardLights()
{

    isLeftIndicatorEnabled = !isLeftIndicatorEnabled;

    if (!isLeftIndicatorEnabled)
    {
        digitalWrite(Car::LeftIndicator.pin, LOW);
        isLeftIndicatorLedOn = false;
    };

    isRightIndicatorEnabled = !isRightIndicatorEnabled;

    if (!isRightIndicatorEnabled)
    {
        digitalWrite(Car::RightIndicator.pin, LOW);
        isRightIndicatorLedOn = false;
    };
}

void Car::updateRightIndicator()
{
    if (!isRightIndicatorEnabled)
        return;

    unsigned long now = millis();
    if (now - lastRightIndicatorToggleTime >= 500)
    {
        lastRightIndicatorToggleTime = now;
        isRightIndicatorLedOn = !isRightIndicatorLedOn;
        digitalWrite(Car::RightIndicator.pin, isRightIndicatorLedOn ? HIGH : LOW);
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
    return isLeftIndicatorEnabled && isRightIndicatorEnabled;
}

// Loop that is used in the .ino loop.
void Car::loop()
{
    Car::updateLeftIndicator();
    Car::updateRightIndicator();
}
