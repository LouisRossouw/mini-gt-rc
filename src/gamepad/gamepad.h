#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <Arduino.h>
#include <Bluepad32.h>

void processControllers();
void dumpGamepad(ControllerPtr ctl);
void onDisconnectedController(ControllerPtr ctl);
void onConnectedController(ControllerPtr ctl);

#endif
