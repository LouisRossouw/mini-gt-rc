# === Config ===


# Need to compile with this core for arduino-cli
# **** Bluepad32: esp32-c3 ****
FQBN=esp32-bluepad32:esp32:lolin_c3_mini
PORT=COM8

# **** Bluepad32: esp32-wroom-32 ****
# FQBN=esp32-bluepad32:esp32:esp32da
# PORT=COM7



BAUD=115200
PROJECT_NAME=esp32-gamepad-starter
SKETCH=$(PROJECT_NAME).ino

# === Arduino CLI settings ===
ARDUINO_CLI=arduino-cli

# === Commands ===
.PHONY: default lint all upload compile monitor clean info

default: all

lint:
	cpplint --extensions=ino --filter=-legal/copyright,-runtime/int *.ino

all: compile upload monitor

compile:	
	$(ARDUINO_CLI) compile --fqbn $(FQBN) .

upload:
	$(ARDUINO_CLI) upload -p $(PORT) --fqbn $(FQBN) .

# **** For Bluepad32: esp32-c3
monitor:
	$(ARDUINO_CLI) monitor -p $(PORT) --fqbn $(FQBN)

# **** For Bluepad32: esp32-wroom-32
# monitor:
# 	$(ARDUINO_CLI) monitor -p $(PORT) --config baudrate=$(BAUD)

clean:
	rm -rf build .arduino*

info:
	$(ARDUINO_CLI) board list
