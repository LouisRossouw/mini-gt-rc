#include "../dev/dev.h"
#include "../car/car.h"
#include "../globals.h"

#include "gamepad.h"
#include <Arduino.h>
#include <Bluepad32.h>

void processGamepad(ControllerPtr ctl)
{

    // Toggle rear brake lights
    if (ctl->a())
    {
        Car::toggleBrakeLights();
    }

    if (ctl->x())
    {
        digitalWrite(LED_BUILTIN, LOW);
    }
    if (ctl->y())
    {
        Car::toggleDriveMode();
    }
    if (ctl->b())
    {
        Car::toggleBrightHeadLights();
    }

    // Toggle left Indicator light.
    if (ctl->dpad() & 0x08)
    {
        Car::toggleLeftIndicator();
    }

    // Toggle right Indicator light.
    if (ctl->dpad() & 0x04)
    {
        Car::toggleRightIndicator();
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

    if (ctl->axisY())
    {
        myServo.servoSpin(-ctl->axisY()); // Note: Reversed the values.
    }

    if (ctl->axisRX())
    {

        myServoTest.servoTurn(-ctl->axisRX()); // Note: Reversed the values.
    }

    // the start button + select button
    if ((ctl->miscButtons() & (0x04 | 0x02)) == (0x04 | 0x02))
    {
        Dev::toggle();
    }
}
