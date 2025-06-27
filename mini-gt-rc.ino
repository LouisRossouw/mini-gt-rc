#include "src/globals.h"
#include <Arduino.h>
#include <Bluepad32.h>

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
  const int servoPin = Car::MotorRear.pin; // replace with your pin
  const int pwmChannel = Car::MotorRear.pin;
  const int pwmFreq = 50;       // 50Hz = 20ms period
  const int pwmResolution = 16; // 16-bit resolution = 0–65535

  ledcSetup(pwmChannel, pwmFreq, pwmResolution);
  ledcAttachPin(servoPin, pwmChannel);

  // Move servo to center (90°)
  writeServoAngle(90);
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

void writeServoAngle(int angle)
{
  // Map angle (0–180) to pulse width (1ms–2ms), converted to 16-bit value
  int dutyMin = 3277; // ~1ms at 50Hz = 3277 ticks
  int dutyMax = 6554; // ~2ms at 50Hz = 6554 ticks
  int duty = map(angle, 0, 180, dutyMin, dutyMax);
  ledcWrite(Car::MotorRear.pin, duty);
}