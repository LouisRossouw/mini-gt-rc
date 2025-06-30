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
    static void toggleHeadLights();
    static void toggleLights();

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

    static constexpr LightConfig LeftFlicker = {21, 0, 255};
    static constexpr LightConfig RightFlicker = {20, 0, 255};
    static constexpr LightConfig HeadLights = {2, 0, 255};
    static constexpr LightConfig RearLights = {1, 40, 255};

    // Motor configuration
    struct MotorConfig
    {
        uint8_t pin;
    };

    static constexpr MotorConfig MotorRear = {18};
};

#endif
