#include "../dev/dev.h"

#include "gamepad.h"
#include <Arduino.h>
#include <Bluepad32.h>

void processGamepad(ControllerPtr ctl)
{
    // Temp
    if (ctl->y() && ctl->b())
    {
        Dev::toggle();
    }
}
