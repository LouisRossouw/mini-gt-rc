#include "dev.h"

bool Dev::enabled = false;

void Dev::log(const String &message)
{
    if (enabled)
    {
        Serial.println(message);
    }
}

void Dev::toggle()
{
    enabled = !enabled;
    log("Dev updated to: " + String(enabled ? "true" : "false"));
}

bool Dev::isEnabled()
{
    return enabled;
}