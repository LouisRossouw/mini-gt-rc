Firmware for a micro RC; using an xbox one controller + an esp32-c3 super mini + Mini GT #658 1:64 car.

Simple setup, uses arduino-cli and make,
Currently setup for esp32-c3 & esp32-wroom-32

To run:

- If on windows, use git bash in project directory to run "make"
- use the commands in the Makefile to compile / upload / monitor. ie run "make" in the terminal of the project and it will run the default command found in the Makefile, or "make monitor" etc

Tips;
For arduino-cli + bluepad32, need to compile with esp32-bluepad32:esp32:lolin_c3_mini

- press button Y + B at the same time enables dumpGamepad and outputs button values

TODO: fix intellisense

In action!

YouTube;
https://www.youtube.com/shorts/F8KlSNT8m0E

Short Gif:
![pies2 (1)](https://github.com/user-attachments/assets/f3198826-a7c1-49fc-82de-3c3a2836c1fd)


