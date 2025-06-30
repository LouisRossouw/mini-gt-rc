#include "../dev/dev.h"
#include "../car/car.h"
#include "../globals.h"

#include "gamepad.h"
#include <Arduino.h>
#include <Bluepad32.h>

void processGamepad(ControllerPtr ctl)
{
    // Toggle rearlights
    // if (ctl->dpad() & 0x02)
    // {
    //     Car::toggleRearLights();
    // }

    // Toggle rear brake lights
    if (ctl->a())
    {
        Car::toggleBrakeLights();
    }

    // Toggle headlights
    // if (ctl->dpad() & 0x01)
    // {
    //     Car::toggleHeadLights();
    // }

    // Toggle left flicker light.
    if (ctl->dpad() & 0x08)
    {
        Car::toggleLeftFlicker();
    }

    // Toggle right flicker light.
    if (ctl->dpad() & 0x04)
    {
        Car::toggleRightFlicker();
    }

    // Toggle hazard light.
    if (ctl->dpad() & 0x02)
    {
        Car::toggleHazardLights();
    }

    // Toggle lights, ie head light & rear lights.
    if (ctl->dpad() & 0x01)
    {
        Car::toggleLights();
    }

    if (ctl->x())
    {
        Car::driveForward();
    }

    if (ctl->axisY())
    {

        myServo.servoSpin(ctl->axisY());
    }

    // the start button + select button
    if ((ctl->miscButtons() & (0x04 | 0x02)) == (0x04 | 0x02))
    {
        Dev::toggle();
    }
}
