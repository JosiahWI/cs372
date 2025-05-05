FM=clang-format

all: stepper.ino
	arduino-cli compile --fqbn teensy:avr:teensy40

#
# Format source and header files
#
format:
	$(FM) -i *.ino *.h
