
# 🏎️ ESP32 C3 Super Mini Micro RC
### Firmware for my micro RC; using an xbox one controller + an esp32-c3 super mini + Mini GT #658 1:64 car.

YouTube;
https://www.youtube.com/shorts/F8KlSNT8m0E

Short Gif:

![pies2 (1)](https://github.com/user-attachments/assets/f3198826-a7c1-49fc-82de-3c3a2836c1fd)

# Setup

## 📍 Pins
- SG90: (drive) pin `3`
- linear servo (steering) pin: `4`
- headlights leds pin: `5`
- Rearlights leds pin: `6`
- Left indicator pin: `7`
- Right indicator pin: `8`

## 🛠️ Parts used in the demo gif:
- esp32 c3 super mini
- sg90 servo (removed potentiometer and replaced with two resistors)
- 1.5g digital linear brushless servo
- 2x4x2.5 miniature ball bearings
- 6 smd leds, oragne, red, white
- 0.18mm enamel copper wire
- 3D printed frame
- xbox one controller (Latest firmware works with esp32c3 Bluetooth low energy)

## 🤖 Compile & upload
- Uses `arduinio_cli` to compile and upload
- If on windows, use git bash in project directory to run `./Makefile`
- Use the commands in the Makefile to compile / upload / monitor to esp32-c3 board. ie; run `make` or `make monitor` etc

## Reminder for self
- all of my esp32 c3 boards automatically reset after upload except for one board, 
this specific board requires me to first flash it (hold down reset + boot for a few seconds, and let go of reset first before boot), then compile and upload, and finally push reset for it to run the new firmware.
TODO: fix intellisense



