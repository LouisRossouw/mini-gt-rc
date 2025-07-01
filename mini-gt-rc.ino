#include "src/globals.h"
#include <Arduino.h>
#include <Bluepad32.h>

ServoStep myServo(3);

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
  // Updating lights with PWN signla; to simulate brake lights
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

  servoSetup();
}

void servoSetup()
{
  // Updating the servo with PWN signals, as there is no servo lib for esp32-c3
  // * Works great with the servo plugged into 3v and not 5v.
  const int servoPin = 3;
  const int pwmChannel = 0;
  const int pwmFreq = 200;
  const int pwmResolution = 8; // 16-bit resolution = 0–65535

  ledcSetup(pwmChannel, pwmFreq, pwmResolution);
  ledcAttachPin(servoPin, pwmChannel);
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