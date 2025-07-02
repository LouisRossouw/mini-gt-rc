#ifndef ServoStep_h
#define ServoStep_h

#include "Arduino.h"

class ServoStep
{
public:
    ServoStep(int pin, int channel);

public:
    void servoSpin(int speed);
    void servoTurn(int angle);
    void servoSet(int angle);
    double duty;

private:
    int _pin;
    int _channel;
};

#endif