#ifndef DEV_H
#define DEV_H

#include <Arduino.h>

class Dev
{
public:
    static bool enabled;

    static void log(const String &msg);
    static void toggle();
    static bool isEnabled();
};

#endif
