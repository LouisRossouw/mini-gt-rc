#include <stdint.h>

#ifndef CAR_H
#define CAR_H

class Car
{
public:
    // Indicators
    static bool isLeftFlickerLedOn;
    static bool isLeftFlickerEnabled;
    static unsigned long lastLeftFlickerToggleTime;

    static bool isRightFlickerLedOn;
    static bool isRightFlickerEnabled;
    static unsigned long lastRightFlickerToggleTime;

    static void toggleLeftFlicker();
    static void updateLeftFlicker();

    static void toggleHazardLights();

    static void toggleRightFlicker();
    static void updateRightFlicker();

    static bool areHazardsOn();

    // Rearlights
    static bool isRearLightsEnabled;
    static bool isBreakLightsEnabled;
    static void toggleRearLights();
    static void toggleBrakeLights();

    // Headlights
    static bool isHeadLightsEnabled;
    static bool isHeadLightsBrightsEnabled;
    static void toggleHeadLights();
    static void toggleLights();
    static void toggleBrightHeadLights();

    static int driveMode;
    static void toggleDriveMode();

    static bool activeDrive;
    static void driveForward();

    static void loop();

    static bool activeLights;

    // Light configuration
    struct LightConfig
    {
        uint8_t pin;
        uint8_t defaultBrightness;
        uint8_t maxBrightness;
    };

    static constexpr LightConfig LeftFlicker = {7, 0, 255};
    static constexpr LightConfig RightFlicker = {8, 0, 255};
    static constexpr LightConfig HeadLights = {5, 40, 255};
    static constexpr LightConfig RearLights = {6, 40, 255}; // pin, defaultBrightness, maxBrighntess

    // Motor configuration
    struct MotorConfig
    {
        uint8_t pin;
    };

    static constexpr MotorConfig MotorRear = {18};
};

#endif
