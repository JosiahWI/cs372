FM=clang-format

all: eeprom.ino CS372EEPROM.cpp CS372EEPROM.h cs372ecc.cpp cs372ecc.h
	arduino-cli compile --fqbn teensy:avr:teensy40

#
# Format source and header files
#
format:
	$(FM) -i *.ino *.cpp *.h
