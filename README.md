WIP
Simple setup, uses arduino-cli and make,
Currently setup for esp32-c3 & esp32-wroom-32

TO run:

- If on windows, use git bash in project directory to run "make"
- use the commands in the Makefile to compile / upload / monitor. ie run "make" in the terminal of the project and it will run the default command found in the Makefile, or "make monitor" etc

Tips;
For arduino-cli + bluepad32, need to compile with esp32-bluepad32:esp32:lolin_c3_mini

- press button Y + B at the same time enables dumpGamepad and outputs button values

TODO: fix intellisense
