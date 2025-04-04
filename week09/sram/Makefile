FM=clang-format

all: sram.ino ParallelSRAM.cpp ParallelSRAM.h
	arduino-cli compile --fqbn teensy:avr:teensy40

#
# Format source and header files
#
format:
	$(FM) -i *.ino *.cpp *.h
