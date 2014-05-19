#This is included here in case sudo is needed
ARDUINO_DIR=/home/joe/Arduino/arduino-1.0.5
ARDMK_DIR=/home/joe/Arduino/Arduino-Makefile
AVR_TOOLS_DIR=/usr

BOARD_TAG = trinket3
ISP_PROG = usbtiny
ISP_PORT = /dev/ttyACM0
ARDUINO_LIBS = Adafruit_Neopixel
ALTERNATE_CORE = attiny

include ../../Arduino/Arduino-Makefile/Arduino.mk

#avrdude -c usbtiny -p attiny85 -U flash:w:build-trinket3/flip_cup.hex
#avrdude -c usbtiny -p attiny85 -D -U flash:w:build-trinket3/flip_cup.hex
