#ifndef ServoStep_h
#define ServoStep_h

#include "Arduino.h"

class ServoStep
{
public:
    ServoStep(int pin);

public:
    void servoUp();
    void servoDown();
    void servoSpin(int speed);
    void servoSet(int angle);
    double duty;

private:
    int _pin;
};

#endif