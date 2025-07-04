#include "src/globals.h"
#include <Arduino.h>
#include <Bluepad32.h>

ServoStep myServo(3, 2);
ServoStep myServoTest(4, 4);

void setup()
{
  Serial.begin(115200);
  Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
  const uint8_t *addr = BP32.localBdAddress();
  Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

  BP32.setup(&onConnectedController, &onDisconnectedController);
  BP32.forgetBluetoothKeys();

  setupPins();
}

void setupPins()
{
  // Updating lights with PWM signla; to simulate brake lights
  const int rearLightPin = Car::RearLights.pin;
  const int pwmChannel = Car::RearLights.pin;
  const int pwmFreq = 5000;
  const int pwmResolution = 8;

  // RearLights
  ledcSetup(pwmChannel, pwmFreq, pwmResolution);
  ledcAttachPin(rearLightPin, pwmChannel);

  // Headlights
  pinMode(Car::HeadLights.pin, OUTPUT);

  // indicators
  pinMode(Car::LeftFlicker.pin, OUTPUT);
  pinMode(Car::RightFlicker.pin, OUTPUT);
}

void loop()
{
  // This call fetches all the controllers' data.
  bool dataUpdated = BP32.update();
  if (dataUpdated)
    processControllers();

  Car::loop();

  delay(150);
}