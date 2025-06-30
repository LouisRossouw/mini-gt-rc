#include "src/globals.h"
#include <Arduino.h>
#include <Bluepad32.h>

ServoStep myServo(3);

// Arduino setup function. Runs in CPU 1
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
  const int rearLightPin = Car::RearLights.pin; // GPIO2 for rear/brake lights
  const int pwmChannel = Car::RearLights.pin;   // Choose a free PWM channel
  const int pwmFreq = 5000;                     // 5kHz
  const int pwmResolution = 8;                  // 8-bit resolution: 0-255

  // RearLights
  ledcSetup(pwmChannel, pwmFreq, pwmResolution);
  ledcAttachPin(rearLightPin, pwmChannel);

  pinMode(Car::HeadLights.pin, OUTPUT); // Headlights

  pinMode(Car::LeftFlicker.pin, OUTPUT);  // Left indicators
  pinMode(Car::RightFlicker.pin, OUTPUT); // Right indicators

  servoSetup();
}

void servoSetup()
{
  const int servoPin = 3; // replace with your pin
  const int pwmChannel = 0;
  const int pwmFreq = 200;     // 50Hz = 20ms period
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